/*This code simulates for infinite population, infinite queue 
 that is, infinite requests, infinite server capacity model
 Every requests that comes to server will be queued.
 No requests will be rejected.
 Equations are given in Slides/Web_Capacity_models.ppt slide no. 5.
 
 All formulas taken from Chapter 8 of book Capacity Planning for Web Services: metrics, models, and methods
 Book URL  https://cs.gmu.edu/~menasce/webservices/
 */

#include <iostream>
#include <cstdio>
#include <cmath>

using namespace std;


class inf_q{
		int arrival_rate;
		int throughput;
	public:
		inf_q(int arrival_rate,int throughput){
			this->arrival_rate = arrival_rate;
			this->throughput = throughput;
		}

		float calculate_p_k(int k);	//Fraction of time when server has k requests
		float server_Utilization();
		int Avg_server_throughput();
		float avg_no_of_req();		//Average number of requests in the server
		float avg_response_time();	//average response time for each request
};

float inf_q :: calculate_p_k(int k)
{
	float U = (float)arrival_rate/(float)throughput;
	float p_k;
	p_k = (1-U)*pow(U,k);

	return p_k;
}

float inf_q :: server_Utilization()
{
	return (float)arrival_rate/(float)throughput;
}

int  inf_q :: Avg_server_throughput()
{
	return arrival_rate;
}

float inf_q :: avg_no_of_req()
{
	float U = (float)arrival_rate/(float)throughput;
	return U/(1-U);

}

float inf_q :: avg_response_time()
{
	float S = 1/(float)throughput;
	float U = (float)arrival_rate/(float)throughput;
	return S/(1-U);
}



int main()
{
	unsigned int arrival_rate, throughput;
	
	//Take inputs
	cout << "Enter Arrival rate: ";
	cin  >> arrival_rate;						//Take this as 30
	cout << "Enter Average throughput: ";
	cin  >> throughput;							//Take this as 50

	inf_q server1(arrival_rate,throughput);

	//Fraction of time server has k requests
	//for infinite queue, infinite k is possible.
	for(int k = 0;k < 20;k++){
		float p_k = server1.calculate_p_k(k);
		cout << k << ":  "<< p_k << endl;
	}

	cout << "Server Utilization U 		: " << server1.server_Utilization() << endl; 
	cout << "Average Server throughput 	: " << server1.Avg_server_throughput() << endl;
	cout << "Average no of requests 	: " <<  server1.avg_no_of_req() << endl;
	cout << "Average avg_response_time	: " <<  server1.avg_response_time() <<endl;
	
	return 0;

}

