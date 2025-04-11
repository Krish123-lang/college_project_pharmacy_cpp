#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
using namespace std;

int i = 0;

struct Medicine
{
    string Name;
    float Price;
    int Quantity, Year, Month, Day;
} s[100];

void clearConsole()
{
    #ifdef _WIN32
        std::system("cls");
    #else
        std::system("clear");
    #endif
}

void Load_Data()
{
    ifstream file("medicine_data.csv");
    if (file.is_open())
    {
        i = 0; // Reset the index
        string line;
        getline(file, line); // Skip the header line

        while (getline(file, line))
        {
            stringstream ss(line);
            string token;

            getline(ss, s[i].Name, ',');
            getline(ss, token, ',');
            s[i].Quantity = stoi(token);
            getline(ss, token, ',');
            s[i].Price = stof(token);
            getline(ss, token, '/');
            s[i].Year = stoi(token);
            getline(ss, token, '/');
            s[i].Month = stoi(token);
            getline(ss, token, ',');
            s[i].Day = stoi(token);

            i++;
        }
        file.close();
    }
    else
    {
        cout << "Error: Unable to open file for reading.\n";
    }
}

void Save_Data()
{
    ofstream file("medicine_data.csv");
    if (file.is_open())
    {
        // Write the header
        file << "Name,Quantity,Price,Expiry Date\n";

        // Write the medicine data
        for (int a = 0; a < i; a++)
        {
            file << s[a].Name << "," << s[a].Quantity << "," << s[a].Price << ","
                 << s[a].Year << "/" << s[a].Month << "/" << s[a].Day << "\n";
        }
        file.close();
    }
    else
    {
        cout << "Error: Unable to open file for writing.\n";
    }
}

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

            clearConsole();

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
        clearConsole();

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

        // Check if the file exists
        ifstream checkFile("medicine_data.csv");
        bool fileExists = checkFile.good();
        checkFile.close();

        // Write the data to a CSV file
        ofstream file("medicine_data.csv", ios::app); // Open in append mode
        if (file.is_open())
        {
            // Add column headers if the file is being created for the first time
            if (!fileExists)
            {
                file << "Name,Quantity,Price,Expiry Date\n";
            }

            // Write the medicine data
            file << s[i].Name << "," << s[i].Quantity << "," << s[i].Price << ","
                << s[i].Year << "/" << s[i].Month << "/" << s[i].Day << "\n";
            file.close();
        }
        else
        {
            cout << "Error: Unable to open file for writing.\n";
        }

        // cin.ignore(); // Clear the input buffer

        cout << "_____________________________________________________________" << endl;
        cout << "\n\t\t Inserted Successfully...!!" << endl;
        cout << "_____________________________________________________________" << endl;
        i++;

        cout << "\nPress Enter to return to the Main Menu... ";
        cin.ignore();
        cin.get();
    }

    void Update_Medicine()
    {
        Load_Data(); // Load data from the CSV file

        clearConsole();

        cout << "\n=============================================================" << endl;
        cout << "||\t\t     Update Medicine                       ||" << endl;
        cout << "=============================================================" << endl;

        if (i == 0)
        {
            cout << "\n\t\t No Record Found...!! " << endl;
            cout << "_____________________________________________________________" << endl;

            cout << "\nPress Enter to return to the Main Menu... ";
            cin.ignore();
            cin.get();

            return;
        }

        string Name;
        bool Found = false;

        cout << " Enter Medicine Name = ";
        cin.ignore();
        getline(cin, Name);

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

                Found = true;
                break;
            }
        }

        if (Found)
        {
            Save_Data(); // Save the updated data back to the CSV file

            cout << "_____________________________________________________________" << endl;
            cout << "\n\t\t Updated Successfully...!!" << endl;
            cout << "_____________________________________________________________" << endl;
        }
        else
        {
            cout << "_____________________________________________________________" << endl
                 << endl;
            cout << " \t\tMedicine Name not found...!!" << endl;
            cout << "_____________________________________________________________" << endl;
        }

        cout << "\nPress Enter to return to the Inventory Management Menu... ";
        cin.ignore();
        cin.get();
    }

    void Search_Medicine()
    {
        Load_Data(); // Load data from the CSV file

        clearConsole();

        cout << "\n=============================================================" << endl;
        cout << "||\t\t     Search Medicine                       ||" << endl;
        cout << "=============================================================" << endl;

        if (i == 0)
        {
            cout << "\n\t\t No Record Found...!! " << endl;
            cout << "_____________________________________________________________" << endl;

            cout << "\nPress Enter to return to the Main Menu... ";
            cin.ignore();
            cin.get();

            return;
        }

        string Name;
        bool Found = false;

        cout << " Enter Medicine Name = ";
        cin.ignore();
        getline(cin, Name);

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
            cout << "_____________________________________________________________" << endl
                 << endl;
            cout << " \t\tMedicine Name not found...!!" << endl;
            cout << "_____________________________________________________________" << endl;
        }

        cout << "\nPress Enter to return to the Inventory Management Menu... ";
        // cin.ignore();
        cin.get();
    }

    void Delete_Medicine()
    {
        Load_Data(); // Load data from the CSV file

        clearConsole();

        cout << "\n=============================================================" << endl;
        cout << "||\t\t     Delete Medicine                       ||" << endl;
        cout << "=============================================================" << endl;

        if (i == 0)
        {
            cout << "\n\t\t No Record Found...!! " << endl;
            cout << "_____________________________________________________________" << endl;

            cout << "\nPress Enter to return to the Main Menu... ";
            cin.ignore();
            cin.get();

            return;
        }

        string Name;
        bool Found = false;

        cout << " Enter Medicine Name = ";
        cin.ignore();
        getline(cin, Name);

        for (int a = 0; a < i; a++)
        {
            if (s[a].Name == Name)
            {
                for (int j = a; j < i - 1; j++)
                {
                    s[j] = s[j + 1];
                }
                i--;
                Found = true;
                break;
            }
        }

        if (Found)
        {
            Save_Data(); // Save the updated data back to the CSV file

            cout << "_____________________________________________________________" << endl;
            cout << "\n\t\t Deleted Successfully...!!" << endl;
            cout << "_____________________________________________________________" << endl;
        }
        else
        {
            cout << "_____________________________________________________________" << endl
                 << endl;
            cout << " \t\tMedicine Name not found...!!" << endl;
            cout << "_____________________________________________________________" << endl;
        }

        cout << "\nPress Enter to return to the Inventory Management Menu... ";
        // cin.ignore();
        cin.get();
    }
    
    void View_Medicine()
    {
        Load_Data(); // Load data from the CSV file

        clearConsole();

        cout << "\n=============================================================" << endl;
        cout << "||\t\t      View All Medicine                    ||" << endl;
        cout << "=============================================================" << endl;

        if (i == 0)
        {
            cout << "\n\t\t No Record Found...!! " << endl;
            cout << "_____________________________________________________________" << endl;

            cout << "\nPress Enter to return to the Main Menu... ";
            cin.ignore();
            cin.get();

            return;
        }

        for (int a = 0; a < i; a++)
        {
            cout << "\nMedicine " << a + 1 << ":" << endl;
            cout << " Name                           = " << s[a].Name << endl;
            cout << " Quantity                       = " << s[a].Quantity << endl;
            cout << " Price                          = " << s[a].Price << endl;
            cout << " Expiry Date ( Year/Month/Day ) = " << s[a].Year << "/" << s[a].Month << "/" << s[a].Day << endl;
            cout << "_____________________________________________________________" << endl;
        }

        cout << "\nPress Enter to return to the Inventory Management Menu... ";
        cin.ignore();
        cin.get();
    }
    
    void Back()
    {
        clearConsole();
    }
    
    void Inventory_print()
    {
        while (true)
        {
            clearConsole();

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
            // getch();
        }
    }
};

class Sales_Billing
{
private:
    struct BillItem
    {
        string Name;
        int Quantity;
        float Price;
        float TotalPrice;
    };

    vector<BillItem> billItems; // Temporary storage for items in the bill
    float totalAmount = 0.0;

public:
    void Add_Item()
    {
        clearConsole();

        cout << "\n=============================================================" << endl;
        cout << "||\t\t     Add Item to Bill                      ||" << endl;
        cout << "=============================================================" << endl;

        Load_Data(); // Load inventory data

        if (i == 0)
        {
            cout << "\n\t\t No Inventory Data Found...!! " << endl;
            cout << "_____________________________________________________________" << endl;

            cout << "\nPress Enter to return to the Main Menu... ";
            cin.ignore();
            cin.get();
            return;
        }

        string itemName;
        int quantity;
        bool found = false;

        cout << " Enter Item Name = ";
        cin.ignore();
        getline(cin, itemName);

        for (int a = 0; a < i; a++)
        {
            if (s[a].Name == itemName)
            {
                found = true;

                cout << " Enter Quantity = ";
                cin >> quantity;

                if (quantity > s[a].Quantity)
                {
                    cout << "\n Not enough stock available. Available Quantity = " << s[a].Quantity << endl;
                    cin.ignore();
                    cin.get();

                    return;
                }

                // Add item to the bill
                BillItem newItem;
                newItem.Name = s[a].Name;
                newItem.Quantity = quantity;
                newItem.Price = s[a].Price;
                newItem.TotalPrice = quantity * s[a].Price;
                billItems.push_back(newItem);

                // Update inventory
                s[a].Quantity -= quantity;

                // Update total amount
                totalAmount += newItem.TotalPrice;

                cout << "\n Item added to the bill successfully!" << endl;
                cin.get();
                break;
            }
        }

        if (!found)
        {
            cout << "\n Item not found in inventory!" << endl;
        }

        Save_Data(); // Save updated inventory data

        cout << "\nPress Enter to return to the Sales and Billing Menu... ";
        // cin.ignore();
        cin.get();
    }

    void Display_Bill()
    {
        clearConsole();

        cout << "\n=============================================================" << endl;
        cout << "||\t\t     Sales Bill                          ||" << endl;
        cout << "=============================================================" << endl;

        if (billItems.empty())
        {
            cout << "\n\t\t No items in the bill...!! " << endl;
            cout << "_____________________________________________________________" << endl;

            cout << "\nPress Enter to return to the Sales and Billing Menu... ";
            cin.ignore();
            cin.get();
            return;
        }

        cout << " Item Name\tQuantity\tPrice\tTotal Price" << endl;
        cout << "-------------------------------------------------------------" << endl;

        for (const auto &item : billItems)
        {
            cout << " " << item.Name << "\t\t" << item.Quantity << "\t\t" << item.Price << "\t" << item.TotalPrice << endl;
        }

        cout << "-------------------------------------------------------------" << endl;
        cout << " Total Amount: " << totalAmount << endl;

        cout << "\nPress Enter to return to the Sales and Billing Menu... ";
        cin.ignore();
        cin.get();
    }

    void Save_Bill()
    {
        clearConsole();

        cout << "\n=============================================================" << endl;
        cout << "||\t\t     Save Bill to File                    ||" << endl;
        cout << "=============================================================" << endl;

        if (billItems.empty())
        {
            cout << "\n\t\t No items in the bill to save...!! " << endl;
            cout << "_____________________________________________________________" << endl;

            cout << "\nPress Enter to return to the Sales and Billing Menu... ";
            cin.ignore();
            cin.get();
            return;
        }

        // Open the CSV file in append mode
        ofstream file("sales_bills.csv", ios::app);
        if (file.is_open())
        {
            // Write the header if the file is empty
            if (file.tellp() == 0) // Check if the file is empty
            {
                file << "Item Name,Quantity,Price,Total Price\n";
            }

            // Write the bill items
            for (const auto &item : billItems)
            {
                file << item.Name << "," << item.Quantity << "," << item.Price << "," << item.TotalPrice << "\n";
            }

            // Write the total amount
            file << "Total Amount,,," << totalAmount << "\n";

            file.close();

            cout << "\n Bill saved successfully to 'sales_bills.csv'!" << endl;
        }
        else
        {
            cout << "\n Error: Unable to save the bill to file!" << endl;
        }

        cout << "\nPress Enter to return to the Sales and Billing Menu... ";
        cin.ignore();
        cin.get();
    }

    void Sales_Billing_Menu()
    {
        int option;

        while (true)
        {
            clearConsole();

            cout << "\n=============================================================" << endl;
            cout << "||\t\t     Sales and Billing Management         ||" << endl;
            cout << "=============================================================" << endl;
            cout << " 1> Add Item to Bill" << endl;
            cout << " 2> Display Bill" << endl;
            cout << " 3> Save Bill to File" << endl;
            cout << " 4> Back to Main Menu" << endl;
            cout << "_____________________________________________________________" << endl;
            cout << " Enter your Option = ";
            cin >> option;

            switch (option)
            {
            case 1:
                Add_Item();
                break;
            case 2:
                Display_Bill();
                break;
            case 3:
                Save_Bill();
                break;
            case 4:
                return;
            default:
                cout << "\n Invalid Option...!!" << endl;
                break;
            }
        }
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

        cout << "\nPress Enter to return to the Main Menu... ";
        cin.ignore();
        cin.get();
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

        cout << "\nPress Enter to return to the Main Menu... ";
        cin.ignore();
        cin.get();
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

    Load_Data();

    int Option1;

    while (true)
    {
        clearConsole();

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
            s1.Sales_Billing_Menu();
            break;
        case 3:
            r1.Reports_Analysis_Print();
            break;
        case 4:
            d1.Data_Storage_Security_Print();
            break;
        case 5:
            cout << "\n Exiting Program...!!\n";
            Save_Data();
            return 0;
        default:
            cout << "\n Invalid Option...!!\n";
            break;
        }

        cout << "\nPress any key to go back to the Main Menu...!! ";
        // return 0;
        // getch();
    }

    return 0;
}