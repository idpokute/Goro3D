/*
    Name: Document
    Date: 2014.07.02
    Desc: XML Tag class
*/
#ifndef __SPARK_DOCUMENT_H__
#define __SPARK_DOCUMENT_H__

#include <vector>
#include <string>
#include "Attribute.h"
using namespace std;

class Element;

//-------------------------------------------------------------------------------
// Name: Document
// Desc: load XML file
//-------------------------------------------------------------------------------
class Document {
public: 
    Document();
    Document(const char* xmlFileName);          // Load XML file
    ~Document();

    const Element* GetRoot() const;             // Return root element
    Element* GetRoot();   
    void Write(const char* outFileName);
private:
    Element* m_Root;
};

#endif