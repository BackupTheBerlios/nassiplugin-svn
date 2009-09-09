#include "NassiFileContent.h"
#include "bricks.h"

NassiFileContent::NassiFileContent():
m_firstbrick(NULL)
{
}
NassiFileContent::~NassiFileContent(void)
{
    if ( m_firstbrick ) delete m_firstbrick;
}

wxOutputStream& NassiFileContent::SaveObject(wxOutputStream& stream)
{
    if ( m_firstbrick ) m_firstbrick->Serialize(stream);
    return stream;
}
wxInputStream& NassiFileContent::LoadObject(wxInputStream& stream)
{
    if ( m_firstbrick ) delete m_firstbrick;

    m_firstbrick = NassiBrick::SetData(stream);

    return stream;
}

wxString NassiFileContent::GetWildcard()
{
    return _T("Nassi Shneiderman diagram, (*.nsd)|*.nsd");
}

NassiBrick *NassiFileContent::GetFirstBrick(void)
{
    return m_firstbrick;
}
NassiBrick *NassiFileContent::SetFirstBrick(NassiBrick *brick)
{
    NassiBrick *tmp = m_firstbrick;
    m_firstbrick = brick;
    if ( m_firstbrick )
    {
        m_firstbrick->SetParent((NassiBrick *)NULL);
        m_firstbrick->SetPrevious((NassiBrick *)NULL);
    }
    return tmp;
}

