#include "flogger/flogger.h"
int main()
{
    const char* server_log_filename = "log.txt";
    alignas(4) char server_log_buffer[256] = {0}; //flogger will prepend a time tag and append new line to each string
    Flogger server_log(const_cast<char*>(server_log_filename), 1024*20, server_log_buffer, sizeof(server_log_buffer)); //20KB log file

    const char* example_log_line = "This is a wonderful log file";
    server_log.log("This is a test entry");
    while (server_log.log(example_log_line) >= 0);
    return 0;
}
