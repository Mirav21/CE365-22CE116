#include <bits/stdc++.h>
#include <fstream>
using namespace std;

bool isInteger(const string &str)
{
    for (char ch : str)
    {
        if (!isdigit(ch))
            return false;
    }
    return !str.empty();
}

bool isCharLiteral(const string &str)
{
    return str.length() == 3 && str[0] == '\'' && str[2] == '\''; // e.g., 'x'
}

bool isValidIdentifier(const string &str)
{
    if (str.empty() || isdigit(str[0]))
        return false;
    return regex_match(str, regex("[_a-zA-Z][_a-zA-Z0-9]*"));
}

int main()
{
    vector<string> keywords = {
        "auto", "break", "case", "char", "const", "continue", "default", "do",
        "double", "else", "enum", "extern", "float", "for", "goto", "if",
        "inline", "int", "long", "register", "restrict", "return", "short",
        "signed", "sizeof", "static", "struct", "switch", "typedef", "union",
        "unsigned", "void", "volatile", "while", "_Alignas", "_Alignof",
        "_Atomic", "_Bool", "_Complex", "_Generic", "_Imaginary", "_Noreturn",
        "_Static_assert", "_Thread_local"};

    vector<string> operators = {
        "+", "-", "*", "/", "%", "++", "--", "=", "+=", "-=", "*=", "/=", "%=",
        "==", "!=", ">", "<", ">=", "<=", "&&", "||", "!", "&", "|", "^", "~",
        "<<", ">>", "->", ".", "?:"};

    vector<string> punctuations = {
        "{", "}", "(", ")", "[", "]", ";", ",", ":", "#", "\\"};

    string filePath = "file.c";
    ifstream cFile(filePath);

    if (!cFile.is_open())
    {
        cout << "Error: Could not open the file " << filePath << endl;
        return 1;
    }

    string line;
    int line_number = 0;
    bool isEndOfComment = false;
    set<string> symbolTable;
    vector<string> lexicalErrors;

    while (getline(cFile, line))
    {
        line_number++;
        string word = "";
        size_t line_length = line.length();

        if (line[0] == '/' && line[1] == '/')
        {
            continue;
        }

        for (size_t j = 0; j < line_length; j++)
        {
            if (!isEndOfComment && j + 1 < line.length() && line[j] == '/' && line[j + 1] == '*')
            {
                isEndOfComment = true;
                j++;
                continue;
            }

            if (isEndOfComment)
            {
                if (j + 1 < line.length() && line[j] == '*' && line[j + 1] == '/')
                {
                    isEndOfComment = false;
                    j++;
                }
                continue;
            }

            if (line[j] == ' ' || find(punctuations.begin(), punctuations.end(), string(1, line[j])) != punctuations.end())
            {
                if (!word.empty())
                {
                    if (isInteger(word))
                    {
                        // Valid Integer
                    }
                    else if (isCharLiteral(word))
                    {
                        // Valid Char Literal
                    }
                    else
                    {
                        auto it_keywords = find(keywords.begin(), keywords.end(), word);
                        auto it_operators = find(operators.begin(), operators.end(), word);
                        auto it_punctuations = find(punctuations.begin(), punctuations.end(), word);

                        if (it_keywords == keywords.end() && it_operators == operators.end() && it_punctuations == punctuations.end())
                        {
                            if (isValidIdentifier(word))
                            {
                                symbolTable.insert(word);
                            }
                            else
                            {
                                lexicalErrors.push_back("line:" + to_string(line_number) + " " + word + " invalid lexeme");
                            }
                        }
                    }
                    word = "";
                }
            }
            else
            {
                word += line[j];
            }
        }

        if (!word.empty())
        {
            if (isInteger(word))
            {
                // Valid Integer
            }
            else if (isCharLiteral(word))
            {
                // Valid Char Literal
            }
            else
            {
                auto it_keywords = find(keywords.begin(), keywords.end(), word);
                auto it_operators = find(operators.begin(), operators.end(), word);
                auto it_punctuations = find(punctuations.begin(), punctuations.end(), word);

                if (it_keywords == keywords.end() && it_operators == operators.end() && it_punctuations == punctuations.end())
                {
                    if (isValidIdentifier(word))
                    {
                        symbolTable.insert(word);
                    }
                    else
                    {
                        lexicalErrors.push_back("line:" + to_string(line_number) + " " + word + " invalid lexeme");
                    }
                }
            }
        }
    }

    cFile.close();

    // Display Lexical Errors
    if (!lexicalErrors.empty())
    {
        cout << "LEXICAL ERRORS" << endl;
        for (const auto &error : lexicalErrors)
        {
            cout << error << endl;
        }
    }

    // Display the Symbol Table
    cout << "\nSYMBOL TABLE ENTRIES" << endl;
    int count = 1;
    for (const auto &symbol : symbolTable)
    {
        cout << count++ << ") " << symbol << endl;
    }

    return 0;
}
