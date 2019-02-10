// LIBRARY MANAGEMENT SYSTEM

//**************************************************************************************
// HEADER FILES USED IN PROJECT
//**************************************************************************************
#include<iostream>
#include<fstream>
#include<conio.h>
#include<iomanip>
#include<windows.h>
using namespace std;
//**************************************************************************************
// CLASSES USED IN PROJECT
//**************************************************************************************
class book
{
char bname[50];
char aname[20];
char bno[4];

public:
    book();
    void create_book()
    {
        cout<<" \n\n\t NEW BOOK ENTRY \n ";
        cout<<" \n\t Enter The 4 digit book no. :  ";
        cin>>bno;
        cin.ignore();
        cout<<" \n\n\t Enter The Name of The Book :  ";
        gets(bname);
        cout<<" \n\n\t Enter The Author's Name :  ";
        gets(aname);
        cout<<" \n\n\n\t Book Created. ";
    }

    void show_book()
    {
        cout<<" \n\n\t Book no.  : "<<bno;
        cout<<" \n\t Book Name : ";
        puts(bname);
        cout<<" \t Author's Name : ";
        puts(aname);
    }
    void modify_book()
    {
        cout<<" \n\n\t Book no.  : "<<bno;
        cin.ignore();
        cout<<" \n\t Modify Book Name : ";
        gets(bname);
        cout<<" \t Modify Author's Name of Book : ";
        gets(aname);
    }

    char* retbno()
    {
        return bno;
    }

    void report()
    {
        cout<<setw(17)<<bno<<setw(25)<<bname<<setw(23)<<aname<<endl;
    }

}; //END OF CLASS BOOK

class student
{
char stbno[6];
char name[20];
char admno[4];
int token;
public:
    void create_student()
    {
        system("cls");
        cout<<" \n\n\t\t NEW STUDENT ENTRY \n ";
        cout<<" \n\t\t Enter The 4 digit admission no. : ";
        cin>>admno;
        cin.ignore();
        cout<<" \n\n\t\t Enter The Name of The Student : ";
        gets(name);
        token=0;
        stbno[0]='\0';
        cout<<" \n\n\t\t Student Record Created. ";
    }

    void show_student()
    {
        cout<<" \n\t Admission no. : "<<admno;
        cout<<" \n\t Student Name  : ";
        puts(name);
        cout<<" \t Books issued  : "<<token;
        if(token==1)
           cout<<"\n\t Book no. : "<<stbno;
    }

    void modify_student()
    {
        cout<<" \n\t Admission no. : "<<admno;
        cin.ignore();
        cout<<" \n\t Modify Student Name : ";
        gets(name);
    }

    char* retadmno()
    {
        return admno;
    }

    char* retstbno()
    {
        return stbno;
    }

    int rettoken()
    {
        return token;
    }

    void addtoken()
    {
        token=1;
    }

    void resettoken()
    {
        token=0;
    }

    void getstbno(char t[])
    {
        strcpy(stbno,t);
    }

    void report()
    {
        cout<<setw(18)<<admno<<setw(24)<<name<<setw(13)<<token<<endl;
    }

}; //END OF CLASS STUDENT
//**************************************************************************************
// GLOBAL DECLARATION FOR STREAM
//**************************************************************************************
fstream fp,fp1;
book bk;
student st;
//**************************************************************************************
// FUNCTION TO WRITE IN FILE
//**************************************************************************************
void write_book()
{
    char ch;
    fp.open("book.dat",ios::out|ios::app);
    do
        {
            system("cls");
            bk.create_book();
            fp.write((char*)&bk,sizeof(book));
            cout<<" \n\n\t Do you want to add more record ? (y/n) : ";
            cin>>ch;
        }while(ch=='y'||ch=='Y');
    fp.close();
}

void write_student()
{
    char ch;
    fp.open("student.dat",ios::out|ios::app);
    do
        {
            system("cls");
            st.create_student();
            fp.write((char*)&st,sizeof(student));
            cout<<"\n\n\t\t Do you want to add more record ? (y/n) : ";
            cin>>ch;
        }while(ch=='y'||ch=='Y');
    fp.close();
}
//**************************************************************************************
// FUNCTION TO READ SPECIFIC RECORD FROM FILE
//**************************************************************************************
void display_spb(char n[])
{
    cout<<" \n\n\t BOOK DETAILS \n ";
    int flag=0;
    fp.open("book.dat",ios::in);
    while(fp.read((char*)&bk,sizeof(book)))
    {
        if(strcmpi(bk.retbno(),n)==0)
        {
            bk.show_book();
            flag=1;
        }
    }
    fp.close();
    if(flag==0)
        cout<<" \n\n\t Book does not exist !! ";
    cout<<" \n\n\n\t Press any key to continue. ";
    getch();
}

void display_sps(char n[])
{
    cout<<" \n\n\t STUDENT DETAILS \n ";
    int flag=0;
    fp.open("student.dat",ios::in);
    while(fp.read((char*)&st,sizeof(student)))
    {
        if((strcmpi(st.retadmno(),n)==0))
        {
            st.show_student();
            flag=1;
        }
    }
    fp.close();
    if(flag==0)
        cout<<" \n\n\t Student does not exist !! ";
    cout<<" \n\n\n\t Press any key to continue. ";
    getch();
}
//**************************************************************************************
// FUNCTION TO MODIFY RECORD OF FILE
//**************************************************************************************
void modify_book()
{
    char n[6];
    int found=0;
    system("cls");
    cout<<" \n\n\t MODIFY BOOK REOCORD ";
    cout<<" \n\n\t Enter The book no. : ";
    cin>>n;
    fp.open("book.dat",ios::in|ios::out);
    while(fp.read((char*)&bk,sizeof(book)) && found==0)
    {
        if(strcmpi(bk.retbno(),n)==0)
        {
            bk.show_book();
            cout<<" \n\n\t Enter the new details of the book : "<<endl;
            bk.modify_book();
            int pos=-1*sizeof(bk);
            fp.seekp(pos,ios::cur);
            fp.write((char*)&bk,sizeof(book));
            cout<<" \n\n\t Record Updated. ";
            found=1;
        }
    }
    fp.close();
    if(found==0)
        cout<<" \n\n\t Record Not Found !! ";
    cout<<" \n\n\n\t Press any key to continue. ";
    getch();
}

void modify_student()
{
    char n[4];
    int found=0;
    system("cls");
    cout<<" \n\n\t MODIFY STUDENT RECORD ";
    cout<<" \n\n\t Enter the admission no. of the Student : ";
    cin>>n;
    fp.open("student.dat",ios::in|ios::out);
    while(fp.read((char*)&st,sizeof(student)) && found==0)
    {
        if(strcmpi(st.retadmno(),n)==0)
        {
            st.show_student();
            cout<<" \n\n\t Enter the new details of Student : "<<endl;
            st.modify_student();
            int pos=-1*sizeof(st);
            fp.seekp(pos,ios::cur);
            fp.write((char*)&st,sizeof(student));
            cout<<" \n\n\t Record Updated. ";
            found=1;
        }
    }
    fp.close();
    if(found==0)
        cout<<" \n\n\t Record Not Found !! ";
    cout<<" \n\n\n\t Press any key to continue. ";
    getch();
}
//**************************************************************************************
// FUNCTION TO DELETE RECORD OF FILE
//**************************************************************************************
void delete_student()
{
    char n[4];
    int flag=0;
    system("cls");
    cout<<" \n\n\n\t DELETE STUDENT ";
    cout<<" \n\n\t Enter The admission no. of the Student : ";
    cin>>n;
    fp.open("student.dat",ios::in|ios::out);
    fstream fp2;
    fp2.open("Temp.dat",ios::out);
    fp.seekg(0,ios::beg);
    while(fp.read((char*)&st,sizeof(student)))
    {
        if(strcmpi(st.retadmno(),n)!=0)
            fp2.write((char*)&st,sizeof(student));
        else
            flag=1;
    }
    fp2.close();
    fp.close();
    remove("student.dat");
    rename("Temp.dat","student.dat");
    if(flag==1)
        cout<<" \n\n\t Record Deleted. ";
    else
        cout<<" \n\n\t Record not found !! ";
    cout<<" \n\n\n\t Press any key to continue. ";
    getch();
}

void delete_book()
{
    char n[6];
    system("cls");
    cout<<" \n\n\n\t DELETE BOOK ";
    cout<<" \n\n\t Enter The Book no. : ";
    cin>>n;
    fp.open("book.dat",ios::in|ios::out);
    fstream fp2;
    fp2.open("Temp.dat",ios::out);
    fp.seekg(0,ios::beg);
    while(fp.read((char*)&bk,sizeof(book)))
    {
        if(strcmpi(bk.retbno(),n)!=0)
        {
            fp2.write((char*)&bk,sizeof(book));
        }
    }
    fp2.close();
    fp.close();
    remove("book.dat");
    rename("Temp.dat","book.dat");
    cout<<" \n\n\t Book Deleted. ";
    cout<<" \n\n\n\t Press any key to continue. ";
    getch();
}
//**************************************************************************************
// FUNCTION TO DISPLAY ALL STUDENTS LIST
//**************************************************************************************
void display_alls()
{
    system("cls");
    fp.open("student.dat",ios::in);
    if(!fp)
    {
        cout<<"\n\n\t ERROR !!! UNABLE TO OPEN FILE ! ";
        getch();
        return;
    }
    cout<<" \n\n\t\t\t      STUDENT LIST \n\n ";
    cout<<" \t ===================================================== \n ";
    cout<<" \t  Admission No."<<setw(15)<<"Name"<<setw(25)<<"Book Issued \n";
    cout<<" \t ===================================================== \n "<<endl;
    while(fp.read((char*)&st,sizeof(student)))
    {
        st.report();
    }
    fp.close();
    cout<<" \n\n\n\t Press any key to continue. ";
    getch();
}
//**************************************************************************************
// FUNCTION TO DISPLAY BOOKS LIST
//**************************************************************************************
void display_allb()
{
    system("cls");
    fp.open("book.dat",ios::in);
    if(!fp)
    {
        cout<<" \n\n\t ERROR !!! UNABLE TO OPEN FILE ! ";
        cout<<" \n\t   Press any key to continue. ";
        getch();
        return;
    }
    cout<<" \n\n\t\t\t         BOOK LIST \n\n ";
    cout<<" \t  ======================================================== \n";
    cout<<" \t    Book No."<<setw(21)<<"Book Name"<<setw(26)<<"Author \n ";
    cout<<" \t  ======================================================== \n";
    while(fp.read((char*)&bk,sizeof(book)))
        {
            bk.report();
        }
    cout<<" \n\n\n\t Press any key to continue. ";
    fp.close();
    getch();
}
//**************************************************************************************
// FUNCTION TO ISSUE BOOK
//**************************************************************************************
void book_issue()
{
    char sn[6];
    char bn[6];
    int found=0,flag=0;
    system("cls");
    cout<<" \n\n\t BOOK ISSUE ";
    cout<<" \n\n\t Enter The student's admission no. : ";
    cin>>sn;
    fp.open("student.dat",ios::in|ios::out);
    fp1.open("book.dat",ios::in|ios::out);
    while(fp.read((char*)&st,sizeof(student)) && found==0)
    {
        if(strcmpi(st.retadmno(),sn)==0)
        {
            found=1;
            if(st.rettoken()==0)
            {
                cout<<" \n\n\t Enter the book no. : ";
                cin>>bn;
                while(fp1.read((char*)&bk,sizeof(book))&& flag==0)
                {
                    if(strcmpi(bk.retbno(),bn)==0)
                    {
                        bk.show_book();
                        flag=1;
                        st.addtoken();
                        st.getstbno(bk.retbno());
                        int pos=-1*sizeof(st);
                        fp.seekp(pos,ios::cur);
                        fp.write((char*)&st,sizeof(student));
                        cout<<" \n\n\t Book issued successfully. ";
                        cout<<" \n\n\t Please Note: Return within 15 days. ";
                        cout<<" \n\t\t      Otherwise a fine of Rs. 10 per day will ";
                        cout<<" \n\t\t      be levied after the 15 days period. ";
                    }
                }
            if(flag==0)
                cout<<" \n\t Book no. does not exist !! ";
            }
            else
                cout<<" \n\t You have not returned the last book !! ";
        }
    }
    if(found==0)
        cout<<" \n\t Student record not exist !! ";
    cout<<" \n\n\n\t Press any key to continue. ";
    getch();
    fp.close();
    fp1.close();
}
//**************************************************************************************
// FUNCTION TO DEPOSIT BOOK
//**************************************************************************************
void book_deposit()
{
    char sn[6];
    char bn[6];
    int found=0,flag=0,day,fine;
    system("cls");
    cout<<" \n\n\t BOOK DEPOSIT ";
    cout<<" \n\n\t Enter The Student's admission no. : ";
    cin>>sn;
    fp.open("student.dat",ios::in|ios::out);
    fp1.open("book.dat",ios::in|ios::out);
    while(fp.read((char*)&st,sizeof(student)) && found==0)
    {
        if(strcmpi(st.retadmno(),sn)==0)
        {
            found=1;
            if(st.rettoken()==1)
            {
                while(fp1.read((char*)&bk,sizeof(book))&& flag==0)
                {
                    if(strcmpi(bk.retbno(),st.retstbno())==0)
                    {
                        bk.show_book();
                        flag=1;
                        cout<<" \n\n\t Book deposited in no. of days : ";
                        cin>>day;
                        if(day>15)
                        {
                            fine=(day-15)*10;
                            cout<<" \n\n\t Fine has to deposited is Rs. "<<fine;
                        }
                    st.resettoken();
                    int pos=-1*sizeof(st);
                    fp.seekp(pos,ios::cur);
                    fp.write((char*)&st,sizeof(student));
                    cout<<" \n\n\t Book deposited successfully. ";
                    }
                }
                if(flag==0)
                   cout<<" \n\n\t Book no. does not exist !! ";
            }
            else
                cout<<" \n\n\t No book is issued,please check !! ";
        }
    }
    if(found==0)
        cout<<" \n\n\t Student record not exist !! ";
    cout<<" \n\n\t Press any key to continue. ";
    getch();
    fp.close();
    fp1.close();
}
//**************************************************************************************
// CONSTRUCTOR FUNCTION TO DISPLAY WELCOME MESSAGE
//**************************************************************************************
book::book()
{
    system("cls");
    cout<<" \n\n\n\n\n\n\n\n\t\t\t  LIBRARY  MANAGEMENT  SYSTEM ";
    cout<<" \n\n\n\t\t\t   Press any key to continue. ";
    getch();
}
//**************************************************************************************
// ADMINISTRATOR MENU FUNCTION
//**************************************************************************************
void admin_menu()
{

    system("cls");
    int ch,ch2,ch3;
    cout<<" \n\n\n\n\t ADMINISTRATOR MENU ";
    cout<<" \n\n\t 1. STUDENT RECORD ";
    cout<<" \n\n\t 2. BOOK RECORD ";
    cout<<" \n\n\t 3. BACK TO MAIN MENU ";
    cout<<" \n\n\t Please Enter Your Choice (1-3) :  ";
    cin>>ch;
    system("cls");
    switch(ch)
    {
        case 1:
            system("cls");
            cout<<" \n\n\n\n\t STUDENT RECORD ";
            cout<<" \n\n\t 1.CREATE STUDENT RECORD ";
            cout<<" \n\n\t 2.DISPLAY ALL STUDENTS RECORD ";
            cout<<" \n\n\t 3.DISPLAY SPECIFIC STUDENT RECORD ";
            cout<<" \n\n\t 4.MODIFY STUDENT RECORD ";
            cout<<" \n\n\t 5.DELETE STUDENT RECORD ";
            cout<<" \n\n\t Please Enter Your Choice (1-5) :  ";
            cin>>ch2;
            system("cls");
            switch(ch2)
            {
            case 1:
                write_student();
                break;
            case 2:
                display_alls();
                break;
            case 3:
                char num[6];
                cout<<" \n\n\t Please Enter The Admission No. : ";
                cin>>num;
                display_sps(num);
                break;
            case 4:
                modify_student();
                break;
            case 5:
                delete_student();
                break;
            default:
                cout<<" \n\n\n\t\t Wrong choice entered, please retry. ";
                cout<<" \n\n\n\t\t Redirecting back to Administrator Menu... ";
                Sleep(5000);
            }
            break;
        case 2:
            system("cls");
            cout<<" \n\n\n\n\t BOOK RECORD ";
            cout<<" \n\n\t 1.CREATE BOOK RECORD ";
            cout<<" \n\n\t 2.DISPLAY ALL BOOKS RECORD ";
            cout<<" \n\n\t 3.DISPLAY SPECIFIC BOOK RECORD ";
            cout<<" \n\n\t 4.MODIFY BOOK RECORD ";
            cout<<" \n\n\t 5.DELETE BOOK RECORD ";
            cout<<" \n\n\t Please Enter Your Choice (1-5) :  ";
            cin>>ch3;
            system("cls");
            switch(ch3)
            {
                case 1:
                    write_book();
                    break;
                case 2:
                    display_allb();
                    break;
                case 3:
                    char num2[6];
                    cout<<" \n\n\t Please Enter The book No. : ";
                    cin>>num2;
                    display_spb(num2);
                    break;
                case 4:
                    modify_book();
                    break;
                case 5:
                    delete_book();
                    break;
                default:
                    cout<<" \n\n\n\t\t Wrong choice entered, please retry. ";
                    cout<<" \n\n\n\t\t Redirecting back to Administrator Menu... ";
                    Sleep(5000);
            }
            break;
        case 3:
            return;
            break;
        default:
            system("cls");
            cout<<" \n\n\n\t\t Wrong choice entered, please retry. ";
            cout<<" \n\n\n\t\t Redirecting back to Administrator Menu... ";
            Sleep(5000);
    }
    admin_menu();
}
//**************************************************************************************
// THE MAIN FUNCTION OF PROGRAM
//**************************************************************************************
int main()
{
    int ch;
    do
        {
            system("cls");
            cout<<"\n\n\t MAIN MENU ";
            cout<<"\n\n\t 1. BOOK ISSUE ";
            cout<<"\n\n\t 2. BOOK DEPOSIT ";
            cout<<"\n\n\t 3. ADMINISTRATOR MENU ";
            cout<<"\n\n\t 4. EXIT ";
            cout<<"\n\n\t Please Select Your Option (1-4) :  ";
            cin>>ch;
            system("cls");
            switch(ch)
            {
                case 1:
                book_issue();
                break;
                case 2:
                book_deposit();
                break;
                case 3:
                admin_menu();
                break;
                case 4:
                cout<<" \n\n\n\n\n\n\t\t\t  LIBRARY  MANAGEMENT  SYSTEM ";
                cout<<" \n\n\n\t\t\t Thank You for using this system. ";
                cout<<" \n\n\n\t\t\t        Have a Nice Day !! ";
                cout<<" \n\n\n";
                Sleep(5000);
                exit(0);
                default :
                cout<<" \n\n\n\t\t Wrong choice entered, please retry. ";
                cout<<" \n\n\n\t\t Redirecting back to Main Menu... ";
                Sleep(5000);
            }
        }while(ch!=4);
    return 0;
}
//**************************************************************************************
// END OF PROJECT
//**************************************************************************************
