#include "Attribute.h"
#include <sstream>
using namespace std;

//--------------------------------------------------------------------------------------
// Name: 
// Desc: 
//-------------------------------------------------------------------------------------
Attribute::Attribute(string name, string value) : m_Name(name), m_Value(value) 
{
}

//--------------------------------------------------------------------------------------
// Name: 
// Desc: 
//-------------------------------------------------------------------------------------
const string* Attribute::GetValue() const
{
    return &m_Value;
}

//--------------------------------------------------------------------------------------
// Name: 
// Desc: 
//-------------------------------------------------------------------------------------
const string* Attribute::GetName() const
{
    return &m_Name;
}
//--------------------------------------------------------------------------------------------------
// Name: GetIntValue & GetDoubleValue
// Desc: Thoses functions parse m_values, then return sigle value.
//       There is no-way to know the functions return right value.
//--------------------------------------------------------------------------------------------------
int Attribute::GetIntValue() const
{
    istringstream iss(m_Value);
    int ret = 0;
    iss>>ret;
    return ret;
}

double Attribute::GetDoubleValue() const
{
    istringstream iss(m_Value);
    double ret = 0;
    iss>>ret;
    return ret;
}
//--------------------------------------------------------------------------------------------------
// Name: GetIntValues & GetDoubleValues
// Desc: Thoses functions parse m_values, then return 'number' of values
//       Also it returns number of right values.
//------------------------------------------------------------------------------------------------
int Attribute::GetIntValues(int* out, int number) const
{   
    istringstream iss(m_Value);
    int numRead=0;
    for(int i=0; i<number; ++i) {
        iss>>out[i];
        if(iss.fail())
            break;
        numRead++;
        iss.ignore(m_Value.size(), ',');
    }
    return numRead;
}
int Attribute::GetDoubleValues(double* out, int number) const
{
    istringstream iss(m_Value);
    int numRead=0;
    for(int i=0; i<number; ++i) {
        iss>>out[i];
        if(iss.fail())
            break;
        numRead++;
        iss.ignore(m_Value.size(), ',');
    }
    return numRead;
}

//--------------------------------------------------------------------------------------------------
// Name: 
// Desc: 
//------------------------------------------------------------------------------------------------
void Attribute::Set(const char* name, const int* values, int  numValues)
{   
    m_Name = name;
    ostringstream oss;
    if( numValues > 0 ) {
        for( int i=0; i<numValues-1; i++) {
            oss << values[i] << ", ";                       
        }
        oss << values[numValues-1];
    }
    m_Value = oss.str();
}

//--------------------------------------------------------------------------------------------------
// Name: 
// Desc: 
//------------------------------------------------------------------------------------------------
 void Attribute::Set(const char* name, const double* values, int numValues)
 {
    m_Name = name;
    ostringstream oss;
    if( numValues > 0 ) {
        for( int i=0; i<numValues-1; i++) {
            oss << values[i] << ", ";                       
        }
        oss << values[numValues-1];
    }
    m_Value = oss.str();
 }