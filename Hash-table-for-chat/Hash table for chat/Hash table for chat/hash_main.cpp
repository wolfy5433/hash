#include "hash.h"

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    User u;

    string login_s;
    string password_s;
    char exit = 'a';

    cout << "��������������� ������ ������������" << endl;

    while (exit != 'y')
    {
        cin.ignore(100, '\n');
        cout << "������� �����: "; getline(cin, login_s);
        cout << "������� ������: "; getline(cin, password_s);

        char* login = const_cast<char*>(login_s.c_str());
        char* password = const_cast<char*>(password_s.c_str());
        u.addUser(login, password, sizeof(password));
        cout << "������������ ��������\n" << endl;
        login_s.clear();
        password_s.clear();
        cout << "�����? \'y\' �� ";
        cin >> exit;
        cout << endl;
    }
    exit = 'a';
    cout << "��������� ��������������� �� ������������ � �������." << endl;

    while (exit != 'y')
    {
        cin.ignore(100, '\n');
        cout << "������� �����: "; getline(cin, login_s);
        cout << "������� ������: "; getline(cin, password_s);

        char* login = const_cast<char*>(login_s.c_str());
        char* password = const_cast<char*>(password_s.c_str());
        
        
        if (u.checkUser(login, password, sizeof(password)))
        {
            cout << "������������ ����\n" << endl;
        }
        else
        {
            cout << "������������ ����\n" << endl;
        }
        cout << "�����? \'y\' �� ";
        cin >> exit;
    }

    return 0;
}