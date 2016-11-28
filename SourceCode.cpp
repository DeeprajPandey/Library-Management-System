/**
 * lib_management.cpp
 *
 * Deepraj Pandey
 * dpandey@nd.edu
 *
 * Computer project prepared for the partial fulfillment of annual practical examination, AISSCE 2017.
 * Program designed to assist user in managing records of books available in a library and the Students
 * who wish to issue books. Records can be inititated by adding information to the Student and the Book
 * directory, which are stored in binary files. Every book and Student is issued with ID numbers and changes
 * are made as and when books are issued/returned.
 */
#include <fstream>
#include <iostream>
#include <conio.h>
#include <stdio.h>
#include <process.h>
#include <string.h>
#include <iomanip>
#include <stdlib.h>
#include "windows.h"
using namespace std;
/**
 * gotooxy definition.
 */
void gotoxy(int x, int y)
{
    static HANDLE h = NULL;
    if(!h)
    {
        h = GetStdHandle(STD_OUTPUT_HANDLE);
    }

    COORD c = { x, y };
    SetConsoleCursorPosition(h,c);
}

/**
 * Stores information pertaining to a Book in the library.
 */
class Book
{
private:
    char BkId[6];
    char BkName[50];
    char AuthName[20];

public:

    // create  new instance of the class Book
    void create_Book()
    {
        cout << endl << "NEW BOOK ENTRY...\n";
        cout << endl << "Enter the Book number: ";
        cin >> BkId;
        fflush(stdin);
        fflush(stdout);
        cout << endl << endl << "Enter the Name of the Book: ";
        gets(BkName);
        fflush(stdin);
        fflush(stdout);
        cout << endl << endl << "Enter Name of the Author: ";
        gets(AuthName);
        fflush(stdin);
        fflush(stdout);
        cout << endl << endl << endl << "Book Record Created..";
    }

    // print the details of a book (accessor function)
    void show_Book()
    {
        cout << endl << "Book Number: " << BkId;
        cout << endl << "Book Name: ";
        puts(BkName);
        cout << "Author Name: ";
        puts(AuthName);
    }

    // modify the details of the book
    void modify_Book()
    {
        cout << endl << "New Book Number: ";
        cin >> BkId;
        fflush(stdin);
        fflush(stdout);
        cout << endl << "New Book Name: ";
        gets(BkName);
        fflush(stdin);
        fflush(stdout);
        cout << endl << "New Author's Name: ";
        gets(AuthName);
    }

    // returns the book number (Book ID)
    char* retBkId()
    {
        return BkId;
    }

    // print report
    void report()
    {
        fflush(stdout);
        cout << "\t" << BkId << setw(30) << BkName << setw(30) << AuthName << endl;
    }
};
// end of class Book


/**
 * Stores Student information.
 */
class Student
{
private:
    // stores the unique Id of the Student
    char AdmNo[6];

    // stores name of the Student
    char Name[20];

    // stores the Book Id of the book issues by the Student
    char IssdBkId[6];

    // container variable for number of issued books
    int token;

public:

    // creates a new instance of the class Student
    void create_Student()
    {
        //clrscr();
        cout << endl << "NEW STUDENT ENTRY...\n";
        cout << endl << "Enter The admission number: ";
        cin >> AdmNo;
        fflush(stdin);
        fflush(stdout);
        cout << endl << endl << "Enter Name of the Student: ";
        gets(Name);
        fflush(stdout);
        fflush(stdin);

        // number of books issues is initialised to 0
        token=0;
        IssdBkId[0] = ' ';
        cout << endl << endl << "Student Record Created..";
    }

    // print details pertaining to a Student record
    void show_Student()
    {
        cout << endl << "Admission number: " << AdmNo;
        cout << endl << "Name of the Student: ";
        puts(Name);
        cout << "Number of Book(s) issued: " << token;
        if (token == 1)
        {
          cout << "Book Number: " << IssdBkId;
        }
    }

    // modify Student details
    void modify_Student()
    {
        cout << endl << "New admission number: ";
        cin >> AdmNo;
        fflush(stdin);
        cout << endl << "New name of the Student: ";
        gets(Name);
        fflush(stdin);
    }

    // returns the admission number (unique Student Id)
    char* retAdmNo()
    {
        return AdmNo;
    }

    // returns the Book Id of the books issued
    char* retIssdBkId()
    {
        return IssdBkId;
    }

    // returns the number of books issued
    int rettoken()
    {
        return token;
    }

    // changes the number of books issued.
    // *imp: student can issue only 1 book at a time.
    void addtoken()
    {

        token = 1;
    }

    // resets the number of books issued
    void resettoken()
    {
        token=0;
    }

    // returns the book Id of the books issued by the Student
    void getIssdBkId(char t[])
    {
        strcpy(IssdBkId,t);
    }

    // prints report
    void report()
    {
        fflush(stdout);
        cout << "\t\t" << AdmNo << setw(25) << Name << setw(22) << token << endl;
    }

};
// end of class Student



/**
 * Global declaration for stream Objects and structure Objects
 */
fstream fp,fp1;
Book newBk;
Student newSt;


/**
 * Function to store Book records in Books.dat file.
 */
void write_Book()
{
    char ch;

    // make a binary file named Books.
    fp.open("Books.dat",ios::out|ios::app);

    do
    {
        //clrscr();
        newBk.create_Book();

        // store the collected information in Books.dat
        fp.write((char*)&newBk,sizeof(Book));

        // for the loop.
        cout << endl << endl << "Do you want to add more records? (y/n)";
        cin >> ch;
    }
    while(ch=='y'||ch=='Y');

    // close Books.dat
    fp.close();
}

/**
 * Function to store Student records in Students.dat file.
 */
void write_Student()
{
    char ch;
    fp.open("Students.dat",ios::out|ios::app);

    do
    {
        // clrscr();
        newSt.create_Student();

        // store the collected information in Students.dat
        fp.write((char*)&newSt,sizeof(Student));

        // for the loop.
        cout << endl << endl << "Do you want to add more records? (y/n)";
        cin >> ch;
    }
    while(ch=='y'||ch=='Y');

    // close Students.dat
    fp.close();
}


/**
 * Function to read Book records from Books.dat file.
 */
void display_spb(char Id[])
{
    cout << endl << "BOOK DETAILS" << endl;

    // to keep track of book status.
    int flag = 0;

    fp.open("Books.dat",ios::in);
    while(fp.read((char*)&newBk,sizeof(Book)))
    {
        if(strcmpi(newBk.retBkId(), Id) == 0)
        {
            // print book details.
            newBk.show_Book();

            // flagged 1 when book is found.
            flag = 1;
        }
    }

    fp.close();

    // when book is not found in records.
    if(flag == 0)
    {
        cout << endl << endl << "The book you are looking for does not exist. ";
        cout << "Write to our suggestion team to add this book to our library.";
    }
}

/**
 * Function to read Student records from Students.dat file.
 */
void display_sps(char adNo[])
{
    cout << endl << "STUDENT DETAILS" << endl;
    int flag = 0;
    fp.open("Students.dat",ios::in);
    while(fp.read((char*)&newSt, sizeof(Student)))
    {
        if((strcmpi(newSt.retAdmNo(), adNo) == 0))
        {
            // print student details.
            newSt.show_Student();

            // flagged 1 when student record is found.
            flag = 1;
        }
    }

    fp.close();

    // when student is not found in records.
    if(flag == 0)
    {
        cout << endl << endl << "Student of the given Admission Number does ";
        cout << "not exist in our records.";
        cout << "Contact the administration for further details.";
    }
}


/**
 * Function to modify Book records in Books.dat file.
 */
void modify_Book()
{
    char Id[6];

    // change value if book is found.
    int found = 0;
//    clrscr();
    cout << endl << endl << "\tMODIFY BOOK RECORD.... ";
    cout << endl << endl << "\tEnter the Book number of the book whose details";
    cout << " are to be modified: ";
    cin >> Id;

    fp.open("Books.dat",ios::in|ios::out);

    while(fp.read((char*)&newBk, sizeof(Book)) && found == 0)
    {
        // when input Id and book Id match.
        if(strcmpi(newBk.retBkId(), Id) == 0)
        {
            // print book details.
            newBk.show_Book();

            cout << endl << endl << "Enter the new details of the book" << endl;

            // calls the modifier function.
            newBk.modify_Book();

            int pos=-1*sizeof(newBk);
                fp.seekp(pos,ios::cur);
                fp.write((char*)&newBk, sizeof(Book));

            cout << endl << endl << "\t Record Updated";

                // when the record is found andthe details modified, set
                // the flag variable to break out of the loop.
                found = 1;
        }
    }

    // close the file.
    fp.close();

        // when book record is not found in the file.
        if(found == 0)
        {
            cout << endl << endl << "Record Not Found";
        }
}

/**
 * Function to modify Student records in Students.dat file.
 */
void modify_Student()
{
    char adNo[6];
    int found = 0;
    //clrscr();
    cout << endl << endl << "\tMODIFY STUDENT RECORD... ";
    cout << endl << endl << "\tEnter The admission number of the student whose";
    fflush(stdin);
    fflush(stdout);
    cout << " details are to be modified: ";
    cin >> adNo;

    fp.open("Students.dat",ios::in|ios::out);

    while(fp.read((char*)&newSt, sizeof(Student)) && found == 0)
    {
        // when input Id and admission number in the file match.
        if(strcmpi(newSt.retAdmNo(), adNo) == 0)
        {
            // print student details.
            newSt.show_Student();

            cout << endl << endl  << "Enter the new details of the student" << endl;

            // calls the modifier function.
            newSt.modify_Student();

            int pos=-1*sizeof(newSt);
                fp.seekp(pos,ios::cur);
                fp.write((char*)&newSt,sizeof(Student));

            cout << endl << endl << "\t Record Updated";

            // when the record is found and the details modified, set
            // the flag variable to break out of the loop.
            found = 1;
        }
    }

    // close the file.
    fp.close();

        // when student record is not found in the file.
        if(found == 0)
        {
            cout << endl << endl << " Record Not Found ";
        }
}


/**
 * Function to delete a Student record from Students.dat file.
 */
void delete_Student()
{
    char Id[6];
    int flag = 0;
    //clrscr();
    cout << endl << endl << endl << "\tDELETE STUDENT...";
    cout << endl << endl << "Enter the admission number of the student you ";
    cout << "want to delete: ";
    cin >> Id;

    fp.open("Students.dat",ios::in|ios::out);

    fstream fp2;
    fp2.open("Temp.dat",ios::out);

    fp.seekg(0,ios::beg);
    while(fp.read((char*)&newSt, sizeof(Student)))
    {
        // when the input Id and the record Id do not match.
        if(strcmpi(newSt.retAdmNo(), Id)!= 0)
        {
            // write the record into temp.dat
            fp2.write((char*)&newSt,  sizeof(Student));
        }
        else

            // flag is set to one if record is found.
            flag = 1;
    }

    fp2.close();
    fp.close();

    // delete the file Students.dat
    remove("Students.dat");

    // rename temp.dat to Students.dat
    rename("Temp.dat","Students.dat");

    // the said record is not in the new Students.dat file.
    if(flag == 1)
    {
      cout << endl << endl << "\tRecord Deleted ..";
    }
    else
    {
        // new Students.dat file is exactly the same as the previous one.
        cout << endl << endl << "Record Not Found";
    }
}

/**
 * Function to delete a Book record from Books.dat file.
 */
void delete_Book()
{
    int flag = 0;
    char Id[6];
    //clrscr();
    cout << endl << endl << endl << "\tDELETE BOOK ...";
    cout << endl << endl << "Enter the book number of the book you want to ";
    cout << "delete: ";
    cin >> Id;

    fp.open("Books.dat",ios::in|ios::out);

    fstream fp2;
    fp2.open("Temp.dat",ios::out);

    fp.seekg(0,ios::beg);
    while(fp.read((char*)&newBk, sizeof(Book)))
    {
        // when the input Id and the record Id do not match.
        if(strcmpi(newBk.retBkId(), Id)!= 0)
        {
            flag = 1;
            // write the record into temp.dat
            fp2.write((char*)&newBk,sizeof(Book));
        }
    }

    fp2.close();
    fp.close();

    // delete the file Books.dat
    remove("Books.dat");

    // rename temp.dat to Books.dat
    rename("Temp.dat","Books.dat");

    // the said record is not in the new Students.dat file.
    if(flag == 1)
    {
      cout << endl << endl << "\tRecord Deleted...";
    }
    else
    {
        // new Students.dat file is exactly the same as the previous one.
        cout << endl << endl << "Record Not Found";
    }
}


/**
 * Function to display list of all students.
 */
void disp_allSt()
{
    //clrscr();
    fp.open("Students.dat",ios::in);
    if(!fp)
    {
        cout << endl << "ERROR!!! FILE COULD NOT BE OPENED";
        return;
    }

    cout << endl << endl << "\t\tSTUDENT LIST" << endl << endl;
    cout << "============================================================================\n";
    cout << "\tAdmission Number" << setw(19) << "Name";
    cout << setw(29) << "Book(s) Issued\n";
    cout << "============================================================================\n";

    // print all records in tabular form.
    while(fp.read((char*)&newSt, sizeof(Student)))
    {
        newSt.report();
    }

    // close file.
    fp.close();
}


/**
 * Function to display list of all books.
 */
void display_allb()
{
    //clrscr();
    fp.open("Books.dat",ios::in);
    if(!fp)
    {
        cout << endl << "ERROR!!! FILE COULD NOT BE OPENED";
        return;
    }

    cout << endl << endl << "\t\tBOOK LIST" << endl << endl;
    cout << "=========================================================================\n";
    cout << "\tBook Number" << setw(23) << "Book" << setw(27) << "Author\n";
    cout << "=========================================================================\n";

    // print all records in tabular form.
    while(fp.read((char*)&newBk,sizeof(Book)))
    {
        newBk.report();
    }

    // close file.
    fp.close();
}


/**
 * Function to issue a book in the name of a particular student.
 */
void book_issuance()
{
    char stNo[6],bkNo[6];
    int found = 0;
    int flag = 0;
    //clrscr();
    cout << endl << endl << "BOOK ISSUE ...";
    cout << endl << endl << "\tEnter the student's admission number: ";
    cin >> stNo;
    fp.open("Students.dat",ios::in|ios::out);
    fp1.open("Books.dat",ios::in|ios::out);

    // search for the student in the Students.dat file.
    while(fp.read((char*)&newSt, sizeof(Student)) && found == 0)
    {
        // when the entered Student Id matches one in the record.
        if(strcmpi(newSt.retAdmNo(),stNo) == 0)
        {
            // change one of the control variables to break.
            found = 1;

            // if the number of books pending to be returned is zero.
            if(newSt.rettoken() == 0)
            {
                cout << endl << endl << "\tEnter the Book number: ";
                cin >> bkNo;

                // keep looking for the book in the Books.dat file.
                while(fp1.read((char*)&newBk,sizeof(Book))&& flag == 0)
                {
                    // when the entered Book Id matches one in the record.
                    if(strcmpi(newBk.retBkId(),bkNo) == 0)
                    {
                        // print the details of the book being issued.
                        newBk.show_Book();

                        // book is found. yay!
                        flag = 1;

                        // update the token variable to 1 before issuance.
                        newSt.addtoken();

                        // store the Book Id in the IssdBkId variable for future
                        // references.
                        newSt.getIssdBkId(newBk.retBkId());

                        int pos = -1*sizeof(newSt);
                        fp.seekp(pos,ios::cur);
                        fp.write((char*)&newSt, sizeof(Student));
                        cout << endl << endl << "\t Book issued successfully.";
                        cout << endl << endl << "\tPlease Note: Write current date ";
                        cout << "on the last page of the Book and deposit here ";
                        cout << "within 15 days. " << endl << "\tA fine of Rs. 15";
                        cout << " will be levied for each additional day delayed ";
                        cout << "after the 15-day period.";
                    }
                }

                // when the entered Id does not match with any record in the file.
                if(flag == 0)
                {
                    cout << endl << "We are sorry, the Book Id you entered was ";
                    cout << "not found in our records.";
                }
            }
            else
            {
              cout << "You have not returned the last Book you issued. ";
              cout << "The library follows a strict one book issuance policy. ";
              cout << endl << "Please return any pending books to proceed.";
            }
        }
    }
    // end of while loop for student search.

    // if control breaks out of loop without found being updated to 1, student
    // was not found.
    if(found == 0)
    {
        cout << "Student record does not exist...";
    }

    // Students.dat file is closed.
    fp.close();

    // Books.dat file is closed.
    fp1.close();
}

/**
 * Function to return book issued by a student.
 */
void book_deposition()
{
    char stNo[6],bkNo[6];
    int found=0,flag=0,day,fine;
    //clrscr();
    cout << endl << endl << "BOOK DEPOSIT";
    cout << endl << endl << "\tEnter the student's admission number: ";
    cin >> stNo;
    cout << endl << endl << "\tEnter the Book Id of the book to be returned: ";
    cin >> bkNo;

    fp.open("Students.dat",ios::in|ios::out);
    fp1.open("Books.dat",ios::in|ios::out);

    // search for the Student in the Students.dat file.
    while(fp.read((char*)&newSt,sizeof(Student)) && found == 0)
    {
        // when the entered Student Id matches one in the record.
        if(strcmpi(newSt.retAdmNo(), stNo) == 0)
        {
            // update control variable.
            found = 1;

            /**
             * Check if the person here to return the book is in fact here for
             * the business (s)he is saying (s)he is here for and the book was
             * really issued in that student's name.
             *
             * you know, just in case...
             */
            if(newSt.rettoken() == 1)
            {
                // keep looking for the book in the Books.dat file
                while(fp1.read((char*)&newBk,sizeof(Book))&& flag == 0)
                {
                    // when the book is found.
                    if(strcmpi(newBk.retBkId(),newSt.retIssdBkId()) == 0)
                    {
                        // print the book details.
                        newBk.show_Book();

                        // update loop control variable.
                        flag = 1;
                        cout << endl << endl << "Number of days book has been deposited after: ";
                        cin >> day;

                        // calculate fine, if book is returned after 15 days.
                        if(day > 15)
                        {
                            fine = (day - 15) * 15;
                            cout << endl << endl << "\tYou have lapsed the free return ";
                            cout << "period." << endl << "\tFine to be paid is Rs. " << fine;
                        }

                        // reset the variable storing the number of books issued by the student.
                        newSt.resettoken();

                        int pos=-1*sizeof(newSt);
                        fp.seekp(pos,ios::cur);
                        fp.write((char*)&newSt,sizeof(Student));
                        cout << endl << endl << "\tBook deposited.";
                    }
                }

                // if flag has not been updated to 1, book was not found.
                if(flag == 0)
                cout << "Entered book number does not exist...";
            }
            else
            {
                cout << "No book has been issued under this student's name, recheck.";
            }
        }
    }

    // if control breaks out of loop without found being updated to 1, student
    // was not found.
    if(found == 0)
    {
        cout << "Student record does not exist...";
    }

    // Students.dat file is closed.
    fp.close();

    // Books.dat file is closed.
    fp1.close();
}


/**
 * Introduction.
 */
void intro()
{
    //clrscr();
    gotoxy(10,11);
    cout << "LIBRARY";
    gotoxy(17,14);
    cout << "MANAGEMENT";
    gotoxy(24,17);
    cout << "SYSTEM";
    cout << endl << endl << "Developed By: Deepraj Pandey";
    cout << endl << endl << "Class XII - C";
    cout << endl << "D.A.V. Public School, Pokhariput" << endl;
}


/**
 * Administrator Menu.
 */
void admin_menu()
{
    //clrscr();
    int ch2;
    cout << "\n\n\n\tADMINISTRATOR MENU";
    cout << "\n\n\t1.Create New Student Record";
    cout << setw(55) << "6.Create a Book Record";

    cout << "\n\n\t2.Display Library Records of All the Students";
    cout << setw(45) << "7.Display Records of All Books";

    cout << "\n\n\t3.Display Details of a Specific Student";
    cout << setw(57) << "8.Display Details of a Specific Book";

    cout << "\n\n\t4.Modify a Student Record";
    cout << setw(57) << "9.Modify a Book Record";

    cout << "\n\n\t5.Delete a Student Record";
    cout << setw(58) << "10.Delete a Book Record";

    cout << "\n\n\t\t\t\t\t11.Go Back to Main Menu";
    cout << "\n\n\tPlease Enter Your Choice (1-11) ";
    cin >> ch2;
    switch(ch2)
    {
            case 1: //clrscr();
                  write_Student();break;
            case 2:
                   disp_allSt();break;
            case 3:
                   char num[6];
                   //clrscr();
                   cout << "\n\n\tPlease Enter The Admission No. ";
                   cin >> num;
                   display_sps(num);
                   break;
            case 4:
                   modify_Student();break;
            case 5:
                   delete_Student();break;
            case 6:
                   //clrscr();
                   write_Book();break;
            case 7:
                   display_allb();break;
            case 8:
                {
                    char num[6];
                   //clrscr();
                   cout << "\n\n\tPlease Enter The Book No. ";
                   cin >> num;
                   display_spb(num);
                   break;
                }
            case 9:
                   modify_Book();break;
            case 10:
                    delete_Book();break;
            case 11:
                    return;

            default:cout << "\a";
    }

    admin_menu();
}


/**
 * main()
 */
int main(void)
{
    char ch;
    intro();
    do
    {
        //clrscr();
        cout << "\n\n\n\tMAIN MENU";
        cout << "\n\n\t01. Issue Book(s)";
        cout << "\n\n\t02. Deposit Book(s)";
        cout << "\n\n\t03. Administrator Menu";
        cout << "\n\n\t04. Exit";
        cout << "\n\n\tPlease Select Your Option (1-4) ";
        ch = getch();

        switch(ch)
        {
            case '1':
                     //clrscr();
                     book_issuance();
                     break;
            case '2':
                     book_deposition();
                     break;
            case '3':
                     admin_menu();
                     break;
            case '4':
                     exit(1);

            default : cout << "\a";
        }
    }
    while(ch!='4');

return 0;
}
/**
 * End of Project. Now please let me sleep!!!
 */
