#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

string cipherText(string, int);

int main(int argc, string argv[]) {
    if (argc != 2) {
        printf ("Usage: ./caesar key\n");
        return 1;
    }

    for (int i = 0, n = strlen(argv[1]); i < n; i++) {
        if (argv[1][i] < '0' || argv[1][i] > '9') {
            printf ("Usage: ./caesar key\n");
            return 1;
        }
    }

    int k = atoi(argv[1]);

    string plainText = get_string("plaintext: ");

    cipherText(plainText, k);

    printf("ciphertext: %s\n", plainText);

    return 0;
}

// thanks, @yakumo ... "So the calculation would be: 122 - 97 (a) = 25 -> 25 + 2 = 27 -> 27 % 26 = 1 -> 1 + 97 (a) = 98 (b)"
string cipherText(string x, int y) {
    for (int i = 0, n = strlen(x); i < n; i++) {
        if (isupper(x[i])) {
            x[i] = (((x[i] - 'A') + y) % 26) + 'A';
        } else if (islower(x[i])) {
            x[i] = (((x[i] - 'a') + y) % 26) + 'a';
        }
    }
    return x;
}

/*
// EDIT: the function below ultimately became the block in lines 33ff
// honestly, idk what is actually goin on here. i sort of mishmashed things until it worked.
// lines 38 and 41 need to exist because if the key brings the sum beyond 122 (ie 'Z'), then the whole formula needs to be treated differently than if the sum is between 97 and 122 (ie, 'A' and 'Z')
// so if the sum is less than 122, then line 41 says to get the sum, which is between 0 and 26, and add that to the constant 97, ie 'A'
// but if the sum is greater than 122, then you need to get the mod of 122 (by subtracting 'Z')

string cipherText(string x, int y) {
    for (int i = 0, n = strlen(x); i < n; i++) {
        if (isupper(x[i])) {
            if ((x[i] + (y % 26)) <= 'Z') {
                x[i] = ((x[i] + (y % 26)) % 'A') + 'A';
            } else if ((x[i] + (y % 26)) >= 'Z') {
                x[i] = ((x[i] + (y % 26)) % 'Z') + ('A' - 1);
            }
        } else if (islower(x[i])) {
            if ((x[i] + (y % 26)) <= 'z') {
                x[i] = ((x[i] + (y % 26)) % 'a') + 'a';
            } else if ((x[i] + (y % 26)) >= 'z') {
                x[i] = ((x[i] + (y % 26)) % 'z') + ('a' - 1);
            }
        }
    }
    return x;
}
*/

/*
// can i use this function instead of the block of code above?
int argvCheck(string argv) {
    if (argc != 2) {
        printf ("Usage: ./caesar key\n");
        return 1;
    }

    for (int i = 0, n = strlen(argv[1]); i < n; i++) {
        if (argv[1][i] < '0' || argv[1][i] > '9') {
            printf ("Usage: ./caesar key\n");
            return 1;
        }
    }

    return 0;
}
*/
