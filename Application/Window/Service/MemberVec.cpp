﻿#include "MemberVec.hpp"

using namespace std;

namespace CornStarch
{;

CMemberVec::CMemberVec(void) : m_isLoaded(false)
{
}

CMemberVec::~CMemberVec(void)
{
	deleteAllMembers();
}

//////////////////////////////////////////////////////////////////////

// メンバー一覧を登録する
void CMemberVec::setMembers(const vector<CMemberData*>& members)
{
	m_isLoaded = true;
	// そのチャンネルのメンバー一覧を削除する
	deleteAllMembers();

	// 順次メンバーを追加する
	size_t length = members.size();
	for (size_t i = 0; i < length; i++){
		push(*members[i]);
	}
}

// メンバーを受信済みか
bool CMemberVec::hasSetMember(void) const
{
	return m_isLoaded;
}

// メンバー情報を更新する
void CMemberVec::updateStatus(const CMemberData& member)
{
	// 同じ名前の人がいたら更新
	size_t length = size();
	for (size_t i = 0; i < length; i++){
		if ((*this)[i]->m_name == member.m_name){
			*(*this)[i] = member;
			return;
		}
	}
}

// メンバーを追加する
void CMemberVec::push(const CMemberData& member)
{
	CMemberData* data = new CMemberData();
	*data = member;
	push_back(data);
}

// メンバーを削除する
void CMemberVec::pop(const wxString& userName)
{
	vector<CMemberData*>::iterator it;
	for (it = begin(); it != end(); it++){

		// 名前が一致すれば削除
		if ((*it)->m_name == userName){
			delete *it;
			erase(it);
			return;
		}
	}
}

// 全メンバーを削除する
void CMemberVec::deleteAllMembers(void)
{
	size_t length = size();
	for (size_t i = 0; i < length; i++){
		delete (*this)[i];
	}
	clear();
}

}
