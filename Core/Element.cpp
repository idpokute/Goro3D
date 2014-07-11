#include "Element.h"
#include "Attribute.h"
#include "Tag.h"

//--------------------------------------------------------------------------------------
// Name: Constructor
// Desc: 
//     : (KR) 
//--------------------------------------------------------------------------------------
Element::Element(const char* name) : m_Name(name)
{

}

//--------------------------------------------------------------------------------------
// Name: Constructor
// Desc: Constructor cannot return value, so use pointer of cursor to move cursor
//     : (KR) beginTag를 입력받아서 같은 이름의 endTag가 나오기전까지 스캔한다.
//--------------------------------------------------------------------------------------
Element::Element(Tag* beginTag, const char** pos, const char* end)
{
    m_Name = *(beginTag->GetName());                // set the name of element from tag
    m_Attributes = *(beginTag->GetAttributes());    // get attributes from tag, then copy it.    
                                                    // (KR) 태그의 GetAttribute는 벡터의 주소를 반환한다. 백터 안에는 attribute* 가 있다.
                                                    // 주소값을 받아들이는 변수라면(vector<Attribute*>*)
                                                    // 전달되는 beginTag의 원본이 사라지면 m_Attribute가 가리키는 벡터가 없어지게된다.
                                                    // 위의 이유로 m_Attributes는 vector<Attribute*> 형이다.
    // Process tags after the beginTag
    while( *pos < end ) {
        if( **pos == '<' ) {
            ++(*pos);
            Tag tag(pos, end);                      // Read single tag
            Tag::Type type = tag.GetType();

            // When this has child element, element add the child. Recursoin                                                                
            // (KR) 재귀함수 처리로 안으로 파고든 후에 한거풀씩 밖으로 나온다.
            if( type == Tag::TYPE_BEGIN )
                AddElement( new Element(&tag, pos, end) );      
            else if( type == Tag::TYPE_END ) 
                break;            
        }
        else {
            ++(*pos);
        }
    }
}
//--------------------------------------------------------------------------------------
// Name: Destructor
// Desc: delete all of children elements and attributes.
//--------------------------------------------------------------------------------------
Element::~Element()
{
    for( unsigned int i=0; i<m_Attributes.size(); i++) {
        delete m_Attributes[i];
        m_Attributes[i] = 0;
    }
    m_Attributes.clear();

    for( unsigned int i=0; i<m_Children.size(); i++) {
        delete m_Children[i];
        m_Children[i] = 0;
    }
    m_Children.clear();
}

//--------------------------------------------------------------------------------------
// Name: AddElement
// Desc: put an element into child vector
//--------------------------------------------------------------------------------------
void Element::AddElement(Element* child)
{
    m_Children.push_back(child);
}

//--------------------------------------------------------------------------------------
// Name: AddAttribute
// Desc: put an attribute
//--------------------------------------------------------------------------------------
void Element::AddAttribute(Attribute* attribute)
{
    m_Attributes.push_back(attribute);
}

//--------------------------------------------------------------------------------------
// Name: GetName
// Desc: return pointer of the string
//--------------------------------------------------------------------------------------
const string* Element::GetName() const
{
    return &m_Name;
}

//--------------------------------------------------------------------------------------
// Name: GetAttribute
// Desc: return pointer of the attribute[i]
//--------------------------------------------------------------------------------------
const Attribute* Element::GetAttribute(int i) const
{
    return m_Attributes[i];
}

//--------------------------------------------------------------------------------------
// Name: AttributeCount
// Desc: (EN) return the number of attribute in the current tag
//     : (KR) 현재 태그의 어티리뷰트의 수를 반환한다.
//--------------------------------------------------------------------------------------
const unsigned int Element::AttributeCount() const
{
    return m_Attributes.size();
}

//--------------------------------------------------------------------------------------
// Name: GetChild
// Desc: return the pointer of child[i] element
//--------------------------------------------------------------------------------------
const Element* Element::GetChild(int i) const
{
    return m_Children[i];
}
Element* Element::GetChild(int i)
{
    return m_Children[i];
}

//--------------------------------------------------------------------------------------
// Name: ChildCount
// Desc: return the number of children elements
//--------------------------------------------------------------------------------------
const unsigned int Element::ChildCount() const
{
    return m_Children.size();
}

//--------------------------------------------------------------------------------------
// Name: ChildCount
// Desc: return the number of children elements
//--------------------------------------------------------------------------------------
void Element::ConvertToString(string* out) const
{
    *out += '<';
    *out += m_Name;
    for( unsigned int i=0; i<m_Attributes.size(); i++ ) {
        *out += ' ';
        *out += *m_Attributes[i]->GetName();
        *out += '=';
        *out += '"';
        *out += *m_Attributes[i]->GetValue();
        *out += '"';
    }
    *out += '>';

    for( unsigned int i=0; i<m_Children.size(); i++) {
        m_Children[i]->ConvertToString(out);
    }

    *out += "</";
    *out += m_Name;
    *out += ">";
}