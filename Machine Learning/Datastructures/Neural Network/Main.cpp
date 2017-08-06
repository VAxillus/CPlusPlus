#include "Net.h"
#include <iostream>
#include <ctime>
#include "TrainingData.h" //Dummy temporary class


//https://vimeo.com/19569529 created with the help of this tutorial


void showVectorValues(std::vector<double>& values);

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	TrainingData trainData("Trainingdata.txt");
	srand(time(NULL));
	std::vector<unsigned> topology;
	std::vector<double> inputValues;
	std::vector<double> targetValues;
	std::vector<double> resultValues;

	trainData.getTopology(topology);
	Net neuralNet(topology);
	int trainingpass = 0;

	while (!trainData.isEof())
	{
		trainingpass++;
		std::cout << std::endl << "Pass: " << trainingpass;

		// Get new input data and feed it forward
		if (trainData.getNextInputs(inputValues) != topology[0])
		{
			break;
		}
		std::cout << "\tInputs: ";
		showVectorValues(inputValues);
		neuralNet.feedForward(inputValues);

		//Collect the net's actual results
		neuralNet.getResults(resultValues);
		std::cout << "Outputs: " ;
		showVectorValues(resultValues);

		// Train the net what the outputs should have been 
		trainData.getTargetOutputs(targetValues);
		std::cout << "Targets: ";
		showVectorValues(resultValues);
		assert(targetValues.size() == topology.back());
		neuralNet.backProp(targetValues);

		//Report how well the training is working
		std::cout << "Net recent average error: " << neuralNet.getRecentAverageError() << std::endl;


	}
	
	std::cout << std::endl << "Done!" << std::endl;
	system("pause");



	return 0;
}

void showVectorValues(std::vector<double>& values)
{
	for (unsigned i = 0; i < values.size(); i++)
	{
		std::cout << values[i] << " ";
	}
	std::cout << std::endl;
}
