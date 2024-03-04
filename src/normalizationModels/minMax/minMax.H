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

#ifndef minMax_H
#define minMax_H

#include "normalizationModel.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{
namespace normalizationModels
{

/*---------------------------------------------------------------------------*\
                           Class minMax Declaration
\*---------------------------------------------------------------------------*/

class minMax
:
    public normalizationModel
{
    // Private data

        dictionary minMaxCoeffs_;

        scalar a_;
        scalar b_;


public:

    //- Runtime type information
    TypeName("minMax");


    // Constructors

        //- construct from components
        minMax
        (
            const word& name,
            const dictionary& architectureDict,
            const word& normModelName
        );


    // Destructor

        virtual ~minMax()
        {}


    // Member Functions

        //- Return a scalar for normalization of a single data
        virtual scalar singleNormalization(const scalarList& data, scalar x) const;

        //- Return a scalarList for normalization of a scalarList data
        virtual const scalarList normalization(const scalarList& data) const;

        //- Return a scalar for unormalization of a single data
        virtual scalar singleUnormalization(const scalarList& data, scalar normalizedSingleData) const;

        //- Read architectureDict dictionary
        virtual bool read(const dictionary& architectureDict);
};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace normalizationModels
} // End namespace Foam

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
