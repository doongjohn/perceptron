#pragma once

#include <array>

#include "perceptron.hpp"

static auto perceptron_train_and_gate(float learning_rate) -> Perceptron {
  Perceptron p(2);
  p.learning_rate = learning_rate;

  while (true) {
    int a = random_int(0, 1);
    int b = random_int(0, 1);
    p.train({float(a), float(b)}, a && b);

    // check training result
    if (
      p.predict({0, 0}) == 0 &&
      p.predict({1, 0}) == 0 &&
      p.predict({0, 1}) == 0 &&
      p.predict({1, 1}) == 1
    ) {
      break;
    }
  }

  return p;
}

static auto perceptron_train_or_gate(float learning_rate) -> Perceptron {
  Perceptron p(2);
  p.learning_rate = learning_rate;

  while (true) {
    int a = random_int(0, 1);
    int b = random_int(0, 1);
    p.train({float(a), float(b)}, a || b);

    // check training result
    if (
      p.predict({0, 0}) == 0 &&
      p.predict({1, 0}) == 1 &&
      p.predict({0, 1}) == 1 &&
      p.predict({1, 1}) == 1
    ) {
      break;
    }
  }

  return p;
}

static auto perceptron_train_not_gate(float learning_rate) -> Perceptron {
  Perceptron p(1);
  p.learning_rate = learning_rate;

  while (true) {
    int a = random_int(0, 1);
    p.train({float(a)}, !a);

    // check training result
    if (
      p.predict({0}) == 1 &&
      p.predict({1}) == 0
    ) {
      break;
    }
  }

  return p;
}
