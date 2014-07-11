#ifndef __INDEXBUFFER_H__
#define __INDEXBUFFER_H__

#include <string>
using namespace std;

class Element;

class IndexBuffer {
public:
    IndexBuffer(int size);
    IndexBuffer(Element* e);
    virtual ~IndexBuffer();

    unsigned int Index(int i) const;
    void SetIndex(int i, unsigned int value);
    int Size() const;
    const string* GetName() const;

private:
    string m_Name;
    unsigned int* m_Indices;
    int m_Size;                     // size of m_Indicies
};

#endif