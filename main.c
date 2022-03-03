#include <stdio.h>

#include "logger.h"

int main () {
	DEF_LOGFILE("text.txt");

	// LOG("buffer %s", "lol");
	TAB_SET (4);
	LOG("-$debug version-%s\n%s", "0.1.0f", " -Header of debugger: This is first version of mchl-logger");
	TAB_SET (4);
	LOG("-string with offset 4*tab");

	TAB_SET (2);
	LOG("-string with offset 2*tab");


	CLOSE_LOG ();
	return 0;
}