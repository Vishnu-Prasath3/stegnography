#include <stdio.h>
#include <string.h>
#include "encode.h"
#include "types.h"

/* Function Definitions */

/* Get image size
 * Input: Image file ptr
 * Output: width * height * bytes per pixel (3 in our case)
 * Description: In BMP Image, width is stored in offset 18,
 * and height after that. size is 4 bytes
 */

uint get_image_size_for_bmp(FILE *fptr_image)
{
    uint width, height;
    // Seek to 18th byte
    fseek(fptr_image, 18, SEEK_SET);

    // Read the width (an int)
    fread(&width, sizeof(int), 1, fptr_image);
    printf("width = %u\n", width);

    // Read the height (an int)
    fread(&height, sizeof(int), 1, fptr_image);
    printf("height = %u\n", height);

    // Return image capacity
    return width * height * 3;
}

/*
 * Get File pointers for i/p and o/p files
 * Inputs: Src Image file, Secret file and
 * Stego Image file
 * Output: FILE pointer for above files
 * Return Value: e_success or e_failure, on file errors
 */

Status open_files(EncodeInfo *encInfo)
{

    // Src Image file assigning src image to fptr
    encInfo->fptr_src_image = fopen(encInfo->src_image_fname, "r");

    // Do Error handling
    if (encInfo->fptr_src_image == NULL)
    {
        perror("fopen");
        fprintf(stderr, "ERROR: Unable to open file %s\n", encInfo->src_image_fname);

        return e_failure;
    }

    // Secret file
    encInfo->fptr_secret = fopen(encInfo->secret_fname, "r");
    // Do Error handling
    if (encInfo->fptr_secret == NULL)
    {
        perror("fopen");
        fprintf(stderr, "ERROR: Unable to open file %s\n", encInfo->secret_fname);

        return e_failure;
    }

    // Stego Image file
    encInfo->fptr_stego_image = fopen(encInfo->stego_image_fname, "w");
    // Do Error handling
    if (encInfo->fptr_stego_image == NULL)
    {
        perror("fopen");
        fprintf(stderr, "ERROR: Unable to open file %s\n", encInfo->stego_image_fname);

        return e_failure;
    }

    // No failure return e_success
    return e_success;
}

Status read_and_validate_encode_args(char *argv[], EncodeInfo *encInfo)
{

    // checking for the .bmp
    if (strcmp(strstr(argv[2], ".bmp"), ".bmp") == 0)
    {
        // assigning source image name
        encInfo->src_image_fname = argv[2];
    }
    else
    {
        // print error message   
        printf(" %s", argv[2]);
        fprintf(stderr, "Error:Invalid file extension .bmp");
    }

    //  checking for the .txt
    if (strcmp(strstr(argv[3], ".txt"), ".txt") == 0)
    {
        // assigning secret file name
        encInfo->secret_fname = argv[3];
    }
    else
    {
        // print error message

        printf("\n %s", argv[3]);

        fprintf(stderr, "Error:Invalid file extension .txt");
    }

    /*
     if no name given in cli for destination file ?
        then create one 

    */ 

    if (strcmp(argv[3], "") == 0)
    {

    
        encInfo->fptr_stego_image = fopen("code.bmp", "w");

        encInfo->stego_image_fname = "code.bmp";

        // printf("\nThe stego_image_fname is :%s", encInfo->stego_image_fname);
        return 1;
    }

    if (strcmp(strstr(argv[4], ".bmp"), ".bmp") == 0)
    {
        // assigning stego image name
        encInfo->stego_image_fname = argv[4];
        // printf("\nThe stego_image_fname is :%s", encInfo->stego_image_fname);
    }
    else
    {
        fprintf(stderr, "Error:Invalid file extension");
    }

}

Status check_capacity(EncodeInfo *encInfo)
{
    // getting size of the secret_file_size 
    fseek(encInfo->fptr_secret, 0, SEEK_END);

    // fptr_secretfile pointer moved to the end of file

    uint size_of_secret = ftell(encInfo->fptr_secret);
 
    if(size_of_secret == -1){
        fprintf(stderr,"Error:ftell failed to determine size of file\n");
        return e_failure;
    }

    // uint src_file_size = get_image_size_for_bmp(encInfo->fptr_src_image);

    // encInfo->size_secret_file;

    // check the (beautifull.bmp) image file size greater than header

    return e_success;
}
