/*
    Name: Attribute
    Date: 2014.07.02
    Desc: Attribute of XML
*/
#ifndef __SPARK_ATTRIBUTE_H__
#define __SPARK_ATTRIBUTE_H__

#include <string>
using namespace std;

// Attribute in the Tag
class Attribute {
public:
    Attribute(string name, string value);
    const string* GetValue() const;
    const string* GetName() const;

    // parsing string of m_Value
    int GetIntValue() const;    
    double GetDoubleValue() const;
    int GetIntValues(int* out, int number) const;           // return number of read values on right-way
    int GetDoubleValues(double* out, int number) const;     // return number of read values on right-way

    void Set(const char* name, const int* values, int numValues);
    void Set(const char* name, const double* values, int numValues);

private:
    string m_Name;
    string m_Value;
};

#endif