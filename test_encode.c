#include <stdio.h>
#include<string.h>
#include "encode.h"
#include "decode.h"
#include "types.h"

int main(int argc,char *argv[])
{
    EncodeInfo encInfo;
    uint img_size;

    DECODE_INFO decode_info;

     

    int result = check_operation_type(argv);

    if(result == e_encode){
        // encoding
        do_encoding(&encInfo);
    }
     else if(result == e_decode){
        
        do_decoding(decode_info,argv);

    }
    
    return 0;

}

OperationType check_operation_type(char *argv[]){

    // printf("%s",argv[1]);

    if(strcmp(argv[1],"-e") == 0){
    
        
        return e_encode;

    }

    else if(strcmp(argv[1],"-d") == 0){
        
        printf("we are enterring the value of e_decode");


        

        return e_decode;
    }

}