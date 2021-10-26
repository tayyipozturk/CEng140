#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

char *formula;

int intervals;
long int experiments;

int n_var ,l_var[26];

int i,j,k;

char *letter;
double **table;
double **limits;

double *numbers;

char *stack,*queue;
int p,s,t;
int q=0;

int count;
char *temporary;
char *operator;
double *processor;

long int r;
long int sum_below, sum_above=0;
long int top,bottom;
long int amount;
long int temp;

long int counter;
long int *probabilities;
long int box;
long int total;

double max, min;
double gap;
double portion;
double result;

void count_variables(char* line){
    for(i=0;i<strlen(line);i++){
        if(line[i]>='A' && line[i]<='Z'){
            switch(l_var[line[i]-65]){
                case 0: n_var++;l_var[line[i]-65]++;break;
            }
        }
    }
}

int baba(char* expression){
	while(*expression){
		if(*expression=='i' || *expression=='o' || *expression=='l' || *expression=='r' || *expression=='~'){
			stack[s++]=*expression;
		}
		else if(*expression=='^'){
			if(stack[s-1]=='i' || stack[s-1]=='o' || stack[s-1]=='l' || stack[s-1]=='r' || stack[s-1]=='~'){
				while(stack[s-1]=='i' || stack[s-1]=='o' || stack[s-1]=='l' || stack[s-1]=='r' || stack[s-1]=='~'){
					queue[q++]=stack[s-1];
					s--;
				}
				stack[s++]='^';
			}
			else{
				stack[s++]='^';
			}
		}
		else if(*expression=='*'){
			if(stack[s-1]=='i' || stack[s-1]=='o' || stack[s-1]=='l' || stack[s-1]=='r' || stack[s-1]=='~' || stack[s-1]=='^' || stack[s-1]=='*' || stack[s-1]=='/'){
				while(stack[s-1]=='i' || stack[s-1]=='o' || stack[s-1]=='l' || stack[s-1]=='r' || stack[s-1]=='~' || stack[s-1]=='^' || stack[s-1]=='*' || stack[s-1]=='/'){
					queue[q++]=stack[s-1];
					s--;
				}
				stack[s++]='*';
			}
			else{
				stack[s++]='*';
			}
		}
		else if(*expression=='/'){
			if(stack[s-1]=='i' || stack[s-1]=='o' || stack[s-1]=='l' || stack[s-1]=='r' || stack[s-1]=='~' || stack[s-1]=='^' || stack[s-1]=='*' || stack[s-1]=='/'){
				while(stack[s-1]=='i' || stack[s-1]=='o' || stack[s-1]=='l' || stack[s-1]=='r' || stack[s-1]=='~' || stack[s-1]=='^' || stack[s-1]=='*' || stack[s-1]=='/'){
					queue[q++]=stack[s-1];
					s--;
				}
				stack[s++]='/';
			}
			else{
				stack[s++]='/';
			}
		}
		else if(*expression=='+'){
			if(stack[s-1]=='i' || stack[s-1]=='o' || stack[s-1]=='l' || stack[s-1]=='r' || stack[s-1]=='~' || stack[s-1]=='^' || stack[s-1]=='*' || stack[s-1]=='/' || stack[s-1]=='+' || stack[s-1]=='-'){
				while(stack[s-1]=='i' || stack[s-1]=='o' || stack[s-1]=='l' || stack[s-1]=='r' || stack[s-1]=='~' || stack[s-1]=='^' || stack[s-1]=='*' || stack[s-1]=='/' || stack[s-1]=='+' || stack[s-1]=='-'){
					queue[q++]=stack[s-1];
					s--;
				}
				stack[s++]='+';
			}
			else{
				stack[s++]='+';
			}
		}
		else if(*expression=='-'){
			if(stack[s-1]=='i' || stack[s-1]=='o' || stack[s-1]=='l' || stack[s-1]=='r' || stack[s-1]=='~' || stack[s-1]=='^' || stack[s-1]=='*' || stack[s-1]=='/' || stack[s-1]=='+' || stack[s-1]=='*'){
				while(stack[s-1]=='i' || stack[s-1]=='o' || stack[s-1]=='l' || stack[s-1]=='r' || stack[s-1]=='~' || stack[s-1]=='^' || stack[s-1]=='*' || stack[s-1]=='/' || stack[s-1]=='+' || stack[s-1]=='-'){
					queue[q++]=stack[s-1];
					s--;
				}
				stack[s++]='-';
			}
			else{
				stack[s++]='-';
			}
		}
		else if(*expression=='('){
			stack[s++]='(';
		}
		else if(*expression==')'){
			s--;
			while(stack[s]!='('){
				queue[q++]=stack[s--];
			}
		}
		else if(*expression>='A' && *expression<='Z'){
			queue[q++]=*expression;
		}
		else if((*expression>='0' && *expression<='9') || *expression=='.'){
			while((*expression>='0' && *expression<='9') || *expression=='.'){
				queue[q++]=*expression++;
			}
			queue[q++]='%';
			expression--;
		}
		expression++;
	}
	s--;
	while(s>=0){
		if(stack[s]!='(' && stack[s]!=')'){
			queue[q++]=stack[s--];
		}
		else{
			s--;
		}
	}
	return q;
}

void compute(){
	for(p=0;p<q;p++){
		if(queue[p]>='A' && queue[p]<='Z'){
			for(i=0;i<n_var;i++){
				if(letter[i]==queue[p]){
					processor[++t]=numbers[i];
				}
			}
		}
		else if((queue[p]>='0' && queue[p]<='9') || queue[p]=='.'){
			while(queue[p]!='%'){
				temporary[count++]=queue[p++];
			}
			temporary[count]=0;
			sscanf(temporary, "%lf", &processor[++t]);
			count=0;
		}
		else if(queue[p]=='i' || queue[p]=='o' || queue[p]=='r' || queue[p]=='l' || queue[p]=='~'){
			if(queue[p]=='i'){
				processor[t]=sin(processor[t]);
			}
			else if(queue[p]=='o'){
				processor[t]=cos(processor[t]);
			}
			else if(queue[p]=='r'){
				processor[t]=sqrt(processor[t]);
			}
			else if(queue[p]=='l'){
				processor[t]=log(processor[t]);
			}
			else if(queue[p]=='~'){
				processor[t]=(-1)*(processor[t]);
			}
		}
		else if(queue[p]=='^' || queue[p]=='*' || queue[p]=='/' || queue[p]=='+' || queue[p]=='-'){
			if(queue[p]=='^'){
				processor[t-1]=pow(processor[t-1],processor[t]);
			}
			else if(queue[p]=='*'){
				processor[t-1]=processor[t-1]*processor[t];
			}
			else if(queue[p]=='/'){
				processor[t-1]=processor[t-1]/processor[t];
			}
			else if(queue[p]=='+'){
				processor[t-1]=processor[t-1]+processor[t];
			}
			else if(queue[p]=='-'){
				processor[t-1]=processor[t-1]-processor[t];
			}
			processor[t]=0;
			t--;
		}
	}
	t=0;
}

int main(){
    formula=malloc(200*sizeof(char));

    gets(formula);

    scanf("%d %ld",&intervals,&experiments);

    count_variables(formula);

    numbers=malloc(n_var*sizeof(double));
    letter=malloc(n_var*sizeof(char));

    table=malloc(n_var*sizeof(double*));
    limits=malloc(n_var*sizeof(double*));

    for(i=0;i<n_var;i++){
        table[i]=malloc(intervals*sizeof(double));
        limits[i]=malloc(2*sizeof(double));
    }

    stack=malloc(200*sizeof(char));
    queue=malloc(200*sizeof(char));

    operator=malloc(sizeof(char));
    processor=malloc(200*sizeof(double));
    temporary=malloc(200*sizeof(char));

    for(i=0;i<n_var;i++){
        scanf(" %c %lf %lf",&letter[i], &limits[i][0], &limits[i][1]);
        for(j=0;j<intervals;j++){
            scanf("%lf",&table[i][j]);
        }
    }
 	
    baba(formula);
 	
 	srand(time(NULL));
 	for(counter=0;counter<experiments;counter++){
		for(i=0;i<n_var;i++){
		r = rand()%10000;
		top = 10000*limits[i][0];
		amount = 10000*(limits[i][1]-limits[i][0])/intervals;
		sum_above=0;
			for(j=0;j<intervals;j++){
				sum_below=sum_above;
				sum_above+=table[i][j]*10000;
				bottom=top;
				top+=amount;
				if(r>=sum_below && r<=sum_above){
					temp=rand()%(top-bottom)+bottom;
					/*printf("Temp:%ld\n",temp);*/
					numbers[i]=((double)temp)/10000;
					/*printf("i:%d %c Number:%lf\n",i,letter[i], numbers[i]);*/
					break;
				}
			}
 		}
 		compute();

 		if(counter==0){
 			max=processor[1];
 			min=processor[1];
 		}
	 	if(processor[1]>max){
	 		max=processor[1];
	 	}
	 	else if(processor[1]<min){
	 		min=processor[1];
	 	}
	}

	probabilities=malloc(intervals*sizeof(long int));

	for(counter=0;counter<experiments;counter++){
		for(i=0;i<n_var;i++){
		r = rand()%10000;
		top = 10000*limits[i][0];
		amount = 10000*(limits[i][1]-limits[i][0])/intervals;
		sum_above=0;
			for(j=0;j<intervals;j++){
				sum_below=sum_above;
				sum_above+=table[i][j]*10000;
				bottom=top;
				top+=amount;
				if(r>=sum_below && r<=sum_above){
					temp=rand()%(top-bottom)+bottom;
					numbers[i]=((double)temp)/10000;
					break;
				}
			}
 		}
 		compute();
 		gap=max-min;
 		portion=gap/(double)intervals;
 		box=(long int)((processor[1]-min)/portion);
 		probabilities[box]+=1;
 		total++;
	}
	printf("%.3f %.3f",min,max);
	for(i=0;i<intervals;i++){
		result=((double)probabilities[i])/((double)total);
		printf(" %.3f",result);
	}
	printf("\n");

	return 0;
}