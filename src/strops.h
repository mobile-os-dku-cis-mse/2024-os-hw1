#ifndef __STROPS_H
#define __STROPS_H

#include <sys/types.h>

// returns the number of occurrences of 'c' in 's'.
size_t strchrcnt(const char *s, int c);

// splits 's' by the delimiter 'c', and stores the result in 'res'.
size_t strchrsplit(char *s, int c, const char **res);

#endif
