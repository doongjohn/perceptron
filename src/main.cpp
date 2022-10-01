// https://www.quora.com/Why-can-t-Perceptron-learn-XOR
// https://towardsdatascience.com/perceptrons-logical-functions-and-the-xor-problem-37ca5025790a
// https://stats.stackexchange.com/questions/410952/why-perceptron-is-linear-classifier
// https://stats.stackexchange.com/questions/263768/can-a-perceptron-with-sigmoid-activation-function-perform-nonlinear-classificati
// 10.4: Neural Networks: Multilayer Perceptron Part 1 - The Nature of Code
//   https://youtu.be/u5GAVdLQyIg

#include "perceptron.hpp"
#include "training.hpp"

auto main() -> int {
  Perceptron p_and = perceptron_train_and_gate(0.1f);
  Perceptron p_or = perceptron_train_or_gate(0.1f);
  Perceptron p_not = perceptron_train_not_gate(0.1f);

  const auto xor_func = [&](int a, int b) -> int {
    // xor(a, b) = and(not(and(a, b)), or(a, b))
    return p_and(p_not(p_and(a, b)), p_or(a, b));
  };

  int a = 0;
  int b = 0;
  std::cin >> a;
  std::cin >> b;
  std::cout << xor_func(a, b) << '\n';

  return 0;
}
