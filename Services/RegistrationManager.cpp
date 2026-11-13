#include "./RegistrationManager.h"

bool registerCourse(HashTable &ht, CourseSectionList &list, string mssv, string idSection)
{
    if (searchStudent(ht, mssv) == nullptr)
        return 0;
    if (searchSection(list, idSection) == nullptr)
        return 0;
}
