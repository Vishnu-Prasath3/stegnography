#include <stdio.h>
#include "encode.h"
#include "types.h"

int main()
{
    EncodeInfo encInfo;
    uint img_size;

    
    // Test open_files
    if (open_files(&encInfo) == e_failure)
    {
        printf("ERROR: %s function failed\n", "open_files" );
    	return 1;
    }
    else
    {
        printf("SUCCESS: %s function completed\n", "open_files" );
    }   
    
    // Test get_image_size_for_bmp
    img_size = get_image_size_for_bmp(encInfo.fptr_src_image);
    printf("INFO: Image size = %u\n", img_size);
    
int result =check_operation_type(*argv[]);

if(result == e_encode){

// encoding
read_and_validate_encode_args(*argv[],*encInfo);

}
else if(result == e_decode){
// decoding
}

    return 0;
}









OperationType check_operation_type(char *argv[]){

    printf("%c",argv[1]);
    if(argv[1] == '-e'){

        
        printf("we are enterring in the e- encode");
        
        return e_encode;
    }

    else if(argv[1] == '-d'){

        printf("we are enterring the value of e_decode");

        return e_decode;
    }

}

// Fill with sample filenames
// encInfo.src_image_fname = "beautiful.bmp";
// encInfo.secret_fname = "secret.txt";
// encInfo.stego_image_fname = "stego_img.bmp";
