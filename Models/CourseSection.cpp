#include "./CourseSection.h"
#include <iostream>
using namespace std;

void initList(CourseSectionList &list)
{
    list.head = list.tail = nullptr;
}
void addTail(CourseSectionList &list, CourseSection s)
{
    CourseSectionNode *p = new CourseSectionNode;
    p->data = s;
    p->next = nullptr;
    if (list.tail == nullptr)
    {
        list.tail = list.head = p;
    }
    else
    {
        list.tail->next = p;
        list.tail = p;
    }
}
void addHead(CourseSectionList &list, CourseSection s)
{
    CourseSectionNode *p = new CourseSectionNode;
    p->data = s;
    p->next = nullptr;

    if (list.head == nullptr)
    {
        list.tail = list.head = p;
    }
    else
    {
        p->next = list.head;
        list.head = p;
    }
}
void printList(CourseSectionList &list)
{
    CourseSectionNode *p = list.head;
    int stt = 1;
    while (p != nullptr)
    {
        cout << stt << "|" << p->data.sectionID << " " << p->data.courseName << " " << p->data.credits << endl;
        stt++;
        p = p->next;
    }
}

bool removeSection(CourseSectionList &list, string sectionID)
{
    CourseSectionNode *p = list.head;
    CourseSectionNode *prev = nullptr;
    while (p != nullptr && p->data.sectionID != sectionID)
    {
        prev = p;
        p = p->next;
    }
    if (p == nullptr)
        return false;
    if (p == list.head)
    {
        if (list.head == list.tail)
        {
            list.head = nullptr;
            list.tail = nullptr;
            delete p;
            return true;
        }
        else
        {
            list.head = p->next;
            delete p;
            return true;
        }
    }

    if (p == list.tail)
    {
        list.tail = prev;
        list.tail->next = nullptr;
        delete p;
        return true;
    }
    else
    {
        prev->next = p->next;
        delete p;
        return true;
    }
}
CourseSectionNode *searchSection(CourseSectionList &list, string sectionID)
{
    CourseSectionNode *p = list.head;
    while (p != nullptr && p->data.sectionID != sectionID)
    {
        p = p->next;
    }
    if (p != nullptr)
        return p;
    return nullptr;
}

void destroyList(CourseSectionList &list)
{
    CourseSectionNode *p = list.head;
    CourseSectionNode *temp = nullptr;

    while (p != nullptr)
    {
        temp = p->next;
        delete p;
        p = temp;
    }
    list.head = list.tail = nullptr;
}