#ifndef _BIPL_CYBER_SECURITY_DIR_OPR_H_
#define _BIPL_CYBER_SECURITY_DIR_OPR_H_

#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>
#include<stdlib.h>
#include<dirent.h>
#include<string.h>

typedef enum{

	DIR_OPR_SUCCESS = 0,
	DIR_OPR_FAILED,
	DIR_OPR_CREATE_ERR,
	DIR_OPR_OPEN_ERR,
	DIR_OPR_DIR_NOT_EXIST_ERR,
	DIR_OPR_DIR_EXIST_ERR,
	DIR_OPR_UNKNOWN_ERR,
	DIR_OPR_INVALID_LEN_ERR

}dir_opr_err_t;

#define DIR_OPR_MAX_DIR_PATH_LEN 512
#define DIR_OPR_MAX_DIR_NAME_LEN 32

dir_opr_err_t is_dir_exist(const char *path);

dir_opr_err_t create_dir(const char *dir_path);

dir_opr_err_t create_dir_path(const char *dir_path,
			      const char *new_dir_name,
		              char **new_dir_path);

DIR *open_dir(const char *dir_path);

void close_dir(DIR *dir);

dir_opr_err_t get_file_from_dir(DIR *dir,
			       char **file);

#endif
