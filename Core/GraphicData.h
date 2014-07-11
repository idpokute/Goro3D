/*
    Name: GraphicData
    Date: 2014.07.02
    Desc: GraphicData class
        : (EN) Resource Manager Class, this class using Document class which means the class use xml.
        : (KR) 리소스 매니저 클래스, Document class를 이용하여 Batch,Index&Vertex buffer, ExtTexture클래스를 채운다.
*/
#ifndef __SPARK_GRAPHICDATA_H__
#define __SPARK_GRAPHICDATA_H__

class Batch;
class IndexBuffer;
class VertexBuffer;
class ExtTexture;
class Model;

//--------------------------------------------------------------------------------------
// Desc: 
//--------------------------------------------------------------------------------------
class GraphicData {
public:
    GraphicData(const char* filename);            
    virtual ~GraphicData();

    const VertexBuffer* GetVertexBuffer(const char* name) const;
    const IndexBuffer* GetIndexBuffer(const char* name) const;
    const ExtTexture* GetTexture(const char* name) const;
    const Batch* GetBatch(const char* name) const;
    
    Model* CreateModel(const char* batchName) const;

private:
    Batch** m_Batches;
    VertexBuffer** m_VertexBuffers;
    IndexBuffer** m_IndexBuffers;
    ExtTexture** m_Textures;

    int m_cntBatches;
    int m_cntVertexBufferes;
    int m_cntIndexBuffers;
    int m_cntTextures;    
};

#endif