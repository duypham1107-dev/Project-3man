#include "./RegistrationList.h"

void initRegistrationList(RegistrationList &l)
{
    l.head = nullptr;
    l.tail = nullptr;
}
bool isEmpty(RegistrationList &l)
{
    if (l.head == nullptr)
        return true;
    return false;
}
bool addTail(RegistrationList &l, string mssv, string sectionID)
{
    time_t now = time(0);
    if (isDuplicate(l, mssv, sectionID))
    {
        return false;
    }
    else
    {
        RegistrationNode *p = new RegistrationNode;
        if (p == NULL)
            return false;
        p->data.MSSV = mssv;
        p->data.sectionID = sectionID;
        p->next = nullptr;

        if (isEmpty(l))
        {
            l.head = l.tail = p;
            p->data.registrationTime = ctime(&now);
            p->data.registrationTime.pop_back();
            return true;
        }
        else
        {
            l.tail->next = p;
            l.tail = p;
            p->data.registrationTime = ctime(&now);
            p->data.registrationTime.pop_back();
            return true;
        }
    }
}
bool isDuplicate(RegistrationList &l, string mssv, string sectionID)
{
    return searchRegistration(l, mssv, sectionID) != nullptr;
}
RegistrationNode *searchRegistration(RegistrationList &l, string mssv, string sectionID)
{
    RegistrationNode *p = l.head;
    while (p != nullptr && (p->data.MSSV != mssv || p->data.sectionID != sectionID))
    {
        p = p->next;
    }
    return p;
}
bool removeRegistration(RegistrationList &l, string mssv, string sectionID)
{
    if (!isEmpty(l))
    {
        RegistrationNode *p = l.head;
        RegistrationNode *temp = nullptr;
        while (p != nullptr && (p->data.MSSV != mssv || p->data.sectionID != sectionID))
        {
            temp = p;
            p = p->next;
        }
        if (p == nullptr)
            return false;
        if (p == l.head)
        {
            if (l.head == l.tail)
            {
                l.head = nullptr;
                l.tail = nullptr;
                delete p;
                return true;
            }
            else
            {
                l.head = p->next;
                delete p;
                return true;
            }
        }
        else if (p == l.tail)
        {
            l.tail = temp;
            l.tail->next = nullptr;
            delete p;
            return true;
        }
        else
        {
            temp->next = p->next;
            delete p;
            return true;
        }
    }
    return false;
}
void printRegistrationList(RegistrationList &l)
{
    if (isEmpty(l))
    {
        cout << "Danh sach dang ky rong!\n";
        return;
    }

    RegistrationNode *p = l.head;

    cout << "\n========== DANH SACH DANG KY ==========\n";
    cout << left
         << setw(15) << "MSSV"
         << setw(20) << "Ma lop hoc phan"
         << setw(25) << "Thoi gian dang ky"
         << '\n';

    cout << string(60, '-') << '\n';

    while (p != nullptr)
    {
        cout << left
             << setw(15) << p->data.MSSV
             << setw(20) << p->data.sectionID
             << setw(25) << p->data.registrationTime
             << '\n';

        p = p->next;
    }

    cout << string(60, '=') << '\n';
}
void printRegistrationBySection(
    RegistrationList &l,
    string sectionID)
{
    RegistrationNode *p = l.head;

    cout << "Danh sach dang ky lop: " << sectionID << endl;

    while (p != nullptr)
    {
        if (p->data.sectionID == sectionID)
        {
            cout << p->data.MSSV << endl;
        }

        p = p->next;
    }
}
void destroyRegistrationList(RegistrationList &l)
{
    RegistrationNode *p = l.head;
    while (p != nullptr)
    {
        l.head = p->next;
        delete p;
        p = l.head;
    }
    l.head = nullptr;
    l.tail = nullptr;
}