# NeuralNetwork
NeuralNetwork is a simple and powerful library that can be easily called in your c++ project to create neural networks of any size.

## Training

In development: Genetic Algorithm

## Installation

There are no dependencies. Just add all the headers to your project and don't forget to #include "NeuralNetwork.h".

## Using

Using the library is easy.

```c
Neuron *input, *output;
int inputNeurons = 2;
int hiddenLayers = 1;
int hiddenNeuronsPerLayer = 3;
int ouputNeurons = 1;

NeuralNetwok nn = NeuralNetwok(inputNeurons, hiddenLayers, hiddenNeuronsPerLayer, ouputNeurons);

//array with size equals to your input neurons number (inputNeurons)
input[0].setValue(1);
input[1].setValue(1);

float weights[] = {0.8, 0.4, 0.3, 0.2, 0.9, 0.5, 0.3, 0.5, 0.9};
nn.setWeights(weights);
nn.calculate();

//array with size equals to your output neurons number (ouputNeurons)
printf("Result = %f\n", output[0].getValue());

//output
//Result = 0.774380
```
