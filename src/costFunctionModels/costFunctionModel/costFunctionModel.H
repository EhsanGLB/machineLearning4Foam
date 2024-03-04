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
#ifndef costFunctionModel_H
#define costFunctionModel_H

#include "IOdictionary.H"
#include "runTimeSelectionTables.H"
#include "autoPtr.H"
#include "activationFunctionModel.H"
#include "eigen4Foam.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{

/*---------------------------------------------------------------------------*\
                         Class costFunctionModel Declaration
\*---------------------------------------------------------------------------*/

class costFunctionModel
{

protected:

    // Protected data

        word name_;
        dictionary architectureDict_;
        autoPtr<activationFunctionModel> activationFunction_;

    // Private Member Functions

        //- Disallow copy construct
        costFunctionModel(const costFunctionModel&);

        //- Disallow default bitwise assignment
        void operator=(const costFunctionModel&);

public:

    //- Runtime type information
    TypeName("costFunctionModel");


    // Declare run-time constructor selection table

        declareRunTimeSelectionTable
        (
            autoPtr,
            costFunctionModel,
            dictionary,
            (
                const word& name,
                const dictionary& architectureDict
            ),
            (name, architectureDict)
        );


    // Selectors

        //- Return a reference to the selected viscosity model
        static autoPtr<costFunctionModel> New
        (
            const word& name,
            const dictionary& architectureDict
        );


    // Constructors

        //- Construct from components
        costFunctionModel
        (
            const word& name,
            const dictionary& architectureDict
        );


    // Destructor

        virtual ~costFunctionModel()
        {}


    // Member Functions

        //- Return the ANN properties dictionary
        const dictionary& architectureDict() const
        {
            return architectureDict_;
        }

        //- Return the value of cost function
        virtual scalar value(scalar actualSignal, scalar predictedSignal) const = 0;

        //- Return the derivative of cost function
        virtual scalar derivative(scalar error, scalar signal, scalar signalSummation) const = 0;

        //- Return the derivative of cost function with array input
        virtual matrix derivative(const colVector& error, const colVector& signal, const colVector& signalSummation) const = 0;

        //- Read architectureDict dictionary
        virtual bool read(const dictionary& architectureDict) = 0;

};

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace Foam

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
