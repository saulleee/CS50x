#include <cs50.h>
#include <stdio.h>

int main(void) {
    int n;
    do {
        n = get_int("How many llamas to start? ");
    } while (n < 9);

    int o;
    do {
        o = get_int("How many llamas at the end? ");
    } while (o < n);

    int years = 0;
    while (n < o) {
        n = n + (n / 3) - (n / 4);
        years++;
    }

    printf("Years: %i\n", years);
}

// this is the way chi says is good--but why? he didn't even check style50 though