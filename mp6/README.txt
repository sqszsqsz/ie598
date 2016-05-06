README

IE598 MP6

By 
Zhe Sun

included:

- Source file: main.cpp
- Makefile: Makefile
- Screenshot of the program output: Screen Shot 1, Screen Shot 2
- this README

----------------------
Command Line Arguments
----------------------

Compile: make

Run: head -[number of lines to read] [input file path] | ./mp6 [minimum value for S] [maximum value for S]

-------------------------
Code Output
-------------------------

In this assignment, the aim is to find an ideal value for S (the number of estimators) for the AMS algorithm to work for any data-set.

The user needs to specify a minimum trial number for S, and a maximum value for S.
An estimate for the second frequency moment is computed for each S value from the minimum value and the maximum value. These estimates obtained using different S values will be compared with the exact solution of the second-moment. The S value obtaining the closest estimate will be chosen as the most ideal number of estimators.

In the example shown in the screenshots, S value from 20 to 100 are used to estimate the second-moment. S value of 35 was found to be the most ideal value for S.

Note: different runs of the program may generate different estimates, so the optimal value of S may vary accordingly.
 



