#ifndef _NEURAL_NETWORK_NEURAL_NETWORK_HPP_
#define _NEURAL_NETWORK_NEURAL_NETWORK_HPP_

#include <vector>

#include "Neuron.hpp"
#include "Synapse.hpp"

namespace NN {

class NeuralNetwork {
private:
	int inputNeurons, hiddenLayers, hiddenNeuronsPerLayer, ouputNeurons, synapsesSize;
	Vector input, output;
	Synapse *synapses;
	std::vector<std::vector<Neuron>> hidden;
	void createNetwork();
public:
	NeuralNetwork(int inputNeurons, int hiddenLayers, int hiddenNeuronsPerLayer, int ouputNeurons);
	~NeuralNetwork();
	void calculate();
	Synapse * getAllSynapses();
        Vector& getInputLayer() { return input; }
	const Vector& getOutputLayer() const { return output; }
	void setWeights(float weights[]);
	int getSynapsesSize();
	std::vector<std::vector<Neuron>> * getHiddenLayer();
};

inline NeuralNetwork::NeuralNetwork(int inputNeurons, int hiddenLayers, int hiddenNeuronsPerLayer, int ouputNeurons)
{
	this->inputNeurons = inputNeurons;
	this->hiddenLayers = hiddenLayers;
	this->hiddenNeuronsPerLayer = hiddenNeuronsPerLayer;
	this->ouputNeurons = ouputNeurons;
	this->synapsesSize = (inputNeurons*hiddenNeuronsPerLayer) + ((hiddenLayers-1)*hiddenNeuronsPerLayer*hiddenNeuronsPerLayer) + (ouputNeurons*hiddenNeuronsPerLayer);
	input.resize(inputNeurons, nullptr);
	output.resize(ouputNeurons, nullptr);
	synapses = new Synapse[this->synapsesSize];
	this->createNetwork();
}

inline NeuralNetwork::~NeuralNetwork()
{
	delete synapses;
}

inline void NeuralNetwork::calculate()
{
	for (int i = 0; i < this->synapsesSize; i++)
	{
		synapses[i].getOutput()->calculateValue(synapses[i].getWeight(), synapses[i].getInput()->getValue(), synapses[i].getInput()->isLast());
	}
}

inline Synapse *  NeuralNetwork::getAllSynapses()
{
	return this->synapses;
}

inline void NeuralNetwork::setWeights(float weights[])
{
	for (int i = 0; i < this->synapsesSize; i++)
	{
		synapses[i].setWeight(weights[i]);
	}
}

inline int NeuralNetwork::getSynapsesSize()
{
	return this->synapsesSize;
}

inline std::vector<std::vector<Neuron>> * NeuralNetwork::getHiddenLayer()
{
	return &this->hidden;
}

inline void NeuralNetwork::createNetwork()
{
	int currentSynapse = 0;

	for (int i = 0; i < this->hiddenNeuronsPerLayer; i++)
	{
		std::vector<Neuron> row;
		for (int j = 0; j < this->hiddenLayers; j++)
		{
			if (i == this->hiddenNeuronsPerLayer - 1)
				row.push_back(Neuron(Layer::hidden, true));
			else
				row.push_back(Neuron(Layer::hidden, false));
		}
		hidden.push_back(row);
	}

	for (int i = 0; i < this->inputNeurons; i++)
	{
		if (i == this->inputNeurons-1)
                        input[i] = new Neuron(Layer::input, true);
		else
                        input[i] = new Neuron(Layer::input, false);
		for (int j = 0; j < this->hiddenNeuronsPerLayer; j++)
		{
			synapses[currentSynapse] = Synapse(input[i], &hidden.at(j).at(0));
			currentSynapse++;
		}
	}

	for (int j = 0; j < this->hiddenNeuronsPerLayer; j++)
	{
		for (int n = 0; n < this->hiddenLayers-1; n++)
		{
			for (int b = 0; b < this->hiddenNeuronsPerLayer; b++)
			{
				synapses[currentSynapse] = Synapse(&hidden.at(j).at(n), &hidden.at(b).at(n + 1));
				currentSynapse++;
			}
		}
	}

	for (int i = 0; i < this->ouputNeurons; i++)
	{
                output[i] = new Neuron(Layer::output, false);
		for (int j = 0; j < this->hiddenNeuronsPerLayer; j++)
		{
			synapses[currentSynapse] = Synapse(&hidden.at(j).at(this->hiddenLayers-1), output[i]);
			currentSynapse++;
		}
	}

}

} // end namespace NN

#endif //_NEURAL_NETWORK_NEURAL_NETWORK_HPP_
