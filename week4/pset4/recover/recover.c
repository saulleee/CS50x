#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef uint8_t BYTE;

int main(int argc, char *argv[]) {

    if (argc != 2) {
        printf("Usage: ./recover <file>\n");
        return 1;
    }

    FILE *memCard = fopen(argv[1], "r");
//    if (!argv[1]) {
    if (memCard == NULL) {
        printf("NULL\n");
        return 2;
    }

/*
    BYTE *buffer = malloc(sizeof(BYTE) * 512);
    if (!(sizeof(BYTE) * 512)) {
        return 2;
        printf("NULL\n");
    }
*/

    BYTE buffer[512];
    int jpegsFound = 0;
    char fileName[8];
    FILE *img = NULL;

    while (fread(buffer, 512, 1, memCard) == 1) {
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0) {
            if (jpegsFound == 0) {
                sprintf (fileName, "%03i.jpg", jpegsFound);
                jpegsFound++;
                img = fopen(fileName, "w");
                fwrite (buffer, 512, 1, img);
            }
            else { // if (jpegsFound > 0) {
                fclose(img);
                sprintf (fileName, "%03i.jpg", jpegsFound);
                jpegsFound++;
                img = fopen(fileName, "w");
                fwrite (buffer, 512, 1, img);
            }
        }
        else if (img != NULL) {
            fwrite (buffer, 512, 1, img);
        }
    }
    fclose(img);
    fclose(memCard);
    return 0;
}