#ifndef COURSE_H
#define COURSE_H

#include <string>
using namespace std;

// Cấu trúc lưu thông tin 1 Học phần 
struct Course {
    string courseId;
    string courseName;
    int credits;
    string prerequisiteId;
};

// Node cho Danh sách liên kết đơn quản lý Học phần
struct CourseNode {
    Course data;
    CourseNode* next;
};

// Cấu trúc quản lý đầu và cuối của DSLK Học phần
struct CourseList {
    CourseNode* head;
    CourseNode* tail;
    int size;
};

#endif
