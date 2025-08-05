#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <sstream>
#include <chrono>
#include <ctime>
#include <limits>
using namespace std;

int i = 0;

// Helper function to check if a date is in the future compared to today
bool isFutureDate(int year, int month, int day) {
    time_t t = time(0);
    tm *now = localtime(&t);
    int currYear = now->tm_year + 1900;
    int currMonth = now->tm_mon + 1;
    int currDay = now->tm_mday;
    if (year > currYear) return true;
    if (year == currYear && month > currMonth) return true;
    if (year == currYear && month == currMonth && day > currDay) return true;
    return false;
}

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

        if ((username == "Nage" && password == "Nage123") || (username == "Krishna" && password == "Krishna123") || (username == "Manish" && password == "Manish123") || (username == "Arati" && password == "Arati123"))
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

        string medicineName;
        int quantity;
        float price;
        int year, month, day;

        cout << " Enter Medicine Name = ";
        cin.ignore();
        getline(cin, medicineName);

        cout << " Enter Quantity = ";
        cin >> quantity;

        cout << " Enter Price = ";
        cin >> price;

        cout << " Enter Expiry Date ( Year/Month/Day )" << endl;
        cout << " Enter Year  = ";
        cin >> year;
        cout << " Enter Month = ";
        cin >> month;
        cout << " Enter Day   = ";
        cin >> day;

        // Check expiry date is in the future
        if (!isFutureDate(year, month, day)) {
            cout << "\n Error: Expiry date must be a future date. Cannot insert expired medicine!\n";
            cout << "\nPress Enter to return to the Main Menu... ";
            cin.ignore();
            cin.get();
            return;
        }

        // Check if the medicine already exists
        bool found = false;
        for (int a = 0; a < i; a++)
        {
            if (s[a].Name == medicineName)
            {
                // Update the existing medicine
                s[a].Quantity += quantity;
                s[a].Price = price;
                s[a].Year = year;
                s[a].Month = month;
                s[a].Day = day;

                found = true;
                break;
            }
        }

        if (!found)
        {
            // Add a new medicine
            s[i].Name = medicineName;
            s[i].Quantity = quantity;
            s[i].Price = price;
            s[i].Year = year;
            s[i].Month = month;
            s[i].Day = day;
            i++;
        }

        Save_Data();

        cout << "_____________________________________________________________" << endl;
        if (found)
        {
            cout << "\n\t\t Medicine Updated Successfully...!!" << endl;
        }
        else
        {
            cout << "\n\t\t Medicine Inserted Successfully...!!" << endl;
        }
        cout << "_____________________________________________________________" << endl;

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
                int newYear, newMonth, newDay;
                cin >> newYear;
                cout << " Enter New Month = ";
                cin >> newMonth;
                cout << " Enter New Day   = ";
                cin >> newDay;
                // Check expiry date is in the future
                if (!isFutureDate(newYear, newMonth, newDay)) {
                    cout << "\n Error: Expiry date must be a future date. Cannot update to expired medicine!\n";
                    cout << "\nPress Enter to return to the Main Menu... ";
                    cin.ignore();
                    cin.get();
                    return;
                }
                s[a].Year = newYear;
                s[a].Month = newMonth;
                s[a].Day = newDay;

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

    BillItem billItems[100];
    int billItemCount = 0;
    float totalAmount = 0.0;
    string customerName; 

public:
    void Add_Item()
    {
        clearConsole();

        cout << "\n=============================================================" << endl;
        cout << "||\t\t     Add Item to Bill                      ||" << endl;
        cout << "=============================================================" << endl;

        Load_Data();

        if (i == 0)
        {
            cout << "\n\t\t No Inventory Data Found...!! " << endl;
            cout << "_____________________________________________________________" << endl;

            cout << "\nPress Enter to return to the Main Menu... ";
            cin.ignore();
            cin.get();
            return;
        }

        // Prompt for customer name only if this is the first item in the bill
        if (billItemCount == 0)
        {
            cout << " Enter Customer Name: ";
            // cin.ignore(numeric_limits<streamsize>::max(), '\n');
            getline(cin, customerName);
            if (customerName.empty()) customerName = "Unknown";
        }

        string itemName;
        int quantity;
        bool found = false;

        cout << " Enter Item Name = ";
        getline(cin, itemName);

        for (int a = 0; a < i; a++)
        {
            if (s[a].Name == itemName)
            {
                // Check if the medicine is expired
                if (!isFutureDate(s[a].Year, s[a].Month, s[a].Day)) {
                    cout << "\n Error: Cannot add expired medicine to the bill!\n";
                    cout << "\nPress Enter to return... ";
                    cin.get();
                    return;
                }
                found = true;

                cout << " Enter Quantity = ";
                cin >> quantity;
                cin.ignore();

                if (quantity > s[a].Quantity)
                {
                    cout << "\n Not enough stock available. Available Quantity = " << s[a].Quantity << endl;
                    cout << "\nPress Enter to return... ";
                    cin.get();
                    return;
                }

                // Check if the item already exists in the bill
                bool billFound = false;
                for (int b = 0; b < billItemCount; b++)
                {
                    if (billItems[b].Name == itemName)
                    {
                        // Update the existing item in the bill
                        billItems[b].Quantity += quantity;
                        billItems[b].TotalPrice += quantity * s[a].Price;

                        // Update inventory
                        s[a].Quantity -= quantity;

                        // Update total amount
                        totalAmount += quantity * s[a].Price;

                        billFound = true;
                        break;
                    }
                }

                if (!billFound)
                {
                    // Add item to the bill
                    billItems[billItemCount].Name = s[a].Name;
                    billItems[billItemCount].Quantity = quantity;
                    billItems[billItemCount].Price = s[a].Price;
                    billItems[billItemCount].TotalPrice = quantity * s[a].Price;
                    billItemCount++;

                    // Update inventory
                    s[a].Quantity -= quantity;

                    // Update total amount
                    totalAmount += quantity * s[a].Price;
                }

                cout << "\n Item added to the bill successfully!" << endl;
                cout << "\nPress Enter to return... ";
                cin.get();
                break;
            }
        }

        if (!found)
        {
            cout << "\n Item not found in inventory!" << endl;
            cout << "\nPress Enter to return... ";
            cin.get();
        }

        Save_Data();
    }

    void Display_Bill()
    {
        clearConsole();

        cout << "\n=============================================================" << endl;
        cout << "||\t\t     Sales Bill                          ||" << endl;
        cout << "=============================================================" << endl;

        if (billItemCount == 0)
        {
            cout << "\n\t\t No items in the bill...!! " << endl;
            cout << "_____________________________________________________________" << endl;

            cout << "\nPress Enter to return to the Sales and Billing Menu... ";
            cin.get();
            return;
        }

        // Get current time as system time
        auto now = std::chrono::system_clock::now();
        std::time_t now_time_t = std::chrono::system_clock::to_time_t(now);
        std::tm* local_tm = std::localtime(&now_time_t);

        cout << "\n\n=============================================================" << endl;
        cout << "||\t\t !!...Purbanchal Pharmacy...!!              ||" << endl;
        cout << "||\t\t  Biratnager, MORANG                        ||" << endl;
        cout << "=============================================================" << endl;

        cout << " CUSTOMER NAME  : " << customerName << "                    PayType : CASH" << endl;
        cout << " DATE           : " << std::put_time(local_tm, "%Y-%m-%d") << " " << std::put_time(local_tm, "%A") << endl;
        cout << " TIME           : " << std::put_time(local_tm, "%H:%M:%S") << endl;
        cout << "-------------------------------------------------------------" << endl;
        cout << left << setw(20) << "Name" << setw(12) << "Quantity" << setw(12) << "Price" << setw(15) << "Total Price" << endl;
        cout << "-------------------------------------------------------------" << endl;

        for (int a = 0; a < billItemCount; a++)
        {
            cout << left << setw(20) << billItems[a].Name
                 << setw(12) << billItems[a].Quantity
                 << setw(12) << fixed << setprecision(2) << billItems[a].Price
                 << setw(15) << fixed << setprecision(2) << billItems[a].TotalPrice << endl;
        }
        cout << "-------------------------------------------------------------" << endl;
        cout << right << setw(50) << "Total Amount: " << fixed << setprecision(2) << totalAmount << endl;

        cout << "\nPress Enter to return to the Sales and Billing Menu... ";
        cin.get();
    }

    void Save_Bill()
    {
        clearConsole();

        cout << "\n=============================================================" << endl;
        cout << "||\t\t     Save Bill to CSV File                ||" << endl;
        cout << "=============================================================" << endl;

        if (billItemCount == 0)
        {
            cout << "\n\t\t No items in the bill to save...!! " << endl;
            cout << "_____________________________________________________________" << endl;

            cout << "\nPress Enter to return to the Sales and Billing Menu... ";
            cin.get();
            return;
        }

        // Open the CSV file in append mode
        ofstream file("sales_bills.csv", ios::app);
        if (file.is_open())
        {
            // Write the header if the file is empty
            if (file.tellp() == 0)
            {
                file << "Customer Name,Item Name,Quantity,Price,Total Price\n";
            }

            // Write the bill items
            for (int a = 0; a < billItemCount; a++)
            {
                if (a == 0)
                    file << customerName << "," << billItems[a].Name << "," << billItems[a].Quantity << "," << billItems[a].Price << "," << billItems[a].TotalPrice << "\n";
                else
                    file << "," << billItems[a].Name << "," << billItems[a].Quantity << "," << billItems[a].Price << "," << billItems[a].TotalPrice << "\n";
            }

            file << "," << "Total Amount" << ",,," << totalAmount << "\n";
            file << ",,,,," << "\n";

            file.close();

            cout << "\n Bill saved successfully to 'sales_bills.csv'!" << endl;
            cout << " Customer Name: " << customerName << endl;

            // Reset bill for next customer
            billItemCount = 0;
            totalAmount = 0.0;
            customerName.clear();
        }
        else
        {
            cout << "\n Error: Unable to save the bill to file!" << endl;
        }

        cout << "\nPress Enter to return to the Sales and Billing Menu... ";
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
            cin.ignore();

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
                cout << "\nPress Enter to continue... ";
                cin.get();
                break;
            }
        }
    }
};


class Reports_Analysis
{
public:

    void Reports_Analysis_Menu()
    {
        int option;

        while (true)
        {
            clearConsole();

            cout << "\n=============================================================" << endl;
            cout << "||\t      REPORT AND ANALYSIS MANAGEMENT               ||" << endl;
            cout << "=============================================================" << endl;
            cout << " 1> View Low-Stock Medicines" << endl;
            cout << " 2> View Expired Medicines" << endl;
            cout << " 3> View Total Sales and Revenue" << endl;
            cout << " 4> Generate Summary Report" << endl;
            cout << " 5> Back to Main Menu" << endl;
            cout << "_____________________________________________________________" << endl;
            cout << " Enter your Option = ";
            cin >> option;

            switch (option)
            {
            case 1:
                View_Low_Stock();
                break;
            case 2:
                View_Expired_Medicines();
                break;
            case 3:
                View_Total_Sales();
                break;
            case 4:
                Generate_Summary_Report();
                break;
            case 5:
                return;
            default:
                cout << "\n Invalid Option...!!" << endl;
                break;
            }

            cout << "\nPress Enter to return to the Reports and Analytics Menu... ";
            cin.ignore();
            cin.get();
        }
    }

    void View_Low_Stock()
    {
        clearConsole();

        cout << "\n=============================================================" << endl;
        cout << "||\t      Low-Stock Medicines Report                   ||" << endl;
        cout << "=============================================================" << endl;

        Load_Data();

        if (i == 0)
        {
            cout << "\n\t\t No Inventory Data Found...!! " << endl;
            cout << "_____________________________________________________________" << endl;
            return;
        }

        int threshold;
        cout << " Enter the low-stock threshold: ";
        cin >> threshold;

        // Sort the medicines in descending order of quantity
        for (int x = 0; x < i - 1; x++)
        {
            for (int y = 0; y < i - x - 1; y++)
            {
                if (s[y].Quantity < s[y + 1].Quantity)
                {
                    // Swap the medicines
                    Medicine temp = s[y];
                    s[y] = s[y + 1];
                    s[y + 1] = temp;
                }
            }
        }

        bool found = false;

        for (int a = 0; a < i; a++)
        {
            if (s[a].Quantity < threshold)
            {
                if (!found)
                {
                    cout << "\nLow-Stock Medicines:\n";
                    cout << " Name\t\tQuantity\n";
                    cout << "-----------------------------------\n";
                }

                cout << " " << s[a].Name << "\t\t" << s[a].Quantity << endl;
                found = true;
            }
        }

        if (!found)
        {
            cout << "\n No medicines are below the threshold.\n";
        }

        cout << "_____________________________________________________________" << endl;
    }

    void View_Expired_Medicines()
    {
        clearConsole();

        cout << "\n=============================================================" << endl;
        cout << "||\t      Expired Medicines Report                     ||" << endl;
        cout << "=============================================================" << endl;

        Load_Data(); 

        if (i == 0)
        {
            cout << "\n\t\t No Inventory Data Found...!! " << endl;
            cout << "_____________________________________________________________" << endl;
            return;
        }

        int currentYear, currentMonth, currentDay;
        cout << " Enter today's date (Year Month Day): ";
        cin >> currentYear >> currentMonth >> currentDay;

        bool found = false;

        for (int a = 0; a < i; a++)
        {
            if (s[a].Year < currentYear ||
                (s[a].Year == currentYear && s[a].Month < currentMonth) ||
                (s[a].Year == currentYear && s[a].Month == currentMonth && s[a].Day < currentDay))
            {
                if (!found)
                {
                    cout << "\nExpired Medicines:\n";
                    cout << " Name\t\tExpiry Date\n";
                    cout << "-----------------------------------\n";
                }

                cout << " " << s[a].Name << "\t\t" << s[a].Year << "/" << s[a].Month << "/" << s[a].Day << endl;
                found = true;
            }
        }

        if (!found)
        {
            cout << "\n No expired medicines found.\n";
        }

        cout << "_____________________________________________________________" << endl;
    }

    void View_Total_Sales()
    {
        clearConsole();

        cout << "\n=============================================================" << endl;
        cout << "||\t      Total Sales and Revenue Report               ||" << endl;
        cout << "=============================================================" << endl;

        ifstream file("sales_bills.csv");
        if (!file.is_open())
        {
            cout << "\n\t\t No Sales Data Found...!! " << endl;
            cout << "_____________________________________________________________" << endl;
            return;
        }

        string line;
        float totalRevenue = 0.0;

        while (getline(file, line))
        {
            stringstream ss(line);
            string firstCol, secondCol, thirdCol, fourthCol, totalCol;

            getline(ss, firstCol, ',');   
            getline(ss, secondCol, ',');  
            getline(ss, thirdCol, ',');   
            getline(ss, fourthCol, ',');  
            getline(ss, totalCol, ',');    

            if (secondCol == "Total Amount")
            {
                if (!totalCol.empty())
                    totalRevenue += stof(totalCol);
            }
        }

        file.close();

        cout << "\n Total Revenue from Sales: " << totalRevenue << endl;
        cout << "_____________________________________________________________" << endl;
    }

    void Generate_Summary_Report()
    {
        clearConsole();

        cout << "\n=============================================================" << endl;
        cout << "||\t      Summary Report                                ||" << endl;
        cout << "=============================================================" << endl;

        ofstream file("summary_report.csv");
        if (!file.is_open())
        {
            cout << "\n Error: Unable to save the summary report to file!" << endl;
            return;
        }

        file << "Summary Report\n";

        int threshold;
        cout << " Enter the low-stock threshold: ";
        cin >> threshold;

        // View Low-Stock Medicines
        file << "\nLow-Stock Medicines:\n";
        file << "Name,Quantity\n";
        cout << "\nLow-Stock Medicines:\n";
        cout << " Name\t\tQuantity\n";
        cout << "-----------------------------------\n";

        Load_Data(); // Load inventory data

        bool lowStockFound = false;

        for (int a = 0; a < i; a++)
        {
            if (s[a].Quantity < threshold)
            {
                cout << " " << s[a].Name << "\t\t" << s[a].Quantity << endl;
                file << s[a].Name << "," << s[a].Quantity << "\n";
                lowStockFound = true;
            }
        }

        if (!lowStockFound)
        {
            cout << "\n No low-stock medicines found.\n";
            file << "No low-stock medicines found.\n";
        }

        cout<<"\n";


        int currentYear, currentMonth, currentDay;
        cout << " Enter today's date (Year Month Day): ";
        cin >> currentYear >> currentMonth >> currentDay;

        // View Expired Medicines
        file << "\nExpired Medicines:\n";
        file << "Name,Expiry Date\n";
        cout << "\nExpired Medicines:\n";
        cout << " Name\t\tExpiry Date\n";
        cout << "-----------------------------------\n";

        bool expiredFound = false;

        for (int a = 0; a < i; a++)
        {
            if (s[a].Year < currentYear ||
                (s[a].Year == currentYear && s[a].Month < currentMonth) ||
                (s[a].Year == currentYear && s[a].Month == currentMonth && s[a].Day < currentDay))
            {
                cout << " " << s[a].Name << "\t\t" << s[a].Year << "/" << s[a].Month << "/" << s[a].Day << endl;
                file << s[a].Name << "," << s[a].Year << "/" << s[a].Month << "/" << s[a].Day << "\n";
                expiredFound = true;
            }
        }

        if (!expiredFound)
        {
            cout << "\n No expired medicines found.\n";
            file << "No expired medicines found.\n";
        }

        cout<<"\n";

        ifstream salesFile("sales_bills.csv");
        float totalRevenue = 0.0;
        int totalSales = 0;

        if (salesFile.is_open())
        {
            string line;
            while (getline(salesFile, line))
            {
                stringstream ss(line);
                // string token;
                string firstCol, secondCol, thirdCol, fourthCol, totalCol;

                getline(ss, firstCol, ',');    
                getline(ss, secondCol, ',');   
                getline(ss, thirdCol, ',');   
                getline(ss, fourthCol, ',');  
                getline(ss, totalCol, ',');   

                if (secondCol == "Total Amount")
                {
                    totalSales++;
                    if (!totalCol.empty())
                        totalRevenue += stof(totalCol);
                }
            }
            salesFile.close();
        }

        cout << "Total Sales: " << totalSales << endl;
        cout << "Total Revenue: " << totalRevenue << endl;
        file << "Total Sales," << totalSales << endl;
        file << "Total Revenue," << totalRevenue << endl;


        // Close the CSV file
        file.close();

        cout << "\n Summary Report Generated Successfully!" << endl;
        cout << "_____________________________________________________________" << endl;

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
        cout << " 4> Exit Program" << endl;
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
            r1.Reports_Analysis_Menu();
            break;
        case 4:
            cout << "\n Exiting Program...!!\n";
            Save_Data();
            return 0;
        default:
            cout << "\n Invalid Option...!!\n";
            break;
        }

        cout << "\nPress any key to go back to the Main Menu...!! ";
    }

    return 0;
}