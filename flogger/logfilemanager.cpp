#include "logfilemanager.h"

#include <cstdio>
#include <sys/stat.h>

#pragma warning( disable : 4996)

BasicFileLogger::BasicFileLogger(){
	logfile_path_ = nullptr;
	logfile_maxlines_per_file_ = 0;
	logfile_maxfilesize_bytes_per_file_ = 0;
}

int BasicFileLogger::write(const char* new_log_entry, int entry_length) {
	//verify params
	if ((logfile_path_ == nullptr) || (entry_length < 1)) return -1;


	//check if file exists
	if (!file_exists()) {
		//if not, create file and all folders it's in
		if (!file_create()) {
			return -2; //signal error
		};
	}

	//check if there is enough room in the log file
	unsigned long long last_log_file_bytesize;
	unsigned long long last_log_file_linesize;

	if (logfile_maxfilesize_bytes_per_file_ == 0) goto log_file_bytesize_check_skip;
	last_log_file_bytesize = file_bytes();
	if ((last_log_file_bytesize + entry_length) > logfile_maxfilesize_bytes_per_file_) {
		return -3;
	}
log_file_bytesize_check_skip:

	if (logfile_maxlines_per_file_ == 0) goto log_file_maxlines_check_skip;
	last_log_file_linesize = file_lines();
	if ((last_log_file_linesize + 1) > logfile_maxlines_per_file_) {
		return -4;
	}
log_file_maxlines_check_skip:

	if (!file_append_charstring(new_log_entry, entry_length)) {
		return -5;
	}
	
	return entry_length;

}

bool BasicFileLogger::file_exists()
{

	if (FILE* file = fopen(logfile_path_, "r")) {
			fclose(file);
			return true;
	}
	else {
			return false;
	}
}

bool BasicFileLogger::file_create()
{
	FILE* fptr;
	fptr = fopen(logfile_path_, "w");
	if (fptr == NULL) return false;
	fclose(fptr);
	return true;
}

unsigned long long BasicFileLogger::file_lines()
{
	FILE* fp = fopen(logfile_path_, "r");
	if (fp == NULL)
	{
		return 0;
	}

	int character;    // this must be an int
	int linecount = 0;

	for (character = getc(fp); character != EOF; character = getc(fp))
		if (character == '\n') // Increment count if this character is newline 
			linecount++;
	linecount++;
	fclose(fp);
	return linecount;
}

unsigned long long BasicFileLogger::file_bytes()
{
	struct stat file_status;
	if (stat(logfile_path_, &file_status) < 0) {
		return -1;
	}
	return file_status.st_size;
}

bool BasicFileLogger::file_append_charstring(const char* newstr, int newstrlen)
{
	FILE* fp = fopen(logfile_path_, "a");
	if (fp == NULL)
	{
		return false;
	}
	
	//write the string itself
	if (newstr[newstrlen - 1] == '\0') newstrlen--; //ignore null terminator
	size_t writtenchars = fwrite(newstr, 1, newstrlen, fp);
	fclose(fp);
	if (writtenchars != newstrlen) {
		return false;
	}
	return true;
}
