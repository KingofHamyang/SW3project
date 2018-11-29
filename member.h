#include <iostream>
#include <string>
#include <vector>
#include "resource.h"
#include "space.h"

using namespace std;
class member
{
protected:
  int storage;

private:
  string name;
  int borrowlimit;
  int restricted;

  int restricted_date;
  vector<book *> borrowings;
  vector<e_book *> borrowings_e_book;
  vector<int> e_book_borrowed_date;
  vector<magazine *> borrowings_magazine;
  seat *borrowing_seat;
  study_room *borrowing_s_room;

public:
  member()
  {
    borrowlimit = 20;
    restricted = 0;
    restricted_date = 0;
    storage = 0;
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
  void borrowing_magazines(magazine *booktoborrow)
  {
    magazine *temp = booktoborrow;
    borrowings_magazine.push_back(temp);
  }
  void borrowing_e_books(e_book *booktoborrow, int date)
  {
    e_book *temp = booktoborrow;
    borrowings_e_book.push_back(temp);
    int date_borrow = date;
    e_book_borrowed_date.push_back(date_borrow);
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
  bool is_borrow_this_magazine(string a)
  {
    int flag = 0;
    for (int i = 0; i < borrowings_magazine.size(); i++)
    {
      if (borrowings_magazine[i]->getname() == a)
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
  bool is_borrow_this_e_book(string a)
  {
    int flag = 0;
    for (int i = 0; i < borrowings_e_book.size(); i++)
    {
      if (borrowings_e_book[i]->getname() == a)
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
  void set_storage(int a)
  {
    storage = a;
  }
  int get_storage()
  {
    return storage;
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
  int get_borrowing_magazine_cnt()
  {
    return borrowings_magazine.size();
  }
  int get_borrowing_e_book_cnt()
  {
    return borrowings_e_book.size();
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
  void returning_e_book(string b)
  {
    for (int i = 0; i < borrowings_e_book.size(); i++)
    {
      if (borrowings_e_book[i]->getname() == b)
      {
        storage = storage - borrowings_e_book[i]->get_size();
        borrowings_e_book.erase(borrowings_e_book.begin() + i);
        e_book_borrowed_date.erase(e_book_borrowed_date.begin() + i);

        return;
      }
    }
  }
  void returning_magazine(string b)
  {
    for (int i = 0; i < borrowings_magazine.size(); i++)
    {
      if (borrowings_magazine[i]->getname() == b)
      {
        borrowings_magazine.erase(borrowings_magazine.begin() + i);
        return;
      }
    }
  }
  void set_s_room(study_room *roomtobor)
  {
    borrowing_s_room = roomtobor;
  }
  void set_seat(seat *roomtobor)
  {
    borrowing_seat = roomtobor;
  }
  study_room *get_s_room()
  {
    return borrowing_s_room;
  }
  seat *get_seat()
  {
    return borrowing_seat;
  }
  void expiring_e_book(int today, string bookname, string member_type)
  {

    int limit = 0;
    if (member_type == "Undergraduate")
    {
      limit = 14;
    }
    else if (member_type == "Graduate")
    {
      limit = 30;
    }
    else if (member_type == "Faculty")
    {
      limit = 30;
    }
    cout << "sd" << limit << member_type << today << endl;
    for (int i = 0; i < borrowings_e_book.size(); i++)
    {
      if (e_book_borrowed_date[i] + limit <= today)
      {
        cout << "sd" << limit << member_type << today << endl;
        storage = storage - borrowings_e_book[i]->get_size();
        borrowings_e_book.erase(borrowings_e_book.begin() + i);
        e_book_borrowed_date.erase(e_book_borrowed_date.begin() + i);

        return;
      }
    }
  }
  int get_borrow_e_book_date(string bookname)
  {

    for (int i = 0; i < borrowings_e_book.size(); i++)
    {
      if (borrowings_e_book[i]->getname() == bookname)
      {

        return e_book_borrowed_date[i];
      }
    }
    return -1;
  }
};
class undergraduate : public member
{
public:
  undergraduate()
  {
    set_s_room(NULL);
    set_seat(NULL);
    storage = 0;
  }
};
class faculty : public member
{
public:
  faculty()
  {
    set_s_room(NULL);
    set_seat(NULL);
    storage = 0;
  }
};
class graduate : public member
{
public:
  graduate()
  {
    set_s_room(NULL);
    set_seat(NULL);
    storage = 0;
  }
};