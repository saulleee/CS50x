#include "helpers.h"
#include "math.h"

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width]) {
    for (int h = 0; h < height; h++) {
        for (int w = 0; w < width; w++) {
            float r, g, b, avg;
            r = image[h][w].rgbtRed;
            g = image[h][w].rgbtGreen;
            b = image[h][w].rgbtBlue;
            avg = (r + b + g) / 3;
            image[h][w].rgbtRed = round(avg);
            image[h][w].rgbtGreen = round(avg);
            image[h][w].rgbtBlue = round(avg);
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width]) {
    for (int h = 0; h < height; h++) {
        for (int w = 0; w < width; w++) {
            float sepiaRed = .393 * image[h][w].rgbtRed + .769 * image[h][w].rgbtGreen + .189 * image[h][w].rgbtBlue;
            if (sepiaRed > 255) {
                sepiaRed = 255;
            }
            float sepiaGreen = .349 * image[h][w].rgbtRed + .686 * image[h][w].rgbtGreen + .168 * image[h][w].rgbtBlue;
            if (sepiaGreen > 255) {
                sepiaGreen = 255;
            }
            float sepiaBlue = .272 * image[h][w].rgbtRed + .534 * image[h][w].rgbtGreen + .131 * image[h][w].rgbtBlue;
            if (sepiaBlue > 255) {
                sepiaBlue = 255;
            }
            image[h][w].rgbtRed = round(sepiaRed);
            image[h][w].rgbtGreen = round(sepiaGreen);
            image[h][w].rgbtBlue = round(sepiaBlue);
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width]) {
    for (int h = 0; h < height; h++) {
        for (int w = 0; w < width / 2; w++) {
            RGBTRIPLE temp;
            temp = image[h][w];
            image[h][w] = image[h][width - w - 1];
            image[h][width - w - 1] = temp;
        }
    }
    return;
}

// first draft of what i attempted for REFLECT
// void reflect(int height, int width, RGBTRIPLE image[height][width]) {
//     for (int h = 0; h < height; h++) {
//         RGBTRIPLE tempArray[height][width];
//         for (int w = 0; w < width; w++) {
//             tempArray[h][w] = image[h][w];
//         }
//         int i = 1;
//         for (int w = 0; w < width; w++) {
//             image[h][w] = tempArray[h][width - i];
//             i++;
//         }
//     }
//     return;
// }

/// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width]) {
    RGBTRIPLE imageCopy[height][width];
    for (int h = 0; h < height; h++) {
        for (int w = 0; w < width; w++) {
            imageCopy[h][w] = image[h][w];
        }
    }
    for (int h = 0; h < height; h++) {
        for (int w = 0; w < width; w++) {

            float counter = 1.0;
            // so i had to add below. before, i didn't have sumX and instead was directly manipulating image[h][w].r/g/b, but that wasn't working. why???
            // because before i was manipulating the actual BYTE value, not storing its RGB int value (like i wanted)
            int sumRed = image[h][w].rgbtRed;
            int sumGreen = image[h][w].rgbtGreen;
            int sumBlue = image[h][w].rgbtBlue;

            if (h - 1 >= 0 && w - 1 >= 0) { // top left corner
                sumRed += imageCopy[h - 1][w - 1].rgbtRed;
                sumGreen += imageCopy[h - 1][w - 1].rgbtGreen;
                sumBlue += imageCopy[h - 1][w - 1].rgbtBlue;
                counter++;
            }
            /*
            what i was doing before:
            if (h - 1 >= 0 && w - 1 >= 0) { // top left corner
                image[h][w].rgbtRed += imageCopy[h - 1][w - 1].rgbtRed;
                image[h][w].rgbtGreen += imageCopy[h - 1][w - 1].rgbtGreen;
                image[h][w].rgbtBlue += imageCopy[h - 1][w - 1].rgbtBlue;
                counter++;
            }
            */
            if (h - 1 >= 0) { // top side
                sumRed += imageCopy[h - 1][w].rgbtRed;
                sumGreen += imageCopy[h - 1][w].rgbtGreen;
                sumBlue += imageCopy[h - 1][w].rgbtBlue;
                counter++;
            }
            if (h - 1 >= 0 && w + 1 < width) { // top right corner
                sumRed += imageCopy[h - 1][w + 1].rgbtRed;
                sumGreen += imageCopy[h - 1][w + 1].rgbtGreen;
                sumBlue += imageCopy[h - 1][w + 1].rgbtBlue;
                counter++;
            }
            if (w - 1 >= 0) { // left side
                sumRed += imageCopy[h][w - 1].rgbtRed;
                sumGreen += imageCopy[h][w - 1].rgbtGreen;
                sumBlue += imageCopy[h][w - 1].rgbtBlue;
                counter++;
            }
            if (w + 1 < width) { // right side
                sumRed += imageCopy[h][w + 1].rgbtRed;
                sumGreen += imageCopy[h][w + 1].rgbtGreen;
                sumBlue += imageCopy[h][w + 1].rgbtBlue;
                counter++;
            }
            if (h + 1 < height && w - 1 >= 0) { // bottom left corner
                sumRed += imageCopy[h + 1][w - 1].rgbtRed;
                sumGreen += imageCopy[h + 1][w - 1].rgbtGreen;
                sumBlue += imageCopy[h + 1][w - 1].rgbtBlue;
                counter++;
            }
            if (h + 1 < height) { // bottom side
                sumRed += imageCopy[h + 1][w].rgbtRed;
                sumGreen += imageCopy[h + 1][w].rgbtGreen;
                sumBlue += imageCopy[h + 1][w].rgbtBlue;
                counter++;
            }
            if (h + 1 < height && w + 1 < width) { // bottom right corner
                sumRed += imageCopy[h + 1][w + 1].rgbtRed;
                sumGreen += imageCopy[h + 1][w + 1].rgbtGreen;
                sumBlue += imageCopy[h + 1][w + 1].rgbtBlue;
                counter++;
            }
            image[h][w].rgbtRed = round(sumRed / counter);
            image[h][w].rgbtGreen = round(sumGreen / counter);
            image[h][w].rgbtBlue = round(sumBlue / counter);
        }
    }
    return;
}

/*
3x3 grid
[-1,-1] [-1,0] [-1,1] [-1,2] [-1,3]
[0,-1]  [0,0]  [0,1]  [0,2]  [0,3]
[1,-1]  [1,0]  [1,1]  [1,2]  [1,3]
[2,-1]  [2,0]  [2,1]  [2,2]  [2,3]
[3,-1]  [3,0]  [3,1]  [3,2]  [3,3]

upper left corner
[-1,-1] [-1,0] [-1,1]
[0,-1]  [0,0]  [0,1]
[-1,1]  [1,0]  [1,1]

upper right corner
[-1,1] [-1,2] [-1,3]
[0,1]  [0,2]  [0,3]
[1,1]  [1,2]  [1,3]

lower left corner
[1,-1] [1,0] [1,1]
[2,-1] [2,0] [2,1]
[3,-1] [3,0] [3,1]

lower right corner
[1,1] [1,2] [1,3]
[2,1] [2,2] [2,3]
[3,1] [3,2] [3,3]

top side
[-1,0] [-1,1] [-1,1]
[0,0]  [0,1]  [0,2]
[1,0]  [1,1]  [1,2]

bottom side
[1,0] [1,1] [1,2]
[2,0] [2,1] [2,2]
[3,0] [3,1] [3,2]

left side
[0,-1] [0,0] [0,1]
[1,-1] [1,0] [1,1]
[2,-1] [2,0] [2,1]

right side
[0,1] [0,2] [0,3]
[1,0] [1,2] [1,3]
[2,0] [2,2] [2,3]
*/

// draft of what i was working on for BLUR
// void blur(int height, int width, RGBTRIPLE image[height][width]) {
//     RGBTRIPLE imageCopy[height][width];
//     for (int h = 0; h < height; h++) {
//         for (int w = 0; w < width; w++) {
//             imageCopy[h][w] = image[h][w];
//         }
//     }
//     // normal iteration through 2d array
//     for (int h = 0; h < height; h++) {
//         for (int w = 0; w < width; w++) {
//             int counter = 0;
//             RGBTRIPLE temp;
//             // "3x3 grid" iteration around [h][w]
//             for (int hSub = h - 1; hSub <= h + 1; hSub++) {
//                 for (int wSub = w - 1; wSub <= w + 1; wSub++) {
//                     // what i assume is all the conditions for being within bounds of [h][w]
//                     if (hSub >= 0 && wSub >= 0 && hSub <= height - 1 && wSub <= width - 1) {
//                         // i need to figure out how to get "x" to be temporary storage for the accumulated values of R, G, B
//                         temp.rgbtRed += imageCopy[hSub][wSub].rgbtRed;
//                         temp.rgbtGreen += imageCopy[hSub][wSub].rgbtGreen;
//                         temp.rgbtBlue += imageCopy[hSub][wSub].rgbtBlue;
//                         counter++;
//                     }
//                 }
//             }
//             image[h][w].rgbtRed = round(temp.rgbtRed / counter);
//             image[h][w].rgbtGreen = round(temp.rgbtGreen / counter);
//             image[h][w].rgbtBlue = round(temp.rgbtBlue / counter);
//         }
//     }
//     return;
// }