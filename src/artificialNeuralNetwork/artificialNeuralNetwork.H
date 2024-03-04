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
#ifndef artificialNeuralNetwork_H
#define artificialNeuralNetwork_H


#include "IOdictionary.H"
#include "autoPtr.H"
#include "tmp.H"
#include "scalarList.H"

#include "eigen4Foam.H"
#include "normalizationModel.H"
#include "activationFunctionModel.H"
#include "costFunctionModel.H"
#include "learningRateModel.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{

/*---------------------------------------------------------------------------*\
                         Class artificialNeuralNetwork Declaration
\*---------------------------------------------------------------------------*/

class artificialNeuralNetwork
{
protected:

    // Protected data

        word name_;
        dictionary architectureDict_;
        const scalarListListList& trainingData_;

        int hiddenLayerNumber_;
        int neuronNumber_;
        int inputNumber_;
        int outputNumber_;
        int rowNumber_;
        int columnNumber_;
        int pageNumber_;
        autoPtr<normalizationModel> inputNormalization_;
        autoPtr<normalizationModel> outputNormalization_;
        autoPtr<activationFunctionModel> activationFunction_;
        autoPtr<costFunctionModel> costFunction_;
        autoPtr<learningRateModel> learningRate_;


    // Private Member Functions

        //- Disallow copy construct
        artificialNeuralNetwork(const artificialNeuralNetwork&);

        //- Disallow default bitwise assignment
        void operator=(const artificialNeuralNetwork&);


public:

    // Constructors

        //- Construct from components
        artificialNeuralNetwork
        (
            const word& name,
            const dictionary& architectureDict,
            const scalarListListList& trainingData
        );

   // Selectors

        //- Select construct from dictionary
        static autoPtr<artificialNeuralNetwork> New
        (
            const word& name,
            const dictionary& architectureDict,
            const scalarListListList& trainingData
        );


    // Destructor

        virtual ~artificialNeuralNetwork()
        {}


    // Member Functions

        //- Return the ANN properties dictionary
        const dictionary& architectureDict() const
        {
            return architectureDict_;
        }

        //- Return the number of hidden layer
        int hiddenLayerNumber() const
        {
            return hiddenLayerNumber_;
        }

        //- Return the number of neuron
        int neuronNumber() const
        {
            return neuronNumber_;
        }

        //- Return the number of input
        int inputNumber() const
        {
            return inputNumber_;
        }

        //- Return the number of output
        int outputNumber() const
        {
            return outputNumber_;
        }

        //- Return the number of column
        int columnNumber() const
        {
            return columnNumber_;
        }

        //- Return the number of page
        int pageNumber() const
        {
            return pageNumber_;
        }

        //- Return a scalarListListList for batch data
        virtual const scalarListListList getBatch(const scalarListListList& data, int batchSize, int currentBatch);

        //- Return a scalarListListList for normalized data
        virtual const scalarListListList dataNormalization(const scalarListListList& data);

        //- Return a matrix for input signal initialization
        virtual const col2Vector col2VectorInitialization();
        virtual const colVector inputSignalInitialization(const scalarListList& normalizedData);

        //- Return a matrix for error between actual and predicted outputs
        virtual const colVector error(const colVector& ANNOutputSignal, const scalarListList& normalizedData);

        //- Return a matrix for computing weights
        virtual const matrixVector matrixVectorInitialization();
        virtual const matrixVector weightInitialization();
        virtual const matrixVector weight(IOdictionary& statisticalMetricsDict);

        //- Print statistical metrics
        void statisticalMetrics(const scalarListListList& actualData, const scalarListListList& ANNData, IOdictionary& statisticalMetricsDict);

        //- Return a scalarList for MAE
        virtual const scalarList MAE(const scalarListListList& error);

        //- Return a scalarList for MSE
        virtual const scalarList MSE(const scalarListListList& error);

        //- Return a scalarList for RMSD
        virtual const scalarList RMSD(const scalarListListList& error);

        //- Return a scalarList for R2
        virtual const scalarList R2(const scalarListListList& actualData, const scalarListListList& error);

        //- Return a scalarListList for predicted data
        virtual const scalarListList predictedSingleData(const scalarListList& singleData, const matrixVector& weight);

        //- Return a scalarListListList for testing data
        virtual const scalarListListList predictedData(const matrixVector& weight, const scalarListListList& data);

        //- Read architectureDict dictionary
        bool read(const dictionary& architectureDict);
};

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace ANN

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
