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
    study_room *s_room[10];
    int study_room_borrowed[10];
    seat *seat_floor[3][50];
    int seat_check[3];

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
    int convert_date_to_int(string date)
    {
        int BorS = 0;
        for (int i = 0;; i++)
        {
            if (date[i] == '/')
            {
                if (i == 2)
                {
                    BorS = 0;
                }
                else
                {
                    BorS = 1;
                }
                break;
            }
        }

        string year;
        string month;
        string day;
        int year2, month2, date2;
        int today_date;
        //cout << date;
        if (BorS == 1)
        {
            year = date.substr(2, 2);
            year2 = stoi(year);
            month = date.substr(5, 2);
            month2 = stoi(month);
            day = date.substr(8, 2);
            date2 = stoi(day);
        }
        else
        {
            year = date.substr(0, 2);
            year2 = stoi(year);
            month = date.substr(3, 2);
            month2 = stoi(month);
            day = date.substr(6, 2);
            date2 = stoi(day);
        }

        today_date = year2 * 360 + 30 * month2 + date2;

        return today_date;
    }

    library()
    {
        for (int i = 0; i < 10; i++)
        {
            s_room[i] = new study_room(9, 18, 6);
        }
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 50; j++)
            {
                seat_floor[i][j] = new seat(0, 24, 1);
            }
        }

        for (int i = 0; i < 10; i++)
        {
            study_room_borrowed[i] = 0;
        }

        seat_check[0] = 0;
        seat_check[1] = 0;
        seat_check[2] = 0;

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
        ifstream openFile_space("space.dat");

        int cnt = 1;
        string date1;
        string date2;
        string resourcetype;
        string resourcename;
        string operation;
        string membertype;
        string member_name;
        int space_id;
        string number_of_member;
        string time_to;
        int space_flag = 0;
        int book_flag = 0;

        of
            << "Op_#\t"
            << "Return_code\t"
            << "Description" << endl;

        if (openFile.is_open() && openFile_space.is_open())
        {
            string line1, line2;
            getline(openFile, line1);
            getline(openFile_space, line2);
            getline(openFile, line1);
            getline(openFile_space, line2);
            stringstream ss1;
            stringstream ss2;
            ss1.str(line1);
            ss2.str(line2);
            ss1 >> date1;
            ss2 >> date2;
            int Bdate = convert_date_to_int(date1);
            int Sdate = convert_date_to_int(date2);

            while (1)
            {
                cout << Bdate << " " << Sdate << endl;
                if (book_flag == 0 && space_flag == 0)
                {

                    if (Sdate < Bdate)
                    {

                        ss2 >> resourcetype;
                        if (resourcetype == "StudyRoom")
                        {
                            ss2 >> space_id;
                            ss2 >> operation;
                            ss2 >> membertype;
                            ss2 >> member_name;

                            of << cnt << "\t";
                            cnt++;
                            cout << space_id << " " << operation << " " << membertype << " " << member_name << endl;
                            if (operation == "B")
                            {
                                ss2 >> number_of_member;
                                ss2 >> time_to;
                                borrowing_study_room(space_id, date2, member_name, number_of_member, time_to);
                            }
                            else if (operation == "R")
                            {
                                return_study_room(space_id, date2, member_name);
                            }
                        }
                        else if (resourcetype == "Seat")
                        {
                            ss2 >> space_id;
                            ss2 >> operation;
                            ss2 >> membertype;
                            ss2 >> member_name;
                            cout << space_id << " " << operation << " " << membertype << " " << member_name << endl;
                            of << cnt << "\t";
                            cnt++;
                            if (operation == "B")
                            {
                                ss2 >> number_of_member;
                                ss2 >> time_to;
                                borrowing_seat(space_id, date2, member_name, number_of_member, time_to);
                            }
                            else if (operation == "E")
                            {
                                emptify_seat(space_id, date2, member_name);
                            }
                            else if (operation == "R")
                            {
                                return_seat(space_id, date2, member_name);
                            }
                            else if (operation == "C")
                            {
                                comback_seat(space_id, date2, member_name);
                            }
                        }

                        if (getline(openFile_space, line2))
                        {
                            stringstream temp(line2);
                            ss2.swap(temp);

                            ss2 >> date2;

                            Sdate = convert_date_to_int(date2);
                        }
                        else
                        {
                            space_flag = 1;
                        }
                    }
                    else
                    {
                        ss1 >> resourcetype;
                        if (resourcetype == "Book")
                        {
                            ss1 >> resourcename;
                            ss1 >> operation;
                            ss1 >> membertype;
                            ss1 >> member_name;
                            cout << space_id << " " << operation << " " << membertype << " " << member_name << endl;
                            of << cnt << "\t";
                            cnt++;
                            if (operation == "B")
                            {

                                borrowing_book(member_name, resourcename, date1);
                            }
                            else
                            {
                                return_the_book(resourcename, member_name, date1);
                            }
                        }
                        if (getline(openFile, line1))
                        {

                            stringstream temp(line1);
                            ss1.swap(temp);
                            ss1 >> date1;
                            Bdate = convert_date_to_int(date1);
                        }
                        else
                        {
                            book_flag = 1;
                        }
                        //book get
                    }
                }
                else if (book_flag == 0 && space_flag == 1)
                {
                    ss1 >> resourcetype;
                    if (resourcetype == "Book")
                    {
                        ss1 >> resourcename;
                        ss1 >> operation;
                        ss1 >> membertype;
                        ss1 >> member_name;
                        cout << space_id << " " << operation << " " << membertype << " " << member_name << endl;
                        of << cnt << "\t";
                        cnt++;
                        if (operation == "B")
                        {

                            borrowing_book(member_name, resourcename, date1);
                        }
                        else
                        {
                            return_the_book(resourcename, member_name, date1);
                        }
                    }

                    if (getline(openFile, line1))
                    {
                        stringstream temp(line1);
                        ss1.swap(temp);
                        ss1 >> date1;
                        Bdate = convert_date_to_int(date1);
                    }
                    else
                    {
                        book_flag = 1;
                    }
                }
                else if (book_flag == 1 && space_flag == 0)
                {
                    ss2 >> resourcetype;
                    if (resourcetype == "StudyRoom")
                    {
                        ss2 >> space_id;
                        ss2 >> operation;
                        ss2 >> membertype;
                        ss2 >> member_name;
                        cout << space_id << " " << operation << " " << membertype << " " << member_name << endl;
                        of << cnt << "\t";
                        cnt++;
                        if (operation == "B")
                        {
                            ss2 >> number_of_member;
                            ss2 >> time_to;
                            borrowing_study_room(space_id, date2, member_name, number_of_member, time_to);
                        }
                        else if (operation == "R")
                        {
                            return_study_room(space_id, date2, member_name);
                        }
                    }
                    else if (resourcetype == "Seat")
                    {
                        ss2 >> space_id;
                        ss2 >> operation;
                        ss2 >> membertype;
                        ss2 >> member_name;
                        cout << space_id << " " << operation << " " << membertype << " " << member_name << endl;
                        of << cnt << "\t";
                        cnt++;
                        if (operation == "B")
                        {
                            ss2 >> number_of_member;
                            ss2 >> time_to;
                            borrowing_seat(space_id, date2, member_name, number_of_member, time_to);
                        }
                        else if (operation == "E")
                        {
                            emptify_seat(space_id, date2, member_name);
                        }
                        else if (operation == "R")
                        {
                            return_seat(space_id, date2, member_name);
                        }
                        else if (operation == "C")
                        {
                            comback_seat(space_id, date2, member_name);
                        }
                    }
                    //space get
                    if (getline(openFile_space, line2))
                    {
                        stringstream temp(line2);
                        ss2.swap(temp);
                        ss2 >> date2;
                        Sdate = convert_date_to_int(date2);
                    }
                    else
                    {
                        space_flag = 1;
                    }
                }
                else
                {
                    break;
                }
            }
            openFile.close();
            openFile_space.close();
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
    int findbyPersonname(string a)
    {
        for (int i = 0; i < student.size(); i++)
        {
            if (student[i].getname() == a)
            {
                return i;
            }
        }
        return -1;
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
    void borrowing_study_room(int space_number, string date, string person, string n_of_member, string time2borrow)
    {
        int person_index;
        int person_exist_flag = 0;
        string year;
        string month;
        string day;
        string hour;
        int year2, month2, date2, hour2;
        int today_date;
        int today_hour;
        int numberofmem = stoi(n_of_member);
        int time_to_bor = stoi(time2borrow);
        year = date.substr(2, 2);
        year2 = stoi(year);
        month = date.substr(5, 2);
        month2 = stoi(month);
        day = date.substr(8, 2);
        date2 = stoi(day);
        hour = date.substr(11, 2);
        hour2 = stoi(hour);
        today_date = year2 * 360 + 30 * month2 + date2;
        today_hour = hour2;
        //cout << today_date << " " << hour2 << " " << numberofmem << " " << time_to_bor << "\n";
        for (int i = 0; i < student.size(); i++)
        {
            if (person == student[i].getname())
            {
                person_index = i;
                person_exist_flag = 1;
                break;
            }
        }
        if (person_exist_flag == 0)
        {
            add_new_member(person);
            for (int i = 0; i < student.size(); i++)
            {

                if (student[i].getname() == person)
                {
                    person_index = i;
                    person_exist_flag = 1;
                    break;
                }
            }
        }

        if (space_number < 1 || space_number > 10)
        {
            of << "8\tInvalid space id." << endl;
            return;
        }
        if (hour2 < 9 || hour2 >= 18)
        {
            of << "9\tThis space is not available now. Available 09 to 18." << endl;
            return;
        }
        study_room *temp = student[person_index].get_s_room();
        if (temp != NULL && temp->get_borrowed_date() == today_date && temp->get_have_to_return_time() > hour2)
        {
            of << "11\tYou already borrowed this kind of space." << endl;
            return;
        }

        if (numberofmem > 6)
        {
            of << "12\tExceed available number." << endl;
            return;
        }
        if (time_to_bor > 3)
        {
            of << "13\tExceed available time." << endl;
            return;
        }
        if (s_room[space_number - 1]->get_borrowed_date() == today_date && s_room[space_number - 1]->get_have_to_return_time() > hour2)
        {
            of << "14\tThere is no remain space. This space is available after " << s_room[space_number - 1]->get_have_to_return_time() << endl;
            return;
        }
        if (s_room[space_number - 1]->get_borrowed_date() != today_date)
        {
            if (s_room[space_number - 1]->get_is_borrowed() == true)
            {
                string origin_person;
                origin_person = s_room[space_number - 1]->get_borrowing_person();
                int origin_index = findbyPersonname(origin_person);
                student[origin_index].set_s_room(NULL);
            }
        }
        s_room[space_number - 1]->set_is_borrowed(true);
        s_room[space_number - 1]->set_borrowed_date(today_date);
        if (hour2 + time_to_bor <= 18)
        {
            s_room[space_number - 1]->set_have_to_return_time(hour2 + time_to_bor);
        }
        else
        {
            s_room[space_number - 1]->set_have_to_return_time(18);
        }
        s_room[space_number - 1]->set_borrowing_person(person);
        s_room[space_number - 1]->set_total_borrowing_person_num(numberofmem);

        student[person_index].set_s_room(s_room[space_number - 1]);
        of << "0\tSuccess." << endl;
    }
    void return_study_room(int space_number, string date, string person)
    {
        int person_index;
        int person_exist_flag = 0;
        string year;
        string month;
        string day;
        string hour;
        int year2, month2, date2, hour2;
        int today_date;
        int today_hour;

        year = date.substr(2, 2);
        year2 = stoi(year);
        month = date.substr(5, 2);
        month2 = stoi(month);
        day = date.substr(8, 2);
        date2 = stoi(day);
        hour = date.substr(11, 2);
        hour2 = stoi(hour);
        today_date = year2 * 360 + 30 * month2 + date2;
        today_hour = hour2;
        for (int i = 0; i < student.size(); i++)
        {
            if (person == student[i].getname())
            {
                person_index = i;
                person_exist_flag = 1;
                break;
            }
        }
        if (person_exist_flag == 0)
        {
            add_new_member(person);
            for (int i = 0; i < student.size(); i++)
            {

                if (student[i].getname() == person)
                {
                    person_index = i;
                    person_exist_flag = 1;
                    break;
                }
            }
        }
        if (space_number < 1 || space_number > 10)
        {
            of << "8\tInvalid space id." << endl;
            return;
        }
        if (s_room[space_number - 1]->get_borrowing_person() != person)
        {
            of << "10\tYou did not borrow this space." << endl;
            return;
        }
        else
        {
            study_room *temp = s_room[space_number - 1];
            if (!(temp->get_borrowed_date() == today_date && temp->get_have_to_return_time() > hour2))
            {
                of << "10\tYou did not borrow this space." << endl;

                return;
            }
        }
        student[person_index].set_s_room(NULL);

        s_room[space_number - 1]->set_is_borrowed(false);
        s_room[space_number - 1]->set_borrowing_person("");
        of << "0\tSuccess." << endl;
    }
    bool check_if_valid_seat(int index, int floor, int today_date, int hour2)
    {

        seat *temp = seat_floor[floor][index];
        if (temp->get_is_borrowed() == false)
        {
            return true;
        }

        if (temp->get_is_empty() == false)
        {
            if (temp->get_borrowed_date() == today_date && temp->get_have_to_return_time() > hour2)
            {

                return false;
            }
            else
                return true;
        }
        else
        {
            if (temp->get_leaving_time() == hour2)
            {

                return false;
            }
            else
                return true;
        }
    }
    void borrowing_seat(int space_number, string date, string person, string n_of_member, string time2borrow)
    {
        int person_index;
        int person_exist_flag = 0;
        string year;
        string month;
        string day;
        string hour;
        int year2, month2, date2, hour2;
        int today_date;
        int today_hour;
        int numberofmem = stoi(n_of_member);
        int time_to_bor = stoi(time2borrow);
        year = date.substr(2, 2);
        year2 = stoi(year);
        month = date.substr(5, 2);
        month2 = stoi(month);
        day = date.substr(8, 2);
        date2 = stoi(day);
        hour = date.substr(11, 2);
        hour2 = stoi(hour);
        today_date = year2 * 360 + 30 * month2 + date2;
        today_hour = hour2;
        for (int i = 0; i < student.size(); i++)
        {
            if (person == student[i].getname())
            {
                person_index = i;
                person_exist_flag = 1;
                break;
            }
        }
        if (person_exist_flag == 0)
        {
            add_new_member(person);
            for (int i = 0; i < student.size(); i++)
            {

                if (student[i].getname() == person)
                {
                    person_index = i;
                    person_exist_flag = 1;
                    break;
                }
            }
        }

        if (space_number < 1 || space_number > 3)
        {
            of << "8\tInvalid space id." << endl;
            return;
        }
        if (space_number == 2)
        {
            if (hour2 < 9 || hour2 >= 21)
            {
                of << "9\tThis space is not available now. Available 09 to 21." << endl;
                return;
            }
            if (hour2 + time_to_bor > 21)
            {
                time_to_bor = 21 - (hour2);
            }
        }
        if (space_number == 3)
        {
            if (hour2 < 9 || hour2 >= 18)
            {
                of << "9\tThis space is not available now. Available 09 to 18." << endl;
                return;
            }
            if (hour2 + time_to_bor > 18)
            {
                time_to_bor = 18 - (hour2);
            }
        }
        else
        {
            if (hour2 + time_to_bor > 24)
            {
                time_to_bor = 24 - (hour2);
            }
        }

        seat *temp = student[person_index].get_seat();
        if (temp != NULL)
        {
            if (temp->get_is_empty() == false)
            {
                if (temp->get_borrowed_date() == today_date && temp->get_have_to_return_time() > hour2)
                {

                    of << "11\tYou already borrowed this kind of space." << endl;
                    return;
                }
            }
            else
            {
                if (temp->get_leaving_time() == hour2)
                {
                    of << "11\tYou already borrowed this kind of space." << endl;
                    return;
                }
            }
        }
        if (numberofmem > 1)
        {
            of << "12\tExceed available number." << endl;
            return;
        }

        if (time_to_bor > 3)
        {
            of << "13\tExceed available time." << endl;
            return;
        }
        int seat_to_desig;

        int flag = 0;
        int min_val = 0x7fffffff;
        if (seat_check[space_number - 1] == 50)
        {
            for (int i = 0; i < 50; i++)
            {

                bool temp_check = check_if_valid_seat(i, space_number - 1, today_date, hour2);
                if (temp_check == true)
                {
                    flag = 1;

                    seat_to_desig = i;
                    for (int j = 0; j < student.size(); j++)
                    {
                        if (student[i].getname() == seat_floor[space_number - 1][seat_to_desig]->get_borrowing_person())
                        {
                            student[i].set_seat(NULL);
                        }
                    }
                    break;
                }
                else
                {
                    if (seat_floor[space_number - 1][i]->get_have_to_return_time() < min_val)
                    {
                        min_val = seat_floor[space_number - 1][i]->get_have_to_return_time();
                    }
                }
            }
            if (flag == 0)
            {

                //TODO -> 최소시간 계산하기

                of << "14\tThere is no remain space. This space is available after " << min_val << endl;
                return;
            }
        }
        else
        {
            seat_to_desig = seat_check[space_number - 1];
            seat_check[space_number - 1]++;
        }

        seat_floor[space_number - 1][seat_to_desig]->set_borrowed_date(today_date);
        seat_floor[space_number - 1][seat_to_desig]->set_borrowing_person(person);
        seat_floor[space_number - 1][seat_to_desig]->set_have_to_return_time(hour2 + time_to_bor);
        seat_floor[space_number - 1][seat_to_desig]->set_is_empty(false);
        seat_floor[space_number - 1][seat_to_desig]->set_is_borrowed(true);
        seat_floor[space_number - 1][seat_to_desig]->set_leaving_time(0);
        seat_floor[space_number - 1][seat_to_desig]->set_borrowed_time(hour2);

        student[person_index].set_seat(seat_floor[space_number - 1][seat_to_desig]);
        of << "0\tSuccess." << endl;
    }

    void return_seat(int space_number, string date, string person)
    {
        int person_index;
        int person_exist_flag = 0;
        string year;
        string month;
        string day;
        string hour;
        int year2, month2, date2, hour2;
        int today_date;
        int today_hour;

        year = date.substr(2, 2);
        year2 = stoi(year);
        month = date.substr(5, 2);
        month2 = stoi(month);
        day = date.substr(8, 2);
        date2 = stoi(day);
        hour = date.substr(11, 2);
        hour2 = stoi(hour);
        today_date = year2 * 360 + 30 * month2 + date2;
        today_hour = hour2;
        //cout << year2 << month2 << date2 << hour2 << endl;
        for (int i = 0; i < student.size(); i++)
        {
            if (person == student[i].getname())
            {
                person_index = i;
                person_exist_flag = 1;
                break;
            }
        }
        if (person_exist_flag == 0)
        {
            add_new_member(person);
            for (int i = 0; i < student.size(); i++)
            {

                if (student[i].getname() == person)
                {
                    person_index = i;
                    person_exist_flag = 1;
                    break;
                }
            }
        }
        if (space_number < 1 || space_number > 3)
        {
            of << "8\tInvalid space id." << endl;
            return;
        }
        seat *temp = student[person_index].get_seat();
        if (temp == NULL)
        {
            of << "10\tYou did not borrow this space1." << endl;
            return;
        }
        int flag_person = 0;
        int flag_expire = 0;
        for (int i = 0; i < 50; i++)
        {
            if (seat_floor[space_number - 1][i]->get_borrowing_person() == person)
            {
                if (seat_floor[space_number - 1][i]->get_is_empty() == false)
                {
                    if (!(seat_floor[space_number - 1][i]->get_borrowed_date() == today_date && seat_floor[space_number - 1][i]->get_have_to_return_time() > hour2))
                    {
                        flag_expire = 1;
                    }
                }
                else
                {
                    if (!(seat_floor[space_number - 1][i]->get_leaving_time() == hour2))
                    {
                        flag_expire = 1;
                    }
                }
                flag_person = 1;
                break;
            }
        }
        if (flag_person == 0 || flag_expire == 1)
        {
            of << "10\tYou did not borrow this space." << endl;
            return;
        }

        student[person_index].set_seat(NULL);

        temp->set_is_borrowed(false);
        temp->set_borrowing_person("");
        temp->set_is_empty(false);

        seat_check[space_number - 1]--;
        of << "0\tSuccess." << endl;
    }
    void emptify_seat(int space_number, string date, string person)
    {
        int person_index;
        int person_exist_flag = 0;
        string year;
        string month;
        string day;
        string hour;
        int year2, month2, date2, hour2;
        int today_date;
        int today_hour;

        year = date.substr(2, 2);
        year2 = stoi(year);
        month = date.substr(5, 2);
        month2 = stoi(month);
        day = date.substr(8, 2);
        date2 = stoi(day);
        hour = date.substr(11, 2);
        hour2 = stoi(hour);
        today_date = year2 * 360 + 30 * month2 + date2;
        today_hour = hour2;
        for (int i = 0; i < student.size(); i++)
        {
            if (person == student[i].getname())
            {
                person_index = i;
                person_exist_flag = 1;
                break;
            }
        }
        if (person_exist_flag == 0)
        {
            add_new_member(person);
            for (int i = 0; i < student.size(); i++)
            {

                if (student[i].getname() == person)
                {
                    person_index = i;
                    person_exist_flag = 1;
                    break;
                }
            }
        }

        if (space_number < 1 || space_number > 3)
        {
            of << "8\tInvalid space id." << endl;
            return;
        }
        seat *temp = student[person_index].get_seat();
        if (temp == NULL)
        {
            of << "10\tYou did not borrow this space." << endl;
            return;
        }
        else
        {
            if (temp->get_is_empty() == false)
            {
                if (!(temp->get_borrowed_date() == today_date && temp->get_have_to_return_time() > hour2))
                {
                    of << "10\tYou did not borrow this space." << endl;
                    return;
                }
            }
            else
            {
                if (temp->get_leaving_time() != hour2)
                {
                    of << "10\tYou did not borrow this space." << endl;
                    return;
                }
            }
        }

        temp = student[person_index].get_seat();
        temp->set_is_empty(true);
        temp->set_leaving_time(hour2);
        of << "0\tSuccess." << endl;
    }
    void comback_seat(int space_number, string date, string person)
    {
        int person_index;
        int person_exist_flag = 0;
        string year;
        string month;
        string day;
        string hour;
        int year2, month2, date2, hour2;
        int today_date;
        int today_hour;

        year = date.substr(2, 2);
        year2 = stoi(year);
        month = date.substr(5, 2);
        month2 = stoi(month);
        day = date.substr(8, 2);
        date2 = stoi(day);
        hour = date.substr(11, 2);
        hour2 = stoi(hour);
        today_date = year2 * 360 + 30 * month2 + date2;
        today_hour = hour2;
        for (int i = 0; i < student.size(); i++)
        {
            if (person == student[i].getname())
            {
                person_index = i;
                person_exist_flag = 1;
                break;
            }
        }
        if (person_exist_flag == 0)
        {
            add_new_member(person);
            for (int i = 0; i < student.size(); i++)
            {

                if (student[i].getname() == person)
                {
                    person_index = i;
                    person_exist_flag = 1;
                    break;
                }
            }
        }

        if (space_number < 1 || space_number > 3)
        {
            of << "8\tInvalid space id." << endl;
            return;
        }
        seat *temp = student[person_index].get_seat();
        if (temp == NULL)
        {
            of << "10\tYou did not borrow this space." << endl;
            return;
        }
        else
        {
            if (temp->get_is_empty() == false)
            {
                if (!(temp->get_borrowed_date() == today_date && temp->get_have_to_return_time() > hour2))
                {
                    of << "10\tYou did not borrow this space." << endl;
                    return;
                }
            }
            else
            {
                if (temp->get_leaving_time() != hour2)
                {
                    of << "10\tYou did not borrow this space." << endl;
                    return;
                }
            }
        }
        temp = student[person_index].get_seat();
        temp->set_is_empty(false);
        of << "0\tSuccess." << endl;
    }
};