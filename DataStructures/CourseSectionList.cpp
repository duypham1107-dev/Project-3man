#include "CourseSectionList.h"
#include <iostream>

// 1. Khởi tạo danh sách rỗng
void initSectionList(CourseSectionList &list) {
    list.head = nullptr;
    list.tail = nullptr;
    list.size = 0;
}

// 2. Cấp phát động 1 Node mới
SectionNode* createSectionNode(CourseSection data) {
    SectionNode* newNode = new SectionNode;
    newNode->data = data;
    newNode->next = nullptr;
    return newNode;
}

// 3. Kiểm tra thông tin lớp học phần có hợp lệ không
bool isValidSection(CourseSection data) {
    if (data.sectionId == "" || data.courseId == "" || data.sectionName == "") return false;
    if (data.maxCapacity <= 0) return false;
    if (data.currentEnrolled < 0 || data.currentEnrolled > data.maxCapacity) return false;
    if (data.dayOfWeek < 2 || data.dayOfWeek > 8) return false; // Thứ 2 đến Chủ Nhật (8)
    if (data.startPeriod < 1 || data.startPeriod > 12) return false;
    if (data.numPeriods < 1 || (data.startPeriod + data.numPeriods - 1) > 12) return false;
    return true;
}

// 4. Tìm kiếm lớp học phần theo mã lớp
SectionNode* findSectionById(CourseSectionList list, string sectionId) {
    SectionNode* curr = list.head;
    while (curr != nullptr) {
        if (curr->data.sectionId == sectionId) {
            return curr; // Tìm thấy
        }
        curr = curr->next;
    }
    return nullptr; // Không tìm thấy
}

// 5. Thêm lớp học phần vào cuối danh sách
bool addSection(CourseSectionList &list, CourseSection data) {
    // Kiểm tra dữ liệu hợp lệ và không bị trùng mã lớp
    if (!isValidSection(data)) return false;
    if (findSectionById(list, data.sectionId) != nullptr) return false;

    SectionNode* newNode = createSectionNode(data);

    if (list.head == nullptr) {
        list.head = list.tail = newNode;
    } else {
        list.tail->next = newNode;
        list.tail = newNode;
    }
    list.size++;
    return true;
}

// 6. Xóa lớp học phần theo mã lớp
bool removeSection(CourseSectionList &list, string sectionId) {
    if (list.head == nullptr) return false;

    SectionNode* curr = list.head;
    SectionNode* prev = nullptr;

    while (curr != nullptr && curr->data.sectionId != sectionId) {
        prev = curr;
        curr = curr->next;
    }

    if (curr == nullptr) return false; // Không tìm thấy

    // Không cho xóa lớp nếu đang có sinh viên theo học
    if (curr->data.currentEnrolled > 0) return false;

    // TH1: Xóa node đầu (head)
    if (curr == list.head) {
        list.head = list.head->next;
        if (list.head == nullptr) {
            list.tail = nullptr;
        }
    }
    // TH2: Xóa node ở giữa hoặc cuối
    else {
        prev->next = curr->next;
        if (curr == list.tail) {
            list.tail = prev;
        }
    }

    delete curr;
    list.size--;
    return true;
}

// 7. Cập nhật thông tin lớp học phần
bool updateSectionInfo(CourseSectionList &list, CourseSection newData) {
    if (!isValidSection(newData)) return false;

    SectionNode* node = findSectionById(list, newData.sectionId);
    if (node == nullptr) return false;

    // Giữ nguyên mã môn học gốc, không cho đổi sang môn khác
    if (node->data.courseId != newData.courseId) return false;

    node->data = newData;
    return true;
}

// 8. Mở lớp hoặc Đóng lớp
bool setSectionStatus(CourseSectionList &list, string sectionId, bool isOpen) {
    SectionNode* node = findSectionById(list, sectionId);
    if (node == nullptr) return false;

    node->data.isOpen = isOpen;
    return true;
}

// 9. Tăng sĩ số lên 1 (Dùng khi TV3 đăng ký thành công cho 1 sinh viên)
bool increaseEnrolled(CourseSectionList &list, string sectionId) {
    SectionNode* node = findSectionById(list, sectionId);
    if (node == nullptr) return false;
    if (!node->data.isOpen) return false; // Lớp đóng thì không tăng được
    if (node->data.currentEnrolled >= node->data.maxCapacity) return false; // Lớp đã đầy

    node->data.currentEnrolled++;
    return true;
}

// 10. Giảm sĩ số đi 1 (Dùng khi TV3 hủy đăng ký của 1 sinh viên)
bool decreaseEnrolled(CourseSectionList &list, string sectionId) {
    SectionNode* node = findSectionById(list, sectionId);
    if (node == nullptr) return false;
    if (node->data.currentEnrolled <= 0) return false;

    node->data.currentEnrolled--;
    return true;
}

// 11. Giải phóng toàn bộ danh sách
void clearSectionList(CourseSectionList &list) {
    SectionNode* curr = list.head;
    while (curr != nullptr) {
        SectionNode* temp = curr;
        curr = curr->next;
        delete temp;
    }
    list.head = list.tail = nullptr;
    list.size = 0;
}
