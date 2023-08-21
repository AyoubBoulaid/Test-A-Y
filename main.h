#ifndef MAIN_H
#define MAIN_H

#include <stdarg.h> // Include for va_list

#define BUFF_SIZE 1024 // Size of the temporary buffer

/* Function prototypes */
int _printf(const char *format, ...);
void print_buffer(char buffer[], int *buff_ind);

/* Add any other function prototypes or definitions you might need */

#endif /* MAIN_H 
