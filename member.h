#include <iostream>
#include <string>
#include <vector>
#include "resource.h"
using namespace std;

class member
{
private:
  string name;
  int borrowlimit;
  int restricted;
  int restricted_date;
  vector<book *> borrowings;

public:
  member()
  {
    borrowlimit = 20;
    restricted = 0;
    restricted_date = 0;
  }
  void setname(string a)
  {
    name = a;
  }
  string getname()
  {
    return name;
  }
  void set_borrowlimit(int a)
  {
    borrowlimit = a;
  }
  int get_borrowlimit(int a)
  {
    return borrowlimit;
  }
  void borrowing(book *booktoborrow)
  {
    book *temp = booktoborrow;
    borrowings.push_back(temp);
  }
  void print_borrowing_list()
  {
    for (int i = 0; i < borrowings.size(); i++)
    {
      string temp = borrowings[i]->getname();
      cout << temp;
    }
  }
  bool is_borrow_this(string a)
  {
    int flag = 0;
    for (int i = 0; i < borrowings.size(); i++)
    {
      if (borrowings[i]->getname() == a)
      {
        flag = 1;
        break;
      }
    }
    if (flag == 0)
    {
      return 0;
    }
    else
      return 1;
  }
  void set_restricted(int a)
  {
    restricted = a;
  }
  int get_restricted()
  {
    return restricted;
  }
  void set_restricted_date(int a)
  {
    restricted_date = a;
  }
  int get_restricted_date()
  {
    return restricted_date;
  }
  int get_borrowing_book_cnt()
  {
    return borrowings.size();
  }
  void returning_book(string b)
  {
    for (int i = 0; i < borrowings.size(); i++)
    {
      if (borrowings[i]->getname() == b)
      {
        borrowings.erase(borrowings.begin() + i);
        return;
      }
    }
  }
};

class undergraduate : public member
{
public:
};