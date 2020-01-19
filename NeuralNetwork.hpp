#ifndef _NEURAL_NETWORK_NEURAL_NETWORK_HPP_
#define _NEURAL_NETWORK_NEURAL_NETWORK_HPP_

#include <vector>

#include "Neuron.hpp"
#include "Synapse.hpp"

namespace NN {

class NeuralNetwork {
private:
  const int inputNeurons, hiddenLayers, hiddenNeuronsPerLayer,
    outputNeurons, synapsesSize;
  Vector input, output;
  Synapse *synapses;
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
      synapsesSize((inputNeurons*hiddenNeuronsPerLayer) +
                   ((hiddenLayers-1) *
                    hiddenNeuronsPerLayer *
                    hiddenNeuronsPerLayer) +
                   (outputNeurons*hiddenNeuronsPerLayer)),
      input(inputNeurons, nullptr),
      output(outputNeurons, nullptr) {
    synapses = new Synapse[synapsesSize];
    createNetwork();
  }

  ~NeuralNetwork();
  void calculate();
  Synapse * getAllSynapses();
  Vector& getInputLayer() { return input; }
  const Vector& getOutputLayer() const { return output; }
  void setWeights(float weights[]);
  int getSynapsesSize();
  std::vector<std::vector<Neuron>> * getHiddenLayer();
};

inline NeuralNetwork::~NeuralNetwork()
{
  delete synapses;
}

inline void NeuralNetwork::calculate()
{
  for (int i = 0; i < synapsesSize; i++)
    {
      synapses[i].getOutput()->
        calculateValue(synapses[i].getWeight(),
                       synapses[i].getInput()->getValue(),
                       synapses[i].getInput()->isLast());
    }
}

inline Synapse *  NeuralNetwork::getAllSynapses()
{
  return synapses;
}

inline void NeuralNetwork::setWeights(float weights[])
{
  for (int i = 0; i < synapsesSize; i++)
    {
      synapses[i].setWeight(weights[i]);
    }
}

inline int NeuralNetwork::getSynapsesSize()
{
  return synapsesSize;
}

inline std::vector<std::vector<Neuron>> * NeuralNetwork::getHiddenLayer()
{
  return &hidden;
}

inline void NeuralNetwork::createNetwork()
{
  int currentSynapse = 0;

  for (int i = 0; i < hiddenNeuronsPerLayer; i++)
    {
      std::vector<Neuron> row;
      for (int j = 0; j < hiddenLayers; j++)
        {
          if (i == hiddenNeuronsPerLayer - 1)
            row.push_back(Neuron(Layer::hidden, true));
          else
            row.push_back(Neuron(Layer::hidden, false));
        }
      hidden.push_back(row);
    }

  for (int i = 0; i < inputNeurons; i++)
    {
      if (i == inputNeurons-1)
        input[i] = new Neuron(Layer::input, true);
      else
        input[i] = new Neuron(Layer::input, false);
      for (int j = 0; j < hiddenNeuronsPerLayer; j++)
        {
          synapses[currentSynapse] = Synapse(input[i], &hidden.at(j).at(0));
          currentSynapse++;
        }
    }

  for (int j = 0; j < hiddenNeuronsPerLayer; j++)
    {
      for (int n = 0; n < hiddenLayers-1; n++)
        {
          for (int b = 0; b < hiddenNeuronsPerLayer; b++)
            {
              synapses[currentSynapse] =
                Synapse(&hidden.at(j).at(n), &hidden.at(b).at(n + 1));
              currentSynapse++;
            }
        }
    }

  for (int i = 0; i < outputNeurons; i++)
    {
      output[i] = new Neuron(Layer::output, false);
      for (int j = 0; j < hiddenNeuronsPerLayer; j++)
        {
          synapses[currentSynapse] =
            Synapse(&hidden.at(j).at(hiddenLayers-1), output[i]);
          currentSynapse++;
        }
    }

}

} // end namespace NN

#endif //_NEURAL_NETWORK_NEURAL_NETWORK_HPP_
