#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "hw3.h"

int main(){
	//struct Course course1 = {.division = "EN",.department = "600",.course_number = "621",.credit = "3.5",.title = "Intermediate Programming"};
	char file_name[] = "cat1.txt";
	int num_records = record_count(file_name);
	struct Course* course_list = malloc(sizeof(struct Course)*num_records);
	read_catalog(course_list,file_name);
	struct Transcript *head = NULL;
	print_catalog(course_list,num_records);
	char choice[2];
	printf("Please enter your choice: ");
	scanf("%s",choice);
	while (toupper(choice[0])!= 'Q'){
		switch(toupper(choice[0])){
			case 'P':
				print_transcript(head);
				break;
			case 'C':
				{
					printf("Please enter the course identifier (xx.ddd.nnn): ");
					char* identifier = malloc(sizeof(char)*11);
					scanf("%s",identifier);
					display_course(course_list,identifier,num_records);
					free(identifier);
					break;
				}
			case 'T':
				{
					printf("Please enter the course identifier (xx.ddd.nnn): ");
					char* identifier = malloc(sizeof(char)*11);
					scanf("%s",identifier);
					printf("Please enter the desired course title (32 characters max): ");
					char* title = malloc(sizeof(char)*34);
					char c;
					c = getchar();
					fgets(title,34,stdin);
					stripNewLine(title);
					int success = update_title(title, identifier, head);
					if (success == 1){
						puts("updated");
					}else{
						puts("absent");
						free(title);
					}
					break;
				}
			case 'A':
				{	printf("Please enter the course identifier (xx.ddd.nnn): ");
					char* identifier = malloc(sizeof(char)*11);
					scanf("%s",identifier);
					char* year = malloc(sizeof(char)*7);
					char* grade = malloc(sizeof(char)*3);
					printf("Please enter the semester and grade (yyyy.s Gg):");
					scanf("%s",year);
					scanf("%s",grade);
					
					int find = catalog_contains_course(identifier, course_list, num_records);
					if (!find){
						puts("invalid");
						free(year);free(grade);
					}else{
						int success = insert(&head,identifier,year,grade);
						if (success){
							puts("added");
						}
						else{
							free(year);free(grade);
							puts("present");
						}
					}
					free(identifier);
					break;
				}
			case 'R':
				{	printf("Please enter the course identifier (xx.ddd.nnn): ");
					char* identifier = malloc(sizeof(char)*11);
					scanf("%s",identifier);
					char* credit = malloc(sizeof(char) * 4);
					printf("Please enter the credit (xx): ");
					scanf("%s", credit);
					int success = update_credit(credit, identifier,head);
					if (success){
						puts("added");
					}else{
						free(credit);
						puts("absent");
					}
					free(identifier);
					break;
				}
			case 'D':
				{	printf("Please enter the course identifier (xx.ddd.nnn): ");
					char* identifier = malloc(sizeof(char)*11);
					scanf("%s",identifier);
					printf("Please enter the semester and grade (yyyy.s Gg): ");
					char* year = malloc(sizeof(char)*7);
					char* grade = malloc(sizeof(char)*3);
					scanf("%s",year);
					scanf("%s", grade);
					int success = delete(&head,identifier,year);
					if (success){
						puts("removed");
					}else{
						puts("absent");
						free(year);
						free(grade);
					}
					free(identifier);
					break;
				}
			case 'I':
				print_transcript_full(head);
				break;
			case 'G':
				{
					float gpa = compute_gpa(head);
					printf("%.2f\n",gpa);
					break;
				}
			default:
				puts("Invalid menu choice");
				break;
		}
		printf("Please enter your choice: ");
		scanf("%s",choice);
	}
	return 1;
}
