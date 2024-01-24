#pragma once

class LogmessageFormatter {
public:
	char front_tag_startsymbol_;
	char front_tag_endsymbol_;
	bool front_tag_use_date_;
	bool front_tag_use_time_;
	bool append_new_line_;
	char new_line_char_[2];
	char* output_buffer_;
	int output_buffer_len_;
public:
	LogmessageFormatter();
	int format(const char* inputstr, int strlength);
	int format(const char* inputstr, int strlength, bool prepend_tag_flag, bool append_newline_flag);

	int intdecimaltoascii(int* inputnumber, char* outputstr, bool nullterm);
	
	int prepend_tag(); //returns length of output
	int copy_payload(const char* inputstr, char* outputstr, int strlength);
	int append_new_line(char* newline_output);

};