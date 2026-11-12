#include "./HashTable.h"
#include <iostream>
using namespace std;

int hashFunction(string key, int capacity)
{
    int sum = 0;
    for (int i = 0; i < key.length(); i++)
    {
        sum += key[i];
    }
    return sum % capacity;
}
bool IsDuplicate(HashTable &ht, string MSSV)
{
    return searchStudent(ht, MSSV) != NULL;
}
void insert(HashTable &ht, Student s)
{
    if (!IsDuplicate(ht, s.MSSV))
    {
        int hash = hashFunction(s.MSSV, ht.capacity);
        StudentNode *p = new StudentNode;
        p->data = s;
        p->next = ht.buckets[hash];
        ht.buckets[hash] = p;
        cout << "Success!";
    }
    else
    {
        cout << "Duplicate Student!!!";
    }
}
StudentNode *searchStudent(HashTable &ht, string MSSV)
{
    int hash = hashFunction(MSSV, ht.capacity);
    StudentNode *p = ht.buckets[hash];
    while (p != NULL && p->data.MSSV != MSSV)
    {
        p = p->next;
    }

    return p;
}
bool deleteStudent(HashTable &ht, string MSSV)
{
    int hash = hashFunction(MSSV, ht.capacity);
    StudentNode *p = ht.buckets[hash];
    StudentNode *prev = NULL;

    while (p != NULL && p->data.MSSV != MSSV)
    {
        prev = p;
        p = p->next;
    }

    if (p == NULL)
        return false;

    if (p == ht.buckets[hash])
    {
        ht.buckets[hash] = p->next;
        delete p;
        return true;
    }

    prev->next = p->next;
    delete p;
    return true;
}

void initHashTable(HashTable &ht, int capacity)
{
    ht.capacity = capacity;
    ht.buckets = new StudentNode *[capacity];
    for (int i = 0; i < capacity; i++)
    {
        ht.buckets[i] = NULL;
    }
}
void printHashTable(HashTable &ht)
{
    for (int i = 0; i < ht.capacity; i++)
    {
        StudentNode *p = ht.buckets[i];

        cout << "Buckets " << i << ": ";

        while (p != NULL)
        {
            cout << p->data.MSSV << " - "
                 << p->data.FullName << " - "
                 << p->data.SchoolYears << " -> ";

            p = p->next;
        }

        cout << "NULL" << endl;
    }
}

void destroyHashTable(HashTable &ht)
{
    for (int i = 0; i < ht.capacity; i++)
    {
        StudentNode *p = ht.buckets[i];
        StudentNode *temp;
        while (p != NULL)
        {
            temp = p->next;
            delete p;
            p = temp;
        }
    }
    delete[] ht.buckets;
    ht.buckets = NULL;
    ht.capacity = 0;
}
