//
// Created by kikig on 4.5.2023 г..
//

#ifndef UNTITLED_OUTPUT_FILE_H
#define UNTITLED_OUTPUT_FILE_H


#include <stdio.h>
#include "structs.h"

void copy_file(FILE *f, FILE *f1);

void flip_1bits(DIB *dib, PIXEL_1 *pixels);

void rotate_1bits(DIB *dib, PIXEL_1 *pixels);

void invert_1bits(DIB *dib, PIXEL_1 *pixels);

void write_1bit(BMP *bmp, DIB *dib, PIXEL_1 *pixels, FILE *f1);

void flip_2bits(DIB *dib, PIXEL_2 *pixels);

void rotate_2bits(DIB *dib, PIXEL_2 *pixels);

void invert_2bits(DIB *dib, PIXEL_2 *pixels);

void write_2bit(BMP *bmp, DIB *dib, PIXEL_2 *pixels, FILE *f1);

void flip_4bits(DIB *dib, PIXEL_4 *pixels);

void rotate_4bits(DIB *dib, PIXEL_4 *pixels);

void invert_4bits(DIB *dib, PIXEL_4 *pixels);

void write_4bit(BMP *bmp, DIB *dib, PIXEL_4 *pixels, FILE *f1);

void flip_8bits(DIB *dib, PIXEL_8 *pixels);

void rotate_8bits(DIB *dib, PIXEL_8 *pixels);

void invert_8bits(DIB *dib, PIXEL_8 *pixels);

void write_8bit(BMP *bmp, DIB *dib, PIXEL_8 *pixels, FILE *f1);

void flip_16bits(DIB *dib, PIXEL_16 *pixels);

void rotate_16bits(DIB *dib, PIXEL_16 *pixels);

void invert_16bits(DIB *dib, PIXEL_16 *pixels);

void write_16bit(BMP *bmp, DIB *dib, PIXEL_16 *pixels, FILE *f1);

void flip_24bits(DIB *dib, PIXEL_24 *pixels);

void rotate_24bits(DIB *dib, PIXEL_24 *pixels);

void invert_24bits(DIB *dib, PIXEL_24 *pixels);

void write_24bit(BMP *bmp, DIB *dib, PIXEL_24 *pixels, FILE *f1);


#endif //UNTITLED_OUTPUT_FILE_H
