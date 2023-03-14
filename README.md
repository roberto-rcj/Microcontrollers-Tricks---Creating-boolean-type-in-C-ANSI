# Microcontrollers Tricks - Creating boolean type in C ANSI
## TIP NUMBER 1 - boolean type to save memory space, processing and make elegant codes

### Created by: Roberto Campos dos Reis Junior
### Date: 14/03/1998
### License and Rights: Free for use



## Introduction

    When we use microcontrollers or embedded systems, CLPs, FPGA, Arduino etc.... using few memory or processing power, normally 
    we face the memory and processing management problem. Many applications request reading and writting of boolean sensors and 
    actuators, ex: LEDs, buttons, cilinders, lamps, valves or even the system state monitorization using flags, that are basically 
    bits: on, off, up, down....
  
    But this type of system, normally operates with C ANSI language, PIC microcontrollers for example. And the basic type in the language is the 
  CHAR TYPE. The char type contais 1 byte = 8 bits. I can use 1 char to each variable of controll in my program, but let´s see the example:
  
   int main(void)
    {
      char button1 = 0;
      char button2 = 1;
      char lamp1 = 0;
      char lamp2 = 1;
      char state1 = 0;
      char state2 = 1;
      .
      .
      .
    }
    this code is an example of declaration of variables that contain the states or informations about some sensor, actuator or state. As you can see,
  the two possibilities for those variables are: 1 or 0, on or off, true or false.
    But, when we declare a char type for this type of variable, in the true, we are allocating 1 BYTE = 8 bits, to store a information requested 
    for only 1 BIT, or in other words... I´m using a variable able to store 8 real objects to store only one :(
    let´s see the memory space of the previous code:

    


