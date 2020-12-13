#include <stdio.h>
#include<stdlib.h>
#include<string.h>
#define FILE_READ_ERR 0
#define FILE_READ_SUCCESS 1
#define FILE_OPEN_ERR 3
unsigned char read_file(const char *input_file);
int main(int argc, char** argv){
    
    unsigned char status;
    char src[256];
    
    if(argc <  2){
        
        printf("\ninvalid input");
        exit(0);
        
    }
    
    strcpy(src,argv[1]);
    
    status =read_file(src);
    if(status == FILE_READ_SUCCESS)
        printf("\nFile display successfully");
    else
        printf("\nOperation failed. Err %d",status);
    
    return(0);
    
}

unsigned char read_file(const char *input_file){
    FILE *fp_input;
    char ch;
    int counter=0;
    
    fp_input = fopen(input_file,"rb");
    if(fp_input == NULL){
        
        printf("Unable to open file\n");
        return(FILE_OPEN_ERR);
        
    }
    printf("%d   ",counter);
    while(1){
        ch=fgetc(fp_input);
        
        if(ch==EOF)
            break;
        else if (ch=='\n'){
            counter++;
            printf("\n%d    ",counter);
        }
        else
            printf("%c",ch);
        
    }
    return(FILE_READ_SUCCESS);
    
}
