#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <set>
#include <iomanip>
using namespace std;

// Grammar rule representation
struct ProductionRule {
    char nonterm;      // LHS nonterminal
    string expansion;  // RHS production (# = epsilon)
};

// Handles predictive parsing table construction and LL(1) verification
class PredictiveParserTable {
private:
    vector<ProductionRule> rules;
    // Maps nonterminals to terminals to applicable productions
    map<char, map<char, vector<string>>> table;

    // Pre-computed FIRST sets for each production
    // (manually calculated for this specific grammar)
    map<pair<char, string>, set<char>> prodFirst;

    // Pre-computed FOLLOW sets for each nonterminal
    map<char, set<char>> followSet;

public:
    PredictiveParserTable(const vector<ProductionRule>& grammarRules) : rules(grammarRules) {
        // Hardcoded FIRST sets for this grammar
        for (const auto &rule : rules) {
            if (rule.nonterm == 'S' && rule.expansion == "ABC")
                prodFirst[{rule.nonterm, rule.expansion}] = {'a', 'b', '(', 'c'};
            else if (rule.nonterm == 'S' && rule.expansion == "D")
                prodFirst[{rule.nonterm, rule.expansion}] = {'a', '(', 'c'};
            else if (rule.nonterm == 'A' && rule.expansion == "a")
                prodFirst[{rule.nonterm, rule.expansion}] = {'a'};
            else if (rule.nonterm == 'A' && rule.expansion == "#")
                prodFirst[{rule.nonterm, rule.expansion}] = {'#'};
            else if (rule.nonterm == 'B' && rule.expansion == "b")
                prodFirst[{rule.nonterm, rule.expansion}] = {'b'};
            else if (rule.nonterm == 'B' && rule.expansion == "#")
                prodFirst[{rule.nonterm, rule.expansion}] = {'#'};
            else if (rule.nonterm == 'C' && rule.expansion == "(S)")
                prodFirst[{rule.nonterm, rule.expansion}] = {'('};
            else if (rule.nonterm == 'C' && rule.expansion == "c")
                prodFirst[{rule.nonterm, rule.expansion}] = {'c'};
            else if (rule.nonterm == 'D' && rule.expansion == "AC")
                prodFirst[{rule.nonterm, rule.expansion}] = {'a', '(', 'c'};
        }

        // Hardcoded FOLLOW sets for this grammar
        followSet['S'] = {')', '$'};
        followSet['A'] = {'b', '(', ')', '$'};
        followSet['B'] = {'(', 'c', '$'};
        followSet['C'] = {')', '$'};
        followSet['D'] = {')', '$'};

        buildTable();
    }

    // Constructs the parsing table based on FIRST and FOLLOW sets
    void buildTable() {
        for (const auto &rule : rules) {
            set<char> firsts = prodFirst[{rule.nonterm, rule.expansion}];

            // For non-epsilon productions: add to cells for each terminal in FIRST
            if (rule.expansion != "#") {
                for (char t : firsts) {
                    if (t == '#') continue;
                    table[rule.nonterm][t].push_back(rule.expansion);
                }
            }
            // For epsilon productions: add to cells for each terminal in FOLLOW
            else {
                for (char t : followSet[rule.nonterm]) {
                    table[rule.nonterm][t].push_back(rule.expansion);
                }
            }
        }
    }

    // Displays the parsing table in a formatted grid
    void printTable() {
        cout << "Predictive Parsing Table:" << endl;
        cout << setw(8) << "NT/T" << " | ";

        // Get all terminals in the table
        set<char> terminals;
        for (auto &row : table) {
            for (auto &entry : row.second)
                terminals.insert(entry.first);
        }
        terminals.insert('$');

        for (char t : terminals)
            cout << setw(8) << t;
        cout << endl;
        cout << string(8 + 3 + terminals.size() * 8, '-') << endl;

        // Print each row of the table
        for (auto &row : table) {
            char nt = row.first;
            cout << setw(8) << nt << " | ";
            for (char t : terminals) {
                if (row.second.count(t)) {
                    string cell;
                    for (const auto &prod : row.second[t])
                        cell += prod + " ";
                    cout << setw(8) << cell;
                } else {
                    cout << setw(8) << "";
                }
            }
            cout << endl;
        }
    }

    // Checks if grammar is LL(1) (no conflicts in the parsing table)
    bool isLL1() {
        for (auto &row : table) {
            for (auto &entry : row.second) {
                if (entry.second.size() > 1)
                    return false;
            }
        }
        return true;
    }
};

// Implements recursive descent parsing with backtracking
class RecursiveDescentParser {
private:
    vector<ProductionRule> ruleList;

    // Checks if a symbol is a nonterminal (uppercase letter)
    bool isNonterminal(char symbol) {
        return (symbol >= 'A' && symbol <= 'Z');
    }

    // Tries to match a single symbol against the input
    bool matchSymbol(char symbol, const string &source, int &pos) {
        if (!isNonterminal(symbol)) {
            // Terminal: direct match
            if (pos < source.size() && source[pos] == symbol) {
                pos++;
                return true;
            }
            return false;
        } else {
            // Nonterminal: try all applicable productions
            int startPos = pos;
            for (const auto &rule : ruleList) {
                if (rule.nonterm == symbol) {
                    pos = startPos; // Reset position before trying each rule
                    if (matchExpansion(rule.expansion, source, pos))
                        return true;
                }
            }
            return false;
        }
    }

    // Tries to match a full production against the input
    bool matchExpansion(const string &expansion, const string &source, int &pos) {
        if (expansion == "#") return true; // Epsilon case

        int currentPos = pos;
        for (int i = 0; i < expansion.size(); i++) {
            char ch = expansion[i];
            if (!isNonterminal(ch)) {
                // Terminal: direct match
                if (currentPos < source.size() && source[currentPos] == ch)
                    currentPos++;
                else
                    return false;
            } else {
                // Nonterminal: recursive match
                if (!matchSymbol(ch, source, currentPos))
                    return false;
            }
        }
        pos = currentPos;
        return true;
    }

public:
    RecursiveDescentParser(const vector<ProductionRule>& rules) : ruleList(rules) {}

    // Parses the entire input string from the start symbol
    bool parse(const string &source) {
        int pos = 0;
        if (!matchSymbol('S', source, pos))
            return false;
        return (pos == source.size()); // Must consume the entire input
    }
};

// Main program: builds table, checks LL(1) property, and validates input strings
int main() {
    // Grammar definition
    // S -> ABC | D
    // A -> a | ε
    // B -> b | ε
    // C -> (S) | c
    // D -> AC
    vector<ProductionRule> grammar = {
        {'S', "ABC"},
        {'S', "D"},
        {'A', "a"},
        {'A', "#"},
        {'B', "b"},
        {'B', "#"},
        {'C', "(S)"},
        {'C', "c"},
        {'D', "AC"}
    };

    // Build and display the parsing table
    PredictiveParserTable table(grammar);
    table.printTable();

    // Check if the grammar is LL(1)
    if (table.isLL1())
        cout << "\nThe grammar is LL(1)." << endl;
    else
        cout << "\nThe grammar is NOT LL(1)." << endl;

    // Validate user input
    RecursiveDescentParser rdParser(grammar);
    string str;
    cout << "\nEnter a string to validate: ";
    cin >> str;
    if (rdParser.parse(str))
        cout << "Valid string." << endl;
    else
        cout << "Invalid string." << endl;

    return 0;
}
