#include <assert.h>
#include <stdio.h>
#include <stdarg.h>

#include "logger.h"

Logger OBJ = {nullptr, 0, 0};
Logger *globalBase = &OBJ;

void TAB_INC    ()              {OBJ.tabs++;}
void TAB_DEC    ()              {OBJ.tabs++;}
void TAB_SET    (unsigned tabs) {OBJ.tabs = tabs;}
void CLOSE_FILE () {if (OBJ.file == nullptr) {return;}	else {fclose (OBJ.file);}}

void DEF_FILE   (const char *name) {
	assert (name);
	OBJ.file = fopen (name, "w");
	atexit (logger_close_file);
}

void logger_close_file() {
	Logger *log = globalBase;
	if(OBJ.file){
		fclose(OBJ.file);
	}
}

void logger_write (Logger *log, const char* format, ...) {
	assert (log);
	assert (format);
	va_list ap;
	va_start (ap, format);

		// write info in file
	switch (mode (log, format)) {
		case output::in_console: {
			for (unsigned tab = 0; tab < log->tabs; tab++) {
				fprintf (stdout, "\t");
			}
			vfprintf (stdout, format + log->skip, ap);
			break;
		}
		case output::in_file: {
			for (unsigned tab = 0; tab < log->tabs; tab++) {
				fprintf (log->file, "\t");
			}
			vfprintf (log->file, format + log->skip, ap);
			break;
		}
		case output::everywhere: {
			for (unsigned tab = 0; tab < log->tabs; tab++) {
				fprintf (stdout, "\t");
			}
			vfprintf (stdout, format + log->skip, ap);
			for (unsigned tab = 0; tab < log->tabs; tab++) {
				fprintf (log->file, "\t");
			}
			vfprintf (log->file, format + log->skip, ap);
			break;
		}
		case output::blocked:{break;}
		default: {
			printf ("\t-$blocked");
			break;
		}
	}

	va_end (ap);
	fflush(log->file);
	return;
}

output mode (Logger *log, const char *format) {
	assert (log);
	assert (format);
	if (*format == '\a' && *(format + 1) != '\f') {
		// printf ("\t-$it is console output.mode\n");
		log->skip += 1;
		return output::in_console;
	}

	if (*format == '\f' && *(format + 1) != '\a' && log->file != nullptr) {
		// printf ("\t-$it is file output.mode\n");
		log->skip += 1;
		return output::in_file;
	}

	if ((*format == '\f' && *(format + 1) == '\a') ||
		(*format == '\a' && *(format + 1) == '\f') ) {
		if (log->file != nullptr) {
			// printf ("\t-$it is costom output.mode\n");
			log->skip += 2;
			return output::everywhere;
		}
		else {
			// printf ("-$you haven't logfile, message will be written in console only\n");
			log->skip += 2;
			return output::in_console;
		}
	}
	if (log->file != nullptr) {
		return output::in_file;
	}
	else {
		return output::in_console;
	}
	printf ("-$you haven't logfile. output in file is blocked\n");
	return output::blocked;
}

