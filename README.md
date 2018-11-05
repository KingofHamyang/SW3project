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

- 4. how to build?
  - using the g++ compiler, command is "g++ main.cpp"
  - if you exacute a.out, and it will make "output.dat"

# I follwe the format in the given example files
