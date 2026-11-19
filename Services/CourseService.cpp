#include "CourseService.h"
#include <fstream>
#include <sstream>
#include <iostream>

// Hàm phụ 1: Xóa ký tự '\r' ở cuối dòng (tránh lỗi khi đọc file txt)
string cleanString(string s) {
    if (!s.empty() && s[s.length() - 1] == '\r') {
        s.erase(s.length() - 1);
    }
    return s;
}

// Hàm phụ 2: Đổi chuỗi sang số nguyên an toàn bằng vòng lặp cơ bản (không dùng try-catch)
int stringToInt(string s) {
    s = cleanString(s);
    if (s == "") return -1;

    int result = 0;
    for (int i = 0; i < (int)s.length(); i++) {
        if (s[i] < '0' || s[i] > '9') return -1; // Chứa ký tự không phải chữ số
        result = result * 10 + (s[i] - '0');
    }
    return result;
}

// 1. Khởi tạo DSLK Học phần
void initCourseList(CourseList &cList) {
    cList.head = nullptr;
    cList.tail = nullptr;
    cList.size = 0;
}

// 2. Tìm Học phần theo mã
CourseNode* findCourseById(CourseList cList, string courseId) {
    CourseNode* curr = cList.head;
    while (curr != nullptr) {
        if (curr->data.courseId == courseId) return curr;
        curr = curr->next;
    }
    return nullptr;
}

// 3. Thêm Học phần mới
bool addCourse(CourseList &cList, Course data) {
    if (data.courseId == "" || data.courseName == "" || data.credits <= 0) return false;
    if (findCourseById(cList, data.courseId) != nullptr) return false;

    if (data.prerequisiteId == "") {
        data.prerequisiteId = "NONE";
    }

    CourseNode* newNode = new CourseNode;
    newNode->data = data;
    newNode->next = nullptr;

    if (cList.head == nullptr) {
        cList.head = cList.tail = newNode;
    } else {
        cList.tail->next = newNode;
        cList.tail = newNode;
    }
    cList.size++;
    return true;
}

// 4. Sửa thông tin Học phần
bool updateCourse(CourseList &cList, Course newData) {
    if (newData.courseName == "" || newData.credits <= 0) return false;

    CourseNode* node = findCourseById(cList, newData.courseId);
    if (node == nullptr) return false;

    if (newData.prerequisiteId == "") newData.prerequisiteId = "NONE";
    node->data = newData;
    return true;
}

// 5. Xóa Học phần (Chỉ cho xóa khi môn đó chưa có lớp học phần nào)
bool removeCourse(CourseList &cList, CourseSectionList sList, string courseId) {
    if (cList.head == nullptr) return false;

    // Kiểm tra xem có lớp học phần nào thuộc môn này không
    SectionNode* secCurr = sList.head;
    while (secCurr != nullptr) {
        if (secCurr->data.courseId == courseId) {
            return false; // Đang có lớp học phần thuộc môn này không được xóa
        }
        secCurr = secCurr->next;
    }

    CourseNode* curr = cList.head;
    CourseNode* prev = nullptr;
    while (curr != nullptr && curr->data.courseId != courseId) {
        prev = curr;
        curr = curr->next;
    }

    if (curr == nullptr) return false;

    if (curr == cList.head) {
        cList.head = cList.head->next;
        if (cList.head == nullptr) cList.tail = nullptr;
    } else {
        prev->next = curr->next;
        if (curr == cList.tail) cList.tail = prev;
    }

    delete curr;
    cList.size--;
    return true;
}

// 6. Giải phóng bộ nhớ DSLK Học phần
void clearCourseList(CourseList &cList) {
    CourseNode* curr = cList.head;
    while (curr != nullptr) {
        CourseNode* temp = curr;
        curr = curr->next;
        delete temp;
    }
    cList.head = cList.tail = nullptr;
    cList.size = 0;
}

// 7. Thêm lớp học phần có kiểm tra mã môn học gốc phải tồn tại
bool addSectionWithCheck(CourseList cList, CourseSectionList &sList, CourseSection data) {
    if (findCourseById(cList, data.courseId) == nullptr) {
        return false; // Mã học phần gốc chưa có trong danh sách môn học
    }
    return addSection(sList, data);
}

// 8. Tìm các lớp còn chỗ theo mã học phần
CourseSectionList getAvailableSectionsByCourse(CourseSectionList sList, string courseId) {
    CourseSectionList result;
    initSectionList(result);

    SectionNode* curr = sList.head;
    while (curr != nullptr) {
        if (curr->data.courseId == courseId &&
            curr->data.isOpen == true &&
            curr->data.currentEnrolled < curr->data.maxCapacity) {
            addSection(result, curr->data);
        }
        curr = curr->next;
    }
    return result;
}

// 9. [Hỗ trợ TV3] Lấy mã môn tiên quyết
string getPrerequisiteCourseId(CourseList cList, string courseId) {
    CourseNode* node = findCourseById(cList, courseId);
    if (node == nullptr) return "NONE";
    return node->data.prerequisiteId;
}

// 10. Kiểm tra 2 lớp học phần có trùng lịch nhau không
bool isScheduleConflict(CourseSection secA, CourseSection secB) {
    if (secA.dayOfWeek != secB.dayOfWeek) return false;

    int endA = secA.startPeriod + secA.numPeriods - 1;
    int endB = secB.startPeriod + secB.numPeriods - 1;

    if (secA.startPeriod <= endB && secB.startPeriod <= endA) {
        return true; // Trùng lịch
    }
    return false;
}

// 11.Lấy số tín chỉ của lớp học phần
int getSectionCredits(CourseList cList, CourseSectionList sList, string sectionId) {
    SectionNode* secNode = findSectionById(sList, sectionId);
    if (secNode == nullptr) return 0;

    CourseNode* courseNode = findCourseById(cList, secNode->data.courseId);
    if (courseNode == nullptr) return 0;

    return courseNode->data.credits;
}

// 12. Đọc file courses.txt
bool loadCoursesFromFile(CourseList &cList, string filename) {
    ifstream file(filename);
    if (!file.is_open()) return false;

    clearCourseList(cList); // Xóa danh sách cũ trước khi đọc mới

    string line;
    while (getline(file, line)) {
        line = cleanString(line);
        if (line == "") continue;

        stringstream ss(line);
        Course c;
        string creditsStr;

        getline(ss, c.courseId, '|');
        getline(ss, c.courseName, '|');
        getline(ss, creditsStr, '|');
        getline(ss, c.prerequisiteId, '|');

        c.courseId = cleanString(c.courseId);
        c.courseName = cleanString(c.courseName);
        c.prerequisiteId = cleanString(c.prerequisiteId);
        c.credits = stringToInt(creditsStr);

        if (c.credits > 0) {
            addCourse(cList, c);
        }
    }
    file.close();
    return true;
}

// 13. Ghi file courses.txt
bool saveCoursesToFile(CourseList cList, string filename) {
    ofstream file(filename);
    if (!file.is_open()) return false;

    CourseNode* curr = cList.head;
    while (curr != nullptr) {
        file << curr->data.courseId << "|"
             << curr->data.courseName << "|"
             << curr->data.credits << "|"
             << curr->data.prerequisiteId << "\n";
        curr = curr->next;
    }
    file.close();
    return true;
}

// 14. Đọc file sections.txt
bool loadSectionsFromFile(CourseList cList, CourseSectionList &sList, string filename) {
    ifstream file(filename);
    if (!file.is_open()) return false;

    clearSectionList(sList); // Xóa danh sách cũ trước khi đọc mới

    string line;
    while (getline(file, line)) {
        line = cleanString(line);
        if (line == "") continue;

        stringstream ss(line);
        CourseSection sec;
        string maxCapStr, curEnrStr, dayStr, startStr, numPerStr, openStr;

        getline(ss, sec.sectionId, '|');
        getline(ss, sec.courseId, '|');
        getline(ss, sec.sectionName, '|');
        getline(ss, maxCapStr, '|');
        getline(ss, curEnrStr, '|');
        getline(ss, dayStr, '|');
        getline(ss, startStr, '|');
        getline(ss, numPerStr, '|');
        getline(ss, openStr, '|');

        sec.sectionId = cleanString(sec.sectionId);
        sec.courseId = cleanString(sec.courseId);
        sec.sectionName = cleanString(sec.sectionName);
        openStr = cleanString(openStr);

        sec.maxCapacity = stringToInt(maxCapStr);
        sec.currentEnrolled = stringToInt(curEnrStr);
        sec.dayOfWeek = stringToInt(dayStr);
        sec.startPeriod = stringToInt(startStr);
        sec.numPeriods = stringToInt(numPerStr);
        sec.isOpen = (openStr == "1");

        // Nếu cList đã có dữ liệu thì kiểm tra mã môn gốc, nếu chưa nạp cList thì thêm trực tiếp
        if (cList.head != nullptr) {
            addSectionWithCheck(cList, sList, sec);
        } else {
            addSection(sList, sec);
        }
    }
    file.close();
    return true;
}

// 15. Ghi file sections.txt
bool saveSectionsToFile(CourseSectionList sList, string filename) {
    ofstream file(filename);
    if (!file.is_open()) return false;

    SectionNode* curr = sList.head;
    while (curr != nullptr) {
        file << curr->data.sectionId << "|"
             << curr->data.courseId << "|"
             << curr->data.sectionName << "|"
             << curr->data.maxCapacity << "|"
             << curr->data.currentEnrolled << "|"
             << curr->data.dayOfWeek << "|"
             << curr->data.startPeriod << "|"
             << curr->data.numPeriods << "|"
             << (curr->data.isOpen ? 1 : 0) << "\n";
        curr = curr->next;
    }
    file.close();
    return true;
}
