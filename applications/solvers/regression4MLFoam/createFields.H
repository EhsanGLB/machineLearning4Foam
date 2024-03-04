
    IOdictionary architectureDict
    (
        IOobject
        (
            "architectureDict",
            mesh,
            IOobject::MUST_READ_IF_MODIFIED,
            IOobject::NO_WRITE
        )
    );

    IOdictionary dataset
    (
        IOobject
        (
            "dataset",
            mesh,
            IOobject::MUST_READ,
            IOobject::NO_WRITE
        )
    );

    IOdictionary statisticalMetricsDict
    (
        IOobject
        (
            "statisticalMetrics",
            mesh,
            IOobject::NO_READ,
            IOobject::AUTO_WRITE
        )
    );

    scalarListListList trainingData = dataset.lookup("trainingData");
    autoPtr<artificialNeuralNetwork> artificialNeuralNetwork(artificialNeuralNetwork::New("artificialNeuralNetwork", architectureDict, trainingData));

