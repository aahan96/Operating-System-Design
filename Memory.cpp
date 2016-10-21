#include "Memory.h"
#include <fstream>
#include <string>
#include <stdlib.h>
#include <iostream>

using namespace std;

Memory::Memory(char* name, int p1[2], int p2[2]) {
    
    this->arr = new int[2000];                  //Initializes the array and pipes
    this->pip1[0] = p1[0];
    this->pip1[1] = p1[1];
    this->pip2[0] = p2[0];
    this->pip2[1] = p2[1];
    int index = 0;
    string line;
    int x;
    ifstream file (name);                   //Opens the file to read from
    
    
    while (file) {                          //Reads from the file and stores in the array
        
        if (file.peek() == '.') {
            file.get();
            file>>x;
            index = x;
        }
        else if(file.peek() >= 48 && file.peek() <= 57) {
            file>>x;
            this->arr[index++] = x;
        }
        
        getline(file, line);
    }
    file.close();                                   //Safely closes the file
    
}

int Memory::read(int add) {
    
    return this->arr[add];
}

void Memory::write(int add, int data) {
    this->arr[add] = data;
}

void Memory::close() {                              //Exits the program
    exit(0);
}
