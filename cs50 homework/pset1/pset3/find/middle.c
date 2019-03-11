#include<stdio.h>
#include<cs50.h>
#include<math.h>

bool search(int value, int values[], int n);

int main(void){
    int values[20];
    for (int i = 0; i < 20; i++){
        values[i] = i;
        //printf("%i\n", values[i]);
    }
    for (int i = 0; i < 20; i++){
        search(i, values, 20);
    }
    search(23, values, 20);
}

bool search(int value, int values[], int n)
{
    if (n < 1){ //returns if the list length is zero
        printf("no\n");
        return false;
    }
    
    int mid = (int)ceil(n/2.0) - 1;
    
    int newValues[mid + 1];//right side list will be longer if even
    //rip dynamicism
    if(value == values[mid]){
        printf("yes\n");
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
