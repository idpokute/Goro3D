/*
    Name: Batch
    Date: 2014.07.02
    Desc: Batch class
        : (EN) Batch class contains Name(for search), VertexBuffer Name, IndexBuffer Name, Texture Name, BlendOption
        : (KR) ����ϱ� ���� ������� ���Ϸ� ��ġ �̸�, ���ؽ�/�ε��� ����,�ؽ�ó �̸��� ����ɼ��� ������ �ִ�.        
*/
#ifndef __SPARK_BATCH_H__
#define __SPARK_BATCH_H__

#include "GameLib\Framework.h"
#include "GraphicData.h"
#include <string>
using namespace std;

class VertexBuffer;
class IndexBuffer;
class Matrix44;
class Element;
class ExtTexture;

namespace GameLib{
    class Texture;
}

//--------------------------------------------------------------------------------------
// Desc: Batch class doesn't have actual data. It has pointers of data.
//--------------------------------------------------------------------------------------
class Batch {    
public:
    Batch(Element* e, GraphicData& gdb);            // Constructor do linking member variables to graphic datas in gdb.
    Batch(const VertexBuffer* vertexBuffer, const IndexBuffer* indexBuffer, 
            const ExtTexture* texture, GameLib::Framework::BlendMode blend);
    virtual ~Batch();

    const string* GetName() const;
    void Draw(const Matrix44& transform ) const;

private:
    string m_Name;      
    const VertexBuffer* m_VertexBuffer;
    const IndexBuffer* m_IndexBuffer;
    const ExtTexture* m_Texture;                    
    GameLib::Framework::BlendMode m_BlendMode;      // Default : Opaque
};

#endif