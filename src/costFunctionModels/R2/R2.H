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

#ifndef R2_H
#define R2_H

#include "costFunctionModel.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{
namespace costFunctionModels
{

/*---------------------------------------------------------------------------*\
                           Class R2 Declaration
\*---------------------------------------------------------------------------*/

class R2
:
    public costFunctionModel
{
    // Private data


public:

    //- Runtime type information
    TypeName("R2");


    // Constructors

        //- construct from components
        R2
        (
            const word& name,
            const dictionary& architectureDict
        );


    // Destructor

        virtual ~R2()
        {}


    // Member Functions

        //- Return the value of cost function
        virtual scalar value(scalar actualSignal, scalar predictedSignal) const;

        //- Return the derivative of cost function
        virtual scalar derivative(scalar error, scalar signal, scalar signalSummation) const;

        //- Return the derivative of cost function with array input
        virtual matrix derivative(const colVector& error, const colVector& signal, const colVector& signalSummation) const;

        //- Read architectureDict dictionary
        virtual bool read(const dictionary& architectureDict);
};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace costFunctionModels
} // End namespace Foam

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
