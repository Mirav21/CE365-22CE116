#include <bits/stdc++.h>

using namespace std;

int main()
{
    char Exit = 'y';

    // Loop to allow multiple FA validations
    while (Exit == 'y')
    {
        int no_of_symbols, no_of_states, initial_state, no_of_accepting_states;

        // Get the number of input symbols
        cout << "Number of input symbols : ";
        cin >> no_of_symbols;
        cout << endl;

        char inp_symbols[no_of_symbols];

        // Input symbols for the FA
        for (int i = 0; i < no_of_symbols; i++)
        {
            cout << "Input symbol (" << i + 1 << ") : ";
            cin >> inp_symbols[i];
            cout << endl;
        }

        // Get the number of states in the FA
        cout << "Enter number of states : ";
        cin >> no_of_states;
        cout << endl;

        // Input the initial state
        cout << "Initial state : ";
        cin >> initial_state;
        cout << endl;

        // Input the number of accepting states
        cout << "Number of accepting states : ";
        cin >> no_of_accepting_states;
        cout << endl;

        // Check if accepting states are valid
        if (no_of_accepting_states > no_of_states)
        {
            cout << "Number of accepting states should be less than number of states..." << endl;
            return 0;
        }

        int accepting_states[no_of_accepting_states];

        // Input accepting states
        for (int i = 0; i < no_of_accepting_states; i++)
        {
            cout << "Accepting state (" << i + 1 << ") : ";
            cin >> accepting_states[i];
            cout << endl;
        }

        cout << endl;

        int transition_table[no_of_states][no_of_symbols];

        // Fill transition table for each state and input symbol
        for (int i = 0; i < no_of_states; i++)
        {
            for (int j = 0; j < no_of_symbols; j++)
            {
                cout << i + 1 << " to " << inp_symbols[j] << " -> : ";
                cin >> transition_table[i][j];
            }
        }
        cout << endl;

        char exit = '1';
        // Loop to allow multiple string validations
        while (exit == '1')
        {
            string inp_string;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Input string: ";
            getline(cin, inp_string);
            cout << endl;

            size_t inp_str_length = inp_string.length();
            int curr_state = initial_state;

            // Process the input string
            for (size_t i = 0; i < inp_str_length; i++)
            {
                for (int j = 0; j < no_of_symbols; j++)
                {
                    if (inp_symbols[j] == inp_string[i])
                    {
                        curr_state = transition_table[curr_state - 1][j];
                    }
                }
            }

            // Check if the string ends in an accepting state
            bool is_valid = false;
            for (int i = 0; i < no_of_accepting_states; i++)
            {
                if (accepting_states[i] == curr_state)
                {
                    is_valid = true;
                    break;
                }
            }

            if (is_valid)
            {
                cout << "Valid String";
            }
            else
            {
                cout << "Invalid String";
            }

            // Ask user if they want to validate another string
            cout << "\nFor continuing the validation of string enter (1) or enter (0) for exit... : ";
            cin >> exit;
            cout << endl;
        }

        // Ask user if they want to define another FA
        cout << "\nFor continuing the validation of another FA enter (y) or enter (n) for exit... : ";
        cin >> Exit;
        cout << endl;
    }

    return 0;
}
