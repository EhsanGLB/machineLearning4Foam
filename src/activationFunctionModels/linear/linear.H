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

#ifndef linear_H
#define linear_H

#include "activationFunctionModel.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{
namespace activationFunctionModels
{

/*---------------------------------------------------------------------------*\
                           Class linear Declaration
\*---------------------------------------------------------------------------*/

class linear
:
    public activationFunctionModel
{
    // Private data

        dictionary linearCoeffs_;

        scalar A_;
        scalar B_;


public:

    //- Runtime type information
    TypeName("linear");


    // Constructors

        //- construct from components
        linear
        (
            const word& name,
            const dictionary& architectureDict
        );


    // Destructor

        virtual ~linear()
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
