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
void initRegistrationList(RegistrationList &l);
bool isEmpty(RegistrationList &l);
bool addTail(RegistrationList &l, string mssv, string sectionID);
RegistrationNode *searchRegistration(RegistrationList &l, string mssv, string sectionID);
bool removeRegistration(RegistrationList &l, string mssv, string sectionID);
void printRegistrationList(RegistrationList &l);
void destroyRegistrationList(RegistrationList &l);
bool isDuplicate(RegistrationList &l, string mssv, string sectionID);