#include <cs50.h>
#include <stdio.h>
#include <math.h>

int main(void) {
    float money;
    do {
        money = get_float("Money please! ");
    } while (money < 0);

    int cents = round(money * 100); // get the total number of cents ??? i'm still unsure of the whole rounding/floats thing
    int coins = 0; // keep track of how many coins are being given to user

    while (cents >= 25) {
        cents = cents - 25;
        coins++;
    }

    while (cents >= 10) {
        cents = cents - 10;
        coins++;
    }

    while (cents >= 5) {
        cents = cents - 5;
        coins++;
    }

    while (cents >= 1) {
        cents = cents - 1;
        coins++;
    }
    printf("%i\n", coins);
}