
#pragma once

#include <vector>
#include <map>
#include <string>
#include <sstream>
#include <random>
#include <algorithm>


class Prefix
{
public:
	std::vector<char> p;
	unsigned prefixLen;

	Prefix();
	Prefix(unsigned _prefixLen);

	void shift(char c);
};

class Counter
{
public:
	int zeroes;
	int ones;
};

class Chain
{
public:
	//Particular vector of chars to a counter
	std::map<std::vector<char>, Counter> chain;
	unsigned prefixLen;

	char prediction;
	int score;

	Chain(unsigned _prefixLen);

	void rebuild(std::vector<char> const &input);
	void predict(std::vector<char> const &input);
};
