#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

// Function for Objective 1: Extract and Print Numbers from Input String
void extractNumbers()
{
    string input;
    cout << "Enter the input string: ";
    getline(cin, input);

    stringstream ss(input);
    string word;

    cout << "Extracted numbers:" << endl;
    while (ss >> word)
    {
        string number = "";
        for (char ch : word)
        {
            if (isdigit(ch))
            {
                number += ch;
            }
            else if (!number.empty())
            {
                cout << number << endl;
                number = "";
            }
        }
        if (!number.empty())
        {
            cout << number << endl;
        }
    }
}

// Function for Objective 2: Replace "charusat" with "university"
void replaceCharusat()
{
    string input;
    cout << "Enter the input string: ";
    getline(cin, input);

    size_t pos = input.find("charusat");
    while (pos != string::npos)
    {
        input.replace(pos, 8, "university");
        pos = input.find("charusat", pos + 10);
    }

    cout << "Modified string: " << input << endl;
}

// Function for Objective 3: Count Characters, Words, and Lines from Input File
void countFileStats()
{
    ifstream file("input.txt");
    if (!file.is_open())
    {
        cout << "Failed to open the file. Make sure 'input.txt' is present in the same directory." << endl;
        return;
    }

    string line;
    int charCount = 0, wordCount = 0, lineCount = 0;

    while (getline(file, line))
    {
        lineCount++;
        charCount += line.length() + 1; // Including newline character

        stringstream ss(line);
        string word;
        while (ss >> word)
        {
            wordCount++;
        }
    }

    file.close();

    cout << "Characters: " << charCount << endl;
    cout << "Words: " << wordCount << endl;
    cout << "Lines: " << lineCount << endl;
}

// Function for Objective 4: Validate Password
bool isValidPassword(const string &password)
{
    if (password.length() < 9 || password.length() > 15)
    {
        return false;
    }

    bool hasLower = false, hasUpper = false, hasDigit = false, hasSymbol = false;
    string symbols = "*;#$@";

    for (char ch : password)
    {
        if (islower(ch))
            hasLower = true;
        else if (isupper(ch))
            hasUpper = true;
        else if (isdigit(ch))
            hasDigit = true;
        else if (symbols.find(ch) != string::npos)
            hasSymbol = true;
    }

    return hasLower && hasUpper && hasDigit && hasSymbol;
}

void validatePassword()
{
    string password;
    cout << "Enter the password: ";
    getline(cin, password);

    if (isValidPassword(password))
    {
        cout << "Valid password" << endl;
    }
    else
    {
        cout << "Invalid password" << endl;
    }
}

// Main Function
int main()
{
    int choice;

    cout << "Select the objective to run:" << endl;
    cout << "1. Extract and print numbers from input string" << endl;
    cout << "2. Replace 'charusat' with 'university' in input text" << endl;
    cout << "3. Count characters, words, and lines from input file" << endl;
    cout << "4. Validate password" << endl;
    cout << "Enter your choice (1-4): ";
    cin >> choice;
    cin.ignore(); // Clear the input buffer

    switch (choice)
    {
    case 1:
        extractNumbers();
        break;
    case 2:
        replaceCharusat();
        break;
    case 3:
        countFileStats();
        break;
    case 4:
        validatePassword();
        break;
    default:
        cout << "Invalid choice. Please select between 1 and 4." << endl;
    }

    return 0;
}
