#include <stdarg.h>
#include <stdio.h>

// Just wrapping printf for now.
void logprint(char *type, char *format, ...)
{
    printf("%s :: ", type);
    
    va_list args;
    va_start(args, format);
    vprintf(format, args);
    va_end(args);
}
