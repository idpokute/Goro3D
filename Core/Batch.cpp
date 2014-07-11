#include "Batch.h"
#include "GameLib\Framework.h"
#include "GameLib\GameLib.h"
#include "Matrix44.h"
#include "Vector2.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "Element.h"
#include "Attribute.h"
#include "ExtTexture.h"
#include "GraphicData.h"
#include "VertexBuffer.h"

//--------------------------------------------------------------------------------------
// Name: Constructor
// Desc: 
//-------------------------------------------------------------------------------------
Batch::Batch(Element* e, GraphicData& gdb) : m_BlendMode(GameLib::Framework::BlendMode::BLEND_OPAQUE)
{
    for( unsigned int i=0; i<e->AttributeCount(); i++ ) {
        const Attribute* a = e->GetAttribute(i);
        const string* name = a->GetName();
        const string* value = a->GetValue();

        if( *name == "name" ) 
            m_Name = *value;
        else if( *name == "vertexBuffer" )
            m_VertexBuffer = gdb.GetVertexBuffer( value->c_str() );
        else if( *name == "indexBuffer" )
            m_IndexBuffer = gdb.GetIndexBuffer( value->c_str() );                
        else if( *name == "texture" )
            m_Texture = gdb.GetTexture( value->c_str() );
        else if( *name == "blend" ) {
            if( *value == "opaque" )
                m_BlendMode = GameLib::Framework::BLEND_OPAQUE;            			
            else if ( *value == "additive" )
				m_BlendMode = GameLib::Framework::BLEND_ADDITIVE;
			else if ( *value == "linear" )
				m_BlendMode = GameLib::Framework::BLEND_LINEAR;
        }
    }    
}

Batch::Batch(const VertexBuffer* vertexBuffer, const IndexBuffer* indexBuffer, const ExtTexture* texture, GameLib::Framework::BlendMode blend) :
    m_VertexBuffer(vertexBuffer), m_IndexBuffer(indexBuffer), m_Texture(texture), m_BlendMode(blend)
{

}

//--------------------------------------------------------------------------------------
// Name:
// Desc: 
//-------------------------------------------------------------------------------------
Batch::~Batch()
{
    m_VertexBuffer = 0;
    m_IndexBuffer = 0;
    m_Texture = 0;
}

//--------------------------------------------------------------------------------------
// Name: Draw
// Desc: 
//-------------------------------------------------------------------------------------
void Batch::Draw(const Matrix44& transform ) const
{    
    GameLib::Framework f = GameLib::Framework::instance();
    if( m_Texture )
        m_Texture->Set();
    else
        f.setTexture(0);
    f.setBlendMode(m_BlendMode);
    (m_BlendMode == GameLib::Framework::BlendMode::BLEND_OPAQUE) ? f.enableDepthWrite(true) : f.enableDepthWrite(false);        
    f.enableDepthTest(true); 
    int vertexSize = m_VertexBuffer->Size();

    double* p4 = new double[ vertexSize * 4 ];  // x,y,z,w
	for ( int i = 0;i < vertexSize; i++ )
        transform.multiply( &p4[ i * 4 ], *m_VertexBuffer->Position( i ) );

    int cntTriangle = m_IndexBuffer->Size()/3;
         
    for( int i=0; i<cntTriangle; i++)
    {        
        unsigned int i0 = m_IndexBuffer->Index(i*3+0);
        unsigned int i1 = m_IndexBuffer->Index(i*3+1);
        unsigned int i2 = m_IndexBuffer->Index(i*3+2);

		f.drawTriangle3DH(  &p4[ i0 * 4 ], &p4[ i1 * 4 ], &p4[ i2 * 4 ],
                            &m_VertexBuffer->UV(i0)->x,
                            &m_VertexBuffer->UV(i1)->x,
                            &m_VertexBuffer->UV(i2)->x );            
    }
    SAFE_DELETE_ARRAY(p4);
}

//--------------------------------------------------------------------------------------
// Name:
// Desc: 
//-------------------------------------------------------------------------------------
const string* Batch::GetName() const
{
    return &m_Name;
}