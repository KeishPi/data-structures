/*************************************************************************
 ** Program Filename: a0part2.c
 ** Author: Keisha Arnold
 ** Date: September 29, 2016
 ** Description: A simple C program that converts inches to cm and
 ** cm to inches.
 ** Input: double 
 ** Output: double
**************************************************************************/
#include <stdio.h>

int main() {

   double inch, cm, cmToInch, inchToCm;
   int choice;

   // Prompt user with a menu
   printf("Choose an option from the menu:\n");
   printf("1) Convert inches to cm:\n");
   printf("2) Convert cm to inches:\n");
   scanf("%d", &choice);
 
   switch (choice) {
   // Prompt user to enter value in inches, convert to cm, and print result
   case 1: 
      printf("Input your value in inches:\n");
      scanf("%lf", &inch);

      inchToCm = inch * 2.54;

      printf("%f inches equals %f cm\n", inch, inchToCm);
      break;

   // Prompt user to enter value in cm, convert to inches and print result
   case 2: 
      printf("Input your value in cm:\n");
      scanf("%lf", &cm);
      
      cmToInch = cm * 0.39370;
     
      printf("%f cm equals %f inches\n", cm, cmToInch);
      break;
  
   // User did not enter a valid menu choice
   default: 
      printf("Not a valid choice\n");
      break;
   }

   return 0;
}
