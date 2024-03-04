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
#ifndef activationFunctionModel_H
#define activationFunctionModel_H

#include "IOdictionary.H"
#include "runTimeSelectionTables.H"
#include "autoPtr.H"
#include "eigen4Foam.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{

/*---------------------------------------------------------------------------*\
                         Class activationFunctionModel Declaration
\*---------------------------------------------------------------------------*/

class activationFunctionModel
{

protected:

    // Protected data

        word name_;
        dictionary architectureDict_;


    // Private Member Functions

        //- Disallow copy construct
        activationFunctionModel(const activationFunctionModel&);

        //- Disallow default bitwise assignment
        void operator=(const activationFunctionModel&);

public:

    //- Runtime type information
    TypeName("activationFunctionModel");


    // Declare run-time constructor selection table

        declareRunTimeSelectionTable
        (
            autoPtr,
            activationFunctionModel,
            dictionary,
            (
                const word& name,
                const dictionary& architectureDict
            ),
            (name, architectureDict)
        );


    // Selectors

        //- Return a reference to the selected viscosity model
        static autoPtr<activationFunctionModel> New
        (
            const word& name,
            const dictionary& architectureDict
        );


    // Constructors

        //- Construct from components
        activationFunctionModel
        (
            const word& name,
            const dictionary& architectureDict
        );


    // Destructor

        virtual ~activationFunctionModel()
        {}


    // Member Functions

        //- Return the ANN properties dictionary
        const dictionary& architectureDict() const
        {
            return architectureDict_;
        }

        //- Return the value of activation function
        virtual scalar value(scalar x) const = 0;

        //- Return the value of activation function with array input
        virtual colVector value(const colVector& X) const;

        //- Return the derivative of activation function
        virtual scalar derivative(scalar x) const = 0;

        //- Return the derivative of activation function with array input
        virtual colVector derivative(const colVector& X) const;

        //- Read architectureDict dictionary
        virtual bool read(const dictionary& architectureDict) = 0;

};

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace Foam

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
