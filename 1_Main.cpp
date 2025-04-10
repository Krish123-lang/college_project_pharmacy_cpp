#include <iostream>
#include <string>
#include <conio.h>
using namespace std;

int i = 0;

struct Medicine
{
    string Name;
    float Price;
    int Quantity, Year, Month, Day;
} s[100];

class Authentication_Management
{
public:
    string username, password;

    void Display_Menu()
    {
        cout << "\n=============================================================" << endl;
        cout << "||\t\t    USER AUTHENTICATION                    ||" << endl;
        cout << "=============================================================" << endl;
    }

    bool login()
    {
        cout << "Enter Username: ";
        cin >> username;
        cout << "Enter Password: ";
        cin >> password;

        if ((username == "Nage" && password == "12") || (username == "Krishna" && password == "Krishna123") || (username == "Manish" && password == "Manish123") || (username == "Aarti" && password == "Aarti123"))
        {
            system("CLS");
            return true;
        }
        else
        {
            cout << "_____________________________________________________________" << endl;
            cout << "\n\t   Incorrect Username and Password...!!" << endl;
            return false;
        }
    }
};

class Inventory
{
public:
    int Option2;

    void Insert_Medicine()
    {
        system("cls");

        cout << "\n=============================================================" << endl;
        cout << "||\t\t     Insert Medicine                       ||" << endl;
        cout << "=============================================================" << endl;

        cout << " Enter Medicine Name = ";
        cin >> s[i].Name;
        
        cout << " Enter Quantity = ";
        cin >> s[i].Quantity;

        cout << " Enter Price = ";
        cin >> s[i].Price;

        cout << " Enter Expiry Date ( Year/Month/Day )" << endl;
        cout << " Enter Year  = ";
        cin >> s[i].Year;
        cout << " Enter Month = ";
        cin >> s[i].Month;
        cout << " Enter Day   = ";
        cin >> s[i].Day;

        cout << "_____________________________________________________________" << endl;
        cout << "\n\t\t Inserted Successfully...!!" << endl;
        cout << "_____________________________________________________________" << endl;

        i++;
    }

    void Update_Medicine()
    {
        system("cls");

        cout << "\n=============================================================" << endl;
        cout << "||\t\t     Update Medicine                       ||" << endl;
        cout << "=============================================================" << endl;

        if (i == 0)
        {
            cout << "\n\t\t No Record Found...!! "<<endl;
            cout << "_____________________________________________________________" << endl;
            return;
        }

        string Name;
        bool Found = false;

        cout << " Enter Medicine Name = ";
        cin >> Name;

        for (int a = 0; a < i; a++)
        {
            if (Name == s[a].Name)
            {
                cout << "Medicine Found. Enter New Details:\n";
                cout << " New Quantity = ";
                cin >> s[a].Quantity;

                cout << " New Price = ";
                cin >> s[a].Price;


                cout << " Enter New Expiry Date ( Year/Month/Day )" << endl;
                cout << " Enter New Year  = ";
                cin >> s[a].Year;
                cout << " Enter New Month = ";
                cin >> s[a].Month;
                cout << " Enter New Day   = ";
                cin >> s[a].Day;

                cout << "_____________________________________________________________" << endl;
                cout << "\n\t\t Updated Successfully...!!" << endl;
                cout << "_____________________________________________________________" << endl;
                Found = true;
                break;
            }
        }
        
        if (!Found)
        {
            cout << "_____________________________________________________________" <<endl<< endl;
            cout << " \t\tMedicine Name not found...!!" << endl;
            cout << "_____________________________________________________________" << endl;
        }
    }

    void Search_Medicine()
    {
        system("cls");

        cout << "\n=============================================================" << endl;
        cout << "||\t\t     Search Medicine                       ||" << endl;
        cout << "=============================================================" << endl;

        if (i == 0)
        {
            cout << "\n\t\t No Record Found...!! "<<endl;
            cout << "_____________________________________________________________" << endl;
            return;
        }
        
        string Name;
        bool Found = false;

        cout << " Enter Medicine Name = ";
        cin >> Name;

        for (int a = 0; a < i; a++)
        {
            if (Name == s[a].Name)
            {
                cout << "\nMedicine Found:\n";
                cout << " Name                           = " << s[a].Name << endl;
                cout << " Quantity                       = " << s[a].Quantity << endl;
                cout << " Price                          = " << s[a].Price << endl;
                cout << " Expiry Date ( Year/Month/Day ) = " << s[a].Year << "/" << s[a].Month << "/" << s[a].Day << endl;
                
                Found = true;
                break;
            }
        }
        
        if (!Found)
        {
            cout << "_____________________________________________________________"<<endl << endl;
            cout << " \t\tMedicine Name not found...!!" << endl;
            cout << "_____________________________________________________________" << endl;
        }
    }

    void Delete_Medicine()
    {
        system("cls");

        cout << "\n=============================================================" << endl;
        cout << "||\t\t     Delete Medicine                       ||" << endl;
        cout << "=============================================================" << endl;

        if (i == 0)
        {
            cout << "\n\t\t No Record Found...!! "<<endl;
            cout << "_____________________________________________________________" << endl;
            return;
        }

        string Name;
        bool Found = false;

        cout << " Enter Medicine Name = ";
        cin >> Name;

        for (int a = 0; a < i; a++)
        {
            if (s[a].Name == Name)
            {
                for (int j = a; j < i - 1; j++)
                {
                    s[j] = s[j + 1];
                }
                i--;
                cout << "_____________________________________________________________" << endl;
                cout << "\n\t\t Deleted Successfully...!!" << endl;
                cout << "_____________________________________________________________" << endl;
                Found = true;
                break;
            }
        }
        
        if (!Found)
        {
            cout << "_____________________________________________________________" << endl<<endl;
            cout << " \t\tMedicine Name not found...!!" << endl;
            cout << "_____________________________________________________________" << endl;
        }
    }
    
    void View_Medicine()
    {
        system("cls");
        
        cout << "\n=============================================================" << endl;
        cout << "||\t\t      View All Medicine                    ||" << endl;
        cout << "=============================================================" << endl;
        
        if (i == 0)
        {
            cout << "\n\t\t No Record Found...!! "<<endl;
            cout << "_____________________________________________________________" << endl;
            return;
        }
        
        for (int a = 0; a < i; a++)
        {
            cout << "\nMedicine " << a + 1 << ":" << endl;
            cout << " Name                           = " << s[a].Name << endl;
            cout << " Price                          = " << s[a].Price << endl;
            cout << " Quantity                       = " << s[a].Quantity << endl;
            cout << " Expiry Date ( Year/Month/Day ) = " << s[a].Year << "/" << s[a].Month << "/" << s[a].Day << endl;
            cout << "_____________________________________________________________" << endl;
        }
    }
    
    void Back()
    {
        system("cls");
    }
    
    void Inventory_print()
    {
        while (true)
        {
            system("cls");

            cout << "\n=============================================================" << endl;
            cout << "||\t\t    INVENTORY MANAGEMENT                   ||" << endl;
            cout << "=============================================================" << endl
                 << endl;
            cout << "  1> Insert Medicine" << endl;
            cout << "  2> Update Medicine" << endl;
            cout << "  3> Search Medicine" << endl;
            cout << "  4> Delete Medicine" << endl;
            cout << "  5> View Medicine List" << endl;
            cout << "  6> Back to Main Menu" << endl;
            cout << "_____________________________________________________________" << endl;
            cout << "  Enter your Option = ";
            cin >> Option2;
            cout << endl;

            switch (Option2)
            {
            case 1:
                Insert_Medicine();
                break;
            case 2:
                Update_Medicine();
                break;
            case 3:
                Search_Medicine();
                break;
            case 4:
                Delete_Medicine();
                break;
            case 5:
                View_Medicine();
                break;
            case 6:
                Back();
                return;
            default:
                cout << "\n Invalid Option...!!\n";
                break;
            }

            cout << "\nPress any key to go back to the Inventory Management Menu...!! ";
            getch();
        }
    }
};

class Sales_Billing
{
public:
    void sales_Billing_Print()
    {
        cout << "\n=============================================================" << endl;
        cout << "||\t      SALES AND BILLING MANAGEMENT                 ||" << endl;
        cout << "=============================================================" << endl;
    }
};

class Reports_Analysis
{
public:
    void Reports_Analysis_Print()
    {
        cout << "\n=============================================================" << endl;
        cout << "||\t      REPORT AND ANALYSIS MANAGEMENT               ||" << endl;
        cout << "=============================================================" << endl;
    }
};

class Data_Storage_Security
{
public:
    void Data_Storage_Security_Print()
    {
        cout << "\n=============================================================" << endl;
        cout << "||\t     DATA STORAGE AND SECURITY MANAGEMENT          ||" << endl;
        cout << "=============================================================" << endl;
    }
};

int main()
{
    Authentication_Management A1;
    bool Authenticated = false;
    int Attempt = 0;
    const int Max_Attempts = 5;

    while (!Authenticated && Attempt < Max_Attempts)
    {
        A1.Display_Menu();
        Authenticated = A1.login();
        Attempt++;

        if (!Authenticated && Attempt < Max_Attempts)
        {
            cout << "\t   Please try again. Attempts left: " << (Max_Attempts - Attempt) << "\n\n";
        }
    }

    if (!Authenticated)
    {
        cout << "\t   Too many failed attempts. Access denied.\n";
        return 0;
    }

    Inventory n1;
    Sales_Billing s1;
    Reports_Analysis r1;
    Data_Storage_Security d1;

    int Option1;

    while (true)
    {
        system("cls");

        cout << "\n=============================================================" << endl;
        cout << "||\t\t!!( Welcome to the System )!!              ||" << endl;
        cout << "-------------------------------------------------------------" << endl;
        cout << "||\t\t Pharmacy Management System                ||" << endl;
        cout << "||\t\t Biratnagar, Morang ( NEPAL )              ||" << endl;
        cout << "=============================================================" << endl
             << endl;
        cout << " 1> Inventory Management" << endl;
        cout << " 2> Sales and Billing Management" << endl;
        cout << " 3> Reports and Analytics Management" << endl;
        cout << " 4> Data Storage and Security" << endl;
        cout << " 5> Exit Program" << endl;
        cout << "_____________________________________________________________" << endl;
        cout << " Enter your Option = ";
        cin >> Option1;

        switch (Option1)
        {
        case 1:
            n1.Inventory_print();
            break;
        case 2:
            s1.sales_Billing_Print();
            break;
        case 3:
            r1.Reports_Analysis_Print();
            break;
        case 4:
            d1.Data_Storage_Security_Print();
            break;
        case 5:
            cout << "\n Exiting Program...!!\n";
            return 0;
        default:
            cout << "\n Invalid Option...!!\n";
            break;
        }

        cout << "\nPress any key to go back to the Main Menu...!! ";
        // return 0;
        getch();
    }

    return 0;
}