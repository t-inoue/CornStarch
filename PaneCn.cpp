#include "PaneCn.hpp"

using namespace std;

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
        wxTR_DEFAULT_STYLE | wxTR_HIDE_ROOT);

    // Rootノードを追加
    AddRoot("Root");
}

// 選択済み項目を決める
void CPaneCn::setStringSelection(const wxString& channel)
{
	// SetStringSelection(channel);
}

// 所属チャンネル一覧を表示
void CPaneCn::displayChannels(const vector<CChatServiceBase*>& connections)
{
    // 項目を削除
    wxTreeItemId rootId = GetRootItem();
    DeleteChildren(rootId);

    // 各サーバについてループ
    vector<CChatServiceBase*>::const_iterator it;
    for (it = connections.begin(); it != connections.end(); it++){

        // サーバ情報をセット
        CTreeServerItem* data = new CTreeServerItem();
        data->setServerId((*it)->getId());

        // サーバ名をセット
        wxTreeItemId id = AppendItem(rootId, (*it)->getHost(), -1, -1, data); 

        // 各チャンネルについてループ
        vector<wxString>::const_iterator cit;
        vector<wxString> vec = (*it)->getChannels();
        for (cit = vec.begin(); cit != vec.end(); cit++){

            // チャンネルをセット
            AppendItem(id, *cit);
        }
    }
}


//////////////////////////////////////////////////////////////////////


// チャンネルが選択された際のイベント処理
void CPaneCn::onChannelSelected(wxTreeEvent& event)
{
    // 自分と親のツリーIDを取得
    wxTreeItemId id = event.GetItem();
    wxTreeItemId parentId = GetItemParent(id);

    // 親のIDがなければ何もしない
    if(parentId == NULL)
    {
    	return;
    }
    // アイテム名の取得
    wxString itemName = GetItemText(id);

    // コントローラへ投げるイベントを作成
    CChannelSelectEvent* chEvent = new CChannelSelectEvent();

    // 選択されたのがチャンネルなら
    if (parentId != GetRootItem()){

        // イベントの初期化
        int serverId = ((CTreeServerItem*)GetItemData(parentId))->getServerId();
        chEvent->setServerOrNot(false);
        chEvent->setServerId(serverId);
        chEvent->setServer(GetItemText(parentId));

    } else {

        // イベントの初期化
        chEvent->setServerOrNot(true);
    }

    // イベントを送信
    chEvent->setText(itemName);
    chEvent->SetEventType(myEVT_SELECt_TREE_NODE);
    wxQueueEvent(GetParent()->GetParent()->GetParent()->GetEventHandler(), chEvent);
}


