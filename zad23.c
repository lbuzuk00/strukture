#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct Person {
	
	char first_name[50];
	char last_name[50];
	int birth_year;
	struct Person* next;
};


struct Person* add_to_beginning(struct Person* head, char first_name[], char last_name[], int birth_year) {
	
	struct Person* new_person = (struct Person*)malloc(sizeof(struct Person));
	
	strcpy(new_person->first_name, first_name);
	strcpy(new_person->last_name, last_name);
	new_person->birth_year = birth_year;
	new_person->next = head;
	
	return new_person;
}

void print_list(struct Person* head) {
	
	struct Person* current = head;
	
	while (current != NULL) {
		printf("Ime: %s, Prezime: %s, Godina rodenja: %d\n", current->first_name, current->last_name, current->birth_year);
		current = current->next;
	}
}


struct Person* add_to_end(struct Person* head, char first_name[], char last_name[], int birth_year) {
	
	struct Person* new_person = (struct Person*)malloc(sizeof(struct Person));
	
	strcpy(new_person->first_name, first_name);
	strcpy(new_person->last_name, last_name);
	new_person->birth_year = birth_year;
	new_person->next = NULL;

	if (head == NULL) {
		return new_person;
	}

	struct Person* current = head;
	while (current->next != NULL) {
		current = current->next;
	}

	current->next = new_person;
	return head;
}


struct Person* find_by_last_name(struct Person* head, char last_name[]) {
	
	struct Person* current = head;
	
	while (current != NULL) {
		if (strcmp(current->last_name, last_name) == 0) {
			return current;
		}
		current = current->next;
	}
	return NULL;
}


struct Person* delete_person(struct Person* head, char last_name[]) {
	
	struct Person* current = head;
	struct Person* previous = NULL;

	while (current != NULL) {
		if (strcmp(current->last_name, last_name) == 0) {
			if (previous == NULL) {
				head = current->next;
			}
			else {
				previous->next = current->next;
			}
			free(current);
			return head;
		}
		previous = current;
		current = current->next;
	}

	return head;
}


struct Person* add_after_person(struct Person* head, char first_name[], char last_name[], int birth_year, char search_last_name[]) {
	
	struct Person* new_person = (struct Person*)malloc(sizeof(struct Person));
	
	strcpy(new_person->first_name, first_name);
	strcpy(new_person->last_name, last_name);
	new_person->birth_year = birth_year;
	new_person->next = NULL;

	struct Person* current = head;

	while (current != NULL) {
		if (strcmp(current->last_name, search_last_name) == 0) {
			new_person->next = current->next;
			current->next = new_person;
			return head;
		}
		current = current->next;
	}

	return head;
}


struct Person* add_before_person(struct Person* head, char first_name[], char last_name[], int birth_year, char search_last_name[]) {
	
	struct Person* new_person = (struct Person*)malloc(sizeof(struct Person));
	
	strcpy(new_person->first_name, first_name);
	strcpy(new_person->last_name, last_name);
	new_person->birth_year = birth_year;
	new_person->next = NULL;

	if (head == NULL) {
		return new_person;
	}

	if (strcmp(head->last_name, search_last_name) == 0) {
		new_person->next = head;
		
		return new_person;
	}

	struct Person* current = head;

	while (current->next != NULL) {
		if (strcmp(current->next->last_name, search_last_name) == 0) {
			new_person->next = current->next;
			current->next = new_person;
			return head;
		}
		current = current->next;
	}

	return head;
}


void free_memory(struct Person* head) {
	
	struct Person* current = head;
	
	while (current != NULL) {
		struct Person* next = current->next;
		free(current);
		current = next;
	}
}

int main() {
	
	struct Person* head = NULL;
	char first_name[50];
	char last_name[50];
	int birth_year;

	head = add_to_beginning(head, "Marko", "Markovic", 2000);
	head = add_to_beginning(head, "Ana", "Anic", 1999);

	printf("Lista ljudi:\n");
	print_list(head);

	head = add_to_end(head, "Maja", "Majic", 2000);

	char search_last_name[] = "Anic";
	struct Person* found_person = find_by_last_name(head, search_last_name);

	if (found_person != NULL) {
		printf("Pronadena osoba: Ime: %s, Prezime: %s, Godina rodenja: %d\n", found_person->first_name, found_person->last_name, found_person->birth_year);
	}
	else {
		printf("Osoba s prezimenom %s nije pronađena.\n", search_last_name);
	}


	head = add_after_person(head, "Ivan", "Ivanic", 1998, "Anic");


	head = add_before_person(head, "Luka", "Lukic", 2005, "Majic");


	printf("Lista nakon promjena:\n");
	print_list(head);


	char deleted_last_name[] = "Majic";
	head = delete_person(head, deleted_last_name);


	printf("Lista nakon brisanja:\n");
	print_list(head);


	free_memory(head);

	return 0;
}
