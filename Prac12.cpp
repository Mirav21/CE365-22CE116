#include <iostream>
#include <string>
#include <stack>
#include <cctype>
#include <cmath>
#include <sstream>

using namespace std;

// Check if a character is an operator
bool isOperator(char c)
{
    return c == '+' || c == '-' || c == '*' || c == '/';
}

// Check if a string represents a number
bool isNumeric(const string &str)
{
    if (str.empty())
        return false;

    bool hasDecimal = false;
    for (size_t i = 0; i < str.size(); i++)
    {
        if (i == 0 && str[i] == '-')
            continue; // Allow negative numbers
        if (str[i] == '.' && !hasDecimal)
        {
            hasDecimal = true;
            continue;
        }
        if (!isdigit(str[i]))
            return false;
    }
    return true;
}

// Check if a string represents a variable
bool isVariable(const string &str)
{
    if (str.empty())
        return false;
    if (!isalpha(str[0]))
        return false;

    for (char c : str)
    {
        if (!isalnum(c))
            return false;
    }
    return true;
}

// Calculate the result of an operation
double calculate(double a, double b, char op)
{
    switch (op)
    {
    case '+':
        return a + b;
    case '-':
        return a - b;
    case '*':
        return a * b;
    case '/':
        return a / b;
    default:
        return 0;
    }
}

// Function to get precedence of operators
int getPrecedence(char op)
{
    if (op == '+' || op == '-')
        return 1;
    if (op == '*' || op == '/')
        return 2;
    return 0;
}

// Convert infix expression to postfix
string infixToPostfix(const string &infix)
{
    stack<char> stk;
    string postfix = "";
    string token = "";

    for (size_t i = 0; i < infix.length(); i++)
    {
        char c = infix[i];

        if (isspace(c))
        {
            if (!token.empty())
            {
                postfix += token + " ";
                token = "";
            }
            continue;
        }

        if (isalnum(c) || c == '.')
        {
            token += c;
        }
        else
        {
            if (!token.empty())
            {
                postfix += token + " ";
                token = "";
            }

            if (c == '(')
            {
                stk.push(c);
            }
            else if (c == ')')
            {
                while (!stk.empty() && stk.top() != '(')
                {
                    postfix += stk.top();
                    postfix += " ";
                    stk.pop();
                }
                if (!stk.empty() && stk.top() == '(')
                {
                    stk.pop();
                }
            }
            else if (isOperator(c))
            {
                while (!stk.empty() && getPrecedence(stk.top()) >= getPrecedence(c) && stk.top() != '(')
                {
                    postfix += stk.top();
                    postfix += " ";
                    stk.pop();
                }
                stk.push(c);
            }
        }
    }

    if (!token.empty())
    {
        postfix += token + " ";
    }

    while (!stk.empty())
    {
        postfix += stk.top();
        postfix += " ";
        stk.pop();
    }

    return postfix;
}

// Evaluate postfix expression with constant folding
string evaluatePostfixWithFolding(const string &postfix)
{
    stack<string> stk;
    stringstream ss(postfix);
    string token;

    while (ss >> token)
    {
        if (isOperator(token[0]) && token.length() == 1)
        {
            if (stk.size() < 2)
                continue;

            string val2 = stk.top();
            stk.pop();
            string val1 = stk.top();
            stk.pop();

            // If both operands are numbers, perform the calculation
            if (isNumeric(val1) && isNumeric(val2))
            {
                double num1 = stod(val1);
                double num2 = stod(val2);
                double result = calculate(num1, num2, token[0]);

                // Check if result is an integer
                if (result == floor(result))
                {
                    stk.push(to_string((int)result));
                }
                else
                {
                    stk.push(to_string(result));
                }
            }
            else
            {
                // If at least one operand is a variable, push back the expression
                stk.push("(" + val1 + " " + token + " " + val2 + ")");
            }
        }
        else
        {
            stk.push(token);
        }
    }

    if (stk.empty())
        return "";
    return stk.top();
}

// Clean up the result by removing unnecessary parentheses and spaces
string cleanupResult(string result)
{
    // Remove outermost parentheses if they enclose the entire expression
    if (!result.empty() && result[0] == '(' && result[result.length() - 1] == ')')
    {
        result = result.substr(1, result.length() - 2);
    }

    // Replace multiple spaces with a single space
    size_t pos = 0;
    while ((pos = result.find("  ", pos)) != string::npos)
    {
        result.replace(pos, 2, " ");
    }

    // Remove space before and after operators
    for (char op : "+-*/()")
    {
        pos = 0;
        string opStr(1, op);
        while ((pos = result.find(" " + opStr + " ", pos)) != string::npos)
        {
            result.replace(pos, 3, opStr);
        }
        pos = 0;
        while ((pos = result.find(" " + opStr, pos)) != string::npos)
        {
            result.replace(pos, 2, opStr);
        }
        pos = 0;
        while ((pos = result.find(opStr + " ", pos)) != string::npos)
        {
            result.replace(pos, 2, opStr);
        }
    }

    return result;
}

// Main function to optimize an expression using constant folding
string optimizeExpression(const string &expr)
{
    string postfix = infixToPostfix(expr);
    string result = evaluatePostfixWithFolding(postfix);
    return cleanupResult(result);
}

int main()
{
    string expr;

    cout << "Enter an arithmetic expression: ";
    getline(cin, expr);

    string optimized = optimizeExpression(expr);

    cout << "Original expression: " << expr << endl;
    cout << "Optimized expression: " << optimized << endl;

    return 0;
}