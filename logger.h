#include <stdio.h>

enum class output:char {
	blocked =    0,
	in_console = 1,
	in_file    = 2,
	everywhere = 3,
};

struct Logger {
	FILE    *file = nullptr;
	unsigned tabs = 0;
	unsigned skip = 0;
};

extern Logger* globalBase;

#define LOG_SPLIT() LOG("---------------------------\n");
#define LOG(format, ...) logger_write (globalBase, format, ##__VA_ARGS__)

output mode (Logger *doc, const char *format);
void logger_write (Logger *Logger, const char* format, ...);
void TAB_INC  ();
void TAB_DEC  ();
void TAB_SET  (unsigned tabs);
void DEF_FILE (const char *name);
void CLOSE_FILE ();
void logger_close_file();
