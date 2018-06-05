/*
 * Version.hpp
 * Class for Version Management.
 * Versions are comparable and Hashable. 
 *  Created on: Apr 4, 2018
 *      Author: Connor Horman
 */

#ifndef __VERSION_HPP__18_04_04_11_12_42
#define __VERSION_HPP__18_04_04_11_12_42
#include <string>
#include <iostream>
#include "Hash.hpp"
#undef major
#undef minor

#include <type_traits>

using std::string;
using std::istream;
using std::ostream;






/*
 * Represents a version of the code.
 * This specification only defines the Major and Minor parts of the version and is encoded
 * using ObjectiveLua's Encoding.
 * This class also provides utilities for obtaining versions from strings, and from a given
 * major and minor, as well as reading and writing to Data Streams (and text streams).
 * The Version class provides both the read from (istream >>) and the write to (ostream <<) operators
 * To write in string form.
 */
class Version : public Hashable{
private:
	unsigned char major;
	unsigned char minor;
public:
	/*
	 * Constructs an unknown (null) version.
	 * The default Version produced is 1.0
	 */
	constexpr Version():major(0),minor(0){}
	/*
	 * Obtains a version given in an encoded form (Ex. 0x0000).
	 * This follows the sentry format for encoding versions (2-bytes BE, High-byte is Major version -1, Low-byte is minor version)
	 * This Constructor should be used only when you are dealing with Embedded and Encoded Version constants
	 */
	constexpr Version(int i):major(i>>8),minor(i&0xff){}
	/*
	 * Parses a given string in the form <Mj>.<mi> and produces a version given those 2 inputs.
	 * Both Mj and mi must be valid integers, with Mj being between 1 and 256 and Mi being between 0 and 255
	 */
	Version(string);
	/*
	 * Obtains a version based on a given Major and minor version.
	 * Major must be between 1 and 256 and minor must be between 0 and 255
	 */
	constexpr Version(int maj,int min):major((maj-1)&0xff),minor(min&0xff){}
	
	constexpr Version(const Version&)=default;
	constexpr Version(Version&&)=default;
	
	constexpr Version& operator=(const Version&)=default;
	constexpr Version& operator=(Version&&)=default
	
	/*
	 * Gets the major version, ranging from 1 to 256
	 */
	constexpr int getMajor()const{
	  return int(major)+1;   
    	}	
	/*
	 * Gets the minor version, ranging from 0 to 255
	 */
	constexpr int getMinor()const{
     	  return minor;   
    	}
	/*
	 * Returns the version in encoded form.
	 * The resultant value is 2-bytes consisting of major-1<<8|minor.
	 */
	int getEncoded()const;
	/*
	 * Obtains the Origin of this Version. The origin of a Version is equal to the Version
	 * that has the same Major version, but a minor version of 0.
	 */
	constexpr Version getOrigin()const{
	     return Version(major,0);   
    	}
	/*
	 * Returns this Version as a string.
	 * The Resultant String is in the form <major>.<minor>
	 */
	string toString()const;
	/*
	 * Computes the hashcode of this Version.
	 * This is effectively major*31+minor
	 */
	int32_t hashCode()const;
	/*
	 * Compares this version with annother. A Version is the same if its Major version and
	 * Minor version are exactly the same
	 */
	constexpr bool operator==(const Version& v)const{
        	return v.major==major&&v.minor==minor;
    	}
	/*
	 * Compares this version with another. A Version is less-than another if its major version is less
	 * than the other version's major version, or they share the same origin, and the first has a lower minor version
	 */
	constexpr bool operator<(const Version& v)const{
        	return major<v.major||(major==v.major&&minor<v.minor);
    	}
	/*
	 * Compares this version with another. A Version is Greater-than another if its major version is greater than
	 * the other versions' major version, or they share the same origin, and the first version has a greater minor version
	 */
	constexpr bool operator>(const Version& v)const{
       	 return major>v.major||(major==v.major&&minor>v.minor);
    	}
	/*
	 * Compound Comparison <=
	 */
	constexpr bool operator<=(const Version& v)const{
     		return major <=v.major||(major==v.major&&minor<=v.minor);   
 	}
	/*
	 * Compound Comparison >=
	 */
	constexpr bool operator>=(const Version& v)const{
        	return major>=v.major||(major==v.major&&minor>=v.minor);
    	}
        constexpr bool operator!=(const Version& v)const{
		return major!=v.major||minor!=v.minor;
    	}
};

/*
 * Reads a version from a text stream.
 * The input text is assumed to be in the form <Mj>.<mi>
 * This is effectively the same as reading a string from the stream,
 * and Constructing the associated version.
 *
 */
istream& operator>>(istream&,Version&);
/*
 * Writes this string to a text stream.
 * The output text is will be in the fomr <Mj>.<mi>
 * This is effecitvely the same as writing that version's toString()
 */
ostream& operator<<(ostream&,const Version&);


template<typename verconst> struct VersionConstants{
public:
    static const constexpr bool isValid = false;
    VersionConstants()=delete;
    VersionConstants(const VersionConstants<verconst>&)=delete;
    VersionConstants(VersionConstants<verconst>&&)=delete;
    VersionConstants& operator=(const VersionConstants<verconst>&)=delete;
    VersionConstants& operator=(Version<verconst>&&)=delete;
};
template<typename verconst> struct VersionConstants<typename std::conditional<false,std::void_t<decltype(verconst::major),decltype(verconst::minor),verconst>::type>{
public:
   static const constexpr bool isValid = true;
   constexpr VersionConstants()=default;
   constexpr VersionConstants(const VersionConstants<verconst>&)=default;
   constexpr VersionConstants(VersionConstants<verconst>&&)=default;
   constexpr VersionConstants<verconst>& operator=(const VersionConstants<verconst>&)=default;
   constexpr VersionConstants<verconst>& operator=(VersionConstants<verconst>&&)=default;
   constexpr operator Version()const{
    return Version(verconst::major,verconst::minor);   
   }
   constexpr Version operator()()const{
    return Version(verconst::major,verconst::minor);   
   }
   constexpr bool operator==(const Version& v)const{
       return verconst::major==v.getMajor()&&verconst::minor==v.getMinor();
   }
   constexpr bool operator!=(const Version& v)const{
       return verconst::major!=v.getMajor()||verconst::minor!=v.getMinor();
   }
   constexpr bool operator< (const Version& v)const{
       return verconst::major<v.getMajor()||(verconst::major==v.getMajor()&&verconst::minor<v.getMinor());
   }
   constexpr bool operator> (const Version& v)const{
       return verconst::major>v.getMajor()||(verconst::major==v.getMajor()&&verconst::minor>v.getMajor());
   }
   constexpr bool operator<=(const Version& v)const{
      return verconst::major<v.getMajor()||(verconst::major==v.getMajor()&&verconst::minor<=v.getMinor());
   }
   constexpr bool operator>=(const Version& v)const{
      return verconst::major>v.getMajor()||(verconst::major==v.getMajor()&&verconst::minor>=v.getMinor());
   }
};
template<typename verconst> using ValidVersionConstant = typename std::enable_if<VersionConstant<verconst>::isValid,const VersionConstant<verconst>>;
template<typename verconst> constexpr bool operator==(const Version& v,ValidVersionConstant<verconst> c){
    return c==v;
}
template<typename verconst> constexpr bool operator!=(const Version& v,ValidVersionConstant<verconst> c){
 return c!=v;   
}
template<typename verconst> constexpr bool operator< (const Version& v,ValidVersionConstant<verconst> c){
 return c>v;   
}
template<typename verconst> constexpr bool operator> (const Version& v,ValidVersionConstant<verconst> c){
 return c<v;   
}
template<typename verconst> constexpr bool operator<=(const Version& v,ValidVersionConstant<verconst> c){
 return c>=v;   
}
template<typename verconst> constexpr bool operator>=(const Version& v,ValidVersionConstant<verconst> c){
 return c<=v;   
}
namespace snesos{
    struct current{
        constexpr int major = 1;
        constexpr int minor = 0;
    };
        constexpr int major = 1;
        constexpr int minor = 0;
    };
    const constexpr VersionConstants<current> CurrentVersion{};
    const constexpr VersionConstants<origin> CurrentOrigin{};
};

#endif /* __VERSION_HPP__18_04_04_11_12_42 */
