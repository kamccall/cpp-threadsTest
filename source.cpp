/**
 * kmccall 4/8/18
 */

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

using namespace std;

int sum = 0;  // can i show effect of race conditions from multiple threads?

void* adder(void* param)
{
   int number = atoi((char*)param);
   // sum = number * 2;
   sum+= number;   
   pthread_exit(0);
}

int main(int argc, char *argv[])
{
   pthread_t       tid1, tid2, tid3;
   pthread_attr_t  attr1, attr2, attr3;

   pthread_attr_init(&attr1);
   // pthread_create(&tid1, &attr1, doubler, (void *) argv[1]);
   pthread_create(&tid1, &attr1, adder, (void *)argv[1]);
 
   pthread_attr_init(&attr2);
   pthread_create(&tid2, &attr2, adder, (void *)argv[1]);
    
   pthread_attr_init(&attr3);
   pthread_create(&tid3, &attr3, adder, (void *)argv[1]);

   pthread_join(tid1, NULL);
   pthread_join(tid2, NULL);
   pthread_join(tid3, NULL);

   cout << "total is: " << sum << endl;
}
