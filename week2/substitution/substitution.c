#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

bool lettersOnly(string);
bool duplicateFound(string);
string keySameCase(string);
string cipherText(string, string);

int main(int argc, string argv[]) {
    if (argc != 2) {
        printf ("Usage: ./substituion key\n");
        return 1;
    } else if (lettersOnly(argv[1]) != true) {
        printf ("Usage: ./substituion key\n");
        return 1;
    } else if (strlen(argv[1]) != 26) {
        printf ("Key must contain 26 characters.\n");
        return 1;
    } else if (duplicateFound(argv[1]) != true) {
        printf ("Key must not contain repeated characters.\n");
        return 1;
    }

    string key = (argv[1]);
    keySameCase(key);
    string plainText = get_string("plaintext: ");
    cipherText(key, plainText);
    printf("ciphertext: %s\n", plainText);
    return 0;
}


bool lettersOnly(string x) {
    for (int i = 0; i <strlen(x); i++) {
        if (isalpha(x[i]) == 0) {
            return false;
        }
    }
    return true;
}

// through this, i was able to get a better grasp of what a nested for loop is exactly doing
// also, learned how to get to the solution with and without calling a function (there's always more ways than one!)
bool duplicateFound(string x) {
    int length = strlen(x);
    for (int i = 0; i < length; i++) {
        for (int j = i + 1; j < length; j++) {
            // if ((x[i] - x[j] == 32) || (x[i] - x[j] == -32)) { // the difference between a lower case and upper case letter of the same letter (eg, 'a' and 'A')
            if (toupper(x[i]) == toupper(x[j])) {
                return false;
            }
        }
    }
    return true;
}

string keySameCase (string x) {
    for (int i = 0; i <strlen(x); i++) {
        x[i] = tolower(x[i]);
    }
    return x;
}

// string x = key, string y = plainText
string cipherText(string x, string y) {
    for (int i = 0; i < strlen(y); i++) {
        int a = y[i] - 'a'; //int a and int b to set a "pointer" of where in the alphabet we are in the key
        int b = y[i] - 'A';
        if (islower(y[i])) {
            y[i] = ((x[a] - 'a') % 26) + 'a'; // change the char in plainText to the char in key
        } else if (isupper(y[i])) {
            char d = toupper(x[b]); // make char in key an uppercase
            char c = ((d - 'A') % 26) +'A';
            y[i] = toupper(c);
        }
    }
    return y;
    return 0;
}
