// Modifies the volume of an audio file

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// Number of bytes in .wav header
const int HEADER_SIZE = 44;

int main(int argc, char *argv[])
{
    // Check command-line arguments
    if (argc != 4)
    {
        printf("Usage: ./volume input.wav output.wav factor\n");
        return 1;
    }

    // Open files and determine scaling factor
    FILE *input = fopen(argv[1], "r");
    if (input == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    FILE *output = fopen(argv[2], "w");
    if (output == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    float factor = atof(argv[3]);

    // TODO: Copy header from input file to output file
    // "inputArray" is basically a temp storing place to write into from "input"
    // then copy that into "output"
    uint8_t *inputArrayHeader = malloc(sizeof(uint8_t) * 44);
    fread(inputArrayHeader, sizeof(uint8_t), 44, input);
    fwrite(inputArrayHeader, sizeof(uint8_t), 44, output);
    free(inputArrayHeader);

    // TODO: Read samples from input file and write updated data to output file
    int16_t *inputArraySamples = malloc(sizeof(int16_t));
    while (fread(inputArraySamples, sizeof(int16_t), 1, input)) {
        *inputArraySamples *= factor;
        fwrite(inputArraySamples, sizeof(int16_t), 1, output);
    }
    free(inputArraySamples);

    // Close files
    fclose(input);
    fclose(output);
}