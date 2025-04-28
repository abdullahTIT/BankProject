#include <iostream>
#include <string>
#include <iomanip>
#include <vector>
#include <fstream>
#include <limits>
using namespace std;

enum EnATMOption
{
    Withdraw = 1,
    QouckWithdraw = 2,
    Deposit = 3,
    CheckBalance = 4,
    Transfer = 5,
    LogOut = 6
};

string ClientFileName = "Client.txt";

struct StClient
{
    string AccountNum = "";
    string PinCode = "";
    string FirstName = "";
    string LastName = "";
    string Phone = "";
    double AccountBalance = 0;
    bool MarkForDelete = false;
};

StClient CurrentCleint;

void ShowATMMenue();

string ReadString(string Message)
{
    string s = "";
    while (s == "" || s == "\n")
    {
        cout << Message;
        getline(cin >> ws, s);
    }

    return s;
}

int ReadNumCon(const string &message, int from = 0, int to = numeric_limits<int>::max())
{
    int num;
    cout << message;
    cin >> num;

    while (cin.fail() || num < from || num > to)
    {
        cin.clear();                                         // مسح حالة الخطأ
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // تجاهل السطر غير الصحيح

        if (cin.fail())
            cout << "Invalid input. Please enter a valid number: ";
        else if (num < from)
            cout << "The number is too small. Please enter a number >= " << from << ": ";
        else if (num > to)
            cout << "The number is too large. Please enter a number <= " << to << ": ";

        cin >> num;
    }
    return num;
}

double ReadDNum(const string &message, double from = 0, double to = numeric_limits<double>::max())
{
    double num;
    cout << message;
    cin >> num;
    while (cin.fail() || num < from || num > to)
    {
        cin.clear();                                         // مسح حالة الخطأ
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // تجاهل السطر غير الصحيح
        if (cin.fail())
            cout << "Invalid input. Please enter a valid number: ";
        else if (num < from)
            cout << "The number is too small. Please enter a number >= " << from << ": ";
        else if (num > to)
            cout << "The number is too large. Please enter a number <= " << to << ": ";
        cin >> num;
    }
    return num;
}

bool ReadAnswer(string Message = "y/n")
{
    char Answer = 'n';
    cout << Message;
    cin >> Answer;
    if (tolower(Answer) == 'y')
        return true;
    else
        return false;
}

vector<string> SplitString(string s, string delim = "***")
{
    vector<string> vwords;
    short pos = 0;
    string sword;
    while ((pos = s.find(delim)) != std::string::npos)
    {
        sword = s.substr(0, pos);
        if (sword != "")
            vwords.push_back(sword);

        s.erase(0, pos + delim.length());
    }
    if (s != "")
        vwords.push_back(s);

    return vwords;
}

StClient ConvertClientLineToRecord(string Line, string Sepereter = "***")
{
    vector<string> vClient = SplitString(Line, Sepereter);
    StClient clinet;
    clinet.AccountNum = vClient[0];
    clinet.PinCode = vClient[1];
    clinet.FirstName = vClient[2];
    clinet.LastName = vClient[3];
    clinet.Phone = vClient[4];
    clinet.AccountBalance = stod(vClient[5]);
    return clinet;
}

string ConvertClientRecordToLine(StClient Client, string Sepereter = "***")
{
    string line = "";
    line += Client.AccountNum + Sepereter;
    line += Client.PinCode + Sepereter;
    line += Client.FirstName + Sepereter;
    line += Client.LastName + Sepereter;
    line += Client.Phone + Sepereter;
    line += to_string(Client.AccountBalance);
    return line;
}

void SaveClientsDataToFile(string FileName, vector<StClient> &VClient)
{
    fstream myFile;
    myFile.open(FileName, ios::out);
    if (myFile.is_open())
    {
        for (StClient &client : VClient)
        {
            if (client.MarkForDelete == false)
                myFile << ConvertClientRecordToLine(client) << endl;
        }
        myFile.close();
    }
    else
    {
        cout << "Error opening file for writing." << endl;
    }
}

vector<StClient> LoadClientDataFromFile(string FileName)
{
    vector<StClient> vClient;
    fstream myFile;
    myFile.open(FileName, ios::in);
    if (myFile.is_open())
    {
        string line;
        StClient client;
        while (getline(myFile, line))
        {
            client = ConvertClientLineToRecord(line);
            vClient.push_back(client);
        }
        myFile.close();
    }
    return vClient;
}

bool FindClientByAccountNumAndPinCode(string AccountNum, string PinCode, vector<StClient> vClient, StClient &Client)
{
    for (StClient c : vClient)
    {
        if (c.AccountNum == AccountNum && c.PinCode == PinCode)
        {
            Client = c;
            return true;
        }
    }
    return false;
}

bool FindClientByAccountNum(string AccountNum, vector<StClient> vClient, StClient &Client)
{
    for (StClient c : vClient)
    {
        if (c.AccountNum == AccountNum)
        {
            Client = c;
            return true;
        }
    }
    return false;
}

bool DepositeBalanceToClientByAccountNum(string AccountNum, double Amount, vector<StClient> &VClient)
{
    char answer = 'n';
    cout << "\nAre you sure to deposite " << Amount << " to account num: " << AccountNum << ": y/n: ";
    cin >> answer;
    if (tolower(answer) == 'y')
    {
        for (StClient &c : VClient)
        {
            if (c.AccountNum == AccountNum)
            {
                c.AccountBalance += Amount;
                SaveClientsDataToFile(ClientFileName, VClient);
                cout << "\nDeposite successfully new balance is: " << c.AccountBalance << endl;
                return true;
            }
        }
    }
    return false;
}

bool WithdrawBalanceToClientByAccountNum(string AccountNum, double Amount, vector<StClient> &VClient)
{
    char answer = 'n';
    cout << "\nAre you sure to withdraw " << Amount << " from account num: " << AccountNum << ": y/n: ";
    cin >> answer;
    if (tolower(answer) == 'y')
    {
        for (StClient &c : VClient)
        {
            if (c.AccountNum == AccountNum && c.AccountBalance > Amount)
            {
                c.AccountBalance -= Amount;
                SaveClientsDataToFile(ClientFileName, VClient);
                cout << "\nWithdraw successfully new balance is: " << c.AccountBalance << endl;
                return true;
            }
            else
            {
                cout << "\nWithdraw failed. Insufficient balance.\n";
                return false;
            }
        }
    }
    return false;
}

bool TransferFromToByAccountNum(string AccountNum1, string AccountNum2, double Amount, vector<StClient> &VClient)
{
    char answer = 'n';
    cout << "\nAre you sure to transfer " << Amount << " from account num: " << AccountNum1 << " to account num: " << AccountNum2 << ": y/n: ";
    cin >> answer;
    if (tolower(answer) == 'y')
    {
        for (StClient &c : VClient)
        {
            if (c.AccountNum == AccountNum1)
            {
                c.AccountBalance -= Amount;
            }
            else if (c.AccountNum == AccountNum2)
            {
                c.AccountBalance += Amount;
            }
        }
        SaveClientsDataToFile(ClientFileName, VClient);
        cout << "\nTransfer successfully new balance is: " << CurrentCleint.AccountBalance << endl;
        return true;
    }
    return false;
}

EnATMOption ReadATMOption()
{
    return (EnATMOption)ReadNumCon("Choese what do you want to do: [1 to 6]: ", 1, 6);
}

void PrintSmallRecrod(StClient Client)
{
    cout << "AccountNum     : " << Client.AccountNum << endl;
    cout << "First Name     : " << Client.FirstName << endl;
    cout << "Account Balance: " << Client.AccountBalance << endl;
}

void ShowDeposite()
{
    cout << "================================================\n";
    cout << "\t\tDeposite Screen\n";
    cout << "================================================\n";
    StClient client;
    vector<StClient> VClient = LoadClientDataFromFile(ClientFileName);
    double Amount = ReadDNum("Enter Amount to Deposite: ", 0);
    DepositeBalanceToClientByAccountNum(CurrentCleint.AccountNum, Amount, VClient);
    system("pause");
}

short MakeQickWithDraw(int option)
{
    switch (option)
    {
    case 1:
        return 20;
    case 2:
        return 50;
    case 3:
        return 100;
    case 4:
        return 200;
    case 5:
        return 400;
    case 6:
        return 600;
    case 7:
        return 800;
    case 8:
        return 1000;

    default:
        return 0;
        break;
    }
    return 0;
}

void ShowQuickWithDraw()
{
    system("cls");
    cout << "================================================\n";
    cout << "\t\tQuick Withdraw Screen\n";
    cout << "================================================\n";
    cout << "\t[1] 20.\t";
    cout << "\t[2] 50.\n";
    cout << "\t[3] 100.\t";
    cout << "\t[4] 200.\n";
    cout << "\t[5] 400.\t";
    cout << "\t[6] 600.\n";
    cout << "\t[7] 800.\t";
    cout << "\t[8] 1000.\n";
    cout << "\t[9] Exit.\n";
    cout << "================================================\n";
    int option = ReadNumCon("Choose the amount you want to withdraw: ", 1, 9);
    if (option == 9)
        return;

    StClient client;
    vector<StClient> VClient = LoadClientDataFromFile(ClientFileName);
    PrintSmallRecrod(client);
    double Amount = 1000;
    WithdrawBalanceToClientByAccountNum(CurrentCleint.AccountNum, MakeQickWithDraw(option), VClient);
    system("pause");
}

void ShowWithdraw()
{
    system("cls");
    cout << "================================================\n";
    cout << "\t\tWithdraw Screen\n";
    cout << "================================================\n";
    vector<StClient> VClient = LoadClientDataFromFile(ClientFileName);
    double Amount = ReadDNum("Enter Amount to Withdraw: ", 0);
    WithdrawBalanceToClientByAccountNum(CurrentCleint.AccountNum, Amount, VClient);
    system("pause");
}

void ShowTransfer()
{
    vector<StClient> vClient = LoadClientDataFromFile(ClientFileName);
    system("cls");
    cout << "================================================\n";
    cout << "\t\tTransfer Screen\n";
    cout << "================================================\n";
    StClient client2;
    string AccountNum1 = CurrentCleint.AccountNum;
    cout << "\nSender Client: \n";
    string AccountNum2 = ReadString("Enter Reciver Account Num: ");
    while (!FindClientByAccountNum(AccountNum2, vClient, client2))
    {
        cout << "\nReciver Client is not found :(\n";
        AccountNum2 = ReadString("Enter Reciver Account Num: ");
    }
    cout << "\nReciver Client: \n";
    cout << client2.FirstName << endl;
    double Amount = ReadDNum("Enter Amount to Transfer: ", 0);

    TransferFromToByAccountNum(AccountNum1, AccountNum2, Amount, vClient);
    system("pause");
}

void ShowCheckBalance()
{
    system("cls");
    cout << "================================================\n";
    cout << "\t\tCheck Balance Screen\n";
    cout << "================================================\n";
    cout << "Account Balace is : " << CurrentCleint.AccountBalance << endl;
    system("pause");
}

void ShowLogOut()
{
    system("cls");
    cout << "================================================\n";
    cout << "\t\tLog Out Screen\n";
    cout << "================================================\n";
    system("pause");
}

void MakeATMMenue(EnATMOption Option)
{
    switch (Option)
    {
    case EnATMOption::Withdraw:
        ShowWithdraw();
        break;
    case EnATMOption::QouckWithdraw:
        ShowQuickWithDraw();
        break;
    case EnATMOption::Deposit:
        ShowDeposite();
        break;
    case EnATMOption::CheckBalance:
        ShowCheckBalance();
        break;
    case EnATMOption::Transfer:
        ShowTransfer();
        break;
    case EnATMOption::LogOut:
        ShowLogOut();
        break;
    default:
        cout << "Invalid option. Please try again.\n";
        system("pause");
    }
}

void ShowATMMenue()
{
    system("cls");
    cout << "================================================\n";
    cout << "\t\tATM Screen\n";
    cout << "================================================\n";
    cout << "\t[1] Withdraw.\n";
    cout << "\t[2] Quick Withdraw.\n";
    cout << "\t[3] Deposit.\n";
    cout << "\t[4] Check Balance.\n";
    cout << "\t[5] Transfer.\n";
    cout << "\t[6] Log Out.\n";
    cout << "================================================\n";
    MakeATMMenue(ReadATMOption());
}

void LogInScreen()
{
    system("cls");
    cout << "================================================\n";
    cout << "\t\tLog In Screen\n";
    cout << "================================================\n";
    short tries = 3;
    do
    {
        string AccountNum = ReadString("Enter Account Num: ");
        string PinCode = ReadString("Enter Pin Code: ");
        vector<StClient> VClient = LoadClientDataFromFile(ClientFileName);
        if (FindClientByAccountNumAndPinCode(AccountNum, PinCode, VClient, CurrentCleint))
        {
            cout << "\nWelcome " << CurrentCleint.FirstName << " " << CurrentCleint.LastName << endl;
            ShowATMMenue();
            break;
        }
        else
        {
            cout << "\nInvalid Account Number or Pin Code. Please try again.\n";
            tries--;
            if (tries == 0)
            {
                cout << "\nYou have exceeded the maximum number of attempts. Exiting...\n";
                system("pause");
                exit(0);
            }
        }

    } while (tries > 0);
}

int main()
{
    do
    {
        LogInScreen();

    } while (true);
    return 0;
}
