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

#include "artificialNeuralNetwork.H"


// * * * * * * * * * * * * * * * Global Functions  * * * * * * * * * * * * * //

namespace Foam
{

// * * * * * * * * * * * * * * * * Selectors * * * * * * * * * * * * * * * * //

autoPtr<artificialNeuralNetwork> artificialNeuralNetwork::New
(
    const word& name,
    const dictionary& architectureDict,
    const scalarListListList& trainingData
)
{
    return autoPtr<artificialNeuralNetwork>(new artificialNeuralNetwork(name, architectureDict, trainingData));
}

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

artificialNeuralNetwork::artificialNeuralNetwork
(
    const word& name,
    const dictionary& architectureDict,
    const scalarListListList& trainingData
)
:
    name_(name),
    architectureDict_(architectureDict),
    trainingData_(trainingData),
    hiddenLayerNumber_(readInt(architectureDict.lookup("hiddenLayerNumber"))),
    neuronNumber_(readInt(architectureDict.lookup("neuronNumber"))),
    inputNumber_(trainingData_[0][0].size()),
    outputNumber_(trainingData_[0][1].size()),
    columnNumber_(hiddenLayerNumber_+2),
    pageNumber_(hiddenLayerNumber_+1),
    inputNormalization_(normalizationModel::New("inputNormalization", architectureDict_, "inputNormalizationModel")),
    outputNormalization_(normalizationModel::New("outputNormalization", architectureDict_, "outputNormalizationModel")),
    activationFunction_(activationFunctionModel::New("activationFunction", architectureDict_)),
    costFunction_(costFunctionModel::New("costFunction", architectureDict_)),
    learningRate_(learningRateModel::New("learningRate", architectureDict_))
{}


// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //
const scalarListListList
artificialNeuralNetwork::getBatch
(
    const scalarListListList& data,
    int batchSize,
    int currentBatch
)
{
    scalarListListList batch_;

    int startIndex = currentBatch * batchSize;
    int endIndex = std::min(startIndex + batchSize, (int)data.size());

    for(int b = 0; b < (endIndex - startIndex); b++)
    {
        //batch_[b] = data[startIndex + b];
        batch_.append(data[startIndex + b]);
    }

    return batch_;
}

const scalarListListList
artificialNeuralNetwork::dataNormalization
(
    const scalarListListList& data
)
{
    int dataNumber_ = data.size();
    scalarListListList normalizedData_(data);
    scalarList data_(dataNumber_);
    scalarList normData_(dataNumber_);


    for(int i = 0; i < data[0][0].size(); i++)
    {
        for(int d = 0; d < dataNumber_; d++)
        {
            data_[d] = data[d][0][i];
        }

        normData_ = inputNormalization_->normalization(data_);

        for(int d = 0; d < dataNumber_; d++)
        {
            normalizedData_[d][0][i] = normData_[d];
        }
    }


    for(int o = 0; o < data[0][1].size(); o++)
    {
        for(int d = 0; d < dataNumber_; d++)
        {
            data_[d] = data[d][1][o];
        }

        normData_ = outputNormalization_->normalization(data_);

        for(int d = 0; d < dataNumber_; d++)
        {
            normalizedData_[d][1][o] = normData_[d];
        }
    }

    return normalizedData_;
}


const col2Vector
artificialNeuralNetwork::col2VectorInitialization
()
{
    col2Vector inputSignal_;

    for(int c=0; c<columnNumber_; c++)
    {
        if(c == 0)
        {
            inputSignal_.push_back(colVector(inputNumber_));
        }
        else if(c == columnNumber_-1)
        {
            inputSignal_.push_back(colVector(outputNumber_));
        }
        else
        {
            inputSignal_.push_back(colVector(neuronNumber_));
        }
    }

    return inputSignal_;
}


const colVector
artificialNeuralNetwork::inputSignalInitialization
(
    const scalarListList& normalizedData
)
{
    colVector inputSignal_(normalizedData[0].size());

    for(int r=0; r<normalizedData[0].size(); r++)
    {
        inputSignal_(r) = normalizedData[0][r];
    }

    return inputSignal_;
}


const matrixVector
artificialNeuralNetwork::matrixVectorInitialization
()
{
    matrixVector m_;

    for(int p=0; p<pageNumber_; p++)
    {
        if(p == 0)
        {
            m_.push_back(matrix(neuronNumber_, inputNumber_));
        }
        else if(p == pageNumber_-1)
        {
            m_.push_back(matrix(outputNumber_, neuronNumber_));
        }
        else
        {
            m_.push_back(matrix(neuronNumber_, neuronNumber_));
        }
    }

    return m_;
}


const matrixVector
artificialNeuralNetwork::weightInitialization
()
{
    matrixVector weight_;

    for(int p=0; p<pageNumber_; p++)
    {
        if(p == 0)
        {
            weight_.push_back(matrix::Random(neuronNumber_, inputNumber_));
        }
        else if(p == pageNumber_-1)
        {
            weight_.push_back(matrix::Random(outputNumber_, neuronNumber_));
        }
        else
        {
            weight_.push_back(matrix::Random(neuronNumber_, neuronNumber_));
        }
    }

    return weight_;
}


const colVector
artificialNeuralNetwork::error
(
    const colVector& ANNOutputSignal,
    const scalarListList& normalizedData
)
{
    colVector error_(outputNumber_);

    for(int o=0; o<outputNumber_; o++)
    {
        error_(o) = normalizedData[1][o] - ANNOutputSignal(o);
    }

    return error_;
}


const matrixVector
artificialNeuralNetwork::weight
(
    IOdictionary& statisticalMetricsDict
)
{
    //- Normzlizing training data
    int trainingDataNumber_(trainingData_.size());
    scalarListListList normalizedTrainingData_ = dataNormalization(trainingData_);
    scalarListListList normalizedANNData_ = normalizedTrainingData_;


    //- Making matrices
    col2Vector inputSignal_ = col2VectorInitialization();
    col2Vector outputSignal_ = col2VectorInitialization();
    matrixVector weight_ = weightInitialization();
    matrixVector costFuncGrad2_ = matrixVectorInitialization();
    matrixVector eta_ = matrixVectorInitialization();
    matrixVector deltaWeight_ = matrixVectorInitialization();
    matrixVector G2, costFuncGrad1_;


    matrix Gd;
    colVector E;
    int batchSize_(architectureDict_.lookupOrDefault<int>("batchSize", trainingDataNumber_));
    int epochNumber_(architectureDict_.lookupOrDefault<int>("epochNumber", 1e8));
    int batchNumber_ = trainingDataNumber_/batchSize_ + ((trainingDataNumber_%batchSize_ == 0) ? 0:1);
    scalar convergence_(readScalar(architectureDict_.lookup("convergence")));
    scalar residual_ = 1.0;
    int e = 0;
    int n = 0;


    // train the neural network
    while(residual_>convergence_)
    {
        //- Making zero the matrices
        G2 = matrixVectorInitialization();
        costFuncGrad1_ = matrixVectorInitialization();

        //- A loop for an epoch
        for(int d = 0; d < trainingDataNumber_; d++)
        {
            inputSignal_[0] = inputSignalInitialization(normalizedTrainingData_[d]);
            outputSignal_[0] = inputSignal_[0];

            // forward propagation of data
            for(int p=0; p<pageNumber_; p++)
            {
                inputSignal_[p+1] = weight_[p]*outputSignal_[p];
                outputSignal_[p+1] = activationFunction_->value(inputSignal_[p+1]);
            }


            // backward propagation of errors made by neurons
            E = error(outputSignal_[columnNumber_-1], normalizedTrainingData_[d]);

            for(int p = pageNumber_-1; p>=0; p--)
            {
                Gd = costFunction_->derivative(E, outputSignal_[p], inputSignal_[p+1]);
                costFuncGrad1_[p] += Gd;
                G2[p] += matrix(Gd.array().pow(2));
                E = weight_[p].transpose()*E;
            }
        }


        // update the weights of connections
        residual_ = 0.0;
        for(int p=0; p<pageNumber_; p++)
        {
            costFuncGrad1_[p] /= trainingDataNumber_;
            costFuncGrad2_[p] += G2[p]/trainingDataNumber_;
            eta_[p] = learningRate_->learningRate(costFuncGrad2_[p]);
            deltaWeight_[p] = -1.0*(eta_[p].array() * costFuncGrad1_[p].array());
            weight_[p] += deltaWeight_[p];
            residual_ = max(residual_ , max(deltaWeight_[p].maxCoeff(), mag(deltaWeight_[p].minCoeff())));
        }

        cout << "Residual of iteration " << n << ": " << residual_ << "\n";
        n++;
    }


    // compute the statistical Metrics
    for(int o=0; o<outputNumber_; o++)
    {
        normalizedANNData_[trainingDataNumber_-1][1][o] = outputSignal_[columnNumber_-1](o);
    }

    statisticalMetrics(normalizedTrainingData_, normalizedANNData_, statisticalMetricsDict);

    return weight_;
}


const scalarList
artificialNeuralNetwork::MAE
(
    const scalarListListList& error
)
{
    int dataNumber_ = error.size();
    scalarList MAE_(outputNumber_);

    for(int o = 0; o < outputNumber_; o++)
    {
        MAE_[o] = 0.0;

        for(int d = 0; d < dataNumber_; d++)
        {
            MAE_[o] += mag(error[d][1][o]);
        }

        MAE_[o] /= dataNumber_;
    }

    return MAE_;
}


const scalarList
artificialNeuralNetwork::MSE
(
    const scalarListListList& error
)
{
    int dataNumber_ = error.size();
    scalarList MSE_(outputNumber_);

    for(int o = 0; o < outputNumber_; o++)
    {
        MSE_[o] = 0.0;

        for(int d = 0; d < dataNumber_; d++)
        {
            MSE_[o] += pow((error[d][1][o]), 2.0);
        }

        MSE_[o] /= dataNumber_;
    }

    return MSE_;
}


const scalarList
artificialNeuralNetwork::RMSD
(
    const scalarListListList& error
)
{
    scalarList RMSD_(outputNumber_);
    scalarList MSE_ = MSE(error);

    for(int o = 0; o < outputNumber_; o++)
    {
        RMSD_[o] = sqrt(MSE_[o]);
    }

    return RMSD_;
}


const scalarList
artificialNeuralNetwork::R2
(
    const scalarListListList& actualData,
    const scalarListListList& error
)
{
    int dataNumber_ = actualData.size();
    scalarList R2_(outputNumber_);
    scalarList actualDataAverage_(outputNumber_);
    
    for(int o = 0; o < outputNumber_; o++)
    {
        actualDataAverage_[o] = 0.0;

        for(int d = 0; d < dataNumber_; d++)
        {
            actualDataAverage_[o] += actualData[d][1][o];
        }

        actualDataAverage_[o] /= dataNumber_;
    }

    scalarList SRes_(outputNumber_);
    scalarList STot_(outputNumber_);

    for(int o = 0; o < outputNumber_; o++)
    {
        SRes_[o] = 0.0;
        STot_[o] = 0.0;

        for(int d = 0; d < dataNumber_; d++)
        {
            SRes_[o] += pow((error[d][1][o]), 2.0);
            STot_[o] += actualData[d][1][o] - actualDataAverage_[o];
        }

        R2_[o] = 1.0 - (SRes_[o]/STot_[o]);
    }

    return R2_;
}


void artificialNeuralNetwork::statisticalMetrics
(
    const scalarListListList& actualData,
    const scalarListListList& ANNData,
    IOdictionary& statisticalMetricsDict
)
{
    dictionary statisticalMetrics_ = architectureDict_.subDict("statisticalMetrics");
    word MAEStatus_ = statisticalMetrics_.lookup("MAE");
    word MSEStatus_ = statisticalMetrics_.lookup("MSE");
    word RMSDStatus_ = statisticalMetrics_.lookup("RMSD");
    word R2Status_ = statisticalMetrics_.lookup("R2");

    int dataNumber_(actualData.size());
    scalarListListList error_ = actualData;

    for(int d = 0; d < dataNumber_; d++)
    {
        for(int o = 0; o < outputNumber_; o++)
        {
            error_[d][1][o] = actualData[d][1][o] - ANNData[d][1][o];
        }
    }

    //- Compute and print MAE
    if(MAEStatus_ == "yes")
    {
        scalarList MAE_ = MAE(error_);
        statisticalMetricsDict.add("MAE", MAE_);
        Info << "MAE: " << MAE_ << endl;
    }

    //- Compute and print MSE
    if(MSEStatus_ == "yes")
    {
        scalarList MSE_ = MSE(error_);
        statisticalMetricsDict.add("MSE", MSE_);
        Info << "MSE: " << MSE_ << endl;
    }

    //- Compute and print RMSD
    if(RMSDStatus_ == "yes")
    {
        scalarList RMSD_ = RMSD(error_);
        statisticalMetricsDict.add("RMSD", RMSD_);
        Info << "RMSD: " << RMSD_ << endl;
    }

    //- Compute and print R2
    if(R2Status_ == "yes")
    {
        scalarList R2_ = R2(actualData, error_);
        statisticalMetricsDict.add("R2", R2_);
        Info << "R2: " << R2_ << endl;
    }
}


const scalarListList
artificialNeuralNetwork::predictedSingleData
(
    const scalarListList& singleData,
    const matrixVector& weight
)
{
    scalarListList predictedSingleData_ = singleData;
    scalarListList normalizedPredictedSingleData_ = singleData;
    scalarList unnormalizedData_(trainingData_.size());


    for(int i = 0; i < inputNumber_; i++)
    {
        for(int d = 0; d < trainingData_.size(); d++)
        {
            unnormalizedData_[d] = trainingData_[d][0][i];
        }

        normalizedPredictedSingleData_[0][i] = inputNormalization_->singleNormalization(unnormalizedData_, singleData[0][i]);
    }


    //- Making matrices
    col2Vector inputSignal_ = col2VectorInitialization();
    inputSignal_[0] = inputSignalInitialization(normalizedPredictedSingleData_);
    col2Vector outputSignal_ = col2VectorInitialization();
    outputSignal_[0] = inputSignal_[0];

    for(int p=0; p<pageNumber_; p++)
    {
        inputSignal_[p+1] = weight[p]*outputSignal_[p];
        outputSignal_[p+1] = activationFunction_->value(inputSignal_[p+1]);
    }

    for(int o = 0; o < outputNumber_; o++)
    {
        normalizedPredictedSingleData_[1][o] = outputSignal_[columnNumber_-1](o);
    }

    for(int o = 0; o < outputNumber_; o++)
    {
        for(int d = 0; d < trainingData_.size(); d++)
        {
            unnormalizedData_[d] = trainingData_[d][1][o];
        }

        predictedSingleData_[1][o] = inputNormalization_->singleUnormalization(unnormalizedData_, normalizedPredictedSingleData_[1][o]);
    }

    return predictedSingleData_;
}


const scalarListListList
artificialNeuralNetwork::predictedData
(
    const matrixVector& weight,
    const scalarListListList& data
)
{
    scalarListListList predictedData_;

    for(int d = 0; d < data.size(); d++)
    {
        predictedData_.append(predictedSingleData(data[d], weight));
    }

    return predictedData_;
}


bool artificialNeuralNetwork::read(const dictionary& architectureDict)
{
    architectureDict_ = architectureDict;

    return true;
}
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace ANN

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //
