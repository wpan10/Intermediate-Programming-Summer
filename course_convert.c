#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*
	code for hw1a	
*/

int main(int argc, char **argv){

	char input_string[16];
	char division[3] = {'\0'};  // last slot contains .
	char course_dep[4] = {'\0'}; // 
    char course_num[4] = {'\0'};
	char grade[3] = {'\0'};
	char credit[4] = {'\0'}; // include a /0 at the end

	void decode_div(char source[], char target[]);
	void decode_grade(char source[], char target[]);
	void decode_credit(char source[], char target[]);
	void display_output(char decoded_div[],char decoded_dep[],char decoded_course[],char decoded_grade[],char decoded_credit[]);
	void substring(char division[], char department[], char course_num[], char grade[], char credit[], char input_string[]);

	while (1){
		printf("Please type your input with following format XX.XXX.XXX|XX|X.X|: \n");
		scanf("%s", input_string);
		substring(division,course_dep,course_num,grade,credit,input_string); // this helper function will sub string the input string to correpsonding char array.
		printf("input string is: %s\n", input_string);
		printf ("div: %s\n", division);
		printf("department: %s\n", course_dep);
		printf("course number: %s\n", course_num);
		printf("grade: %s\n", grade);
		printf("credit: %s\n", credit);
		puts("----------------+++++++-------------");
		char decoded_div[2]; // save it as string, put /0 at the end
		decode_div(division,decoded_div);
		char decoded_dep[4];
		strncpy(decoded_dep,course_dep,4);
		char decoded_course[4];
		strncpy(decoded_course,course_num,4);
		char decoded_grade[4];
		decode_grade(grade,decoded_grade);
		char decoded_credit[4];
		decode_credit(credit,decoded_credit);
		display_output(decoded_div,decoded_dep,decoded_course,decoded_grade,decoded_credit);
		printf ("do you want to continue? y/n\n");
		char continue_[2];
		scanf("%s", continue_);
		if (strcmp(continue_,"y")==0){
			puts("user wants to continue\n");
		}else{
			puts("terminate program\n");
			break;
		}
	}
	return 0;
}

void substring(char division[], char department[], char course_num[], char grade[], char credit[], char input_string[]){

	int div_counter,department_counter,course_counter,grade_counter, credit_counter;
	div_counter = department_counter = course_counter = grade_counter = credit_counter = 0;

	for (int i = 0; i < 16; i++){
		if (i < 2){
			division[div_counter++] = input_string[i]; 
		}else if((3<=i) && (i<6)){
			department[department_counter++] = input_string[i];
		}else if ( (7<= i) && (i < 10)){
			course_num[course_counter++] = input_string[i];
		}else if ((10<= i) && (i < 12)){
			grade[grade_counter++] = input_string[i]; 
		}else if((12<= i) && (i <15)){
			credit[credit_counter++] = input_string[i];
		}else{}
	}
}

void decode_div(char source[],char target[]){
	// this function will decode div
	if (strcmp(source,"ME") == 0){
		target[0] = '0';
	}else if (strcmp(source,"BU") == 0){
		target[0] = '1';
	}else if (strcmp(source,"ED") == 0){
		target[0] = '2';
	}else if (strcmp(source,"EN") == 0){
		target[0]= '3';
	}else if (strcmp(source,"AS") == 0){
		target[0] = '4';
	}else if (strcmp(source,"PH") == 0){
		target[0] = '5';
	}else if (strcmp(source,"PY") == 0){
		target[0] = '6';
	}else if (strcmp(source,"SA") == 0){
		target[0] = '7';
	}else{
		printf("wrong input! No correpsonding decoder,set value to be 9");
		target[0] = '9';
	}
	target[1] = '\0';
} 

void decode_grade(char source[], char target[]){
	switch (source[0]){
		case 'A':
			target[0] = '0';
			break;
		case 'B':
			target[0] = '1';
			break;
		case 'C':
			target[0] = '2';
			break;
		case 'D':
			target[0] = '3';
			break;
		case 'F':
			target[0] = '4';
			break;
		case 'I':
			target[0] = '5';
			break;
		case 'S':
			target[0] = '6';
			break;
		case 'U':
			target[0] = '7';
			break;
		default:
			target[0] = '9';
			break;
	}
	target[1] = ' ';
	switch(source[1]){
		case '+':
			target[2] = '0';
			break;
		case '-':
			target[2] = '1';
			break;
		case '\\':
			target[2] = '2';
			break;
		default:
			target[2] = '9';
			break;
	}
	target[3] = '\0';
}

void decode_credit(char source[], char target[]){
	// first digit
	int check = source[1] - '0';
	if (check <= 5){
		target[0] = source[0];
	}else{
		printf("invlid input of credit, set value to be 9 \n");
		target[0] = '9';
	}
	// space
	target[1] = ' ';
	// second digit
	if (source[2] == '0'){
		target[2] = '0';
	}else if (source[2] == '5'){
		target[2] = '1';
	}else{
		printf("invalid assignment,set value to be 9 \n");
		target[2] = '9';
	}
}


void display_output(char decoded_div[],char decoded_dep[],char decoded_course[],char decoded_grade[],char decoded_credit[]){
	printf("Division: %s\n",decoded_div);
	printf("Department: %s\n", decoded_dep);
	printf("Course: %s\n", decoded_course);
	printf("Grade: %s\n", decoded_grade);
	printf("Credits %s\n", decoded_credit);
}




















