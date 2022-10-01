#pragma once

#include <vector>

#include "utils.hpp"

// forward declaration
struct Perceptron;
static auto train(Perceptron &p, std::vector<float> inputs, int target) -> void;
static auto predict(Perceptron p, std::vector<float> inputs) -> int;
static auto step(float sum) -> int;

struct Perceptron {
  std::vector<float> weights;
  float bias;
  float learning_rate = 0.1f;

  Perceptron(int input_size) {
    // initialize the weights and bias randomly
    new (&weights) std::vector<float>(input_size);
    for (auto &w : weights) {
      w = random_float(-0.5f, 0.5f);
    }
    bias = random_float(-0.5f, 0.5f);
  }

  template<typename... T>
  auto operator()(T... inputs) -> int {
    auto args = std::initializer_list{inputs...};
    std::vector<float> inputs_f;
    std::copy(args.begin(), args.end(), back_inserter(inputs_f));
    return predict(*this, inputs_f);
  }
};

// supervised learning
static auto train(Perceptron &p, std::vector<float> inputs, int target) -> void {
  int error = target - predict(p, inputs);

  if (error != 0) {
    // tune weights and bias
    for (int i = 0; i < inputs.size(); ++i) {
      p.weights[i] += error * inputs[i] * p.learning_rate;
    }
    p.bias += error * p.learning_rate;
  }
}

static auto predict(Perceptron p, std::vector<float> inputs) -> int {
  float dot_product = 0;

  // get a dot product between inputs and weights
  for (int i = 0; i < p.weights.size(); ++i) {
    dot_product += inputs[i] * p.weights[i];
  }
  dot_product += p.bias;

  // pass the result to the activation function (feed forward)
  return step(dot_product);
}

// activation function determines the output of this preceptron
static auto step(float sum) -> int {
  // https://en.wikipedia.org/wiki/Heaviside_step_function
  int output = sum > 0 ? 1 : 0; // -> 0 or 1
  return output;
}
