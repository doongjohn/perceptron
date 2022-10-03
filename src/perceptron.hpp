#pragma once

#include <vector>

#include "utils.hpp"

// forward declaration
static auto step(float sum) -> int;

struct Perceptron {
  std::vector<float> weights;
  float bias;
  float learning_rate;

  Perceptron(int input_size);

  auto train(std::vector<float> inputs, int target) -> void;
  auto predict(std::vector<float> inputs) -> int;

  template<typename... T>
  auto operator()(T... inputs) -> int;
};

inline Perceptron::Perceptron(int input_size) {
  // initialize the weights and bias randomly
  new (&weights) std::vector<float>(input_size);
  for (auto &w : weights) {
    w = random_float(-0.5f, 0.5f);
  }
  bias = random_float(-0.5f, 0.5f);
}

inline auto Perceptron::train(std::vector<float> inputs, int target) -> void {
  // supervised learning
  int error = target - predict(inputs);
  if (error != 0) {
    // tune weights and bias
    for (int i = 0; i < inputs.size(); ++i) {
      weights[i] += error * inputs[i] * learning_rate;
    }
    bias += error * learning_rate;
  }
}

inline auto Perceptron::predict(std::vector<float> inputs) -> int {
  // get a dot product between inputs and weights
  float dot_product = 0;
  for (int i = 0; i < weights.size(); ++i) {
    dot_product += inputs[i] * weights[i];
  }
  dot_product += bias;

  // pass the result to the activation function (feed forward)
  // activation function determines the output of this preceptron
  return step(dot_product);
}

// conveniant way of calling predict method
template<typename... T>
auto Perceptron::operator()(T... inputs) -> int {
  auto args = std::initializer_list{inputs...};
  std::vector<float> inputs_f;
  std::copy(args.begin(), args.end(), back_inserter(inputs_f));
  return predict(inputs_f);
}

static auto step(float sum) -> int {
  // https://en.wikipedia.org/wiki/Heaviside_step_function
  int output = sum > 0 ? 1 : 0; // -> 0 or 1
  return output;
}
