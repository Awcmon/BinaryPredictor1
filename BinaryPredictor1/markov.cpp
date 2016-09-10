
#include "markov.h"

using std::vector;
using std::string;
using std::map;

Prefix::Prefix()
{
	prefixLen = 1;
}

Prefix::Prefix(unsigned _prefixLen)
{
	prefixLen = _prefixLen;
}

void Prefix::shift(char c)
{
	if (p.size() >= prefixLen)
	{
		p.erase(p.begin());
	}
	p.push_back(c);
}

Chain::Chain(unsigned _prefixLen)
{
	prefixLen = _prefixLen;
}

void Chain::rebuild(vector<char> const &input)
{
	chain.clear();
	Prefix p(prefixLen);
	for (int i = 0; i < (int)input.size(); i++)
	{
		char c = input[i];
		vector<char> key = p.p;
		if (c == '0')
		{
			chain[key].zeroes++;
		}
		else if(c == '1')
		{
			chain[key].ones++;
		}
		p.shift(c);
	}
}

void Chain::predict(vector<char> const &input)
{
	if (input.size() <= prefixLen * 2)
	{
		prediction = 'P';
	}
	else
	{
		vector<char>::const_iterator first = input.end() - prefixLen;
		vector<char>::const_iterator last = input.end();
		vector<char> key(first, last);
		if (chain.count(key) > 0)
		{
			Counter counter = chain[key];
			if (counter.ones > counter.zeroes)
			{
				prediction = '1';
			}
			else if (counter.ones < counter.zeroes)
			{
				prediction = '0';
			}
			else
			{
				prediction = 'P';
			}
		}
		else
		{
			prediction = 'P';
		}
	}
}
