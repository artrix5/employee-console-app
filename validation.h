#ifndef VALIDATION_H
#define VALIDATION_H

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <time.h>

void capitalize_first_letter(char* str);
int is_alpha(const char* str);
void flush_input(void);
int calculate_age(int birth_year, int birth_month, int birth_day);
int is_valid_age(int birth_year);

#endif // VALIDATION_H
