#include<stdio.h>
#include<cs50.h>

#define MAX 65536 //define the largest array size allowed based on the paramaters of ./generate

void sort(int values[], int n);


int main(void){
    int haystack[10] = {5, 5, 5, 2, 4, 64, 9, 3, 10, 10};
    
    sort(haystack, 10);
    
    for (int i = 0; i < 10; i++){
        printf("%i\n", haystack[i]);
    }
}

void sort(int values[], int n)
{   
    int count[MAX] = {0}; //inializes all elements in the count array to 0
    int sorted[n]; //makes an array to store all the sorted elements once completed
    int place = 0; //keeps track of how far we are in the sorted array
    
    for (int i = 0; i < n; i++){ //counts how many of each value there are
        count[values[i]] ++;
        printf("counted: %i    count: %i\n", values[i], count[values[i]]);
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