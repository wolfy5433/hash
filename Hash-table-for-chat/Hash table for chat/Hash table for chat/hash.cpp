#include "hash.h"

User::User()
{
    storage_count = 0;
    storage = nullptr;

    new_storage(8);
}

void User::addUser(char _login[LENGTH], char _password[], int password_length)
{
    uint* digest = sha1(_password, password_length);
    addUserRecursio(_login, digest);
}

void User::delUser(char _login[LENGTH])
{
    int index, i = 0;
    for (; i < storage_size; ++i)
    {
        index = hash_func(_login, i * i);
        if (storage[index].status == LoginPasswordStatus::free)
        {
            return;
        }
        else if (storage[index].status == LoginPasswordStatus::engaged && !memcmp(_login, storage[index].login, LENGTH))
        {
            break;
        }
    }
    if (i >= storage_size)
    {
        return;
    }

    storage[index].status = LoginPasswordStatus::deleted;
}

bool User::checkUser(char _login[LENGTH], char _password[], int password_length)
{

    int index, i = 0;
    for (; i < storage_size; i++) {
        index = hash_func(_login, i * i);
        if (storage[index].status == LoginPasswordStatus::free)
        {
            return false;
        }
        else if (storage[index].status == LoginPasswordStatus::engaged && !memcmp(_login, storage[index].login, LENGTH))
        {
            break;
        }
    }
    if (i >= storage_size)
    {
        return false;
    }

    uint* digest = sha1(_password, password_length);

    bool result = !memcmp(storage[index].password, digest, SHA1HASHLENGTHBYTES);
    
    delete[] digest;

    return result;
}

void User::addUserRecursio(char login[LENGTH], uint* digest)
{
    int index, i = 0;
    for (; i < storage_size; ++i)
    {
        index = hash_func(login, i * i);
        if (storage[index].status == LoginPasswordStatus::free)
        {
            break;
        }
    }
    if (i >= storage_size)
    {
        resize();
        addUserRecursio(login, digest);
    }
    else 
    {
        storage[index] = LoginPassword(login, digest);
        ++storage_count;
    }
}

void User::new_storage(int newStorageSize)
{
    storage_size = newStorageSize;
    storage = new LoginPassword[storage_size];
}

int User::hash_func(char login[LENGTH], int step)
{
    long sum = 0;
    for (int i = 0; i < LENGTH; ++i) 
    {
        sum += login[i];
    }
    return (hf_multiply(sum) + step) % storage_size;
}

int User::hf_multiply(int value)
{
    const double A = 0.7;
    return int(storage_size * (A * value - int(A * value)));
}

void User::resize()
{
    std::cout << "resize()" << endl;
    LoginPassword* save = storage;
    int save_ms = storage_size;

    new_storage(storage_size * 2);
    storage_count = 0;

    for (int i = 0; i < save_ms; ++i) 
    {
        LoginPassword& old_data = save[i];
        if (old_data.status == LoginPasswordStatus::engaged)
        {

            uint* sha_hash_copy = new uint[SHA1HASHLENGTHUINTS];
            memcpy(sha_hash_copy, old_data.password, SHA1HASHLENGTHBYTES);

            addUserRecursio(old_data.login, sha_hash_copy);
        }
    }

    delete[] save;
}