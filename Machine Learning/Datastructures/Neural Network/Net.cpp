#include "Net.h"

Net::Net(const std::vector<unsigned>& topology)
{
	unsigned numberOfLayers = topology.size();
	unsigned numberOfOutputs;
	for (unsigned layerNumber = 0; layerNumber < numberOfLayers; layerNumber++)
	{
		this->layers.push_back(Layer()); // Construct new layers

		numberOfOutputs = layerNumber == topology.size() - 1 ? 0 : topology[layerNumber + 1];

		// Add neurons to the layer
		for (unsigned neuronNumber = 0; neuronNumber <= topology[layerNumber]; neuronNumber++) // <= instead of < to add a biased neuron
		{
			this->layers.back().push_back(Neuron(numberOfOutputs, neuronNumber));
		}

		// Force the biased neurons output value to 1.0 (last neuron created above)
		this->layers.back().back().setOutputValue(1.0);

	}
}

void Net::feedForward(const std::vector<double>& inputValues)
{
	assert(inputValues.size() == (layers[0].size() - 1));

	// Assign the input values to the input neurons
	for (unsigned i = 0; i < inputValues.size(); i++)
	{
		layers[0][i].setOutputValue(inputValues[i]);
	}

	//Forward propagate
	for (unsigned layerNumber = 1; layerNumber < layers.size(); layerNumber++)
	{
		Layer& previousLayer = layers[layerNumber - 1];
		for (unsigned neuron = 0; neuron < layers[layerNumber].size() - 1; neuron++)
		{
			layers[layerNumber][neuron].feedForward(previousLayer);
		}
	}
}

void Net::backProp(const std::vector<double>& targetValues)
{
	//Calculate overall net error (RMS (Root Mean Square Error) of output neuron errors)
	Layer& outputLayer = this->layers.back();
	double delta = 0.0;
	this->error = 0.0;
	for (unsigned neuron = 0; neuron < outputLayer.size() - 1; neuron++)
	{
		delta = targetValues[neuron] - outputLayer[neuron].getOutputValue();
		this->error += (delta * delta);
	}
	
	this->error /= (outputLayer.size() - 1);
	this->error = sqrt(this->error); // RMS Value

	// Print out an error indication of how well the net has been doing
	this->recentAverageError = ((this->recentAverageError * this->recentAverageSmoothingFactor + error) / (this->recentAverageSmoothingFactor + 1.0));


	//Calculate output layer gradients
	for (unsigned neuron = 0; neuron < outputLayer.size() - 1; neuron++)
	{
		outputLayer[neuron].calculateOutputGradients(targetValues[neuron]);
	}


	//Calculate gradients on hidden layers
	for (unsigned layerNumber = this->layers.size() - 2; layerNumber > 0; layerNumber--)
	{
		Layer& hiddenLayer = this->layers[layerNumber];
		Layer& nextLayer = this->layers[layerNumber + 1];

		for (unsigned neuron = 0; neuron < hiddenLayer.size() - 1; neuron++)
		{
			hiddenLayer[neuron].calculateHiddenGradients(nextLayer);
		}

	}

	//For all layers from output to first hidden layer
	//Update connection weights
	for (unsigned layerNumber = this->layers.size() - 1; layerNumber > 0; layerNumber--)
	{
		Layer& currLayer = this->layers[layerNumber];
		Layer& prevLayer = this->layers[layerNumber - 1];

		for (unsigned neuron = 0; neuron < currLayer.size() - 1; neuron++)
		{
			currLayer[neuron].updateInputWeights(prevLayer);
		}
	}
}

void Net::getResults(std::vector<double>& resultValues) const
{
	resultValues.clear();

	for (unsigned neuron = 0; neuron < this->layers.back().size() - 1; neuron++)
	{
		resultValues.push_back(this->layers.back()[neuron].getOutputValue());
	}
}


