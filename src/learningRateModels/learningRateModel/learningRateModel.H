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
#ifndef learningRateModel_H
#define learningRateModel_H

#include "IOdictionary.H"
#include "runTimeSelectionTables.H"
#include "autoPtr.H"
#include "eigen4Foam.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{

/*---------------------------------------------------------------------------*\
                         Class learningRateModel Declaration
\*---------------------------------------------------------------------------*/

class learningRateModel
{

protected:

    // Protected data

        word name_;
        dictionary architectureDict_;

    // Private Member Functions

        //- Disallow copy construct
        learningRateModel(const learningRateModel&);

        //- Disallow default bitwise assignment
        void operator=(const learningRateModel&);

public:

    //- Runtime type information
    TypeName("learningRateModel");


    // Declare run-time constructor selection table

        declareRunTimeSelectionTable
        (
            autoPtr,
            learningRateModel,
            dictionary,
            (
                const word& name,
                const dictionary& architectureDict
            ),
            (name, architectureDict)
        );


    // Selectors

        //- Return a reference to the selected viscosity model
        static autoPtr<learningRateModel> New
        (
            const word& name,
            const dictionary& architectureDict
        );


    // Constructors

        //- Construct from components
        learningRateModel
        (
            const word& name,
            const dictionary& architectureDict
        );


    // Destructor

        virtual ~learningRateModel()
        {}


    // Member Functions

        //- Return the ANN properties dictionary
        const dictionary& architectureDict() const
        {
            return architectureDict_;
        }

        //- Return the learningRate
        virtual matrix learningRate(const matrix& m) const = 0;

        //- Read architectureDict dictionary
        virtual bool read(const dictionary& architectureDict) = 0;

};

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace Foam

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
