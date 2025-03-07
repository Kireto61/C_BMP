//
// Created by kikig on 2.5.2023 г..
//
#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *file;
    unsigned char header[54];
    int width, height;
    unsigned char *pixels;

    // Open BMP file for reading and writing
    file = fopen("bmp_1_indexed.bmp", "rb+");
    if (!file) {
        printf("Unable to open file\n");
        return 1;
    }

    // Read BMP header
    fread(header, sizeof(unsigned char), 54, file);

    // Get image dimensions
    width = *(int*)&header[18];
    height = *(int*)&header[22];

    // Move file pointer to beginning of pixel data
    fseek(file, *(int*)&header[10], SEEK_SET);

    // Allocate memory for pixel data
    pixels = (unsigned char*)malloc(width * height * 3);

    // Read pixel data
    fread(pixels, sizeof(unsigned char), width * height * 3, file);

    // Flip a single bit in the pixel data
    // For example, to flip the first bit in the first pixel:
    pixels[0] ^= 0x80;

    // Write modified pixel data back to file
    fseek(file, *(int*)&header[10], SEEK_SET);
    fwrite(pixels, sizeof(unsigned char), width * height * 3, file);

    // Free memory and close file
    free(pixels);
    fclose(file);

    return 0;
}