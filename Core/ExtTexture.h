/*
    Name: Ext Texture
    Date: 2014.07.02
    Desc: Extended Texture class
        : (EN) GameLib::Texture Wrapping class  
        : (KR) GameLib::Texture ���� Ŭ������ XML ��ũ��Ʈ���� ã�� ����� ���� �̸��� �߰��Ǿ��ִ�.

*/
#ifndef __SPARK_EXTTEXTURE_H__
#define __SPARK_EXTTEXTURE_H__

#include <string>
using namespace std;

namespace GameLib { 
    class Texture;
}
class Element;

//--------------------------------------------------------------------------------------
// Desc: 
//--------------------------------------------------------------------------------------
class ExtTexture {
public:
	ExtTexture(const Element* e);
	virtual ~ExtTexture();
   
	void Set() const;                       // set texture before draw primitive
	const string* GetName() const;
    const GameLib::Texture* GetTexture() const;

private:
    string m_Name;
	GameLib::Texture* m_Texture;
};

#endif
