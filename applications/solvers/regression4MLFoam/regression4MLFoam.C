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

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //
int main(int argc, char *argv[])
{
#   include "setRootCase.H"
#   include "createTime.H"
#   include "createMesh.H"

    pisoControl piso(mesh);

#   include "createFields.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

    matrixVector weight = artificialNeuralNetwork->weight(statisticalMetricsDict);


    if(dataset.found("testingData"))
    {
        scalarListListList testingData = dataset.lookup("testingData");
        scalarListListList predictedTestingData = artificialNeuralNetwork->predictedData(weight, testingData);
        Info << "predictedTestingData: " << predictedTestingData << endl;
    }

    if(architectureDict.found("datasetGeneration"))
    {
        scalarListList datasetGenerationDict = architectureDict.lookup("datasetGeneration");
        scalarListListList generatedDataset;
        scalarListList value;
        int inputNumber = artificialNeuralNetwork->inputNumber();
        value.append(scalarList(inputNumber));
        value.append(scalarList(artificialNeuralNetwork->outputNumber()));
        int i = 0;
        datasetGenerator(datasetGenerationDict, generatedDataset, value, i);

        generatedDataset = artificialNeuralNetwork->predictedData(weight, generatedDataset);

        std::ofstream output;
        output.open("generatedDataset.txt",std::ofstream::app);

        for(int d = 0; d < generatedDataset.size(); d++)
        {
            for(int i = 0; i < generatedDataset[0][0].size(); i++)
            {
                output << generatedDataset[d][0][i] << "\t\t";
            }

            for(int o = 0; o < generatedDataset[0][1].size(); o++)
            {
                output << generatedDataset[d][1][o] << "\t\t";
            }

            output << "\n";
        }

        output.close();
    }

    return 0;
}

// ************************************************************************* //
