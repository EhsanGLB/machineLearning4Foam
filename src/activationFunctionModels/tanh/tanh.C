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

#include "tanh.H"
#include "addToRunTimeSelectionTable.H"

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace Foam
{
namespace activationFunctionModels
{
    defineTypeNameAndDebug(tanh, 0);
    addToRunTimeSelectionTable(activationFunctionModel, tanh, dictionary);
}
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

Foam::activationFunctionModels::tanh::tanh
(
    const word& name,
    const dictionary& architectureDict
)
:
    activationFunctionModel(name, architectureDict),
    tanhCoeffs_(architectureDict.subDict(typeName + "Coeffs")),
    A_(readScalar(tanhCoeffs_.lookup("A"))),
    B_(readScalar(tanhCoeffs_.lookup("B"))),
    C_(readScalar(tanhCoeffs_.lookup("C")))
{}


// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //
Foam::scalar
Foam::activationFunctionModels::tanh::value(scalar x) const
{
    scalar X = B_*x - C_;
    return A_*(Foam::exp(X) - Foam::exp(-1.0*X))/(Foam::exp(X) + Foam::exp(-1.0*X));
}


Foam::scalar
Foam::activationFunctionModels::tanh::derivative(scalar x) const
{
    return 1.0-value(x)*value(x);
}


bool Foam::activationFunctionModels::tanh::read
(
    const dictionary& architectureDict
)
{
    activationFunctionModel::read(architectureDict);

    tanhCoeffs_ = architectureDict.subDict(typeName + "Coeffs");

    tanhCoeffs_.lookup("A") >> A_;
    tanhCoeffs_.lookup("B") >> B_;
    tanhCoeffs_.lookup("C") >> C_;

    return true;
}


// ************************************************************************* //
