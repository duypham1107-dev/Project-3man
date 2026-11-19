#ifndef COURSE_SERVICE_H
#define COURSE_SERVICE_H

#include "Course.h"
#include "CourseSectionList.h"

//Quản lý danh sách Học phần (CourseList)
void initCourseList(CourseList &cList);
CourseNode* findCourseById(CourseList cList, string courseId);
bool addCourse(CourseList &cList, Course data);
bool updateCourse(CourseList &cList, Course newData);
bool removeCourse(CourseList &cList, CourseSectionList sList, string courseId);
void clearCourseList(CourseList &cList);

// Thêm lớp học phần (có kiểm tra mã môn học gốc phải tồn tại trong CourseList)
bool addSectionWithCheck(CourseList cList, CourseSectionList &sList, CourseSection data);

//Tìm các lớp đang MỞ và CÒN CHỖ theo mã học phần
CourseSectionList getAvailableSectionsByCourse(CourseSectionList sList, string courseId);

//Hàm cung cấp cho (Module Đăng ký)
string getPrerequisiteCourseId(CourseList cList, string courseId);
bool isScheduleConflict(CourseSection secA, CourseSection secB);
int getSectionCredits(CourseList cList, CourseSectionList sList, string sectionId);

//Đọc và ghi File
bool loadCoursesFromFile(CourseList &cList, string filename);
bool saveCoursesToFile(CourseList cList, string filename);
bool loadSectionsFromFile(CourseList cList, CourseSectionList &sList, string filename);
bool saveSectionsToFile(CourseSectionList sList, string filename);

#endif
