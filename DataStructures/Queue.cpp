#include "./Queue.h"
#include <iostream>
using namespace std;

void initQueue(Queue &q)
{
    q.front = nullptr;
    q.rear = nullptr;
}
bool isEmpty(Queue &q)
{
    if (q.front == NULL)
        return true;
    return false;
}

bool enqueue(Queue &q, string x)
{
    WaitNode *p = new WaitNode;
    p->MSSV = x;
    p->next = nullptr;
    if (p == NULL)
        return 0;
    if (q.front == NULL)
    {
        q.front = q.rear = p;
        return 1;
    }
    else
    {

        q.rear->next = p;
        q.rear = p;
        return 1;
    }
}
bool dequeue(Queue &q)
{
    if (q.front == NULL)
        return 0;
    WaitNode *p = q.front;
    q.front = p->next;
    delete p;
    if (q.front == NULL)
        q.rear = NULL;
    return 1;
}

bool getFront(Queue &q, string &result)
{
    if (isEmpty(q))
        return false;

    result = q.front->MSSV;
    return true;
}

void printQueue(Queue &q)
{
    WaitNode *p = q.front;
    while (p != NULL)
    {
        cout << p->MSSV << " ";
        p = p->next;
    }
}

void destroyQueue(Queue &q)
{
    WaitNode *p = q.front;
    while (p != nullptr)
    {
        q.front = p->next;
        delete p;
        p = q.front;
    }
    q.front = nullptr;
    q.rear = nullptr;
}