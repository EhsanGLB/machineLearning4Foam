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

#ifndef adaGrad_H
#define adaGrad_H

#include "learningRateModel.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{
namespace learningRateModels
{

/*---------------------------------------------------------------------------*\
                           Class adaGrad Declaration
\*---------------------------------------------------------------------------*/

class adaGrad
:
    public learningRateModel
{
    // Private data

        dictionary adaGradCoeffs_;
        scalar eta_;
        scalar epsilon_;


public:

    //- Runtime type information
    TypeName("adaGrad");


    // Constructors

        //- construct from components
        adaGrad
        (
            const word& name,
            const dictionary& architectureDict
        );


    // Destructor

        virtual ~adaGrad()
        {}


    // Member Functions

        //- Return the learningRate
        virtual matrix learningRate(const matrix& m) const;

        //- Read architectureDict dictionary
        virtual bool read(const dictionary& architectureDict);
};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace learningRateModels
} // End namespace Foam

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
