#include "GameLib/GameLib.h"
#include "Vector2.h"
#include "Vector3.h"
#include "VertexBuffer.h"
#include "Element.h"
#include "Attribute.h"

VertexBuffer::VertexBuffer(int size) : m_Size(size), m_Positions(0), m_UVs(0)
{
    m_Positions = new Vector3 [size];
    m_UVs = new Vector2 [size];
}

VertexBuffer::VertexBuffer(Element* e) : m_Size(0), m_Positions(0), m_UVs(0)
{
    m_Size = e->ChildCount();

    // Load Vertex Data
    if( m_Size > 0 ) {
        m_Positions = new Vector3 [m_Size];
        m_UVs = new Vector2 [m_Size];

        for( int i=0; i<m_Size; i++) {
            Element* child = e->GetChild(i);
            int numAttribute = child->AttributeCount();

            for( int j=0; j<numAttribute; j++ ) {
                const Attribute* attribute = child->GetAttribute(j);
                const string* atName = attribute->GetName();
                if( *atName == "position" )     attribute->GetDoubleValues( &m_Positions[i].x, 3 );
                else if( *atName == "uv" )      attribute->GetDoubleValues( &m_UVs[i].x, 2 );
            }                
        }
    }
    // Load Vertex Buffer Name
    if( e->AttributeCount() > 0 ) {
        for( unsigned int i=0; i<e->AttributeCount(); i++ ) {                    
            const Attribute* at = e->GetAttribute(i);
            if( *at->GetName() == "name" )
                m_Name = *at->GetValue();
        }
    }
}

VertexBuffer::~VertexBuffer()
{
    SAFE_DELETE_ARRAY(m_Positions);
    SAFE_DELETE_ARRAY(m_UVs);
}

const Vector3* VertexBuffer::Position(int i) const
{
    ASSERT( i>=0 && i<m_Size );
    return &m_Positions[i];
}

const Vector2* VertexBuffer::UV(int i) const
{
    ASSERT( i>=0 && i<m_Size );
    return &m_UVs[i];
}

void VertexBuffer::SetPosition(int i, const Vector3& p)
{
    ASSERT( i>=0 && i<m_Size );
    m_Positions[i] = p;
}

void VertexBuffer::SetUV(int i, const Vector2& uv)
{
    ASSERT( i>=0 && i<m_Size );
    m_UVs[i] = uv;
}

int VertexBuffer::Size() const
{
    return m_Size;
}

const string* VertexBuffer::GetName() const
{
    return &m_Name;
}