#ifndef SRC_LOG_H
#define SRC_LOG_H

__attribute__((format(printf, 2, 3)))
void logprint(char *type, char *format, ...);

#endif
