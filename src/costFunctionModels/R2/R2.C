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

#include "R2.H"
#include "addToRunTimeSelectionTable.H"

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace Foam
{
namespace costFunctionModels
{
    defineTypeNameAndDebug(R2, 0);
    addToRunTimeSelectionTable(costFunctionModel, R2, dictionary);
}



// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

costFunctionModels::R2::R2
(
    const word& name,
    const dictionary& architectureDict
)
:
    costFunctionModel(name, architectureDict)
{}


// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //
scalar
costFunctionModels::R2::value(scalar actualSignal, scalar predictedSignal) const
{
    return pow((actualSignal-predictedSignal), 2.0);
}


scalar
costFunctionModels::R2::derivative(scalar error, scalar signal, scalar signalSummation) const
{
    return -2.0*error*activationFunction_->derivative(signalSummation)*signal;
}


matrix
costFunctionModels::R2::derivative
(
    const colVector& error,
    const colVector& signal,
    const colVector& signalSummation
) const
{
    colVector A = error.array() * activationFunction_->derivative(signalSummation).array()*-2.0;
    matrix B = A*signal.transpose();

    return B;
}


bool costFunctionModels::R2::read
(
    const dictionary& architectureDict
)
{
    costFunctionModel::read(architectureDict);

    return true;
}

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace Foam


// ************************************************************************* //
