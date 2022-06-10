#ifndef FLOWSEARCH_H
#define FLOWSEARCH_H

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include "webpage.h"
#include <string>
using namespace std;

void startscreen(vector <webpage> pgs);
void newsearch(vector <webpage> pgs);
vector<int> search_two(string k1, string k2, vector <webpage> pgs);
vector<int> search_one(string k1, string k2, vector <webpage> pgs);
vector<int> search_kw(string kw, vector <webpage> pgs);
void display_results(vector<int> results, vector<webpage> pgs);
void open_webpage(int x, vector<int> results, vector<webpage> pgs);
void exit_program(vector <webpage> pgs);
bool comparator(webpage pg1, webpage pg2);

#endif