
#include <iostream>
#include <cstdlib>
#include <iomanip>
#include <cmath>

#include "simulation.h"
#include "queueAsArray.h" 

using namespace std;

void setSimulationParameters(int& sTime, int& numOfServers,
                             int& transTime,
                             int& tBetweenCArrival);

void runSimulation();
 
int main()
{
    runSimulation();

    return 0;
}

void setSimulationParameters(int& sTime, int& numOfServers,
							 int& transTime,
							 int& tBetweenCArrival)
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
}

void runSimulation()
{
    //cout << "Write the definition of the function runSimulation." << endl;
    //cout << "See programming Exercise 18." << endl;
    
    int sTime;
    int numOfServers;
    int transTime;
    int tBetweenCArrival;
    
    setSimulationParameters(sTime,numOfServers,transTime,tBetweenCArrival);
    
    int customerNumber;
    int clock;
    int totalWaitingTime;
    int averageWaitingTime;
    int numberOfCustomersArrived;
    int numberOfCustmersServed;
    int numberOfCustomersLeftInWaitingQueue;
    int numberOfCustomersLeftWithServers;

    serverListType listOfServers = serverListType(numOfServers);
    
    waitingCustomerQueueType waitingCustomerQueue = waitingCustomerQueueType();
    
    
    
    double randomNumber;
    srand(time(NULL));
    
    double threshhold = exp(-1.0/tBetweenCArrival);
    
    
    for (clock = 1;clock <= sTime; clock++)
    {
        listOfServers.updateServers(cout);
        
        if (waitingCustomerQueue.isEmptyQueue() == false)
        {
            waitingCustomerQueue.updateWaitingQueue();
        }
        
        randomNumber = ((double)rand() / (INT_MAX));
        
        if (randomNumber > threshhold)
        {
            //cout somthing
            customerNumber++;
            
            customerType newCustomer = customerType(customerNumber,clock,0,transTime);
            waitingCustomerQueue.addQueue(newCustomer);
        }
        

        while (listOfServers.getFreeServerID() != -1  && !waitingCustomerQueue.isEmptyQueue())
        {
            
                customerType sendingCustomer = waitingCustomerQueue.front();
                listOfServers.setServerBusy(listOfServers.getFreeServerID(),sendingCustomer, transTime);
                waitingCustomerQueue.deleteQueue();
            
            
            
        }
    }
    
}


















