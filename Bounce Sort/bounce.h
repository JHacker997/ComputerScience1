//
//  Header.h
//  Bounce Header
// Nafisa Mostofa
// Warren Atchison
// John Hacker

#ifndef Header_h
#define Header_h

// TEAM BAGEL: Warren Atchison, Nafisa Mostofa, John Hacker
// COP 3502H, Section 0201

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int retSize(FILE *ifp);
int *buildArr(FILE *ifp, int size);
void bounce(int *arr, int size);
void printArr(int *arr, int size);
#endif /* Header_h */
