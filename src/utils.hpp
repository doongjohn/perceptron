#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <random>

auto random_int(int min, int max) -> int {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> distr(min, max);
  return distr(gen);
}

auto random_float(float min, float max) -> float {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_real_distribution<float> distr(min, max);
  return distr(gen);
}

auto read_file(const std::string path) -> std::string {
  std::string result = "";

  std::fstream fs;
	fs.open(path, std::ios::in);

	if (!fs) {
    std::cout << "file not found!\n";
	} else {
    std::stringstream ss;
    ss << fs.rdbuf();
    result = ss.str();
	}

  fs.close();

  return result;
}
