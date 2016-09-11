
#include <iostream>
#include <string>
#include <vector>
#include <map>

#include "markov.h"

#include <stdlib.h>     /* srand, rand */
#include <time.h>

using std::vector;
using std::map;

template<typename T, typename A>
void printVec(std::vector<T, A> const& vec, std::string delim)
{
	for (int i = 0; i < (int)vec.size(); i++)
	{
		std::cout << vec[i] << delim;
	}
}

int main()
{
	vector<char> all;
	int score = 0;

	char input = '\0';

	srand(time(NULL));

	vector<Chain> chains;
	int chainmaxorder = 3;
	int threshold = 10;
	/*
	for (unsigned i = 3; i < 6; i++)
	{
		chains.push_back(Chain(i));
	}
	*/
	do
	{
		if (all.size() % threshold == 0)
		{
			chains.push_back(chainmaxorder + 1);
			chainmaxorder++;
			threshold = chainmaxorder * 2;
		}
		int one = 0;
		int zero = 0;
		int pass = 0;
		for (unsigned i = 0; i < chains.size(); i++)
		{
			chains[i].rebuild(all);
			chains[i].predict(all);
			if (chains[i].score >= 0)
			{
				if (chains[i].prediction == '0')
				{
					zero += chains[i].score;
				}
				else if (chains[i].prediction == '1')
				{
					one += chains[i].score;
				}
				else
				{
					pass += chains[i].score;
				}
			}
			else
			{
				if (chains[i].prediction == '0')
				{
					one -= chains[i].score;
				}
				else if (chains[i].prediction == '1')
				{
					zero -= chains[i].score;
				}
				else
				{
					pass -= chains[i].score;
				}
			}
		}
		char prediction;
		if (one > zero && one > pass)
		{
			prediction = '1';
		}
		else if (zero > one && zero > pass)
		{
			prediction = '0';
		}
		else
		{
			prediction = 'P';
		}

		/*
		std::cout << "Input: ";
		std::cin >> input;
		*/
		rand() % 2 == 0 ? input = '0' : input = '1';
		std::cout << "Input: " << input << "\n";
		
		if (!(input == '1' || input == '0'))
		{
			break;
		}

		for (unsigned i = 0; i < chains.size(); i++)
		{
			if (chains[i].prediction != 'P')
			{
				if (chains[i].prediction == input)
				{
					chains[i].score++;
				}
				else
				{
					chains[i].score--;
				}
			}
		}
		
		if (prediction != 'P')
		{
			if (prediction == input)
			{
				score++;
			}
			else
			{
				score--;
			}
		}
		
		std::cout << "Aggregate Prediction: " << prediction << "\n";
		std::cout << "Aggregate Predictor's Score: " << score << " in " << all.size() << " rounds.\n";
		for (unsigned i = 0; i < chains.size(); i++)
		{
			std::cout << "Chain" << chains[i].prefixLen << " Prediction: " << chains[i].prediction << " Score: " << chains[i].score << "\n";
		}
		std::cout << "\n\n";

		all.push_back(input);

		/*
		printVec(all, " ");
		std::cout << "\n\n";
		*/
		
	} while (input == '1' || input == '0');

	return 0;
}
