#include "../include/file_opr.h"

// Public functions.

file_opr_err_t file_copy(const char *src_file,
			 const char *dst_file){

	int retval;;
	char cmd[FILE_OPR_MAX_CMD_LEN];
	file_opr_err_t err;


	memset(cmd,0,FILE_OPR_MAX_CMD_LEN);

	// Check inputs file path lenght.
	// if it exceeds then return with error.
	
	// Check whether file already exist or not.
	// if already exist return with status.
	err = is_file_exist(dst_file);
	if(err == FILE_OPR_FILE_EXIST_ERR)
		return(err);
	
	// Compose copy command. It only works in Linux or Mac.
	// Code is OS specific.
	sprintf(cmd,"cp %s %s",src_file,dst_file);
	
	retval = system(cmd);
	if(retval == 0)
		return(FILE_OPR_SUCCESS);
	else
		return(FILE_OPR_FAILED);


}


file_opr_err_t is_file_exist(const char *file){

	int retval;
	file_opr_err_t err;
	struct stat status;

	// Check if file already exist.
	// if already exist returns FILE_OPR_ALREADY_EXIST.

	// Get the file info
	// If file exist then it return 0 else some other value.
	retval = stat(file,&status);
	if(retval == 0)
		return(FILE_OPR_FILE_EXIST_ERR);
	else
		return(FILE_OPR_FILE_NOT_EXIST_ERR);

}


file_opr_err_t get_file_extension(const char *file,
                                 char **extension){

	
	char *file_ext = *extension;
	char *temp_ext = NULL;
	int len;

	// Validate 
	temp_ext = strrchr(file,'.');
	if(temp_ext == NULL)
		return(FILE_OPR_FAILED);
	else{

		len = strlen(temp_ext);
		strncpy(file_ext,&temp_ext[1],len-1);

	}	
	
	return(FILE_OPR_SUCCESS);	

}


file_opr_err_t set_file_path(const char *path,
			     const char *filename,
			     char **fullpath){

        int path_len;
        char *retpath = *fullpath;

        path_len = strlen(path);

        if(path[path_len-1] == '/')
                sprintf(retpath,"%s%s",path,filename);
        else
                sprintf(retpath,"%s/%s",path,filename);

        return(FILE_OPR_SUCCESS);

}

file_opr_err_t delete_file(const char *path){

	int retval;
	char cmd[FILE_OPR_MAX_CMD_LEN];
        file_opr_err_t err;

	memset(cmd,0,FILE_OPR_MAX_CMD_LEN);
	sprintf(cmd,"rm %s",path);
	retval = system(cmd);
	if(retval == 0)
		return(FILE_OPR_SUCCESS);
	else
		return(FILE_OPR_FAILED);

}

