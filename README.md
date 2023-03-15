# Microcontrollers Tricks - Creating boolean type in C ANSI
## TIP NUMBER 1 - boolean type to save memory space, processing and make elegant codes

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
   
this code is an example of declaration of variables that contain the states or informations about some sensor, actuator or state. As you can see,the two possibilities for those variables are: 1 or 0, on or off, true or false. But, when we declare a char type for this type of variable, in the true, we are allocating 1 BYTE = 8 bits, to store a information requested for only 1 BIT, or in other words... I´m using a variable able to store 8 real objects to store only one :(
let´s see the memory space of the previous code:

  ```
      char button1 = 0 = 0x00 = 0 0 0 0 0 0 0 0 (binary) 
      char button2 = 1 = 0x01 = 0 0 0 0 0 0 0 1 (binary)
      .
      .
      .
   ```
As you can see, we use exactly 1 BIT, but we allocate 8 bits, so for the example we are allocating 6 variables x 8 bits = 48 bits, but using only 6 bits...
in other words, we are reaching an efficiency of 6/48 = 0,125 = 12,5% in memory management, that is TERRIBLE!

## Pseudo Variables & Bit by Bit Selection

C language is very powerfull. One of the "lost resources" from the language is the hability to select exactly one bit or a group of bits inside one variable of 1 byte or more. The syntax is described bellow:

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
in the truth, those variables are pseudo, because they don´t exist...yet! To allocate memory we use other powerfull resource of the language... STRUCTS & UNIONS!

## Structs and Unions
When we declare a struct we are creating a group of variables that are part of the same type, or in other words, we prepare a specific quantity of memory to be allocated. But, I can use the pseudo variables inside the struct to divide my variables, let´s see:

  ```
  typedef struct
  {
    unsigned varA:1
    unsigned varB:2
    unsigned varC:5
  }pseudoTypes
  ```
pseudoTypes is the name of my new type. As you can see, I created 3 pseudo types that occupies 8 bits (1+2+5) = 1 byte, and it is intentional!

This struct in the true will prepare my system to allocate an memory space of 1 bit, 2 bits or 5 bits, according to my pseudo variable, BUT, I have yet a pseudo variable (or pseudo type). I need to link them to a real type, and I will choose the char type (can be int, float etc... but char is easier for my explanation).

And in C languagem we have another resource that shares allocated memory spaces.... UNIONS! This is the secret! linking the space memory between the pseudo type and a real type, I can allocate real space using the properties of bit acessing. let´s see:

 ```
  typedef union
  {
    char          auxChar;
    pseudoTypes   bitAcess;
  }newType
  ```
  
Let´s understand it!
Unions shares the memory space between their variables. An struct adds the space. So, in the first step I added bits to create the same space as a char type:

```
  typedef struct
  {
    unsigned varA:1
    unsigned varB:2
    unsigned varC:5
  }pseudoTypes
  
  varA + varB + varC = 1 + 2 + 5 = 8 bits = 1 byte
```
but how this type of declaration dont create a variable but prepares the system to stores and select the data, I need a second resource that helps me to allocate the real memory space so I used an UNION. This union is special because WE NEED SELECT AN TYPE THAT HAS THE SAME MEMORY SPACE OF THE PSEUDO TYPES. So, if my pseudo types in the total, results in 8 bits, I need a type that occupies 8 bits, or a CHAR.

Declaring a char type in my union, I define the whole memory space shared between the elements (8 bits). This variable char (charAux) won´t be used more, but now I have a memory link with my next declaration, the type pseudoTypes, that contains the exactly memory space allocated, but distributed as my manner between the bits!
So, I created the variable bitAcess, that is a special type pseudoTypes. Let´s see the draw:

  ```
  typedef union
  {
    char          auxChar   =       _ _ _ _ _   _ _    _              (8 bits)
    pseudoTypes   bitAcess  =       varC     | varB | varA            (5 + 2 + 1 = 8 bits)
  }newType
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
As you can see, we created a new type, with the memory space of a char, but I can acess the first 5 bits, the 2 bits in the middle and the 1 last bit. Now I have total controll of my variable O.o

## Boolean types in C (fake news)
As seen before, in the truth I need to allocate at least 1 byte of memory, but now I´m able to manage bit by bit. By this way, I can create a new type to acess bit by bit, emulating a boolean type:

```
  typedef struct
  {
    unsigned bit0:1
    unsigned bit1:1
    unsigned bit2:1
    unsigned bit3:1
    unsigned bit4:1
    unsigned bit5:1
    unsigned bit6:1
    unsigned bit7:1
  } bitAcess
  
  typedef union
  {
    char auxChar;
    bitAcess bitPosition;
  } fakeBoolean
  
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

Using defines in my code, I can turn it more elegant, but I need to separate my code in a header file and in a C file. The header file will contain the struct, union and define declarations, and in my C code I will declare the variables in the new type, but I need to be wise and coordinate the declarations:

```
//header file
#ifndef _MAIN_H
        #define _MAIN_H
        
  typedef struct
  {
    unsigned bit0:1
    unsigned bit1:1
    unsigned bit2:1
    unsigned bit3:1
    unsigned bit4:1
    unsigned bit5:1
    unsigned bit6:1
    unsigned bit7:1
  } bitAcess
  
  typedef union
  {
    char auxChar;
    bitAcess Boolean;
  } fakeBoolean
 
 //object is the name of the variable declared in the main.C
  #define button1_state    object.Boolean.bit0
  #define button2_state    object.Boolean.bit1
  #define LED1_state       object.Boolean.bit2
  #define LED1_state       object.Boolean.bit3
  #define system1_state    object.Boolean.bit4
  #define system2_state    object.Boolean.bit5
 
 #endif
```
```
//C file
 #include main.h
 
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
 }
```
As you can see, now, I have allocated 1 byte in my memory (8 bits) but I can controll individually each bit, so, using the first real example, now I have 6 objects using 1 bit each one, in a total o 8 bits allocated, so I have an efficiency of 6/8 = 75% of memory allocation !

## The End




