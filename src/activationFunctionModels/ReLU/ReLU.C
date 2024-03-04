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

#include "ReLU.H"
#include "addToRunTimeSelectionTable.H"

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace Foam
{
namespace activationFunctionModels
{
    defineTypeNameAndDebug(ReLU, 0);
    addToRunTimeSelectionTable(activationFunctionModel, ReLU, dictionary);
}
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

Foam::activationFunctionModels::ReLU::ReLU
(
    const word& name,
    const dictionary& architectureDict
)
:
    activationFunctionModel(name, architectureDict),
    ReLUCoeffs_(architectureDict.subDict(typeName + "Coeffs")),
    A_(readScalar(ReLUCoeffs_.lookup("A")))
{}


// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //
Foam::scalar
Foam::activationFunctionModels::ReLU::value(scalar x) const
{
    return max(0 ,A_*x);
}


Foam::scalar
Foam::activationFunctionModels::ReLU::derivative(scalar x) const
{
    return (x >= 0.0) ? A_ : 0;
}


bool Foam::activationFunctionModels::ReLU::read
(
    const dictionary& architectureDict
)
{
    activationFunctionModel::read(architectureDict);

    ReLUCoeffs_ = architectureDict.subDict(typeName + "Coeffs");

    ReLUCoeffs_.lookup("A") >> A_;

    return true;
}


// ************************************************************************* //
