#ifndef _NEURAL_NETWORK_NEURON_HPP_
#define _NEURAL_NETWORK_NEURON_HPP_

#include <cmath>
#include <vector>

#include "Layer.hpp"

namespace NN {

class Neuron {
private:
	Layer layerType;
	float value;
	bool last;
public:
	Neuron();
	Neuron(Layer layerType, bool last);
	Neuron(Layer layerType, int id, bool last);
	int id;
	void calculateValue(float weight, float inputValue, bool doSigmoid);
	float sigmoid(float value);
	void setValue(float value);
	float getValue();
	bool isLast();
};

using Vector = std::vector<Neuron*>;

inline Neuron::Neuron()
{
	this->value = 0;
	this->last = false;
}

inline Neuron::Neuron(Layer layerType, bool last)
{
	this->layerType = layerType;
	this->value = 0;
	this->last = last;
}

inline Neuron::Neuron(Layer layerType, int id, bool last)
{
	this->layerType = layerType;
	this->id = id;
	this->value = 0;
	this->last = last;
}

inline void Neuron::calculateValue(float weight, float inputValue, bool doSigmoid)
{
	if(doSigmoid)
		this->value = this->sigmoid(this->value + (weight * inputValue));
	else
		this->value = this->value + (weight * inputValue);
}

inline float Neuron::sigmoid(float value)
{
	return 1 / (1 + exp(-value));
}

inline void Neuron::setValue(float value)
{
	this->value = value;
}

inline float Neuron::getValue()
{
	return this->value;
}

inline bool Neuron::isLast()
{
	return this->last;
}

} // end namespace NN

#endif //_NEURAL_NETWORK_NEURON_HPP_
