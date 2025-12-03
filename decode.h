#include<stdio.h>
#include"encode.h"
#include "common.h"
#include "types.h"

typedef struct _DECODE_INFO{

/*src image */ 
char *src_file_name;
FILE *stego_bmp;

/*output text file*/
char *output_filename;
FILE *output_file;


}DECODE_INFO;


Status check_operation( );

Status read_and_validation();

Status do_decoding(DECODE_INFO decode_info,char *argv[]);

Status open_files();

Status decode_magic_string();

Status file_extn_size();

Status secret_files_size();

Status secret_file_size();

Status secret_file_data();

