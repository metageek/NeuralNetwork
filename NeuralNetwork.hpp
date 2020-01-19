#ifndef _NEURAL_NETWORK_NEURAL_NETWORK_HPP_
#define _NEURAL_NETWORK_NEURAL_NETWORK_HPP_

#include <vector>

#include "Neuron.hpp"
#include "Synapse.hpp"

namespace NN {

class NeuralNetwork {
private:
  const int inputNeurons, hiddenLayers, hiddenNeuronsPerLayer, outputNeurons;
  Vector input, output;
  std::vector<Synapse*> synapses;
  std::vector<std::vector<Neuron>> hidden;

  void createNetwork();
  
public:
  NeuralNetwork(int _inputNeurons,
                int _hiddenLayers, int _hiddenNeuronsPerLayer,
                int _outputNeurons)
    : inputNeurons(_inputNeurons),
      hiddenLayers(_hiddenLayers),
      hiddenNeuronsPerLayer(_hiddenNeuronsPerLayer),
      outputNeurons(_outputNeurons),
      input(inputNeurons, nullptr),
      output(outputNeurons, nullptr),
      synapses((inputNeurons*hiddenNeuronsPerLayer) +
               ((hiddenLayers-1) *
                hiddenNeuronsPerLayer *
                hiddenNeuronsPerLayer) +
               (outputNeurons*hiddenNeuronsPerLayer),
               nullptr) {
    createNetwork();
  }

  void calculate();
  const std::vector<Synapse*>& getAllSynapses() { return synapses; }
  Vector& getInputLayer() { return input; }
  const Vector& getOutputLayer() const { return output; }
  void setWeights(const std::vector<float>& weights);
  int getSynapsesSize() { return synapses.size(); }
  std::vector<std::vector<Neuron>> * getHiddenLayer() { return &hidden; }
};

inline void NeuralNetwork::calculate()
{
  for (int i = 0; i < synapses.size(); i++) {
    synapses[i]->getOutput()->
      calculateValue(synapses[i]->getWeight(),
                     synapses[i]->getInput()->getValue(),
                     synapses[i]->getInput()->isLast());
  }
}

inline void NeuralNetwork::setWeights(const std::vector<float>& weights) {
  if (weights.size() == synapses.size()) {
    for (int i = 0; i < synapses.size(); i++) {
      synapses[i]->setWeight(weights[i]);
    }
  }
}

inline void NeuralNetwork::createNetwork()
{
  int currentSynapse = 0;

  for (int i = 0; i < hiddenNeuronsPerLayer; i++) {
    std::vector<Neuron> row;
    for (int j = 0; j < hiddenLayers; j++) {
      row.push_back(Neuron(Layer::hidden,
                           (i == hiddenNeuronsPerLayer - 1)));
    }
    hidden.push_back(row);
  }

  for (int i = 0; i < inputNeurons; i++) {
    input[i] = new Neuron(Layer::input, (i == inputNeurons-1));
    for (int j = 0; j < hiddenNeuronsPerLayer; j++) {
      synapses[currentSynapse] = new Synapse(input[i], &hidden.at(j).at(0));
      currentSynapse++;
    }
  }

  for (int j = 0; j < hiddenNeuronsPerLayer; j++) {
    for (int n = 0; n < hiddenLayers-1; n++) {
      for (int b = 0; b < hiddenNeuronsPerLayer; b++) {
        synapses[currentSynapse] =
          new Synapse(&hidden.at(j).at(n), &hidden.at(b).at(n + 1));
        currentSynapse++;
      }
    }
  }

  for (int i = 0; i < outputNeurons; i++) {
    output[i] = new Neuron(Layer::output, false);
    for (int j = 0; j < hiddenNeuronsPerLayer; j++) {
      synapses[currentSynapse] =
        new Synapse(&hidden.at(j).at(hiddenLayers-1), output[i]);
      currentSynapse++;
    }
  }
}

} // end namespace NN

#endif //_NEURAL_NETWORK_NEURAL_NETWORK_HPP_
