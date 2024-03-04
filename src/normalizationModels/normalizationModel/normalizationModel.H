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
#ifndef normalizationModel_H
#define normalizationModel_H

#include "IOdictionary.H"
#include "runTimeSelectionTables.H"
#include "autoPtr.H"
#include "scalarList.H"
#include "fvCFD.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{

/*---------------------------------------------------------------------------*\
                         Class normalizationModel Declaration
\*---------------------------------------------------------------------------*/

class normalizationModel
{

protected:

    // Protected data

        word name_;
        dictionary architectureDict_;
        word normModelName_;


    // Private Member Functions

        //- Disallow copy construct
        normalizationModel(const normalizationModel&);

        //- Disallow default bitwise assignment
        void operator=(const normalizationModel&);

public:

    //- Runtime type information
    TypeName("normalizationModel");


    // Declare run-time constructor selection table

        declareRunTimeSelectionTable
        (
            autoPtr,
            normalizationModel,
            dictionary,
            (
                const word& name,
                const dictionary& architectureDict,
                const word& normModelName
            ),
            (name, architectureDict, normModelName)
        );


    // Selectors

        //- Return a reference to the selected viscosity model
        static autoPtr<normalizationModel> New
        (
            const word& name,
            const dictionary& architectureDict,
            const word& normModelName
        );


    // Constructors

        //- Construct from components
        normalizationModel
        (
            const word& name,
            const dictionary& architectureDict,
            const word& normModelName
        );


    // Destructor

        virtual ~normalizationModel()
        {}


    // Member Functions

        //- Return the ANN properties dictionary
        const dictionary& architectureDict() const
        {
            return architectureDict_;
        }

        //- Return the maximum of data
        inline scalar max(const scalarList& data) const
        {
            return Foam::max(data);
        }

        //- Return the minumum of data
        inline scalar min(const scalarList& data) const
        {
            return Foam::min(data);
        }

        //- Return the average of data
        inline scalar average(const scalarList& data) const
        {
            return Foam::average(data);
        }

        //- Return a scalar for normalization of a single data
        virtual scalar singleNormalization(const scalarList& data, scalar x) const = 0;

        //- Return a scalarList for normalization of a scalarList data
        virtual const scalarList normalization(const scalarList& data) const = 0;

        //- Return a scalar for unormalization of a single data
        virtual scalar singleUnormalization(const scalarList& data, scalar normalizedSingleData) const = 0;

        //- Read architectureDict dictionary
        virtual bool read(const dictionary& architectureDict) = 0;

};

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace Foam

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
