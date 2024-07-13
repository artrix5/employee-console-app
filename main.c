#define _CRT_SECURE_NO_WARNINGS
#include "validation.h" 
#include "employee.h"

const char* ASCII_ART =
"  ______                 _                         _____        _        _                          \n"
" |  ____|               | |                       |  __ \\      | |      | |                         \n"
" | |__   _ __ ___  _ __ | | ___  _   _  ___  ___  | |  | | __ _| |_ __ _| |__   __ _ ___  ___       \n"
" |  __| | '_ ` _ \\| '_ \\| |/ _ \\| | | |/ _ \\/ _ \\ | |  | |/ _` | __/ _` | '_ \\ / _` / __|/ _ \\      \n"
" | |____| | | | | | |_) | | (_) | |_| |  __/  __/ | |__| | (_| | || (_| | |_) | (_| \\__ \\  __/      \n"
" |______|_| |_| |_| .__/|_|\\___/ \\__, |\\___|\\___|_|_____/ \\__,_|\\__\\__,_|_.__/ \\__,_|___/\\___|      \n"
"  __  __          | |             __/ |                    _      _____           _                 \n"
" |  \\/  |         |_|            |___/                    | |    / ____|         | |                \n"
" | \\  / | __ _ _ __   __ _  __ _  ___ _ __ ___   ___ _ __ | |_  | (___  _   _ ___| |_ ___ _ __ ___  \n"
" | |\\/| |/ _` | '_ \\ / _` |/ _` |/ _ \\ '_ ` _ \\ / _ \\ '_ \\| __|  \\___ \\| | | / __| __/ _ \\ '_ ` _ \\ \n"
" | |  | | (_| | | | | (_| | (_| |  __/ | | | | |  __/ | | | |_   ____) | |_| \\__ \\ ||  __/ | | | | |\n"
" |_|  |_|\\__,_|_| |_|\\__,_|\\__, |\\___|_| |_| |_|\\___|_| |_|\\__| |_____/ \\__, |___/\\__\\___|_| |_| |_|\n"
"                            __/ |                                        __/ |                      \n"
"                           |___/                                        |___/                       \n";

const char* MENU_OPTIONS =
" 1. Add Employee        5. Delete Employee\n"
" 2. View All Employees  6. Save Database\n"
" 3. Search Employee     7. Load Database\n"
" 4. Update Employee     8. Exit\n";

int main(void) {
	int choice;
	printf(YELLOW "%s" RESET "\n", ASCII_ART);

	while (1) {
		printf(YELLOW "\n" "%s" RESET, MENU_OPTIONS);
		printf("\nEnter your choice: ");
		if (scanf("%d", &choice) != 1) {
			printf(YELLOW "Invalid input. Please enter a number." RESET "\n");
			flush_input();
			continue;
		}

		flush_input();
		switch (choice) {
		case 1: add_employee(); break;
		case 2: view_all_employees(); break;
		case 3: search_employee(); break;
		case 4: update_employee(); break;
		case 5: delete_employee(); break;
		case 6: save_database(); break;
		case 7: load_database(); break;
		case 8:
			free(database);
			printf(YELLOW "Exiting program." RESET "\n");
			return 0;
		default: printf(YELLOW "Invalid choice. Please try again." RESET "\n");
		}
	}

	return 0;
}