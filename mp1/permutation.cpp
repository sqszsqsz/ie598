//
//  main.cpp
//  nth lexicographic permutation
//
//  Created by Ramavarapu Sreenivas on 6/22/15.
//  Copyright (c) 2015 Ramavarapu Sreenivas. All rights reserved.
//
//  Generalization of the following problem at Project Euler: https://projecteuler.net/problem=24
//  Hint File

#include <iostream>
#include <vector>
#include <deque>
#include <algorithm>
#include <stdio.h>
using namespace std;

long my_factorial(long n)
{
    if (1 == n)
        return 1;
    else
        return n*my_factorial(n-1);
}

vector <long> factorial_expansion(long n, long size)
{
    vector <long> result;
    // write code here that generates the factorial-expansion of n
    // see https://en.wikipedia.org/wiki/Factorial_number_system for details
    // the only issue I have with this wikipedia-page is that there is really
    // no reason why you would want to consider an expansion using 0! (Why?)
    // you need to write the number "n" in terms of 1!, 2!, 3!, etc etc (no 0!)
    // store the factorial-expansion in a vector "result" and return it.

    long num = n;
    
    for (int i=2;i<=size;i++){
    	result.push_back(num%i);
    	num/=i;
    }

    return result;
}


int main(int argc, const char * argv[])
{
	if (argc!=3) {
    	cout << "The legal input format is ./permutation number symbol_size" << endl;
    	return 0;
    }


    long number, symbol_size, limit;
    sscanf (argv[1], "%ld", &number);
    sscanf (argv[2], "%ld", &symbol_size);

    
    // I do not want an "alphabet" set that is more than 10-symbols -- because I will have a
    // hard-time writing the result (you will have to use 0,1,...,9,A,B,C... etc...).  But
    // it is do-able.  Also, this way your result can be verified with the solution for
    // Project Euler Problem 24 (which is a one-off/specific-case of the general problem your
    // code is supposed to solve.
    if (symbol_size > 10)
    {
        cout << "Symbol Size (which is, " << symbol_size << ") has to be <= 10" << endl << "Quitting..." << endl;
        return 0;
    }

    if (number==0) {
    	cout << "The number should start from 1." << endl;
    	return 0;
    }
    
    // creating my "alphabet" set which is 0,1,2,... etc
    deque <int> symbols;
    for (int i = 0; i < symbol_size; i++)
        symbols.push_back(i);
    cout << "Adopted Lexicographic Order is: ";
    for (int i = 0; i < symbols.size(); i++)
        cout << symbols[i];
    cout << endl;
    
    vector <long> result = factorial_expansion(number-1, symbol_size);
    vector<long> result_OneIndex = factorial_expansion(number,symbol_size);
    cout << "Factorial-Number-System-Expansion of " << number << " is given below"<< endl;
    
    cout << number << " = ";
    for (int i = 0; i < result_OneIndex.size(); i++)
    {
        cout << "(" << result_OneIndex[i] << "*" << i+1 << "!) ";
        if (i != result_OneIndex.size()-1)
            cout << "+ ";
    }
    cout << endl;
    //cout << "(cf. https://en.wikipedia.org/wiki/Factorial_number_system)" << endl;
    
    int bunga=number;
    limit = my_factorial(symbol_size);
    if (bunga > limit)
    {
        cout << "There are at most " << limit << "-many permutations of " << symbol_size << "-many objects" << endl;
        cout << "There is no " << bunga << "-th lexicographic permutations... quitting" << endl;
    }
    else
    {
        cout << "Therefore, the " << bunga << "-th lexicographic permutation is: ";
        
        // figure out what needs to go in here for things to work...
        // come see me if you are lost/stuck.
        for (int i=result.size()-1;i>=0;i--){
        	cout << symbols[result[i]];
        	symbols.erase(symbols.begin()+result[i]);
        }
        cout << symbols[0];
        cout << endl;
    }
    
    return 0;
}
