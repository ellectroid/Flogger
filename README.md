# Flogger
File logger - minimalist log file utility

The purpose of this mini-library is to allow easy logging with minimal setup and configuration. Config & forget.
It's not intended to be the best/most feature rich/most efficient. It's intended to be easy to use. Due to its simplicity, it's also easily modifyable.

Useful properties:
- One trivially destructible object works with 1 log file (but configurable/reconfigurable at runtime, so it's possible to use more files if you really want)
- Writes const char*[] and char*[] strings, null terminated or with explicit length
- Returns integers with error codes, so error events can be handled (e.g. log file full, or out of memory for string formatting)
- Basic log file size limiter (optional, by file byte length or by number of lines in the log file)
- Autoformats input strings (prepends data and time tags - configurable, appends new line characters - configurable, you can set your own new line characters)
- Autoformatting memory buffer is provided by the user, use as much (little) memory as you see necessary

Example:
main.cpp: 
...
server_log.log("This is a test entry");
...

log.txt:
[dd.mm.yyyy hh:mm:ss] This is a test entry[new line character(s) here]

License: Unlicense. It's just some code. I don't care what you do with it.
