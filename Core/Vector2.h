#ifndef __VECTOR2_H__
#define __VECTOR2_H__

class Vector2{
public:
	Vector2();
	Vector2( int x, int y );
	Vector2( double x, double y );
	Vector2( const Vector2& );

	void operator+=( const Vector2& );
	void operator-=( const Vector2& );
	void operator=( const Vector2& );
	void setAdd( const Vector2&, const Vector2& );
	void setSub( const Vector2&, const Vector2& );
	//( this = a + u*ab + v*ac )
	void setInterporation( 
		const Vector2& a, 
		const Vector2& ab, 
		const Vector2& ac, 
		double u, 
		double v );

	double x;
	double y;
};

#endif
