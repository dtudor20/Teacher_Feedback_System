#include "teacher.h"
//#include "user.h"

// Copy constructor
TEACHER::TEACHER(const TEACHER& other) : name(other.name), nr_reviews(other.nr_reviews) {
    if (other.reviews) {
        reviews = new REVIEW[nr_reviews];
        for (int i = 0; i < nr_reviews; ++i) {
            reviews[i] = other.reviews[i];
        }
    }
    else {
        reviews = nullptr;
    }
}

// Copy assignment operator
TEACHER& TEACHER::operator=(const TEACHER& other) {
    if (this == &other) {
        return *this;
    }

    delete[] reviews;

    name = other.name;
    nr_reviews = other.nr_reviews;

    if (other.reviews) {
        reviews = new REVIEW[nr_reviews];
        for (int i = 0; i < nr_reviews; ++i) {
            reviews[i] = other.reviews[i];
        }
    }
    else {
        reviews = nullptr;
    }

    return *this;
}


USER* user = new USER[2]{ USER("guest","guest",0,0,0), USER("admin","admin",1,1,0) };
TEACHER* teacher = new TEACHER[1];
//extern int nr_teachers = 0;

 REVIEW* TEACHER::add_review()
{
    string review_text;
    int stars;
    cout << "Enter your review: ";
    cin.ignore();
    getline(cin, review_text);
    cout << "Enter the number of stars (0-5): ";
    cin >> stars;
    REVIEW* new_reviews = new REVIEW[nr_reviews + 1];
    for (int j = 0; j < nr_reviews; ++j)
    {
        new_reviews[j] = reviews[j];
    }
    new_reviews[nr_reviews] = REVIEW(review_text, stars);

    delete[] reviews;
    reviews = new_reviews;
    nr_reviews++;

    cout << "Review added successfully.\n";
    return &reviews[nr_reviews - 1];
}



bool TEACHER::get_reviews(string nume, int nr_teachers,int id)
{
	for (int index1 = 0; index1 < nr_teachers; index1++)
	{
		if (nume == teacher[index1].name)
		{
			cout << "Teacher found \n"<<"Choose 1 to see the teacher's reviews or 0 to skip\n";
            if (user[id].get_logged() == true)
            {
                cout << "Choose 2 to add a review \n";
            }
			if (user[id].get_admin() == true)
			{
				cout << "Choose 3 to delete the teacher \n";
			}
            int choice;
            cin >> choice;
            switch (choice)
            {
            case 1:
                {
                int it = 1;
                    for (int index2 = 0; index2 < teacher[index1].nr_reviews; index2++)
                    {
                        cout << "Review nr " << it << ":\n";
                        cout << teacher[index1].reviews[index2].rev <<endl;
                        cout << "Number of stars received is :" << teacher[index1].reviews[index2].stars << endl<<endl;
                        it++;
                    }
                    break;
                }
            case 2:
            {
                if (user[id].get_logged() == false)
                {
                    break;
                }
                else
                {
                    teacher[index1].add_review();
                }
                break;
            }
            case 3:
            {
                if (user[id].get_admin() == false)
                {
                    break;
                }
                else
                {
                    TEACHER* new_teacher = new TEACHER[nr_teachers -1];
                    int bonus = 0;
                    if (teacher != nullptr) {
                        for (int index2 = 0; index2 < nr_teachers-1; index2++)
                        {
  
                            if (teacher[index2+bonus].name == nume)
                            {
                                index2--;
                                bonus = 1;
                            }
                            else
                            {
                                new_teacher[index2] = teacher[index2 + bonus];
                            }
                           
                        }
                        delete[] teacher;
                    }
                    teacher = new_teacher;
                    nr_teachers--;
                    cout << "Teacher deletion succesful!\n";
                    break;
                }
                break;
            }
            }
            return 1;
		}
	}
	return 0;
}