//Names: Sresha Ventrapragada, Amy Manning, Amanda Lee
////UT EID: svv346, alm7377, awl646
#include <iostream>
#include <memory>
#include <vector>
#include <cstdlib>
#include <random>
#pragma once
using std::string;
using std::cout;
using std::endl;
using std::vector;
using std::shared_ptr;
using std::make_shared;

// return random int from 0 to max but not including max
int realrandom_int(int max) {
	std::random_device r;
	static std::default_random_engine static_engine{ r() };
	std::uniform_int_distribution<int> ints(0, max - 1);
	return ints(static_engine);
};
