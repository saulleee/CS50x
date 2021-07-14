#include <cs50.h>
#include <stdio.h>

int main(void) {
    int bricks;
    do {
        bricks = get_int("How high does the pyramid go? ");
    } while (bricks < 1 || bricks > 8);

    for (int row = 0; row < bricks; row++) { // counter for var row
        int totalSpaces = bricks - row; // totalSpaces meaning just ... the total number of spaces that ROW will have
        for (int spaces = 1; spaces < totalSpaces; spaces++) {
            printf(" "); // to print a ' ' minus at least one, since the first row will always have one '#'
        }

        for (int pound = 0; pound <= row ; pound++) {
            printf("#"); // to print a '#' check if pound is <= row (when you start, row is at 0, so if pound is also at 0, then the iteration of pound++ !true)
        }
        printf("\n");
    }
}

/*#include <cs50.h>
#include <stdio.h>

int main(void) {
    int bricks;
    do {
        bricks = get_int("How high does the pyramid go? ");
    } while (bricks < 1 || bricks > 8);

    for (int i = 0; i < bricks; i++) {
        for (int j = 0; j <= i; j++) {
            printf("#");
        }
        printf("\n");
    }
}*/

// make a whole block of code a comment with "ctrl + shift + /"