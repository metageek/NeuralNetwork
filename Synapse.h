#pragma once
#include "Neuron.h"

class Synapse {
private:
	float weight;
	Neuron *input, *output;
public:
	Synapse(Neuron *input, Neuron *output);
	Synapse();
	void setWeight(float weight);
	float getWeight();
	Neuron * getInput();
	Neuron * getOutput();
};

inline Synapse::Synapse(Neuron *input, Neuron *output)
{
	this->input = input;
	this->output = output;
	this->weight = 0;
}

inline Synapse::Synapse()
{
}
inline void Synapse::setWeight(float weight)
{
	this->weight = weight;
}

inline float Synapse::getWeight()
{
	return this->weight;
}

inline Neuron * Synapse::getInput()
{
	return this->input;
}

inline Neuron * Synapse::getOutput()
{
	return this->output;
}
