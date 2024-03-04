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

#include "adaGrad.H"
#include "addToRunTimeSelectionTable.H"

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace Foam
{
namespace learningRateModels
{
    defineTypeNameAndDebug(adaGrad, 0);
    addToRunTimeSelectionTable(learningRateModel, adaGrad, dictionary);
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

learningRateModels::adaGrad::adaGrad
(
    const word& name,
    const dictionary& architectureDict
)
:
    learningRateModel(name, architectureDict),
    adaGradCoeffs_(architectureDict.subDict(typeName + "Coeffs")),
    eta_(readScalar(adaGradCoeffs_.lookup("eta"))),
    epsilon_(readScalar(adaGradCoeffs_.lookup("epsilon")))
{}


// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //
matrix
learningRateModels::adaGrad::learningRate
(
    const matrix& m
) const
{
    matrix mm = m + matrix::Constant(m.rows(), m.cols(), epsilon_);
    return eta_/(mm.array().sqrt());
}


bool learningRateModels::adaGrad::read
(
    const dictionary& architectureDict
)
{
    learningRateModel::read(architectureDict);

    adaGradCoeffs_ = architectureDict.subDict(typeName + "Coeffs");
    adaGradCoeffs_.lookup("eta") >> eta_;
    adaGradCoeffs_.lookup("epsilon") >> epsilon_;

    return true;
}

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace Foam


// ************************************************************************* //
