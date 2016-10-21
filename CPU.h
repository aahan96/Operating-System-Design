/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   CPU.h
 * Author: Aahan
 *
 * Created on September 26, 2016, 7:36 PM
 */

#ifndef CPU_H
#define CPU_H

class CPU {                                     //Class for handling CPUoperations
    
public: 
    
    CPU(int p1[2], int p2[2], int timer);       //Constructor for CPU
    
    bool kernel;                                    //All the values defined
    bool btimer;
    int pc, sp, ir, ac, x, y;
    int pip1[2];
    int pip2[2];
    
    int c_read(int a=-67);
    void c_write(int add, int x);
    
    void load_ir();
    void start_timer();
    int time_counter;
    
    void load_value ();
    void load_addr ();
    void loadInd_addr ();
    void loadIdxX_addr ();
    void loadIdxY_addr ();
    void LoadSpX ();
    void store_addr ();
    void get_random ();
    void put_port ();
    void addX ();
    void addY ();
    void subX ();
    void subY ();
    void copyTo_X ();
    void copyTo_Y ();
    void copyFrom_X ();
    void copyFrom_Y ();
    void copyTo_Sp ();
    void copyFrom_Sp ();
    void jump_addr ();
    void jumpIfEqual_addr ();
    void jumpIfNotEqual_addr ();
    void call_addr ();
    void ret ();
    void inc_X ();
    void dec_X ();
    void push ();
    void pop ();
    void Intt ();
    void IRet ();
    void End ();
    
};

#endif /* CPU_H */

