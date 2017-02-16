#ifndef CLINKEDSTACK_H_INCLUDED
#define CLINKEDSTACK_H_INCLUDED
#include "CLinkedNode.h"
#include <iostream>
#include <string>
template <typename T>
class CLinkedStack{
public:
        CLinkedStack();
        ~CLinkedStack();
        void MakeEmpty();
        bool IsEmpty();
        void Push(const T& value);
        bool Pop();
        T& GetTop();
        int GetSize();
        void Print();
        void Path(int x,int y);
private:
        CLinkNode<T> *m_TTop;
};

template <typename T>
CLinkedStack<T>::CLinkedStack()//:m_TTop(NULL){
        m_TTop = new CLinkNode<T>();
        m_TTop = NULL;
}

template <typename T>
CLinkedStack<T>::~CLinkedStack(){
        MakeEmpty();
}

template <typename T>
void CLinkedStack<T>::MakeEmpty(){
        CLinkNode<T> *current;
        while(m_TTop != NULL){
                current = m_TTop;
                m_TTop = m_TTop -> m_CNext;
                delete current;
        }
}

template <typename T>
bool CLinkedStack<T>::IsEmpty(){
        return (m_TTop == NULL) ? true : false;
}

template <typename T>
void CLinkedStack<T>::Push(const T& value){
        m_TTop = new CLinkNode<T>(value,m_TTop);
        if(m_TTop == NULL)
                cout << "Error Distribution!" << endl;

        //assert(m_TTop != NULL);
}

template <typename T>
bool CLinkedStack<T>::Pop(){
        if(IsEmpty() == true){
                cout << " Empty" << endl;
                return false;
        }

        CLinkNode<T> *current = m_TTop;

        m_TTop = m_TTop -> m_CNext;
        delete current;
        current = NULL;

        return true;
}

template <typename T>
T& CLinkedStack<T>::GetTop(){
        return m_TTop->m_TData;
}

template <typename T>
int CLinkedStack<T>::GetSize(){
        CLinkNode<T> *current = m_TTop;
        int i = 0;
        while(current != NULL){
                ++i;
                current = current -> m_TNext;
        }
        return i;
}

#endif // CLINKEDSTACK_H_INCLUDED
