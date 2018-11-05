#include <iostream>
#include <fstream>
//#include "resource.h"
#include "member.h"
#include <vector>
class library
{
  public:
    ofstream of;
    vector<undergraduate> student;
    vector<book> books;
    int bookcount;
    int studentcount;
    string convert_date(int a)
    {
        int year_date;
        int month_date;
        int day_date;
        string y;
        string m;
        string d;
        year_date = a / 360;
        a = a - year_date * 360;
        month_date = a / 30;
        a = a - month_date * 30;
        day_date = a;
        y = to_string(year_date);
        m = to_string(month_date);
        if (month_date < 10)
            m = "0" + m;
        d = to_string(day_date);
        if (day_date < 10)
            d = "0" + d;
        string res = y + "/" + m + "/" + d;
        return res;
    }

    library()
    {
        bookcount = 0;
        string temp;
        fstream fs;

        of.open("output.dat");
        fs.open("resource.dat", std::fstream::in);
        fs >> temp;
        fs >> temp;
        while (!fs.eof())
        {
            fs >> temp;
            if (temp == "Book")
            {
                fs >> temp;
                book *temp_book;
                temp_book = new book();
                temp_book->setname(temp);
                books.push_back(*temp_book);
            }
        }
        ifstream openFile("input.dat");
        int cnt = 1;
        string date;
        string resourcetype;
        string resourcename;
        string operation;
        string membertype;
        string member_name;
        of << "Op_#\t"
           << "Return_code\t"
           << "Description" << endl;

        if (openFile.is_open())
        {
            string line;
            getline(openFile, line);

            while (getline(openFile, line))
            {
                stringstream ss(line);
                ss >> date;
                ss >> resourcetype;
                ss >> resourcename;
                ss >> operation;
                ss >> membertype;
                ss >> member_name;
                of << cnt << "\t";
                cnt++;
                if (operation == "B")
                {

                    borrowing_book(member_name, resourcename, date);
                }
                else
                {
                    return_the_book(resourcename, member_name, date);
                }
            }
            openFile.close();
        }
        of.close();
    }
    void add_new_member(string a)
    {
        undergraduate *temp;
        temp = new undergraduate();
        temp->setname(a);
        student.push_back(*temp);
        return;
    }
    void print_book_list()
    {
        for (int i = 0; i < books.size(); i++)
        {
            string temp;
            temp = books[i].getname();
            cout << temp << endl;
        }
        return;
    }
    void print_student_list()
    {
        for (int i = 0; i < student.size(); i++)
        {
            string temp;
            temp = student[i].getname();
            cout << temp << endl;
        }
        return;
    }
    int get_book_count()
    {
        return books.size();
    }
    int get_student_count()
    {
        return student.size();
    }
    void print_borrowings_by_person(string p)
    {
        for (int i = 0; i < student.size(); i++)
        {
            string temp;
            temp = student[i].getname();
            if (temp == p)
            {
                student[i].print_borrowing_list();
            }
        }
        return;
    }
    void borrowing_book(string p, string b, string date)
    {
        string year;
        string month;
        string day;
        int year2, month2, date2;
        int today_date;
        year = date.substr(0, 2);
        year2 = stoi(year);
        month = date.substr(3, 2);
        month2 = stoi(month);
        day = date.substr(6, 2);
        date2 = stoi(day);
        today_date = year2 * 360 + 30 * month2 + date2;

        string temp_book;
        int temp_book2;
        int temp_student2;
        int flag_Book = 0;
        int flag_person = 0;
        string temp_student;

        for (int i = 0; i < books.size(); i++)
        {

            temp_book = books[i].getname();
            if (temp_book == b)
            {
                temp_book2 = i;
                flag_Book = 1;
                break;
            }
        }
        for (int i = 0; i < student.size(); i++)
        {

            temp_student = student[i].getname();
            if (temp_student == p)
            {
                temp_student2 = i;
                flag_person = 1;
                break;
            }
        }
        if (flag_Book == 0)
        {
            of << "1\tNon exist resource." << endl;
            return;
        }
        if (flag_person == 0)
        {
            add_new_member(p);
            for (int i = 0; i < student.size(); i++)
            {

                temp_student = student[i].getname();
                if (temp_student == p)
                {
                    temp_student2 = i;
                    flag_person = 1;
                    break;
                }
            }
        }
        if (student[temp_student2].get_borrowing_book_cnt() == 1)
        {
            of << "2\tExceeds your possible number of borrow. Possible # of borrows: " << 1 << endl;
            return;
        }

        if (books[temp_book2].if_borrowed() == 1)
        {

            if (student[temp_student2].is_borrow_this(b))
            {
                of << "4\tYou already borrowed this book at" << convert_date(books[temp_book2].get_borrow_date()) << endl;
                return;
            }
            else
            {
                of << "5\tOther member already borrowed this book. This book will be returned at " << convert_date(books[temp_book2].get_borrow_date() + 13) << endl;
                return;
            }
        }
        if (student[temp_student2].get_restricted() == 1)
        {
            //cout << "sdfsaf " << today_date << " " << student[temp_student2].get_restricted_date() << endl;
            if (student[temp_student2].get_restricted_date() >= today_date)
            {
                of << "6\tRestricted member until " << convert_date(student[temp_student2].get_restricted_date()) << endl;
                return;
            }
        }

        books[temp_book2].set_borrow_date(date);

        books[temp_book2].set_borrow_name(p);
        books[temp_book2].set_borrowed(1);

        student[temp_student2].borrowing(&books[temp_book2]);
        of << "0\tSuccess." << endl;
    }
    void return_the_book(string b, string p, string date)
    {
        string temp_book;
        int temp_book2;
        int temp_student2;
        int flag_Book = 0;
        int flag_person = 0;
        string temp_student;
        for (int i = 0; i < books.size(); i++)
        {

            temp_book = books[i].getname();
            if (temp_book == b)
            {
                temp_book2 = i;
                flag_Book = 1;
                break;
            }
        }
        for (int i = 0; i < student.size(); i++)
        {

            temp_student = student[i].getname();
            if (temp_student == p)
            {
                temp_student2 = i;
                flag_person = 1;
                break;
            }
        }
        if (flag_Book == 0)
        {
            of << "1\tNon exist resource." << endl;
            return;
        }
        if (flag_person == 0)
        {
            add_new_member(p);
            for (int i = 0; i < student.size(); i++)
            {

                temp_student = student[i].getname();
                if (temp_student == p)
                {
                    temp_student2 = i;
                    flag_person = 1;
                    break;
                }
            }
        }
        if (student[temp_student2].is_borrow_this(b) == 0)
        {
            of << "3\tYou did not borrow this book." << endl;
            return;
        }

        string year;
        string month;
        string day;
        int year2, month2, date2;
        int today_date;
        year = date.substr(0, 2);
        year2 = stoi(year);
        month = date.substr(3, 2);
        month2 = stoi(month);
        day = date.substr(6, 2);
        date2 = stoi(day);
        today_date = year2 * 360 + 30 * month2 + date2;

        if (books[temp_book2].get_borrow_date() + 13 < today_date)
        {
            of << "7\tDelayed return. You'll be restricted until " << convert_date(2 * today_date - (books[temp_book2].get_borrow_date() + 13)) << endl;
            student[temp_student2].set_restricted_date(2 * today_date - (books[temp_book2].get_borrow_date() + 13));
            student[temp_student2].set_restricted(1);
        }
        else
        {
            of << "0\tSuccess." << endl;
        }
        student[temp_student2].returning_book(b);
        books[temp_book2].set_borrowed(0);
    }
};
