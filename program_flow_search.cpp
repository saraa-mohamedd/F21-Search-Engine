#include "program_flow_search.h"

void startscreen(vector <webpage> pgs)
{
    string choice;
    char c;
    cout << endl << endl;
    cout << " Welcome!\n What would you like to do?" << endl;
    cout << " 1. New Search\n 2. Exit" << endl << endl;
    cout << " Type in your choice: ";
    cin.get(c);

    while (c != '\n')
    {
        choice += c;
        cin.get(c);
    }
        
    while (choice != "1" && choice != "2")
    {
        choice = "";
        cout << "\n Invalid choice! Please try again: ";

        cin.get(c);
        while (c != '\n')
        {
            choice += c;
            cin.get(c);
        }
    }

    if (choice == "1")
    {
        newsearch(pgs);
    }

    else if (choice == "2")
    {
        exit(0);
    }

}

void newsearch(vector <webpage> pgs)
{
    sort(pgs.begin(), pgs.end(), &comparator);

    string search; char c;
    vector<int> searchresults;

    cout << " What keywords would you like to search for ?" << endl << endl;
    cout << " SEARCH BAR: ";

    cin.get(c);
    while (c != '\n')
    {
        search += c;
        cin.get(c);
    }

    int andexists, orexists, spaceexists;
    andexists = search.find(" AND ");
    orexists = search.find(" OR ");
    spaceexists = search.find(" ");
    if (andexists != search.npos)
    {
        string k1 = search.substr(0, andexists);
        string k2 = search.substr(andexists + 5, search.length() - (andexists + 5));

        searchresults = search_two(k1, k2, pgs);
    }
    else if (orexists != search.npos)
    {
        string k1 = search.substr(0, orexists);
        string k2 = search.substr(orexists + 4, search.length() - (orexists + 4));

        searchresults = search_one(k1, k2, pgs);
    }
    else if (search[0] == '"' && search[search.length() - 1] == '"')
    {
        string keyword = search.substr(1, search.length() - 2);
        searchresults = search_kw(keyword, pgs);
    }
    else if (spaceexists != search.npos)
    {
        string k1 = search.substr(0, spaceexists);
        string k2 = search.substr(spaceexists + 1, search.length() - (spaceexists + 1));

        searchresults = search_one(k1, k2, pgs);
    }
    else
    {
        searchresults = search_kw(search, pgs);
    }

    display_results(searchresults, pgs);
}

vector<int> search_two(string k1, string k2, vector <webpage> pgs)
{
    vector <int> result;

    for (int i = 0; i < pgs.size(); i++)
    {
        if (pgs[i].keywordfound(k1) && pgs[i].keywordfound(k2))
        {
            result.push_back(i);
        }
    }

    return result;
}

vector<int> search_one(string k1, string k2, vector <webpage> pgs)
{
    vector <int> result;

    for (int i = 0; i < pgs.size(); i++)
    {
        if (pgs[i].keywordfound(k1) || pgs[i].keywordfound(k2))
        {
            result.push_back(i);
        }
            
    }
    return result;
}

vector<int> search_kw(string kw, vector <webpage> pgs)
{
    vector <int> result;

    for (int i = 0; i < pgs.size(); i++)
    {
        if (pgs[i].keywordfound(kw))
        {
            result.push_back(i);
        }
    }
    return result;
}

void display_results(vector<int> results, vector<webpage> pgs)
{

    if (results.empty())
    {
        string choice; char c;

        cout << " No results found for your entered keywords :(." << endl;
        cout << endl << " Would you like to: " << endl;
        cout << " 1. New Search" << endl << " 2. Exit" << endl << endl;
        cout << " Type in your choice: ";
        cin.get(c);

        while (c != '\n')
        {
            choice += c;
            cin.get(c);
        }

        while (choice != "1" && choice != "2")
        {
            choice = "";
            cout << "\n Invalid choice! Please try again: ";

            cin.get(c);
            while (c != '\n')
            {
                choice += c;
                cin.get(c);
            }
        }

        if (choice == "1")
        {
            newsearch(pgs);
        }

        else if (choice == "2")
        {
            exit_program(pgs);
        }
    }

    string choice; char c;
    cout << " Search results: " << endl;
    for (int i = 0; i < results.size(); i++)
    {
        pgs[results[i]].incrementimpressions();
        cout << " " << i + 1 << ". " << pgs[results[i]].getname() << endl;
    }

    cout << endl << " Would you like to: " << endl;
    cout << " 1. Choose a webpage to open" << endl;
    cout << " 2. New Search" << endl << " 3. Exit" << endl << endl;
    cout << " Type in your choice: ";
    cin.get(c);

    while (c != '\n')
    {
        choice += c;
        cin.get(c);
    }

    while (choice != "1" && choice != "2" && choice != "3")
    {
        choice = "";
        cout << "\n Invalid choice! Please try again: ";

        cin.get(c);
        while (c != '\n')
        {
            choice += c;
            cin.get(c);
        }
    }

    if (choice == "1")
    {
        char n, discard;
        cout << endl << " Which webpage would you like to open? Please enter its number: ";

        cin.get(n);
        cin.get(discard);           // encountered issue with the '\n' being sent to open_webpage so used discard to ignore '\n'
        open_webpage(n - '0' - 1, results, pgs);
    }

    else if (choice == "2")
    {
        newsearch(pgs);
    }

    else if (choice == "3")
    {
        exit_program(pgs);
    }
}

void open_webpage(int x, vector<int> results, vector<webpage> pgs)
{
    pgs[results[x]].incrementclicks();

    cout << endl << " You are now viewing " << pgs[results[x]].getname() << ".";
    cout << endl << " Would you like to " << endl;

    cout << " 1. Go back to search results" << endl;
    cout << " 2. New Search" << endl << " 3. Exit" << endl << endl;
    cout << " Type in your choice: ";

    string choice; char c;
    cin.get(c);

    while (c != '\n')
    {
        choice += c;
        cin.get(c);
    }

    while (choice != "1" && choice != "2" && choice != "3")
    {
        choice = "";
        cout << "\n Invalid choice! Please try again: ";

        cin.get(c);
        while (c != '\n')
        {
            choice += c;
            cin.get(c);
        }
    }

    if (choice == "1")
    {
        display_results(results, pgs);
    }

    else if (choice == "2")
    {
        newsearch(pgs);
    }

    else if (choice == "3")
    {
        exit_program(pgs);
    }
}

void exit_program(vector <webpage> pgs)
{
    ofstream updated;
    updated.open("newimpressionsandclicks.csv");

    for (int i = 0; i < pgs.size(); i++)
    {
        updated << pgs[i].getname() << ",";
        updated << pgs[i].getimpressions();

        if (pgs[i].getclicks() == 0)
            updated << "\n";

        else
            updated << "," << pgs[i].getclicks() << "\n";
    }

    updated.close();

    remove("impressionsfile.csv");
    rename("newimpressionsandclicks.csv", "impressionsfile.csv");
}

bool comparator(webpage pg1, webpage pg2)
{
    return (pg1 > pg2);
}