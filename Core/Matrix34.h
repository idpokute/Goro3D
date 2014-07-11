#ifndef INCLUDED_MATRIX34_H
#define INCLUDED_MATRIX34_H

class Vector3;

class Matrix34{
public:
	Matrix34();
	void setTranslation( const Vector3& );
	void setScaling( const Vector3& );
	void setRotationX( double radian );
	void setRotationY( double radian );
	void setRotationZ( double radian );
	void setViewTransform( const Vector3& position, const Vector3& target );
	void multiply( Vector3* out, const Vector3& in ) const;
	void operator*=( const Matrix34& );
	void translate( const Vector3& );
	void scale( const Vector3& );
	void rotateX( double radian );
	void rotateY( double radian );
	void rotateZ( double radian );
private:
	friend class Matrix44; 

	double m00, m01, m02, m03;
	double m10, m11, m12, m13;
	double m20, m21, m22, m23;
};

#endif
