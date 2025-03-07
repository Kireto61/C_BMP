//
// Created by kikig on 5.5.2023 г..
//

#ifndef UNTITLED_STRUCTS_H
#define UNTITLED_STRUCTS_H
///struktora za bmp
typedef struct BMP {
    char filetype[2]; // must be BM, must check if BM
    unsigned int filesize;
    short reserved1;
    short reserved2;
    unsigned int dataoffset;

} BMP;
///struktora za dib
typedef struct DIB {
    unsigned int fileheader;
    unsigned int headersize;
    int width;
    int height;
    short planes;
    short bitsperpixel;
    unsigned int compression;
    unsigned int bitmapsize;
    int horizontalres;
    int verticalres;
    unsigned int numcolors;
    unsigned int importantcolors;
}
        DIB;
///structora za 24bita na piksel
typedef struct PIXEL_24 {
    unsigned char b;
    unsigned char g;
    unsigned char r;

} PIXEL_24;
///structora za 16bita na piksel
typedef struct PIXEL_16 {
    unsigned char a_r;
    unsigned char b_g;

} PIXEL_16;
///structora za 8bita na piksel
typedef struct PIXEL_8 {
    unsigned char color;

} PIXEL_8;
///structora za 4bita na piksel
typedef struct PIXEL_4 {
    unsigned char color;

} PIXEL_4;
///structora za 2bita na piksel
typedef struct PIXEL_2 {
    unsigned char color;

} PIXEL_2;
///structora za 1bit na piksel

typedef struct PIXEL_1 {
    unsigned char color;

} PIXEL_1;
#endif //UNTITLED_STRUCTS_H
