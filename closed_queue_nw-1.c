//******************************************************************
//please refer slide no 17 for equations
//******************************************************************

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

FILE *fp;
typedef struct{
	char name[30];
	int number;
	double multiple;
	double serv_time;
	double visits;
}resource;

resource resources[30];
int res_size;

void extract_data(){
	char fp_name[30],garbage[100];
	fscanf(fp,"%[^\n]c ",garbage);
	double fp_multiple, fp_serv_time, fp_visits;
	while(fscanf(fp,"%s %lf %lf %lf ",fp_name,&fp_multiple,&fp_serv_time,&fp_visits)!=EOF){
		strcpy(resources[res_size].name,fp_name);
		resources[res_size].multiple = fp_multiple;
		resources[res_size].serv_time = fp_serv_time;
		resources[res_size].visits = fp_visits;
		res_size++;
		resources[res_size].number = res_size;
	}
}

void queue_nw(int N){
	int k,i;
	double *new_r,*prev_n,sum,new_x,new_n;
	new_r = (double *)calloc(res_size,sizeof(double));
	prev_n = (double *)calloc(res_size,sizeof(double));
	printf("n[%d] ",0);
	for(i=0;i<res_size;i++) printf("r[%d]=%f ",i+1,(double)0); 
	printf("R0=%f X0=%f ",(double)0,(double)0);
	for(i=0;i<res_size;i++) printf("n[%d]=%f ",i+1,(double)0); printf("\n");
	for(k=1;k<=N;k++){
		printf("n[%d] ",k);
		sum=0;
		for(i=0;i<res_size;i++){
			new_r[i] = (resources[i].visits * resources[i].serv_time)*(1+prev_n[i])/resources[i].multiple;
			printf("r[%d]=%f ",i+1,new_r[i]);
			sum += new_r[i];
		}
		new_x = k/sum;
		printf("R0=%f X0=%f ",sum,new_x);
		for(i=0;i<res_size;i++){
			new_n = new_x * new_r[i];
			printf("n[%d]=%f ",i,new_n);
			prev_n[i]=new_n;
		}
		printf("\n"); 
	}
}

int main(int argc, char **argv){
	int i;
	fp = fopen("data.csv","r");
	extract_data();
	fclose(fp);
	for(i=0;i<res_size;i++) printf("%d) %s %d %f %f\n",resources[i].number,resources[i].name,
							(int)resources[i].multiple,resources[i].serv_time,resources[i].visits);
	if(argc==2) queue_nw(atoi(argv[1]));
	else queue_nw(7);
	return 0;
}
/*
Name	Multiple	service 	visits
CPU		1			0.015		2
DISK1	1			0.008		3
DISK2 	1			0.007		5 
*/
