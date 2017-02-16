#ifndef CLINKEDQUEUE_H_INCLUDED
#define CLINKEDQUEUE_H_INCLUDED

#include "CLinkedNode.h"
#include <iostream>
using namespace std;

template <typename T>
class CLinkedQueue{
public:
        CLinkedQueue();
        ~CLinkedQueue();
        void Print();
        void MakeEmpty();
        bool IsEmpty();
        bool EnQueue(const T& value);
        bool DeQueue();
        T& GetFront();
        int GetSize();
private:
        CLinkNode<T> *m_CFront;
        CLinkNode<T> *m_CRear;

};

template <typename T>
CLinkedQueue<T>::CLinkedQueue():m_CFront(NULL),m_CRear(NULL){
}

template <typename T>
CLinkedQueue<T>::~CLinkedQueue(){
        MakeEmpty();
}

template <typename T>
void CLinkedQueue<T>::Print(){
        CLinkNode<T> *current = m_CFront;
        while(current != NULL){
                cout << current -> m_TData << " ";
                current = current -> m_CNext;
        }
        cout << endl;
}
template <typename T>
void CLinkedQueue<T>::MakeEmpty(){
        CLinkNode<T> *current;
        while(m_CFront != NULL){
                current = m_CFront;
                m_CFront = m_CFront -> m_CNext;
                delete current;
        }
        m_CRear = NULL;
}

template <typename T>
bool CLinkedQueue<T>::IsEmpty(){
        return (m_CFront == NULL)? true : false;
}

template <typename T>
bool CLinkedQueue<T>::EnQueue(const T& value){
        if(m_CFront == NULL){
                m_CFront = m_CRear = new CLinkNode<T>(value);
                if(m_CFront == NULL)
                        cout << "Error Distribution!" << endl;return false;
        }
        else{
                m_CRear -> m_CNext = new CLinkNode<T>(value);
                m_CRear = m_CRear -> m_CNext;
        }
        return true;
}

template <typename T>
bool CLinkedQueue<T>::DeQueue(){
        if(IsEmpty() == true)
                return false;
        CLinkNode<T> *current = m_CFront;
        m_CFront = m_CFront -> m_CNext;

        delete current;//ÀÏÎÊÌâ£¡
        current = NULL;

        return true;
}

template <typename T>
T& CLinkedQueue<T>::GetFront(){
        return m_CFront->m_TData;
}

template <typename T>
int CLinkedQueue<T>::GetSize(){
        int number = 0;
        CLinkNode<T> *current = m_CFront;
        while(current != NULL){
                ++number;
                current = current -> m_CNext;
        }
        return number;
}
#endif // CLINKEDQUEUE_H_INCLUDED
