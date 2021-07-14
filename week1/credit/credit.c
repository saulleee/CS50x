#include <stdio.h>
#include <cs50.h>

int checkSum(long ccNumber);
bool isVISA(int ccDigits, long ccNumber);
bool isAMEX(int ccDigits, long ccNumber);
bool isMASTERCARD(int ccDigits, long ccNumber);

int main(void) {
    long ccNumber;
    do {
        ccNumber = get_long("Credit card number, please! ");
    } while (ccNumber < 0);

    if (checkSum(ccNumber) % 10 != 0) { // because <sum> needs to end in 0, and if it does, i want the program to keep running, otherwise, see a couple lines below (basically, it's the first gate)
        printf("INVALID\n");
        return 0; // this is making the program stop altogether
    }

    int ccDigits;
    long ccNumber2 = ccNumber;
    for (ccDigits = 1; ccNumber2 /= 10; ccDigits++); // assign ccDigits the total number of digits in ccNumber (but reassigned to ccNumber2 so i don't mess ccNumber up) -- in other words, i need ccNumber as a value, not a reference

    if (isVISA(ccDigits, ccNumber)) {
        printf("VISA\n");
    } else if (isMASTERCARD(ccDigits, ccNumber)) {
        printf("MASTERCARD\n");
    } else if (isAMEX(ccDigits, ccNumber)) {
        printf("AMEX\n");
    } else {
        printf("INVALID\n");
    }
}

// Custom functions below

int checkSum(long ccNumber) {
    int sum = 0;
    int a, x, y, z;
    while (ccNumber > 0) {
        a = ccNumber % 10; // assign <a> the last digit of <checkSum>
        sum += a; // add that number to <sum>
        ccNumber = ccNumber / 10; // assign <checkSum> as all the digits except the last digit
        x = ccNumber % 10; // assign <x> as the the last digit of <checkSum>
        x = x * 2; // assign <x> as <x> multiplied by 2
        y = x % 10; // assign <y> as the second digit of <x> (for two-digit numbers)
        z = x / 10; // assign <z> as the first digit of <x> (for two-digit numbers)
        sum += y + z; // assign <sum> as the sum of <sum>, <y>, <z>
        ccNumber = ccNumber / 10; // assign <checkSum> as all the digits except the last digit
    }
    return sum;
}

bool isAMEX(int ccDigits, long ccNumber) {
    if (ccDigits != 15) {
        return false;
    }
    ccNumber /= 10000000000000; // EDIT: fixed // FYI, if i just get rid of reassigning of ccNumber, it messes it up as a reference (but i assumed it'd be a value???)
    return (ccNumber == 34 || ccNumber == 37);
}

bool isMASTERCARD(int ccDigits, long ccNumber) {
    if (ccDigits != 16) {
        return false;
    }
    int a = ccNumber / 100000000000000;
    return (a >= 51 && a <= 55);
}

bool isVISA(int ccDigits, long ccNumber) {
    if (ccDigits !=16) {
        if (ccDigits != 13) {
            return false; // basically, if it's not 16, and then if it's not 13, THEN return false--otherwise, keep going, because at that point it HAS TO BE either 16 or 13
        }
        int a = ccNumber / 1000000000000;
        return (a == 4);
    }
    int a = ccNumber / 1000000000000000;
    return (a == 4);
}


/*
EVOLUTION OF WORKING OUT THE LATTER HALF OF THE PROBLEM SET AND MAKING CUSTOM FUNCTIONS

EDIT: worked on these issues with chi

// up until here everything works fine
// the code above, i've checked by making it printf ccDigits
// the code below doesn't work because ccDigits is undefined ??? but why, if it's defined above???
// and then the code below, the compiler DOES NOT like the use of the || ???

    // STEP 3: check for ccNumber starting-digit number
    int ccDigits15;
    int ccDigits16;
    int ccDigits13;

    while (ccDigits == 15) {
        ccDigits15 = ccNumber / 1000000000000; // because i'm trying to grab only the first two digits of <ccNumber>
    }

    if (ccDigits15 == 34 || ccDigits15 == 37) {
        printf("AMEX\n");
    } else {
        printf("INVALID\n");
    }

    while (ccDigits == 16) {
        ccDigits16 = ccNumber / 10000000000000;
    }

    if (ccDigits16 >= 51 && ccDigits16 <= 55) {
        printf("MASTERCARD\n");
    } else {
        printf("INVALID\n");
    }

    // how do i accommodate the extra number that needs to get cut in line 73, since this Visa card's first digit is 4 (as opposed to the MC above, that's a double-digit number)
    while (ccDigits == 16) {
        ccDigits16 = ccNumber / 100000000000000;
    }

    if (ccDigits16 == 4) {
        printf("VISA\n");
    } else {
        printf("INVALID\n");
    }

    while (ccDigits == 13) {
        ccDigits13 = ccNumber / 100000000000;
    }

    if (ccDigits13 == 4) {
        printf("VISA\n");
    } else {
        printf("INVALID\n");
    }


EDIT: worked on this block to make these into separate functions instead
    int ccDigits15;
    int ccDigits16;
    int ccDigits13;
    if (ccDigits == 15) {
        ccDigits15 = ccNumber / 10000000000000;  // because i'm trying to grab only the first two digits of <ccNumber>
        if (ccDigits15 == 34 || ccDigits15 == 37) {
            printf("AMEX\n");
        } else {
            printf("INVALID\n");
        }


    } else if (ccDigits == 16) {
        ccDigits16 = ccNumber / 100000000000000; {
            if (ccDigits16 >= 51 && ccDigits16 <= 55) {
                printf("MASTERCARD\n");
            } else if (ccDigits16 / 10 == 4) {
                printf("VISA\n");
            } else {
                printf("INVALID\n");
            }
        }

    } else if (ccDigits == 13) {
        ccDigits13 = ccNumber / 1000000000000; {
            if (ccDigits13 == 4) {
                printf("VISA\n");
            } else {
                printf("INVALID\n");
            }
        }


    } else if (ccDigits != 15 && ccDigits != 16 && ccDigits != 13) {
        printf("INVALID\n");
    }


    } else { // for <sum> that don't end in 0
        printf("INVALID\n");
    }


EDIT: initial drafts of custom functions, which got made more efficient and finalized in main

bool isVISA(int ccDigits, long ccNumber) {
    int a;
    if (ccDigits == 16) {
        a = ccNumber / 1000000000000000;
        if (a == 4) {
            return true;
        } else {
            return false;
        }
    } else if (ccDigits == 13) {
        a = ccNumber / 1000000000000;
        if (a == 4) {
            return true;
        } else {
            return false;
        }
    } else {
        return false;
    }
}

bool isMASTERCARD(int ccDigits, long ccNumber) {
    int a;
    if (ccDigits == 16) {
        a = ccNumber / 100000000000000;
        if (a >= 51 && a <= 55) {
            return true;
        } else {
            return false;
        }
    } else {
        return false;
    }
}

*/