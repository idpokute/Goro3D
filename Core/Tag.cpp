#include "Tag.h"
#include "Attribute.h"

//--------------------------------------------------------------------------------------
// Name: 
// Desc: 
//-------------------------------------------------------------------------------------
static bool isNormalChar(char c)
{
    if((c >= '0' && c <= '9') || (c >= 'A' && c <='Z') || (c >= 'a' && c <= 'z') || (c=='_'))
        return true;
    return false;
}

//--------------------------------------------------------------------------------------
// Name: constuctor
// Desc: 
//--------------------------------------------------------------------------------------
Tag::Tag(const char* name) : m_Name(name), m_Type(TYPE_BEGIN)
{
    m_Attributes.clear();
}

//--------------------------------------------------------------------------------------
// Name: constuctor
// Desc: 
//--------------------------------------------------------------------------------------
Tag::Tag(const char** readPointer, const char* end) : m_Type(TYPE_BEGIN)
{
    m_Attributes.clear();

    // temp value to save attribute
    string name;
    string value;

    int state=0;                            // state
    bool done = false;                      // to break while loop
    while( *readPointer < end ) {
        char c = **readPointer;             // save the char value
        ++(*readPointer);                   // move cursor to the next

        switch(state) {
        // initial state
        case 0:        
            // read the first charactor
            switch(c) {
            case '/':   m_Type = TYPE_END;  break;
            default:    
                m_Name += c;    // add first char of Element name to m_Name
                state = 1;  
                break;
            }
            break;
        case 1:
            if(c == '>')                done = true;
            else if(isNormalChar(c))    m_Name += c;          
            else                        state = 2;          // it means whitespace, ',', '"', or invalid char
            break;
        // char after Element name
        case 2:
            if(c == '>')                
                done = true;
            else if(isNormalChar(c)) {
                name += c;                                  // it's attribute's name.
                state = 3;
            }
            break;
        case 3:
            switch(c) {
            case '=':   state = 4;  break;
            default:    name+=c;    break;                  // 현재는 = 앞의 공백도 문자로 인식한다.
            }
            break;
        case 4:
            switch(c) {
            case '"':   state = 5;  break;                  // value값은 항상 "안에 있다.
            default:                break;
            }
            break;
        case 5:
            switch(c) {
            case '"':
                state = 2;
                m_Attributes.push_back( (new Attribute(name.c_str(), value.c_str())) );                
                name.clear();
                value.clear();
                break;
            default:
                value += c;                                 // 현재는 공백도 문자로 인식한다.
                break;
            }
            break;
        }
        if(done)
            break;
    }
}
//--------------------------------------------------------------------------------------
// Name: Destructor
// Desc: Each attributes in m_Attributes are delete in the Element class
//     : 생성된 어트리뷰트는 엘리먼트로 전달되어 처리된다.
//-------------------------------------------------------------------------------------
Tag::~Tag()
{    
}

//--------------------------------------------------------------------------------------
// Name: 
// Desc: 
//-------------------------------------------------------------------------------------
const string* Tag::GetName() const
{
    return &m_Name;
}
//--------------------------------------------------------------------------------------
// Name: 
// Desc: 
//-------------------------------------------------------------------------------------
const Tag::Type Tag::GetType() const
{
    return m_Type;
}
//--------------------------------------------------------------------------------------
// Name: 
// Desc: 
//-------------------------------------------------------------------------------------
const vector<Attribute*>* Tag::GetAttributes() const
{
    return &m_Attributes;
}
