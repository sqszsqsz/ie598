#include <iostream>
#include <cmath>
#include <time.h>
#include <stdio.h>
#include <string.h>
#include <unordered_map>

using namespace std;


int main (int argc, char* argv[])
{
	clock_t time_before, time_after;
	float diff;
	string input;
	unordered_map<string,long long> hashmap;
	int power;

	if (argc == 1) {
		power = 2;
	} else {
		power = (int)(argv[1][0]-'0');
	}

	time_before = clock();
	while (getline(cin, input)) {
	    if (hashmap.find(input) == hashmap.end()) {
	    	hashmap[input] = 1;
	    }
	    else hashmap[input]++;
	}
	cout << "Number of Distinct Words in the Input Stream = " << hashmap.size() << endl;
	time_after = clock(); 
	diff = ((float) time_after - (float) time_before);
	cout << "It took " << diff/CLOCKS_PER_SEC << " seconds to complete" << endl;

	time_before = clock();
	long long second_moment = 0;
	for (auto kv : hashmap) {
		second_moment += pow(kv.second,power);
	}

	cout << "Surprise number (or the sum of second-moments of frequency vector) = " << second_moment << endl;
	time_after = clock(); 
	diff = ((float) time_after - (float) time_before);
	cout << "It took " << diff/CLOCKS_PER_SEC << " seconds to complete" << endl;
}