//
// Created by kikig on 26.4.2023 г..
//
#include <stdio.h>
#include <string.h>

int main() {
    char inpath[100];
    char outpath[100];
    printf("Vavedete pat do vhoden fail\n");
    scanf("%s", &inpath);
    printf("Vavedete pat do izhoden fail\n");
    scanf("%s", &outpath);



    while(1) {
        printf("Vavedete edna ot slednite vazmojnosti:\n1. FLIP\n2. INVERT\n3. ROTATE\n4. EXIT\n");
        char str1[6];
        char str2[]="FLIP";
        char str3[]="INVERT";
        char str4[]="ROTATE";
        char str5[]="EXIT";
        scanf("%s", &str1);
        for (int i = 0; str1[i] != '\0'; i++) {
            if (str1[i] >= 'a' && str1[i] <= 'z') {
                str1[i] = str1[i] - 32;
            }
        }
        if (!strcmp(str1, str2)) {
            printf("%s\n", str1);
        } else if (!strcmp(str1, str3)) {
            printf("%s\n", str1);
        } else if (!strcmp(str1,str4)) {
            printf("%s\n", str1);

        } else if(!strcmp(str1, str5)) {
            break;
        }
    }

    return 0;
}
#include "BMPheader.h"
#include "BMPfunctionality.h"
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]){

    int         height          = 0;
    int         width           = 0;
    int         size_of_image   = 0;
    int         size_of_file    = 0;
    FILE*       fbmp            = NULL;
    FILE*       mFile           = NULL;
    void**      ImageData       = NULL;
    bmpHeader*  pHeader         = NULL;
    char*       ImageFile       = NULL;
    char*       ImageDataOffset = NULL;
    int         offset          = 0;

    if(argc > 2)
    {
        fbmp = fopen(argv[1], "rb");
        if(fbmp == NULL){
            perror("file does not exist!\n");
            return -1;
        }
        mFile = fopen(argv[2], "wb");
        if(mFile == NULL){
            perror("file did not open!\n");
            return -1;
        }
    }
    else
    {
        printf("Input files!\n(Example: inputfile.bmp   outputfile.bmp)\n");
        return -1;
    }

    pHeader = (bmpHeader*) malloc(sizeof(bmpHeader));

    if(1 != fread(pHeader,sizeof(bmpHeader),1,fbmp))
    {
        printf("error 1 reading from file\n");
    }

    size_of_image = get_sizeofImageData(*pHeader);

    ImageDataOffset = bmp_header_offset(*pHeader, &offset);

    if(offset != fread(ImageDataOffset,sizeof(char),offset,fbmp))
    {
        printf("error 2 reading from file\n");
    }

    ImageFile = (char*) malloc(sizeof(char)* size_of_image);

    if(ImageFile != NULL)
    {
        fread(ImageFile,sizeof(char),size_of_image,fbmp);
    }

    ImageData = BMP_Image_data_handler(ImageFile, *pHeader);
//// main functions ////

    horizontal_flip(ImageData,pHeader);

    ImageData = rotate(ImageData,pHeader);

    Inverce(ImageData,pHeader);

//// main functions end ////
    get_current_dimentions(pHeader,&width,&height);

    fwrite(pHeader,sizeof(bmpHeader),1,mFile);

    fwrite(ImageDataOffset,sizeof(char),offset,mFile);

    int size = size_of_image/(height * width);

    char** Image = (char**)ImageData;

    for(int i = 0; i < height ; i ++)
    {
        for(int p = 0; p < width*size; p++)
        {
            fwrite(&Image[i][p],sizeof(char),1,mFile);
        }
    }

////////////////////////////////////////////
/// free
///////////////////////////////////////////

    free(pHeader);
    free(ImageDataOffset);
    for(int p = 0; p < height ; p++)
    {
        free(ImageData[p]);
    }
    free(ImageData);
    free(ImageFile);
    fclose(fbmp);
    fclose(mFile);
    return 0;
}