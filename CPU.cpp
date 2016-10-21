#include "CPU.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

using namespace std;

    CPU::CPU(int p1[2], int p2[2], int timer) {             //CPU Constructor
        this->kernel = false;                               //Keeps a track of the mode
        this->btimer = false;                               //Keeps a track of the type of interupt
        this->ac = this->x = this->y = this->ir = 0;            //Values being intialized
        this->sp = 999;
        this->pc = 0;
        this->pip1[0] = p1[0];
        this->pip1[1] = p1[1];
        this->pip2[0] = p2[0];
        this->pip2[1] = p2[1];
        time_counter = 1;
        while(true) {                                                  // Keeps on looping until exit condition
            if(time_counter%timer == 0) {                               //Checks for timed interupts
                this->start_timer();
            }   
            this->ir = this->c_read();                                  //Reads instruction
            
            this->load_ir();                                            //Loads instruction
            
            time_counter++;
        }
    }
    
    void CPU::start_timer() {                           //Starts the timed interupt by setting up the values
        if(this->kernel == true) {
            return;
        }
        this->btimer = true;
        this->kernel = true;
        this->c_write(1999, pc);
        this->c_write(1998, sp);
        this->sp = 1997;
        
        pc = 1000;
    }
    
    int CPU::c_read(int a) {                                //Reads from the memory through pipes
        int prompt = 0;
        int prompt_exit = 2;
        int data;
        
        if(!kernel && (a>=1000)) {                          //Terminates program if memory violation
            cout<<endl<<"Memory violation: accessing system address 1000 in user mode "<<endl;
            write(pip1[1], &prompt_exit, sizeof(int));            
        }
        
        write(pip1[1], &prompt, sizeof(int));
        if(a == -67) {
            write(pip1[1], &(pc), sizeof(int));
            pc++;
        }
        else
            write(pip1[1], &a, sizeof(int));
        read(pip2[0], &data, sizeof(int));
        return data;
    }
    
    void CPU::c_write(int add, int x) {                 //Writes back to the memory through pipes
        int prompt = 1;
        write(pip1[1], &prompt, sizeof(int));
        write(pip1[1], &add, sizeof(int));
        write(pip1[1], &x, sizeof(int));
    }
    
    void CPU::load_ir() {                       //Calls the appropriate commands and functions for the instructions

        if(this->ir == 1)
            this->load_value();
        else if (this->ir == 2)
            this->load_addr();
        else if (this->ir == 3)
            this->loadInd_addr();
        else if (this->ir == 4)
            this->loadIdxX_addr();
        else if (this->ir == 5)
            this->loadIdxY_addr();
        else if (this->ir == 6)
            this->LoadSpX();
        else if (this->ir == 7)
            this->store_addr();
        else if (this->ir == 8)
            this->get_random();
        else if (this->ir == 9)
            this->put_port();
        else if (this->ir == 10)
            this->addX();
        else if (this->ir == 11)
            this->addY();
        else if (this->ir == 12)
            this->subX();
        else if (this->ir == 13)
            this->subY();
        else if (this->ir == 14)
            this->copyTo_X();
        else if (this->ir == 15)
            this->copyFrom_X();
        else if (this->ir == 16)
            this->copyTo_Y();
        else if (this->ir == 17)
            this->copyFrom_Y();
        else if (this->ir == 18)
            this->copyTo_Sp();
        else if (this->ir == 19)
            this->copyFrom_Sp();
        else if (this->ir == 20)
            this->jump_addr();
        else if (this->ir == 21)
            this->jumpIfEqual_addr();
        else if (this->ir == 22)
            this->jumpIfNotEqual_addr();
        else if (this->ir == 23)
            this->call_addr();
        else if (this->ir == 24)
            this->ret();
        else if (this->ir == 25)
            this->inc_X();
        else if (this->ir == 26)
            this->dec_X();
        else if (this->ir == 27)
            this->push();
        else if (this->ir == 28)
            this->pop();
        else if (this->ir == 29)
            this->Intt();
        else if (this->ir == 30)
            this->IRet();
        else if (this->ir == 50)
            this->End();
    }
    
    void CPU::load_value () {                       //Several instructions that CPU can perform
        int a = this->c_read();
        ac = a;
    }
    
    void CPU::load_addr () {
        int a = this->c_read();
        ac = this->c_read(a);
        
    }
    
    void CPU::loadInd_addr () {
        int a = this->c_read();
        int temp = this->c_read(a);
        ac = this->c_read(temp);
        
    }
    
    void CPU::loadIdxX_addr () {
        int a = this->c_read();
        ac = this->c_read(a+x);
        
    }
    
    void CPU::loadIdxY_addr () {
        int a = this->c_read();
        ac = this->c_read(a+y);
    }
    
    void CPU::LoadSpX () {
        ac = this->c_read(x+sp+1);
    }
    
    void CPU::store_addr () {
        int a = this->c_read();
        this->c_write(a, ac);
        
    }
    
    void CPU::get_random () {
        ac = rand()%100 + 1;
    }
    
    void CPU::put_port () {
        int port = this->c_read();
        if(port == 1) {
            cout << this->ac;
        }
        else if (port == 2) {
            char a = this->ac;
            cout << a;
        }
        
    }
    
    void CPU::addX () {
        ac = ac + x;
        
    }
    
    void CPU::addY () {
        ac = ac + y;
    }
    
    void CPU::subX () {
        ac = ac - x;
        
    }
    
    void CPU::subY () {
        ac = ac - y;
        
    }
    
    void CPU::copyTo_X () {
        x = ac;
    }
    
    void CPU::copyTo_Y () {
        y  = ac;
    }
    
    void CPU::copyFrom_X () {
        ac = x;
        
    }
    
    void CPU::copyFrom_Y () {
        ac = y;
        
    }
    
    void CPU::copyTo_Sp () {
        sp = ac; 
        
    }
    
    void CPU::copyFrom_Sp () {
        ac = sp;
        
    }
    
    void CPU::jump_addr () {
        int a = this->c_read();
        pc = a;
    }
    
    void CPU::jumpIfEqual_addr () {
        int a = this->c_read();
        
        if(ac == 0) {
            pc = a;
        }
    }
    
    void CPU::jumpIfNotEqual_addr () {
        int a = this->c_read();
        if(ac != 0) {
            pc = a;
        }
    }
    
    void CPU::call_addr () {
        int a = this->c_read();
        this->c_write(sp, pc);
        sp--;
        pc = a;
    }
    
    void CPU::ret () {
        sp++;
        int a = this->c_read(sp);
        pc = a;
    }
    
    void CPU::inc_X () {
        x = x + 1;
        
    }
    
    void CPU::dec_X () {
        x = x - 1;
        
    }
    
    void CPU::push () {
        this->c_write(sp, ac);
        sp--;
    }
    
    void CPU::pop () {
        sp++;
        ac = this->c_read(sp);
    }
    
    void CPU::Intt () {
        if(this->kernel == true) {
            return;
        }
        this->kernel = true;
        this->c_write(1999, pc);
        this->c_write(1998, sp);
        this->sp = 1997;
        pc = 1500;
    }
    
    void CPU::IRet () {
        
        if(this->kernel == false)
            return;
        if(btimer == true) {
            time_counter = 1;
            btimer = false;
        }
        
        this->pc = this->c_read(1999);
        this->sp = this->c_read(1998);
        this->kernel = false;
        
        
    }
    
    void CPU::End () {                                  //Terminates the program
        int prompt = 2;
        write(pip1[1], &prompt, sizeof(int));
    }
    