//
// Created by kikig on 4.5.2023 г..
//

#ifndef UNTITLED_INPUT_FILE_H
#define UNTITLED_INPUT_FILE_H

#include <stdio.h>
#include <stdlib.h>
#include "structs.h"


void input_bmp_Dib(FILE *f, BMP *bmp, DIB *dib);

void read_pixel_1bit(FILE *f1, BMP *bmp, DIB *dib, PIXEL_1 *pixels);

void read_pixel_2bit(FILE *f1, BMP *bmp, DIB *dib, PIXEL_2 *pixels);

void read_pixel_4bit(FILE *f1, BMP *bmp, DIB *dib, PIXEL_4 *pixels);

void read_pixel_8bit(FILE *f1, BMP *bmp, DIB *dib, PIXEL_8 *pixels);

void read_pixel_16bit(FILE *f1, BMP *bmp, DIB *dib, PIXEL_16 *pixels);

void read_pixel_24bit(FILE *f1, BMP *bmp, DIB *dib, PIXEL_24 *pixels);

#endif //UNTITLED_INPUT_FILE_H
