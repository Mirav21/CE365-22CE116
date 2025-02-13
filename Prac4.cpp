#include <bits/stdc++.h>
#include <fstream>

using namespace std;

bool isInteger(const string &str)
{
    try
    {
        // Try converting the string to an integer
        stoi(str);
        return true;
    }
    catch (const invalid_argument &e)
    {
        return false; // Not a valid integer
    }
    catch (const out_of_range &e)
    {
        return false; // Number out of range for int type
    }
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

    while (getline(cFile, line))
    {
        line_number++;
        string word = "";
        size_t i = 0;
        size_t line_length = line.length();

        if (line[i] == '/' && line[i + 1] == '/')
        {
            continue;
        }

        for (size_t j = 0; j < line_length; j++)
        {
            // Handle block comments
            if (!isEndOfComment && j + 1 < line.length() && line[j] == '/' && line[j + 1] == '*')
            {
                isEndOfComment = true;
                j++; // Skip the '*' after '/'
                continue;
            }

            if (isEndOfComment)
            {
                if (j + 1 < line.length() && line[j] == '*' && line[j + 1] == '/')
                {
                    isEndOfComment = false; // End of the comment
                    j++;                    // Skip the '/' after '*'
                }
                continue; // Skip the content inside the comment
            }

            // Check for spaces, operators, or punctuation
            if (line[j] == ' ' || find(punctuations.begin(), punctuations.end(), string(1, line[j])) != punctuations.end())
            {
                if (!word.empty())
                {
                    auto it_keywords = find(keywords.begin(), keywords.end(), word);
                    auto it_operators = find(operators.begin(), operators.end(), word);
                    auto it_punctuations = find(punctuations.begin(), punctuations.end(), word);

                    if (it_keywords != keywords.end())
                    {
                        // cout << "Keyword: " << word << endl;
                    }
                    else if (it_operators != operators.end())
                    {
                        // cout << "Operator: " << word << endl;
                    }
                    else if (it_punctuations != punctuations.end())
                    {
                        // cout << "Punctuation: " << word << endl;
                    }
                    else
                    {
                        // cout << "Other: " << word << endl;

                        if (!isInteger(word))
                        {
                            if (!isalpha(word[0]) || !word[0] != '_')
                            {
                                cout << "line:" << line_number << " " << word << " invalid lexeme" << endl;
                            }
                        }
                        else if (!isInteger(word))
                        {
                            cout << "line:" << line_number << " " << word << " invalid lexeme" << endl;
                        }
                    }
                    word = ""; // Reset word after processing
                }

                // Handle punctuation as single tokens
                if (find(punctuations.begin(), punctuations.end(), string(1, line[j])) != punctuations.end())
                {
                    // cout << "Punctuation: " << line[j] << endl;
                }
            }
            else
            {
                word += line[j]; // Accumulate characters for a word
            }
        }

        // After finishing the line, check for the last word
        if (!word.empty())
        {
            auto it_keywords = find(keywords.begin(), keywords.end(), word);
            auto it_operators = find(operators.begin(), operators.end(), word);
            auto it_punctuations = find(punctuations.begin(), punctuations.end(), word);

            if (it_keywords != keywords.end())
            {
                cout << "Keyword: " << word << endl;
            }
            else if (it_operators != operators.end())
            {
                cout << "Operator: " << word << endl;
            }
            else if (it_punctuations != punctuations.end())
            {
                cout << "Punctuation: " << word << endl;
            }
            else
            {
                cout << "Other: " << word << endl;
            }
        }
    }

    cFile.close();
    return 0;
}
