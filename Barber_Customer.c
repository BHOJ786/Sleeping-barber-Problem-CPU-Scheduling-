#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "sem.h"
Semaphore cst; // for customer
Semaphore bbr; // for barber	
Semaphore acc_seats; // Access Seats
int seats_free = 25;
int t_cst = 5; // Total customers	
void bbr_pro(); // Barber process
void cst_pro(); // Customer process
	

int main()
{
	  sem_init(&cst, 0);
	  sem_init(&bbr, 0);
	  sem_init(&acc_seats, 1);
	

	  // Create the cst
	  int i;
	  for (i = 0; i < t_cst; i++) {
	    if(fork() == 0) {
	      printf("Fork!\n");
	      cst_pro(i);
	      exit(0);
	    }
	  }
	  bbr_pro();
	  return 0;
	}
	

	void bbr_pro()
	{
	  // runs in an infinite loop
	  for (;;) {
	    // tries to acquire a customer
	    printf("Barber is ready for customer.\n");
	    sem_wait(&cst);
	    // modify the number of available seats
	    printf("Barber is trying to access seats\n");
	    sem_wait(&acc_seats);
	    
	    seats_free++;
	   
	    printf("Barber is ready to cut.\n");
	    sem_signal(&bbr);
	    
	    sem_signal(&acc_seats);
	    
	    printf("Barber is cutting hair");
	  }
	}
	

	void cst_pro(int number)
	{
	  
	  for (;;) {
	    
	    printf("[PID %d] Customer %d: Trying to access seat.\n",
		   getpid(), number);
	    sem_wait(&acc_seats);
	    printf("[PID %d] Customer %d: Checking if any free seats.\n",
		   getpid(), number);
	    
	    if (seats_free > 0) {
	      
	      printf("Customer %d sat down in waiting room. [PID: %d]\n",
		     number, getpid());
	      seats_free--;
	      
	      sem_signal(&cst);
	      
	      sem_signal(&acc_seats);
	      
	      sem_wait(&bbr);
	    }
	    
	    else {
	      
	      sem_signal(&acc_seats);
	      
	      printf("Customer %d left (no free seats).\n", number);
	    }
	  }
}
