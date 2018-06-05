#ifndef __UUID_hpp_2018_05_16_08_22
#define __UUID_hpp_2018_05_16_08_22
#include <string>
#include <cstdint>
#include <iostream>
#include <functional>

using std::string;
using std::ostream;
using std::istream;

/*
    A Class which represents a UUID, IE. a Universally Unique Identifier.
    This class defines many factories which can generate UUIDs.
    All factory Methods satisfy one of the UUID construction methods (Time Based, Namespaced (either SHA-1 or MD5), and Random)
    In addition converting constructors from string and const char* exist (as well a conversion operator to string).
    UUID satisfies TrivialType, Plain-Old-Datatype, and (in supporting Implementations) LiteralType.
    
*/
class UUID{
private:
	uint64_t high;
	uint64_t low;
public:
	static UUID fromString(string);
	static UUID randomUUID();
	static UUID uuidFromNamespace(string);
	static UUID ofNow();
	constexpr UUID(uint64_t high,uint64_t low):high(high),low(low){}
	constexpr UUID()=default;
	explicit UUID(const string&);
	explicit UUID(const char*);
	constexpr UUID(const UUID&)=default;
	constexpr UUID(UUID&&)=default;
	constexpr UUID& operator=(const UUID&)=default;
	constexpr UUID& operator=(UUID&&)=default;
	constexpr uint64_t getHigh()const{
	 return high;	
	}
	constexpr uint64_t getLow()const{
	 return low;	
	}
	int32_t hashCode()const noexcept;
	string toString()const;
    	explicit operator string()const;
};

ostream& operator<<(ostream&,const UUID&);
istream& operator>>(istream&,UUID&);
string  operator+(const string&,const UUID&);

namespace std{
    template<> struct hash<UUID>{
    public:
	size_t operator()(const UUID& u)noexcept{
	  return u.hashCode();	
	}
    };
};

#endif
