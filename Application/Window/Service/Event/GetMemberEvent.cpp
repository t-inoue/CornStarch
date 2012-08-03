#include "GetMemberEvent.hpp"

using namespace std;

namespace CornStarch
{
;

CGetMemberEvent::CGetMemberEvent(void)
{
}

CGetMemberEvent::~CGetMemberEvent(void)
{
    int size = (int) (m_members.size());
    for (int i = 0; i < size; i++){
        delete m_members[i];
    }
}
wxString CGetMemberEvent::getChannel() const
{
    return m_channel;
}

void CGetMemberEvent::setChannel(wxString channel)
{
    m_channel = channel;
}
void CGetMemberEvent::setMembers(const vector<CMemberData*>& members)
{
    m_members = members;
}

vector<CMemberData*> CGetMemberEvent::getMembers(void) const
{
    return m_members;
}

}

