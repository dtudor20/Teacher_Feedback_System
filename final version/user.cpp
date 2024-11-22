#include "user.h"
#include "teacher.h"
#include <iostream> 

int nr_teachers = 0;
int id = 0;
int USER::nr_users = 2;

USER::USER() : is_logged(false), is_admin(false), username(""), password(""), user_reviews(nullptr), nr_user_reviews(0) {}

// Copy constructor
USER::USER(const USER& other)
    : is_logged(other.is_logged), is_admin(other.is_admin), username(other.username), password(other.password), nr_user_reviews(other.nr_user_reviews)
{
    if (other.user_reviews != nullptr) {
        user_reviews = new REVIEW[nr_user_reviews];
        for (int i = 0; i < nr_user_reviews; ++i) {
            user_reviews[i] = other.user_reviews[i];
        }
    }
    else {
        user_reviews = nullptr;
    }
}

// Copy assignment operator
USER& USER::operator=(const USER& other)
{
    if (this == &other) return *this; // handle self-assignment

    // Clean up existing resources
    delete[] user_reviews;

    // Copy data from other
    is_logged = other.is_logged;
    is_admin = other.is_admin;
    username = other.username;
    password = other.password;
    nr_user_reviews = other.nr_user_reviews;

    if (other.user_reviews != nullptr) {
        user_reviews = new REVIEW[nr_user_reviews];
        for (int i = 0; i < nr_user_reviews; ++i) {
            user_reviews[i] = other.user_reviews[i];
        }
    }
    else {
        user_reviews = nullptr;
    }

    return *this;
}

void USER::solve(int& choice)
{
    std::cout << "Write 1 to search a teacher\n";
    if (id == 0)
    {
        std::cout << "Write 2 to log in\n";
    }
    else
    {
        std::cout << "Write 2 to log out\n" << "Write 3 to see your reviews\n";
    }
    std::cout << "Write 0 to stop\n";
    std::cin >> choice;
    while (choice < 0 || choice > 3)
    {
        std::cout << "Your choice should be between 0 and 3, pick again\n";
        std::cin >> choice;
    }
    switch (choice)
    {
    case 0:
        break;
    case 1:
    {
        std::cout << "Write the teacher's last name and name in this order with a space between them: \n";
        std::string name;
        std::cin.ignore();
        std::getline(std::cin, name);
        bool found = TEACHER::get_reviews(name, nr_teachers, id);
        if (!found)
        {
            std::cout << "Teacher not found\n";
            int choice2;
            if (user[id].get_logged())
            {
                std::cout << "Choose 1 to write the teacher a review or 0 if you don't want to \n";
                std::cin >> choice2;
                if (choice2 == 1)
                {
                    TEACHER* new_teacher = new TEACHER[nr_teachers + 1];
                    if (teacher != nullptr) {
                        for (int index1 = 0; index1 < nr_teachers; index1++)
                        {
                            new_teacher[index1] = teacher[index1];
                        }
                        delete[] teacher;
                    }
                    teacher = new_teacher;
                    teacher[nr_teachers] = TEACHER(name);
                    nr_teachers++;

                    REVIEW* new_user_reviews = new REVIEW[user[id].nr_user_reviews + 1];
                    if (user[id].user_reviews != nullptr) {
                        for (int index1 = 0; index1 < user[id].nr_user_reviews; index1++)
                        {
                            new_user_reviews[index1] = user[id].user_reviews[index1];
                        }
                        delete[] user[id].user_reviews;
                    }
                    user[id].user_reviews = new_user_reviews;
                    user[id].user_reviews[user[id].nr_user_reviews] = *teacher[nr_teachers - 1].add_review();
                    user[id].nr_user_reviews++;
                }
            }
            else
            {
                std::cout << "You need to log in to add a review. " << "Log in and try again\n";
            }
        }
        break;
    }
    case 2:
    {
        if (id == 0)
        {
            std::cout << "Type in your username:\n";
            std::string usern;
            std::cin.ignore();
            std::getline(std::cin, usern);
            bool found = false;
            for (int index2 = 0; index2 < USER::nr_users; index2++)
            {
                if (usern == user[index2].username)
                {
                    found = true;
                    std::cout << "Account found!\n" << "Type in your password:\n";
                    std::string pass;
                    //std::cin.ignore();
                    std::getline(std::cin, pass);
                    while (pass != user[index2].password)
                    {
                        std::cout << "Wrong password. Try again or press 0 to exit\n";
                        //std::cin.ignore();
                        std::getline(std::cin, pass);
                        if (pass == "0")
                        {
                            break;
                        }
                    }
                    cout << "Correct password! Now you are logged in\n";
                    id = index2;
                    user[index2].solve(choice);
                }
            }
            if (!found)
            {
                std::cout << "Account doesn't exist. Choose 1 if you want to create an account for the username or 0 to skip\n";
                int choice3;
                std::cin >> choice3;
                if (choice3 == 1)
                {
                    std::cout << "Enter the account password:\n";
                    std::string passn;
                    std::cin >> passn;
                    USER* new_user = new USER[USER::nr_users + 1];
                    for (int index3 = 0; index3 < USER::nr_users; index3++)
                    {
                        new_user[index3] = user[index3];
                    }
                    delete[] user;
                    user = new_user;
                    user[USER::nr_users] = USER(passn, usern, true, false, 0);
                    USER::nr_users++;
                }
            }
        }
        else
        {
            id = 0;
        }
        break;
    }
    case 3:
    {
        cout << "The reviews you wrote are the following:\n";
        int it = 1;
        for (int index2 = 0; index2 < user[id].nr_user_reviews; index2++)
        {
            cout << "Review nr " << it << ":\n";
            cout << user[id].user_reviews[index2].rev << endl;
            cout << "Number of stars given is :" << user[id].user_reviews[index2].stars << endl << endl;
            it++;
        }
        break;

    }
    std::cout << std::endl;
    }
}

