#ifndef CLINKEDNODE_H_INCLUDED
#define CLINKEDNODE_H_INCLUDED

#include <iostream>
using namespace std;

template <typename T>
class CLinkedQueue;
template <typename T>
class CLinkedStack;
template <typename T>
class CLinkNode
{
        friend class CLinkedQueue<T>;
        //friend ostream& operator << (ostream& os,CLinkedQueue<T>& lq);
public:
        CLinkNode(CLinkNode<T> *ptr = NULL)
        {
                m_CNext = ptr;
        }

        CLinkNode(const T& value,CLinkNode<T> *ptr = NULL)
        {
                m_TData = value;
                m_CNext = ptr;
        }
        T m_TData;
        CLinkNode<T> *m_CNext;
};


#endif // CLINKEDNODE_H_INCLUDED
