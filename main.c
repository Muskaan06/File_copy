#include "include/config.h"
#include "include/dir_opr.h"
#include "include/file_opr.h"

void file_distributor_bot(const char *src_working_dir,
			  const char *dst_working_dir);

void main(){


	while(1){

		// This file distributor bot wake up every 5 ms
		// and checks if any file exist then copy it to 
		// the respective directories.
		printf("\nTask hunting started");
		file_distributor_bot(SRC_WORKING_DIR,DST_WORKING_DIR);
		printf("\nTask completed.");
		sleep(5);

	}

}

void file_distributor_bot(const char *src_working_dir,
                          const char *dst_working_dir){


	dir_opr_err_t dir_err;
	file_opr_err_t file_err;
	DIR *dir;
	int dst_dir_len;
	char *filename;
	char *file_extension;
	char *src_path;
	char *dst_path;

	dst_dir_len = strlen(dst_working_dir);

	filename = (char *)malloc(FILE_OPR_MAX_FILE_NAME_LEN);
	if(filename == NULL)
		return;
	
	file_extension = (char *)malloc(FILE_OPR_MAX_FILE_NAME_LEN);
	if(file_extension == NULL){

		free(filename);
		return;

	}

	src_path = (char *)malloc(DIR_OPR_MAX_DIR_PATH_LEN);
	if(src_path == NULL){

		free(filename);
		free(file_extension);
		return;

	}

	dst_path = (char *)malloc(DIR_OPR_MAX_DIR_PATH_LEN);
	if(dst_path == NULL){

		free(filename);
		free(file_extension);
		free(src_path);
		return;

	}

	
    // This function reads file from the src_working_dir 
	// and copies it into the dst_working_dir/file_extension 
	// based on the file extention.
    // If file extension directory does not exist in dst_working_dir 
    // then it creates else just copies to the same dir.
	
	// Open directory.
	dir = open_dir(src_working_dir);
	printf("\nDir name: %s",src_working_dir);
	if(dir == NULL){

		printf("\nDirectory accesss failed.");
		return;

	}

	// Read file from directory.
	while(1){

		memset(filename,0,FILE_OPR_MAX_FILE_NAME_LEN);
		file_err = get_file_from_dir(dir,&filename);
		if(file_err == FILE_OPR_SUCCESS){


			// Got file name.
			// Get file extension
			memset(file_extension,0,FILE_OPR_MAX_FILE_NAME_LEN);
			file_err = get_file_extension(filename,&file_extension);
			if(file_err == FILE_OPR_SUCCESS){


				// File extension received.
				// Reset variable.
				memset(dst_path,0,DIR_OPR_MAX_DIR_PATH_LEN);
				create_dir_path(dst_working_dir,file_extension,&dst_path);	
				
				// Check whether directory exist or not.
				dir_err = is_dir_exist(dst_path); 
				if(dir_err == DIR_OPR_DIR_NOT_EXIST_ERR){

					// Create directory.
					// if fails then simple return with error message.
					dir_err = create_dir(dst_path);
					if(dir_err != DIR_OPR_SUCCESS){
					
						printf("\n Directory creation error. Error Number: %d",dir_err);
						break;

					}

				}

				// At this point directory is created or already exist.
				// Now copy file from src to dst.
				// For that set src and dst path.
				memset(src_path,0,DIR_OPR_MAX_DIR_PATH_LEN);
				set_file_path(src_working_dir,filename,&src_path);

				// dst path already contains file extension directory information.
				// just append file name.
				set_file_path(dst_path,filename,&dst_path);

				// Copy file from src directory to destination directory.
				file_err = file_copy(src_path,dst_path);
				if(file_err != FILE_OPR_SUCCESS){ 
					
					// Get out and try next time again.
					printf("\n File copy error. Error Number: %d",file_err);
					break;
					
				}else	// delete file from src directory.
					delete_file(src_path);
					
				// Go back and read more file from the 
				continue;

			}else{

				// File extension retrival error.
				printf("\n File extension retrival error. Error Number: %d",file_err);
				break;

			} // File extension error.

		} // No file name received from read directory function call/ or error occured.
		
		break;

	} // End of reading files from opened directory.

	// Free allocated memories.
	free(filename);
	free(file_extension);
	free(src_path);
	free(dst_path);

	// Close directory.
	if(dir != NULL)
		close_dir(dir);
	

}



