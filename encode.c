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
    // the pointer moved to 18
    fseek(fptr_image, 18, SEEK_SET);

    // Read the width (an int)
    fread(&width, sizeof(int), 1, fptr_image);
    // printf("width = %u\n", width);

    // Read the height (an int)
    fread(&height, sizeof(int), 1, fptr_image);
    // printf("height = %u\n", height);

    rewind(fptr_image);
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
        return e_failure;
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
        return e_failure;
    }

    /*
     if no name given in cli for destination file ?
        then create one 

    */ 

    // if no name assigned to the destination image then assign name
    if( argv[4] == NULL){

        encInfo->fptr_stego_image = fopen("code.bmp","w+");
        encInfo->stego_image_fname = "code.bmp";

    }

    else if(strcmp(strstr(argv[4], ".bmp"), ".bmp") == 0)
    {
        // assigning destination image name
        encInfo->stego_image_fname = argv[4];
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
    
    
    encInfo->image_capacity = get_image_size_for_bmp( encInfo->fptr_src_image);

    // printf("The image capacity of the image were %ld",encInfo->image_capacity);
        if( encInfo->image_capacity  >   ((54+4+4+4+size_of_secret)*8)   )
      {
         printf("Enough Capacity\n starting the encoding process\n");
         copy_bmp_header(encInfo->fptr_src_image,  encInfo->fptr_stego_image);
         return e_success;
     }
        else
    {
        printf("Not Enough Capacity");
        return e_failure;
    }
    
    // printf("The length of the  sorce img capacity %ld The calculated lenth of the size wewre %ld ",encInfo->image_capacity,size_of_secret);
    
    return e_success;

}
uint get_file_size(FILE *fptr)
{
	fseek(fptr, 0, SEEK_END);
	return ftell(fptr);
}


Status copy_bmp_header(FILE *fptr_src_image, FILE *fptr_dest_image)
{

    // fread()number of bytes read successfully
    fseek(fptr_src_image, 0, SEEK_SET);
    char str[54];
    fread(str,sizeof(char),54,fptr_src_image);
    fwrite(str,sizeof(char),54,fptr_dest_image);
    return e_success;
}

Status encode_byte_to_lsb(char data, char *image_buffer){

    int i;
    for(i=0;i<8;i++)
    {
        image_buffer[i]=(image_buffer[i] & 0xFE)|((data >> (7 - i)) & 1);       /////
    }
}

Status encode_magic_string( char *magic_string, EncodeInfo *encInfo)
{
    encode_data_to_image(magic_string, strlen(magic_string), encInfo->fptr_src_image, encInfo->fptr_stego_image);
    return e_success;
}

Status encode_data_to_image(char *data, int size, FILE *fptr_src_image, FILE *fptr_stego_image){
    int i;
    for(i=0;i<size;i++)
    {
        char image_buffer[8];
        fread(image_buffer,8,1,fptr_src_image);
        encode_byte_to_lsb(data[i], image_buffer);
        fwrite(image_buffer,8,1,fptr_stego_image);
    }
    return e_success;
}

Status encode_size_to_lsb(int size, char *image_buffer)//GENERIC
{
	int i;
	for(i=0;i<32;i++)
	{
		image_buffer[i]=(image_buffer[i] & 0xFE)|((size >> (31 - i)) & 1);
	}
}


Status copy_remaining_img_data(FILE *fptr_src_image, FILE *fptr_dest_image)
									
{
	char ch;
	while(fread(&ch,1,1,fptr_src_image)>0)
	{
		fwrite(&ch,1,1,fptr_dest_image);
	}
	return e_success;
}

Status encode_secret_file_size(long file_size, EncodeInfo *encInfo){
    char str[32];
    fread(str, 32, 1, encInfo -> fptr_src_image);
    encode_size_to_lsb(file_size,str);
    fwrite(str, 32, 1, encInfo -> fptr_stego_image);
    return e_success;
}

Status encode_secret_file_extn(const char* file_ext, EncodeInfo* encInfo)
{
    file_ext = ".txt";
    encode_data_to_image(file_ext, strlen(file_ext), encInfo -> fptr_src_image, encInfo -> fptr_stego_image, encInfo);
    return e_success;
}



Status do_encoding(EncodeInfo *encInfo)
{
	if (open_files(encInfo) == e_success)
	{
		printf("Open Files is a Success\n");
		if(check_capacity(encInfo)==e_success)
		{
			printf("Check capacity is Success\n");
			if(copy_bmp_header(encInfo -> fptr_src_image, encInfo -> fptr_stego_image)==e_success)
			{
				printf("Copied bmp header successfully\n");
				if(encode_magic_string(MAGIC_STRING, encInfo) == e_success)
				{
					printf("Encoded magic string successfully\n");
					strcpy(encInfo -> extn_secret_file, strstr(encInfo -> secret_fname,"."));
					//printf("%s\n",encInfo -> extn_secret_file);
					if(encode_extn_size(strlen(encInfo -> extn_secret_file),encInfo) == e_success)
					{
						printf("Encoded the extn_size\n");
						if(encode_secret_file_extn( encInfo -> extn_secret_file , encInfo) == e_success)
						{
							printf("Encoded the secret_file extn\n");
							if(encode_secret_file_size( encInfo -> size_secret_file , encInfo) == e_success)
							{
								printf("Encoded the secret_file Size\n");
								if(encode_secret_file_data(encInfo)==e_success)
								{
									printf("Encoded the secret_file Data\n");
									if(copy_remaining_img_data(encInfo -> fptr_src_image, encInfo -> fptr_stego_image)==e_success)
									{
										printf("Copied Remainaing Data\n");					
									}
									else
									{
										printf("Failure to Copy Remainaing Data \n");
										return e_failure;
									}	
								}//
								else
								{
									printf("Failure to encode secret file Data\n");
									return e_failure;
								}						
							}
							else
							{
								printf("Failure to encode secret file Size\n");
								return e_failure;
							}							
						}
						else
						{
							printf("Failure to encode secret file extn\n");
							return e_failure;
						}			
					}
					else
					{
						printf("Failure to encode extn_size\n");
						return e_failure;
					}		
				}
				else
				{
					printf("Failure to Encode Magic String\n");
					return e_failure;
				}
			}
			else
			{
				printf("failure to copy bmp header \n");
				return e_failure;/////
			}
		}
		else
		{
			printf("Check capacity is Failure\n");
			return e_failure;
		}
	}
	else
	{
		printf("Open Files is a Failure\n");
		return e_failure;
	}
	return e_success;
}