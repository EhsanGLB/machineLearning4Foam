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

#ifndef sigmoid_H
#define sigmoid_H

#include "activationFunctionModel.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{
namespace activationFunctionModels
{

/*---------------------------------------------------------------------------*\
                           Class sigmoid Declaration
\*---------------------------------------------------------------------------*/

class sigmoid
:
    public activationFunctionModel
{
    // Private data

        dictionary sigmoidCoeffs_;

        scalar A_;
        scalar B_;
        scalar C_;
        scalar D_;
        scalar E_;
        scalar F_;


public:

    //- Runtime type information
    TypeName("sigmoid");


    // Constructors

        //- construct from components
        sigmoid
        (
            const word& name,
            const dictionary& architectureDict
        );


    // Destructor

        virtual ~sigmoid()
        {}


    // Member Functions

        //- Return the value of activation function
        virtual scalar value(scalar x) const;

        //- Return the derivative of activation function
        virtual scalar derivative(scalar x) const;

        //- Read architectureDict dictionary
        virtual bool read(const dictionary& architectureDict);
};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace activationFunctionModels
} // End namespace Foam

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
