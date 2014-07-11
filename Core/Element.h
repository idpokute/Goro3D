/*
    Name: Element
    Date: 2014.07.02
    Desc: (EN) Element of XML
        : (KR) ø§∏Æ∏’∆Æ π∂≈÷¿Ã
*/
#ifndef __SPARK_ELEMENT_H__
#define __SPARK_ELEMENT_H__

#include <vector>
#include <string>
using namespace std;

class Tag;
class Attribute;

class Element {
public:
    Element(const char* name);                                      // for writing
    Element(Tag* beginTag, const char** pos, const char* end);      // pos is cursor for scan to the 'end'
    virtual ~Element();

    const string* GetName() const;
    const Attribute* GetAttribute(int i) const;
    const unsigned int AttributeCount() const;
    const unsigned int ChildCount() const;
    const Element* GetChild(int i) const;
    Element* GetChild(int i);
    void AddElement(Element* child);
    void AddAttribute(Attribute* attribute);
    void ConvertToString(string* out) const;        // convert element to xml style 
                                                    // ie.<Object pos="1,1,1" rot="0,0,0">

private:        
    string m_Name;                          // Tag name
    vector<Attribute*> m_Attributes;        // attributes in the tag (not children)
    vector<Element*> m_Children;
};

#endif