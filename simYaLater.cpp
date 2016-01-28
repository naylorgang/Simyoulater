
#include <iostream>
#include <cstdlib>
#include <iomanip>
#include <cmath>

#include "simulation.h"
#include "queueAsArray.h" 

using namespace std;

void setSimulationParameters(int& sTime, int& numOfServers,
		int& transTime,
		int& tBetweenCArrival,unsigned int& seed);

void runSimulation();

int main()
{
	runSimulation();

	return 0;
}

void setSimulationParameters(int& sTime, int& numOfServers,
		int& transTime,
		int& tBetweenCArrival,unsigned int& seed)
{
	cout << "Enter the simulation time: ";
	cin >> sTime;
	cout << endl;

	cout << "Enter the number of servers: ";
	cin >> numOfServers;
	cout << endl;

	cout << "Enter the transaction time: ";
	cin >> transTime;
	cout << endl;

	cout << "Enter the time between customer arrivals: ";
	cin >> tBetweenCArrival;
	cout << endl;

	cout << "Enter your seed (or 0 for no seed) ";
	cin >> seed;
	cout <<endl;
}

void runSimulation()
{
	//cout << "Write the definition of the function runSimulation." << endl;
	//cout << "See programming Exercise 18." << endl;

	int sTime;
	int numOfServers;
	int transTime;
	int tBetweenCArrival;
	unsigned int seed; 
	setSimulationParameters(sTime,numOfServers,transTime,tBetweenCArrival,seed);

	int customerNumber;
	int clock;
	int totalWaitingTime =0;
	int numberOfCustmersServed=0;
	int numberOfCustomersLeftInWaitingQueue=0;
	int numberOfCustomersLeftWithServers=0;
	double threshhold = exp(-1.0/tBetweenCArrival);
	double randomNumber;
	serverListType listOfServers = serverListType(numOfServers);

	waitingCustomerQueueType waitingCustomerQueue = waitingCustomerQueueType();

	if(seed!=0){
		srand(seed);
	} else {
		srand(time(NULL));
	}

	for (clock = 1;clock <= sTime; clock++)
	{
		listOfServers.updateServers(cout);

		if (waitingCustomerQueue.isEmptyQueue() == false)
		{
			waitingCustomerQueue.updateWaitingQueue();
		}

		randomNumber = ((double)rand() / (RAND_MAX));

		if (randomNumber > threshhold)
		{
			customerNumber++;
			cout << "Customer "<<customerNumber<< " enters queue at time "<<clock<<endl;
			numberOfCustomersLeftInWaitingQueue++;
			customerType newCustomer = customerType(customerNumber,clock,0,transTime);
			waitingCustomerQueue.addQueue(newCustomer);
		}

		while (listOfServers.getFreeServerID() != -1  && !waitingCustomerQueue.isEmptyQueue())
		{
			numberOfCustomersLeftInWaitingQueue--;
			customerType sendingCustomer = waitingCustomerQueue.front();
			cout << "Customer "<<sendingCustomer.getCustomerNumber()<< " leaves queue at time "<<clock<<endl;
			listOfServers.setServerBusy(listOfServers.getFreeServerID(),sendingCustomer, transTime);
			waitingCustomerQueue.deleteQueue();
		}
		
		if(!waitingCustomerQueue.isEmptyQueue()){
			totalWaitingTime +=numberOfCustomersLeftInWaitingQueue;
		}
	}

	cout<< "-------------------Simulation Parameters-------------------" <<endl;
	cout<< "Simulation Time: "<< clock <<endl;
	cout<< "Number of Servers: "<< numOfServers << endl;
	cout<< "Transaction Time: " << transTime << endl;
	cout<< "Average Time Between Customer Arrival: "<< tBetweenCArrival << endl;
	cout<< "-------------------Customer Stats-------------------" << endl;
	cout<< "Total Number of Customers Who Arrived: "<<customerNumber <<endl;
	numberOfCustomersLeftWithServers=listOfServers.getNumberOfBusyServers();
	numberOfCustmersServed= (customerNumber-numberOfCustomersLeftInWaitingQueue)-numberOfCustomersLeftWithServers;
	cout<< "Number of Customers Still in the Queue: "<< numberOfCustomersLeftInWaitingQueue <<endl;
	cout<< "Number of Customers at a Server: "<<numberOfCustomersLeftWithServers << endl;
	cout<< "Number of Customers who Completed Service: "<< numberOfCustmersServed<< endl;
	cout<< "Total Waiting Time of All Customers: "<< totalWaitingTime << endl;
	cout<< "Average Waiting Time of All Customers: "<<((double) totalWaitingTime/customerNumber)<< endl << endl;
	cout<< "-------------------Sim Ya Later!-------------------"<<endl<<endl;

}


















