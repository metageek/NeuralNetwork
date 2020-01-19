#pragma once
#include "Neuron.h"
#include "Synapse.h"
#include <vector>

class NeuralNetwork {
private:
	int inputNeurons, hiddenLayers, hiddenNeuronsPerLayer, ouputNeurons, synapsesSize;
	Neuron *input, *output;
	Synapse *synapses;
	std::vector<std::vector<Neuron>> hidden;
	void createNetwork();
public:
	NeuralNetwork(int inputNeurons, int hiddenLayers, int hiddenNeuronsPerLayer, int ouputNeurons);
	~NeuralNetwork();
	void calculate();
	Synapse * getAllSynapses();
	Neuron * getInputLayer();
	Neuron * getOutputLayer();
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
	input = new Neuron[inputNeurons];
	output = new Neuron[ouputNeurons];
	synapses = new Synapse[this->synapsesSize];
	this->createNetwork();
}

inline NeuralNetwork::~NeuralNetwork()
{
	delete synapses;
	delete input;
	delete output;
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

inline Neuron * NeuralNetwork::getInputLayer()
{
	return this->input;
}

inline Neuron * NeuralNetwork::getOutputLayer()
{
	return this->output;
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
	int id = 0;

	for (int i = 0; i < this->hiddenNeuronsPerLayer; i++)
	{
		std::vector<Neuron> row;
		for (int j = 0; j < this->hiddenLayers; j++)
		{
			if (i == this->hiddenNeuronsPerLayer - 1)
				row.push_back(Neuron(Layer::hidden, id, true));
			else
				row.push_back(Neuron(Layer::hidden, id, false));
			id++;
		}
		hidden.push_back(row);
	}

	for (int i = 0; i < this->inputNeurons; i++)
	{
		if(i == this->inputNeurons-1)
			input[i] = Neuron(Layer::input, true);
		else
			input[i] = Neuron(Layer::input, false);
		input[i].id = id;
		id++;
		for (int j = 0; j < this->hiddenNeuronsPerLayer; j++)
		{
			synapses[currentSynapse] = Synapse(&input[i], &hidden.at(j).at(0));
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
		output[i] = Neuron(Layer::output, false);
		output[i].id = id;
		id++;
		for (int j = 0; j < this->hiddenNeuronsPerLayer; j++)
		{
			synapses[currentSynapse] = Synapse(&hidden.at(j).at(this->hiddenLayers-1), &output[i]);
			currentSynapse++;
		}
	}

}
