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

#include "dataset.H"


// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace Foam
{

void datasetGenerator
(
    scalarListList datasetDict,
    scalarListListList& predicteddataset,
    scalarListList value,
    int i
)
{
    int inputNumber = value[0].size();

    if(i == (inputNumber-1))
    {
        scalar min = datasetDict[i][0];
        scalar max = datasetDict[i][1];
        scalar number = datasetDict[i][2];
        scalar delta = (max - min)/(number-1);

        for(int n = 0; n < number; n++)
        {
            value[0][i] = min + n*delta;
            predicteddataset.append(value);
        }

        return;
    }

    else
    {
        scalar min = datasetDict[i][0];
        scalar max = datasetDict[i][1];
        scalar number = datasetDict[i][2];
        scalar delta = (max - min)/(number-1);
        i++;

        for(int n = 0; n < number; n++)
        {
            value[0][i-1] = min + n*delta;
            datasetGenerator(datasetDict, predicteddataset, value, i);
        }
    }
}

} // End namespace Foam

// ************************************************************************* //
