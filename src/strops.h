#ifndef __STROPS_H
#define __STROPS_H

// strips all leading/trailing whitespace characters from 's' and returns it.
char *strstrip(char *s);

// returns the number of occurrences of 'c' in 's'.
int strchrcnt(const char *s, int c);

// splits 's' by the provided delimiter, and stores the result in 'res'; 'res' will be null-terminated.
void strsplit(char *s, const char *delim, char **res);

#endif
