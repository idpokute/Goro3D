#ifndef INCLUDED_VECTOR3_H
#define INCLUDED_VECTOR3_H

class Vector3{
public:
	Vector3();
	Vector3( double x, double y, double z );
	Vector3( const Vector3& );
	void set( double x, double y, double z );
	void operator+=( const Vector3& );
	void operator-=( const Vector3& );
	void operator=( const Vector3& );
	void setAdd( const Vector3&, const Vector3& );
	void setSub( const Vector3&, const Vector3& );
	void operator*=( double );
	void setMul( const Vector3&, double );

	double x, y, z;
};

#endif
