#include <bits/stdc++.h>

using namespace std;
char startSymbol = 'S';

// Function to calculate FIRST set
void calculateFirst(map<char, vector<string>> &grammar, map<char, set<char>> &first)
{
    bool changed;
    do
    {
        changed = false;
        for (auto &entry : grammar)
        {
            char nonTerminal = entry.first;
            vector<string> productions = entry.second;

            size_t oldSize = first[nonTerminal].size();

            for (const string &production : productions)
            {
                bool isNullable = true;

                for (char symbol : production)
                {
                    if (!isupper(symbol))
                    { // Terminal or empty string (epsilon)
                        if (symbol != '\0')
                        { // Avoid inserting empty character
                            first[nonTerminal].insert(symbol);
                        }
                        isNullable = (production == ""); // Empty string is epsilon
                        break;
                    }
                    else
                    { // Non-terminal
                        for (char ch : first[symbol])
                        {
                            if (ch != '\0')
                                first[nonTerminal].insert(ch);
                        }
                        if (first[symbol].find('\0') == first[symbol].end())
                        {
                            isNullable = false;
                            break;
                        }
                    }
                }

                if (isNullable)
                    first[nonTerminal].insert('\0'); // Using '\0' for empty string
            }

            if (first[nonTerminal].size() > oldSize)
                changed = true;
        }
    } while (changed);
}

// Function to calculate FOLLOW set
void calculateFollow(map<char, vector<string>> &grammar, map<char, set<char>> &first, map<char, set<char>> &follow)
{
    // Initialize FOLLOW(S) with '$'
    follow[startSymbol].insert('$');

    bool changed;
    do
    {
        changed = false;
        for (auto &entry : grammar)
        {
            char nonTerminal = entry.first;
            vector<string> productions = entry.second;

            for (const string &production : productions)
            {
                for (size_t i = 0; i < production.size(); i++)
                {
                    char symbol = production[i];
                    if (isupper(symbol))
                    { // If it's a non-terminal
                        size_t oldSize = follow[symbol].size();

                        bool isNullable = true;
                        for (size_t j = i + 1; j < production.size(); j++)
                        {
                            char nextSymbol = production[j];

                            if (!isupper(nextSymbol))
                            { // If terminal, add directly
                                follow[symbol].insert(nextSymbol);
                                isNullable = false;
                                break;
                            }
                            else
                            { // If non-terminal, add its FIRST set
                                for (char ch : first[nextSymbol])
                                {
                                    if (ch != '\0') // Skip epsilon
                                        follow[symbol].insert(ch);
                                }
                                if (first[nextSymbol].find('\0') == first[nextSymbol].end())
                                {
                                    isNullable = false;
                                    break;
                                }
                            }
                        }

                        // If nullable, inherit FOLLOW set
                        if (isNullable)
                        {
                            for (char ch : follow[nonTerminal])
                            {
                                follow[symbol].insert(ch);
                            }
                        }

                        if (follow[symbol].size() > oldSize)
                            changed = true;
                    }
                }
            }
        }
    } while (changed);
}

// Function to print FIRST & FOLLOW sets
void printSets(const string &name, map<char, set<char>> &sets)
{
    cout << "\n"
         << name << " sets:\n";
    for (auto &entry : sets)
    {
        cout << name << "(" << entry.first << ") = { ";
        for (char ch : entry.second)
        {
            if (ch == '\0')
                cout << "ε ";
            else if (ch == '$')
                cout << "$ ";
            else
                cout << ch << " ";
        }
        cout << "}" << endl;
    }
}

int main()
{
    map<char, vector<string>> grammar = {
        {'S', {"ABC", "D"}},
        {'A', {"a", ""}}, // Using "" for epsilon
        {'B', {"b", ""}},
        {'C', {"(S)", "c"}},
        {'D', {"AC"}}};

    map<char, set<char>> first;
    map<char, set<char>> follow;

    calculateFirst(grammar, first);
    calculateFollow(grammar, first, follow);

    printSets("FIRST", first);
    printSets("FOLLOW", follow);

    return 0;
}
