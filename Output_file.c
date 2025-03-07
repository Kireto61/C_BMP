//
// Created by kikig on 4.5.2023 г..
//
#include "structs.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

///flip na dva bita na pixel priema BMP, DIB, i dinamichen masiv s pixelite
void flip_2bits(DIB *dib, PIXEL_2 *pixels) {
    PIXEL_2 *pixels_2 = malloc(dib->width * dib->height * sizeof(PIXEL_2));
    PIXEL_2 *pixels_3 = malloc(dib->width * dib->height * sizeof(PIXEL_2));
    PIXEL_2 *pixels_4 = malloc(dib->width * dib->height * sizeof(PIXEL_2));
    unsigned char pading2 = (8 - ((dib->width) % 8)) % 8;
    int count = 0;
    for (int i = 0; i < dib->height; i++) {
        for (int j = 0; j < (int) ceil(dib->width / 4.0); j++) {
            unsigned char c = pixels[i * dib->width + j].color;
            for (int k = 7; k >= 0; k -= 2) {
                unsigned char d = 0;
                d += (c >> k) & 1;
                d = d << 1;
                d += (c >> (k - 1)) & 1;
                pixels_2[count].color = d;
                count++;

            }
        }
        count -= pading2;

    }
    count = 0;
    for (int i = 0; i < dib->height; i++) {
        count = dib->width - 1;
        for (int j = 0; j < dib->width; j++) {
            pixels_3[i * dib->width + j].color = pixels_2[i * dib->width + count].color;
            count--;
        }

    }
    count = 0;
    for (int i = 0; i < dib->height; i++) {
        for (int j = 0; j < (int) ceil(dib->width / 4.0); j++) {
            unsigned char c = 0;
            for (int k = 0; k < 3; k++) {
                c = c + pixels_3[count].color;
                c = c << 1;
                count++;
            }
            c = c + pixels_3[count].color;
            count++;
            pixels_4[i * dib->width + j].color = c;
        }
        count -= pading2;

    }
    for (int i = 0; i < dib->height; i++) {
        for (int j = 0; j < (int) (ceil(dib->width / 4.0)); j++) {
            pixels[i * dib->width + j].color = pixels_4[i * dib->width + j].color;
        }

    }
    free(pixels_2);
    free(pixels_3);
    free(pixels_4);

}

///rotate na dva bita na pixel priema BMP, DIB, i dinamichen masiv s pixelite
void rotate_2bits(DIB *dib, PIXEL_2 *pixels) {
    PIXEL_2 *pixels_2 = malloc(dib->width * dib->height * sizeof(PIXEL_2));
    PIXEL_2 *pixels_3 = malloc(dib->width * dib->height * sizeof(PIXEL_2));
    PIXEL_2 *pixels_4 = malloc(dib->width * dib->height * sizeof(PIXEL_2));
    unsigned char pading2 = (8 - ((dib->height) % 8)) % 8;
    int count = 0;
    for (int i = 0; i < dib->height; i++) {
        for (int j = 0; j < (int) ceil(dib->width / 4.0); j++) {
            unsigned char c = pixels[i * dib->width + j].color;
            for (int k = 7; k >= 0; k -= 2) {
                unsigned char d = 0;
                d += (c >> k) & 1;
                d = d << 1;
                d += (c >> (k - 1)) & 1;
                pixels_2[count].color = d;
                pixels_3[count].color = d;
                count++;

            }
        }
        count -= pading2;

    }
    int x1 = (*dib).height - 1;
    for (int i = 0; i < (*dib).height; i++) {
        for (int y = 0; y < (*dib).width; y += 1) {
            pixels_2[y * (*dib).height + x1].color = pixels_3[i * (*dib).width + y].color;
        }
        x1 -= 1;
    }
    for (int i = 0; i < dib->height; i++) {
        for (int j = 0; j < (int) ceil(dib->width / 4.0); j++) {
            unsigned char c = 0;
            for (int k = 0; k < 3; k++) {
                c = c + pixels_3[count].color;
                c = c << 1;
                count++;
            }
            c = c + pixels_3[count].color;
            count++;
            pixels_4[i * dib->width + j].color = c;
        }
        count -= pading2;

    }
    int temp = dib->width;
    dib->width = dib->height;
    dib->height = temp;
    for (int i = 0; i < dib->height; i++) {
        for (int j = 0; j < (int) (ceil(dib->width / 4.0)); j++) {
            pixels[i * dib->width + j].color = pixels_4[i * dib->width + j].color;
        }
    }
    free(pixels_2);
    free(pixels_3);
    free(pixels_4);
}

///invert na dva bita na pixel priema BMP, DIB, i dinamichen masiv s pixelite
void invert_2bits(DIB *dib, PIXEL_2 *pixels) {
    for (int i = 0; i < dib->height; i++) {
        for (int j = 0; j < (int) ceil(dib->width / 4.0); j++) {
            unsigned int color = pixels[i * (*dib).width + j].color;
            color = ~color;
            pixels[i * (*dib).width + j].color = (char) color;
        }
    }
}
///zapisva pikselovia masiv v izhodniq fail
void write_2bit(BMP *bmp, DIB *dib, PIXEL_2 *pixels, FILE *f1) {
    fseek(f1, 18, SEEK_SET);
    fwrite(&dib->width, 4, 1, f1);
    fwrite(&dib->height, 4, 1, f1);
    unsigned char pading = (4 - ((int) ceil((dib->width / 4.0))) % 4) % 4;
    fseek(f1, (*bmp).dataoffset, SEEK_SET);
    for (int i = 0; i < dib->height; i++) {
        for (int j = 0; j < (int) (ceil(dib->width / 4.0)); j++) {
            fwrite(&pixels[i * dib->width + j].color, 1, 1, f1);
        }
        unsigned char d = 0x00;
        fwrite(&d, 1, pading, f1);

    }
}

///rotate na edin bit na pixel priema BMP, DIB, i dinamichen masiv s pixelite
void rotate_1bits(DIB *dib, PIXEL_1 *pixels) {
    PIXEL_1 *pixels_2 = malloc(dib->width * dib->height * sizeof(PIXEL_1));
    PIXEL_1 *pixels_3 = malloc(dib->width * dib->height * sizeof(PIXEL_1));
    PIXEL_1 *pixels_4 = malloc(dib->width * dib->height * sizeof(PIXEL_1));
    unsigned char pading2 = (8 - ((dib->width) % 8)) % 8;
    int count = 0;
    for (int i = 0; i < dib->height; i++) {
        for (int j = 0; j < (int) ceil(dib->width / 8.0); j++) {
            unsigned char c = pixels[i * dib->width + j].color;
            for (int k = 7; k >= 0; k--) {
                pixels_2[count].color = (c >> k) & 1;
                pixels_3[count].color = (c >> k) & 1;

                count++;
            }
        }
        count -= pading2;

    }
    int x1 = (*dib).height - 1;
    for (int i = 0; i < (*dib).height; i++) {
        for (int y = 0; y < (*dib).width; y += 1) {
            pixels_2[y * (*dib).height + x1].color = pixels_3[i * (*dib).width + y].color;
        }
        x1 -= 1;
    }
    count = 0;

    for (int i = 0; i < dib->height; i++) {
        for (int j = 0; j < (int) ceil(dib->width / 8.0); j++) {
            unsigned char c = 0;
            for (int k = 0; k < 7; k++) {
                c = c + pixels_2[count].color;
                c = c << 1;
                count++;
            }
            c = c + pixels_2[count].color;
            count++;
            pixels_4[i * dib->width + j].color = c;
        }
        count -= pading2;

    }
    int temp = dib->width;
    dib->width = dib->height;
    dib->height = temp;
    for (int i = 0; i < dib->height; i++) {
        for (int j = 0; j < (int) (ceil(dib->width / 8.0)); j++) {
            pixels[i * dib->width + j].color = pixels_4[i * dib->width + j].color;
        }

    }
    free(pixels_2);
    free(pixels_3);
    free(pixels_4);
}

///flip na edin bit na pixel priema BMP, DIB, i dinamichen masiv s pixelite
void flip_1bits(DIB *dib, PIXEL_1 *pixels) {
    PIXEL_1 *pixels_2 = malloc(dib->width * dib->height * sizeof(PIXEL_1));
    PIXEL_1 *pixels_3 = malloc(dib->width * dib->height * sizeof(PIXEL_1));
    PIXEL_1 *pixels_4 = malloc(dib->width * dib->height * sizeof(PIXEL_1));
    unsigned char pading2 = (8 - ((dib->width) % 8)) % 8;
    int count = 0;
    for (int i = 0; i < dib->height; i++) {
        for (int j = 0; j < (int) ceil(dib->width / 8.0); j++) {
            unsigned char c = pixels[i * dib->width + j].color;
            for (int k = 7; k >= 0; k--) {
                pixels_2[count].color = (c >> k) & 1;
                count++;
            }
        }
        count -= pading2;

    }
    count = 0;
    for (int i = 0; i < dib->height; i++) {
        count = dib->width - 1;
        for (int j = 0; j < dib->width; j++) {
            pixels_3[i * dib->width + j].color = pixels_2[i * dib->width + count].color;
            count--;
        }

    }
    count = 0;
    for (int i = 0; i < dib->height; i++) {
        for (int j = 0; j < (int) ceil(dib->width / 8.0); j++) {
            unsigned char c = 0;
            for (int k = 0; k < 7; k++) {
                c = c + pixels_3[count].color;
                c = c << 1;
                count++;
            }
            c = c + pixels_3[count].color;
            count++;
            pixels_4[i * dib->width + j].color = c;
        }
        count -= pading2;

    }
    for (int i = 0; i < dib->height; i++) {
        for (int j = 0; j < (int) (ceil(dib->width / 8.0)); j++) {
            pixels[i * dib->width + j].color = pixels_4[i * dib->width + j].color;
        }

    }
    free(pixels_2);
    free(pixels_3);
    free(pixels_4);
}
///zapisva pikselovia masiv v izhodniq fail
void write_1bit(BMP *bmp, DIB *dib, PIXEL_1 *pixels, FILE *f1) {
    fseek(f1, 18, SEEK_SET);
    fwrite(&dib->width, 4, 1, f1);
    fwrite(&dib->height, 4, 1, f1);

    unsigned char pading = (4 - ((int) ceil((dib->width / 8.0))) % 4) % 4;
    fseek(f1, (*bmp).dataoffset, SEEK_SET);
    for (int i = 0; i < dib->height; i++) {
        for (int j = 0; j < (int) (ceil(dib->width / 8.0)); j++) {
            fwrite(&pixels[i * dib->width + j].color, 1, 1, f1);
        }
        unsigned char d = 0x00;
        fwrite(&d, 1, pading, f1);

    }
}
///zapisva pikselovia masiv v izhodniq fail
void write_4bit(BMP *bmp, DIB *dib, PIXEL_4 *pixels, FILE *f1) {
    fseek(f1, 18, SEEK_SET);
    fwrite(&dib->width, 4, 1, f1);
    fwrite(&dib->height, 4, 1, f1);
    unsigned char pading = (4 - ((int) ceil((dib->width / 2.0))) % 4) % 4;
    fseek(f1, bmp->dataoffset, SEEK_SET);
    for (int i = 0; i < dib->height; i++) {
        for (int j = 0; j < (int) ceil(dib->width / 2.0); j++) {
            fwrite(&pixels[i * dib->width + j].color, 1, 1, f1);
        }
        unsigned char d = 0x00;
        fwrite(&d, 1, pading, f1);
    }
}
///zapisva pikselovia masiv v izhodniq fail
void write_8bit(BMP *bmp, DIB *dib, PIXEL_8 *pixels, FILE *f1) {
    fseek(f1, 18, SEEK_SET);
    fwrite(&dib->width, 4, 1, f1);
    fwrite(&dib->height, 4, 1, f1);
    unsigned char pading = (4 - ((int) ceil((dib->width / 1.0))) % 4) % 4;
    fseek(f1, bmp->dataoffset, SEEK_SET);
    for (int i = 0; i < dib->height; i++) {
        for (int j = 0; j < dib->width; j++) {
            fwrite(&pixels[i * dib->width + j].color, 1, 1, f1);
        }
        unsigned char d = 0x00;
        fwrite(&d, 1, pading, f1);
    }
}
///zapisva pikselovia masiv v izhodniq fail
void write_16bit(BMP *bmp, DIB *dib, PIXEL_16 *pixels, FILE *f1) {
    fseek(f1, 18, SEEK_SET);
    fwrite(&dib->width, 4, 1, f1);
    fwrite(&dib->height, 4, 1, f1);
    unsigned char pading = (4 - ((int) ceil((dib->width * 2.0))) % 4) % 4;
    fseek(f1, bmp->dataoffset, SEEK_SET);
    for (int i = 0; i < dib->height; i++) {
        for (int j = 0; j < dib->width; j++) {
            fwrite(&pixels[i * dib->width + j].b_g, 1, 1, f1);
            fwrite(&pixels[i * dib->width + j].a_r, 1, 1, f1);
        }
        unsigned char d = 0x00;
        fwrite(&d, 1, pading, f1);
    }
}
///zapisva pikselovia masiv v izhodniq fail
void write_24bit(BMP *bmp, DIB *dib, PIXEL_24 *pixels, FILE *f1) {
    fseek(f1, 18, SEEK_SET);
    fwrite(&dib->width, 4, 1, f1);
    fwrite(&dib->height, 4, 1, f1);
    printf("%d width, %d, heigt", dib->width, dib->height);
    unsigned char pading = (4 - (((int) ceil((dib->width * 3.0))) % 4)) % 4;
    fseek(f1, bmp->dataoffset, SEEK_SET);
    for (int i = 0; i < dib->height; i++) {
        for (int j = 0; j < dib->width; j++) {
            fwrite(&pixels[i * dib->width + j].b, 1, 1, f1);
            fwrite(&pixels[i * dib->width + j].g, 1, 1, f1);
            fwrite(&pixels[i * dib->width + j].r, 1, 1, f1);
        }
        unsigned char d = 0x00;
        fwrite(&d, 1, pading, f1);
    }
}

///invert na edin bit na pixel priema BMP, DIB, i dinamichen masiv s pixelite
void invert_1bits(DIB *dib, PIXEL_1 *pixels) {
    for (int i = 0; i < dib->height; i++) {
        for (int j = 0; j < (int) ceil(dib->width / 8.0); j++) {
            unsigned int color = pixels[i * (*dib).width + j].color;
            color = ~color;
            pixels[i * (*dib).width + j].color = (char) color;
        }
    }
}

///flip na chetiri bita na pixel priema BMP, DIB, i dinamichen masiv s pixelite
void flip_4bits(DIB *dib, PIXEL_4 *pixels) {
    int pixelSize = (*dib).height * (*dib).width;
    int count = 0;
    unsigned char pading2 = (8 - ((dib->width) % 8)) % 8;
    PIXEL_4 *pixels_2 = malloc(dib->width * dib->height * sizeof(PIXEL_4));
    PIXEL_4 *pixels_3 = malloc(dib->width * dib->height * sizeof(PIXEL_4));

    for (int i = 0; i < dib->height; i++) {
        for (int j = 0; j < (int) ceil(dib->width / 2.0); j++) {
            unsigned char c = pixels[i * dib->width + j].color;
            for (int k = 7; k >= 0; k -= 4) {
                unsigned char d = 0;
                d += (c >> k) & 1;
                d = d << 1;
                d += (c >> (k - 1)) & 1;
                d = d << 1;
                d += (c >> (k - 2)) & 1;
                d = d << 1;
                d += (c >> (k - 3)) & 1;
                pixels_2[count].color = d;
                pixels_3[count].color = d;
                count++;

            }
        }
        count -= pading2;

    }

    for (int x = 0; x < (*dib).height; x++) {
        int x1 = (*dib).width - 1;
        for (int y = 0; y < (*dib).width; y += 1) {
            pixels_2[x * (*dib).width + y].color = pixels_3[x * (*dib).width + x1].color;
            x1 -= 1;
        }
    }
    count = 0;
    for (int i = 0; i < dib->height; i++) {
        for (int j = 0; j < (int) ceil(dib->width / 2.0); j++) {
            unsigned char c = 0;
            c = c + pixels_2[count].color;
            c = c << 4;
            count++;
            c = c + pixels_2[count].color;
            count++;
            pixels[i * dib->width + j].color = c;
        }

        count -= pading2;
    }
    free(pixels_2);
    free(pixels_3);
}

///rotate na chetiri bita na pixel priema BMP, DIB, i dinamichen masiv s pixelite
void rotate_4bits(DIB *dib, PIXEL_4 *pixels) {
    int pixelSize = (*dib).height * (*dib).width;
    int count = 0;
    unsigned char pading2 = (8 - ((dib->width) % 8)) % 8;
    PIXEL_4 *pixels_2 = malloc(dib->width * dib->height * sizeof(PIXEL_4));
    PIXEL_4 *pixels_3 = malloc(dib->width * dib->height * sizeof(PIXEL_4));

    for (int i = 0; i < dib->height; i++) {
        for (int j = 0; j < (int) ceil(dib->width / 2.0); j++) {
            unsigned char c = pixels[i * dib->width + j].color;
            for (int k = 7; k >= 0; k -= 4) {
                unsigned char d = 0;
                d += (c >> k) & 1;
                d = d << 1;
                d += (c >> (k - 1)) & 1;
                d = d << 1;
                d += (c >> (k - 2)) & 1;
                d = d << 1;
                d += (c >> (k - 3)) & 1;
                pixels_2[count].color = d;
                pixels_3[count].color = d;
                count++;

            }
        }

    }


    int x1 = (*dib).height - 1;
    for (int i = 0; i < dib->height; i++) {
        for (int j = 0; j < (int) ceil(dib->width); j++) {
            pixels_2[j * (*dib).height + x1].color = pixels_3[i * (*dib).width + j].color;
        }
        x1--;
    }
    int temp = dib->width;
    dib->width = dib->height;
    dib->height = temp;
    for (int i = 0; i < dib->height; i++) {
        int k = 0;
        for (int j = 0; j < (int) ceil(dib->width / 2.0); j++) {
            unsigned char c = 0;
            c = c + pixels_2[i * (*dib).width + k].color;
            c = c << 4;
            c = c + pixels_2[i * (*dib).width + k + 1].color;
            k += 2;
            pixels[i * dib->width + j].color = c;
        }
    }
    free(pixels_2);
    free(pixels_3);
}

///invert na chetiri bita na pixel priema BMP, DIB, i dinamichen masiv s pixelite
void invert_4bits(DIB *dib, PIXEL_4 *pixels) {
    for (int i = 0; i < dib->height; i++) {
        for (int j = 0; j < (int) ceil(dib->width / 2.0); j++) {
            unsigned int color = pixels[i * dib->width + j].color;
            color = ~color;
            pixels[i * dib->width + j].color = (char) color;
        }
    }
}

///flip na osem bita na pixel priema BMP, DIB, i dinamichen masiv s pixelite
void flip_8bits(DIB *dib, PIXEL_8 *pixels) {
    PIXEL_8 *pixels_2 = malloc(dib->width * dib->height * sizeof(PIXEL_8));
    for (int x = 0; x < (*dib).height; x++) {
        int x1 = (*dib).width - 1;
        for (int y = 0; y < (*dib).width; y++) {
            pixels_2[x * (*dib).width + y].color = pixels[x * (*dib).width + x1].color;
            x1--;
        }
    }

    for (int i = 0; i < dib->height; i++) {
        for (int j = 0; j < dib->width; j++) {
            pixels[i * (*dib).width + j].color = pixels_2[i * (*dib).width + j].color;
        }
    }
    free(pixels_2);
}

///rotate na osem bita na pixel priema BMP, DIB, i dinamichen masiv s pixelite
void rotate_8bits(DIB *dib, PIXEL_8 *pixels) {
    PIXEL_8 *pixels_2 = malloc(dib->width * dib->height * sizeof(PIXEL_8));
    int x1 = (*dib).height - 1;
    for (int i = 0; i < dib->height; i++) {
        for (int j = 0; j < dib->width; j++) {
            pixels_2[j * (*dib).height + x1].color = pixels[i * (*dib).width + j].color;
        }
        x1--;
    }
    int temp = dib->width;
    dib->width = dib->height;
    dib->height = temp;
    for (int i = 0; i < dib->height; i++) {
        for (int j = 0; j < dib->width; j++) {
            pixels[i * (*dib).width + j].color = pixels_2[i * (*dib).width + j].color;
        }
    }
    free(pixels_2);
}

///invert na osem bita na pixel priema BMP, DIB, i dinamichen masiv s pixelite
void invert_8bits(DIB *dib, PIXEL_8 *pixels) {
    for (int i = 0; i < dib->height; i++) {
        for (int j = 0; j < dib->width; j++) {
            unsigned int color = pixels[i * dib->width + j].color;
            color = ~color;
            pixels[i * dib->width + j].color = (char) color;
        }
    }
}

///flip na shesnadeset bita na pixel priema BMP, DIB, i dinamichen masiv s pixelite
void flip_16bits(DIB *dib, PIXEL_16 *pixels) {
    PIXEL_16 *pixels_2 = malloc(dib->width * dib->height * sizeof(PIXEL_16));
    for (int x = 0; x < (*dib).height; x++) {
        int x1 = (*dib).width - 1;
        for (int y = 0; y < (*dib).width; y++) {
            pixels_2[x * (*dib).width + y].a_r = pixels[x * (*dib).width + x1].a_r;
            pixels_2[x * (*dib).width + y].b_g = pixels[x * (*dib).width + x1].b_g;
            x1--;
        }
    }
    for (int i = 0; i < dib->height; i++) {
        for (int j = 0; j < dib->width; j++) {
            pixels[i * (*dib).width + j].b_g = pixels_2[i * (*dib).width + j].b_g;
            pixels[i * (*dib).width + j].a_r = pixels_2[i * (*dib).width + j].a_r;
        }
    }
    free(pixels_2);
}

///rotate na shesnadeset bita na pixel priema BMP, DIB, i dinamichen masiv s pixelite
void rotate_16bits(DIB *dib, PIXEL_16 *pixels) {
    PIXEL_16 *pixels_2 = malloc(dib->width * dib->height * sizeof(PIXEL_16));
    int x1 = (*dib).height - 1;
    for (int i = 0; i < dib->height; i++) {
        for (int j = 0; j < dib->width; j++) {
            pixels_2[j * (*dib).height + x1].a_r = pixels[i * (*dib).width + j].a_r;
            pixels_2[j * (*dib).height + x1].b_g = pixels[i * (*dib).width + j].b_g;
        }
        x1--;
    }
    int temp = dib->width;
    dib->width = dib->height;
    dib->height = temp;
    for (int i = 0; i < dib->height; i++) {
        for (int j = 0; j < dib->width; j++) {
            pixels[i * (*dib).width + j].b_g = pixels_2[i * (*dib).width + j].b_g;
            pixels[i * (*dib).width + j].a_r = pixels_2[i * (*dib).width + j].a_r;
        }
    }
    free(pixels_2);
}

///rotate na shesnadeset bita na pixel priema BMP, DIB, i dinamichen masiv s pixelite
void invert_16bits(DIB *dib, PIXEL_16 *pixels) {
    for (int i = 0; i < dib->height; i++) {
        for (int j = 0; j < dib->width; j++) {
            unsigned int blue = pixels[i * dib->width + j].b_g;
            blue = ~blue;
            pixels[i * dib->width + j].b_g = (char) blue;
            unsigned int green = pixels[i * dib->width + j].a_r;
            green = ~green;
            pixels[i * dib->width + j].a_r = (char) green;
        }
    }
}

///flip na dvadeset i chetiri bita na pixel priema BMP, DIB, i dinamichen masiv s pixelite
void flip_24bits(DIB *dib, PIXEL_24 *pixels) {
    PIXEL_24 *pixels_2 = malloc(dib->width * dib->height * sizeof(PIXEL_24));
    for (int x = 0; x < (*dib).height; x++) {
        int x1 = (*dib).width - 1;
        for (int y = 0; y < (*dib).width; y++) {
            pixels_2[x * (*dib).width + y].b = pixels[x * (*dib).width + x1].b;
            pixels_2[x * (*dib).width + y].g = pixels[x * (*dib).width + x1].g;
            pixels_2[x * (*dib).width + y].r = pixels[x * (*dib).width + x1].r;
            x1--;
        }
    }
    for (int i = 0; i < dib->height; i++) {
        for (int j = 0; j < dib->width; j++) {
            pixels[i * (*dib).width + j].b = pixels_2[i * (*dib).width + j].b;
            pixels[i * (*dib).width + j].g = pixels_2[i * (*dib).width + j].g;
            pixels[i * (*dib).width + j].r = pixels_2[i * (*dib).width + j].r;
        }
    }
    free(pixels_2);
}

///rotate na dvadeset i chetiri bita na pixel priema BMP, DIB, i dinamichen masiv s pixelite
void rotate_24bits(DIB *dib, PIXEL_24 *pixels) {
    PIXEL_24 *pixels_2 = malloc(dib->width * dib->height * sizeof(PIXEL_24));
    int x1 = (*dib).height - 1;
    for (int i = 0; i < dib->height; i++) {
        for (int j = 0; j < dib->width; j++) {
            pixels_2[j * (*dib).height + x1].b = pixels[i * (*dib).width + j].b;
            pixels_2[j * (*dib).height + x1].g = pixels[i * (*dib).width + j].g;
            pixels_2[j * (*dib).height + x1].r = pixels[i * (*dib).width + j].r;
        }
        x1--;
    }
    int temp = dib->width;
    dib->width = dib->height;
    dib->height = temp;
    for (int i = 0; i < dib->height; i++) {
        for (int j = 0; j < dib->width; j++) {
            pixels[i * (*dib).width + j].b = pixels_2[i * (*dib).width + j].b;
            pixels[i * (*dib).width + j].g = pixels_2[i * (*dib).width + j].g;
            pixels[i * (*dib).width + j].r = pixels_2[i * (*dib).width + j].r;
        }
    }
    free(pixels_2);
}

///invert na dvadeset i chetiri bita na pixel priema BMP, DIB, i dinamichen masiv s pixelite
void invert_24bits(DIB *dib, PIXEL_24 *pixels) {
    for (int i = 0; i < dib->height; i++) {
        for (int j = 0; j < dib->width; j++) {
            unsigned int blue = pixels[i * dib->width + j].b;
            blue = ~blue;
            pixels[i * dib->width + j].b = (char) blue;
            unsigned int green = pixels[i * dib->width + j].g;
            green = ~green;
            pixels[i * dib->width + j].g = (char) green;
            unsigned int red = pixels[i * dib->width + j].r;
            red = ~red;
            pixels[i * dib->width + j].r = (char) red;
        }
    }
}

///kopira vhodnia faila i go slaga v izhodniq
void copy_file(FILE *f, FILE *f1) {
    size_t n, m;
    unsigned char buff[8192];
    do {
        n = fread(buff, 1, sizeof buff, f);
        if (n) m = fwrite(buff, 1, n, f1);
        else m = 0;
    } while ((n > 0) && (n == m));
    if (m) perror("copy");
}