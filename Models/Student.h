#pragma once
#include <string>
using namespace std;

struct Student
{
    string MSSV;
    string FullName;
    int SchoolYears;
};

struct StudentNode
{
    Student data;
    StudentNode *next;
};