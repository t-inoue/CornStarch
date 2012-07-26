//
//  Thread.h
//  testtest
//
//  Created by  on 12/07/17.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#ifndef _Thread_h
#define _Thread_h
#include "../../../../header.hpp"

namespace CornStarch
{
// スレッドを実行するためのクラス
class Thread: public wxThread
{

private:

	// スレッドを実行するための基本クラス
	class ThreadDataBase
	{
	protected:
		// スレッド終了時にインスタンスを削除するか
		bool m_isDeleteInstance;
	public:
		ThreadDataBase() :
				m_isDeleteInstance(false)
		{
		}
		void setDeleteInstance(bool value)
		{
			m_isDeleteInstance = value;
		}
		virtual ~ThreadDataBase()
		{
		}
		// スレッドを開始します。
		virtual void startThread() = 0;
	};
	/*
	 * スレッドで実行するインスタンスとメソッドを保持するクラス
	 */
	template<typename T>
	class ThreadData: public ThreadDataBase
	{
	public:
		ThreadData() :
				instance(NULL), method(NULL)
		{
		}
		virtual ~ThreadData()
		{
			free(method);
		}
		//　メソッドを実行するインスタンスです。
		void* instance;
		// 実行するメソッドです。
		void* method;

		//override スレッドを開始します。
		void startThread()
		{
			typedef void (T::*method_t)(void);

			method_t method_ = *(method_t*) method;
			T *instance_ = (T*) instance;
			(instance_->*method_)();
			//
			if (m_isDeleteInstance){
				delete instance_;
			}
		}
	};

	// Thread実行のための要素です。
	ThreadDataBase* threadData;

public:

	// スレッドを開始します。
	void start()
	{
		this->Create();
		this->Run();
	}
	// wxThreadのエントリポイントです。
	wxThread::ExitCode Entry(void)
	{
		threadData->startThread();
		delete threadData;
		if (TestDestroy()){
			return (wxThread::ExitCode) -1;
		}
		return (wxThread::ExitCode) 0;
	}

	// インスタンスとメソッドを指定する
	template<typename T>
	Thread(T *obje, void (T::*method)(void), bool isDeleteInstance = false)
	{
		ThreadData<T> *data = new ThreadData<T>();
		data->instance = (void*) obje;
		data->setDeleteInstance(isDeleteInstance);
		typedef void (T::*method_t)(void);
		// void*はdeleteができないのでmalloc、freeをする
		int size = sizeof(method_t);
		data->method = malloc(size);
		*(method_t*) data->method = method;

		threadData = data;
	}
	virtual ~Thread()
	{
	}
};
}

#endif
