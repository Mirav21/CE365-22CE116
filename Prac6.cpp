#include <iostream>
using namespace std;

// Grammar:
// S → ( L ) | a
// L → S L’
// L’ → , S L’ | ϵ

int i, f = 0;  // 'i' is the current index, 'f' is a flag for validation
string str;

void _L();
void S();

// Function to process L → S L'
void L()
{
    S();  // Process 'S'
    _L(); // Process 'L’' (optional part)
}

// Function to process S → ( L ) | a
void S()
{
    if (str[i] == '(')  // If '(' is found, it must be followed by L and ')'
    {
        i++;
        L();
        if (str[i] == ')')
            i++;
        else
            f = 1;  // Invalid if ')' is missing
    }
    else if (str[i] == 'a')  // If 'a' is found, move to the next character
    {
        i++;
    }
    else
    {
        f = 1;  // Invalid case
    }
}

// Function to process L' → , S L' | ϵ
void _L()
{
    if (str[i] == ',')  // If ',' is found, process the next 'S' and continue
    {
        i++;
        S();
        _L();
    }
    // Else, return (ϵ case: nothing needs to be done)
}

int main()
{
    cout << "Enter a string: ";
    getline(cin, str);
    i = 0;
    S();  // Start parsing

    // If parsing completed successfully and we reached the end of the string
    if (f == 0 && i == str.length())
        cout << "Valid string" << endl;
    else
        cout << "Invalid string" << endl;

    return 0;
}
