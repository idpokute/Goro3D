/*
    Name: Tag
    Date: 2014.07.02
    Desc: XML Tag class
        : (EN) single tag which start from '<' to '>'
        : (KR) <부터 >까지의 한개의 태그를 의미한다. 느슨하게 되어있다. <뒤에 바로 태그명이 와야한다.
*/
#ifndef __SPARK_TAG_H__
#define __SPARK_TAG_H__

#include <vector>
#include <string>
using namespace std;

class Attribute;

// Single Tag class
class Tag {
public:
    enum Type { 
        TYPE_BEGIN,         // <TAG ...>
        TYPE_END,           // </TAG>
    };
    Tag(const char* tag_name);
    Tag(const char** readPointer, const char* end);     // readPointer must the character right after <
    virtual ~Tag();

    const string* GetName() const;
    const Type GetType() const;
    const vector<Attribute*>* GetAttributes() const;

private:
    string m_Name;                                   // name of the tag
    Type m_Type;                                     // type of the tag
    vector<Attribute*> m_Attributes;                 // attributes in the tag
};

#endif