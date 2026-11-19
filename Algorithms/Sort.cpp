#include "Sort.h"

// Sắp xếp danh sách lớp học phần theo tên tăng dần (A -> Z) bằng thuật toán Selection Sort
void selectionSortSectionsByName(CourseSectionList &list) {
    if (list.head == nullptr || list.head->next == nullptr) {
        return;
    }

    for (SectionNode* i = list.head; i->next != nullptr; i = i->next) {
        SectionNode* minNode = i; // Tạm coi node i đang có tên lớp đứng đầu bảng chữ cái

        for (SectionNode* j = i->next; j != nullptr; j = j->next) {
            if (j->data.sectionName < minNode->data.sectionName) {
                minNode = j; // Ghi nhận lại node có tên nhỏ hơn
            }
        }
        if (minNode != i) {
            CourseSection temp = i->data;
            i->data = minNode->data;
            minNode->data = temp;
        }
    }
}
