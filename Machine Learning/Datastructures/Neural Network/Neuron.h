#ifndef NEURON_H
#define NEURON_H
#include <vector>
#include "Connection.h"



class Neuron
{
	typedef std::vector<Neuron> Layer;
	private:
		double outputValue;
		double gradient;
		unsigned index;
		std::vector<Connection> outputWeights;

		static double eta;  //[0,0..1.0] overall net training rate
		static double alpha; //[0,0..n] multiplier of the last deltaWeight (momentum)
		static double randomWeight() { return (rand() / double(RAND_MAX)); }
		static double transferFunction(double value);
		static double transferFunctionDerivative(double value);
		double sumDOW(const Layer& nextLayer);
		

	public:
		Neuron(unsigned numberOfOutputs, unsigned index);

		void setOutputValue(double value) { this->outputValue = value; }
		double getOutputValue() const { return this->outputValue; }
		double getGradient() const { return this->gradient; }
		void feedForward(const Layer& previousLayer);
		void calculateOutputGradients(double targetValue);
		void calculateHiddenGradients(const Layer& nextLayer);
		void updateInputWeights(Layer& previousLayer);
	

};


#endif // !NEURON_H