README

IE598 MP5

By 
Zhe Sun

included:

- Source file: main.cpp
- Makefile: Makefile
- Screenshot of the program output
- this README

----------------------
Command Line Arguments
----------------------

Compile: make

Run: head -[number of lines to read] [input file path] | ./mp5 [number of bins] [number of trials for each bin]

-------------------------
Code Output
-------------------------

The user needs to specify the number of bins, and the number of trials for each bin.
Flajolet-Martin algorithm will be run for (number of bin * number of trial) times, each time an estimate of the distinct count of the stream inputs is computed.
The average value for each bin is computed, and the median of the bin-averages will be the final estimated answer for the distinct-count problem.

