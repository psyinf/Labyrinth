#pragma once
#include <random>

auto rand_between(uint16_t start, uint16_t end) -> uint16_t
{
	std::random_device rd;  //Will be used to obtain a seed for the random number engine
	std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
	std::uniform_int_distribution<> dis(start, end);
	return dis(gen);
}


