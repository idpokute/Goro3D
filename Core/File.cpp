#include "GameLib/GameLib.h"
#include "File.h"
#include <fstream>
using namespace std;

File::File( const char* filename ) : m_Size( 0 ), m_Data( 0 )
{
	ifstream in( filename, ifstream::binary );
	if(in) {
		in.seekg( 0, ifstream::end );
		m_Size = static_cast< int >( in.tellg() );      // get file size
		in.seekg( 0, ifstream::beg );                   // move cursor at the beginning of the file
		m_Data = new char[ m_Size ];
		in.read( m_Data, m_Size );
	}
    else{
		HALT( "can't open file." );
	}
}

File::~File()
{
    delete [] m_Data;
    m_Data = 0;
}

int File::GetSize() const 
{
	return m_Size;
}

const char* File::GetData() const 
{
	return m_Data;
}

unsigned File::GetUnsignedInt( int pos ) const 
{
	const unsigned char* up;
	up = reinterpret_cast< const unsigned char* >( m_Data );

	unsigned int r = up[ pos ];
	r |= up[ pos + 1 ] << 8;
	r |= up[ pos + 2 ] << 16;
	r |= up[ pos + 3 ] << 24;
	return r;
}

void File::Write( const char* filename, const char* data, int size ){
	ofstream out( filename, ofstream::binary );
	if ( out ){
		out.write( data, size );
	}else{
		HALT( "can't open file." );
	}
}
