#include <assert.h>
#include <stdio.h>
#include <stdarg.h>

#include "test.h"

DOCCER Logger2 = {0, 0};
const DOCCER *const Logger = &Logger2;


void TAB_INC    ()                 {Logger2.tabs++;}
void TAB_DEC    ()                 {Logger2.tabs++;}
void TAB_SET    (unsigned tabs)    {Logger2.tabs = tabs;}
void DEF_FILE   (const char *name) {Logger2.file = fopen (name, "w");}
void CLOSE_FILE () {if (Logger2.file == nullptr) {return;}	else {fclose (Logger2.file);}}

void logger_write (const DOCCER *doc, const char* format, ...) {
	assert (doc);
	va_list ap;
	va_start (ap, format);

	// write info in file
	switch (mode (format)) {
		case output::in_console: {
			for (unsigned tab = 0; tab < Logger2.tabs; tab++) {
				fprintf (stdout, "\t");
			}
			vfprintf (stdout, format + Logger2.skip, ap);
			break;
		}
		case output::in_file: {
			for (unsigned tab = 0; tab < Logger2.tabs; tab++) {
				fprintf (Logger2.file, "\t");
			}
			vfprintf (Logger2.file, format + doc->skip, ap);
			break;
		}
		case output::everywhere: {
			for (unsigned tab = 0; tab < Logger2.tabs; tab++) {
				fprintf (stdout, "\t");
			}
			vfprintf (stdout, format + Logger2.skip, ap);
			for (unsigned tab = 0; tab < Logger2.tabs; tab++) {
				fprintf (Logger2.file, "\t");
			}
			vfprintf (Logger2.file, format + doc->skip, ap);
			break;
		}
		case output::blocked:{break;}
		default: {
			printf ("\t-$blocked");
			break;
		}
	}

	fclose (Logger2.file);
	va_end (ap);
	fflush(doc->file);
	return;
}

output mode (const char *format) {
	if (*format == '\a' && *(format + 1) != '\f') {
		// printf ("\t-$it is console output.mode\n");
		Logger2.skip += 1;
		return output::in_console;
	}

	if (*format == '\f' && *(format + 1) != '\a' && Logger2.file != nullptr) {
		// printf ("\t-$it is file output.mode\n");
		Logger2.skip += 1;
		return output::in_file;
	}

	if ((*format == '\f' && *(format + 1) == '\a') ||
		(*format == '\a' && *(format + 1) == '\f') ) {
		if (Logger2.file != nullptr) {
			// printf ("\t-$it is costom output.mode\n");
			Logger2.skip += 2;
			return output::everywhere;
		}
		else {
			// printf ("-$you haven't logfile, message will be written in console only\n");
			Logger2.skip += 2;
			return output::in_console;
		}
	}

	printf ("-$you haven't logfile. output in file is blocked\n");
	return output::blocked;
}

