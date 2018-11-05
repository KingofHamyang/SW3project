#include <iostream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;
class resource
{
  private:
    string name;
    string borrowing_person;
    int borrowed_date;
    int due_date;
    bool borrowed;

  public:
    resource()
    {
        borrowed_date = 0;
        borrowed = 0;
        due_date = 0;
    }

    void setname(string a)
    {
        name = a;
    }
    string getname()
    {
        return name;
    }
    void set_borrow_name(string a)
    {
        borrowing_person = a;
    }
    string get_borrow_name()
    {
        return borrowing_person;
    }
    bool if_borrowed()
    {
        return borrowed;
    }
    void set_borrowed(bool a)
    {
        borrowed = a;
    }
    void set_borrow_date(string a)
    {
        string year;
        string month;
        string date;
        int year2, month2, date2;
        year = a.substr(0, 2);
        year2 = stoi(year);
        month = a.substr(3, 2);
        month2 = stoi(month);
        date = a.substr(6, 2);
        date2 = stoi(date);
        borrowed_date = year2 * 360 + 30 * month2 + date2;

        // cout << year2 << " " << month << " " << date << endl;
        return;
    }
    int get_borrow_date()
    {
        return borrowed_date;
    }
};
class book : public resource
{
  public:
    char borrowed_person[20];
};