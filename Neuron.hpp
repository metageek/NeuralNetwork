#ifndef _NEURAL_NETWORK_NEURON_HPP_
#define _NEURAL_NETWORK_NEURON_HPP_

#include <cmath>
#include <vector>

#include "Layer.hpp"

namespace NN {

class Neuron {
private:
  const Layer layerType;
  float value;
  const bool last;

  float calculate(float weight, float inputValue, bool doSigmoid) {
    return doSigmoid ?
      sigmoid(value + (weight * inputValue)) :
      value + (weight * inputValue);
  }

public:
  Neuron(Layer _layerType, bool _last = false)
    : layerType(_layerType), value(0), last(_last) {
  }
  void calculateValue(float weight, float inputValue, bool doSigmoid) {
    value = calculate(weight, inputValue, doSigmoid);
  }
  static float sigmoid(float value) { return 1 / (1 + exp(-value)); }
  void setValue(float _value) { value = _value; }
  float getValue() const { return value; }
  bool isLast() const { return last; }
};

using Vector = std::vector<Neuron*>;

} // end namespace NN

#endif //_NEURAL_NETWORK_NEURON_HPP_
