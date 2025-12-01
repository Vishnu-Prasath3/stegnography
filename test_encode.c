#include <stdio.h>
#include<string.h>
#include "encode.h"
#include "types.h"

int main(int argc,char *argv[])
{
    EncodeInfo encInfo;

    uint img_size;
    
    int result = check_operation_type(argv);

    if(result == e_encode){
        // encoding
    }
     else if(result == e_decode){
        // decoding
    }
    
    read_and_validate_encode_args(argv, &encInfo);

    open_files(&encInfo);
    
    check_capacity(&encInfo);

    return 0;

}

OperationType check_operation_type(char *argv[]){

    // printf("%s",argv[1]);

    if(strcmp(argv[1],"-e") == 0){
         //pointer comparing with the string
        // printf("we are enterring in the e- encode");
        
        return e_encode;

    }

    else if(strcmp(argv[1],"-d") == 0){
        printf("we are enterring the value of e_decode");

        return e_decode;
    }

}