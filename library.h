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
    vector<faculty> professor;
    vector<graduate> grad_student;
    vector<magazine> magazines;
    vector<e_book> e_books;
    vector<book> books;

    study_room *s_room[10];
    int study_room_borrowed[10];
    seat *seat_floor[3][50];
    int seat_check[3];

    int bookcount;
    int studentcount;
    int test;
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

    library(int argc, char** argv)
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
            else if (temp == "Magazine")
            {
                fs >> temp;
                magazine *temp_magazine;
                temp_magazine = new magazine();
                temp_magazine->setname(temp);
                magazines.push_back(*temp_magazine);
            }
            else if (temp == "E-book")
            {

                fs >> temp;
                int sizeofthis = 0;
                int index_;
                cout << temp << " " << endl;
                for (int k = 0; k < temp.size(); k++)
                {
                    if (temp[k] == '[')
                    {
                        index_ = k;
                        break;
                    }
                }

                string sizing = temp.substr(index_ + 1, temp.size() - 2 - index_);
                cout << sizing << endl;
                sizeofthis = stoi(sizing);
                e_book *temp_book;
                temp_book = new e_book(sizeofthis);
                temp_book->setname(temp.substr(0, index_));
                e_books.push_back(*temp_book);
            }
        }
        print_book_list();
        print_e_book_list();
        print_magazine_list();
        
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

            if(getline(openFile, line1)){
                cout<<"good!";
            }
            else{
                cout<<"there's no data";
                book_flag = 1;
            }
            if(getline(openFile_space, line2)){
                
                cout<<"good";
            }else{
                cout<<"there's no data";
                space_flag = 1;
            }
            stringstream ss1;
            stringstream ss2;
            if(book_flag == 0) ss1.str(line1);
            if(space_flag == 0) ss2.str(line2);
            if(book_flag == 0) ss1 >> date1;
            if(space_flag == 0) ss2 >> date2;
            int cntcnt = 0;
            int Bdate;

            if(book_flag == 0) Bdate = convert_date_to_int(date1);
            int Sdate;
            if(space_flag == 0) Sdate = convert_date_to_int(date2);

            while (!(book_flag == 1 && space_flag == 1))
            {
                cout << book_flag << " " << space_flag << " " << cntcnt << endl;

                if (book_flag == 0 && space_flag == 0)
                {

                    if (Sdate < Bdate)
                    {
                        try
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
                                if (convert_date_to_int(date2) < convert_date_to_int("09/12/30"))
                                {
                                    throw 1;
                                }

                                if (!(operation == "B" || operation == "R"))
                                {
                                    throw 5;
                                }
                                if (!(membertype == "Faculty" || membertype == "Undergraduate" || membertype == "Graduate"))
                                {
                                    throw 4;
                                }
                                for (int index = 0; index < member_name.size(); index++)
                                {
                                    if (member_name[index] - '0' < 10 && member_name[index] - '0' >= 0)
                                    {
                                        throw 7;
                                    }
                                }
                                if (time_to[0] == '-')
                                {
                                    throw 8;
                                }
                                if (operation == "B")
                                {
                                    ss2 >> number_of_member;
                                    ss2 >> time_to;
                                    borrowing_study_room(space_id, date2, member_name, number_of_member, time_to, membertype);
                                }
                                else if (operation == "R")
                                {
                                    return_study_room(space_id, date2, member_name, membertype);
                                }
                                else
                                {
                                    throw 2;
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
                                if (convert_date_to_int(date2) < convert_date_to_int("09/12/30"))
                                {
                                    throw 1;
                                }

                                if (!(operation == "B" || operation == "R" || operation == "E" || operation == "C"))
                                {
                                    throw 5;
                                }
                                if (!(membertype == "Faculty" || membertype == "Undergraduate" || membertype == "Graduate"))
                                {
                                    throw 4;
                                }
                                for (int index = 0; index < member_name.size(); index++)
                                {
                                    if (member_name[index] - '0' < 10 && member_name[index] - '0' >= 0)
                                    {
                                        throw 7;
                                    }
                                }

                                if (time_to[0] == '-')
                                {
                                    throw 8;
                                }
                                if (operation == "B")
                                {
                                    ss2 >> number_of_member;
                                    ss2 >> time_to;
                                    borrowing_seat(space_id, date2, member_name, number_of_member, time_to, membertype);
                                }
                                else if (operation == "E")
                                {
                                    emptify_seat(space_id, date2, member_name, membertype);
                                }
                                else if (operation == "R")
                                {
                                    return_seat(space_id, date2, member_name, membertype);
                                }
                                else if (operation == "C")
                                {
                                    comback_seat(space_id, date2, member_name, membertype);
                                }
                                else
                                {
                                    throw 2;
                                }
                            }
                            else
                            {
                                throw 6;
                            }
                        }
                        catch (int err)
                        {
                            of << "-1\t";
                            if (err == 1)
                            {
                                of << "Date out of Range" << endl;
                            }
                            else if (err == 6)
                            {
                                of << "Non-exist space type" << endl;
                            }
                            else if (err == 5)
                            {
                                of << "Non-exist operation" << endl;
                            }
                            else if (err == 4)
                            {
                                of << "Non-exist member type" << endl;
                            }
                            else if (err == 7)
                            {
                                of << "Member name with numbers" << endl;
                            }
                            else
                            {
                                of << "Negative time" << endl;
                            }

                            if (operation == "B")
                            {
                                ss2 >> number_of_member;
                                ss2 >> time_to;
                            }
                        }
                        cntcnt++;
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

                                borrowing_book(member_name, resourcename, date1, membertype, resourcetype);
                            }
                            else if (operation == "R")
                            {
                                return_the_book(resourcename, member_name, date1, membertype, resourcetype);
                            }
                        }
                        else if (resourcetype == "Magazine")
                        {
                            ss1 >> resourcename;
                            ss1 >> operation;
                            ss1 >> membertype;
                            ss1 >> member_name;

                            fs >> temp;

                            int index_;
                            for (int k = 0; k < resourcename.size(); k++)
                            {
                                if (resourcename[k] == '[')
                                {
                                    index_ = k;
                                    break;
                                }
                            }
                            string emitted_date = resourcename.substr(index_, 7);

                            cout << space_id << " " << operation << " " << membertype << " " << member_name << " " << emitted_date << endl;
                            of << cnt << "\t";
                            cnt++;

                            if (operation == "B")
                            {
                                borrowing_magazine(member_name, resourcename.substr(0, index_), date1, membertype, resourcetype, emitted_date);
                            }
                            else if (operation == "R")
                            {
                                return_the_magazine(resourcename.substr(0, index_), member_name, date1, membertype, resourcetype, resourcename, emitted_date);
                            }
                        }
                        else if (resourcetype == "E-book")
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

                                borrowing_E_book(member_name, resourcename, date1, membertype, resourcetype);
                            }
                            else if (operation == "R")
                            {
                                return_the_E_book(resourcename, member_name, date1, membertype, resourcetype);
                            }
                        }

                        cntcnt++;
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

                            borrowing_book(member_name, resourcename, date1, membertype, resourcetype);
                        }
                        else if (operation == "R")
                        {
                            return_the_book(resourcename, member_name, date1, membertype, resourcetype);
                        }
                    }
                    else if (resourcetype == "Magazine")
                    {
                        ss1 >> resourcename;
                        ss1 >> operation;
                        ss1 >> membertype;
                        ss1 >> member_name;

                        fs >> temp;

                        int index_;
                        for (int k = 0; k < resourcename.size(); k++)
                        {
                            if (resourcename[k] == '[')
                            {
                                index_ = k;
                                break;
                            }
                        }
                        string emitted_date = resourcename.substr(index_, 7);

                        cout << space_id << " " << operation << " " << membertype << " " << member_name << emitted_date << endl;
                        of << cnt << "\t";
                        cnt++;

                        if (operation == "B")
                        {

                            borrowing_magazine(member_name, resourcename.substr(0, index_), date1, membertype, resourcetype, emitted_date);
                        }
                        else if (operation == "R")
                        {
                            return_the_magazine(resourcename.substr(0, index_), member_name, date1, membertype, resourcetype, resourcename, emitted_date);
                        }
                    }
                    else if (resourcetype == "E-book")
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

                            borrowing_E_book(member_name, resourcename, date1, membertype, resourcetype);
                        }
                        else if (operation == "R")
                        {
                            return_the_E_book(resourcename, member_name, date1, membertype, resourcetype);
                        }
                    }

                    cntcnt++;
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
                    try
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
                            if (convert_date_to_int(date2) < convert_date_to_int("09/12/30"))
                            {
                                throw 1;
                            }

                            if (!(operation == "B" || operation == "R"))
                            {
                                throw 5;
                            }
                            if (!(membertype == "Faculty" || membertype == "Undergraduate" || membertype == "Graduate"))
                            {
                                throw 4;
                            }
                            for (int index = 0; index < member_name.size(); index++)
                            {
                                if (member_name[index] - '0' < 10 && member_name[index] - '0' >= 0)
                                {
                                    throw 7;
                                }
                            }
                            if (time_to[0] == '-')
                            {
                                throw 8;
                            }
                            if (operation == "B")
                            {
                                ss2 >> number_of_member;
                                ss2 >> time_to;
                                borrowing_study_room(space_id, date2, member_name, number_of_member, time_to, membertype);
                            }
                            else if (operation == "R")
                            {
                                return_study_room(space_id, date2, member_name, membertype);
                            }
                            else
                            {
                                throw 2;
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
                            if (convert_date_to_int(date2) < convert_date_to_int("09/12/30"))
                            {
                                throw 1;
                            }

                            if (!(operation == "B" || operation == "R" || operation == "E" || operation == "C"))
                            {
                                throw 5;
                            }
                            if (!(membertype == "Faculty" || membertype == "Undergraduate" || membertype == "Graduate"))
                            {
                                throw 4;
                            }
                            for (int index = 0; index < member_name.size(); index++)
                            {
                                if (member_name[index] - '0' < 10 && member_name[index] - '0' >= 0)
                                {
                                    throw 7;
                                }
                            }
                            if (time_to[0] == '-')
                            {
                                throw 8;
                            }
                            if (operation == "B")
                            {
                                ss2 >> number_of_member;
                                ss2 >> time_to;
                                borrowing_seat(space_id, date2, member_name, number_of_member, time_to, membertype);
                            }
                            else if (operation == "E")
                            {
                                emptify_seat(space_id, date2, member_name, membertype);
                            }
                            else if (operation == "R")
                            {
                                return_seat(space_id, date2, member_name, membertype);
                            }
                            else if (operation == "C")
                            {
                                comback_seat(space_id, date2, member_name, membertype);
                            }
                            else
                            {
                                throw 2;
                            }
                        }
                        else
                        {
                            throw 6;
                        }
                    }
                    catch (int err)
                    {
                        of << "-1\t";
                        if (err == 1)
                        {
                            of << "Date out of Range" << endl;
                        }
                        else if (err == 6)
                        {
                            of << "Non-exist space type" << endl;
                        }
                        else if (err == 5)
                        {
                            of << "Non-exist operation" << endl;
                        }
                        else if (err == 4)
                        {
                            of << "Non-exist member type" << endl;
                        }
                        else if (err == 7)
                        {
                            of << "Member name with numbers" << endl;
                        }
                        else
                        {
                            of << "Negative time" << endl;
                        }
                        if (operation == "B")
                        {
                            ss2 >> number_of_member;
                            ss2 >> time_to;
                        }
                    }
                    //space get
                    cntcnt++;
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
                    openFile.close();
                    openFile_space.close();
                    break;
                }
            }
        }
        of.close();
    }
    void add_new_member(string a, string mem_type)
    {
        if (mem_type == "Undergraduate")
        {
            undergraduate *temp;
            temp = new undergraduate();
            temp->setname(a);
            student.push_back(*temp);
        }
        else if (mem_type == "Graduate")
        {
            graduate *temp;
            temp = new graduate();
            temp->setname(a);
            grad_student.push_back(*temp);
        }
        else
        {
            faculty *temp;
            temp = new faculty();
            temp->setname(a);
            professor.push_back(*temp);
        }
        return;
    }
    int findbyPersonname(string a, string type)
    {
        if (type == "Undergraduate")
        {
            for (int i = 0; i < student.size(); i++)
            {
                if (student[i].getname() == a)
                {
                    return i;
                }
            }
        }
        else if (type == "Graduate")
        {
            for (int i = 0; i < grad_student.size(); i++)
            {
                if (grad_student[i].getname() == a)
                {
                    return i;
                }
            }
        }
        else if (type == "Faculty")
        {
            for (int i = 0; i < professor.size(); i++)
            {
                if (professor[i].getname() == a)
                {
                    return i;
                }
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
    void print_e_book_list()
    {
        for (int i = 0; i < e_books.size(); i++)
        {
            string temp;
            temp = e_books[i].getname();
            cout << temp << endl;
        }
        return;
    }
    void print_magazine_list()
    {
        for (int i = 0; i < magazines.size(); i++)
        {
            string temp;
            temp = magazines[i].getname();
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

    void borrowing_study_room(int space_number, string date, string person, string n_of_member, string time2borrow, string member_type)
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

        if (member_type == "Undergraduate")
        {
            for (int i = 0; i < student.size(); i++)
            {
                if (person == student[i].getname())
                {
                    person_index = i;
                    person_exist_flag = 1;
                    break;
                }
            }
        }
        else if (member_type == "Graduate")
        {
            for (int i = 0; i < grad_student.size(); i++)
            {
                if (person == grad_student[i].getname())
                {
                    person_index = i;
                    person_exist_flag = 1;
                    break;
                }
            }
        }
        else if (member_type == "Faculty")
        {
            for (int i = 0; i < professor.size(); i++)
            {
                if (person == professor[i].getname())
                {
                    person_index = i;
                    person_exist_flag = 1;
                    break;
                }
            }
        }
        if (person_exist_flag == 0)
        {
            add_new_member(person, member_type);
            if (member_type == "Undergraduate")
            {
                for (int i = 0; i < student.size(); i++)
                {
                    if (person == student[i].getname())
                    {
                        person_index = i;
                        person_exist_flag = 1;
                        break;
                    }
                }
            }
            else if (member_type == "Graduate")
            {
                for (int i = 0; i < grad_student.size(); i++)
                {
                    if (person == grad_student[i].getname())
                    {
                        person_index = i;
                        person_exist_flag = 1;
                        break;
                    }
                }
            }
            else if (member_type == "Faculty")
            {
                for (int i = 0; i < professor.size(); i++)
                {
                    if (person == professor[i].getname())
                    {
                        person_index = i;
                        person_exist_flag = 1;
                        break;
                    }
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
        study_room *temp;
        if (member_type == "Undergraduate")
        {
            temp = student[person_index].get_s_room();
            if (temp != NULL && temp->get_borrowed_date() == today_date && temp->get_have_to_return_time() > hour2)
            {
                of << "11\tYou already borrowed this kind of space." << endl;
                return;
            }
        }
        else if (member_type == "Graduate")
        {
            temp = grad_student[person_index].get_s_room();
            if (temp != NULL && temp->get_borrowed_date() == today_date && temp->get_have_to_return_time() > hour2)
            {
                of << "11\tYou already borrowed this kind of space." << endl;
                return;
            }
        }
        else if (member_type == "Faculty")
        {
            temp = professor[person_index].get_s_room();
            if (temp != NULL && temp->get_borrowed_date() == today_date && temp->get_have_to_return_time() > hour2)
            {
                of << "11\tYou already borrowed this kind of space." << endl;
                return;
            }
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
                int origin_index = findbyPersonname(origin_person, member_type);
                if (member_type == "Undergraduate")
                {
                    student[origin_index].set_s_room(NULL);
                }
                else if (member_type == "Graduate")
                {
                    grad_student[origin_index].set_s_room(NULL);
                }
                else if (member_type == "Faculty")
                {
                    professor[origin_index].set_s_room(NULL);
                }
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
        s_room[space_number - 1]->set_borrowing_person_type(member_type);
        s_room[space_number - 1]->set_total_borrowing_person_num(numberofmem);

        if (member_type == "Undergraduate")
        {
            student[person_index].set_s_room(s_room[space_number - 1]);
        }
        else if (member_type == "Graduate")
        {
            grad_student[person_index].set_s_room(s_room[space_number - 1]);
        }
        else if (member_type == "Faculty")
        {
            professor[person_index].set_s_room(s_room[space_number - 1]);
        }
        of << "0\tSuccess." << endl;
    }
    void return_study_room(int space_number, string date, string person, string member_type)
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
        if (member_type == "Undergraduate")
        {
            for (int i = 0; i < student.size(); i++)
            {
                if (person == student[i].getname())
                {
                    person_index = i;
                    person_exist_flag = 1;
                    break;
                }
            }
        }
        else if (member_type == "Graduate")
        {
            for (int i = 0; i < grad_student.size(); i++)
            {
                if (person == grad_student[i].getname())
                {
                    person_index = i;
                    person_exist_flag = 1;
                    break;
                }
            }
        }
        else if (member_type == "Faculty")
        {
            for (int i = 0; i < professor.size(); i++)
            {
                if (person == professor[i].getname())
                {
                    person_index = i;
                    person_exist_flag = 1;
                    break;
                }
            }
        }
        if (person_exist_flag == 0)
        {
            add_new_member(person, member_type);
            if (member_type == "Undergraduate")
            {
                for (int i = 0; i < student.size(); i++)
                {
                    if (person == student[i].getname())
                    {
                        person_index = i;
                        person_exist_flag = 1;
                        break;
                    }
                }
            }
            else if (member_type == "Graduate")
            {
                for (int i = 0; i < grad_student.size(); i++)
                {
                    if (person == grad_student[i].getname())
                    {
                        person_index = i;
                        person_exist_flag = 1;
                        break;
                    }
                }
            }
            else if (member_type == "Faculty")
            {
                for (int i = 0; i < professor.size(); i++)
                {
                    if (person == professor[i].getname())
                    {
                        person_index = i;
                        person_exist_flag = 1;
                        break;
                    }
                }
            }
        }
        if (space_number < 1 || space_number > 10)
        {
            of << "8\tInvalid space id." << endl;
            return;
        }
        if (s_room[space_number - 1]->get_borrowing_person() != person || s_room[space_number - 1]->get_borrowing_person_type() != member_type)
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
        if (member_type == "Undergraduate")
        {
            student[person_index].set_s_room(NULL);
        }
        else if (member_type == "Graduate")
        {
            grad_student[person_index].set_s_room(NULL);
        }
        else if (member_type == "Faculty")
        {
            professor[person_index].set_s_room(NULL);
        }

        s_room[space_number - 1]->set_is_borrowed(false);
        s_room[space_number - 1]->set_borrowing_person("");
        s_room[space_number - 1]->set_borrowing_person_type("");
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
    void borrowing_seat(int space_number, string date, string person, string n_of_member, string time2borrow, string member_type)
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
        if (member_type == "Undergraduate")
        {
            for (int i = 0; i < student.size(); i++)
            {
                if (person == student[i].getname())
                {
                    person_index = i;
                    person_exist_flag = 1;
                    break;
                }
            }
        }
        else if (member_type == "Graduate")
        {
            for (int i = 0; i < grad_student.size(); i++)
            {
                if (person == grad_student[i].getname())
                {
                    person_index = i;
                    person_exist_flag = 1;
                    break;
                }
            }
        }
        else if (member_type == "Faculty")
        {
            for (int i = 0; i < professor.size(); i++)
            {
                if (person == professor[i].getname())
                {
                    person_index = i;
                    person_exist_flag = 1;
                    break;
                }
            }
        }
        if (person_exist_flag == 0)
        {
            add_new_member(person, member_type);
            if (member_type == "Undergraduate")
            {
                for (int i = 0; i < student.size(); i++)
                {
                    if (person == student[i].getname())
                    {
                        person_index = i;
                        person_exist_flag = 1;
                        break;
                    }
                }
            }
            else if (member_type == "Graduate")
            {
                for (int i = 0; i < grad_student.size(); i++)
                {
                    if (person == grad_student[i].getname())
                    {
                        person_index = i;
                        person_exist_flag = 1;
                        break;
                    }
                }
            }
            else if (member_type == "Faculty")
            {
                for (int i = 0; i < professor.size(); i++)
                {
                    if (person == professor[i].getname())
                    {
                        person_index = i;
                        person_exist_flag = 1;
                        break;
                    }
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
        if (member_type == "Undergraduate")
        {
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
        }
        else if (member_type == "Graduate")
        {
            seat *temp = grad_student[person_index].get_seat();
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
        }
        else if (member_type == "Faculty")
        {
            seat *temp = professor[person_index].get_seat();
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
                    if (member_type == "Undergraduate")
                    {
                        for (int j = 0; j < student.size(); j++)
                        {
                            if (student[i].getname() == seat_floor[space_number - 1][seat_to_desig]->get_borrowing_person())
                            {
                                student[i].set_seat(NULL);
                            }
                        }
                    }
                    else if (member_type == "Graduate")
                    {
                        for (int j = 0; j < grad_student.size(); j++)
                        {
                            if (grad_student[i].getname() == seat_floor[space_number - 1][seat_to_desig]->get_borrowing_person())
                            {
                                grad_student[i].set_seat(NULL);
                            }
                        }
                    }
                    else if (member_type == "Faculty")
                    {
                        for (int j = 0; j < professor.size(); j++)
                        {
                            if (professor[i].getname() == seat_floor[space_number - 1][seat_to_desig]->get_borrowing_person())
                            {
                                professor[i].set_seat(NULL);
                            }
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
        seat_floor[space_number - 1][seat_to_desig]->set_borrowing_person_type(member_type);
        seat_floor[space_number - 1][seat_to_desig]->set_have_to_return_time(hour2 + time_to_bor);
        seat_floor[space_number - 1][seat_to_desig]->set_is_empty(false);
        seat_floor[space_number - 1][seat_to_desig]->set_is_borrowed(true);
        seat_floor[space_number - 1][seat_to_desig]->set_leaving_time(0);
        seat_floor[space_number - 1][seat_to_desig]->set_borrowed_time(hour2);

        if (member_type == "Undergraduate")
        {
            student[person_index].set_seat(seat_floor[space_number - 1][seat_to_desig]);
        }
        else if (member_type == "Graduate")
        {
            grad_student[person_index].set_seat(seat_floor[space_number - 1][seat_to_desig]);
        }
        else if (member_type == "Faculty")
        {
            professor[person_index].set_seat(seat_floor[space_number - 1][seat_to_desig]);
        }
        of << "0\tSuccess." << endl;
    }

    void return_seat(int space_number, string date, string person, string member_type)
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
        if (member_type == "Undergraduate")
        {
            for (int i = 0; i < student.size(); i++)
            {
                if (person == student[i].getname())
                {
                    person_index = i;
                    person_exist_flag = 1;
                    break;
                }
            }
        }
        else if (member_type == "Graduate")
        {
            for (int i = 0; i < grad_student.size(); i++)
            {
                if (person == grad_student[i].getname())
                {
                    person_index = i;
                    person_exist_flag = 1;
                    break;
                }
            }
        }
        else if (member_type == "Faculty")
        {
            for (int i = 0; i < professor.size(); i++)
            {
                if (person == professor[i].getname())
                {
                    person_index = i;
                    person_exist_flag = 1;
                    break;
                }
            }
        }
        if (person_exist_flag == 0)
        {
            add_new_member(person, member_type);
            if (member_type == "Undergraduate")
            {
                for (int i = 0; i < student.size(); i++)
                {
                    if (person == student[i].getname())
                    {
                        person_index = i;
                        person_exist_flag = 1;
                        break;
                    }
                }
            }
            else if (member_type == "Graduate")
            {
                for (int i = 0; i < grad_student.size(); i++)
                {
                    if (person == grad_student[i].getname())
                    {
                        person_index = i;
                        person_exist_flag = 1;
                        break;
                    }
                }
            }
            else if (member_type == "Faculty")
            {
                for (int i = 0; i < professor.size(); i++)
                {
                    if (person == professor[i].getname())
                    {
                        person_index = i;
                        person_exist_flag = 1;
                        break;
                    }
                }
            }
        }
        if (space_number < 1 || space_number > 3)
        {
            of << "8\tInvalid space id." << endl;
            return;
        }

        seat *temp;
        if (member_type == "Undergraduate")
        {
            temp = student[person_index].get_seat();
            if (temp == NULL)
            {
                of << "10\tYou did not borrow this space1." << endl;
                return;
            }
        }
        else if (member_type == "Graduate")
        {
            temp = grad_student[person_index].get_seat();
            if (temp == NULL)
            {
                of << "10\tYou did not borrow this space1." << endl;
                return;
            }
        }
        else if (member_type == "Faculty")
        {
            temp = professor[person_index].get_seat();
            if (temp == NULL)
            {
                of << "10\tYou did not borrow this space1." << endl;
                return;
            }
        }

        int flag_person = 0;
        int flag_expire = 0;
        for (int i = 0; i < 50; i++)
        {
            if (seat_floor[space_number - 1][i]->get_borrowing_person() == person && seat_floor[space_number - 1][i]->get_borrowing_person_type() == member_type)
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
        if (member_type == "Undergraduate")
        {
            student[person_index].set_seat(NULL);
        }
        else if (member_type == "Graduate")
        {
            grad_student[person_index].set_seat(NULL);
        }
        else if (member_type == "Faculty")
        {
            professor[person_index].set_seat(NULL);
        }

        temp->set_is_borrowed(false);
        temp->set_borrowing_person("");
        temp->set_borrowing_person_type("");
        temp->set_is_empty(false);

        seat_check[space_number - 1]--;
        of << "0\tSuccess." << endl;
    }
    void emptify_seat(int space_number, string date, string person, string member_type)
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
        if (member_type == "Undergraduate")
        {
            for (int i = 0; i < student.size(); i++)
            {
                if (person == student[i].getname())
                {
                    person_index = i;
                    person_exist_flag = 1;
                    break;
                }
            }
        }
        else if (member_type == "Graduate")
        {
            for (int i = 0; i < grad_student.size(); i++)
            {
                if (person == grad_student[i].getname())
                {
                    person_index = i;
                    person_exist_flag = 1;
                    break;
                }
            }
        }
        else if (member_type == "Faculty")
        {
            for (int i = 0; i < professor.size(); i++)
            {
                if (person == professor[i].getname())
                {
                    person_index = i;
                    person_exist_flag = 1;
                    break;
                }
            }
        }
        if (person_exist_flag == 0)
        {
            add_new_member(person, member_type);
            if (member_type == "Undergraduate")
            {
                for (int i = 0; i < student.size(); i++)
                {
                    if (person == student[i].getname())
                    {
                        person_index = i;
                        person_exist_flag = 1;
                        break;
                    }
                }
            }
            else if (member_type == "Graduate")
            {
                for (int i = 0; i < grad_student.size(); i++)
                {
                    if (person == grad_student[i].getname())
                    {
                        person_index = i;
                        person_exist_flag = 1;
                        break;
                    }
                }
            }
            else if (member_type == "Faculty")
            {
                for (int i = 0; i < professor.size(); i++)
                {
                    if (person == professor[i].getname())
                    {
                        person_index = i;
                        person_exist_flag = 1;
                        break;
                    }
                }
            }
        }

        if (space_number < 1 || space_number > 3)
        {
            of << "8\tInvalid space id." << endl;
            return;
        }
        seat *temp;
        if (member_type == "Undergraduate")
        {
            temp = student[person_index].get_seat();
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
        }
        else if (member_type == "Graduate")
        {
            temp = grad_student[person_index].get_seat();
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
        }
        else if (member_type == "Faculty")
        {
            temp = professor[person_index].get_seat();
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
        }
        if (member_type == "Undergraduate")
        {
            temp = student[person_index].get_seat();
        }
        else if (member_type == "Graduate")
        {
            temp = grad_student[person_index].get_seat();
        }
        else if (member_type == "Faculty")
        {
            temp = professor[person_index].get_seat();
        }
        temp->set_is_empty(true);
        temp->set_leaving_time(hour2);
        of << "0\tSuccess." << endl;
    }
    void add_new_magazine(string magazine_name)
    {
        magazine *temp = new magazine();
        temp->setname(magazine_name);
        magazines.push_back(*temp);
        return;
    }
    void comback_seat(int space_number, string date, string person, string member_type)
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
        if (member_type == "Undergraduate")
        {
            for (int i = 0; i < student.size(); i++)
            {
                if (person == student[i].getname())
                {
                    person_index = i;
                    person_exist_flag = 1;
                    break;
                }
            }
        }
        else if (member_type == "Graduate")
        {
            for (int i = 0; i < grad_student.size(); i++)
            {
                if (person == grad_student[i].getname())
                {
                    person_index = i;
                    person_exist_flag = 1;
                    break;
                }
            }
        }
        else if (member_type == "Faculty")
        {
            for (int i = 0; i < professor.size(); i++)
            {
                if (person == professor[i].getname())
                {
                    person_index = i;
                    person_exist_flag = 1;
                    break;
                }
            }
        }
        if (person_exist_flag == 0)
        {
            add_new_member(person, member_type);
            if (member_type == "Undergraduate")
            {
                for (int i = 0; i < student.size(); i++)
                {
                    if (person == student[i].getname())
                    {
                        person_index = i;
                        person_exist_flag = 1;
                        break;
                    }
                }
            }
            else if (member_type == "Graduate")
            {
                for (int i = 0; i < grad_student.size(); i++)
                {
                    if (person == grad_student[i].getname())
                    {
                        person_index = i;
                        person_exist_flag = 1;
                        break;
                    }
                }
            }
            else if (member_type == "Faculty")
            {
                for (int i = 0; i < professor.size(); i++)
                {
                    if (person == professor[i].getname())
                    {
                        person_index = i;
                        person_exist_flag = 1;
                        break;
                    }
                }
            }
        }

        if (space_number < 1 || space_number > 3)
        {
            of << "8\tInvalid space id." << endl;
            return;
        }
        seat *temp;

        if (member_type == "Undergraduate")
        {
            temp = student[person_index].get_seat();
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
        }
        else if (member_type == "Graduate")
        {
            temp = grad_student[person_index].get_seat();
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
        }
        else if (member_type == "Faculty")
        {
            temp = professor[person_index].get_seat();
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
        }
        if (member_type == "Undergraduate")
        {
            temp = student[person_index].get_seat();
        }
        else if (member_type == "Graduate")
        {
            temp = grad_student[person_index].get_seat();
        }
        else if (member_type == "Faculty")
        {
            temp = professor[person_index].get_seat();
        }
        temp->set_is_empty(false);
        of << "0\tSuccess." << endl;
    }

    void borrowing_magazine(string p, string b, string date, string memeber_type, string book_type, string emitted_date)
    {
        string year;
        string month;
        string day;
        int year2, month2, date2;
        int today_date;
        string real_magazine_name = b + emitted_date;
        year = date.substr(0, 2);
        year2 = stoi(year);
        month = date.substr(3, 2);
        month2 = stoi(month);
        day = date.substr(6, 2);
        date2 = stoi(day);
        today_date = year2 * 360 + 30 * month2 + date2;

        int magazine_date;
        string y_m;
        string m_m;
        y_m = emitted_date.substr(1, 2);
        m_m = emitted_date.substr(4, 2);

        int y_m2 = stoi(y_m);
        int m_m2 = stoi(m_m);
        magazine_date = y_m2 * 360 + m_m2 * 30;

        string temp_book;
        int temp_book2;
        int temp_student2;
        int flag_Book = 0;
        int flag_person = 0;
        string temp_student;

        cout << "asdfasfasdf" << b << " " << real_magazine_name << " " << emitted_date << " " << endl;

        for (int i = 0; i < magazines.size(); i++)
        {

            temp_book = magazines[i].getname();
            cout << temp_book << " " << endl;
            if (temp_book == b)
            {
                temp_book2 = i;
                flag_Book = 1;
                break;
            }
        }
        if (memeber_type == "Undergraduate")
        {
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
        else if (memeber_type == "Graduate")
        {
            for (int i = 0; i < grad_student.size(); i++)
            {

                temp_student = grad_student[i].getname();
                if (temp_student == p)
                {
                    temp_student2 = i;
                    flag_person = 1;
                    break;
                }
            }
        }
        else
        {
            for (int i = 0; i < professor.size(); i++)
            {

                temp_student = professor[i].getname();
                if (temp_student == p)
                {
                    temp_student2 = i;
                    flag_person = 1;
                    break;
                }
            }
        }
        if (flag_Book == 0)
        {
            of << "1\tNon exist resource." << endl;
            return;
        }
        else
        {
            if (!(today_date - magazine_date <= 360 && today_date - magazine_date >= 0))
            {
                of << "1\tNon exist resource." << endl;
                return;
            }
        }
        flag_Book = 0;
        for (int i = 0; i < magazines.size(); i++)
        {

            temp_book = magazines[i].getname();

            if (temp_book == real_magazine_name)
            {
                temp_book2 = i;
                flag_Book = 1;
                break;
            }
        }
        if (flag_Book == 0)
        {
            add_new_magazine(real_magazine_name);
            for (int i = 0; i < magazines.size(); i++)
            {
                cout << temp_book << " borrow " << endl;
                temp_book = magazines[i].getname();
                //cout << temp_book << " " << endl;
                if (temp_book == real_magazine_name)
                {
                    temp_book2 = i;
                    flag_Book = 1;
                    break;
                }
            }
        }

        if (flag_person == 0)
        {
            add_new_member(p, memeber_type);
            if (memeber_type == "Undergraduate")
            {
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
            else if (memeber_type == "Graduate")
            {
                for (int i = 0; i < grad_student.size(); i++)
                {

                    temp_student = grad_student[i].getname();
                    if (temp_student == p)
                    {
                        temp_student2 = i;
                        flag_person = 1;
                        break;
                    }
                }
            }
            else
            {
                for (int i = 0; i < professor.size(); i++)
                {

                    temp_student = professor[i].getname();
                    if (temp_student == p)
                    {
                        temp_student2 = i;
                        flag_person = 1;
                        break;
                    }
                }
            }
        }
        if (memeber_type == "Undergraduate")
        {
            if (student[temp_student2].get_borrowing_magazine_cnt() + student[temp_student2].get_borrowing_book_cnt() >= 1)
            {
                of << "2\tExceeds your possible number of borrow. Possible # of borrows: " << 1 << endl;
                return;
            }
        }
        else if (memeber_type == "Graduate")
        {
            if (grad_student[temp_student2].get_borrowing_magazine_cnt() + grad_student[temp_student2].get_borrowing_book_cnt() >= 5)
            {
                of << "2\tExceeds your possible number of borrow. Possible # of borrows: " << 2 << endl;
                return;
            }
        }
        else if (memeber_type == "Faculty")
        {
            if (professor[temp_student2].get_borrowing_magazine_cnt() + professor[temp_student2].get_borrowing_book_cnt() >= 10)
            {
                of << "2\tExceeds your possible number of borrow. Possible # of borrows: " << 3 << endl;
                return;
            }
        }

        if (magazines[temp_book2].if_borrowed() == 1)
        {
            if (memeber_type == "Undergraduate")
            {
                if (student[temp_student2].is_borrow_this_magazine(real_magazine_name))
                {
                    of << "4\tYou already borrowed this magazine at" << convert_date(magazines[temp_book2].get_borrow_date()) << endl;
                    return;
                }
                else
                {
                    if (magazines[temp_book2].get_borrow_person_type() == "Undergraduate")
                        of << "5\tOther member already borrowed magazine book. This book will be returned at " << convert_date(magazines[temp_book2].get_borrow_date() + 13) << endl;
                    else if (magazines[temp_book2].get_borrow_person_type() == "Graduate")
                        of << "5\tOther member already borrowed magazine book. This book will be returned at " << convert_date(magazines[temp_book2].get_borrow_date() + 29) << endl;
                    else if (magazines[temp_book2].get_borrow_person_type() == "Faculty")
                        of << "5\tOther member already borrowed magazine book. This book will be returned at " << convert_date(magazines[temp_book2].get_borrow_date() + 29) << endl;
                    return;
                }
            }
            else if (memeber_type == "Graduate")
            {
                if (grad_student[temp_student2].is_borrow_this_magazine(real_magazine_name))
                {
                    of << "4\tYou already borrowed this magazine at" << convert_date(magazines[temp_book2].get_borrow_date()) << endl;
                    return;
                }
                else
                {
                    if (magazines[temp_book2].get_borrow_person_type() == "Undergraduate")
                        of << "5\tOther member already borrowed magazine book. This book will be returned at " << convert_date(magazines[temp_book2].get_borrow_date() + 13) << endl;
                    else if (magazines[temp_book2].get_borrow_person_type() == "Graduate")
                        of << "5\tOther member already borrowed magazine book. This book will be returned at " << convert_date(magazines[temp_book2].get_borrow_date() + 29) << endl;
                    else if (magazines[temp_book2].get_borrow_person_type() == "Faculty")
                        of << "5\tOther member already borrowed magazine book. This book will be returned at " << convert_date(magazines[temp_book2].get_borrow_date() + 29) << endl;
                    return;
                }
            }
            else if (memeber_type == "Faculty")
            {
                if (professor[temp_student2].is_borrow_this_magazine(real_magazine_name))
                {
                    of << "4\tYou already borrowed this magazine at" << convert_date(magazines[temp_book2].get_borrow_date()) << endl;
                    return;
                }
                else
                {
                    if (magazines[temp_book2].get_borrow_person_type() == "Undergraduate")
                        of << "5\tOther member already borrowed magazine book. This book will be returned at " << convert_date(magazines[temp_book2].get_borrow_date() + 13) << endl;
                    else if (magazines[temp_book2].get_borrow_person_type() == "Graduate")
                        of << "5\tOther member already borrowed magazine book. This book will be returned at " << convert_date(magazines[temp_book2].get_borrow_date() + 29) << endl;
                    else if (magazines[temp_book2].get_borrow_person_type() == "Faculty")
                        of << "5\tOther member already borrowed magazine book. This book will be returned at " << convert_date(magazines[temp_book2].get_borrow_date() + 29) << endl;
                    return;
                }
            }
        }
        if (memeber_type == "Undergraduate")
        {
            if (student[temp_student2].get_restricted() == 1)
            {
                //cout << "sdfsaf " << today_date << " " << student[temp_student2].get_restricted_date() << endl;
                if (student[temp_student2].get_restricted_date() >= today_date)
                {
                    of << "6\tRestricted member until " << convert_date(student[temp_student2].get_restricted_date()) << endl;
                    return;
                }
            }
            if (student[temp_student2].none_returned_resource(13, today_date) == true)
            {
                of << "16\tPreviously borrowed books are overdue, so borrow is limited" << endl;
                return;
            }
        }
        else if (memeber_type == "Graduate")
        {
            if (grad_student[temp_student2].get_restricted() == 1)
            {
                //cout << "sdfsaf " << today_date << " " << student[temp_student2].get_restricted_date() << endl;
                if (grad_student[temp_student2].get_restricted_date() >= today_date)
                {
                    of << "6\tRestricted member until " << convert_date(grad_student[temp_student2].get_restricted_date()) << endl;
                    return;
                }
            }
            if (grad_student[temp_student2].none_returned_resource(29, today_date) == true)
            {
                of << "16\tPreviously borrowed books are overdue, so borrow is limited" << endl;
                return;
            }
        }
        else if (memeber_type == "Faculty")
        {
            if (professor[temp_student2].get_restricted() == 1)
            {
                //cout << "sdfsaf " << today_date << " " << student[temp_student2].get_restricted_date() << endl;
                if (professor[temp_student2].get_restricted_date() >= today_date)
                {
                    of << "6\tRestricted member until " << convert_date(professor[temp_student2].get_restricted_date()) << endl;
                    return;
                }
            }
            if (professor[temp_student2].none_returned_resource(29, today_date) == true)
            {
                of << "16\tPreviously borrowed books are overdue, so borrow is limited" << endl;
                return;
            }
        }

        magazines[temp_book2].set_borrow_date(date);

        magazines[temp_book2].set_borrow_name(p);
        magazines[temp_book2].set_borrowed(1);
        if (memeber_type == "Undergraduate")
        {
            student[temp_student2].borrowing_magazines(&magazines[temp_book2]);
            magazines[temp_book2].set_borrow_person_type("Undergraduate");
        }
        else if (memeber_type == "Graduate")
        {
            grad_student[temp_student2].borrowing_magazines(&magazines[temp_book2]);
            magazines[temp_book2].set_borrow_person_type("Graduate");
        }
        else
        {
            professor[temp_student2].borrowing_magazines(&magazines[temp_book2]);
            magazines[temp_book2].set_borrow_person_type("Faculty");
        }
        of << "0\tSuccess." << endl;
    }
    void borrowing_E_book(string p, string b, string date, string memeber_type, string book_type)
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

        for (int i = 0; i < e_books.size(); i++)
        {

            temp_book = e_books[i].getname();
            if (temp_book == b)
            {
                temp_book2 = i;
                flag_Book = 1;
                break;
            }
        }
        if (memeber_type == "Undergraduate")
        {
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
        else if (memeber_type == "Graduate")
        {
            for (int i = 0; i < grad_student.size(); i++)
            {

                temp_student = grad_student[i].getname();
                if (temp_student == p)
                {
                    temp_student2 = i;
                    flag_person = 1;
                    break;
                }
            }
        }
        else
        {
            for (int i = 0; i < professor.size(); i++)
            {

                temp_student = professor[i].getname();
                if (temp_student == p)
                {
                    temp_student2 = i;
                    flag_person = 1;
                    break;
                }
            }
        }
        if (flag_Book == 0)
        {
            of << "1\tNon exist resource." << endl;
            return;
        }
        if (flag_person == 0)
        {
            add_new_member(p, memeber_type);
            if (memeber_type == "Undergraduate")
            {
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
            else if (memeber_type == "Graduate")
            {
                for (int i = 0; i < grad_student.size(); i++)
                {

                    temp_student = grad_student[i].getname();
                    if (temp_student == p)
                    {
                        temp_student2 = i;
                        flag_person = 1;
                        break;
                    }
                }
            }
            else
            {
                for (int i = 0; i < professor.size(); i++)
                {

                    temp_student = professor[i].getname();
                    if (temp_student == p)
                    {
                        temp_student2 = i;
                        flag_person = 1;
                        break;
                    }
                }
            }
        }
        if (memeber_type == "Undergraduate")
        {
            student[temp_student2].expiring_e_book(today_date, b, memeber_type);
        }
        else if (memeber_type == "Graduate")
        {
            grad_student[temp_student2].expiring_e_book(today_date, b, memeber_type);
        }
        else if (memeber_type == "Faculty")
        {
            professor[temp_student2].expiring_e_book(today_date, b, memeber_type);
        }
        /* if (memeber_type == "Undergraduate")
        {
            if (student[temp_student2].get_borrowing_e_book_cnt() == 1)
            {
                of << "2\tExceeds your possible number of borrow. Possible # of borrows: " << 1 << endl;
                return;
            }
        }
        else if (memeber_type == "Graduate")
        {
            if (grad_student[temp_student2].get_borrowing_e_book_cnt() == 5)
            {
                of << "2\tExceeds your possible number of borrow. Possible # of borrows: " << 5 << endl;
                return;
            }
        }
        else if (memeber_type == "Faculty")
        {
            if (professor[temp_student2].get_borrowing_e_book_cnt() == 10)
            {
                of << "2\tExceeds your possible number of borrow. Possible # of borrows: " << 10 << endl;
                return;
            }
        }*/

        if (memeber_type == "Undergraduate")
        {
            if (student[temp_student2].is_borrow_this_e_book(b))
            {
                of << "4\tYou already borrowed this e-book at" << convert_date(student[temp_student2].get_borrow_e_book_date(b)) << endl;
                return;
            }
        }
        else if (memeber_type == "Graduate")
        {
            if (grad_student[temp_student2].is_borrow_this_e_book(b))
            {
                of << "4\tYou already borrowed this e-book at" << convert_date(grad_student[temp_student2].get_borrow_e_book_date(b)) << endl;
                return;
            }
        }
        else if (memeber_type == "Faculty")
        {
            if (professor[temp_student2].is_borrow_this_e_book(b))
            {
                of << "4\tYou already borrowed this e-book at" << convert_date(professor[temp_student2].get_borrow_e_book_date(b)) << endl;
                return;
            }
        }

        if (memeber_type == "Undergraduate")
        {
            if (student[temp_student2].get_restricted() == 1)
            {
                //cout << "sdfsaf " << today_date << " " << student[temp_student2].get_restricted_date() << endl;
                if (student[temp_student2].get_restricted_date() >= today_date)
                {
                    of << "6\tRestricted member until " << convert_date(student[temp_student2].get_restricted_date()) << endl;
                    return;
                }
            }
        }
        else if (memeber_type == "Graduate")
        {
            if (grad_student[temp_student2].get_restricted() == 1)
            {
                //cout << "sdfsaf " << today_date << " " << student[temp_student2].get_restricted_date() << endl;
                if (grad_student[temp_student2].get_restricted_date() >= today_date)
                {
                    of << "6\tRestricted member until " << convert_date(grad_student[temp_student2].get_restricted_date()) << endl;
                    return;
                }
            }
        }
        else if (memeber_type == "Faculty")
        {
            if (professor[temp_student2].get_restricted() == 1)
            {
                //cout << "sdfsaf " << today_date << " " << student[temp_student2].get_restricted_date() << endl;
                if (professor[temp_student2].get_restricted_date() >= today_date)
                {
                    of << "6\tRestricted member until " << convert_date(professor[temp_student2].get_restricted_date()) << endl;
                    return;
                }
            }
        }
        if (memeber_type == "Undergraduate")
        {
            if (student[temp_student2].get_storage() + e_books[temp_book2].get_size() > 100)
            {
                of << "15\tExceeds your storage capacity." << endl;
                return;
            }
            else
            {
                int size_ = student[temp_student2].get_storage() + e_books[temp_book2].get_size();
                student[temp_student2].set_storage(size_);
            }

            if (student[temp_student2].none_returned_resource(13, today_date) == true)
            {
                of << "16\tPreviously borrowed books are overdue, so borrow is limited" << endl;
                return;
            }
        }
        else if (memeber_type == "Graduate")
        {
            if (grad_student[temp_student2].get_storage() + e_books[temp_book2].get_size() > 500)
            {
                of << "15\tExceeds your storage capacity." << endl;
                return;
            }
            else
            {
                int size_ = grad_student[temp_student2].get_storage() + e_books[temp_book2].get_size();
                grad_student[temp_student2].set_storage(size_);
            }
            if (grad_student[temp_student2].none_returned_resource(29, today_date) == true)
            {
                of << "16\tPreviously borrowed books are overdue, so borrow is limited" << endl;
                return;
            }
        }
        else if (memeber_type == "Faculty")
        {
            if (professor[temp_student2].get_storage() + e_books[temp_book2].get_size() > 1000)
            {
                of << "15\tExceeds your storage capacity." << endl;
                return;
            }
            else
            {
                int size_ = professor[temp_student2].get_storage() + e_books[temp_book2].get_size();
                professor[temp_student2].set_storage(size_);
            }
            if (professor[temp_student2].none_returned_resource(29, today_date) == true)
            {
                of << "16\tPreviously borrowed books are overdue, so borrow is limited" << endl;
                return;
            }
        }

        if (memeber_type == "Undergraduate")
        {
            student[temp_student2].borrowing_e_books(&e_books[temp_book2], today_date);
        }
        else if (memeber_type == "Graduate")
        {
            grad_student[temp_student2].borrowing_e_books(&e_books[temp_book2], today_date);
        }
        else if (memeber_type == "Faculty")
        {
            professor[temp_student2].borrowing_e_books(&e_books[temp_book2], today_date);
        }
        of << "0\tSuccess." << endl;
    }

    void borrowing_book(string p, string b, string date, string memeber_type, string book_type)
    {
        cout << memeber_type << endl;
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
        if (memeber_type == "Undergraduate")
        {
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
        else if (memeber_type == "Graduate")
        {
            for (int i = 0; i < grad_student.size(); i++)
            {

                temp_student = grad_student[i].getname();
                if (temp_student == p)
                {
                    temp_student2 = i;
                    flag_person = 1;
                    break;
                }
            }
        }
        else
        {
            for (int i = 0; i < professor.size(); i++)
            {

                temp_student = professor[i].getname();
                if (temp_student == p)
                {
                    temp_student2 = i;
                    flag_person = 1;
                    break;
                }
            }
        }
        if (flag_Book == 0)
        {
            of << "1\tNon exist resource." << endl;
            return;
        }
        if (flag_person == 0)
        {
            add_new_member(p, memeber_type);
            if (memeber_type == "Undergraduate")
            {
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
            else if (memeber_type == "Graduate")
            {
                for (int i = 0; i < grad_student.size(); i++)
                {

                    temp_student = grad_student[i].getname();
                    if (temp_student == p)
                    {
                        temp_student2 = i;
                        flag_person = 1;
                        break;
                    }
                }
            }
            else
            {
                for (int i = 0; i < professor.size(); i++)
                {

                    temp_student = professor[i].getname();
                    if (temp_student == p)
                    {
                        temp_student2 = i;
                        flag_person = 1;
                        break;
                    }
                }
            }
        }
        if (memeber_type == "Undergraduate")
        {
            if (student[temp_student2].get_borrowing_book_cnt() + student[temp_student2].get_borrowing_magazine_cnt() >= 1)
            {
                of << "2\tExceeds your possible number of borrow. Possible # of borrows: " << 1 << endl;
                return;
            }
        }
        else if (memeber_type == "Graduate")
        {
            if (grad_student[temp_student2].get_borrowing_book_cnt() + grad_student[temp_student2].get_borrowing_magazine_cnt() >= 5)
            {
                of << "2\tExceeds your possible number of borrow. Possible # of borrows: " << 5 << endl;
                return;
            }
        }
        else if (memeber_type == "Faculty")
        {
            if (professor[temp_student2].get_borrowing_book_cnt() + professor[temp_student2].get_borrowing_magazine_cnt() >= 10)
            {
                of << "2\tExceeds your possible number of borrow. Possible # of borrows: " << 10 << endl;
                return;
            }
        }

        if (books[temp_book2].if_borrowed() == 1)
        {
            if (memeber_type == "Undergraduate")
            {
                if (student[temp_student2].is_borrow_this(b))
                {
                    of << "4\tYou already borrowed this magazine at" << convert_date(books[temp_book2].get_borrow_date()) << endl;
                    return;
                }
                else
                {
                    if (books[temp_book2].get_borrow_person_type() == "Undergraduate")
                        of << "5\tOther member already borrowed magazine book. This book will be returned at " << convert_date(books[temp_book2].get_borrow_date() + 13) << endl;
                    else if (books[temp_book2].get_borrow_person_type() == "Graduate")
                        of << "5\tOther member already borrowed magazine book. This book will be returned at " << convert_date(books[temp_book2].get_borrow_date() + 29) << endl;
                    else if (books[temp_book2].get_borrow_person_type() == "Faculty")
                        of << "5\tOther member already borrowed magazine book. This book will be returned at " << convert_date(books[temp_book2].get_borrow_date() + 29) << endl;
                    return;
                }
            }
            else if (memeber_type == "Graduate")
            {
                if (grad_student[temp_student2].is_borrow_this(b))
                {
                    of << "4\tYou already borrowed this magazine at" << convert_date(books[temp_book2].get_borrow_date()) << endl;
                    return;
                }
                else
                {
                    if (books[temp_book2].get_borrow_person_type() == "Undergraduate")
                        of << "5\tOther member already borrowed magazine book. This book will be returned at " << convert_date(books[temp_book2].get_borrow_date() + 13) << endl;
                    else if (books[temp_book2].get_borrow_person_type() == "Graduate")
                        of << "5\tOther member already borrowed magazine book. This book will be returned at " << convert_date(books[temp_book2].get_borrow_date() + 29) << endl;
                    else if (books[temp_book2].get_borrow_person_type() == "Faculty")
                        of << "5\tOther member already borrowed magazine book. This book will be returned at " << convert_date(books[temp_book2].get_borrow_date() + 29) << endl;
                    return;
                }
            }
            else if (memeber_type == "Faculty")
            {
                if (professor[temp_student2].is_borrow_this(b))
                {
                    of << "4\tYou already borrowed this magazine at" << convert_date(books[temp_book2].get_borrow_date()) << endl;
                    return;
                }
                else
                {
                    if (books[temp_book2].get_borrow_person_type() == "Undergraduate")
                        of << "5\tOther member already borrowed magazine book. This book will be returned at " << convert_date(books[temp_book2].get_borrow_date() + 13) << endl;
                    else if (books[temp_book2].get_borrow_person_type() == "Graduate")
                        of << "5\tOther member already borrowed magazine book. This book will be returned at " << convert_date(books[temp_book2].get_borrow_date() + 29) << endl;
                    else if (books[temp_book2].get_borrow_person_type() == "Faculty")
                        of << "5\tOther member already borrowed magazine book. This book will be returned at " << convert_date(books[temp_book2].get_borrow_date() + 29) << endl;
                    return;
                }
            }
        }
        if (memeber_type == "Undergraduate")
        {
            if (student[temp_student2].get_restricted() == 1)
            {
                //cout << "sdfsaf " << today_date << " " << student[temp_student2].get_restricted_date() << endl;
                if (student[temp_student2].get_restricted_date() >= today_date)
                {
                    of << "6\tRestricted member until " << convert_date(student[temp_student2].get_restricted_date()) << endl;
                    return;
                }
            }
            if (student[temp_student2].none_returned_resource(13, today_date) == true)
            {
                of << "16\tPreviously borrowed books are overdue, so borrow is limited" << endl;
                return;
            }
        }
        else if (memeber_type == "Graduate")
        {
            if (grad_student[temp_student2].get_restricted() == 1)
            {
                //cout << "sdfsaf " << today_date << " " << student[temp_student2].get_restricted_date() << endl;
                if (grad_student[temp_student2].get_restricted_date() >= today_date)
                {
                    of << "6\tRestricted member until " << convert_date(grad_student[temp_student2].get_restricted_date()) << endl;
                    return;
                }
            }
            if (grad_student[temp_student2].none_returned_resource(29, today_date) == true)
            {
                of << "16\tPreviously borrowed books are overdue, so borrow is limited" << endl;
                return;
            }
        }
        else if (memeber_type == "Faculty")
        {
            if (professor[temp_student2].get_restricted() == 1)
            {
                //cout << "sdfsaf " << today_date << " " << student[temp_student2].get_restricted_date() << endl;
                if (professor[temp_student2].get_restricted_date() >= today_date)
                {
                    of << "6\tRestricted member until " << convert_date(professor[temp_student2].get_restricted_date()) << endl;
                    return;
                }
            }
            if (professor[temp_student2].none_returned_resource(29, today_date) == true)
            {
                of << "16\tPreviously borrowed books are overdue, so borrow is limited" << endl;
                return;
            }
        }

        books[temp_book2].set_borrow_date(date);

        books[temp_book2].set_borrow_name(p);
        books[temp_book2].set_borrowed(1);
        if (memeber_type == "Undergraduate")
        {
            student[temp_student2].borrowing(&books[temp_book2]);
            books[temp_book2].set_borrow_person_type("Undergraduate");
        }
        else if (memeber_type == "Graduate")
        {
            grad_student[temp_student2].borrowing(&books[temp_book2]);
            books[temp_book2].set_borrow_person_type("Graduate");
        }
        else
        {
            professor[temp_student2].borrowing(&books[temp_book2]);
            books[temp_book2].set_borrow_person_type("Faculty");
        }
        of << "0\tSuccess." << endl;
    }

    void return_the_E_book(string b, string p, string date, string member_type, string book_type)
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
        for (int i = 0; i < e_books.size(); i++)
        {

            temp_book = e_books[i].getname();
            if (temp_book == b)
            {
                temp_book2 = i;
                flag_Book = 1;
                break;
            }
        }
        if (member_type == "Undergraduate")
        {
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
        else if (member_type == "Graduate")
        {
            for (int i = 0; i < grad_student.size(); i++)
            {

                temp_student = grad_student[i].getname();
                if (temp_student == p)
                {
                    temp_student2 = i;
                    flag_person = 1;
                    break;
                }
            }
        }
        else if (member_type == "Faculty")
        {
            for (int i = 0; i < professor.size(); i++)
            {

                temp_student = professor[i].getname();
                if (temp_student == p)
                {
                    temp_student2 = i;
                    flag_person = 1;
                    break;
                }
            }
        }
        if (flag_Book == 0)
        {
            of << "1\tNon exist resource." << endl;
            return;
        }
        if (flag_person == 0)
        {
            add_new_member(p, member_type);
            if (member_type == "Undergraduate")
            {
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
            else if (member_type == "Graduate")
            {
                for (int i = 0; i < grad_student.size(); i++)
                {

                    temp_student = grad_student[i].getname();
                    if (temp_student == p)
                    {
                        temp_student2 = i;
                        flag_person = 1;
                        break;
                    }
                }
            }
            else if (member_type == "Faculty")
            {
                for (int i = 0; i < professor.size(); i++)
                {

                    temp_student = professor[i].getname();
                    if (temp_student == p)
                    {
                        temp_student2 = i;
                        flag_person = 1;
                        break;
                    }
                }
            }
        }

        if (member_type == "Undergraduate")
        {

            student[temp_student2].expiring_e_book(today_date, b, member_type);
        }
        else if (member_type == "Graduate")
        {
            grad_student[temp_student2].expiring_e_book(today_date, b, member_type);
        }
        else if (member_type == "Faculty")
        {
            professor[temp_student2].expiring_e_book(today_date, b, member_type);
        }

        if (member_type == "Undergraduate")
        {
            if (student[temp_student2].is_borrow_this_e_book(b) == 0)
            {
                of << "3\tYou did not borrow this book." << endl;
                return;
            }
        }
        else if (member_type == "Graduate")
        {
            if (grad_student[temp_student2].is_borrow_this_e_book(b) == 0)
            {
                of << "3\tYou did not borrow this book." << endl;
                return;
            }
        }
        else if (member_type == "Faculty")
        {
            if (professor[temp_student2].is_borrow_this_e_book(b) == 0)
            {
                of << "3\tYou did not borrow this book." << endl;
                return;
            }
        }

        if (member_type == "Undergraduate")
        {

            of << "0\tSuccess." << endl;
        }
        else if (member_type == "Graduate")
        {

            of << "0\tSuccess." << endl;
        }
        else if (member_type == "Faculty")
        {

            of << "0\tSuccess." << endl;
        }
        if (member_type == "Undergraduate")
        {
            student[temp_student2].returning_e_book(b);
        }
        else if (member_type == "Graduate")
        {
            grad_student[temp_student2].returning_e_book(b);
        }
        else if (member_type == "Faculty")
        {
            professor[temp_student2].returning_e_book(b);
        }
    }

    void return_the_magazine(string b, string p, string date, string member_type, string book_type, string real_magazine_name, string emitted_date)
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
        cout << b << " asdf" << endl;

        int magazine_date;
        string y_m;
        string m_m;
        y_m = emitted_date.substr(1, 2);
        m_m = emitted_date.substr(4, 2);

        int y_m2 = stoi(y_m);
        int m_m2 = stoi(m_m);
        magazine_date = y_m2 * 360 + m_m2 * 30;

        for (int i = 0; i < magazines.size(); i++)
        {

            temp_book = magazines[i].getname();
            cout << temp_book << endl;
            if (temp_book == b)
            {
                temp_book2 = i;
                flag_Book = 1;
                break;
            }
        }
        if (member_type == "Undergraduate")
        {
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
        else if (member_type == "Graduate")
        {
            for (int i = 0; i < grad_student.size(); i++)
            {

                temp_student = grad_student[i].getname();
                if (temp_student == p)
                {
                    temp_student2 = i;
                    flag_person = 1;
                    break;
                }
            }
        }
        else if (member_type == "Faculty")
        {
            for (int i = 0; i < professor.size(); i++)
            {

                temp_student = professor[i].getname();
                if (temp_student == p)
                {
                    temp_student2 = i;
                    flag_person = 1;
                    break;
                }
            }
        }
        if (flag_Book == 0)
        {
            of << "1\tNon exist resource." << endl;
            return;
        }
        else
        {
            if (!(today_date - magazine_date <= 360 && today_date - magazine_date >= 0))
            {
                of << "1\tNon exist resource." << endl;
                return;
            }
        }

        flag_Book = 0;
        for (int i = 0; i < magazines.size(); i++)
        {

            temp_book = magazines[i].getname();

            if (temp_book == real_magazine_name)
            {
                printf("asdfasdfasdfsadfsaf######\n");
                temp_book2 = i;
                flag_Book = 1;
                break;
            }
        }
        if (flag_Book == 0)
        {
            add_new_magazine(real_magazine_name);
            for (int i = 0; i < magazines.size(); i++)
            {
                cout << temp_book << " borrow " << endl;
                temp_book = magazines[i].getname();
                //cout << temp_book << " " << endl;
                if (temp_book == real_magazine_name)
                {
                    temp_book2 = i;
                    flag_Book = 1;
                    break;
                }
            }
        }

        if (flag_person == 0)
        {
            add_new_member(p, member_type);
            if (member_type == "Undergraduate")
            {
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
            else if (member_type == "Graduate")
            {
                for (int i = 0; i < grad_student.size(); i++)
                {

                    temp_student = grad_student[i].getname();
                    if (temp_student == p)
                    {
                        temp_student2 = i;
                        flag_person = 1;
                        break;
                    }
                }
            }
            else if (member_type == "Faculty")
            {
                for (int i = 0; i < professor.size(); i++)
                {

                    temp_student = professor[i].getname();
                    if (temp_student == p)
                    {
                        temp_student2 = i;
                        flag_person = 1;
                        break;
                    }
                }
            }
        }

        if (member_type == "Undergraduate")
        {
            if (student[temp_student2].is_borrow_this_magazine(real_magazine_name) == 0)
            {
                of << "3\tYou did not borrow this book." << endl;
                return;
            }
        }
        else if (member_type == "Graduate")
        {
            if (grad_student[temp_student2].is_borrow_this_magazine(real_magazine_name) == 0)
            {
                of << "3\tYou did not borrow this book." << endl;
                return;
            }
        }
        else if (member_type == "Faculty")
        {
            if (professor[temp_student2].is_borrow_this_magazine(real_magazine_name) == 0)
            {
                of << "3\tYou did not borrow this book." << endl;
                return;
            }
        }

        if (member_type == "Undergraduate")
        {
            if (magazines[temp_book2].get_borrow_date() + 13 < today_date)
            {
                of << "7\tDelayed return. You'll be restricted until " << convert_date(2 * today_date - (magazines[temp_book2].get_borrow_date() + 13)) << endl;
                student[temp_student2].set_restricted_date(2 * today_date - (magazines[temp_book2].get_borrow_date() + 13));
                student[temp_student2].set_restricted(1);
            }
            else
            {
                of << "0\tSuccess." << endl;
            }
        }
        else if (member_type == "Graduate")
        {
            if (magazines[temp_book2].get_borrow_date() + 29 < today_date)
            {
                of << "7\tDelayed return. You'll be restricted until " << convert_date(2 * today_date - (magazines[temp_book2].get_borrow_date() + 29)) << endl;
                grad_student[temp_student2].set_restricted_date(2 * today_date - (magazines[temp_book2].get_borrow_date() + 29));
                grad_student[temp_student2].set_restricted(1);
            }
            else
            {
                of << "0\tSuccess." << endl;
            }
        }
        else if (member_type == "Faculty")
        {
            if (magazines[temp_book2].get_borrow_date() + 29 < today_date)
            {
                of << "7\tDelayed return. You'll be restricted until " << convert_date(2 * today_date - (magazines[temp_book2].get_borrow_date() + 29)) << endl;
                professor[temp_student2].set_restricted_date(2 * today_date - (magazines[temp_book2].get_borrow_date() + 29));
                professor[temp_student2].set_restricted(1);
            }
            else
            {
                of << "0\tSuccess." << endl;
            }
        }
        if (member_type == "Undergraduate")
        {
            student[temp_student2].returning_magazine(real_magazine_name);
        }
        else if (member_type == "Graduate")
        {
            grad_student[temp_student2].returning_magazine(real_magazine_name);
        }
        else if (member_type == "Faculty")
        {
            professor[temp_student2].returning_magazine(real_magazine_name);
        }
        magazines[temp_book2].set_borrowed(0);
    }
    void return_the_book(string b, string p, string date, string member_type, string book_type)
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
        if (member_type == "Undergraduate")
        {
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
        else if (member_type == "Graduate")
        {
            for (int i = 0; i < grad_student.size(); i++)
            {

                temp_student = grad_student[i].getname();
                if (temp_student == p)
                {
                    temp_student2 = i;
                    flag_person = 1;
                    break;
                }
            }
        }
        else if (member_type == "Faculty")
        {
            for (int i = 0; i < professor.size(); i++)
            {

                temp_student = professor[i].getname();
                if (temp_student == p)
                {
                    temp_student2 = i;
                    flag_person = 1;
                    break;
                }
            }
        }
        if (flag_Book == 0)
        {
            of << "1\tNon exist resource." << endl;
            return;
        }
        if (flag_person == 0)
        {
            add_new_member(p, member_type);
            if (member_type == "Undergraduate")
            {
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
            else if (member_type == "Graduate")
            {
                for (int i = 0; i < grad_student.size(); i++)
                {

                    temp_student = grad_student[i].getname();
                    if (temp_student == p)
                    {
                        temp_student2 = i;
                        flag_person = 1;
                        break;
                    }
                }
            }
            else if (member_type == "Faculty")
            {
                for (int i = 0; i < professor.size(); i++)
                {

                    temp_student = professor[i].getname();
                    if (temp_student == p)
                    {
                        temp_student2 = i;
                        flag_person = 1;
                        break;
                    }
                }
            }
        }

        if (member_type == "Undergraduate")
        {
            if (student[temp_student2].is_borrow_this(b) == 0)
            {
                of << "3\tYou did not borrow this book." << endl;
                return;
            }
        }
        else if (member_type == "Graduate")
        {
            if (grad_student[temp_student2].is_borrow_this(b) == 0)
            {
                of << "3\tYou did not borrow this book." << endl;
                return;
            }
        }
        else if (member_type == "Faculty")
        {
            if (professor[temp_student2].is_borrow_this(b) == 0)
            {
                of << "3\tYou did not borrow this book." << endl;
                return;
            }
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
        if (member_type == "Undergraduate")
        {
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
        }
        else if (member_type == "Graduate")
        {
            if (books[temp_book2].get_borrow_date() + 29 < today_date)
            {
                of << "7\tDelayed return. You'll be restricted until " << convert_date(2 * today_date - (books[temp_book2].get_borrow_date() + 29)) << endl;
                grad_student[temp_student2].set_restricted_date(2 * today_date - (books[temp_book2].get_borrow_date() + 29));
                grad_student[temp_student2].set_restricted(1);
            }
            else
            {
                of << "0\tSuccess." << endl;
            }
        }
        else if (member_type == "Faculty")
        {
            if (books[temp_book2].get_borrow_date() + 29 < today_date)
            {
                of << "7\tDelayed return. You'll be restricted until " << convert_date(2 * today_date - (books[temp_book2].get_borrow_date() + 29)) << endl;
                professor[temp_student2].set_restricted_date(2 * today_date - (books[temp_book2].get_borrow_date() + 29));
                professor[temp_student2].set_restricted(1);
            }
            else
            {
                of << "0\tSuccess." << endl;
            }
        }
        if (member_type == "Undergraduate")
        {
            student[temp_student2].returning_book(b);
        }
        else if (member_type == "Graduate")
        {
            grad_student[temp_student2].returning_book(b);
        }
        else if (member_type == "Faculty")
        {
            professor[temp_student2].returning_book(b);
        }
        books[temp_book2].set_borrowed(0);
    }
};