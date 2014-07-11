#include "IndexBuffer.h"
#include "GameLib\GameLib.h"
#include "Element.h"
#include "Attribute.h"

IndexBuffer::IndexBuffer(int size) : m_Size(size), m_Indices(0), m_Name(0)
{
    m_Indices = new unsigned int [size];
}

IndexBuffer::IndexBuffer(Element* e) : m_Size(0), m_Indices(0)
{
    int triangleNum = e->ChildCount();
    m_Size = e->ChildCount() * 3;

    // Load Vertex Data
    if( triangleNum > 0 ) {
        m_Indices = new unsigned int [m_Size];

        for( int i=0; i<triangleNum; i++) {
            Element* child = e->GetChild(i);
            int numAttribute = child->AttributeCount();

            for( int j=0; j<numAttribute; j++ ) {
                const Attribute* attribute = child->GetAttribute(j);
                const string* atName = attribute->GetName();
                
                if( *atName == "indices" ) {                                    
                    int tmp[3];
                    attribute->GetIntValues( tmp, 3 );
                    
                    m_Indices[i * 3 + 0] = tmp[0];
                    m_Indices[i * 3 + 1] = tmp[1];
                    m_Indices[i * 3 + 2] = tmp[2];
                }                
            }                
        }
    }
    // Load Index Buffer Name
    if( e->AttributeCount() > 0 ) {
        for( unsigned int i=0; i<e->AttributeCount(); i++ ) {                    
            const Attribute* at = e->GetAttribute(i);
            if( *at->GetName() == "name" )
                m_Name = *at->GetValue();
        }
    }
}

IndexBuffer::~IndexBuffer()
{
    SAFE_DELETE_ARRAY(m_Indices);
}

unsigned int IndexBuffer::Index(int i) const
{
    ASSERT( i>=0 && i<m_Size );
    return m_Indices[i];
}

void IndexBuffer::SetIndex(int i, unsigned int value)
{
    ASSERT( i>=0 && i<m_Size );
    m_Indices[i] = value;
}

int IndexBuffer::Size() const
{
    return m_Size;
}

const string* IndexBuffer::GetName() const
{
    return &m_Name;
}