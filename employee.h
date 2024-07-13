#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>

#define RED "\x1B[31m"
#define GREEN "\x1B[32m"
#define YELLOW "\x1B[33m"
#define RESET "\x1B[0m"

#define MAX_LENGTH 50
#define BUFFER_LENGTH 256
#define FILENAME "database.txt"

typedef struct {
    int id;
    char name[MAX_LENGTH];
    char surname[MAX_LENGTH];
    int age;
    char position[MAX_LENGTH];
    float salary;
} Employee;

extern Employee* database;
extern size_t database_size;
extern int next_id;

void add_employee(void);
void view_all_employees(void);
void search_employee(void);
void update_employee(void);
void delete_employee(void);
void save_database(void);
void load_database(void);
void free_database(void);
int find_employee_by_id(int id);
void print_employee(const Employee* emp);

#endif // EMPLOYEE_H
