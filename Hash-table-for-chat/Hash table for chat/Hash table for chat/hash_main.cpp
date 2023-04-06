#include "hash.h"

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    User u;

    string login_s;
    string password_s;
    char exit = 'a';

    cout << "Зарегистрируйте нового пользователя" << endl;

    while (exit != 'y')
    {
        cin.ignore(100, '\n');
        cout << "Введите логин: "; getline(cin, login_s);
        cout << "Введите пароль: "; getline(cin, password_s);

        char* login = const_cast<char*>(login_s.c_str());
        char* password = const_cast<char*>(password_s.c_str());
        u.addUser(login, password, sizeof(password));
        cout << "Пользователь добавлен\n" << endl;
        login_s.clear();
        password_s.clear();
        cout << "Выйти? \'y\' да ";
        cin >> exit;
        cout << endl;
    }
    exit = 'a';
    cout << "Проверьте зарегистрирован ли пользователь в системе." << endl;

    while (exit != 'y')
    {
        cin.ignore(100, '\n');
        cout << "Введите логин: "; getline(cin, login_s);
        cout << "Введите пароль: "; getline(cin, password_s);

        char* login = const_cast<char*>(login_s.c_str());
        char* password = const_cast<char*>(password_s.c_str());
        
        
        if (u.checkUser(login, password, sizeof(password)))
        {
            cout << "Пользователь есть\n" << endl;
        }
        else
        {
            cout << "Пользователя нету\n" << endl;
        }
        cout << "Выйти? \'y\' да ";
        cin >> exit;
    }

    return 0;
}