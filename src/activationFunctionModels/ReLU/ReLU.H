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

#ifndef ReLU_H
#define ReLU_H

#include "activationFunctionModel.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{
namespace activationFunctionModels
{

/*---------------------------------------------------------------------------*\
                           Class ReLU Declaration
\*---------------------------------------------------------------------------*/

class ReLU
:
    public activationFunctionModel
{
    // Private data

        dictionary ReLUCoeffs_;

        scalar A_;


public:

    //- Runtime type information
    TypeName("ReLU");


    // Constructors

        //- construct from components
        ReLU
        (
            const word& name,
            const dictionary& architectureDict
        );


    // Destructor

        virtual ~ReLU()
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
