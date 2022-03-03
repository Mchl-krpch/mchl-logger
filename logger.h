#ifndef _LOGGER_
#define _LOGGER_

#include <stdio.h>

enum mode {
	console = 0,
	file,
};

struct Log {
	unsigned outputMode = console;
	FILE    *file = nullptr;
	unsigned tabs = 0;
};

extern Log log;

void DEF_LOGFILE (const char* name);
void CLOSE_LOG ();

#define LOG(format, ...)\
	for (unsigned tab = 0; tab < log.tabs; tab++) {\
		fprintf (log.file, "\t");\
	}\
	fprintf (log.file, format, ##__VA_ARGS__);\
	fprintf (log.file, "\n")

void TAB_INC ();
void TAB_DEC ();
void TAB_SET (unsigned nTabs);

#endif