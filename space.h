#include <iostream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;
class space
{
protected:
  int available_time_start;
  int available_time_end;
  int borrowing_person_limit;
  string borrowing_person;
  string borrowing_person_type;
  int borrowed_time;
  int have_to_return_time;
  int borrowed_date;
  bool is_borrowed;
  int total_borrowing_person_num;

public:
  int get_borrowed_date()
  {
    return borrowed_date;
  }
  void set_borrowed_date(int a)
  {
    borrowed_date = a;
  }
  int get_have_to_return_time()
  {
    return have_to_return_time;
  }
  void set_have_to_return_time(int a)
  {
    have_to_return_time = a;
  }
  int get_borrowed_time()
  {
    return borrowed_time;
  }
  void set_borrowed_time(int a)
  {
    borrowed_time = a;
  }
  string get_borrowing_person()
  {
    return borrowing_person;
  }
  void set_borrowing_person(string a)
  {
    borrowing_person = a;
  }
  void set_borrowing_person_type(string a)
  {
    borrowing_person_type = a;
  }
  string get_borrowing_person_type()
  {
    return borrowing_person_type;
  }
  bool get_is_borrowed()
  {
    return is_borrowed;
  }
  void set_is_borrowed(bool a)
  {
    is_borrowed = a;
  }
};
class study_room : public space
{
private:
public:
  study_room(int a, int b, int c)
  {
    available_time_start = a;
    available_time_end = b;
    borrowing_person_limit = c;
    is_borrowed = 0;
  }
  void set_total_borrowing_person_num(int a)
  {
    total_borrowing_person_num = a;
  }
  int get_total_borrowing_person_num()
  {
    return total_borrowing_person_num;
  }
};

class seat : public space
{
private:
  int is_empty;
  int leaving_time;

public:
  seat(int a, int b, int c)
  {
    available_time_start = a;
    available_time_end = b;
    borrowing_person_limit = c;
    is_borrowed = 0;
    set_is_empty(false);
  }
  int get_is_empty()
  {
    return is_empty;
  }
  int get_leaving_time()
  {
    return leaving_time;
  }
  void set_is_empty(int a)
  {
    is_empty = a;
  }
  void set_leaving_time(int a)
  {
    leaving_time = a;
  }
};