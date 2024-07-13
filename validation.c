#include "validation.h"

void capitalize_first_letter(char* str) {
	if (str[0] != '\0') {
		if (str[0] >= 'a' && str[0] <= 'z') {
			str[0] = str[0] - 'a' + 'A';
		}
	}
}

int is_alpha(const char* str) {
	while (*str) {
		if ((*str < 'A' || *str > 'Z') && (*str < 'a' || *str > 'z')) {
			return 0;
		}
		str++;
	}
	return 1;
}

void flush_input(void) {
	int c;
	while ((c = getchar()) != '\n' && c != EOF);
}

// Helper function to calculate age
int calculate_age(int birth_year, int birth_month, int birth_day) {
	time_t t = time(NULL);
	struct tm* tm = localtime(&t);

	int current_year = tm->tm_year + 1900;
	int current_month = tm->tm_mon + 1;
	int current_day = tm->tm_mday;

	int age = current_year - birth_year;

	if (current_month < birth_month || (current_month == birth_month && current_day < birth_day)) {
		age--;
	}

	return age;
}

int is_valid_age(int age) {
	return (age >= 18 && age <= 65);
}