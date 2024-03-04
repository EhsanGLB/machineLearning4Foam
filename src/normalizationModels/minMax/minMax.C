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

#include "minMax.H"
#include "addToRunTimeSelectionTable.H"

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace Foam
{
namespace normalizationModels
{
    defineTypeNameAndDebug(minMax, 0);
    addToRunTimeSelectionTable(normalizationModel, minMax, dictionary);
}
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

Foam::normalizationModels::minMax::minMax
(
    const word& name,
    const dictionary& architectureDict,
    const word& normModelName
)
:
    normalizationModel(name, architectureDict, normModelName),
    minMaxCoeffs_(architectureDict.subDict(normModelName_+"Dict").subDict(typeName + "Coeffs")),
    a_(readScalar(minMaxCoeffs_.lookup("a"))),
    b_(readScalar(minMaxCoeffs_.lookup("b")))
{}


// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //
Foam::scalar
Foam::normalizationModels::minMax::singleNormalization
(
    const scalarList& data,
    scalar x
) const
{
    return a_ + ((x-min(data))*(b_-a_))/(max(data)-min(data));
}


const Foam::scalarList
Foam::normalizationModels::minMax::normalization
(
    const scalarList& data
) const
{
    scalarList norm_(data.size());

    forAll(data, i)
    {
        norm_[i] = singleNormalization(data, data[i]);
    }

    return norm_;
}


Foam::scalar
Foam::normalizationModels::minMax::singleUnormalization
(
    const scalarList& data,
    scalar normalizedSingleData
) const
{
    return min(data) + (normalizedSingleData-a_)*(max(data)-min(data))/(b_-a_);
}


bool Foam::normalizationModels::minMax::read
(
    const dictionary& architectureDict
)
{
    normalizationModel::read(architectureDict);

    minMaxCoeffs_ = architectureDict.subDict(normModelName_+"Dict").subDict(typeName + "Coeffs");

    minMaxCoeffs_.lookup("a") >> a_;
    minMaxCoeffs_.lookup("b") >> b_;

    return true;
}


// ************************************************************************* //
