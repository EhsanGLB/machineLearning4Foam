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

#include "activationFunctionModel.H"

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace Foam
{
    defineTypeNameAndDebug(activationFunctionModel, 0);
    defineRunTimeSelectionTable(activationFunctionModel, dictionary);


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

activationFunctionModel::activationFunctionModel
(
    const word& name,
    const dictionary& architectureDict
)
:
    name_(name),
    architectureDict_(architectureDict)
{}


// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

colVector
activationFunctionModel::value(const colVector& X) const
{
    colVector A(X.size());

    for (size_t i = 0; i < X.size(); i++)
    {
        A(i) = value(X(i));
    }

    return A;
}


colVector
activationFunctionModel::derivative(const colVector& X) const
{
    colVector A(X.size());

    for (size_t i = 0; i < X.size(); i++)
    {
        A(i) = derivative(X(i));
    }

    return A;
}

bool activationFunctionModel::read(const dictionary& architectureDict)
{
    architectureDict_ = architectureDict;

    return true;
}

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace Foam

// ************************************************************************* //
