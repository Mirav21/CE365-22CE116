#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <sstream>
#include <iomanip>

using namespace std;

// Structure to represent a quadruple
struct Quadruple
{
    string op;
    string arg1;
    string arg2;
    string result;
};

class QuadrupleGenerator
{
private:
    string str;
    vector<Quadruple> quads;
    int tempCount = 0;
    int pos = 0;

    // Generate a new temporary variable name
    string newTemp()
    {
        return "t" + to_string(++tempCount);
    }

    // Check if the character is a digit or decimal point
    bool isDigitOrDecimal(char c)
    {
        return isdigit(c) || c == '.';
    }

    // Parse a number from the input
    string parseNumber()
    {
        int start = pos;
        while (pos < str.length() && isDigitOrDecimal(str[pos]))
        {
            pos++;
        }
        return str.substr(start, pos - start);
    }

    // Skip whitespace
    void skipWhitespace()
    {
        while (pos < str.length() && isspace(str[pos]))
        {
            pos++;
        }
    }

    // Parse expressions according to the grammar
    // E → E + T | E – T | T
    string parseE()
    {
        string left = parseT();

        while (pos < str.length() && (str[pos] == '+' || str[pos] == '-'))
        {
            char op = str[pos++];
            skipWhitespace();
            string right = parseT();
            string temp = newTemp();

            Quadruple q;
            q.op = string(1, op);
            q.arg1 = left;
            q.arg2 = right;
            q.result = temp;
            quads.push_back(q);

            left = temp;
        }

        return left;
    }

    // T → T * F | T / F | F
    string parseT()
    {
        string left = parseF();

        while (pos < str.length() && (str[pos] == '*' || str[pos] == '/'))
        {
            char op = str[pos++];
            skipWhitespace();
            string right = parseF();
            string temp = newTemp();

            Quadruple q;
            q.op = string(1, op);
            q.arg1 = left;
            q.arg2 = right;
            q.result = temp;
            quads.push_back(q);

            left = temp;
        }

        return left;
    }

    // F → (E) | digit
    string parseF()
    {
        skipWhitespace();
        string result;

        if (pos < str.length() && str[pos] == '(')
        {
            pos++; // Skip '('
            skipWhitespace();
            result = parseE();
            skipWhitespace();
            if (pos < str.length() && str[pos] == ')')
            {
                pos++; // Skip ')'
            }
        }
        else if (pos < str.length() && isDigitOrDecimal(str[pos]))
        {
            result = parseNumber();
        }

        skipWhitespace();
        return result;
    }

public:
    QuadrupleGenerator(const string &input) : str(input) {}

    void generate()
    {
        pos = 0;
        tempCount = 0;
        quads.clear();
        parseE();
    }

    void printQuadruples()
    {
        cout << left << setw(10) << "Operator"
             << setw(10) << "Operand 1"
             << setw(10) << "Operand 2"
             << setw(10) << "Result" << endl;

        for (const auto &q : quads)
        {
            cout << left << setw(10) << q.op
                 << setw(10) << q.arg1
                 << setw(10) << q.arg2
                 << setw(10) << q.result << endl;
        }
    }
};

int main()
{
    string str;

    cout << "Enter an arithmetic expression: ";
    getline(cin, str);

    QuadrupleGenerator gen(str);
    gen.generate();

    cout << "\nQuadruple Table:\n";
    gen.printQuadruples();

    return 0;
}
