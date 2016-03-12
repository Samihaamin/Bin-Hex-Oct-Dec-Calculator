#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

struct Number{
	char type[1];
	char * value;
	int negative;
};

//Takes in an int solution and a char base
//Uses the char base to convert the solution into the output base
//Determines if the solution is positive or negative and prints accordingly
void Formatter(int Sol, char *  base){

   if ((strcmp(base, "d") == 0)){
	
	if (Sol<0){
		Sol = Sol * (-1);
		printf("-%s%i\n",base,Sol);
	}
	else {
	printf("%s%i\n",base,Sol);
	}
	}

 else  if ((strcmp(base, "b") == 0)){

        if (Sol<0){
                Sol = Sol * (-1);
                printf("-%s",base);
        }
        else {
        printf("%s",base);
        }

	int c, k;
	int check = 0;
	
	for (c = 31; c>= 0; c--){
	k = Sol >> c;
	
	if (k & 1){
	printf("1");
	check = 1;
        }
	else if (check == 1) {
	printf("0");
	}
	else {
	continue;
	}
     }
	printf("\n");
}
 else if ((strcmp(base, "x") == 0)){

        if (Sol<0){
                Sol = Sol * (-1);
                printf("-%s",base);
        }
        else {
        printf("%s",base);
        }
	
	int r;
	int quo = Sol;
	int i = 1;
	
	char hex[100];

	while (quo != 0){	
		
		r = quo%16;
		
		if (r<10){
		r  = r+48;
                }
		else r = r+55;

		hex[i++] = r;

		quo = quo/16;
	}
	int j;	
	for (j = i - 1; j>0;j--){
        printf("%c",hex[j]);
}
        printf("\n"); 
       }


 else if ((strcmp(base, "o") == 0)){

        if (Sol<0){
                Sol = Sol * (-1);
                printf("-%s",base);
        }
        else {
        printf("%s",base);
        }
	
	int octnum[100];
	int i =1; 
	int j;
	
	int quo = Sol;
	while (quo!=0){
	octnum[i++] = quo%8;
	quo = quo/8;

	}
	for (j = i - 1; j>0;j--){
	printf("%i", octnum[j]);}
	printf("\n");
	}

}

//takes in a string and breaks it down into negative sign (if exists), type and decimal number
//Uses the type determined to convert to decimal int
int generateDec( char * Num ){

	if (strlen(Num)<=1){
	fprintf(stderr,"ERROR: Number format invalid");
	}

	char* iterator = &Num[0];

	struct Number *result =(struct Number*) malloc(sizeof(struct Number));

	int k = 0;
        if (*iterator == '-'){
       		result->negative = -1;
       		iterator++;
		k++;
       	}  
	else {result->negative = 1;}

	if((*iterator == 'd') || (*iterator == 'x') || (*iterator == 'b') ||(*iterator == 'o')){		
     			result->type[0] = *iterator;
			result->type[1] = '\0';
       			iterator++;
			k++;
    		}
       	else {
       		fprintf(stderr,"ERROR: Number format wrong. Enter as -?(b|o|d|x)<digits>.\n");
       		exit(0);
       	}

	int i = 0;
       	
	result->value=malloc(sizeof(Num));
	
	while (k!=strlen(Num)){
	result->value[i] = *iterator;
       		iterator++;
       		i++;
		k++;
       	}
       result->value[i]='\0';	
 
	int final = 0;

	//converting decimal string to decimal int
	if (result->type[0] == 'd'){
	
		int j = 0;
		while (result->value[j] != '\0'){
	
			if(isdigit(result->value[j]==0)){
			fprintf(stderr,"ERROR: Decimal numbers can only consist of digits.");
			exit(0);}
			
                        final = (final*10) + (result->value[j] - '0');
                        j++;
        }
	}
	//converting binary string to decimal int
	if (result->type[0] == 'b'){
		int j = 0;
                while (result->value[j] != '\0'){
		if (result->value[j] == '1'){
		final = final + pow(2, (strlen(result->value)-1) - j);
		j++;
		}
		else if (result->value[j] == '0'){
		j++;}
		else {fprintf(stderr,"ERROR: Binary Number can only consist of 0 and 1");
			exit(0);}		
		}
	}
	
	//converting octal string to decimal int
	 if (result->type[0] == 'o'){

                int j = 0;
                while (result->value[j] != '\0'){
		if (result->value[j]=='8' || result->value[j]=='9' || (isdigit(result->value[j])==0)){
			fprintf(stderr,"ERROR: Octal Numbers can only consist of 0,1,2,3,4,5,6,7.");
			exit(0);}
		int Cbase = pow(8,(strlen(result->value)-1) - j);
		final = final + ((result->value[j] - '0') * Cbase);
		j++;
		}
	}
	
	//converting hexadecimal string to decimal int	
	if (result->type[0] == 'x'){

                int j = 0;
                while (result->value[j] != '\0'){
		
		int Cbase = pow(16,(strlen(result->value)-1) - j);
		if (isdigit(result->value[j])>0){		
			final = final + ((result->value[j] - '0') * Cbase);
			j++;}
		else if(result->value[j] == 'A'){
		final = final + (10 * Cbase);
		j++;}
		else if(result->value[j] == 'B'){
                final = final + (11 * Cbase);
                j++;}
		else if(result->value[j] == 'C'){
                final = final + (12 * Cbase);
                j++;}
		else if(result->value[j] == 'D'){
                final = final + (13 * Cbase);
                j++;}
		else if(result->value[j] == 'E'){
                final = final + (14 * Cbase);
                j++;}
		else if(result->value[j] == 'F'){
                final = final + (15 * Cbase);
                j++;}
		else {
		fprintf(stderr,"ERROR: Hexademical numbers can only consist of digits and letters A-F.");
		exit(0);}
	}
	}
	final = final * result->negative;
	
	free(result);
	free(result->value);
	return(final);
}

int main ( int argc, char *argv[] ){
	 if (argc != 5){
                fprintf(stderr,"ERROR: Number Of Arguments Passed Wrong. Exiting Program\n");
                exit(0);
        }
	char * operator = argv[1];

        if ((strcmp(operator, "+") != 0) && (strcmp(operator, "-") != 0) && (strcmp(operator, "*") != 0)){
                fprintf(stderr,"ERROR: Invalid Operator. Can Only Accept +, - or *. Exiting Program\n");
                exit(0);
        }
	 char * base = argv[4];

        if((strcmp(base, "d") != 0) && (strcmp(base, "x") != 0) && (strcmp(base, "o") != 0) && (strcmp(base, "b") != 0)){
                fprintf(stderr,"ERROR: Invalid Output Base. Can Only Accept lower case d, x, o or b. Exiting Program\n");
                exit(0);
        }

	
        char * Num1 = strdup(argv[2]);
       	int Dec1 =  generateDec(Num1);
       
        char * Num2 = strdup(argv[3]);
        int Dec2 =  generateDec(Num2);

	int solution= 0;

	//performing calculations on the decimal numbers
        if (strcmp(operator,"+")==0){
                solution = Dec1 + Dec2;}

	if (strcmp(operator,"-")==0){
                solution = Dec1 - Dec2;}

	if (strcmp(operator,"*")==0){
                solution = Dec1 * Dec2;}

	Formatter(solution,base);

        free(Num1);
        free(Num2);

    return(0);

}

