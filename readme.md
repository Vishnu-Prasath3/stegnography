### ### ### ### ### ### ### ### cli command ### ### ### ### ### ### ### ### 
./a.out -e beautiful.bmp secret.txt code.bmp

## 1. open file

## 2. check capacity

## 3.copy .bmp header

## 4.encode magic string

# 5pcs of the secret data and they were #
 --char ' #* ' <--{magic string} 2bytes
 
 1. 4 integer- 2char

 2. secret file size extension-4-(int) (.txt)

 3. secret file exten(.txt) - char

 4. (4char) secret file ( size-25 integer=>(memnber) ) characters

 5. secret data




### 1st check the [argc] in the main function arguement 

<!-- check the arguement count equal 4 -->

<!-- check for [ ./a.out .bmp .txt stego.bmp ] -->

if(argc ==4 ){

    @__continue
}

### store the image in the ->stego-image


### do_encoding
 => open files
 
 =>check capacity
 
 =>copy_bmp_header
 
 =>encode_magic_string
 
 =>encode_secret_file_extn_size

 =>encode_secret_file_extn

 <!-- use rewind() to se the pointer position to starting point -->