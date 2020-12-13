#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILE_RW_SUCCESS     0
#define FILE_OPEN_ERR       1
#define FILE_WRITE_ERR      2
#define FILE_READ_ERR       3
#define FILE_UNKNOWN_ERR    4

unsigned char copy_file(const char *input_file,
                        const char *output_file);

int main(int argc, char** argv){
    
    unsigned char status;
    char src[256];
    char dst[256];
    
    if(argc <  3){
        
        printf("\nUsage: input_file output_file");
        exit(0);
        
    }
    
    strcpy(src,argv[1]);
    strcpy(dst,argv[2]);
    
    status = copy_file(src,dst);
    if(status == FILE_RW_SUCCESS)
        printf("\nFile copied successfully");
    else
        printf("\nOperation failed. Err %d",status);
    
    return(0);
    
}


//Function to create the duplicate file.
unsigned char copy_file(const char *input_file,const char *output_file){
    
    char ch,ch1 = '\0';
    FILE *fp_input,*fp_output;
    
    fp_input = fopen(input_file,"rb");
    if(fp_input == NULL){
        
        printf("Unable to open file\n");
        return(FILE_OPEN_ERR);
        
    }
    
    fp_output = fopen(output_file,"rb+");
    if(fp_output == NULL){
        
        // Close already open file.
         printf("Unable to open file\n");
        return(FILE_OPEN_ERR);
        
    }
    
    // Both read and write files are opened successfully.
    
    while(1){
        
        ch1 = fgetc(fp_output);
        if(ch1==EOF){
            ch=fgetc(fp_input);
            while(1){
                if(ch==EOF)
                    break;
                else
                    fputc(ch,fp_output);
            }
            break;
        }
        else
            continue;
        
    }
    
    fclose(fp_output);
    fclose(fp_input);
    return(FILE_RW_SUCCESS);
    
}
