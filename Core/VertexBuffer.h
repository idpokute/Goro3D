#ifndef __VERTEXBUFFER_H__
#define __VERTEXBUFFER_H__

#include <string>
using namespace std;

class Vector3;
class Vector2;
class Element;

class VertexBuffer {
public:
    VertexBuffer(int size);
    VertexBuffer(Element* e);
    virtual ~VertexBuffer();

    const Vector3* Position(int i) const;
    const Vector2* UV(int i) const;
    void SetPosition(int i, const Vector3& p);
    void SetUV(int i, const Vector2& uv);
    int Size() const;
    const string* GetName() const;

private:
    string m_Name;                          // VertexBuffer name for searching at the database
    int m_Size;
    Vector3* m_Positions;
    Vector2* m_UVs;
};

#endif