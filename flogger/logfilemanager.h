#ifndef _ELLECTROID_LOG_FILE_MANAGER_H_
#define _ELLECTROID_LOG_FILE_MANAGER_H_

struct BasicFileLogger{
public:
	/* General file management */
	const char* logfile_path_; //relative path with file name, creates folders and file if doesn't exist
	unsigned long long logfile_maxlines_per_file_; //doesn't write if limit reached, 0=unlim
	unsigned long long logfile_maxfilesize_bytes_per_file_; //doesn't write if limit reached, 0=unlim

public:
	BasicFileLogger();
	int write(const char* new_log_entry, int entry_length); //returns number of characters written

private:
	//internal helper functions
	bool file_exists();
	bool file_create();
	unsigned long long file_lines();
	unsigned long long file_bytes();
	bool file_append_charstring(const char* newstr, int newstrlen);

};


















#endif //_ELLECTROID_LOG_FILE_MANAGER_H_
