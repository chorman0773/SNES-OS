#ifndef __Hash_hp_2018_03_23_09_48
#define __Hash_hp_2018_03_23_09_48
#pragma once
#include <cstdint>
#include <type_traits>
#include <typeinfo>
#include <vector>
#include <memory>
#include <utility>
#include <map>
class Hashable{
public:
	virtual int hashCode()const = 0;
};

 constexpr int32_t hashcode(char c){
	return int(c)|(c&0x80!=0?0xffffff00:0);	 
 }
 constexpr int32_t hashcode(unsigned char c){
 	return int(c)&0xff;	 
 }
 constexpr int32_t hashcode(short s){
	return int(s)|(s&0x8000!=0?0xffff0000:0);	 
 }
 constexpr int32_t hashcode(unsigned short s){
	return int(s)&0xffff;	 
 }
 constexpr int32_t hashcode(int i){
	return i;	 
 }
 constexpr int32_t hashcode(unsigned int i){
	return int(i);	 
 }
 constexpr int32_t hashcode(long long l){
	return (l>>32)^(l&0xffffffff);	 
 }
 constexpr int32_t hashcode(unsigned long long l){
	return (l>>32)^(l&0xffffffff);	 
 }
 constexpr int32_t hashcode(float f){
	union{
	 float f1;
         int bits;
	};
	f1 = f;
	return hashcode(bits);
 }
 
 constexpr int32_t hashcode(double d){
	 union{
	  double d1;
          long long bits;
	 };
	 d1 = d;
	 return hashcode(Bits);
 }

 template<typename E,typename UType=typename std::underlying_type<E>::type> constexpr int32_t hashcode(E e){
	union{
	  E e1;
          UType bits;
	};
	e1 = e;
	return hashcode(bits);
 }

 constexpr int32_t hashcode(void* v){
   return (int32_t)v;	 
 }
 constexpr int32_t hashcode(nullptr_t n){
  return 0;	 
 }

using std::vector;

template<typename T> int32_t hashcode(const vector<T>& v){
	int32_t h = 0;
	for(int i = 0;i<v.size();i++){
		h*=31;
		h+=hashcode(v[i]);
	}
	return h;
}

using std::array;

template<typename T,int size>  int32_t hashcode(const array<T,size>& a){
	int32_t h = 0;
	for(int i = 0;i<size;i++){
		h*=31;
		h+=hashcode(a[i]);
	}
	return h;
} 

using std::unique_ptr;
using std::shared_ptr;

const int32_t uniqueSmartPrime = 11443717;
const int32_t sharedSmartPrime = 540283;

template<typename T> int32_t hashcode(const unique_ptr<T>&ptr){
	return hashcode(ptr.get())*uniqueSmartPrime;
}

template<typename T> int32_t hashcode(const shared_ptr<T>& ptr){
	return hashcode(ptr.get())*sharedSmartPrime;
}

using std::pair;
template<typename T,typename U> int32_t hashcode(const pair<T,U>& p){
	return hashcode(p.first)*31+hashcode(p.second);
}

template<typename T> int32_t hashcode(const pair<T*,int>& a){
	//Treat as array not as pair
	int32_t h = 0;
	for(int i =0;i<a.second;i++){
		h*=31;
		h+=hashcode(a.second()[i]);
	}
	return h;
}

using std::map;

template<typename K,typename V> int32_t hashcode(const map<K,V>& m){
	int32_t hash = 0;
	for(pair<K,V>& p:m){
		hash*=31;
		hash+=hashcode(p);
	}
	return hash;
}


#endif
