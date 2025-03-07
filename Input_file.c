//
// Created by kikig on 4.5.2023 г..
//
#include "structs.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
///prochitane na bmp i dib
void input_bmp_Dib(FILE *f, struct BMP *bmp, struct DIB *dib) {
    fread(&(*bmp).filetype, 1, 2, f);


    if ((*bmp).filetype[0] != 'B' && (*bmp).filetype[1] != 'M') {
        printf("Greshen format");
        exit(1);
    }


    fread(&(*bmp).filesize, 4, 1, f);
    printf("Value is %d\n", (*bmp).filesize);

    fseek(f, 4, SEEK_CUR);

    fread(&(*bmp).dataoffset, 4, 1, f);
    printf("Offset is %d\n", (*bmp).dataoffset);


    //   fwrite(&bmp, sizeof(bmp), 1, f1);


    fread(&(*dib).fileheader, 4, 1, f);
    printf("File header is %d bytes\n", (*dib).fileheader);

    //if (dib.fileheader != 40) {
//    printf("Greshen format");
//   exit(-1);
//}

    fread(&(*dib).width, 4, 1, f);
    printf("Width is %d\n", (*dib).width);

    fread(&(*dib).height, 4, 1, f);
    printf("Height is %d\n", (*dib).height);

    fread(&(*dib).planes, 2, 1, f);
    printf("Color planes is %d\n", (*dib).planes);


    fread(&(*dib).bitsperpixel, 2, 1, f);
    printf("Pixels per bit is %d\n", (*dib).bitsperpixel);

    fread(&(*dib).compression, 4, 1, f);
    printf("Compression scheme used is %d\n", (*dib).compression);

    fread(&(*dib).bitmapsize, 4, 1, f);
    printf("Image size is %d\n", (*dib).bitmapsize);

    fread(&(*dib).horizontalres, 4, 1, f);
    printf("Horizontal resolution is %d\n", (*dib).horizontalres);

    fread(&(*dib).verticalres, 4, 1, f);
    printf("Vertical resolution is %d\n", (*dib).verticalres);

    fread(&(*dib).numcolors, 4, 1, f);
    printf("Number of colors used %d\n", (*dib).numcolors);

    fread(&(*dib).importantcolors, 4, 1, f);
    printf("Important colors used %d\n", (*dib).importantcolors);
}
///prochitane na 24bita na pixel
void read_pixel_24bit(FILE *f, struct BMP *bmp, struct DIB *dib, PIXEL_24 *pixels) {
    fseek(f, (*bmp).dataoffset, SEEK_SET);
    unsigned char pading = (4 - (((int) ceil((dib->width * 3.0))) % 4)) % 4;
    for (int i = 0; i < dib->height; i++) {
        for (int j = 0; j < dib->width; j++) {
            // Blue
            fread(&pixels[i * dib->width + j].b, 1, 1, f);
            // Green
            fread(&pixels[i * dib->width + j].g, 1, 1, f);
            // Red
            fread(&pixels[i * dib->width + j].r, 1, 1, f);
        }
        fseek(f, pading, SEEK_CUR);
    }
}
///prochitane na 16bita na pixel
void read_pixel_16bit(FILE *f1, struct BMP *bmp, struct DIB *dib, PIXEL_16 *pixels) {
    fseek(f1, (*bmp).dataoffset, SEEK_SET);
    unsigned char pading = (4 - ((int) ceil((dib->width * 2.0))) % 4) % 4;
    for (int i = 0; i < dib->height; i++) {
        for (int j = 0; j < dib->width; j++) {
            // Blue
            fread(&pixels[i * dib->width + j].b_g, 1, 1, f1);
            // Green
            fread(&pixels[i * dib->width + j].a_r, 1, 1, f1);
        }
        fseek(f1, pading, SEEK_CUR);

    }
}


///prochitane na 8bita na pixel
void read_pixel_8bit(FILE *f1, struct BMP *bmp, struct DIB *dib, PIXEL_8 *pixels) {
    fseek(f1, (*bmp).dataoffset, SEEK_SET);
    unsigned char pading = (4 - ((int) ceil((dib->width / 1.0))) % 4) % 4;
    int pixelSize = (*dib).height * (*dib).width;
    for (int i = 0; i < dib->height; i++) {
        for (int j = 0; j < dib->width; j++) {
            fread(&pixels[i * dib->width + j].color, 1, 1, f1);
        }
        fseek(f1, pading, SEEK_CUR);
    }
}
///prochitane na 4bita na pixel
void read_pixel_4bit(FILE *f1, struct BMP *bmp, struct DIB *dib, PIXEL_4 *pixels) {
    fseek(f1, (*bmp).dataoffset, SEEK_SET);
    unsigned char pading = (4 - ((int) ceil((dib->width / 2.0))) % 4) % 4;
    for (int i = 0; i < dib->height; i++) {
        for (int j = 0; j < (int) ceil(dib->width / 2.0); j++) {
            fread(&pixels[i * dib->width + j].color, 1, 1, f1);
        }
        fseek(f1, pading, SEEK_CUR);
    }
}
///prochitane na 2bita na pixel
void read_pixel_2bit(FILE *f1, struct BMP *bmp, struct DIB *dib, PIXEL_2 *pixels) {
    fseek(f1, (*bmp).dataoffset, SEEK_SET);
    unsigned char pading = (4 - ((int) ceil((dib->width / 4.0))) % 4) % 4;
    for (int i = 0; i < dib->height; i++) {
        unsigned char d = 0;
        for (int j = 0; j < (int) ceil(dib->width / 4.0); j++) {
            fread(&d, 1, 1, f1);
            pixels[i * dib->width + j].color = d;

        }
        fseek(f1, pading, SEEK_CUR);

    }
}
///prochitane na 1bit na pixel
void read_pixel_1bit(FILE *f1, struct BMP *bmp, struct DIB *dib, PIXEL_1 *pixels) {
    fseek(f1, (*bmp).dataoffset, SEEK_SET);
    unsigned char pading = (4 - ((int) ceil((dib->width / 8.0))) % 4) % 4;

    for (int i = 0; i < dib->height; i++) {
        unsigned char d = 0;
        for (int j = 0; j < (int) ceil(dib->width / 8.0); j++) {
            fread(&d, 1, 1, f1);
            pixels[i * dib->width + j].color = d;

        }
        fseek(f1, pading, SEEK_CUR);

    }
}

