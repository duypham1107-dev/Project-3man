#pragma once
#include "../DataStructures/Queue.h"
#include <string>
using namespace std;

struct CourseSection
{
    string sectionID;
    string courseName;
    int credits;
    int maxStudents;
    int currentStudents;

    int day;
    int startPeriod;
    int numberOfPeriods;

    Queue seniorQueue;
    Queue normalQueue;
};

struct CourseSectionNode
{
    CourseSection data;
    CourseSectionNode *next;
};

struct CourseSectionList
{
    CourseSectionNode *head;
    CourseSectionNode *tail;
};

void initList(CourseSectionList &list);
void addTail(CourseSectionList &list, CourseSection s);
void addHead(CourseSectionList &list, CourseSection s);
void printList(CourseSectionList &list);
bool removeSection(CourseSectionList &list, string sectionID);
CourseSectionNode *searchSection(CourseSectionList &list, string sectionID);
void destroyList(CourseSectionList &list);