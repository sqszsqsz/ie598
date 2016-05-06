//
//  main.cpp
//  FMS 1
//
//  Created by Ramavarapu Sreenivas on 3/11/16.
//  Copyright © 2016 Ramavarapu Sreenivas. All rights reserved.
//
//  Worked off sample code found at https://github.com/kunalghosh/
// 
#include <cstdlib>
#include <cmath>
#include <unordered_map>
#include <functional>
#include <algorithm>
#include <cstring>
#include <iostream>
#include <map>
#include <chrono>
#include <ctime>
#include <vector>
#include <numeric> 
#include "hashes.h"

using namespace std;

unsigned long long rho(unsigned long hashVal)
{
    // computing the tail-length of hashVal (we are looking for strings of 0's)
    unsigned long long rho = 0;
    int mask = 0x1;
    if(hashVal != 0)
    {
        // while-loop is executed only of the least-significant-bit of hashVal is 0
        while((hashVal & mask) == 0)
        {
            rho++;
            hashVal = hashVal  >> 1; // right-shift the hashVal by 1 bit position
        }
    }
    return rho;
}

void set_bit(unsigned long long &bit_str, long long pos)
{
    // see BITMAP operation in https://en.wikipedia.org/wiki/Flajolet–Martin_algorithm
    long long mask = 0x1 << pos;
    bit_str = bit_str | mask;
}

unsigned long long get_estimated_distinct_nums(unsigned long long bit_str)
{
    // see https://en.wikipedia.org/wiki/Flajolet–Martin_algorithm for details
    double phi = 0.77351;
    unsigned long long pos = 0;
    int mask = 0x1;
    
    while((bit_str & mask)!= 0)
    {
        bit_str = bit_str >> 1;
        pos++;
    }
    return (pow(2,pos) / phi) ;
}


int main(int argc, char *argv[])
{
    clock_t time_before, time_after;
    // unsigned long long seed1;

    if (argc != 3) {
    	cout << "Input format: ./mp5 [number of bins] [number of trials in each bin] " << endl;
    	return 0;
    }

    int num_bin = atoi(argv[1]);
    int num_trial = atoi(argv[2]);
    
    // took this off http://www.cplusplus.com/reference/random/mersenne_twister_engine/seed/
    typedef std::chrono::high_resolution_clock myclock;
    myclock::time_point beginning = myclock::now();
    
    // obtain a seed from the timer

    vector<vector<unsigned long long>> seed(num_bin, vector<unsigned long long>(num_trial));

    for (int i=0;i<num_bin;i++){
    	for (int j=0;j<num_trial;j++){

    		myclock::time_point now = myclock::now();
    		myclock::duration d = myclock::now() - now;
			seed[i][j] = d.count();
			// cout << "seed " << d.count() << endl;
    		
    	}
    }
    
    // we are going to use the MurmurHash2 as our hash function
    // to get different outcomes, we are relying on changing seed1
    // (which is set using the system clock; see above).
    string hashFunc = "mm2";
    unsigned int bit_limit = 0;
    
    string a;
    ios::sync_with_stdio(false);
    time_before = clock();

    vector<vector<unsigned long long>> bit_fields(num_bin, vector<unsigned long long>(num_trial,0));
    vector<vector<double>> bit_results(num_bin, vector<double>(num_trial));

    while(getline(cin,a))
    {
        if(a.empty())
        {
            a = "\n";
        }

        for (int i=0;i<num_bin;i++){
        	for (int j=0;j<num_trial;j++){

        		set_bit(bit_fields[i][j], int(rho(hashstr(hashFunc,a,bit_limit,seed[i][j],seed[i][j]))));
        		
        	}
        }
    }

	vector<double> result(num_bin);

    for (int i=0;i<num_bin;i++){
    	for (int j=0;j<num_trial;j++){

    		bit_results[i][j] = get_estimated_distinct_nums(bit_fields[i][j]);
    		// cout << "average anser: " << bit_results[i][j] << endl;
			    		
    	}

    	double sum = std::accumulate(bit_results[i].begin(), bit_results[i].end(), 0.0);
		double mean = sum / bit_results[i].size();
		result[i] = mean;
		 cout << "average of a bin: " << (int)mean << endl;

    }

    double median;
    sort(result.begin(),result.end());

	if (num_bin % 2 == 0)
	{
	  median = (result[num_bin/2 - 1] + result[num_bin/2]) / 2;
	}
	else 
	{
	  median = result[num_bin/ 2];
	}

    time_after = clock();
    cout << "Median of bin-averages: " << (int)median << endl;
    cout << "Time: " << ((double) time_after - (double) time_before)/CLOCKS_PER_SEC << " seconds"<< endl;
    return 0;
}


