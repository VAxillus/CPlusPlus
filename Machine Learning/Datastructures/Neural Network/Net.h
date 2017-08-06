#ifndef NET_H
#define NET_H
#include "Neuron.h"
#include <vector>
#include <assert.h>



typedef std::vector<Neuron> Layer;

class Net
{
	private:
		std::vector<Layer> layers; // layers[layerNumber][neuronNumber]
		double error;
		double recentAverageError;
		double recentAverageSmoothingFactor;
	public:
		Net(const std::vector<unsigned> &topology);

		void feedForward(const std::vector<double>& inputValues); // Feed data
		void backProp(const std::vector<double>& targetValues); // What the output should be
		void getResults(std::vector<double>& resultValues) const; 

		double getRecentAverageError() const { return this->recentAverageError; }
};
#endif // !NET_H