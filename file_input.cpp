#include "file_input.h"

void page_initialization(vector<webpage> &pgs)
{
    ifstream pages;
    pages.open("keywordsfile.csv");

    if (pages.fail())
    {
        cout << "file open fail" << endl;
        return;
    }

    string temp;
    string nm;
    int num = 0;
    while (getline(pages, nm, ','))
    {
        string keywords, kw;
        vector<string> kws;

        getline(pages, keywords, '\n');

        string word;
        while (keywords.find_first_of(',') != -1)
        {
            int loc = keywords.find_first_of(',');
            word = keywords.substr(0, loc);

            kws.push_back(word);

            keywords = keywords.substr(loc + 1, keywords.length() - loc);
        }


        kws.push_back(keywords);

        pgs.push_back(webpage(nm, kws));

        webpage::keys.insert({ nm, num });
        num++;

    }

    webpage::count = num;
    pages.close();

    ifstream impressions;
    impressions.open("impressionsfile.csv");

    if (impressions.fail())
    {
        cout << "file open fail" << endl;
        return;
    }

    string name;
    while (getline(impressions, name, ','))
    {
        int key;
        key = webpage::keys[name];
        string i;

        getline(impressions, i, '\n');

        if (i.find(",") != i.npos)
        {
            string imp, clicks;
            imp = i.substr(0, i.find(","));
            clicks = i.substr(i.find(",") + 1, i.length() - (i.find(",") + 1));

            pgs.at(key).setimpressions(stoi(imp));
            pgs.at(key).setclicks(stoi(clicks));
        }
        else
        {
            pgs.at(key).setimpressions(stoi(i));
        }
        
    }

    impressions.close();

    ifstream hyperlinks;
    hyperlinks.open("hyperlinksfile.csv");

    if (hyperlinks.fail())
    {
        cout << "file open fail" << endl;
        return;
    }

    int** links = new int* [webpage::count];
    for (int i = 0; i < webpage::count; i++)
    {
        links[i] = new int[webpage::count];
    }

    for (int i = 0; i < webpage::count; i++)
    {
        for (int j = 0; j < webpage::count; j++)
        {
            links[i][j] = 0;
        }
    }
    webpage::pointingto = new int[webpage::count];
    for (int i = 0; i < webpage::count; i++)
        webpage::pointingto[i] = 0;

    string n1;
    while (getline(hyperlinks, n1, ','))
    {
        string n2;
        int node1, node2;

        getline(hyperlinks, n2, '\n');

        node1 = webpage::keys[n1];
        node2 = webpage::keys[n2];

        links[node1][node2] = 1;

        webpage::pointingto[node1]++;
    }

    webpage::pagerank(pgs, links);
}