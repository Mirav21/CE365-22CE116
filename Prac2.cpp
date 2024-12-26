#include <bits/stdc++.h>

using namespace std;

int main(){
    char Exit= 'y';

    while(Exit=='y'){
        int no_of_symbols,no_of_states,initial_state,no_of_accepting_states;

        cout<<"Number of input symbols : ";
        cin>>no_of_symbols;
        cout<<endl;

        char inp_symbols[no_of_symbols],curr_symbol;

        for(int i=0;i<no_of_symbols;i++){
            cout<<"Input symbol ("<<i+1<<") : ";
            cin>>inp_symbols[i];
            cout<<endl;
        }

        cout<<"Enter number of states : ";
        cin>>no_of_states;
        cout<<endl;

        cout<<"Initial state : ";
        cin>>initial_state;
        cout<<endl;

        cout<<"Number of accepting states : ";
        cin>>no_of_accepting_states;
        cout<<endl;

        if(no_of_accepting_states>no_of_states){
            cout<<"Number of states should be less then number of states..."<<endl;
            return 0;
        }

        int accepting_states[no_of_accepting_states];

        for(int i=0;i<no_of_accepting_states;i++){
            cout<<"Accepting state ("<<i+1<<") : ";
            cin>>accepting_states[i];
            cout<<endl;
        }

        cout<<endl;

        int transition_table[no_of_states][no_of_symbols];

        for(int i=0;i<no_of_states;i++){
            for(int j=0;j<no_of_symbols;j++){
                cout<<i+1<<" to "<<inp_symbols[j]<<" -> : ";
                cin>>transition_table[i][j];
            }
        }
        cout<<endl;

        char exit='1';
        while(exit == '1'){
            string inp_string;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Input string: ";
            getline(cin, inp_string);
            cout << endl;

            size_t inp_str_length = inp_string.length();
            int curr_state = initial_state;

            for(size_t i=0;i<inp_str_length;i++){
                for(int j=0;j<no_of_symbols;j++){
                    if(inp_symbols[j]==inp_string[i]){
                        curr_state = transition_table[curr_state-1][j];
                    }
                }
            }


            for(int i=0;i<no_of_accepting_states;i++){
                if(accepting_states[i]==curr_state){
                    cout<<"Valid String";
                    break;
                }
                else{
                    cout<<"Invalid String";
                    break;
                }
            }

            cout<<"\nFor continuing the validation of string enter (1) or enter (0) for exit... : ";
            cin>>exit;
            cout<<endl;

        }

        cout<<"\nFor continuing the validation of another FA enter (y) or enter (n) for exit... : ";
        cin>>Exit;
        cout<<endl;
    }

    return 0;
}
