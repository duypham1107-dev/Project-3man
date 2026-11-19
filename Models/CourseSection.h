#ifndef COURSE_SECTION_H
#define COURSE_SECTION_H

#include <string>
using namespace std;

//thông tin 1 Lớp học phần
struct CourseSection {
    string sectionId;      // Mã lớp học phần
    string courseId;       // Mã học phần gốc
    string sectionName;    // Tên lớp học phần
    int maxCapacity;       // Sĩ số tối đa
    int currentEnrolled;   // Số sinh viên hiện tại đã đăng ký
    int dayOfWeek;
    int startPeriod;       // Tiết bắt đầu (1 -> 12)
    int numPeriods;        // Số tiết học
    bool isOpen;           // Trạng thái lớp: true (1) = Mở, false (0) = Đóng
};

//DSLK đơn quản lý Lớp học phần
struct SectionNode {
    CourseSection data;
    SectionNode* next;
};

#endif
