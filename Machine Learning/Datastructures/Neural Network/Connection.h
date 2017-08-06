#ifndef CONNECTION_H
#define CONNECTION_H
#include <vector>
#include <cstdlib>


class Connection
{
	private:
		double weight;
		double deltaWeight;
	public:
		Connection() { this->weight = rand() / double(RAND_MAX); }
		Connection(double randomWeight) { this->weight = randomWeight; }

		double getWeight() const { return this->weight; }
		double getDeltaWeight() const { return this->deltaWeight; }
		void setWeight(const double weight) { this->weight = weight; }
		void setDeltaWeight(const double deltaWeight) { this->deltaWeight = deltaWeight; }

};
#endif // !CONNECTION_H