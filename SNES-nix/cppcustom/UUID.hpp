#ifndef __UUID_hpp_2018_05_16_08_22
#define __UUID_hpp_2018_05_16_08_22
#include <string>
#include <cstdint>
#include "Hash.hpp"
#include <iostream>

using std::string;
using std::ostream;
using std::istream;

class UUID : public Hashable{
private:
	uint64_t high;
	uint64_t low;
public:
	static UUID fromString(string);
	static UUID randomUUID();
	static UUID uuidFromNamespace(string);
	static UUID ofNow();
	UUID(uint64_t,uint64_t);
	UUID();
	UUID(string);
	uint64_t getHigh()const;
	uint64_t getLow()const;
	int32_t hashCode()const;
	string toString()const;
};

ostream& operator<<(ostream&,const UUID&);
istream& operator>>(istream&,UUID&);
string  operator+(const string&,const UUID&);



#endif
