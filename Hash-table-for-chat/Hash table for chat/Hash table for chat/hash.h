#pragma once
#include <iostream>
#include <string>
#include <windows.h> 
#include "sha_1.h" // string.h is already included in sha_1.h
#define LENGTH 10

class User 
{
private:
    enum LoginPasswordStatus
    {
        free, engaged, deleted
    };
    struct LoginPassword 
    {
        LoginPassword() : login(""), password(0), status(LoginPasswordStatus::free)
        {

        }
        ~LoginPassword()
        {
            if (password != 0)
            {
                delete[] password;
            }   
        }
        LoginPassword(char _login[LENGTH], uint* _password)
        {
            memcpy(login, _login, LENGTH);
            password = _password;
            status = LoginPasswordStatus::engaged;
        }
        LoginPassword& operator = (const LoginPassword& other)
        {
            memcpy(login, other.login, LENGTH);
            if (password != 0)
            {
                delete[] password;
            }

            password = new uint[SHA1HASHLENGTHUINTS];
            memcpy(password, other.password, SHA1HASHLENGTHBYTES);
            status = other.status;

            return *this;
        }
        char login[LENGTH];
        uint* password; 
        LoginPasswordStatus status;
    };

    void resize();
    void new_storage(int newStorageSize);
    int hash_func(char login[LENGTH], int step);
    int hf_multiply(int value);
    void addUserRecursio(char login[LENGTH], uint* digest);

    LoginPassword* storage;
    int storage_size;
    int storage_count;

public:
    User();
    void addUser(char _login[LENGTH], char _password[], int password_length);
    bool checkUser(char _login[LENGTH], char _password[], int password_length);
    void delUser(char _login[LENGTH]);
};