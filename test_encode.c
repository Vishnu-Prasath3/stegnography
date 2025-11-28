#include <stdio.h>
#include<string.h>
#include "encode.h"
#include "types.h"

int main(int argc,char *argv[])
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
    
int result =check_operation_type(argv);

if(result == e_encode){

// encoding
read_and_validate_encode_args(argv, &encInfo);

}
else if(result == e_decode){
// decoding
}

    return 0;
}

OperationType check_operation_type(char *argv[]){

    printf("%s",argv[1]);
    if(strcmp(argv[1],"-e") == 0){ //pointer comparing with the string
        printf("we are enterring in the e- encode");
        
        return e_encode;
    }

    else if(strcmp(argv[1],"-d") == 0){
        printf("we are enterring the value of e_decode");

        return e_decode;
    }

}
