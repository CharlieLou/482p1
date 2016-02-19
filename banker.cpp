#include<iostream>


bool issafe(State& state, String customer, unsigned int value);
void makeLoan(State& state, String customer, unsigned int value);
void acceptRepayment(State& state, String customer, unsigned int value);

mutex lock;
//cv NoRequest;
queue<cv*> cv_queue;
cv bank;
unsigned int NUM = 0;
//unsigned int NUM;

void RequestLoan(State& state, String customer, unsigned int value){
	lock.lock();
	cv cv1;		
	NUM++;
	while(!issafe(state,customer,value)){

		customer_waiting.push(&cv1);
		cv1.wait(lock);

	}



	makeLoan(...);
	NUM--;
	bank.signal();
	
	lock.unlock();

}


void RepayBank( State& state, String customer, unsigned int value){
	lock.lock();

	while(NUM == 0){
		bank.wait(lock);
	}
	acceptRepayment(...);
	for(int i = 0; i < cv_queue.size(); i++){
		cv* cv1 = cv_queue.front();
		cv_queue.pop();
		cv1->signal();

		thread_yield();
	}

	lock.unlock();

}



////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////
semaphore lock(1);
semaphore ban
queue<semaphore*> waiting_queue;
unsigned int NUM = 0;
void RequestLoan(State& state, String customer, unsigned int value){
	lock.down();
	NUM++;
	semaphore customer_loan(0);
	while(!issafe(state,customer,value)){
		waiting_queue.push(&customer_loan);
		customer_loan.down();
	}

	makeLoan(...);
	NUM--;	
		

	lock.up();

}
