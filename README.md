# Disk-Scheduler
C Program designed to simulate disk scheduling algorithms

## About
C Program designed to simulate the following disk scheduling algorithms

1. FCFS 
2. SSTF
3. SCAN
4. C-SCAN
5. LOOK
6. C-LOOK

The program reads its request from a binary file called “request.bin”. It goes through 300 cylinder numbers (from 0 to 299). Based on the algorithm it would simulate moving. This program was developed as part of my CS 3SH3 : Operating Systems class.

## Usage
The program takes the initial position of the disk head as the first command line argument and the direction of the head as the second command line argument. 

To use this program, you have to first create an executable file. 

1. Download the diskscheduler.c file 
2. Run the following command to create an executable file:
    1. gcc diskscheduler.c -o diskscheduler
3. To run the program, use a command in the following format:
    1. diskscheduler 100 LEFT
        1. Where 100 is the initial disk head position 
        2. and LEFT is the direction the disk head will move 
        

All the Algorithms will be executed when this one command is run
