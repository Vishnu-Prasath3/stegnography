#include <stdio.h>
#include<string.h>
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
    // Src Image file
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

Status read_and_validate_encode_args(char *argv[], EncodeInfo *encInfo){

 if(strcmp(strstr(argv[2],".bmp"),".bmp")){
  
encInfo->src_image_fname = argv[2];

 }
 else{
    // print error message
    fprintf(stderr,"Error:Invalid file extension");
 }

 if(strcmp(strstr(argv[3],".txt"),".txt")){

    encInfo->secret_fname = argv[3];

 }
 else{
    // print error message
    fprintf(stderr,"Error:Invalid file extension");
 }

 if(strcmp(strstr(argv[4],".bmp"),".bmp")){

 encInfo->stego_image_fname = argv[4];

 }else{
    fprintf(stderr,"Error:Invalid file extension");
 }
 
 if(strstr(argv[4],"")){
    
    FILE *fp;

    fp=fopen("code.bmp","w");
    
    if(fp != NULL)
    {
        printf("file opened");
        encInfo->stego_image_fname="code.bmp";
    }
    else{
        printf("File not-opened");
    }
    fclose(fp);

 }

}










    /*
--argv[2]--
------>check for .bmp =====>(use strstr())
-------->pass argv[]-->return the address 
------------------------------->then strcmp()                               
--------------------------------------------->strcmp(strstr(argc[2],".bmp"),".bmp");
!!!!!if not .bmp print error message

--argv[3]--
check for .txt
if not print error

--argc[4]--
wheather user has given the destination file or not

 Fill with sample filenames

if not create it
*/