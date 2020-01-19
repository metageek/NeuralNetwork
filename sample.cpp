#include <stdio.h>

#include "NeuralNetwork.hpp"

using namespace NN;

int main(int argc, const char* argv[]) {
  int inputNeurons = 2;
  int hiddenLayers = 1;
  int hiddenNeuronsPerLayer = 3;
  int ouputNeurons = 1;

  NeuralNetwork nn = NeuralNetwork(inputNeurons,
                                   hiddenLayers, hiddenNeuronsPerLayer,
                                   ouputNeurons);
  Vector& input = nn.getInputLayer();
  const Vector& output = nn.getOutputLayer();

  //array with size equals to your input neurons number (inputNeurons)
  input[0]->setValue(1);
  input[1]->setValue(1);

  float weights[] = {0.8, 0.4, 0.3, 0.2, 0.9, 0.5, 0.3, 0.5, 0.9};
  nn.setWeights(weights);
  nn.calculate();

  //array with size equals to your output neurons number (ouputNeurons)
  printf("Result = %f\n", output[0]->getValue());
}
