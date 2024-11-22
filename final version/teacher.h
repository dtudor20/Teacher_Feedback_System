#pragma once
#include "user.h"
//#include "TrieNode.h"
#include <iostream>
#include <string>
#include <vector>
using namespace std;
class USER;
class REVIEW
{
public:
	REVIEW() : rev(""), stars(0) {}
	REVIEW(string rev, int stars) : rev(rev) 
	{
		while (stars < 0 || stars>5)
		{
			cout << "Pick a number between 0 and 5\n";
			cin >> stars;
		}
		this->stars = stars;
	}
	REVIEW(const REVIEW& other) : rev(other.rev), stars(other.stars) {}
	REVIEW& operator=(const REVIEW& other) {
		if (this == &other) return *this; // handle self assignment
		this->rev = other.rev;
		this->stars = other.stars;
		return *this;
	}
private:
	string rev;
	int stars;
	friend class TEACHER;
	friend class USER;
};

class TEACHER
{
public:
	TEACHER() : name(""), reviews(nullptr), nr_reviews(0) {}
	TEACHER(string name) : name(name),reviews(nullptr), nr_reviews(0) {}
	
	static bool get_reviews(string,int,int);
	REVIEW* add_review();
	TEACHER(const TEACHER& other); // Copy constructor
	TEACHER& operator=(const TEACHER& other); // Copy assignment operator
	~TEACHER() {
		delete[] reviews;
	}
private:
	string name;
	REVIEW* reviews;
	int nr_reviews;
	//static Trie trie;
};
extern TEACHER* teacher; 
//extern int nr_teachers;
