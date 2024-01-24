#include "logmessage_formatter.h"
#include <ctime>

#include <iostream>
#pragma warning( disable : 4996)


LogmessageFormatter::LogmessageFormatter()
{
	front_tag_startsymbol_ = '\0';
	front_tag_endsymbol_ = '\0';
	front_tag_use_date_ = false;
	front_tag_use_time_ = false;
	append_new_line_ = false;
	new_line_char_[0] = '\0';
	new_line_char_[1] = '\0';
	output_buffer_ = nullptr;
	output_buffer_len_ = 0;
}

int LogmessageFormatter::format(const char* inputstr, int strlength)
{
	if (inputstr[strlength - 1] == '\0') strlength--; //ignore null terminator
	int outputlen = 0;
	if (front_tag_use_date_ || front_tag_use_time_) {
		outputlen += prepend_tag();
	}
	outputlen += copy_payload(inputstr, &output_buffer_[outputlen], strlength);
	if (append_new_line_) {
		outputlen += append_new_line(&output_buffer_[outputlen]);
	}
	
	return outputlen;
}

int LogmessageFormatter::format(const char* inputstr, int strlength, bool prepend_tag_flag, bool append_newline_flag)
{
	if (inputstr[strlength - 1] == '\0') strlength--; //ignore null terminator
	int outputlen = 0;
	if (prepend_tag_flag && (front_tag_use_date_ || front_tag_use_time_)) {
		outputlen += prepend_tag();
	}
	outputlen += copy_payload(inputstr, &output_buffer_[outputlen], strlength);
	if (append_newline_flag) {
		outputlen += append_new_line(&output_buffer_[outputlen]);
	}

	return outputlen;
}

int LogmessageFormatter::prepend_tag()
{

	int output_index = 0;
	time_t now;
	tm* ltm;

	if (front_tag_use_date_ || front_tag_use_time_) {
		output_buffer_[output_index] = front_tag_startsymbol_;
		output_index++;
	}
		
	now = time(0);
	ltm = localtime(&now);
		if (front_tag_use_date_) {

			int current_year = 1900 + ltm->tm_year;
			int current_month = 1 + ltm->tm_mon;
			int current_day = ltm->tm_mday;

			if (current_day < 10) {
				output_buffer_[output_index] = '0';
				output_index++;
			}
			output_index += intdecimaltoascii(&current_day, &output_buffer_[output_index], false);

			output_buffer_[output_index] = '.';
			output_index++;

			if (current_month < 10) {
				output_buffer_[output_index] = '0';
				output_index++;
			}
			output_index += intdecimaltoascii(&current_month, &output_buffer_[output_index], false);

			output_buffer_[output_index] = '.';
			output_index++;

			output_index += intdecimaltoascii(&current_year, &output_buffer_[output_index], false);

			if (front_tag_use_time_) {
				output_buffer_[output_index] = ' ';
				output_index++;
			}

		}

		if (front_tag_use_time_) {
			int current_hour = ltm->tm_hour;
			int current_minute = ltm->tm_min;
			int current_second = ltm->tm_sec;

			if (current_hour < 10) {
				output_buffer_[output_index] = '0';
				output_index++;
			}
			output_index += intdecimaltoascii(&current_hour, &output_buffer_[output_index], false);

			output_buffer_[output_index] = ':';
			output_index++;

			if (current_minute < 10) {
				output_buffer_[output_index] = '0';
				output_index++;
			}
			output_index += intdecimaltoascii(&current_minute, &output_buffer_[output_index], false);

			output_buffer_[output_index] = ':';
			output_index++;

			if (current_second < 10) {
				output_buffer_[output_index] = '0';
				output_index++;
			}
			output_index += intdecimaltoascii(&current_second, &output_buffer_[output_index], false);
		}

		
		if (front_tag_use_date_ || front_tag_use_time_) {
			output_buffer_[output_index] = front_tag_endsymbol_;
			output_index++;
			output_buffer_[output_index] = ' ';
			output_index++;
		}
		
		
	

		return output_index;
}

int LogmessageFormatter::copy_payload(const char* inputstr, char* outputstr, int strlength)
{
	int output_index = 0;
	for (int i = 0; i < strlength; i++) {
		outputstr[output_index] = inputstr[i];
		output_index++;
	}

	return output_index;
}

int LogmessageFormatter::intdecimaltoascii(int* inputnumber, char* outputstr, bool nullterm) {
	//how many digits the number has
	int digitlength = 0;
	int int_temp = *inputnumber;
	bool input_is_negative = int_temp < 0;
	if (input_is_negative) int_temp = -int_temp;
	int int_buildtemp = 0;
	if (int_temp == 0) digitlength = 1;
	while (int_temp != 0) {
		int_buildtemp += (10 * digitlength) * (int_temp % 10);
		int_temp = int_temp / 10;
		digitlength++;
	}

	//print to output
	int printindex = 0;
	if (input_is_negative) {
		outputstr[printindex] = '-';
		printindex++;
	}

	int_temp = *inputnumber;
	if (input_is_negative) int_temp = -int_temp;

	for (int i = digitlength; i > 0; i--) {
		int digit;
		int divisor = 1;

		for (int j = 0; j < i - 1; j++) {
			divisor *= 10;
		}
		digit = (int_temp / divisor) % 10;

		outputstr[printindex] = digit + 0x30; //convert decimal digit to ascii character
		printindex++;
	}
	if (nullterm) {
		outputstr[printindex] = '\0';
		printindex++;
	}

	return printindex;

}

int LogmessageFormatter::append_new_line(char* newline_output)
{
	if (append_new_line_) {
		if (new_line_char_[0] == '\0') return 0;
		newline_output[0] = new_line_char_[0];
		if (new_line_char_[1] == '\0') return 1;
		newline_output[1] = new_line_char_[1];
		return 2;
	}
	return 0;
}

