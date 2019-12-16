#include "queue.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define AVG_SERVICE 2.0
#define WORK_DAY_MIN 480.0
//Global variable for .dat data
int nums[5];

/* Function responcible for loading a given .dat file for the event driven simulation */
void readDat(int numList[], FILE *datFile) {
	int numIndex;
	int numData;
	while(fscanf(datFile, "%d %d\n", &numIndex, &numData) != EOF) {
		numList[numIndex] = numData;
	}
}
/* Function responcible for creating a random number to determine how many customers arrive*/
int customerGeneration() {
	int rng = rand() % 100 + 1;
		
	//If branch responcible for determining amount of customers arriving
	if(rng > 0 && rng <= nums[0]) {
		return 0;
	}else if(rng > nums[0] && rng <= (nums[0] + nums[1])) {
		return 1;
	}else if(rng > (nums[0] + nums[1]) && rng <= (nums[0]+nums[1]+nums[2])) {
		return 2;
	}else if(rng > (nums[0]+nums[1]+nums[2]) && rng <= (nums[0]+nums[1]+nums[2]+nums[3])) {
		return 3;
	}else if(rng > (nums[0]+nums[1]+nums[2]+nums[3]) && rng <= 100){
		return 4;
	} else {
		printf("ERROR: rng has surpassed the percentile range\n");
	}
	return -1;
	
}
/* Function responcible for using the rand() number and generating a time for how long 
 * service will take in the business */
double expdist(double mean) {
	double r = rand();
	r /= RAND_MAX;
	return -mean *  log(r);
}
/* Function responcible for starting a simulation of a given business */
void simulation(int numTellers) {
	//Setting up queue and variables
	double curr_time = 0.0;
	int served_customers = 0;
	
	double total_wait = 0.0;
	double avg_wait = 0.0;
	
	double avg_q_wait = 0.0;
	
	double max_wait = 0.0;
	double temp_wait = 0.0;
	
	int en_q_count = 0;
	int tot_q_count = 0;

	int avg_q_count = 0;
	int max_line_num = 0;
	//Creating queue object	
	queue line;
	init(&line);
	//Loop used to simulate a day of business
	while(curr_time <= WORK_DAY_MIN) {
		
		int customers = customerGeneration();
		//Each min customers are added
		curr_time += 1.0;
	
		//Loop that enqueues customers
		if(customers > 0) {
			for(int i = 0; i < customers; i++) {
				if(!full(&line)) {
					enqueue(curr_time, &line);
				}
					
			}
			en_q_count++;
			tot_q_count += customers;


		}
		//Check the queue count after every time customers are enequeued: max_line_num
		if(line.count > max_line_num) {
			max_line_num = line.count;

		}
		//Once customers are enqueued the tellers go to work
		for(int i = 0; i < numTellers; i++) {
			
			if(!empty(&line)) {
				double service_time = expdist(AVG_SERVICE);
				total_wait += service_time;
				served_customers++;
				dequeue(&line);
				curr_time += service_time;
			
				temp_wait = curr_time-(rear(&line));
				
			}
			//If branches used for max_wait
			if(empty(&line)) {
				temp_wait = 0.0;
			}	
			if(temp_wait > max_wait) {				
				max_wait = temp_wait;
			}
			
		}
	}
	//File output for easy viewing
	FILE *fout;
	fout = fopen("proj2_out.txt", "a");
	//Calc and display stats
	avg_wait = total_wait / (double)served_customers;
	avg_q_count = tot_q_count / en_q_count;
	fprintf(fout, "SIMULATING WITH %d TELLERS:\n",numTellers);
	fprintf(fout, "\tCUSTOMERS SERVED: %d\n", served_customers);
	fprintf(fout, "\tAVERAGE WAIT TIME: %f mins\n", avg_wait);
	fprintf(fout, "\tMAX QUEUE NUMBER: %d\n", max_line_num);
	fprintf(fout, "\tAVG LENGTH OF QUEUE: %d\n", avg_q_count);
	fprintf(fout, "\tMAX WAIT TIME: %f\n\n", max_wait);
	fclose(fout);

	



}


int main(int argc, char* argv[]) {
	//Load business file for simulation	
	FILE *dat;
	dat = fopen("proj2.dat", "r");
	readDat(nums, dat);
	
	//Run simulations
	simulation(7);
	
	simulation(6);
	simulation(5);
	simulation(4);
	simulation(3);

	
	fclose(dat);
	return 0;	
}
