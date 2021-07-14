#include <cs50.h>
#include <stdio.h>

int main(void) {
    int bricks;
    do {
        bricks = get_int("How high does the pyramid go? ");
    } while (bricks < 1 || bricks > 8);

    for (int row = 0; row < bricks; row++) {
        int totalSpaces = bricks - row;
        for (int spaces = 1; spaces < totalSpaces; spaces++) {
            printf(" ");
        }

        for (int hash1 = 0; hash1 <= row; hash1++) {
            printf("#");
        }

        printf("  ");

        for (int hash2 = 0; hash2 <= row; hash2++) {
            printf("#");
        }
        printf("\n");
    }
}