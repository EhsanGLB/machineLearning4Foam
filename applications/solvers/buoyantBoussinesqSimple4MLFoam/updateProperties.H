
    forAll(T.internalField(), i)
    {
        singleData[0][0] = T.internalField()[i];
        singleData[0][1] = alpha.internalField()[i];
        rho.internalField()[i] = artificialNeuralNetwork->predictedSingleData(singleData, weight)[1][0];
        Cp.internalField()[i] = artificialNeuralNetwork->predictedSingleData(singleData, weight)[1][1];
        kappa.internalField()[i] = artificialNeuralNetwork->predictedSingleData(singleData, weight)[1][2];
        mu.internalField()[i] = artificialNeuralNetwork->predictedSingleData(singleData, weight)[1][3];
    }

    forAll(T.boundaryField(), i)
    {
	forAll(T.boundaryField()[i], j)
	{
            singleData[0][0] = T.boundaryField()[i][j];
            singleData[0][1] = alpha.boundaryField()[i][j];
            rho.boundaryField()[i][j] = artificialNeuralNetwork->predictedSingleData(singleData, weight)[1][0];
            Cp.boundaryField()[i][j] = artificialNeuralNetwork->predictedSingleData(singleData, weight)[1][1];
            kappa.boundaryField()[i][j] = artificialNeuralNetwork->predictedSingleData(singleData, weight)[1][2];
            mu.boundaryField()[i][j] = artificialNeuralNetwork->predictedSingleData(singleData, weight)[1][3];
	}
    }

    turbulence->correct();
    //rhok = 1.0 - beta*(T - TRef);
    rhok = rho/rhoRef;
