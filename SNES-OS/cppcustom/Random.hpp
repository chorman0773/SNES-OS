#ifndef Random_hpp_2018_02_26_08_26
#define Random_hpp_2018_02_26_08_26
#pragma once
#include <cstdint>
#include <ctime>
#include <vector>
#include <cmath>
#include <mutex>
#include <thread>
#include <array>
typedef uint64_t seed_t;


/**
	Random Number Generator Definition provided by java standard library:
	Generator location is: https://docs.oracle.com/javase/8/docs/api/java/util/Random.html
	This file follows the specification for the Random class defined by that document.
	As per the specification this class comes with 2 Warnings:
	The Random class is thread-safe, however using an instance of Random across multiple threads may have unpredictable effects.
	The Random class is not cryptographically-secure. 
	See the warnings on https://docs.oracle.com/javase/8/docs/api/java/util/Random.html for more details on these warnings
	Code implementation provided by Connor Horman.
*/
using std::mutex;
using std::try_lock;
using std::array;
class Random{
private:
	seed_t seed;
	double nextNextGaussian;
	bool haveNextNextGaussian;
	mutex lock;
protected:
	virtual uint32_t next(int bits);

public:
	Random();

	Random(seed_t);
	virtual void setSeed(seed_t);

	int nextInt();
	int nextInt(int);
	double nextGuassian();
	int64_t nextLong();
	float nextFloat();
	double nextDouble();
	virtual void nextBytes(uint8_t*,size_t);
	template<size_t size> void nextBytes(array<uint8_t,size>&);
	
};

template<size_t size> void Random::nextBytes(array<uint8_t,size>& bytes) {
   this->nextBytes(bytes.data(),size);
 }


#endif
