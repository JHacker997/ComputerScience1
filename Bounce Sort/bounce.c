//
//  main.c
//
// Team Bagel
// Nafisa Mostofa
// Warren Atchison
// John Hacker
// Bounce Sort



#include "bounce.h"


int main(void) {
    //Declare varaibles
       //int *arr = NULL;
    FILE *inPtr = fopen("bounce.txt", "r");
    
    //Returns the Size of the Array from the File
    int size = retSize(inPtr);
    
    //Builds an Array based on the numbers of the file
    int *arr = buildArr(inPtr, size);
    
    //Close the File
    fclose(inPtr);
    
    //Print array before it is sorted
    printf("Before Sort:\n");
    printArr(arr, size);
 
    clock_t begin = clock(); //starting the clock
    //Loop until array has been sorted
    for (int i = 0; i < size; i += 2)
        //Call bounce function without variable amount of final values
        bounce(arr, size - i);
    //Stop the clock
    clock_t end = clock();
    
    //Print the array after it has been sorted
    printf("\nAfter Sort:\n");
    printArr(arr, size);
    printf("\n\nTIME SPENT: %lf\n\n", (double)(end - begin) / CLOCKS_PER_SEC);
    
    //Free memory allocated to the array
    free(arr);
    
    //Successfully terminate program
    return 0;
}

int retSize(FILE *ifp){
    int size = 0;
    //Check if the file pointer is NULL
    if (ifp == NULL)
        //Terminate program with error code
        return 1;
    
    //Scan the file for the size of the array
    fscanf(ifp, "%d", &size);
    return size;
}

int *buildArr(FILE *ifp, int size){
    
    
    //Allocate memory to the array
   int * arr = malloc(sizeof(int) * size);
    
    //Read in the integers and stores them in the array
    for (int i = 0; i < size; i ++)
        //Reading value of each index of the array from the file
        fscanf(ifp, "%d", &arr[i]);
    return arr;
}



void bounce(int *arr, int size) {
    //Check if the array is size one
    if (size == 1)
        //Exit method without checking values
        return;
    
    //Check if the first value is larger than the last value
    if (arr[0] > arr[size - 1]) {
        //Swap the values in the array
        int temp = arr[0];
        arr[0] = arr[size - 1];
        arr[size - 1] = temp;
    }
    
    //Recursively call function without the first value
    bounce(arr + 1, size - 1);
    
    //Check if the first value is larger than the second to last value
    if (arr[0] > arr[size - 2]) {
        //Swap the values in the array
        int temp = arr[0];
        arr[0] = arr[size - 2];
        arr[size - 2] = temp;
    }
}



//Prints the array
void printArr(int *arr, int size) {
    //Loop for evey index of the array
    for(int i = 0; i < size; i++)
        //Print the value at the current array index
        printf("%d  ", arr[i]);
    
    //Print new lines for spacing convenience
    printf("\n");
}
