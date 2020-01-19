#ifndef _NEURAL_NETWORK_SYNAPSE_HPP_
#define _NEURAL_NETWORK_SYNAPSE_HPP_

#include "Neuron.hpp"

namespace NN {

class Synapse {
private:
  float weight = 0;
  Neuron* input = nullptr;
  Neuron* output = nullptr;
public:
  Synapse(Neuron *_input, Neuron *_output)
    : input(_input), output(_output) {
  }
  Synapse() {}
  void setWeight(float _weight) { weight = _weight; }
  float getWeight() const { return weight; }
  Neuron * getInput() { return input; }
  Neuron * getOutput() { return output; }
};

} // end namespace NN

#endif //_NEURAL_NETWORK_SYNAPSE_HPP_
