#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *ptr,*left,*right;
char **table_left, **table_right;
char *lhs,*rhs;
int p,q,boolean;

int lever=0,counter_left=0,counter_right=0;
int i=0,j=0,m=0,n=0;
int k=0,l=0;

void func(char** pl, char** pr, int wc_l, int wc_r);
void control();

void func(char** pl, char** pr, int wc_l, int wc_r){
	for(k=0;k<wc_l;k++){
		if(pl[k][0]){
			char *start, *one_more, *operator=0;
			int count=0,x=0, y=0, z=0, r=0;
			int cl=0;
			int t;
			
			start=&pl[k][y];
			one_more=start+1;
			
			if(*start=='-'){
				while(*one_more){
					pr[wc_r][z++]=*one_more++;
				}
				pr[wc_r++][z]=0;

				for(t=0;t<200;t++){
					pl[k][t]=0;
				}
				continue;
			}
				while(pl[k][x]){
					if(pl[k][x]=='('){
						count++;
					}
					else if(pl[k][x]==')'){
						count--;
					}
					else{
						if(count==1 && (pl[k][x]=='&' || pl[k][x]=='|' || pl[k][x]=='>')){
							operator=&pl[k][x];
							if(*operator=='&'){
								while(*one_more!=*operator){
									*start++=*one_more++;
									cl++;
								}
								*start=0;
								start-=cl;
								x++; 
								while(pl[k][x+1]){
									pl[wc_l][r++]=pl[k][x++];
								}
								pl[wc_l++][r]=0;
							}
							else if(*operator=='|'){
								while(*one_more!=*operator){
									*start++=*one_more++;
									cl++;
								}
								*start=0;
								start-=cl;
								x++; 
								while(pl[k][x+1]){
									pl[wc_l][r++]=pl[k][x++];
								}
								pl[wc_l++][r]=0;
							}
							else if(*operator=='>'){
								*start++='-';
								while(*one_more!=*operator){
									*start++=*one_more++;
									cl++;
								}
								*start--=0;
								start-=cl;
								x++; 					
								while(pl[k][x+1]){
										pl[wc_l][r++]=pl[k][x++];
								}
								pl[wc_l++][r]=0;
							}
						}
					}
					x++;
				}
		}
	}
	for(l=0;l<wc_r;l++){
		if(pr[l][0]){
			char *first, *after, *change=0;
			int count_r=0, u=0, v=0, w=0, s=0;
			int lc=0;
			int t;

			first=&pr[l][v];
			after=first+1;

			if(*first=='-'){
				while(*after){
					pl[wc_l][w++]=*after++;
				}
				pl[wc_l++][w]=0;

				for(t=0;t<200;t++){
					pr[l][t]=0;
				}
				continue;
			}
				while(pr[l][u]){
					if(pr[l][u]=='('){
						count_r++;
					}
					else if(pr[l][u]==')'){
						count_r--;
					}
					else{
						if(count_r==1 && (pr[l][u]=='&' || pr[l][u]=='|' || pr[l][u]=='>')){
							change=&pr[l][u];
							if(*change=='&'){
								while(*after!=*change){
									*first++=*after++;
									lc++;
								}
								*first=0;
								first-=lc;
								u++;
								while(pr[l][u+1]){
									pr[wc_r][s++]=pr[l][u++];
								}
								pr[wc_r++][s]=0;
							}
							else if(*change=='|'){
								while(*after!=*change){
									*first++=*after++;
									lc++;
								}
								*first=0;
								first-=lc;
								u++;
								while(pr[l][u+1]){
									pr[wc_r][s++]=pr[l][u++];
								}
								pr[wc_r++][s]=0;
							}
							else if(*change=='>'){
								*first++='-';
								while(*after!=*change){
									*first++=*after++;
									lc++;
								}
								*first--=0;
								first-=lc;
								u++;
								while(pr[l][u+1]){
									pr[wc_r][s++]=pr[l][u++];
								}
								pr[wc_r++][s]=0;
							}
						}
					}
				u++;
			}
		}
	}
	i=wc_l;
	m=wc_r;
}

void control(){
	for(p=0;p<i;p++){
		if(table_left[p][0]<'A' || table_left[p][0]>'Z'){
			func(table_left,table_right,i,m);
		}
		else{
			for(q=0;q<m;q++){
				if(table_right[q][0]<'A' || table_right[q][0]>'Z'){
					func(table_left,table_right,i,m);
				}
				else{
					if(table_left[p][0]==table_right[q][0]){
						boolean=1;
						break;
					}
				}
			}
		}
	}
	if(boolean==1){
		printf("T\n");
	}
	else{
		printf("F\n");
	}
}

int main(){
	ptr=malloc(sizeof(char)*200);
	left=malloc(sizeof(char)*200);
	right=malloc(sizeof(char)*200);
	lhs=malloc(sizeof(char)*200);
	rhs=malloc(sizeof(char)*200);
	
	scanf("%s", ptr);

	while(*ptr){
		if(lever==0){
			if(*ptr!='#'){
				*left++=*ptr++;
				counter_left++;
			}
			else{
				lever=1;
				ptr++;
			}
		}
		else{
			*right++=*ptr++;
			counter_right++;
		}
	}
	*left='\0';
	*right='\0';
	
	left-=counter_left++;
	right-=counter_right++;

	table_left=malloc(sizeof(char*)*499);
	table_right=malloc(sizeof(char*)*499);

	for(i=0;i<499;i++){
		table_left[i]=malloc(sizeof(char)*200);
	}
	
	for(i=0;i<499;i++){
		table_right[i]=malloc(sizeof(char)*200);
	}

	for(i=0,j=0;*left;++left){
		if(*left==','){
			table_left[i][j]=0;
			j=0;
			i++;
		}
		else{
			table_left[i][j++]=*left;
		}
	}
	for(m=0,n=0;*right;++right){
		if(*right==','){
			table_right[m][n]=0;
			n=0;
			m++;
		}
		else{
			table_right[m][n++]=*right;
		}
	}
	table_left[i][j]=0;
	table_right[m][n]=0;
	i++;
	m++;

	
	func(table_left,table_right,i,m);
	control();

	free(lhs);
	free(rhs);

	return 0;
}