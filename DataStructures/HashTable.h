
#pragma once
#include "../Models/Student.h"
using namespace std;

struct HashTable
{
    StudentNode **buckets;
    int capacity;
};

int hashFunction(string key, int capacity);
bool IsDuplicate(HashTable &ht, string MSSV);
void insert(HashTable &ht, Student s);
StudentNode *searchStudent(HashTable &ht, string MSSV);
bool deleteStudent(HashTable &ht, string MSSV);

void initHashTable(HashTable &ht, int capacity);
void printHashTable(HashTable &ht);

void destroyHashTable(HashTable &ht);