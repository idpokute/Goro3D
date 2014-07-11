#include "GraphicData.h"
#include "Document.h"
#include "Element.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "ExtTexture.h"
#include "Batch.h"
#include "GameLib/GameLib.h"
#include "GameLib/Framework.h"
#include "Model.h"

//--------------------------------------------------------------------------------------
// Name: Constructor
// Desc: load xml file
//     : (KR) 스크립트를 한번 훓어서 로드할 리소스 갯수를 샌 후에, 메모리할당 후에 로드한다.
//     :      이후 로드된 리소스로 배치 파일을 만든다.
//--------------------------------------------------------------------------------------
GraphicData::GraphicData(const char* filename) : m_cntBatches(0), m_cntIndexBuffers(0), m_cntVertexBufferes(0), m_cntTextures(0)
{        
    Document doc(filename);                 // constructor of Document makes dummy tag then load xml files. Loaded tags are children.
    Element* root = doc.GetRoot();
    unsigned int n = root->ChildCount();

    // Get size of the buffers to alloc memory
    for( unsigned int i=0; i<n; ++i ) {
        Element* e = root->GetChild(i);        
        const string* name = e->GetName();
        if( *name == "VertexBuffer" )       m_cntVertexBufferes++;
        else if( *name == "IndexBuffer" )   m_cntIndexBuffers++;
        else if( *name == "Batch" )         m_cntBatches++;
        else if( *name == "Texture" )       m_cntTextures++;
    }
    m_Batches       = new Batch* [m_cntBatches];
    m_VertexBuffers = new VertexBuffer* [m_cntVertexBufferes];
    m_IndexBuffers  = new IndexBuffer* [m_cntIndexBuffers];
    m_Textures      = new ExtTexture* [m_cntTextures];

    unsigned int nVB = 0;
    unsigned int nIB = 0;
    unsigned int nTX = 0;
    unsigned int nBT = 0;

    // Load all Resource data
    for( unsigned int i=0; i<n; ++i ) {
        Element* e = root->GetChild(i);

        // Get size of the buffers to alloc memory
        const string* name = e->GetName();
        if( *name == "VertexBuffer" ) {
            m_VertexBuffers[nVB] = new VertexBuffer(e);
            nVB++;
        }
        else if( *name == "IndexBuffer" ) {
            m_IndexBuffers[nIB] = new IndexBuffer(e);
            nIB++;
        }
        else if( *name == "Texture" ) {
            m_Textures[nTX] = new ExtTexture(e);
            nTX++;
        }
    }
    // Load Batch using resource data
    for( unsigned int i=0; i<n; ++i ) {
        Element* e = root->GetChild(i);

        // Get size of the buffers to alloc memory
        const string* name = e->GetName();
        if( *name == "Batch" ) {
            m_Batches[nBT] = new Batch(e, *this);
            nBT++;
        }
    }
}
//--------------------------------------------------------------------------------------
// Name: 
// Desc: 
//--------------------------------------------------------------------------------------
GraphicData::~GraphicData()
{     
    if( m_Batches ) {
        for( int i=0; i<m_cntBatches; i++) 
            SAFE_DELETE( m_Batches[i] );
        SAFE_DELETE_ARRAY( m_Batches );
    }
    if( m_Textures ) {
        for( int i=0; i<m_cntTextures; i++) 
            SAFE_DELETE( m_Textures[i] );
        SAFE_DELETE_ARRAY( m_Textures );
    }
    if( m_VertexBuffers ) {
        for( int i=0; i<m_cntVertexBufferes; i++) 
            SAFE_DELETE( m_VertexBuffers[i] );
        SAFE_DELETE_ARRAY( m_VertexBuffers );
    }
    if( m_IndexBuffers ) {
        for( int i=0; i<m_cntIndexBuffers; i++) 
            SAFE_DELETE( m_IndexBuffers[i] );
        SAFE_DELETE_ARRAY( m_IndexBuffers );
    }
}

//--------------------------------------------------------------------------------------
// Name: GetVertexBuffer
// Desc: 
//--------------------------------------------------------------------------------------
const VertexBuffer* GraphicData::GetVertexBuffer(const char* name) const
{
    for(int i=0; i<m_cntVertexBufferes; ++i) {
        if( *m_VertexBuffers[i]->GetName() == name )
            return m_VertexBuffers[i];
    }
    return 0;
}

//--------------------------------------------------------------------------------------
// Name: GetIndexBuffer
// Desc: 
//--------------------------------------------------------------------------------------
const IndexBuffer* GraphicData::GetIndexBuffer(const char* name) const
{
    for(int i=0; i<m_cntIndexBuffers; ++i) {
        if( *m_IndexBuffers[i]->GetName() == name )
            return m_IndexBuffers[i];
    }
    return 0;
}
//--------------------------------------------------------------------------------------
// Name: 
// Desc: 
//--------------------------------------------------------------------------------------
const ExtTexture* GraphicData::GetTexture(const char* name) const
{
    for(int i=0; i<m_cntTextures; ++i) {
        if( *m_Textures[i]->GetName() == name )
            return m_Textures[i];
    }
    return 0;
}
//--------------------------------------------------------------------------------------
// Name: GetBatch
// Desc: 
//--------------------------------------------------------------------------------------
const Batch* GraphicData::GetBatch(const char* name) const
{
    for(int i=0; i<m_cntBatches; ++i) {
        if( *m_Batches[i]->GetName() == name )
            return m_Batches[i];
    }
    return 0;
}

//--------------------------------------------------------------------------------------
// Name: GetBatch
// Desc: 
//--------------------------------------------------------------------------------------
Model* GraphicData::CreateModel(const char* batchName) const
{
    const Batch* b = 0;
    b = GetBatch(batchName);
    if( b ) {
        Model* model = new Model( b );    
        return model;
    }
    return 0;
}