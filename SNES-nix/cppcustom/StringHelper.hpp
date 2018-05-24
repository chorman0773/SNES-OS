#ifndef __StringHelper_hpp_2018_05_16_08_24
#define __StringHelper_hpp_2018_05_16_08_24
#include <string>

using std::string;

string tokenize(string&,string);

void replace(string&,string,string);

int count(string,string);

string toLowerCase(string&);
string toUpperCase(string&);
#endif
