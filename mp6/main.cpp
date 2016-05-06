//
//  main.cpp
//  FMS 3
//
//  Created by Ramavarapu Sreenivas on 3/12/16.
//  Copyright © 2016 Ramavarapu Sreenivas. All rights reserved.
//
//
//  Worked off sample code found at https://github.com/kunalghosh/
//

#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <random>
#include <algorithm>
#include <cstdlib>
#include <chrono>
#include <unordered_map>

using namespace std;

int main(int argc, char* argv[])
{
    unsigned long long seed1;
    
    // took this off http://www.cplusplus.com/reference/random/mersenne_twister_engine/seed/
    typedef std::chrono::high_resolution_clock myclock;
    myclock::time_point beginning = myclock::now();
    
    // obtain a seed from the timer
    myclock::duration d = myclock::now() - beginning;
    seed1 = d.count();
    // let us look at the seed
    cout << "Current Seed: " << std::bitset<32> (seed1) << endl;
    
    // Default value of the number of 2nd moment estimates is 20
    // The user can ask for more/less
    // unsigned long long S = 20;
    // char *end; // need this for http://www.cplusplus.com/reference/cstdlib/strtoull/
    // if(argc >= 2)
    // {
    //     S = strtoull(argv[1], &end,10);
    // }

    if(argc != 3) {
        cout << "Specify a minimum value and a maximum value for S" <<endl;
        cout << "Format: ./mp6 [minimum value for S] [maximum value for S]" << endl;
        return 0;
    }


    int min_S = atoi(argv[1]);
    int max_S = atoi(argv[2]);
    if (max_S < min_S) {
        cout << "Max S must be larger than the minimum S" << endl;
        return 0;
    }
    int num_S = max_S - min_S + 1;
    unordered_map<string,long long> hashmap;


    unsigned long long idx_to_del;
    string line_to_del;
    
    // X_ListIdx is a map that keeps track of the stream-positions where the
    // string-argument appeared in the data-stream.  The stream-positions are
    // stored as vectors, indexed to the name (i.e. string) of the stream-element.
    // Wrt my notes -- X_listIdx[j] keeps track of the stream-positions where "j"
    // occurred
    // map <string, vector<unsigned long> > X_listIdx;
    
    // X_xcount keeps track of the number "r" (see my notes)
    // vector <pair<string, unsigned long> > X_xcount;
    
    // something that I saw on web (https://github.com/kunalghosh/) to keep help
    // with the nitty-gritty of AMS-procedure


    vector < map <string, vector<unsigned long> > > index_array(num_S);
    vector < vector< pair<string, unsigned long> > > count_array(num_S);


    pair <string , unsigned long> p;
    unsigned long n = -1;
    
    // Using the Marsenne Twister Engine as the "source" of randomness
    // (cf. http://www.cplusplus.com/reference/random/mersenne_twister_engine/mersenne_twister_engine/)
    // In previous code samples we (implicitly) used the Linear-Congruential-Engine
    // (cf. http://www.cplusplus.com/reference/random/linear_congruential_engine/)
    //
    mt19937 mt (seed1);

    // Need this for random sampling of streams
    // took it from http://www.cplusplus.com/reference/random/uniform_real_distribution/
    std::uniform_real_distribution<double> distribution(0.0,1.0);
    
    // To get the random index to remove from X_xcount
    typedef uniform_int_distribution<unsigned long long> my_uniform_int;

    
    ios::sync_with_stdio(false);
    string a;
    while(getline(cin, a))
    {
        if(a.empty())
        {
            a = "\n";
        }
        n += 1;

        if (hashmap.find(a) == hashmap.end()) {
	    	hashmap[a] = 1;
	    }
	    else hashmap[a]++;


        for (int i=min_S;i<=max_S;i++){
                
                if(n < i)
                {
                    if(index_array[i-min_S].find(a) == index_array[i-min_S].end()) // check if a was seen before
                    {

                        p = pair<string, unsigned long> (a,1);
                        count_array[i-min_S].push_back(p);
                        index_array[i-min_S][a].push_back(n);
                    }
                    else
                    {
                        for(auto idx: index_array[i-min_S][a]){
                            count_array[i-min_S][idx].second += 1;
                        }

                    }
                    
                } else
                { 
                    // check if the new stream-element should replace one of the S-many estimators
                    if(distribution(mt) < ((double) i)/((double) n))
                    {
                        // figuring out which of the S-many estimators is to be deleted
                        idx_to_del = my_uniform_int(0,i)(mt);
                      
                        line_to_del = count_array[i-min_S][idx_to_del].first;

                        index_array[i-min_S][line_to_del].erase(remove(index_array[i-min_S][line_to_del].begin(), index_array[i-min_S][line_to_del].end(), idx_to_del), index_array[i-min_S][line_to_del].end());

                        if(index_array[i-min_S][line_to_del].empty())
                        {
                            index_array[i-min_S].erase(index_array[i-min_S].find(line_to_del));
                        }

                        // adding the new stream-element as the new member of the S-many estimators
                        p = pair<string, unsigned long>(a,1);
                        count_array[i-min_S][idx_to_del] = p;
                        index_array[i-min_S][a].push_back(idx_to_del);

                    } else {
                        // line was not picked

                        if(index_array[i-min_S].find(a) != index_array[i-min_S].end()){
                            for(auto idx: index_array[i-min_S][a]){
                                count_array[i-min_S][idx].second += 1;
                            }
                        }

                    }
                }


            
        }

        



    }
    
    cout << "#Elements seen: " << n+1 << "; " << "#Estimators from " << min_S << " to " << max_S <<  endl;
    
    vector<long long> results(num_S);

    for (int i=min_S;i<=max_S;i++){
        

            long long mean = 0;
            for (auto v: count_array[i-min_S])
            {
                mean += (n+1) * ((2*v.second) - 1);
            }

            // cout << "mean =" << mean << endl;

            results[i-min_S] = mean/index_array[i-min_S].size();
            // cout << "F2 Estimate in this trial: " << bin_results[i][j] << endl;

        
    }

    long long second_moment = 0;
	for (auto kv : hashmap) {
		second_moment += pow(kv.second,2);
	}

	cout << "Exact F2 moments is " << second_moment << endl;

    int diff_idx;
    long long min_diff = results[0];

    for (int i=min_S; i<= max_S ; i++){

        long long diff = abs(results[i-min_S] - second_moment);
        if (diff < min_diff) {
            diff_idx = i;
            min_diff = diff;
        }
	    
		cout <<  "F2 Estimate using " << i << " estimators = " << results[i-min_S] << endl;
	
    }

    cout << "The most ideal number of estimator is " << diff_idx << endl;
    
    return 0;
}

