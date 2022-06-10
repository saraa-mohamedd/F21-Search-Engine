#ifndef WEBPAGE_H
#define WEBPAGE_H

#include <vector>
#include <string>
#include <iostream>
#include <unordered_map>
using namespace std;

class webpage
{
public:
	webpage();
	webpage(string n, vector<string> k);

	void setname(string n);
	void setscore(double s);
	string getname();
	int getclicks();
	int getimpressions();
	double getscore();

	void setkeywords(vector<string> kw);
	void setimpressions(int n);
	void setclicks(int n);
	void setpagerank(double pr);

	void incrementclicks();
	void incrementimpressions();
	void updateCTR();
	void updatescore();

	void printpage();
	bool keywordfound(string kw);

	static unordered_map<string, int> keys;
	static int* pointingto;
	static webpage* sortedpgs;
	static int count;
	static void pagerank(vector<webpage> &wp, int** links);

	bool operator >(webpage pg2);
	bool operator <(webpage pg2);

private:
	string name;
	vector<string> keywords;
	int impressions;

	int clicks;
	double CTR;
	double pr;
	double score;
};

#endif