#include "./Queue.h"
#include <iostream>
using namespace std;

WaitNode *initQueue(string x)
{
    WaitNode *p = new WaitNode;
    if (p == NULL)
        return NULL;
    p->MSSV = x;
    p->next = NULL;
    return p;
}

bool isEmpty(Queue &q)
{
    if (q.front == NULL)
        return true;
    return false;
}

bool enqueue(Queue &q, string x)
{
    WaitNode *p = initQueue(x);
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