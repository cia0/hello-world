/**
 * helpers.c
 *
 * Helper functions for Problem Set 3.
 */
 
#include <cs50.h>
#include<math.h>
#include "helpers.h"

#define MAX 65536 //define the largest array size allowed based on the paramaters of generate.c

/**
 * Returns true if value is in array of n values, else false.
 */
bool search(int value, int values[], int n)
{
    if (n < 1){ //returns if the list length is zero
        return false;
    }
    
    int mid = (int)ceil(n/2.0) - 1;
    
    int newValues[mid + 1];//right side list will be longer if even
    //rip dynamicism
    if(value == values[mid]){
        return true;
    }
    
    if(value > values[mid]){ //right half
        
        if(n % 2 == 1){
    
            for (int i = 0; i < mid; i++){
                newValues[i] = values[i + 1 + mid];
            }
        }
        
        else{
            mid += 1; //because right half list will be bigger in this instance
            for (int i = 0; i < mid; i++){
                newValues[i] = values[i + mid];
            }
        }
    }
    
    if(value < values[mid]){ //left half
        for (int i = 0; i < mid; i++){
            newValues[i] = values[i];
        }
        
    }
    
    return search(value, newValues, mid);
    
}

/**
 * Sorts array of n values.
 */
void sort(int values[], int n)
{   
    int count[MAX] = {0}; //inializes all elements in the count array to 0
    int sorted[n]; //makes an array to store all the sorted elements once completed
    int place = 0; //keeps track of how far we are in the sorted array
    
    for (int i = 0; i < n; i++){ //counts how many of each value there are
        count[values[i]] ++;
    }
    
    for (int i = 0; i < MAX; i++){ //goes through the entire list and appends the counted values to the sorted list
        
        if (count[i] > 0){
            for (int j = 0; j < count[i]; j++){
                sorted[place] = i;
                place++;
            }
        }
    }
    
    for (int i = 0; i < n; i++){ // takes the sorted list and transfers it back into haystack
        values[i] = sorted[i];
    }
    
    return;
}
