#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(int argc, char **argv){
	/*****************       declare functions    ************************/
	void generate_div(int num, char division[]);
	void generate_charArray(int num, char array[], int length);
	void generate_grade(int num, char grade[]);
	void generate_credit(int num, char credit[]);
	void generate_output(char division[], char department[], char course[], char grade[], char credit[], char output_string[]);
	/***************         declare char arrays   **********************/
	char division[3];
	char department[4];
	char course[3];
	char grade[2];
	char credit[3];
	char output_string[16];
	/*****************      main function      ****************/
	FILE* f_out;
	f_out = fopen(argv[1],"w");
	printf("Please input number of course strings you want to generate: \n");
	int num_strings;
	scanf("%d", &num_strings);
	while (num_strings > 0){
		num_strings--;
		int div_num = rand() % 8;
		int dep_num = (rand() % 9+1) *(int) pow(10,2) + (rand() % 10) * (int) pow(10,1) + rand() % 10;
		int course_num = (rand() % 9+1) *(int) pow(10,2) + (rand() % 10) * (int) pow(10,1) + rand() % 10;
		int grade_num = (rand() % 9 + 1) * (int) pow(10,1) + rand() % 3;
		int credit_num = (rand() % 6 + 1) * (int) pow(10,1) + rand() %2;
		printf("division: %d\n", div_num);
		printf("department: %d\n", dep_num);
		printf("course_num: %d\n", course_num);
		printf("grade: %d\n", grade_num);
		printf("credit: %d\n", credit_num);
		printf("-----------******************------------\n");
		generate_div(div_num,division);
		generate_charArray(dep_num,department,4);
		generate_charArray(course_num,course,3);
		generate_grade(grade_num,grade);
		generate_credit(credit_num, credit);
		generate_output(division,department,course,grade,credit,output_string);
		fprintf(f_out, "%s\n",output_string);
	}
	fclose(f_out);
}

void generate_div(int num, char division[]){
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

void generate_charArray(int num, char array[],int length){
	int mod;
	int i = 0;
	if (num < 100  || num > 1000){
		puts("wrong input #");
		printf("%d\n",num);
		exit(-1);
	}else{
		while (num > 0){
			mod = num % 10;
			array[2-i] = mod + '0';
			num = num/10;
			i++;
		}	
	}
	if (length > 3) array[i] = '.';
}

void generate_grade(int num, char grade[]){
	int quo, mod;
	mod = num % 10;
	quo = num/10;
	switch(quo){
		case 1:
			grade[0] = 'A';
			break;
		case 2:
			grade[0] = 'B';
			break;
		case 3:
			grade[0] = 'C';
			break;
		case 4:
			grade[0] = 'D';
			break;
		case 5:
			grade[0] = 'F';
			break;
		case 6:
			grade[0] = 'I';
			break;
		case 7:
			grade[0] = 'S';
			break;
		default:
			grade[0] = 'U';
	}
	switch(mod){
		case 1:
			grade[1] = '+';
			break;
		case 2:
			grade[1] = '-';
			break;
		default:
			grade[1] ='\\';
	}
}


void generate_credit(int num, char credit[]){
	int mod, quo;
	mod = num % 10;
	quo = num/10;
	credit[0] = quo +'0';
	credit[1] = '.';

	(mod == 0) ? (credit[2] = '0'):(credit[2] = '5');
}


void generate_output(char division[], char department[], char course[], char grade[], char credit[], char output_string[]){
	int div_counter, dep_counter, course_counter,grade_counter,credit_counter;
	div_counter = dep_counter = course_counter = grade_counter = credit_counter = 0;
	for (int i = 0; i < 16; i++){
		if ( i < 3){
			output_string[i] = division[div_counter++];
		}else if ( 3<=i  && i < 7){
			output_string[i] = department[dep_counter++];
		}else if ( 7<=i && i < 10){
			output_string[i] = course[course_counter++];
		}else if ( 10<=i && i < 12){
			output_string[i] = grade[grade_counter++];
		}else if (12<= i && i < 15){
			output_string[i] = credit[credit_counter++];
		}else{
			output_string[i] = '\0';
		}
	}
}









