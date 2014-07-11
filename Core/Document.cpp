#include "Document.h"
#include "File.h"
#include "Element.h"
#include "Tag.h"

//--------------------------------------------------------------------------------------
// Name: 
// Desc: 
//--------------------------------------------------------------------------------------
Document::Document() : m_Root(0)
{
    m_Root = new Element( "ROOT" );
}
//--------------------------------------------------------------------------------------
// Name: 
// Desc: Create Dummy tag. then put all tags which are in the xmlFile
//--------------------------------------------------------------------------------------
Document::Document(const char* xmlFileName) : m_Root(0)
{
    File file(xmlFileName);
    Tag tag("<ROOT>");                                   // create dummy tag
    const char* begin = file.GetData();         
    const char* end = file.GetData() + file.GetSize();
    m_Root = new Element(&tag, &begin,end);
}

//--------------------------------------------------------------------------------------
// Name: 
// Desc: 
//--------------------------------------------------------------------------------------
Document::~Document()
{
    delete m_Root;
    m_Root = 0;
}

//--------------------------------------------------------------------------------------
// Name: 
// Desc: 
//--------------------------------------------------------------------------------------
const Element* Document::GetRoot() const
{
    return m_Root;
}

Element* Document::GetRoot()
{
    return m_Root;
}

//--------------------------------------------------------------------------------------
// Name: 
// Desc: 
//--------------------------------------------------------------------------------------
void Document::Write(const char* outFileName)
{
    string str;
    m_Root->ConvertToString(&str);
    File::Write(outFileName, str.c_str(), str.size() );
}