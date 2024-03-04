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

#include "constant.H"
#include "addToRunTimeSelectionTable.H"

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace Foam
{
namespace learningRateModels
{
    defineTypeNameAndDebug(constant, 0);
    addToRunTimeSelectionTable(learningRateModel, constant, dictionary);
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

learningRateModels::constant::constant
(
    const word& name,
    const dictionary& architectureDict
)
:
    learningRateModel(name, architectureDict),
    constantCoeffs_(architectureDict.subDict(typeName + "Coeffs")),
    eta_(readScalar(constantCoeffs_.lookup("eta")))
{}


// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //
matrix
learningRateModels::constant::learningRate
(
    const matrix& m
) const
{
    return matrix::Constant(m.rows(), m.cols(), eta_);
}


bool learningRateModels::constant::read
(
    const dictionary& architectureDict
)
{
    learningRateModel::read(architectureDict);

    constantCoeffs_ = architectureDict.subDict(typeName + "Coeffs");
    constantCoeffs_.lookup("eta") >> eta_;

    return true;
}

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace Foam


// ************************************************************************* //
