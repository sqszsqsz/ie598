#ifndef HASHES_H
#define HASHES_H
/*
 * =====================================================================================
 *
 *       Filename:  hashes.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  12/26/2015 20:15:37
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */
#include <cstdlib>
#include <cmath>
#include <unordered_map>
#include <functional>
#include <cstring>
#include <iostream>
#include <map>

extern std::map<std::string,int> algos;
unsigned long long hashstr(std::string algo, std::string str, unsigned int bit_limit = 0, unsigned long long seed1 = 363019, unsigned long long seed2 = 363277);
unsigned long long polynomial_hash(std::string str, unsigned long seed = 5381);
unsigned long long djb2(std::string str, unsigned long seed = 5381);
unsigned long long jenkins_one_at_a_time_hash(std::string key);
unsigned long long paul_hash(std::string str,unsigned int seed = 5381);
uint32_t MurmurHash2 ( std::string key, int len, uint32_t seed = 5381 );
uint64_t MurmurHash64A ( const void * key, int len, uint64_t seed = 5381);
unsigned long long RSHash(const std::string str, unsigned long long a = 5381, unsigned long long b = 2887);
unsigned long long sum_mod(std::string str, unsigned long long seed = 5381);

std::map<std::string,int> algos = {{"jenkins",1},{"paul",2},{"cpp",3},{"mm2",4},{"poly",5},{"mm64a",6},{"rsh",7},{"djb2",8},{"cheap",9}};

unsigned long long hashstr(std::string algo, std::string str, unsigned int bit_limit, unsigned long long seed1, unsigned long long seed2)
{
    // std::map<std::string,int> algos = {{"jenkins",1},{"paul",2},{"cpp",3},{"mm2",4},{"poly",5},{"mm64a",6},{"rsh",7},{"djb2",8},{"cheap",9}};
    // NOTE !! Remember to update the algos map in hashes.h when any hash function is added or deleted.
    // bit_limit is used to simulate various bit limitations on the hash value.
    // put in 32 to mimic a 32 bit hash
    // max value is 64 because unsigned long long is (atmost) 64 bits. So values above 64 for bit_limit don't have predefied output.
    unsigned long long hashVal = -1;
    switch(algos[algo])
    {
        case 1:
            hashVal = jenkins_one_at_a_time_hash(str);
            break;
        case 2:
            hashVal = paul_hash(str, seed1);
            break;
        case 3:
            hashVal = std::hash<std::string>()(str);
            break;
        case 4:
            hashVal = MurmurHash2(str, (int) strlen(str.c_str()), seed1);
            break;
        case 5:
            hashVal = polynomial_hash(str,seed1);
            break;
        case 6:
            hashVal = MurmurHash64A(&str, (int) strlen(str.c_str()), seed1);
            break;
        case 7:
            hashVal = RSHash(str,seed1,seed2);
            break;
        case 8:
            hashVal = djb2(str, seed1);
            break;
        case 9:
            hashVal = sum_mod(str, seed1);
            break;
        default:
            std::cout << "Undefined hashing algorithm." << std::endl;
            break;
    }
    if(bit_limit != 0)
    {
        // mod with a power of 2
        unsigned long long div = 1; //(1 << bit_limit);
        hashVal = hashVal % (div << bit_limit);
    }
    return hashVal;
}

unsigned long long djb2(std::string str, unsigned long seed)
{
    // http://www.cse.yorku.ca/~oz/hash.html
    unsigned long hash = seed;
    for(char& c: str){
        hash = ((hash << 5) + hash) + int(c); /*  hash * 33 + c */
    }
    return hash;
}

unsigned long long sum_mod(std::string str, unsigned long long seed)
{
    // Really bad hash function size is at most the number of bits = log2(seed)
    unsigned long long sum = 0;
    for(char &c: str){
        sum += c;
    }
    // std::cout << str ;
    // std::cout <<  sum % seed << std::endl;
    return sum % seed;
}

unsigned long long polynomial_hash(std::string str, unsigned long seed)
{
    unsigned long retVal = 0;
    unsigned long power = 1;
    for(unsigned long idx = 0; idx < str.size(); idx++){
        // retVal += str[idx] * get_pow(seed, idx);
        retVal += str[idx] * power;
        power = power * seed;
    }
    return retVal;
}

unsigned long long RSHash(const std::string str, unsigned long long a, unsigned long long b)
{
    //unsigned int b    = 378551;
    //unsigned int a    = 63689;
    // unsigned int b    = 378533;
    // unsigned int a    = 63671;
    unsigned long long hash = 0;
    
    for(std::size_t i = 0; i < str.length(); i++)
    {
        hash = hash * a + str[i];
        a    = a * b;
    }
    
    return hash; // Why not modulo something to limit these values
}


unsigned long long jenkins_one_at_a_time_hash(std::string key)
{
    // https://en.wikipedia.org/wiki/Jenkins_hash_function
    long long hash, i, len=key.size();
    for(hash = i = 0; i < len; ++i)
    {
        hash += key[i];
        hash += (hash << 10);
        hash ^= (hash >> 6);
    }
    hash += (hash << 3);
    hash ^= (hash >> 11);
    hash += (hash << 15);
    return hash;
}

unsigned long long paul_hash(std::string str,unsigned int seed)
{
    unsigned long hash = seed;
    for(char& c: str)
    {
        hash = hash * 101  +  int(c);
    }
    return hash;
}

#define BIG_CONSTANT(x) (x##LLU)
uint32_t MurmurHash2 ( std::string str, int len, uint32_t seed )
{
    // https://code.google.com/p/smhasher/source/browse/branches/chandlerc_dev/MurmurHash2.cpp
    // 32 bit hash
    //  'm' and 'r' are mixing constants generated offline.
    // They're not really 'magic', they just happen to work well.
    const void * key = &str;
    
    const uint32_t m = 0x5bd1e995;
    const int r = 24;
    
    // Initialize the hash to a 'random' value
    
    uint32_t h = seed ^ len;
    
    // Mix 4 bytes at a time into the hash
    
    const unsigned char * data = (const unsigned char *)key;
    
    while(len >= 4)
    {
        uint32_t k = *(uint32_t*)data;
        
        k *= m;
        k ^= k >> r;
        k *= m;
        
        h *= m;
        h ^= k;
        
        data += 4;
        len -= 4;
    }
    
    // Handle the last few bytes of the input array
    
    switch(len)
    {
        case 3: h ^= data[2] << 16;
        case 2: h ^= data[1] << 8;
        case 1: h ^= data[0];
            h *= m;
    };
    
    // Do a few final mixes of the hash to ensure the last few
    // bytes are well-incorporated.
    
    h ^= h >> 13;
    h *= m;
    h ^= h >> 15;
    
    // std::cout << "Murmur2 seed :" << seed << " key : " << str << " hash : " << h << std::endl;
    
    return h;
}

uint64_t MurmurHash64A ( const void * key, int len, uint64_t seed )
{
    const uint64_t m = BIG_CONSTANT(0xc6a4a7935bd1e995);
    const int r = 47;
    
    uint64_t h = seed ^ (len * m);
    
    const uint64_t * data = (const uint64_t *)key;
    const uint64_t * end = data + (len/8);
    
    while(data != end)
    {
        uint64_t k = *data++;
        
        k *= m;
        k ^= k >> r;
        k *= m;
        
        h ^= k;
        h *= m;
    }
    
    const unsigned char * data2 = (const unsigned char*)data;
    
    switch(len & 7)
    {
        case 7: h ^= uint64_t(data2[6]) << 48;
        case 6: h ^= uint64_t(data2[5]) << 40;
        case 5: h ^= uint64_t(data2[4]) << 32;
        case 4: h ^= uint64_t(data2[3]) << 24;
        case 3: h ^= uint64_t(data2[2]) << 16;
        case 2: h ^= uint64_t(data2[1]) << 8;
        case 1: h ^= uint64_t(data2[0]);
            h *= m;
    };
    
    h ^= h >> r;
    h *= m;
    h ^= h >> r;
    // std::cout << "Murmur64a seed :" << seed << " key : " << (char*)key << " hash : " << h << std::endl;
    
    return h;
}


#endif /*  HASHES_H */
