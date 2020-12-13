#include "../include/dir_opr.h"

// Public functions.

DIR *open_dir(const char *dir_path){

	// Validate dir path.
	if(dir_path == NULL)
		return(NULL);

	//Is directory exist
	if(is_dir_exist(dir_path) == DIR_OPR_DIR_EXIST_ERR)
		return(opendir(dir_path));
	else
		return(NULL);

}

void close_dir(DIR *dir){
	
	if(dir == NULL)
		return;

	closedir(dir);

}

dir_opr_err_t get_file_from_dir(DIR *dir,
                                char **file){

	struct dirent *record;
	char *temp_file = *file;
	unsigned long len;
	unsigned char counter;

	while(1){

		record = readdir(dir);
		if(record == NULL)
			return(DIR_OPR_FAILED);

		if((strcmp(record->d_name,".") == 0) || (strcmp(record->d_name,"..") == 0))
			continue;
		
		break;	

	}

	if(record != NULL){
	
		// Allow only the vaild files
		len = strlen(record->d_name);
		for(counter = 0; counter < len; counter++)
			temp_file[counter]=record->d_name[counter];
		
		temp_file[len] = '\0';
		return(DIR_OPR_SUCCESS);

	}
	
	return(DIR_OPR_FAILED);

}

dir_opr_err_t create_dir_path(const char *dir_path,
			      const char *dir_name,
			      char **full_path){

	int dir_path_len;
	char *ret_path = *full_path;

	dir_path_len = strlen(dir_path);

	// Check whether dir_path name is end with backslash
	// if exist then don't add backslash at end else add.
	if(dir_path[dir_path_len-1] == '/')
		sprintf(ret_path,"%s%s",dir_path,dir_name);
	else
		sprintf(ret_path,"%s/%s",dir_path,dir_name);
	
	return(DIR_OPR_SUCCESS);

}

dir_opr_err_t create_dir(const char *dir_path){

	int retval;
	dir_opr_err_t err;

	
	// Check if directory already exist.
	// if already exist return success.
	err = is_dir_exist(dir_path);
	if(err == DIR_OPR_DIR_EXIST_ERR)
		return(DIR_OPR_SUCCESS);


	// if directory does not exist, create it.
	retval = mkdir(dir_path,0664);
	if(retval == 0)
		return(DIR_OPR_SUCCESS);
	else
		return(DIR_OPR_FAILED);


}

dir_opr_err_t is_dir_exist(const char *path){

	// It checks whether directory exist or not.
	// Using Stat API.

	struct stat status;
	int retval;

	retval = stat(path,&status);
	if(retval != -1){

		if(S_ISDIR(status.st_mode))
			return(DIR_OPR_DIR_EXIST_ERR);
		
	}

	return(DIR_OPR_DIR_NOT_EXIST_ERR);

}

	

	
