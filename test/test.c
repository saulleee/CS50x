#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <stdlib.h>

// recursion
//
// void draw(int h)
// {
//     if (h == 0) {
//         return;
//     }

//     draw(h - 1);

//     for (int i = 0; i < h; i++) {
//         printf("#");
//     }

//     printf("\n");
// }

// #include <stdio.h>

// int main(void)
// {
//   int answer, i;
//   int right, wrong;

//   right = 0;
//   wrong = 0;

//   for( i = 1; i < 11; i = i + 1) {
//     printf("What is %d + %d? ", i, i);
//     scanf("%d", &answer);

//     if(answer == i + i) {
//       printf("Right!  \n");
//       right++;
//     }
//   }
//   printf("You got %d right and %d wrong.\n", right, wrong);

//   return 0;
// }

// make each index in the array the average of that index and the index before it and after it
int main(void) {
    int arr[] = {0, 10, 25, 35, 45};
    int sizeOfArray = sizeof(arr)/sizeof(*arr);

    for (int i = 0; i < sizeOfArray; i++) {
        int count = 1;
        if (i > 0) {
            arr[i] += arr[i - 1];
            count++;
        }

        if (i < sizeOfArray - 1) {
            arr[i] += arr[i + 1];
            count++;
        }

        arr[i] = arr[i] / count;
    }
    for (int i = 0; i < sizeOfArray; i++) {
        printf("%i\n", arr[i]);
    }
}

// a version of the code above, but where there's another for loop that takes a block of the array
// int main(void) {
//     int arr[] = {0, 10, 25, 35, 45};
//     int sizeOfArray = sizeof(arr)/sizeof(*arr);

//     for (int i = 0; i < sizeOfArray; i++) {
//         int temp = 0;
//         int counter = 0;
//         for (int iSub = i - 1; iSub <= i + 1; iSub++) {
//             if (iSub >= 0 && iSub <= sizeOfArray - 1) { // range is 0 to 4
//                 temp += arr[iSub];
//                 counter++;
//             }
//         }
//         arr[i] = temp / counter;
//     }
//     for (int i = 0; i < sizeOfArray; i++) {
//         printf("%i\n", arr[i]);
//     }
// }

// 5 / 13 / 24 / 34 / 39

// 0 1 2 3 4
// if i can take the left number, add it
// if i can take the right number, add it
// then average it out