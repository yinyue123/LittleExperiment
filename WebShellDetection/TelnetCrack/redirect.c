#include <stdarg.h>
#include <stdio.h>


/* Accodring to the user needs to be redirected to network, serial port */
void output_to_user(const char *format, ...)
{
	va_list ap;
	char buf[512];
	va_start(ap,format);
	vsprintf(buf,format,ap);
	va_end(ap);

	printf("%s",buf);
}



