//******************************************************************
//please refer slide no 15 and 16 for equations
//******************************************************************

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

FILE *fp;
typedef struct{
	char name[30];
	double multiple;
	double serv_time;
	double *util;
	double *request;
	double *response;
}resource;

typedef struct{
	char name[30];
	double arr_rate;
	double *visits;
}class; 

class classes[30];
resource resources[30];
int res_size,class_size;

void extract_data(){
	int i,j;
	char garbage[100];
	fscanf(fp,"%[^\n]s ",garbage);
	fscanf(fp,"%d ",&res_size);
	for(i=0;i<res_size;i++){
		fscanf(fp,"%s %lf %lf ",resources[i].name,
			&resources[i].multiple,&resources[i].serv_time);
	}
	fscanf(fp,"%[^\n]s ",garbage);
	fscanf(fp,"%d ",&class_size);
	for(i=0;i<class_size;i++){
		classes[i].visits = (double *)malloc(sizeof(double)*res_size);
		fscanf(fp,"%s %lf ",classes[i].name,&classes[i].arr_rate);
		for(j=0;j<res_size;j++)
			fscanf(fp,"%lf ",&classes[i].visits[j]); 
	}
	for(i=0;i<res_size;i++){
		resources[i].util = (double *)malloc(sizeof(double)*class_size);
		resources[i].request = (double *)malloc(sizeof(double)*class_size);
		resources[i].response = (double *)malloc(sizeof(double)*class_size);
	}
}

void queue_nw(){
	int i,j;
	printf("Performance Parameters for:\n\n");
	for(i=0;i<class_size;i++){
		printf("CLASS %d -->\n",i+1);
		printf("UTILIZATION --> ");
		for(j=0;j<res_size;j++){
			resources[j].util[i] = classes[i].arr_rate*classes[i].visits[j]*resources[j].serv_time/resources[j].multiple;
			printf("RES%d=%f ",j+1,resources[j].util[i]);
		}
		printf("\n");
	}
	double sum;
	for(i=0;i<res_size;i++){
		sum=0;
		printf("\nRESOURCE%d --> \n",i+1);
		for(j=0;j<class_size;j++) sum += resources[i].util[j];
		printf("TOTAL UTILIZATION = %f\n",sum);
		printf("Response Time\t Average No. of request -->\n");
		for(j=0;j<class_size;j++){
			resources[i].request[j] = resources[i].util[j]/(1-sum);
			resources[i].response[j] = (classes[j].visits[i] * resources[i].serv_time/resources[i].multiple)/(1-sum);
			printf("CLASS%d= %f,%f ",j+1,resources[i].response[j],resources[i].request[j]);
		}
		sum=0;
		for(j=0;j<class_size;j++) sum+=resources[i].request[j];
		printf("\nAverage No. of requests=%f\n",sum); 
	}
	for(i=0;i<class_size;i++){
		printf("\nCLASS%d -->",i+1);
		sum=0;
		for(j=0;j<res_size;j++) sum += resources[j].response[i];
		printf("Average Respnse Time=%f\n",sum);
	}
	printf("\n");
}

int main(){
	int i,j;
	fp = fopen("data.csv","r");
	extract_data();
	fclose(fp);
	printf("\nRESOURCEs\n");
	for(i=0;i<res_size;i++)	printf("%d) %s %f %f\n",i+1,resources[i].name
									,resources[i].multiple,resources[i].serv_time);
	printf("\n");
	printf("CLASSEs\n");
	for(i=0;i<class_size;i++){
		printf("%d) %s %f ",i+1,classes[i].name,classes[i].arr_rate);
		for(j=0;j<res_size;j++)	printf("%f ",classes[i].visits[j]);
		printf("\n");
	}
	printf("\n");
	queue_nw();	
}
/*
Name     Multiple   service
3
CPU 		1 		0.015 
DISK1 		2	 	0.008 
DISK2		1		0.008

Name	Arrival_rate	visits
2
Queries		2		1	2	0
Updates		2		1	0	1 
*/
