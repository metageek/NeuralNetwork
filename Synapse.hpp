#ifndef _NEURAL_NETWORK_SYNAPSE_HPP_
#define _NEURAL_NETWORK_SYNAPSE_HPP_

#include "Neuron.hpp"

namespace NN {

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

inline Synapse::Synapse(Neuron *_input, Neuron *_output)
  : weight(0), input(_input), output(_output)
{
}

inline Synapse::Synapse()
{
}

inline void Synapse::setWeight(float _weight)
{
	weight = _weight;
}

inline float Synapse::getWeight()
{
	return weight;
}

inline Neuron * Synapse::getInput()
{
	return input;
}

inline Neuron * Synapse::getOutput()
{
	return output;
}

} // end namespace NN

#endif //_NEURAL_NETWORK_SYNAPSE_HPP_
