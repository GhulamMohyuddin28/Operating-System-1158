//Write a C program that simulates a bank account with multiple transactions:
//1. Create a shared global variable
//2. Create 4 threads:
//  Thread 1: Deposits 1000 (repeat 5 times)
//  Thread 2: Withdraws 500 (repeat 5 times)
//  Thread 3: Deposits 800 (repeat 5 times)
//  Thread 4: Withdraws 300 (repeat 5 times)
//3.  Use mutex to protect balance updates
//4.  Each thread should print after each transaction:   Thread ID
//  Operation (Deposit/Withdraw)   Amount
// initialized to 5000
//  New balance
// 5.  Main thread prints final balance

#include<stdio.h>
#include<pthread.h>
int g_balance=5000;
pthread_mutex_t lock;
void* Withdraw(void* arg)
{
    printf("Thread ID=%lu .. Start \n",pthread_self()); // pthread self return the current thread ID
    int num=*(int*)arg;  // Derefrencing the variable to pass it in integer.
    pthread_mutex_lock(&lock);  // Executing to critical section
    for(int i =1;i<=5;i++)
    {
        printf("Repition: %d This amount: %d Withdraw\n",i,num); // Each iteration minus the amount from total balance
        g_balance=g_balance-num;
    }
    
    pthread_mutex_unlock(&lock); // Finish execution of critical section
    printf("Thread ID=%lu .. Ending \n",pthread_self());
}

void* Deposit(void* arg)
{
    printf("Thread ID=%lu .. Start \n",pthread_self());
    int num=*(int*)arg;
    pthread_mutex_lock(&lock);
    for(int i =1;i<=5;i++)
    {
        printf("Repition: %d This amount: %d is Deposit\n",i, num);
        g_balance=g_balance+num;  // Each iteration add the amount into total balance
    }
    pthread_mutex_unlock(&lock);
    printf("Thread ID=%lu .. Ending \n",pthread_self());

}

int main()
{
    pthread_t T1,T2,T3,T4;
    pthread_mutex_init(&lock,NULL);
    printf("Balance =%d\n",g_balance);
    int n1=1000;
    pthread_create(&T1,NULL,Deposit,&n1);
    int n2=500;
    pthread_create(&T2,NULL,Withdraw,&n2);
    int n3=800;
    pthread_create(&T3,NULL,Deposit,&n3);
    int n4=300;
    pthread_create(&T4,NULL,Withdraw,&n4);
    pthread_join(T1,NULL);
    pthread_join(T2,NULL);
    pthread_join(T3,NULL);
    pthread_join(T4,NULL); 

    pthread_mutex_destroy(&lock);
    printf("\nBalance=%d",g_balance);
}