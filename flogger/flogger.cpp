#include "flogger.h"

Flogger::Flogger(char* logfile_path, unsigned long long logfile_maxlen, char* logmessage_buffer, int bufferlen)
{
	file_handler_.logfile_path_ = logfile_path;
	file_handler_.logfile_maxfilesize_bytes_per_file_ = logfile_maxlen;
	formatter_.output_buffer_ = logmessage_buffer;
	formatter_.output_buffer_len_ = bufferlen;

	//configure other params
    formatter_.front_tag_startsymbol_ = '[';
    formatter_.front_tag_endsymbol_ = ']';
    formatter_.front_tag_use_date_ = true;
    formatter_.front_tag_use_time_ = true;
    formatter_.append_new_line_ = true;

    //WINDOWS
    //logger_formatter.new_line_char_[0] = '\r';
    //logger_formatter.new_line_char_[1] = '\n';

    //LINUX & MACOS X, usually works with Windows too actually
    formatter_.new_line_char_[0] = '\n';
    formatter_.new_line_char_[1] = '\0';

}

int Flogger::log(char* message)
{
    int maxmsglen = formatter_.output_buffer_len_ - 24; //compensate for front tag and end of line
    int stringlength = 0;
    for (; stringlength < maxmsglen; stringlength++) {
        if (message[stringlength] == '\0') break;
    }
    int final_len = formatter_.format(message, stringlength);
    return file_handler_.write(formatter_.output_buffer_, final_len);
}

int Flogger::log(char* message, int msglen)
{
    int final_len = formatter_.format(message, msglen);
    return file_handler_.write(formatter_.output_buffer_, final_len);
}

int Flogger::log(const char* message) {
    int maxmsglen = formatter_.output_buffer_len_ - 24; //compensate for front tag and end of line
    int stringlength = 0;
    for (; stringlength < maxmsglen; stringlength++) {
        if (message[stringlength] == '\0') break;
    }
    int final_len = formatter_.format(message, stringlength);
    return file_handler_.write(formatter_.output_buffer_, final_len);
}
int Flogger::log(const char* message, int msglen) {
    int final_len = formatter_.format(message, msglen);
    return file_handler_.write(formatter_.output_buffer_, final_len);
}
