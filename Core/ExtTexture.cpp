#include "ExtTexture.h"
#include "GameLib/Framework.h"
#include "Element.h"
#include "Attribute.h"

//--------------------------------------------------------------------------------------
// Name: Constructor
// Desc: If attribute name is texture, load the texture. Path of the texture is in the attribute value.
//--------------------------------------------------------------------------------------
ExtTexture::ExtTexture( const Element* e ) : m_Texture( 0 ) 
{  
	for( unsigned int i=0; i<e->AttributeCount(); ++i ) {
        const Attribute* a = e->GetAttribute( i );
		const string* name = a->GetName();
        
        // Path of the file
		if( *name == "filename" )                  
            GameLib::Framework::instance().createTexture( &m_Texture, a->GetValue()->c_str() );
		else if( *name == "name" ) 
            m_Name = *a->GetValue();
	}
}

//--------------------------------------------------------------------------------------
// Name: Destructor
// Desc: 
//--------------------------------------------------------------------------------------
ExtTexture::~ExtTexture()
{
	GameLib::Framework::instance().destroyTexture( &m_Texture );
}

//--------------------------------------------------------------------------------------
// Name: Set
// Desc: Set texture before draw 3d primitive
//--------------------------------------------------------------------------------------
void ExtTexture::Set() const 
{
	GameLib::Framework::instance().setTexture( m_Texture );
}

//--------------------------------------------------------------------------------------
// Name: GetName
// Desc: return pointer of the name
//--------------------------------------------------------------------------------------
const string* ExtTexture::GetName() const 
{
	return &m_Name;
}

//--------------------------------------------------------------------------------------
// Name: GetName
// Desc: return pointer of the name
//--------------------------------------------------------------------------------------
const GameLib::Texture* ExtTexture::GetTexture() const
{
    return m_Texture;
}
