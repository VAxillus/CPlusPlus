#include "TrainingData.h"

TrainingData::TrainingData(const std::string fileName)
{
	this->read.open(fileName.c_str());
}

TrainingData::~TrainingData()
{
	this->read.close();
}

void TrainingData::getTopology(std::vector<unsigned>& topology)
{
	std::string line;
	std::string label;

	std::getline(this->read, line);
	
	std::stringstream ss(line);
	ss >> label;

	if (this->isEof() || label.compare("topology:") != 0)
	{
		abort();
	}

	unsigned n = 0;
	while (!ss.eof())
	{
		ss >> n;
		topology.push_back(n);
	}

}

unsigned TrainingData::getNextInputs(std::vector<double>& inputValues)
{
	std::string line;
	std::string label;
	inputValues.clear();
	
	std::getline(this->read, line);
	std::stringstream ss(line);
	ss >> label;

	double value = 0.0;
	if (label.compare("in:") == 0)
	{
		while (ss >> value)
		{
			inputValues.push_back(value);
		}
	}

	return inputValues.size();
}

unsigned TrainingData::getTargetOutputs(std::vector<double>& targetOutputValues)
{
	std::string line;
	std::string label;
	targetOutputValues.clear();

	std::getline(this->read, line);
	std::stringstream ss(line);
	ss >> label;
	
	double value = 0.0;
	if (label.compare("out:") == 0)
	{
		while (ss >> value)
		{
			targetOutputValues.push_back(value);
		}
	}
	return targetOutputValues.size();
}
