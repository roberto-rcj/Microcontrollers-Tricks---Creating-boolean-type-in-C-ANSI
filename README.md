# Microcontrollers Tricks - Creating boolean type in C ANSI
## TIP NUMBER 1 - boolean type to save memory space, processing and making elegant codes

### Created by: Roberto Campos dos Reis Junior
### Date: 14/03/2023
### License and Rights: Free for use



## Introduction

When we use microcontrollers or embedded systems, CLPs, FPGA, Arduino etc... using few memory or processing power, normally we face the memory and processing management problem. Many applications request reading and writting of boolean sensors and actuators, ex: LEDs, buttons, cilinders, lamps, valves or even the system state monitorization using flags, that are basically bits: on, off, up, down...

But this type of system, normally operates with C ANSI language, PIC microcontrollers for example. And the basic type in the language is the CHAR TYPE. The char type contais 1 byte = 8 bits. I can use 1 char to each variable of controll in my program, but let´s see the example:

  ```
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
   ```
   
this code is an example of declaration of variables that contain the states or informations about some sensor, actuator or state. As you can see,there are two possibilities for those variables: 1 or 0, on or off, true or false. But, when we declare a char type for this type of variable, actually, we are allocating 1 BYTE = 8 bits, to store an information requested for only 1 BIT, or in other words... I´m using a variable able to store 8 real objects to store only one :(
let´s see the memory space of the previous code:

  ```
      char button1 = 0 = 0x00 = 0 0 0 0 0 0 0 0 (binary) 
      char button2 = 1 = 0x01 = 0 0 0 0 0 0 0 1 (binary)
      .
      .
      .
   ```
As you can see, we use exactly 1 BIT, but we allocate 8 bits, so for this example we are allocating 6 variables x 8 bits = 48 bits, but using only 6 bits...
in other words, we are reaching an efficiency of 6/48 = 0,125 = 12,5% in memory management, that is TERRIBLE!

## Pseudo Variables & Bit by Bit Selection

C language is very powerful. One of the "lost resources" from the language is the ability to select exactly one bit or a group of bits inside one variable of 1 byte or more. The syntax is described bellow:

  ```
  unsigned varA:1
  unsigned varB:3
  unsigned varC:8
  .
  .
  .
  ```
  
  in this syntax, the undefined type UNSIGNED is used as a standard declaration. After, we describe the name of the variable (varA, varB, varC....) and with the syntax of ':' indicates that we will select some bits, and this number is described after the ':'.
  
  ```
  unsigned varA:1 -> varA is a pseudo variable, that will refer to 1 bit
  unsigned varB:3 -> varA is a pseudo variable, that will refer to 3 bits
  unsigned varC:8 -> varA is a pseudo variable, that will refer to 8 bits
  ```
in the truth, those variables are pseudo, because they don´t exist...yet! To allocate memory we use another powerful resources of the language... STRUCTS and UNIONS!

## Structs and Unions
When we declare a struct we are creating a group of variables that are part of the same type, or in other words, we prepare a specific quantity of memory to be allocated. But, I can use the pseudo variables inside the struct to divide my variables, let´s see:

  ```
  typedef struct
  {
    unsigned varA:1;
    unsigned varB:2;
    unsigned varC:5;
  }pseudoTypes;
  ```
pseudoTypes is the name of my new type. As you can see, I created 3 pseudo types that occupies 8 bits (1+2+5) = 1 byte, and this is intentional!

This struct, actually, will prepare my system to allocate a memory space of 1 bit, 2 bits or 5 bits, according to my pseudo variable, BUT, I have yet a pseudo variable (or pseudo type). I need to link them to a real type, and I will choose the char type (can be int, float etc... but char is easier for my explanation).

And in C languagem we have another resource that shares allocated memory spaces.... UNIONS! This is the secret! linking the space memory between the pseudo type and a real type, I can allocate real space using the properties of bit acessing. let´s see:

 ```
  typedef union
  {
    char          auxChar;
    pseudoTypes   bitAcess;
  }newType;
  ```
  
Let´s understand it!
Unions shares the memory space between their variables. An struct adds the space. So, in the first step I added bits to create the same space as a char type:

```
  typedef struct
  {
    unsigned varA:1;
    unsigned varB:2;
    unsigned varC:5;
  }pseudoTypes;
  
  varA + varB + varC = 1 + 2 + 5 = 8 bits = 1 byte
```
but how this type of declaration doesn´t create a variable but prepares the system to stores and selects the data, I need a second resource that helps me to allocate the real memory space so I used an UNION. This union is special because WE NEED TO SELECT A TYPE THAT HAS THE SAME MEMORY SPACE OF THE PSEUDO TYPES. So, if my pseudo types in the total, results in 8 bits, I need a type that occupies 8 bits, or a CHAR.

Declaring a char type in my union, I define the whole memory space shared between the elements (8 bits). This variable char (charAux) won´t be used more, but now I have a memory link with my next declaration, the type pseudoTypes, that contains the exactly memory space allocated, but distributed as my manner between the bits!
So, I´ve created the variable bitAcess, that is a special type pseudoTypes. Let´s see the draw:

  ```
  typedef union
  {
    char          auxChar   =       _ _ _ _ _   _ _    _              (8 bits)
    pseudoTypes   bitAcess  =       varC     | varB | varA            (5 + 2 + 1 = 8 bits)
  }newType;
  ```

## Acessing the Bits
After this process, I call my specific bit numbers using the C natural sintax for structs, calling the types:

```
//declare a new char variable using the new type
newType testChar = 0;

//call the specific bits from the variable
newType.bitAcess.varA = 1;  //1 = 0x01 = 1b
newtype.bitAcess.varB = 2;  //2 = 0x02 = 10b
newtype.bitAcess.varC = 7;  //7 = 0x07 = 111b
```
after this, if you print the binary state, you will see:

```
testChar = 00111101 = 00111  10   1
//                    varC  varB varA
//or 00111101 = 61;
```
As you can see, we´ve created a new type, with the memory space of a char, but I can acess the first 5 bits, the 2 bits in the middle and the 1 last bit. Now I have total controll of my variable!

## Boolean types in C (fake news)
As seen before, actually, I need to allocate at least 1 byte of memory, but now I´m able to manage bit by bit. By this way, I can create a new type to acess bit by bit, emulating a boolean type:

```
  typedef struct
  {
    unsigned bit0:1;
    unsigned bit1:1;
    unsigned bit2:1;
    unsigned bit3:1;
    unsigned bit4:1;
    unsigned bit5:1;
    unsigned bit6:1;
    unsigned bit7:1;
  } bitAcess;
  
  typedef union
  {
    char auxChar;
    bitAcess bitPosition;
  } fakeBoolean;
  
  int main(void)
  {
    fakeBoolean testVar;
    testVar.bitPosition.bit0 = 0;
    testVar.bitPosition.bit1 = 1;
    .
    .
    .
  }
```

Using defines in my code, I can make it more elegant, but I need to separate my code in a header file and in a C file. The header file will contain the struct, union and define declarations, and in my C code I will declare the variables in the new type, but I need to be wise and coordinate the declarations:

```
//header file
#ifndef _MAIN_H
        #define _MAIN_H
        
  typedef struct
  {
    unsigned bit0:1;
    unsigned bit1:1;
    unsigned bit2:1;
    unsigned bit3:1;
    unsigned bit4:1;
    unsigned bit5:1;
    unsigned bit6:1;
    unsigned bit7:1;
  } bitAcess;
  
  typedef union
  {
    char auxChar;
    bitAcess Boolean;
  } fakeBoolean;
 
 //object is the name of the variable declared in the main.C
  #define button1_state    object.Boolean.bit0
  #define button2_state    object.Boolean.bit1
  #define LED1_state       object.Boolean.bit2
  #define LED2_state       object.Boolean.bit3
  #define system1_state    object.Boolean.bit4
  #define system2_state    object.Boolean.bit5
 
 #endif
```
```
//C file
 #include<stdio.h>
 #include<stdlib.h>
 #include "main.h"
 
 int main(void)
 {
  //declaring the new type with 8 bits, but now I can acess bit by bit
  fakeBoolean object; //object is the name of the variable
                      //now I can use the definition in my header file to sincronize boolean sensors, actuators and states
                      //to the bits of my new variable, let´s take a look
 
 //If I want to store the LED1state, I can use:
 object.Boolean.bit2 = 1;
 
 //or I can use this elegant writting:
 LED1_state = 1;
 
 //both writes are the same!
 //printing the values on the prompt
 printf("the value of LED1 is %d", LED1_state);
 
 }
```
As you can see, now, I have allocated 1 byte in my memory (8 bits) but I can controll individually each bit, so, using the first real example, now I have 6 objects using 1 bit each one, in a total o 8 bits allocated, so I have an efficiency of 6/8 = 75% of memory allocation !

## The End... or not

In a first look, the program really appears correct, and it is, but we have a little trouble. Structs in C need a space in the memory, so if you print the size of the object variable, you will see:

```
.
.
.
printf("%d", sizeof(object));

>> 4
```
the prompt will return 4 bytes, not only 1 as expected :(

but if life gives you lemons, take them and make a juice :)
if I have 4 bytes reserved, so I can use these whole 32 bits one by one. To make the programming correct, you can turn your auxChar into a vector of 4 bytes, but is not necessary. In the example code, you will see a declaration going from bit0 to bit31 (32 bits). You will be able to declare variables from "object.Boolean.bit0" to "object.Boolean.bit31", so unfortunatelly we need allocate more memory but happily we can use all those bits one by one.

## Pay atention
if you change the auxiliar char vector "auxChar[4]" to "auxChar[5]", the union will request more space enough to the whole process, so in the truth you will allocate 8 bytes, so the correct and elegant way is change the variable to "auxChar[8]". As I said, "auxChar[5]" is not a problem, because the compilers corrects it, allocating more memory to the structure, but is important make it clear and let evident the number of real bytes allocated by the program!

if you print the size of "object", with auxChar[5], auxChar[6], auxChar[7], or auxChar[8], the prompt will show 8, as the same logic applied to  auxChar[1], auxChar[2], auxChar[3], or auxChar[4], that had shown 1 byte.

## Finishing

You can use and create new tipes, but keep in mind the space allocated to otimize your program and memory allocation. Good luck!


