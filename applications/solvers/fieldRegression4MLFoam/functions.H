
scalarList fieldToList
(
    const volScalarField& field,
    const scalar a,
    const scalar b
)
{
    scalarList list_;

    forAll(field.internalField(), i)
    {
        list_.append(field.internalField()[i] + (b - a)*((double) rand() / (RAND_MAX)) + a);
    }

    forAll(field.boundaryField(), i)
    {
	forAll(field.boundaryField()[i], j)
	{
            list_.append(field.boundaryField()[i][j] + (b - a)*((double) rand() / (RAND_MAX)) + a);
	}
    }

    return list_;
}



void listToField
(
    const scalarList& list,
    volScalarField& field
)
{
    int n = 0;

    forAll(field.internalField(), i)
    {
        field.internalField()[i] = list[n];
        n++;
    }

    forAll(field.boundaryField(), i)
    {
	forAll(field.boundaryField()[i], j)
	{
            field.boundaryField()[i][j] = list[n];
            n++;
	}
    }
}




/*
// setRootCase.H
// ~~~~~~~~~~~~~

    Foam::argList args(argc, argv);
    if (!args.checkRootCase())
    {
        Foam::FatalError.exit();
    }

// createTime.H
// ~~~~~~~~~~~~

Foam::Info<< "Create time\n" << Foam::endl;

Foam::Time runTime(Foam::Time::controlDictName, args);
*/


    /*const fileName rootPath = runTime.rootPath();
    const fileName caseName = runTime.caseName();

    dictionary architectureDict(rootPath + "/" + caseName + "/architectureDict");
    IOdictionary dict(casePath);*/


//Time& runTime = Time::run();
//const dictionary& controlDict = runTime.controlDict();
