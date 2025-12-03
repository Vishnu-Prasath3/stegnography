#include<stdio.h>
#include<string.h>
#include "decode.h"
#include "types.h"

read_and_validation(char *input[],DECODE_INFO decode){


    if(strcmp(input[2],".bmp")== 0){

        // name asigning
        printf("The file name were assining is %s",input[2]);
        
        decode.src_file_name=input[2];

    }
    else
    {
        printf(stderr,"Invalid file extension .bmp");
        return e_failure;
    }

    if(input[3] != NULL){
            
        decode.output_filename = strtok(input[3],".");
         printf("THe output filename is %s",decode.output_filename);
    }

}


Status do_decoding(DECODE_INFO decode_info,char *argv[]){

read_and_validation(argv,decode_info);

}
