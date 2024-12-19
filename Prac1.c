#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#define MAX 100 // Maximum length of the string that can be input by the user

int main() {
    char re[MAX]; // Array to store the input string
    int count = 0; // Counter to keep track of occurrences of "bb"
    bool valid = true; // mark it false if other then a's and b's are present in string

    printf("Enter your string to check for (a*bb) regular expression: ");

    // Read the input string
    scanf("%s", re);

    int length = strlen(re); // Find the length of the input string

    // Loop through each character in the string
    for (int i = 0; i < length; i++) {
        // Skip 'a' characters as they are allowed in any number
        if (re[i] != 'a') {
            // Check if the current character and the next one form "bb" then it will increment the 'count' by one'
            if(re[i]!='a' && re[i]!='b'){
                valid = false;
            }
            else if (re[i] == 'b' && re[i + 1] == 'b') {
                count++;
                valid=true;
            }
        }
        else if(re[i]!='b'){
            valid = false;
        }
    }

    // After the loop, check if the count is less than 2
    // If there is exactly one "bb" after zero or more 'a's, the string matches
    if (count < 2 && valid) {
        //printf("\nThe string (%s) matches the regular expression (a*bb).\n",re);
        printf("Valid string\n");
    } else {
        // If there are multiple "bb" occurrences, it does not match
        //printf("\nThe string (%s) does not match the regular expression (a*bb).\n",re);
        printf("Invalid string\n");
    }

    return 0;
}
