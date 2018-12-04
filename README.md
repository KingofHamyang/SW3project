# Making a library management system in C++

it includes 3 header files and main function

## Files

- 1. resource.h

  - there is a definition of reousrce and book class
    this class include borrowed_date, borrowed, due_date member

    **constructor** of this class set all member as a 0
    and it inlcude setter and getter method for each memeber

    **if_borrow** is the getter method of borrowed.

- 2. member.h

  - there is a definition of member and undergraduate class
    this class include borrowlimit, restruced, restricted_date, and borrowing list in vector form
    **constructor** of this class set all member as a 0
    and i include setter and getter method for each member

    **is_borrow_this** method is to find if this member borrow specific book.
    it iterate the borrowings list and find the matced resource name

    **returning_book** method is to erase the book from borrowing list.

    **borriwng** method is to append the book to the borrowing list

    **변경된 사항!!**

    - 총 빌리고있는 E_Book의 용량을 알기 위해 storage 라는 멤버를 추가하였다.
    - E_book 을 expiration 시키는 method를 추가하여, 매 E_book관련 처리마다 실행시켜 준다.
    - 추가된 resource type 별로 getter 와 setter, 빌리고 있는 여부 판단하는 메소드를 추가했다.

- 3. library.h

  - it incldues vector for student and books list, constrcutor of this class read the input source data to make a resource list and read the instructions from input.dat file and excution it

    It saves the date in integer form, **year*360 + month*30 + date**, so it needs convert_date method
    add_new member method append the new member in member lists

    **borrowing_book** method is borrwing the books and it append the book to the members status and it check each error message and print it
    first, it find the matched resource name. if it doesn't exist, print error
    Then, iterate the member lists and if there is a no matched member, append him/her to the member lists
    After that, check limitation, if borrow or not, and other error types and returns them.

    **return_the_book** method erase th book from the member's borrowing list and check the error message of it and print it
    first, it find the matched resource name. if it doesn't exist, print error
    if it delayed, calculate the `(current_date - borrowed_date)` and restricte him or her.

    **변경된 사항!!**

    - 각 오퍼레이션 별로, 멤버 타입을 검사하여 거기에 알맞는 동작을 해준다.
    - LAB에서 진행해야 했던, space 관련 오퍼레이션에 Exception Handler를 추가해주었다.

- 4. how to build?

  - using the g++ compiler, command is "g++ main.cpp"
  - if you exacute a.out, and it will make "output.dat"

* 5. space.h

  - space.h 는 seat과 study_room class 를 정의하고 있다. 각각의 클래스는 space클래스를 상속받는다.
  - space 클래스는 빌린 날짜, 빌린 반납해야 하는 날짜, 빌린 시간, 빌린 사람,빌리고 있는지에 대한 여부를 멤버로 가지며, 각 멤버별 setter 와 getter 가 있다.
  - study_room class 는 space class를 상속받는다. 각각 종료시간을 나타내기 위한 멤벼 변수들을 초기화하는 생성자가 있다.
  - seat class는 space class를 상속받는다. seat는 empty와 comeback이 있으므로, 따로 멤버를 설정해준다.
  - 각 멤버에게도 자신이 빌리고있는 스터디룸과 seat을 가리킬 수 있는 포인터 변수를 설정해주었다.

* 6. study_room 대여
  - 먼저 요청 멤버가 등록되어 있지 않다면, 멤버를 추가해준다. 잘못된 번호나, 영업 시간이 아닐 때에 빌리러 왔다면 에러를 출력한다. 빌리려고 하는 사람이 카리키는 스터디룸 포인터가 NULL이 아니고, 해당 시간이 유효하다면, 에러코드 11번을 출력한다. 빌리려고 하는 사람이 가리키는 스터디룸 포인터가 NULL 이거나 가리키고 있는 스터디룸이 저번 날짜거나, 반납시간이 훨씬 지났다면, 자동 반납 된것으로 간주하고, Success를 출력한다. 하지만 후자의 경우, 해당 스터디룸을 빌리고있던 사람을 찾아서, 그 사람의 스터디룸 포인터를 NULL로 바꿔주어야 한다. 올바른 대여 요청이면 변수들을 세팅하고, Success를 출력한다.
* 7. seat 대여
  - 영업시간과, space_id를 검사하여 옳지 않으면 에러를 출력한다. 만약 빌린적이 있거나, 자신이 빌린 자리가 아직 expire 되지 않았다면, 이미 빌리고있다는 에러를 출력한다. 만약 자리가 꽉 차있다면(층별로 세는 카운트가 50이라면) 검사해서 expire 된 자리가 있는지 확인한다. 만약 없다면, 자리가 없다라는 메세지를 출력하고, 자리가 있으면 expire 된 자리를 할당해주고, 원래 주인에 객체에 접근해서 해당 seat을 가리키는 포인터를 NULL로 만든다.
* 8. empty
  - 만약 빌린적이 없거나, 자리가 expire 됬다면, 에러코드 10을 출력한다. 아니라면, 해당 seat에 접근하여 is_empty 멤버를 true 로 바꾼다.
* 9. come back
  - 만약 빌린적이 없거나, 자리가 expire 됬다면 에러코드 10을 출력한다. empty 없이 come back이 들어오는 경우는 없으므로, 처리하지 않는다. 해당 seat에 접근하여 is_empty를 false 로 만든다.

### 기본적으로 expire에 대한 구현은 하지않았다. 어떤 장소에 대한 할당 요청이 들어올때, 그 전에 빌리고있떤 사람이 시간을 제대로 지켰는지 아닌지를 판단하여, 그 사람을 cancle하고 새로운 사람을 배정해준다.

### to_string 과 stoi같은 C++11 부터 지원되는 라이브러리를 사용했기 때문에 컴파일 옵션을 **g++ -std=c++11 main.cpp** 로 주어야 한다.

# I follwe the format in the given example files
