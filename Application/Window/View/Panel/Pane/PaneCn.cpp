#include "PaneCn.hpp"

using namespace std;

namespace CornStarch
{
;

CPaneCn::CPaneCn(void)
{
}

CPaneCn::~CPaneCn(void)
{
}

//////////////////////////////////////////////////////////////////////

// 初期化を行う
void CPaneCn::init(wxWindow* parent)
{
    // スクロールバー(水平、垂直を必要に応じて)、ソート
    Create(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize,
            wxTR_HIDE_ROOT | wxTR_NO_BUTTONS);

    // Rootノードを追加
    AddRoot("Root");
}

// 選択済み項目を決める
void CPaneCn::setStringSelection(const wxString& channel)
{
    // SetStringSelection(channel);
}

// 所属チャンネル一覧を表示
void CPaneCn::displayChannels(const map<int, CChatServiceBase*>& connections)
{
    // 項目を削除
    wxTreeItemId rootId = GetRootItem();
    DeleteChildren(rootId);

    // 各サーバについてループ
    map<int, CChatServiceBase*>::const_iterator it;
    for (it = connections.begin(); it != connections.end(); it++){

        // サーバ情報をセット
        CTreeServerItem* data = new CTreeServerItem();
        data->setServerId((*it).second->getId());

        // サーバ名をセット

        wxString name(
                wxString::Format(wxT("%s[%s]"), (*it).second->getName(),
                        (*it).second->getHost()));
        wxTreeItemId id = AppendItem(rootId, name, -1, -1, data);
        if ((*it).second->IsConnected() == false){
            this->SetItemTextColour(id, *wxLIGHT_GREY);
        }
        // 各チャンネルについてループ
        vector<CChannelStatus*>::const_iterator cit;
        vector<CChannelStatus*> channels = (*it).second->getChannels();
        for (cit = channels.begin(); cit != channels.end(); cit++){

            // チャンネルをセット
            wxTreeItemId childId = AppendItem(id, (*cit)->getChannelName());
            if ((*it).second->IsConnected() == false){
                this->SetItemTextColour(childId, *wxLIGHT_GREY);
            }
        }

        Expand(id);
    }
}

//////////////////////////////////////////////////////////////////////

// チャンネルが選択された際のイベント処理
void CPaneCn::onChannelSelected(wxTreeEvent& event)
{
    wxTreeItemId id = event.GetItem();
    CChannelSelectEvent* chEvent = newSelectEvent(id);

    if (chEvent == NULL){
        return;
    }

    // イベント送信
    chEvent->SetEventType(myEVT_SELECT_TREE_NODE); // イベントタイプ
    wxQueueEvent(GetParent()->GetParent()->GetParent()->GetEventHandler(),
            chEvent);
}

// 項目が右クリックされた際のイベント処理
void CPaneCn::onItemRightClicked(wxTreeEvent& event)
{
    SelectItem(event.GetItem());
    wxTreeItemId id = event.GetItem();
    CChannelSelectEvent* chEvent = newSelectEvent(id);

    if (chEvent == NULL){
        return;
    }

    // イベント送信
    chEvent->SetEventType(myEVT_SELECT_TREE_NODE_RIGHT); // イベントタイプ
    wxQueueEvent(GetParent()->GetParent()->GetParent()->GetEventHandler(),
            chEvent);
}

// チャンネルを選択したというイベントを返す
CChannelSelectEvent* CPaneCn::newSelectEvent(const wxTreeItemId& id)
{
    // 自分と親のツリーIDを取得
    wxTreeItemId parentId = GetItemParent(id);

    //　背景を白に戻す。
    this->SetItemBackgroundColour(id, *wxWHITE);
    // アイテム名の取得
    wxString itemName = GetItemText(id);

    // Mac番で、ルートノードが選択されるケースがある
    if (parentId == NULL){
        return NULL;
    }

    // コントローラへ投げるイベントを作成
    CChannelSelectEvent* chEvent = new CChannelSelectEvent();

    // 選択されたのがチャンネルなら
    if (parentId != GetRootItem()){

        // イベントの初期化
        int serverId =
                ((CTreeServerItem*) GetItemData(parentId))->getServerId();
        chEvent->setServerOrNot(false);
        chEvent->setServerId(serverId);
        chEvent->setServer(GetItemText(parentId));

    } else{

        // 選択されたのがサーバなら
        int serverId = ((CTreeServerItem*) GetItemData(id))->getServerId();
        chEvent->setServerId(serverId);

        // イベントの初期化
        chEvent->setServerOrNot(true);
    }

    // イベントを返す
    chEvent->setChannelName(itemName);
    return chEvent;
}

// アクティベートされた
void CPaneCn::onActivated(wxTreeEvent& event)
{
    return;
}
// Messageが追加された時に呼ばれます。
void CPaneCn::addUnreadMessage(const CMessageData* message)
{
    wxTreeItemIdValue cookie;
    wxTreeItemId root = GetRootItem();
    wxTreeItemId server = GetFirstChild(root, cookie);
    ;
    while (server.IsOk()) // サーバーノードを探索
    {
        if (((CTreeServerItem*) GetItemData(server))->getServerId()
                == message->m_serviceId){
            wxTreeItemId channel = this->GetFirstChild(server, cookie);
            while (channel.IsOk()) // チャンネルノードを探索
            {
                if (GetItemText(channel) == message->m_channel){
                    //　背景を色を返る。
                    this->SetItemBackgroundColour(channel, *wxLIGHT_GREY);
                    return;
                }
                channel = this->GetNextSibling(channel);
            }
        }
        server = this->GetNextSibling(server);
    }
}
}
