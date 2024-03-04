
    IOdictionary architectureDict
    (
        IOobject
        (
            "architectureDict",
            runTime.constant(),
            mesh,
            IOobject::MUST_READ_IF_MODIFIED,
            IOobject::NO_WRITE
        )
    );

    IOdictionary statisticalMetricsDict
    (
        IOobject
        (
            "statisticalMetrics",
            runTime.constant(),
            mesh,
            IOobject::NO_READ,
            IOobject::AUTO_WRITE
        )
    );

    scalarList inputs(1);
    scalarList outputs;
    scalarListList singleData(2);
    scalarListListList trainingData;
