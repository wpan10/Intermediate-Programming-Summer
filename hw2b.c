#include <stdio.h>
#include <stdlib.h>
#include <math.h>
/*
	Requirement:
	n - display the total number of courses
	d - list all courses from a particular department (prompt for number)
	l - list all courses with a particular letter grade  (prompt for grade)
	c - list all courses with at least a specified number of credits (prompt for credits)
	g - compute the GPA of all the courses with letter grades (skipping those with 'I', 'S' or 'U' grades)
	q - quit the program
	Enter letter choice ->
*/

void convertUnsignedInt2bin(unsigned int integer, int bin[], int size ){
	for (int i = 0; i < size; i++){
		bin[i] = (integer >> (size-1-i) & 1);
	}
}

int convertBint2Int(int bin[], int size){
	int target = 0;
	for (int i =0; i < size; i++){
		target += bin[i] * (int)pow(2,size-1-i);
	}
	return target;
}

void print_bin_array(char string[], int array[], int num){
	printf("%s", string);
	for (int i=0;i< num;i++){
		printf("%d", array[i]);
	}
	printf("\n");
}

void print_char_array(char string[], int size){
	for (int i =0; i < size; i++){
		printf("%c",string[i]);
	}
	printf("\n");
}

void div_convert(int source[], char division[]){
	int num = convertBint2Int(source,3);
	switch(num){
		case 0:
			division[0] = 'M';
			division[1] = 'E';
			break;
		case 1:
			division[0] = 'B';
			division[1] = 'U';
			break;
		case 2:
			division[0] = 'E';
			division[1] = 'D';
			break;
		case 3:
			division[0] = 'E';
			division[1] = 'N';
			break;
		case 4:
			division[0] = 'A';
			division[1] = 'S';
			break;
		case 5:
			division[0] = 'P';
			division[1] = 'H';
			break;
		case 6:
			division[0] = 'P';
			division[1] = 'Y';
			break;
		case 7:
			division[0] = 'S';
			division[1] = 'A';
			break;
		default:
			printf("invalid input");
			exit(-1);
	}
	division[2] = '.';
}


void dep_convert(int source[], char dep[]){
	int num = convertBint2Int(source,10);
	int mod;
	int i = 0;
	while (num > 0){
			mod = num % 10;
			dep[2 - i] = mod + '0';
			num = num/10;
			i++;
	}	
	dep[i] = '.';
}

void course_convert(int source[], char course[]){
	int num = convertBint2Int(source,10);
	int mod;
	int i = 0;
	while (num > 0){
			mod = num % 10;
			course[2 - i] = mod + '0';
			num = num/10;
			i++;
	}	
}


void grade_convert(int source1[],int source2[], char grade[]){
	int num1 = convertBint2Int(source1,3);
	int num2 = convertBint2Int(source2,2);
	switch(num1){
		case 0:
			grade[0] = 'A';
			break;
		case 1:
			grade[0] = 'B';
			break;
		case 2:
			grade[0] = 'C';
			break;
		case 3:
			grade[0] = 'D';
			break;
		case 4:
			grade[0] = 'F';
			break;
		case 5:
			grade[0] = 'I';
			break;
		case 6:
			grade[0] = 'S';
			break;
		case 7:
			grade[0] = 'U';
			break;
		default:
			printf("int1 : %d", num1);
			puts("wrong input");
			exit(-1);
	}
	switch(num2){
		case 0:
			grade[1] = '+';
			break;
		case 1:
			grade[1] = '-';
			break;
		case 2:
			grade[1] = '\\';
			break;
		default:
			printf("int2 : %d", num2);
			puts("wrong input");
			exit(-1);
	}
}

void credit_convert(int source1[],int source2[], char credit[]){
	int num1 = convertBint2Int(source1,3);
	int num2 = convertBint2Int(source2,1);
	credit[0] = num1 +'0';
	credit[1] = '.';
	(num2 == 0) ? (credit[2] = '0'):(credit[2] = '5');
}

void convert2string(char division[], char dep[],char course[], char grade[], char credit[], char string[]){
	int div_counter,department_counter,course_counter,grade_counter,credit_counter;
	div_counter = department_counter = course_counter = grade_counter = credit_counter = 0;	

	for (int i =0; i < 16; i++){
		if (i < 3){
			string[i] = division[div_counter++];
		}else if( 3<=i && i < 7){
			string[i] = dep[department_counter++];
		}else if ( 7<= i && i < 10){
			string[i] = course[course_counter++];
		}else if (10<=i && i < 12){
			string[i] = grade[grade_counter++];
		}else if(12<=i && i < 15){
			string[i] = credit[credit_counter++];
		}else{
			string[i] = '\0';
		}
	}
}

void convertBin2String(int bin[], char output_string[]){

	char c_division[3] = {'0'};  // last slot contains .
	char c_dep[4] = {'0'}; // 
	char c_course[3] = {'0'};
	char c_grade[2] = {'0'};
	char c_credit[3] = {'0'}; // include a /0 at the end
	/*************************************************/	
	int division[3];
	int dep[10];
	int course[10];
	int grade_1[3];
	int grade_2[2];
	int credit_1[3];
	int credit_2[1];	
	int div_counter,department_counter,course_counter,grade1_counter,grade2_counter,credit1_counter,credit2_counter;
	div_counter = department_counter = course_counter = grade1_counter = grade2_counter = credit1_counter = credit2_counter = 0;
	// extract info from bin array
	for (int i = 0; i < 32; i++){
		if (i < 3){
			division[div_counter++] = bin[i];
		}else if ( 3<= i && i < 13){
			dep[department_counter++] = bin[i];
		}else if ( 13<=i && i < 23){
			course[course_counter++] = bin[i];
		}else if ( 23<= i && i< 26){
			grade_1[grade1_counter++] = bin[i];
		}else if( 26<=i && i< 28){
			grade_2[grade2_counter++] = bin[i];
		}else if (28<= i  && i< 31){
			credit_1[credit1_counter++] = bin[i];
		}else{
			credit_2[0] = bin[i];
		}
	}
	/***************************************************/
	div_convert(division, c_division);
	dep_convert(dep, c_dep);
	course_convert(course, c_course);
	grade_convert(grade_1,grade_2, c_grade);
	credit_convert(credit_1,credit_2,c_credit);
	convert2string(c_division, c_dep,c_course, c_grade, c_credit, output_string);
	//print_char_array(c_grade, 2);
}

int count(char *input_name){
	FILE *f_in; 
	f_in = fopen(input_name,"r");
	int counts = 0;
	unsigned int input;
	while (!feof(f_in)){
		fscanf(f_in,"%u\n",&input);
		counts ++;
	}
	fclose(f_in);	
	return counts;
}

void display_courses_under_department(char *input_name , char department[]){
	FILE *f_in; 
	f_in = fopen(input_name,"r");
	unsigned int input;
	int bin[32];
	while (!feof(f_in)){
		fscanf(f_in,"%u\n",&input);
		//printf("%u\n", input);
		convertUnsignedInt2bin(input,bin,32);	
		char output_string[16];
		convertBin2String(bin, output_string);
		if (department[0] == output_string[3] && department[1] == output_string[4] && department[2] == output_string[5]){
			printf("decoded string: %s\n", output_string);
		}
	}
	fclose(f_in);	
}

void display_courses_under_grade(char *input_name, char grade[]){
	FILE *f_in; 
	f_in = fopen(input_name,"r");
	unsigned int input;
	int bin[32];
	while (!feof(f_in)){
		fscanf(f_in,"%u\n",&input);
		convertUnsignedInt2bin(input,bin,32);	
		char output_string[16];
		convertBin2String(bin, output_string);
		if (grade[0] == output_string[10] && grade[1] == output_string[11]){
			printf("decoded string: %s\n", output_string);
		}
	}
	fclose(f_in);	
}

void display_courses_under_credit(char *input_name, char credit[]){
	FILE *f_in; 
	f_in = fopen(input_name,"r");
	unsigned int input;
	int bin[32];
	while (!feof(f_in)){
		fscanf(f_in,"%u\n",&input);
		convertUnsignedInt2bin(input,bin,32);	
		char output_string[16];
		convertBin2String(bin, output_string);
		if (credit[0] == output_string[12] && credit[2] == output_string[13]){
			printf("decoded string: %s\n", output_string);
		}
	}
	fclose(f_in);	
}

void display(){
	puts("n - display the total number of courses");
	puts("d - list all courses from a particular department (prompt for number");
	puts("l - list all courses with a particular letter grade  (prompt for grade e.g. A+) ");
	puts("c - list all courses with at least a specified number of credits (prompt for credits)");
	puts("g - compute the GPA of all the courses with letter grades (skipping those with 'I', 'S' or 'U' grades)");
	puts("q - quit the program");
	puts("Enter letter choice ->");
}

int main(int argc, char ** argv){

	display();
	// read records from file and transfer the integer data to char array write to file
	char option[2];
	scanf("%s",option);

	while(option[0] != 'q'){
		switch(option[0]){
			case 'n':{
				int num_records;
				num_records = count(argv[1]);
				printf("There are total %d courses\n",num_records);
				break;
			}
			case 'd':{
				char department[4];
				puts("please type a department of format XXX");
				scanf("%s", department);
				display_courses_under_department(argv[1],department);
				break;
			}
			case 'l':{
				char grade[3];
				puts("please type a letter grade of format XX");
				scanf("%s", grade);
				display_courses_under_grade(argv[1], grade);
				break;
			}
			case 'c':{
				char credit[4];
				puts("please type a letter grade of format XX");
				scanf("%s", credit);
				display_courses_under_credit(argv[1],credit);
				break;
			}
			case 'g':{
				//double gpa = compute_grades(argv[1]);
				//printf("")
				break;
			}
			case 'q':{
				exit(1);
			}
			default:{
				break;
			}
		}
		display();
		scanf("%s",option);
	}

	return 0;
}

