#ifndef _BIPL_CYBER_SECURITY_FILE_OPR_H_
#define _BIPL_CYBER_SECURITY_FILE_OPR_H_

#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>

typedef enum{

	FILE_OPR_SUCCESS = 0,
	FILE_OPR_FAILED,
	FILE_OPR_CREATE_ERR,
	FILE_OPR_OPEN_ERR,
	FILE_OPR_FILE_NOT_EXIST_ERR,
	FILE_OPR_FILE_EXIST_ERR,
	FILE_OPR_UNKNOWN_ERR,
	FILE_OPR_INVALID_LEN_ERR

}file_opr_err_t;

#define FILE_OPR_MAX_FILE_NAME_LEN 	32

#define FILE_OPR_MAX_CMD_LEN 		512

file_opr_err_t is_file_exist(const char *path);

file_opr_err_t file_copy(const char *src_path,
                         const char *dst_path);

file_opr_err_t get_file_extension(const char *file,
			     	 char **extension);

file_opr_err_t set_file_path(const char *path,
                             const char *filename,
                             char **fullpath);

file_opr_err_t delete_file(const char *path);

#endif
