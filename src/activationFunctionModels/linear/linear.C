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

#include "linear.H"
#include "addToRunTimeSelectionTable.H"

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace Foam
{
namespace activationFunctionModels
{
    defineTypeNameAndDebug(linear, 0);
    addToRunTimeSelectionTable(activationFunctionModel, linear, dictionary);
}
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

Foam::activationFunctionModels::linear::linear
(
    const word& name,
    const dictionary& architectureDict
)
:
    activationFunctionModel(name, architectureDict),
    linearCoeffs_(architectureDict.subDict(typeName + "Coeffs")),
    A_(readScalar(linearCoeffs_.lookup("A"))),
    B_(readScalar(linearCoeffs_.lookup("B")))
{}


// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //
Foam::scalar
Foam::activationFunctionModels::linear::value(scalar x) const
{
    return A_*x + B_;
}


Foam::scalar
Foam::activationFunctionModels::linear::derivative(scalar x) const
{
    return A_;
}


bool Foam::activationFunctionModels::linear::read
(
    const dictionary& architectureDict
)
{
    activationFunctionModel::read(architectureDict);

    linearCoeffs_ = architectureDict.subDict(typeName + "Coeffs");
    linearCoeffs_.lookup("A") >> A_;
    linearCoeffs_.lookup("B") >> B_;

    return true;
}


// ************************************************************************* //
