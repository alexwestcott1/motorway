/* 
* Program to simulate a motorway
* Written by Alex Westcott for an assignment at the University of Liverpool in 2018
*/

#include <stdio.h>
#include <stdlib.h>

/*Defining a struct for a 'vehicle' type which will hold the row and arrival time of the vehicle*/
typedef struct{
	int arrivalTime;
	int rowIndex;
} vehicle;

/*Global variables to be used in the program that can be altered by multiple functions*/

/*Array of char type that will contain information about the state of the motorway*/
char* motorway;

/*Array of previously defined type 'vehicle' which will contain information about all the vehicles*/
vehicle* vehicleData;

/*Integers to count the number of vehicles that have entered the motorway, the number of rows/columns, and the number of steps to simulate*/
int count = 0;
int rowNo = 0, colNo = 0, stepNo = 0;

/*Method used to check if any new vehicles are arriving at the current time
Takes the current number of cars checked and the current time of the simulation as arguments*/
void checkArrival(int pos, int currentTime){
	
	/*If the next vehicle in the list is due to arrive, put the vehicle in the row specified in the array vehicleData*/
	if(vehicleData[pos].arrivalTime == currentTime){
		motorway[vehicleData[pos].rowIndex*colNo] = '1';
		/*Increment the vehicle count, and then recursively check if there are any more vehicles due to arrive
		Recursively checking for vehicles mean more than one vehicle can arrive at the same time*/
		count++;
		checkArrival(count, currentTime);
	}
	
}

int main(void){
	
	/*Variables to be used by the main method*/
	int input1, input2;
	int vehicleNo = 0;
	
	/*32 is an arbitrary limit for the number of vehicles that can be entered, but will be increased if the number of vehicles is larger than 32*/
	int inputNo = 32;
	
	/*Allocate memory for the vehicle data used
	This is equal to the input number (currently 32) multiplied by the amount of memory required for one instance of the vehicle struct*/
	vehicleData = (vehicle*)malloc(inputNo * sizeof(vehicle));
	
	/*If, for whatever reason, there is no memory available, exit the program with an error printed to the user*/
	if(vehicleData == NULL){
		fprintf(stderr, "Out of memory\n");
		exit(1);
	}
	
	/*Taking user input for the number of rows/columns, and the number of steps to simulate*/
	scanf("%i%i%i", &rowNo, &colNo, &stepNo);
	
	/*Allocate the amount of memory required for the motorway*/
	motorway = (char*)calloc((rowNo * colNo), sizeof(char));
	
	/*While loop which runs until there are no more inputs (i.e. End of File)*/
	/*Note that 'input1' is the arrival time of a vehicle on the motorway and that 'input2' is the index of the row the vehicle is on*/
	
	while(scanf("%i%i", &input1, &input2) != EOF){
		
		/*If the number of vehicles is above 32, reallocate memory to the vehicleData array using the realloc() method*/
		if(vehicleNo == inputNo){
			inputNo = inputNo * 2;
			vehicleData = realloc(vehicleData, inputNo * sizeof(vehicle));
			
			/*Like earlier, if, for whatever reason, there is no memory available, exit the program with an error printed to the user*/
			if(vehicleData == NULL){
				fprintf(stderr, "Out of memory\n");
				exit(1);
			}
		}
		
		/*Assign the next two numbers entered by the user as the arrival time and row index of the vehicles in the vehicleData array*/
		vehicleData[vehicleNo].arrivalTime = input1;
		vehicleData[vehicleNo].rowIndex = input2;
		
		/*Increment the number of vehicles by 1*/
		vehicleNo++;
	}
	
	/*For loop which fills out the motorway array with '.', indicating an 'empty' motorway with no vehicles (default state)*/
	for(int i=0;i<rowNo;i++){
		for(int j=0;j<colNo;j++){
			motorway[(i*colNo) + j] = '.';
		}
	}
	
	/*Run through the simulation the number of steps the user requested (stepNo)*/
	for(int k=0;k<stepNo;k++){
		
		/*At every step, check every element of the motorway array*/
		for(int i=0;i<rowNo;i++){
			for(int j=colNo-1;j>=0;j--){
				
				/*If the element contains a '1' (i.e. a vehicle is in this spot), check to make sure the vehicle isn't at the end of a row
				If the vehicle isn't in the last column, make the next element in the array a '1', indicating the vehicle has moved forward one space
				Also make sure the current element in the array becomes a '.', regardless of the position of the element, as the vehicle has left*/
				if(motorway[(i*colNo) + j] == '1'){
					if(j != (colNo - 1)){
						motorway[(i*colNo) + j + 1] = '1';
					}
					motorway[(i*colNo) + j] = '.';
				}
			}
		}
		
		/*For each step of the simulation, call the checkArrival() method to see if any new vehicles have arrived*/
		checkArrival(count, k);

	}

	/*After all steps have been simulated, print out the final state of the motorway to the user*/
	for(int i=0;i<rowNo;i++){
		for(int j=0;j<colNo;j++){
			printf("%c", motorway[(i*colNo) + j]);
		}
		printf("\n");
	}
	
	/*Free the memory that was allocated to both arrays*/
	free(vehicleData);
	free(motorway);
	
}