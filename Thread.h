//
//  Thread.h
//  testtest
//
//  Created by  on 12/07/17.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#ifndef _Thread_h
#define _Thread_h
#include "header.hpp"


namespace CornStarch {
    class Thread : public wxThread{
        
    private:
        
        class ThreadDataBase
        {
        public:
            ThreadDataBase(){
            }
            virtual ~ThreadDataBase() {}
            virtual void startThread() = 0;
        };
        /*
         * スレッドで実行するインスタンスとメソッドを保持するクラス
         */
        template<typename T>
        class ThreadData :public ThreadDataBase{
        public:
            ThreadData() :
            instance(NULL), method(NULL){
            }
            virtual ~ThreadData() {
                free(method);
            }
            void* instance;
            void* method;
            
            void startThread()
            {
                typedef void (T::*method_t)(void);
                
                method_t method_ = *(method_t*)method;
                T *instance_ = (T*)instance;
                (instance_->*method_)();
                
            }
        };
 
         ThreadDataBase* threadData;
        
        
    public:
        
        void start(){
            this->Create();
            this->Run();
        }
        wxThread::ExitCode Entry(void)
        {
            threadData->startThread();
            delete threadData;
            if (TestDestroy()){
                return (wxThread::ExitCode)-1;
            }
           return (wxThread::ExitCode)0;
        }
        

        // インスタンスとメソッドを指定する
        template<typename T>
        Thread(T *obje, void (T::*method)(void)) {
            ThreadData<T> *data = new ThreadData<T>();
            data->instance = (void*) obje;
            
            typedef void (T::*method_t)(void);
            // void*はdeleteができないのでmalloc、freeをする
            int size = sizeof(method_t);
            data->method = malloc(size);
            *(method_t*) data->method = method;
            
            threadData = data;
        }
        virtual ~Thread() {
        }
    };
}


#endif
