#pragma once

#include "logmessage_formatter.h"
#include "logfilemanager.h"
class Flogger {
private:
	BasicFileLogger file_handler_;
	LogmessageFormatter formatter_;
public:
	Flogger(char* logfile_path, unsigned long long logfile_maxlen, char* logmessage_buffer, int bufferlen);
	int log(char* message);
	int log(char* message, int msglen);
	int log(const char* message);
	int log(const char* message, int msglen);
};