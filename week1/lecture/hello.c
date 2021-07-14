#include <cs50.h>
#include <stdio.h>

int main(void)
{
    string answer = get_string("What's your name? ");
    printf("hello, %s\n", answer);
    // the ", answer" is there because %s is grabbing that argument
}

// in the terminal window, what I learned: "make hello" "help50 make hello" "style50 hello.c" "check50 ..."