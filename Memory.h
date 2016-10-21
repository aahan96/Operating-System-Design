/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Memory.h
 * Author: Aahan
 *
 * Created on September 27, 2016, 12:40 PM
 */
#include <string>
using namespace std;

#ifndef MEMORY_H
#define MEMORY_H

class Memory {              //Class that handles the memory
    
public:
    
    Memory(char* name, int p1[2], int p2[2]);               //Constructor for intiliazing memory
    
    int *arr;
    
    int pip1[2];
    int pip2[2];
    
    int read(int add);                      //Function to read from memory
    
    void write(int add, int data);          //Function to write back to the memory
    
    void close();                           //Function to close the memory
};

#endif /* MEMORY_H */

