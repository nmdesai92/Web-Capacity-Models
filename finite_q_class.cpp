/*This code calculates parameters for infinite population, finite queue model
 that is, infinite requests, finite server capacity model. If more than 'W' requests 
 comes, they will be rejected.
 Equations are given in Slides/Web_Capacity_models.ppt slide no. 7,8.
 
 All formulas taken from Chapter 8 of book Capacity Planning for Web Services: metrics, models, and methods
 Book URL  https://cs.gmu.edu/~menasce/webservices/
 */

#include <iostream>
#include <cstdio>
#include <cmath>


using namespace std;


class finite_q{
		int arrival_rate;
		int throughput;
		int W;
	public:
		finite_q(int a, int t, int W){
			arrival_rate = a;
			throughput = t;
			this->W = W;
		}
		float calculate_p_k(int k);	//Fraction of time when the server has k requests.
		float server_Utilization();
		int Avg_server_throughput();
		float avg_no_of_req();		//Average number of requests in the server
		float avg_response_time();	// Average response time to process each request	
};

float finite_q :: calculate_p_k(int k)
{
	float U = (float)arrival_rate/(float)throughput;
	float p_k;
	
	if(arrival_rate != throughput){
		p_k = ((1 - U)*pow(U,k))/(1-pow(U,W+1));
	}
	else{
		p_k = 1/(float)(W+1);
	}
	return p_k;
}

float finite_q :: server_Utilization()
{
	float U = (float)arrival_rate/(float)throughput;
	float util;
	if(arrival_rate != throughput){
		util = (U*(1 - pow(U,W)))/(1 - pow(U,W+1));
	}	
	else{
		util = W/(W+1);
	}

}

int  finite_q:: Avg_server_throughput()
{
	float U = (float)arrival_rate/(float)throughput;
	return U*throughput;
}

float finite_q :: avg_no_of_req()
{
	float U = (float)arrival_rate/(float)throughput;
	int N_bar;
	float temp1 = pow(U,W+1);
	float temp2 = (W+1)*pow(U,W);

	if(arrival_rate != throughput){
		N_bar = (U*(W*temp1 - temp2 + 1))/((1 - temp1)*(1 - U));
	}
	else{
		N_bar = W/2;
	}

}

float finite_q :: avg_response_time()
{
	return avg_no_of_req()/Avg_server_throughput();
}



int main()
{
	unsigned int arrival_rate, throughput,W;
	
	//Take inputs
	cout << "Enter Arrival rate: ";
	cin  >> arrival_rate;						//Take this as 30
	cout << "Enter Average throughput: ";
	cin  >> throughput;							//Take this as 50
	cout << "Enter Max queue length: ";
	cin  >> W;									//Take this as 4

	finite_q server1(arrival_rate,throughput,W);

	//Fraction of time server has k requests
	//For finite queue, Maximum W requests are possible.
	for(int k = 0;k <= W;k++){
		float p_k = server1.calculate_p_k(k);
		cout << k << ":  " << p_k << endl;
	}

	cout << "Server Utilization U 		: " << server1.server_Utilization() << endl; 
	cout << "Average Server throughput 	: " << server1.Avg_server_throughput() << endl;
	cout << "Average no of requests 	: " << server1.avg_no_of_req() << endl;
	cout << "Average avg_response_time	: " << server1.avg_response_time() <<endl;
	return 0;

}

