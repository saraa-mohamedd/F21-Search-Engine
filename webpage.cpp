#include "webpage.h"


unordered_map<string, int> webpage::keys = unordered_map<string, int>();
int* webpage::pointingto = new int;
int webpage::count = 0;
webpage* webpage::sortedpgs = new webpage;

webpage::webpage()
{
	name = "";
	impressions = 0;
	clicks = 0;
	CTR = 0.0;
	pr = 0.0;
}

webpage::webpage(string n, vector<string> k)
{
	name = n;
	for (int i = 0; i < k.size(); i++)
	{
		keywords.push_back(k[i]);
	}

	impressions = 0;
	clicks = 0;
	CTR = 0.0;
	pr = 0.0;
}

void webpage::setname(string n)
{
	name = n;
}

void webpage::setscore(double s)
{
	score = s;
}

string webpage::getname()
{
	return name;
}

int webpage::getclicks()
{
	return clicks;
}

int webpage::getimpressions()
{
	return impressions;
}

double webpage::getscore()
{
	return score;
}

void webpage::setkeywords(vector<string> kw)
{
	for (int i = 0; i < kw.size(); i++)
	{
		keywords.push_back(kw[i]);
	}
}

void webpage::setimpressions(int n)
{
	impressions = n;
}

void webpage::setclicks(int n)
{
	clicks = n;
}

void webpage::setpagerank(double pr)
{
	this->pr = pr;
}

void webpage::incrementclicks()
{
	clicks++;
	updateCTR();
}

void webpage::incrementimpressions()
{
	impressions++;
	updateCTR();
}

void webpage::updateCTR()
{
	CTR = (clicks / impressions);
	updatescore();
}

void webpage::updatescore()
{
	double temp1, temp2;
	temp1 = (1 - ((0.1 * impressions) / (1 + 0.1 * impressions)));
	temp1 *= pr;

	temp2 = ((0.1 * impressions) / (1 + 0.1 * impressions));
	temp2 *= CTR;

	score = (0.4 * pr) + ((temp1 + temp2) * 0.6);
}

bool webpage::keywordfound(string kw)
{
	bool found = false;

	for (int i = 0; i < keywords.size(); i++)
	{
		if (keywords[i] == kw)
			found = true;
	}

	return found;
}

void webpage::printpage()
{
	cout << name << "  ";

	for (int i = 0; i < keywords.size(); i++)
	{
		cout << keywords[i] << "  ";
	}

	cout << impressions << "  " << clicks << "  " << pr;

	cout << endl;
}

void webpage::pagerank(vector<webpage> &wp, int** links)
{
	cout.precision(5);
	cout.setf(ios::fixed);
	cout.setf(ios::showpoint);

	double d = 0.85;
	double N = (double)count;
	double* previousrank;
	double* newrank;

	previousrank = new double[count];
	newrank = new double[count];

	for (int i = 0; i < count; i++)
	{
		newrank[i] = (1.0 / count);
		previousrank[i] = 0.0;
	}

	for (int k = 0; k < 100; k++)
	{
		for (int i = 0; i < count; i++)
			previousrank[i] = newrank[i];

		for (int i = 0; i < count; i++)
			newrank[i] = 0.0;

		double rank;
		for (int i = 0; i < count; i++)
		{
			rank = 0;
			for (int j = 0; j < count; j++)
			{
				if (links[j][i] == 1)
				{
					rank += (previousrank[j] / pointingto[j]);
				}
			}
			newrank[i] = ((1 - d)/N) + (d * rank);
		}

	}

	double minpr = 0.0, maxpr = 0.0;

	for (int i = 0; i < count; i++)
	{
		if (newrank[i] > maxpr)
			maxpr = newrank[i];
		if (newrank[i] < minpr)
			minpr = newrank[i];
	}

	for (int i = 0; i < count; i++)
	{
		double p_rank;
		p_rank = ((newrank[i] - minpr) / (maxpr - minpr));
		wp[i].pr = p_rank;
		wp[i].updateCTR();
	}
}

bool webpage::operator >(webpage pg2)
{
	return (score > pg2.getscore());
}
bool webpage::operator <(webpage pg2)
{
	return (score > pg2.getscore());
}