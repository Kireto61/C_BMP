//
// Created by Kiril Valkov on 26.04.23.
//


#include <stdio.h>
#include <stdlib.h>
#include <intrin.h>
#include "Input_file.h"
#include "Output_file.h"


void throw_exception(int code, char message[]);

void perform_commands1(const char *commands, struct BMP *bmp, struct DIB *dib, PIXEL_1 *one_byte_pixels,
                       FILE *output_file);

void perform_commands2(const char *commands, struct BMP *bmp, struct DIB *dib, PIXEL_2 *two_byte_pixels,
                       FILE *output_file);

void perform_commands4(const char *commands, struct BMP *bmp, struct DIB *dib, PIXEL_4 *four_byte_pixels,
                       FILE *output_file);

void perform_commands8(const char *commands, struct BMP *bmp, struct DIB *dib, PIXEL_8 *eight_byte_pixels,
                       FILE *output_file);

void perform_commands16(const char *commands, struct BMP *bmp, struct DIB *dib, PIXEL_16 *sixteen_byte_pixels,
                        FILE *output_file);

void perform_commands24(const char *commands, struct BMP *bmp, struct DIB *dib, PIXEL_24 *twenty_four_byte_pixels,
                        FILE *output_file);


char *getline(void) {
    char *line = malloc(100), *linep = line;
    size_t lenmax = 100, len = lenmax;
    int c;
    if (line == NULL)
        return NULL;
    for (;;) {
        c = fgetc(stdin);
        if (c == EOF)
            break;
        if (--len == 0) {
            len = lenmax;
            char *linen = realloc(linep, lenmax *= 2);

            if (linen == NULL) {
                free(linep);
                return NULL;
            }
            line = linen + (line - linep);
            linep = linen;
        }
        if (c == 10) {
            break;
        }
        *line++ = c;
    }
    *line = '\0';
    return linep;
}

int validate_path(char *word) {
    int string_len = strlen(word);
    return string_len > 4 && word[string_len - 1] == 'p' && word[string_len - 2] == 'm' &&
           word[string_len - 3] == 'b' &&
           word[string_len - 4] == '.';
}


int main(int argc, char *argv[]) {
    struct BMP bmp;
    struct DIB dib;


    FILE *input_file;
    FILE *output_file;

    int index = 1;

    char *arguments[4];
    int num_arguments_expected = 3;
    int word_count = 0;
    for (int i = 0; i < argc; ++i) {
        char *word = argv[i];
        if (validate_path(word) == 1) {
            arguments[word_count] = word;
            word_count++;
        } else {
            arguments[2] = word;
        }
    }
    if (argc < num_arguments_expected + index) {
        char *cmd_hints[] = {"Enter path to input file:", "Enter path to output file:", "Enter commands:"};
        for (int i = argc; i < index + num_arguments_expected; ++i) {
            if (word_count < 2) {
                printf("%s\n", cmd_hints[word_count]);
            } else {
                printf("%s\n", cmd_hints[2]);
            }
            char *word = getline();
            if (validate_path(word) == 1) {
                arguments[word_count] = word;
                word_count++;
            } else {
                arguments[2] = word;
            }
        }
    } else if (argc > 4) {
        throw_exception(-1,
                        "Wrong number of argument passed! Expected 2 arguments: 1 - input file, 2 - output file, 3 - commands.");
    }
    if (word_count != 2) {
        throw_exception(-1,
                        "The arguments passed are wrong! Expected 2 arguments: 1 - input file, 2 - output file, 3 - commands.");
    }

    input_file = fopen(arguments[0], "rb+");
    if (input_file == NULL) {
        throw_exception(-1, "Invalid input file");
    }
    output_file = fopen(arguments[1], "wb+");
    if (output_file == NULL) {
        throw_exception(-1, "Invalid output file");
    }

    copy_file(input_file, output_file);

    fseek(input_file, 0, SEEK_SET);
    fseek(output_file, 0, SEEK_SET);

    input_bmp_Dib(input_file, &bmp, &dib);

    PIXEL_1 *one_byte_pixels;
    PIXEL_2 *two_byte_pixels;
    PIXEL_4 *four_byte_pixels;
    PIXEL_8 *eight_byte_pixels;
    PIXEL_16 *sixteen_byte_pixels;
    PIXEL_24 *twenty_four_byte_pixels;

    switch (dib.bitsperpixel) {
        case 1:
            one_byte_pixels = (PIXEL_1 *) malloc(dib.width * dib.height * sizeof(PIXEL_1));
            read_pixel_1bit(input_file, &bmp, &dib, one_byte_pixels);
            perform_commands1(arguments[2], &bmp, &dib, one_byte_pixels, output_file);
            free(one_byte_pixels);
            break;
        case 2:
            two_byte_pixels = (PIXEL_2 *) malloc(dib.width * dib.height * sizeof(PIXEL_2));
            read_pixel_2bit(input_file, &bmp, &dib, two_byte_pixels);
            perform_commands2(arguments[2], &bmp, &dib, two_byte_pixels, output_file);
            free(two_byte_pixels);
            break;
        case 4:
            four_byte_pixels = (PIXEL_4 *) malloc(dib.width * dib.height * sizeof(PIXEL_4));
            read_pixel_4bit(input_file, &bmp, &dib, four_byte_pixels);
            perform_commands4(arguments[2], &bmp, &dib, four_byte_pixels, output_file);
            free(four_byte_pixels);
            break;
        case 8:
            eight_byte_pixels = (PIXEL_8 *) malloc(dib.width * dib.height * sizeof(PIXEL_8));
            read_pixel_8bit(input_file, &bmp, &dib, eight_byte_pixels);
            perform_commands8(arguments[2], &bmp, &dib, eight_byte_pixels, output_file);
            free(eight_byte_pixels);
            break;
        case 16:
            sixteen_byte_pixels = (PIXEL_16 *) malloc(dib.width * dib.height * sizeof(PIXEL_16));
            read_pixel_16bit(input_file, &bmp, &dib, sixteen_byte_pixels);
            perform_commands16(arguments[2], &bmp, &dib, sixteen_byte_pixels, output_file);
            free(sixteen_byte_pixels);
            break;
        case 24:
            twenty_four_byte_pixels = (PIXEL_24 *) malloc(dib.width * dib.height * sizeof(PIXEL_24));
            read_pixel_24bit(input_file, &bmp, &dib, twenty_four_byte_pixels);
            perform_commands24(arguments[2], &bmp, &dib, twenty_four_byte_pixels, output_file);
            free(twenty_four_byte_pixels);
            break;
        default:
            throw_exception(-1, "Error! Invalid image bits");
    }

    printf("reddy");
    fclose(input_file);
    fclose(output_file);

    return 0;
}

void perform_commands1(const char *commands, struct BMP *bmp, struct DIB *dib, PIXEL_1 *one_byte_pixels,
                       FILE *output_file) {
    int index = 0;
    while (commands[index] != 'D') {
        char current_command = commands[index];
        if (current_command == 'A') {
            flip_1bits(dib, one_byte_pixels);
        } else if (current_command == 'B') {
            invert_1bits(dib, one_byte_pixels);
        } else if (current_command == 'C') {
            rotate_1bits(dib, one_byte_pixels);
        }
        index++;
    }
    write_1bit(bmp, dib, one_byte_pixels, output_file);
}


void perform_commands2(const char *commands, struct BMP *bmp, struct DIB *dib, PIXEL_2 *two_byte_pixels,
                       FILE *output_file) {
    int index = 0;
    while (commands[index] != 'D') {
        char current_command = commands[index];
        if (current_command == 'A') {
            flip_2bits(dib, two_byte_pixels);
        } else if (current_command == 'B') {
            invert_2bits(dib, two_byte_pixels);
        } else if (current_command == 'C') {
            rotate_2bits(dib, two_byte_pixels);
        }
        index++;
    }
    write_2bit(bmp, dib, two_byte_pixels, output_file);
}


void perform_commands4(const char *commands, struct BMP *bmp, struct DIB *dib, PIXEL_4 *four_byte_pixels,
                       FILE *output_file) {
    int index = 0;
    while (commands[index] != 'D') {
        char current_command = commands[index];
        if (current_command == 'A') {
            flip_4bits(dib, four_byte_pixels);
        } else if (current_command == 'B') {
            invert_4bits(dib, four_byte_pixels);
        } else if (current_command == 'C') {
            rotate_4bits(dib, four_byte_pixels);
        }
        index++;
    }
    write_4bit(bmp, dib, four_byte_pixels, output_file);
}


void perform_commands8(const char *commands, struct BMP *bmp, struct DIB *dib, PIXEL_8 *eight_byte_pixels,
                       FILE *output_file) {
    int index = 0;
    while (commands[index] != 'D') {
        char current_command = commands[index];
        if (current_command == 'A') {
            flip_8bits(dib, eight_byte_pixels);
        } else if (current_command == 'B') {
            invert_8bits(dib, eight_byte_pixels);
        } else if (current_command == 'C') {
            rotate_8bits(dib, eight_byte_pixels);
        }
        index++;
    }
    write_8bit(bmp, dib, eight_byte_pixels, output_file);
}

void perform_commands16(const char *commands, struct BMP *bmp, struct DIB *dib, PIXEL_16 *sixteen_byte_pixels,
                        FILE *output_file) {
    int index = 0;
    while (commands[index] != 'D') {
        char current_command = commands[index];
        if (current_command == 'A') {
            flip_16bits(dib, sixteen_byte_pixels);
        } else if (current_command == 'B') {
            invert_16bits(dib, sixteen_byte_pixels);
        } else if (current_command == 'C') {
            rotate_16bits(dib, sixteen_byte_pixels);
        }
        index++;
    }
    write_16bit(bmp, dib, sixteen_byte_pixels, output_file);
}

void perform_commands24(const char *commands, struct BMP *bmp, struct DIB *dib, PIXEL_24 *twenty_four_byte_pixels,
                        FILE *output_file) {
    int index = 0;
    while (commands[index] != 'D') {
        char current_command = commands[index];
        if (current_command == 'A') {
            flip_24bits(dib, twenty_four_byte_pixels);
        } else if (current_command == 'B') {
            invert_24bits(dib, twenty_four_byte_pixels);
        } else if (current_command == 'C') {
            rotate_24bits(dib, twenty_four_byte_pixels);
        }
        index++;
    }
    write_24bit(bmp, dib, twenty_four_byte_pixels, output_file);
}

void throw_exception(int code, char message[]) {
    perror(message);
    exit(code);
}



