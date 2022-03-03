#include <assert.h>
#include <stdio.h>
#include <stdarg.h>

#include "logger.h"

Log log = {NULL, 0};

void DEF_LOGFILE (const char* name) {
	assert (name);

	if (name == NULL) {
		log.file = NULL;
		return;
	}
	log.file = fopen(name, "w");
	return;
}

void CLOSE_LOG () {
	if (log.file != NULL) {
		fclose (log.file);
	}
}

void TAB_INC () {log.tabs++; return;}
void TAB_DEC () {log.tabs--; return;}
void TAB_SET (unsigned nTabs) {log.tabs = nTabs; return;}