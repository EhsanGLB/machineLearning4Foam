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

#include "sigmoid.H"
#include "addToRunTimeSelectionTable.H"

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace Foam
{
namespace activationFunctionModels
{
    defineTypeNameAndDebug(sigmoid, 0);
    addToRunTimeSelectionTable(activationFunctionModel, sigmoid, dictionary);
}
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

Foam::activationFunctionModels::sigmoid::sigmoid
(
    const word& name,
    const dictionary& architectureDict
)
:
    activationFunctionModel(name, architectureDict),
    sigmoidCoeffs_(architectureDict.subDict(typeName + "Coeffs")),
    A_(readScalar(sigmoidCoeffs_.lookup("A"))),
    B_(readScalar(sigmoidCoeffs_.lookup("B"))),
    C_(readScalar(sigmoidCoeffs_.lookup("C"))),
    D_(readScalar(sigmoidCoeffs_.lookup("D"))),
    E_(readScalar(sigmoidCoeffs_.lookup("E"))),
    F_(readScalar(sigmoidCoeffs_.lookup("F")))
{}


// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //
Foam::scalar
Foam::activationFunctionModels::sigmoid::value(scalar x) const
{
    return A_ + B_/(C_+D_*Foam::exp(E_*x+F_));
}

Foam::scalar
Foam::activationFunctionModels::sigmoid::derivative(scalar x) const
{
    return value(x)*(1.0-value(x));
}


bool Foam::activationFunctionModels::sigmoid::read
(
    const dictionary& architectureDict
)
{
    activationFunctionModel::read(architectureDict);

    sigmoidCoeffs_ = architectureDict.subDict(typeName + "Coeffs");

    sigmoidCoeffs_.lookup("A") >> A_;
    sigmoidCoeffs_.lookup("B") >> B_;
    sigmoidCoeffs_.lookup("C") >> C_;
    sigmoidCoeffs_.lookup("D") >> D_;
    sigmoidCoeffs_.lookup("E") >> E_;
    sigmoidCoeffs_.lookup("F") >> F_;

    return true;
}


// ************************************************************************* //
