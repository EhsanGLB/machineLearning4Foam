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

#ifndef tanh_H
#define tanh_H

#include "activationFunctionModel.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{
namespace activationFunctionModels
{

/*---------------------------------------------------------------------------*\
                           Class tanh Declaration
\*---------------------------------------------------------------------------*/

class tanh
:
    public activationFunctionModel
{
    // Private data

        dictionary tanhCoeffs_;

        scalar A_;
        scalar B_;
        scalar C_;


public:

    //- Runtime type information
    TypeName("tanh");


    // Constructors

        //- construct from components
        tanh
        (
            const word& name,
            const dictionary& architectureDict
        );


    // Destructor

        virtual ~tanh()
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
