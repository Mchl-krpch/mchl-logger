#include <stdio.h>

enum class output:char {
	blocked =    0,
	in_console = 1,
	in_file    = 2,
	everywhere = 3,
};

struct DOCCER {
	FILE    *file = nullptr;
	unsigned tabs = 0;
	unsigned skip = 0;
};

extern const DOCCER *const Logger;
output mode (const char *format);


#define LOG(format, ...) logger_write (Logger, format, ##__VA_ARGS__)

void logger_write (const DOCCER *Logger, const char* format, ...);
void TAB_INC  ();
void TAB_DEC  ();
void TAB_SET  (unsigned tabs);
void DEF_FILE (const char *name);
void CLOSE_FILE ();
