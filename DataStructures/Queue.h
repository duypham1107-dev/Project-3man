#pragma once
#include <string>
using namespace std;

struct WaitNode
{
    string MSSV;
    WaitNode *next;
};

struct Queue
{
    WaitNode *front;
    WaitNode *rear;
};

void initQueue(Queue &q);
bool isEmpty(Queue &q);
bool enqueue(Queue &q, string MSSV);
bool dequeue(Queue &q);
bool getFront(Queue &q, string &result);
void destroyQueue(Queue &q);
void printQueue(Queue &q);