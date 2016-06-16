#include "hw3.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int insert(struct Transcript **phead,char* identifier, char*year, char* grade){
	/*
		input args: pointer of pointer of head, pointer of course struct
		add a new course to the catalog at front.
	*/
	struct Transcript *ptr = *phead;
	char *div = malloc(sizeof(char)*3);
	char *dep = malloc(sizeof(char)*4);
	char *number = malloc(sizeof(char)*3);

	int div_count,dep_count,number_count;
	div_count = dep_count = number_count = 0;
	
	for (int i =0; identifier[i]!= '\0';i++){
		if (i < 3){
			div[div_count++] = identifier[i];
			//printf("%c",div[div_count]);
		}else if( 3 <=i && i <7){
			dep[dep_count++] = identifier[i];
		}else if( 7<=i && i< 10){
			number[number_count++] = identifier[i];
		}else{
			break;
		}
	}
	
	//printf("%s ",identifier);
	//printf("year:%s ",year);
	//printf("%s ",grade);
	//printf("div:%s ", div);
	//printf("dep:%s ",dep);
	//printf("number:%s\n", number);
	struct Transcript *elem = malloc(sizeof(struct Transcript));//assert elem as a pointer
	struct Course course1 = {.division = div,.department = dep,.course_number = number};
	elem->course = course1;
	elem->grade = grade;
	elem->year = year;

	while(ptr!= NULL && (ptr->next)!=NULL && (strncmp(ptr->next->year,year,6)<0)){
		if (compare(ptr->course,identifier) && (strncmp(ptr->year,year,6)==0)){
			free(div);free(dep);free(number);free(elem);
			return 0;
		}
		//printf("ptr->year: %s\n",ptr->year);
		ptr = ptr ->next;
	}

	if (ptr == *phead){
		if (*phead == NULL){
			elem->next = NULL;
			*phead = elem;
		}else{
				if (compare(ptr->course,identifier) && (strncmp(ptr->year,year,6)==0)){
					free(div);free(dep);free(number);free(elem);
					return 0;
				}
				if (strncmp(ptr->year,year,6)<0){
					elem->next = (*phead)->next;
					(*phead)->next = elem;
				}else{
					elem->next = (*phead);
					(*phead) = elem;
				}
			}
	}else{
		elem->next = ptr->next;
		ptr->next = elem;
	}
	int length = 0;
	struct Transcript *q = *phead;
	while(q!=NULL){
		q = q->next;
		length++;
	}
	printf("length is: %d\n", length);
	return 1;
}


int delete(struct Transcript **phead,char* identifier, char* year){
	struct Transcript *ptr = *phead;
	struct Transcript *ptr_prev = *phead;
	while(ptr!=NULL){
		if (compare(ptr->course,identifier)&& (strncmp(ptr->year,year,6)==0)){
			ptr_prev->next = ptr->next;
			free(ptr);
			return 1;
		}else{
			ptr_prev = ptr;
			ptr = ptr->next;
		}
	}
	return 0;
}


int catalog_contains_course(char* identifier, struct Course *course_list, int size ){
	for (int i= 0; i < size; i++){
		if (compare(*(course_list+i), identifier) == 1)
			return 1;
	}
	return 0;
}


int compare(struct Course course, char* identifier){
	//this function will find the course struct w.r.t indentifier
	int div_count,dep_count,number_count;
	div_count = dep_count = number_count = 0;
	//printf("identifer: %s\n",identifier);
	for (int i =0; identifier[i]!= '\0';i++){
		if (i < 3){
			//printf("div: %c",course.division[div_count]);
			if (course.division[div_count++] != identifier[i])
				return 0;
		}else if( 3 <=i && i <7){
			//printf("dep: %c",course.department[dep_count]);
			if (course.department[dep_count++] != identifier[i])
				return 0;
		}else if( 7<=i && i< 10){
			//printf("course: %c",course.course_number[number_count]);
			if (course.course_number[number_count++] != identifier[i])
				return 0;
		}else if(10<=i){
			break;
		}
	}
	return 1; 
}


int update_title(char* title, char* identifier, struct Transcript *phead){
	int add_ed = 0;
	while(phead!= NULL){
		if (compare(phead->course, identifier)){
			phead->course.title = title;
			add_ed = 1;
		}
		phead = phead -> next;
	}
	return add_ed;
}


int update_credit(char* credit, char* identifier, struct Transcript *phead){
	int add_ed = 0;
	while(phead!= NULL){
		if(compare(phead->course, identifier)){
			phead->course.credit = credit;
			add_ed = 1;
		}
		phead = phead -> next;
	}
	return add_ed;
}


void convertString2course(char* records, struct Course* course_list){
	char *div = malloc(sizeof(char)*3);
	char *dep = malloc(sizeof(char)*4);
	char *number = malloc(sizeof(char)*3);
	char *credit = malloc(sizeof(char)*3);
	char *title = malloc(sizeof(char)*32);
	int div_count,dep_count,number_count,credit_count,title_count;
	div_count = dep_count = number_count = credit_count = title_count = 0;
	
	for (int i =0; records[i]!= '\0';i++){
		if (i < 3){
			div[div_count++] = records[i];
		}else if( 3 <=i && i <7){
			dep[dep_count++] = records[i];
		}else if( 7<=i && i< 10){
			number[number_count++] = records[i];
		}else if(11<= i && i < 14){
			credit[credit_count++] = records[i];
		}else if (14<i){
			title[title_count++] = records[i];
		}
	}
	course_list->division = div;
	course_list->department = dep;
	course_list->course_number = number;
	course_list->credit = credit;
	course_list->title = title;
}


int record_count(char* file_name){
	/*
		this functino will read file once and count the number of records
	*/
	FILE *fptr;
	fptr = fopen(file_name, "r");
	char* record = malloc(sizeof(char)*100);
	int count = 0;
	while(fgets(record,100,fptr)!= NULL){
		count++;
		//printf("%s\n",record);
	}
	fclose(fptr);
	free(record);
	return count;
}


void read_catalog(struct Course * course_list,char* file_name){
	FILE *fptr;
	fptr = fopen(file_name,"r");
	int num_records = 0;
	char* record = malloc(sizeof(char)*100);
	while (fgets(record,100,fptr)!=NULL){
		convertString2course(record,course_list);
		print(*course_list);
		course_list++;	
	}
	fclose(fptr);
	free(record);
} 


void print_transcript(struct Transcript *p){
	while(p!=NULL){
		print(p->course);
		p = (p->next);
	}
}


void print_transcript_full(struct Transcript *p){
	while(p!=NULL){
		printf("%s",(p->course).division);
		printf("%s", (p->course).department);
		printf("%s ", (p->course).course_number);
		printf("%s ", (p->course).credit);
		printf("%s ", (p->course).title);
		printf("%s ", (p->year));
		printf("%s\n", (p->grade));
		p = (p->next);
	}
}


void print(struct Course course){
	printf("%s",course.division);
	printf("%s", course.department);
	printf("%s ", course.course_number);
	printf("%s ", course.credit);
	printf("%s\n", course.title);
}


void print_catalog(struct Course *course, int size){
	for (int i =0; i<size; i++){
		print(*course);
		course++;
	}
}


void display_course(struct Course *course_list, char* identifier, int size){
	int i =0;
	for (; i < size; i++){
		if (compare(*(course_list+i),identifier)){
			printf("%s ",(course_list+i)->credit);
			printf("%s", (course_list+i)->title);
			break;
		}
	}
	if (i == size)
		printf("absent\n");
}


float convertString2Decimal(char* credit){
	float cred = 0;
	int i = 0;
	if (credit == NULL)
		return cred;
	for (; credit[i]!= '.';i++){
	}
	for (int j =0; j < i; j++){
		cred = cred + credit[j]*pow(10,i-j);
	}
	for (int j= 1; credit[j]!= '\0';j++){
		cred = cred + credit[j+i] *pow(10,-j);
	}
	return cred;
}


float convertGrade2Decimal(char* grade){
	float gpa = 0;
	if (grade[0] =='A'){
		gpa = 4;
	}else if(grade[0] == 'B'){
		gpa = 3;
	}else if(grade[0] == 'C'){
		gpa = 2;
	}else if (grade[0] == 'D'){
		gpa = 1;
	}else if(grade[0] == 'F'){
		gpa = 0;
	}else{
		printf("invalid grade\n");
	}

	if (grade[2] == '+'){
		gpa = gpa +0.3;
	}else if (grade[2] == '-'){
		gpa = gpa - 0.3;
	}else{}

	if (gpa > 4){
		gpa = 4;
	}
	return gpa;
}


float compute_gpa(struct Transcript *phead){
	float cum_gpa = 0;
	float gpa;
	float credit;
	float cum_credict = 0;
	while (phead!= NULL){
		credit = convertString2Decimal(phead->course.credit);
		gpa = convertGrade2Decimal(phead->grade);
		cum_gpa += gpa*credit;
		cum_credict += credit;
		phead = phead->next;
	}
	return cum_gpa/cum_credict;
}


void stripNewLine(char* arr){
	/* 
		Assume the new line is at the end of the string
	*/ 
	int i =0;
	for(; arr[i]!= '\n';i++){
	}	
	arr[i] = '\0';
}

void read(char* arr){
	char c = getchar();
	int i =0;
	while (c!='\n'){
		if (c!='\n')
			arr[i++] = c;
	}
}