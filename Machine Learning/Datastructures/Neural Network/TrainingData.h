#ifndef TRAININGDATA_H
#define TRAININGDATA_H
#include <fstream>
#include <sstream>
#include <vector>

class TrainingData
{
	private:
		std::ifstream read;

	public:
		TrainingData(const std::string fileName);
		~TrainingData();

		bool isEof() { return this->read.eof(); }
		void getTopology(std::vector<unsigned>& topology);

		// Return the number of input values read from file
		unsigned getNextInputs(std::vector<double>& inputValues);
		unsigned getTargetOutputs(std::vector<double>& targetOutputValues);



};
#endif // !TRAININGDATA_H