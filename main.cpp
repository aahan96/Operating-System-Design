

/* 
 * File:   main.cpp
 * Author: Aahan
 *
 * Created on September 26, 2016, 7:34 PM
 */

#include <cstdlib>
#include <iostream>
#include "CPU.h"
#include "Memory.h"
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {                       //Main program starts

    int pip1[2];                                        //Pipes are created
    int pip2[2];
    char* name = argv[1];                               //File Name taken from argument
    int timer = atoi(argv[2]);                          //Time taken from argument
    
   int result = pipe(pip1);                             //Pipes Made
   if (result == -1)
      exit(1);

   result = pipe(pip2);
   if (result == -1)
      exit(1);

   result = fork();                                     //Process forked
   if (result == -1)
      exit(1);

   if (result == 0) {                                  //Child process that handles CPU
       CPU *c = new CPU(pip1, pip2, timer);            //CPU created
       _exit(0);
   }
   
   else {                                           //Parent process that handles Memory
       Memory *m = new Memory(name, pip1, pip2);    //Memory created
       int request;
       int add;
       int data;
       
       
       while(true) {                                        //Keeps on waiting for CPU
           read(pip1[0], &request, sizeof(int));            //Takes appropriate actions for the CPU
           
           if(request == 0 ) {
               read(pip1[0], &add, sizeof(int));
               data = m->read(add);
               
               write(pip2[1], &data, sizeof(int));
           }
           
           else if(request == 1) {
               read(pip1[0], &add, sizeof(int));
               read(pip1[0], &data, sizeof(int));
               m->write(add, data);
           } 
           
           else if(request == 2) {                      //Closes the memory and the program
               m->close();
           }
           
       }
   }
    
    return 0;
}

