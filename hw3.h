#ifndef HW3_H
#define HW3_H

struct Course{
	char* division;
	char* department;
	char* course_number;
	char* credit;
	char* title; 
};

struct Transcript{
	struct Course course;
	char* year;
	char* grade;
	struct Transcript* next;
};

int insert(struct Transcript **phead,char* identifier, char*year, char* grade);
int delete(struct Transcript **phead,char* identifier, char* year);
void convertString2course(char* records, struct Course* course_list);
int compare(struct Course course, char* identifier);
int update_title(char* title, char* identifier, struct Transcript *phead);
int update_credit(char* credit, char* identifier, struct Transcript *phead);
int record_count(char* file_name);
void read_catalog(struct Course * course_list,char* file_name);
void print_transcript(struct Transcript *p);
void print_transcript_full(struct Transcript *p);
void print_catalog(struct Course *course,int size);
void print(struct Course course);
int catalog_contains_course(char* identifier, struct Course *course_list, int size );
void display_course(struct Course *course_list, char* identifier,int size);
float compute_gpa(struct Transcript *phead);
float convertGrade2Decimal(char* grade);
float convertString2Decimal(char* credit);
void stripNewLine(char* arr);
void read(char* arr);
#endif 