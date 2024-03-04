/*---------------------------------------------------------------------------*\
 .----------------.  .-----------------. .-----------------.
| .--------------. || .--------------. || .--------------. |
| |      __      | || | ____  _____  | || | ____  _____  | |
| |     /  \     | || ||_   \|_   _| | || ||_   \|_   _| | |
| |    / /\ \    | || |  |   \ | |   | || |  |   \ | |   | |
| |   / ____ \   | || |  | |\ \| |   | || |  | |\ \| |   | |
| | _/ /    \ \_ | || | _| |_\   |_  | || | _| |_\   |_  | |
| ||____|  |____|| || ||_____|\____| | || ||_____|\____| | |
| |              | || |              | || |              | |
| '--------------' || '--------------' || '--------------' |
 '----------------'  '----------------'  '----------------' 



-------------------------------------------------------------------------------

\*---------------------------------------------------------------------------*/

#include "fvCFD.H"
#include "pisoControl.H"
#include "IOdictionary.H"
#include "dataset.H"
#include "artificialNeuralNetwork.H"
#include "functions.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //
int main(int argc, char *argv[])
{
#   include "setRootCase.H"
#   include "createTime.H"
#   include "createMesh.H"

    pisoControl piso(mesh);

#   include "createFields.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //
    timeSelector::addOptions();
    instantList timeDirs = timeSelector::select0(runTime, args);

    forAll(timeDirs, timeI)
    {
        runTime.setTime(timeDirs[timeI], timeI);

        if(runTime.time().value() != 0.0)
        {
            volScalarField T
            (
                IOobject
                (
                    "T",
                    runTime.timeName(),
                    mesh,
                    IOobject::MUST_READ,
                    IOobject::NO_WRITE
                ),
                mesh
            );

            inputs[0] = runTime.time().value();
            outputs = fieldToList(T, 0.0, 0.001);
            singleData[0] = inputs;
            singleData[1] = outputs;
            trainingData.append(singleData);
        }
    }


    autoPtr<artificialNeuralNetwork> artificialNeuralNetwork(artificialNeuralNetwork::New("artificialNeuralNetwork", architectureDict, trainingData));
    matrixVector weight = artificialNeuralNetwork->weight(statisticalMetricsDict);


    if(architectureDict.found("testingDataInput"))
    {
        scalarListList testingDataInput = architectureDict.lookup("testingDataInput");
        scalarListListList testingData;

        for(int d = 0; d < testingDataInput.size(); d++)
        {
            singleData[0] = testingDataInput[d];
            testingData.append(singleData);
        }


        scalarListListList predictedTestingData = artificialNeuralNetwork->predictedData(weight, testingData);


        volScalarField newT
        (
            IOobject
            (
                "T",
                runTime.timeName(),
                mesh,
                IOobject::NO_READ,
                IOobject::AUTO_WRITE
            ),
            mesh,
            dimensionedScalar("T", dimTemperature, SMALL)
        );

        for(int d = 0; d < predictedTestingData.size(); d++)
        {
            runTime.setTime(predictedTestingData[d][0][0], 0);
            listToField(predictedTestingData[d][1], newT);
            newT.write();
        }

    }


    Info<< "output Number = " << singleData[1].size() << endl;

    return 0;
}

// ************************************************************************* //
