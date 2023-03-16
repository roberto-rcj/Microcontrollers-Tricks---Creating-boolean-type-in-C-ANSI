#include<stdio.h>
 #include<stdlib.h>
 #include "main.h"
 
 int main(void)
 {
  //declaring the new type with 8 bits, but now I can acess bit by bit
  fakeBoolean object; //object is the name of the variable
                      //now I can use the definition in my header file to sincronize boolean sensors, actuators and states
                      //to the bits of my new variable, let�s take a look
 
 //If I want to store the LED1state, I can use:
 object.Boolean.bit2 = 1;
 
 //or I can use this elegant writting:
 LED1_state = 1;
 
 //both writes are the same!

 //declaring more variables
 system1_state = 0;
 button1_state = 1;

 //printing the values on the prompt
 printf("the value of LED1 is %d \n", LED1_state);
 printf("the value of button1 is %d \n", button1_state);
 printf("the value of system1 is %d \n", system1_state);
 printf("\n");
 
 //cheking the size
 printf("the size of the object type is %d",sizeof(object));
 }

