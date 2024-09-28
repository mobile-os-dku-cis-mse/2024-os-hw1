//
// Created by user on 2024-09-19.
//

#include "string_tools.h"
#include <ctype.h>
#include <string.h>

/* AI Generated Code */

// Function to strip leading and trailing whitespace
void strip(char *str) {
    // Remove leading spaces
    char *start = str;
    while (isspace((unsigned char)*start)) {
        start++;
    }

    // Move stripped content to the beginning of the string
    memmove(str, start, strlen(start) + 1);

    // Remove trailing spaces
    char *end = str + strlen(str) - 1;
    while (end > str && isspace((unsigned char)*end)) {
        *end = '\0';
        end--;
    }
}

#ifdef TEST
int main() {
    char text[] = "   Hello, World!   ";
    strip(text);
    printf("%s\n", text);  // Output: 'Hello, World!'
    return 0;
}
#endif