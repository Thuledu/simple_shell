#include "main.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/**
 * my_getline - Read characters from stdin and store them in a buffer.
 * Description: Reads characters from stdin and stores them in a 
 * buffer, until either a newline character is 
 * encountered /the maximum buffer size is reached.
 * Arguments:The buffer to store the characters in, and the maximum buffer size.
 * Returns:The number of bytes read, or -1 on failure.
 */
int my_getline(char *buffer, size_t max_size)
{
    static char internal_buffer[1024];
    static size_t buffer_index = 0;
    static size_t buffer_size = 0;

    int total_bytes = 0;
    int bytes_read = 0;

    while (1) {
        /* If the buffer is empty, read more data from stdin*/
        if (buffer_index >= buffer_size) {
            bytes_read = read(STDIN_FILENO, internal_buffer, sizeof(internal_buffer));
            if (bytes_read < 0) {
                return -1;
            } else if (bytes_read == 0) {
                /* End of file reached*/
                break;
            }
            buffer_index = 0;
            buffer_size = bytes_read;
        }

        /* Copy data from the internal buffer to the output buffer*/
        while (buffer_index < buffer_size && total_bytes < max_size) {
            char c = internal_buffer[buffer_index++];
            buffer[total_bytes++] = c;
            if (c == '\n') {
                /* End of line reached*/
                buffer[total_bytes] = '\0';
                return total_bytes;
            }
        }

        /* If the buffer is full and the end of file has not been reached,
         increase the buffer size and call my_getline() again*/
        if (total_bytes == max_size) {
            max_size *= 2;
            buffer = (char*)realloc(buffer, max_size);
        }
    }

    /* All data was read before a newline was reached, or end of file was reached,
     so return the number of bytes read*/
    buffer[total_bytes] = '\0';
    return total_bytes;
}
