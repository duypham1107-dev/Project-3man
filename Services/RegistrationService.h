#pragma once

#include "../DataStructures/HashTable.h"
#include "../Models/CourseSection.h"
#include "../DataStructures/RegistrationList.h"
#include "../Models/Registration.h"

bool registerCourse(HashTable &ht, CourseSectionList &list, string mssv, string idSection);