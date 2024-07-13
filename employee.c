#include "employee.h"

void add_employee(void) {
	Employee new_employee;

	printf("Enter name: ");
	if (fgets(new_employee.name, MAX_LENGTH, stdin) == NULL) {
		printf(RED "Error reading name." RESET "\n");
		return;
	}
	new_employee.name[strcspn(new_employee.name, "\n")] = 0;

	if (!is_alpha(new_employee.name)) {
		printf(YELLOW "Name must contain only alphabetic characters. Please enter a valid name." RESET "\n");
		return;
	}
	capitalize_first_letter(new_employee.name);

	printf("Enter surname: ");
	if (fgets(new_employee.surname, MAX_LENGTH, stdin) == NULL) {
		printf(RED "Error reading surname." RESET "\n");
		return;
	}
	new_employee.surname[strcspn(new_employee.surname, "\n")] = 0;

	if (!is_alpha(new_employee.surname)) {
		printf(YELLOW "Surname must contain only alphabetic characters. Please enter a valid surname." RESET "\n");
		return;
	}
	capitalize_first_letter(new_employee.surname);

	int birth_year, birth_month, birth_day;

	printf("Enter birth date (YYYY MM DD): ");
	if (scanf("%d %d %d", &birth_year, &birth_month, &birth_day) != 3) {
		printf(YELLOW "Invalid input. Please enter year, month, and day as numbers." RESET "\n");
		flush_input();
		return;
	}
	flush_input();

	int age = calculate_age(birth_year, birth_month, birth_day);

	if (!is_valid_age(age)) {
		printf(YELLOW "Employee must be between 18 and 65 years old. Please try again." RESET "\n");
		return;
	}

	new_employee.age = age;

	printf("Enter position: ");
	if (fgets(new_employee.position, MAX_LENGTH, stdin) == NULL) {
		printf(RED "Error reading position." RESET "\n");
		return;
	}
	new_employee.position[strcspn(new_employee.position, "\n")] = 0;

	if (!is_alpha(new_employee.position)) {
		printf(YELLOW "Position must contain only alphabetic characters. Please enter a valid position." RESET "\n");
		return;
	}
	capitalize_first_letter(new_employee.position);

	printf("Enter salary: ");
	if (scanf("%f", &new_employee.salary) != 1) {
		printf(YELLOW "Invalid salary input." RESET "\n");
		flush_input();
		return;
	}
	flush_input();

	Employee* temp = realloc(database, (database_size + 1) * sizeof(Employee));
	if (temp == NULL) {
		printf(RED "Memory allocation failed. Exiting." RESET "\n");
		exit(EXIT_FAILURE);
	}

	new_employee.id = next_id++;
	database = temp;
	database[database_size++] = new_employee;
	printf(GREEN "Employee added successfully." RESET "\n");
}


void view_all_employees(void) {
	// Check if database is empty
	if (database_size == 0) {
		printf(YELLOW "Employee Database is empty." RESET "\n");
		return;
	}

	printf("\nEmployee Database:\n");
	printf("--------------------------------------------------------------------------------------------------------\n");
	printf("| %-5s | %-20s | %-20s | %-20s | %-10s | %-10s |\n", "ID", "Name", "Surname", "Position", "Salary", "Age");
	printf("--------------------------------------------------------------------------------------------------------\n");
	for (int i = 0; i < database_size; i++) {
		print_employee(&database[i]);
	}
}

void search_employee(void) {
	if (database_size == 0) {
		printf(YELLOW "Employee database is empty." RESET "\n");
		return;
	}

	int choice;
	printf("\nSearch by:\n");
	printf("1. ID\n");
	printf("2. Name\n");
	printf("3. Surname\n");
	printf("4. Position\n");
	printf("5. Age\n");
	printf("6. Salary\n");
	printf("\nEnter your choice: ");

	if (scanf("%d", &choice) != 1) {
		printf(YELLOW "Invalid input. Please enter a number." RESET "\n");
		flush_input();
		return;
	}
	flush_input();

	char searchStr[MAX_LENGTH];
	int searchInt;
	float searchFloat;
	int found = 0;

	switch (choice) {
	case 1:
		printf("Enter ID: ");
		if (scanf("%d", &searchInt) != 1) {
			printf(YELLOW "Invalid ID input." RESET "\n");
			flush_input();
			return;
		}
		flush_input();
		break;
	case 2:
		printf("Enter Name: ");
		if (fgets(searchStr, MAX_LENGTH, stdin) == NULL) {
			printf(RED "Error reading name." RESET "\n");
			return;
		}
		searchStr[strcspn(searchStr, "\n")] = 0;
		break;
	case 3:
		printf("Enter Surname: ");
		if (fgets(searchStr, MAX_LENGTH, stdin) == NULL) {
			printf(RED "Error reading surname." RESET "\n");
			return;
		}
		searchStr[strcspn(searchStr, "\n")] = 0;
		break;
	case 4:
		printf("Enter Position: ");
		if (fgets(searchStr, MAX_LENGTH, stdin) == NULL) {
			printf(RED "Error reading position." RESET "\n");
			return;
		}
		searchStr[strcspn(searchStr, "\n")] = 0;
		break;
	case 5:
		printf("Enter Age: ");
		if (scanf("%d", &searchInt) != 1) {
			printf(YELLOW "Invalid age input." RESET "\n");
			flush_input();
			return;
		}
		flush_input();
		break;
	case 6:
		printf("Enter Salary: ");
		if (scanf("%f", &searchFloat) != 1) {
			printf(YELLOW "Invalid salary input." RESET "\n");
			flush_input();
			return;
		}
		flush_input();
		break;
	default:
		printf(YELLOW "Invalid choice." RESET "\n");
		return;
	}

	printf("\nSearch Results:\n");
	printf("--------------------------------------------------------------------------------------------------------\n");
	printf("| %-5s | %-20s | %-20s | %-20s | %-10s | %-10s |\n", "ID", "Name", "Surname", "Position", "Salary", "Age");
	printf("--------------------------------------------------------------------------------------------------------\n");

	for (size_t i = 0; i < database_size; i++) {
		int match = 0;
		switch (choice) {
		case 1:
			match = (database[i].id == searchInt);
			break;
		case 2:
			match = (_stricmp(database[i].name, searchStr) == 0);
			break;
		case 3:
			match = (_stricmp(database[i].surname, searchStr) == 0);
			break;
		case 4:
			match = (_stricmp(database[i].position, searchStr) == 0);
			break;
		case 5:
			match = (database[i].age == searchInt);
			break;
		case 6:
			match = (fabs(database[i].salary - searchFloat) < 0.01);
			break;
		}

		if (match) {
			print_employee(&database[i]);
			found = 1;
		}
	}

	if (!found) {
		printf(YELLOW "No matching employees found." RESET "\n");
	}
}

void update_employee(void) {
	int target_id;
	printf("Enter employee ID: ");
	if (scanf("%d", &target_id) != 1) {
		printf(YELLOW "Invalid ID input." RESET "\n");
		flush_input();
		return;
	}
	flush_input();

	int index = find_employee_by_id(target_id);

	if (index != -1) {
		// Display current employee details
		printf("Current Details:\n");
		printf("--------------------------------------------------------------------------------------------------------\n");
		printf("| %-5s | %-20s | %-20s | %-20s | %-10s | %-10s |\n", "ID", "Name", "Surname", "Position", "Salary", "Age");
		printf("--------------------------------------------------------------------------------------------------------\n");
		print_employee(&database[index]);
		printf("\n");

		// Ask user what fields to update
		printf("Select what you want to update (enter numbers separated by spaces):\n");
		printf("1. Update name\n");
		printf("2. Update surname\n");
		printf("3. Update age\n");
		printf("4. Update position\n");
		printf("5. Update salary\n");
		printf("6. Update all fields\n");

		int choice;
		if (scanf("%d", &choice) != 1) {
			printf(YELLOW "Invalid input. Please enter a number." RESET "\n");
			flush_input();
			return;
		}
		flush_input();

		switch (choice) {
		case 1:
			printf("Enter new name: ");
			if (fgets(database[index].name, MAX_LENGTH, stdin) == NULL) {
				printf(RED "Error reading name." RESET "\n");
				return;
			}
			database[index].name[strcspn(database[index].name, "\n")] = 0;
			capitalize_first_letter(database[index].name);
			break;
		case 2:
			printf("Enter new surname: ");
			if (fgets(database[index].surname, MAX_LENGTH, stdin) == NULL) {
				printf(RED "Error reading surname." RESET "\n");
				return;
			}
			database[index].surname[strcspn(database[index].surname, "\n")] = 0;
			capitalize_first_letter(database[index].surname);
			break;
		case 3:
			printf("Enter birth date (YYYY MM DD): ");
			int birth_year, birth_month, birth_day;
			if (scanf("%d %d %d", &birth_year, &birth_month, &birth_day) != 3) {
				printf(YELLOW "Invalid input. Please enter year, month, and day as numbers." RESET "\n");
				flush_input();
				return;
			}
			flush_input();

			int age = calculate_age(birth_year, birth_month, birth_day);

			if (!is_valid_age(age)) {
				printf(YELLOW "Employee must be between 18 and 65 years old. Please try again." RESET "\n");
				return;
			}
			database[index].age = age;
			break;
		case 4:
			printf("Enter new position: ");
			if (fgets(database[index].position, MAX_LENGTH, stdin) == NULL) {
				printf(RED "Error reading position." RESET "\n");
				return;
			}
			database[index].position[strcspn(database[index].position, "\n")] = 0;
			break;
		case 5:
			printf("Enter new salary: ");
			if (scanf("%f", &database[index].salary) != 1) {
				printf(YELLOW "Invalid salary input." RESET "\n");
				flush_input();
				return;
			}
			flush_input();
			break;
		case 6:
			// Update all fields
			printf("Enter new name: ");
			if (fgets(database[index].name, MAX_LENGTH, stdin) == NULL) {
				printf(RED "Error reading name." RESET "\n");
				return;
			}
			database[index].name[strcspn(database[index].name, "\n")] = 0;
			capitalize_first_letter(database[index].name);

			printf("Enter new surname: ");
			if (fgets(database[index].surname, MAX_LENGTH, stdin) == NULL) {
				printf(RED "Error reading surname." RESET "\n");
				return;
			}
			database[index].surname[strcspn(database[index].surname, "\n")] = 0;
			capitalize_first_letter(database[index].surname);

			printf("Enter new age: ");
			if (scanf("%d", &database[index].age) != 1) {
				printf(YELLOW "Invalid age input." RESET "\n");
				flush_input();
				return;
			}
			flush_input();

			printf("Enter new position: ");
			if (fgets(database[index].position, MAX_LENGTH, stdin) == NULL) {
				printf(RED "Error reading position." RESET "\n");
				return;
			}
			database[index].position[strcspn(database[index].position, "\n")] = 0;

			printf("Enter new salary: ");
			if (scanf("%f", &database[index].salary) != 1) {
				printf(YELLOW "Invalid salary input." RESET "\n");
				flush_input();
				return;
			}
			flush_input();
			break;
		default:
			printf(YELLOW "Invalid choice. Please try again." RESET "\n");
			return;
		}
		printf(GREEN "Employee details updated successfully." RESET "\n");
	}
	else {
		printf(YELLOW "Employee not found." RESET "\n");
	}
}


void delete_employee(void) {
	if (database_size == 0) {
		printf(YELLOW "No employees to delete." RESET "\n");
		return;
	}

	int target_id;
	printf("Enter employee ID: ");
	if (scanf("%d", &target_id) != 1) {
		printf(YELLOW "Invalid ID input." RESET "\n");
		flush_input();
		return;
	}
	flush_input();

	int index = find_employee_by_id(target_id);

	if (index != -1) {
		for (size_t i = index; i < database_size - 1; i++) {
			database[i] = database[i + 1];
		}
		database_size--;

		Employee* temp = realloc(database, database_size * sizeof(Employee));
		if (temp == NULL && database_size > 0) {
			printf(RED "Memory reallocation failed. Exiting." RESET "\n");
			exit(EXIT_FAILURE);
		}
		database = temp;

		printf(GREEN "Employee deleted successfully." RESET "\n");
	}
	else {
		printf(YELLOW "Employee not found." RESET "\n");
	}
}


void save_database(void) {
	FILE* fp = fopen(FILENAME, "w");
	if (fp == NULL) {
		printf(RED "Error opening file!" RESET "\n");
		return;
	}

	for (size_t i = 0; i < database_size; i++) {
		fprintf(fp, "%d %s %s %d %s %.2f\n", database[i].id, database[i].name, database[i].surname,
			database[i].age, database[i].position, database[i].salary);
	}

	fclose(fp);
	printf(GREEN "Database saved successfully." RESET "\n");
}

void load_database(void) {
	FILE* fp = fopen(FILENAME, "r");
	if (fp == NULL) {
		printf(RED "Error opening file or file does not exist!" RESET "\n");
		return;
	}

	free_database();

	Employee temp;
	while (fscanf(fp, "%d %s %s %d %s %f", &temp.id, temp.name, temp.surname,
		&temp.age, temp.position, &temp.salary) == 6) {
		Employee* new_database = realloc(database, (database_size + 1) * sizeof(Employee));
		if (new_database == NULL) {
			printf(RED "Memory allocation failed. Exiting." RESET "\n");
			fclose(fp);
			exit(EXIT_FAILURE);
		}
		database = new_database;
		database[database_size++] = temp;
		if (temp.id >= next_id) {
			next_id = temp.id + 1;
		}
	}

	fclose(fp);
	printf(GREEN "Database loaded successfully. %zu employees imported." RESET "\n", database_size);
}

void free_database(void) {
	free(database);
	database = NULL;
	database_size = 0;
	next_id = 1;
}

int find_employee_by_id(int id) {
	for (size_t i = 0; i < database_size; i++) {
		if (database[i].id == id) {
			return (int)i;
		}
	}
	return -1;
}

void print_employee(const Employee* emp) {
	printf("| %-5d | %-20s | %-20s | %-20s | %-10.2f | %-10d |\n",
		emp->id, emp->name, emp->surname, emp->position, emp->salary, emp->age);
	printf("--------------------------------------------------------------------------------------------------------\n");
}
