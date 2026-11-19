#pragma once
#include <string>
using namespace std;

struct Registration
{
    string MSSV;
    string sectionID;
    string registrationTime;
};

struct RegistrationNode
{
    Registration data;
    RegistrationNode *next;
};

struct RegistrationList
{
    RegistrationNode *head;
    RegistrationNode *tail;
};
