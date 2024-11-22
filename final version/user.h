#pragma once
#include "teacher.h"
#include <string> 
using namespace std;
class TEACHER;
class REVIEW;
class USER
{
public:
    USER();
    USER(string password, string username, bool is_logged, bool is_admin,int nr_user_reviews)
        : password(password), username(username), is_logged(is_logged), is_admin(is_admin), user_reviews(nullptr), nr_user_reviews(0) {
    }

    USER(const USER& other);
    USER& operator=(const USER& other);

    static int nr_users;
    static void solve(int&);
    int nr_user_reviews;
    bool get_admin() {
        return is_admin;
    }
    bool get_logged()
    {
        return is_logged;
    }
    ~USER() { delete[] user_reviews; };
private:
    bool is_logged;
    bool is_admin;
    string username;
    string password;
    REVIEW* user_reviews;
    //friend TEACHER;
};
extern USER* user;
//extern int nr_users=0; 