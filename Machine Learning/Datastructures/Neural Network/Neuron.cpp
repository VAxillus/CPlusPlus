#include "Neuron.h"

double Neuron::eta = 0.15; // overall net learning rate
double  Neuron::alpha = 0.5; // momentum, multiplier of the last deltaWeight

double Neuron::transferFunction(double value)
{
	//Could use a different curve
	//Using a hyperbolic tan function -> output in the range [-1,0..1,0]
	return tanh(value);
}

double Neuron::transferFunctionDerivative(double value)
{
	//Tanh derivative quick approximation
	return 1.0 - (value * value);
}

double Neuron::sumDOW(const Layer & nextLayer)
{
	double sum = 0.0;

	//Sum the error of the nodes
	for (unsigned neuron = 0; neuron < nextLayer.size() - 1; neuron++)
	{
		sum += (this->outputWeights[neuron].getWeight() * nextLayer[neuron].getGradient());
	}
	return sum;
}

void Neuron::updateInputWeights(Layer & previousLayer)
{
	// The weights to be updated are in the Connection container
	// in the neurons in the preceding layer
	for (unsigned neuron = 0; neuron < previousLayer.size(); neuron++)
	{
		Neuron& currNeuron = previousLayer[neuron];
		double oldDeltaWeight = currNeuron.outputWeights[this->index].getDeltaWeight();

		
		double newDeltaWeight =
			// Individual input, multiplied by the gradient and train rate
			eta * currNeuron.getOutputValue() * this->gradient

			// Add momentum = a fraction of the previous delta weight
			+ alpha * oldDeltaWeight;

		currNeuron.outputWeights[this->index].setDeltaWeight(newDeltaWeight);
		currNeuron.outputWeights[this->index].setWeight(currNeuron.outputWeights[this->index].getWeight() + newDeltaWeight);

	}
}

Neuron::Neuron(unsigned numberOfOutputs, unsigned index)
{
	this->index = index;

	for (unsigned connections = 0; connections < numberOfOutputs; connections++)
	{
		this->outputWeights.push_back(Connection());
		this->outputWeights.back().setWeight(randomWeight());
		
	}
}

void Neuron::feedForward(const Layer& previousLayer)
{
	double sum = 0.0;

	//Sum the previous layer's outputs (which are the inputs)
	//Include the bias node from the previous layer
	for (unsigned neuron = 0; neuron < previousLayer.size() - 1; neuron++)
	{
		sum += previousLayer[neuron].getOutputValue() * previousLayer[neuron].outputWeights[index].getWeight();
	}
	this->outputValue = this->transferFunction(sum);
}

void Neuron::calculateOutputGradients(double targetValue)
{
	double delta = (targetValue - this->outputValue);
	gradient = (delta * this->transferFunctionDerivative(this->outputValue));
}

void Neuron::calculateHiddenGradients(const Layer & nextLayer)
{
	double dow = sumDOW(nextLayer);
	this->gradient = (dow * this->transferFunctionDerivative(this->outputValue));
}
