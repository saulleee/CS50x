#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

int countLetters(string);
int countWords(string);
int countSents(string);
int indexFormula(int, int, int);
void readingLevel(int);

int main(void) {
    string inputTxt = get_string("Text: ");

    int countedLetters = countLetters(inputTxt);

    int countedWords = countWords(inputTxt);

    int countedSents = countSents(inputTxt);

    int indexNumber = indexFormula(countedLetters, countedWords, countedSents);

    // printf("Number of letters: %i\n", countedLetters);

    // printf("Number of words: %i\n", countedWords);

    // printf("Number of sentences: %i\n", countedSents);

    // printf("Your reading level: %i\n", indexNumber);
    readingLevel(indexNumber);

}

int countLetters(string a) {
    int counter = 0;

    for(int i = 0, n = strlen(a); i < n; i++) {
        if (isupper(a[i])) {
            counter++;
        } else if (islower(a[i])) {
            counter++;
        }
    }

    return counter;
}

int countWords(string a) {
    int counter = 0;

    for (int i = 0, n = strlen(a); i < n; i++) {
        if (a[i] == ' ') {
            counter++;
        } else if (i == 1) { // doing this was a happy accident O_O
            counter++;
        }
    }

    return counter;
}

int countSents(string a) {
    int counter = 0;

    for (int i = 0, n = strlen(a); i < n; i++) {
        if (a[i] == '.' || a[i] == '!' || a[i] == '?') {
            counter++;
        }
    }

    return counter;
}

int indexFormula(int a, int b, int c) {
    float L = ((float)a / b) * 100;
    float S = ((float)c / b) * 100;
    float x = 0.0588 * L - 0.296 * S - 15.8; // still confused on casting here from floats to ints
    int z = round(x);
    return z;
}

void readingLevel(int a) {
    if (a < 1) {
        printf("Before Grade 1\n");
    } else if (a > 16) {
        printf("Grade 16+\n");
    } else {
        printf("Grade %i\n", a);
    }
}