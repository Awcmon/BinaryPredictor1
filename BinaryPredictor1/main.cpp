
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
	do
	{

		Chain chain4(12);
		chain4.rebuild(all);
		chain4.predict(all);
		char prediction = chain4.prediction;

		std::cout << "Input: ";
		std::cin >> input;
		

		//rand() % 2 == 0 ? input = '0' : input = '1';

		if (!(input == '1' || input == '0'))
		{
			break;
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

		std::cout << "Prediction: " << prediction << "\n";
		std::cout << "Predictor's Score: " << score << " in " << all.size() << " rounds.\n";
		std::cout << "\n\n";

		all.push_back(input);

		/*
		printVec(all, " ");
		std::cout << "\n\n";
		*/
		
	} while (input == '1' || input == '0');

	return 0;
}
