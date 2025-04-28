#include <iostream>
#include <string>
#include <iomanip>
#include <vector>
#include <fstream>
#include <limits>
using namespace std;
string ClientFileName = "Client.txt";

enum EnMainOption
{
	Show = 1, Add = 2, Delete = 3, Update = 4, Find = 5, Transction = 6, Exit = 7
};

enum EnTransctionOption
{
	Deposit = 1, Withdraw = 2, Transfer = 3, Back = 4
};

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
void ShowMainMenue();
void ShowTransactionScreen();
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

int ReadNumCon(const string& message, int from = 0, int to = numeric_limits<int>::max())
{
	int num;
	cout << message;
	cin >> num;

	while (cin.fail() || num < from || num > to)
	{
		cin.clear(); // „”Õ Õ«·… «·Œÿ√
		cin.ignore(numeric_limits<streamsize>::max(), '\n'); //  Ã«Â· «·”ÿ— €Ì— «·’ÕÌÕ

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

double ReadDNum(const string& message, double from = 0, double to = numeric_limits<double>::max())
{
	double num;
	cout << message;
	cin >> num;
	while (cin.fail() || num < from || num > to)
	{
		cin.clear(); // „”Õ Õ«·… «·Œÿ√
		cin.ignore(numeric_limits<streamsize>::max(), '\n'); //  Ã«Â· «·”ÿ— €Ì— «·’ÕÌÕ
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

StClient ConvertLineToRecord(string Line, string Sepereter = "***")
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

string ConvertRecordToLine(StClient Client, string Sepereter = "***")
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

void SaveClientsDataToFile(string FileName, vector<StClient> VClient)
{
	fstream myFile;
	myFile.open(FileName, ios::out | ios::trunc);
	if (myFile.is_open())
	{
		for (StClient client : VClient)
		{
			myFile << ConvertRecordToLine(client) << endl;
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
			client = ConvertLineToRecord(line);
			vClient.push_back(client);
		}
		myFile.close();
	}
	return vClient;
}

void PrintRecord(StClient Client)
{
	cout << "AccountNum     : " << Client.AccountNum << endl;
	cout << "PinCode        : " << Client.PinCode << endl;
	cout << "First Name     : " << Client.FirstName << endl;
	cout << "Last Nmae      : " << Client.LastName << endl;
	cout << "Phone          : " << Client.Phone << endl;
	cout << "Account Balance: " << Client.AccountBalance << endl;
}
void PrintSmallRecrod(StClient Client)
{
	cout << "AccountNum     : " << Client.AccountNum << endl;
	cout << "First Name     : " << Client.FirstName << endl;
	cout << "Account Balance: " << Client.AccountBalance << endl;
}

bool FindClientByAccountNum(string AccountNum, vector<StClient> vClient, StClient& Client)
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

bool MarkClinetForDeleteByAccountNum(string AccountNum, vector<StClient> VClient)
{
	for (StClient& c : VClient)
	{
		if (c.AccountNum == AccountNum)
		{
			c.MarkForDelete = true;
			return true;
		}
	}
	return false;
}

bool DeleteClientByAccountNum(string AccuntNum, vector<StClient>& VClient)
{
	StClient client;
	char Answer = 'n';
	if (FindClientByAccountNum(AccuntNum, VClient, client))
	{
		PrintRecord(client);
		cout << "\nAre you sure to delete: y/n: ";
		cin >> Answer;
		if (tolower(Answer) == 'y')
		{
			MarkClinetForDeleteByAccountNum(AccuntNum, VClient);
			SaveClientsDataToFile(ClientFileName, VClient);
			VClient = LoadClientDataFromFile(ClientFileName);
			cout << "\nClient delete successfully\n";
			return true;
		}
	}
	else
	{
		cout << "\nClient is not found :(\n";
		return false;
	}
	return false;
}

StClient ReadUpdateClient(string AccountNum)
{
	StClient client;
	client.AccountNum = AccountNum;
	client.PinCode = ReadString("Enter PinCode: ");
	client.FirstName = ReadString("Enter First Name: ");
	client.LastName = ReadString("Enter Last Name: ");
	client.Phone = ReadString("Enter Phone Num: ");
	client.AccountBalance = ReadDNum("Enter Account Balance: ");
	return client;
}

void AddNewClient(vector<StClient>& VClient)
{
	string AccountNum = ReadString("Enter Account Num: ");
	StClient client;
	while (FindClientByAccountNum(AccountNum, VClient, client))
	{
		cout << "\nAccount Num is already exist, please enter new one: ";
		AccountNum = ReadString("Enter Account Num: ");
	}
	client = ReadUpdateClient(AccountNum);
	VClient.push_back(client);
	SaveClientsDataToFile(ClientFileName, VClient);
	cout << "\nNew Client added successfully\n";
	VClient = LoadClientDataFromFile(ClientFileName);
}

void UpdateClient(string AccountNum, vector<StClient>& VClient)
{
	StClient client;
	if (FindClientByAccountNum(AccountNum, VClient, client))
	{
		client = ReadUpdateClient(AccountNum);
		for (int i = 0; i < VClient.size(); i++)
		{
			if (VClient[i].AccountNum == AccountNum)
			{
				VClient[i] = client;
				break;
			}
		}
		SaveClientsDataToFile(ClientFileName, VClient);
		VClient = LoadClientDataFromFile(ClientFileName);
		cout << "\nClient updated successfully\n";
	}
	else
	{
		cout << "\nClient is not found :(\n";
	}
}

void UpdateClinetScreen()
{
	cout << "================================================\n";
	cout << "\t\t\tUpdate Client Screen\n";
	cout << "================================================\n";
	string AccountNum = ReadString("Enter Account Num: ");
	vector<StClient> VClient = LoadClientDataFromFile(ClientFileName);
	UpdateClient(AccountNum, VClient);
	system("pause");
}

bool DepositeBalanceToClientByAccountNum(string AccountNum, double Amount, vector<StClient>& VClient)
{
	char answer = 'n';
	cout << "\nAre you sure to deposite " << Amount << " to account num: " << AccountNum << ": y/n: ";
	cin >> answer;
	if (tolower(answer) == 'y')
	{
		for (StClient& c : VClient)
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

bool WithdrawBalanceToClientByAccountNum(string AccountNum, double Amount, vector<StClient>& VClient)
{
	char answer = 'n';
	cout << "\nAre you sure to withdraw " << Amount << " from account num: " << AccountNum << ": y/n: ";
	cin >> answer;
	if (tolower(answer) == 'y')
	{
		for (StClient& c : VClient)
		{
			if (c.AccountNum == AccountNum)
			{
				c.AccountBalance -= Amount;
				SaveClientsDataToFile(ClientFileName, VClient);
				cout << "\nWithdraw successfully new balance is: " << c.AccountBalance << endl;
				return true;
			}
		}
	}
	return false;
}

bool TransferFromToByAccountNum(string AccountNum1, string AccountNum2, double Amount, vector<StClient>& VClient)
{
	char answer = 'n';
	cout << "\nAre you sure to transfer " << Amount << " from account num: " << AccountNum1 << " to account num: " << AccountNum2 << ": y/n: ";
	cin >> answer;
	if (tolower(answer) == 'y')
	{
		for (StClient& c : VClient)
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
		cout << "\nTransfer successfully new balance is: " << endl;
		return true;
	}
	return false;
}


string Tap()
{
	return "\t\t\t\t";
}

EnMainOption ReadMenueOption()
{
	return EnMainOption(ReadNumCon("Choese what do you want to do: [1 to 7]: ", 1, 7));
}

EnTransctionOption ReadTransctionOption()
{
	return EnTransctionOption(ReadNumCon("Choese what do you want to do: [1 to 4]: ", 1, 4));
}

void PrintClinetRecord(StClient Client)
{
	cout << "| " << setw(15) << left << Client.AccountNum;
	cout << "| " << setw(10) << left << Client.PinCode;
	cout << "| " << setw(40) << left << Client.FirstName + " " + Client.LastName;
	cout << "| " << setw(12) << left << Client.Phone;
	cout << "| " << setw(12) << left << Client.AccountBalance;
}

void ShowClientList()
{
	vector<StClient> VClient = LoadClientDataFromFile(ClientFileName);
	cout << "\n_________________________________________________________________________________________________________\n";
	cout << "\n\t\tClient List (" << VClient.size() << ") Client(s).";

	cout << "\n_________________________________________________________________________________________________________\n";
	cout << "\n_________________________________________________________________________________________________________\n";
	cout << "| " << left << setw(15) << "Account Number";
	cout << "| " << left << setw(10) << "PinCode";
	cout << "| " << left << setw(40) << "Client Name";
	cout << "| " << left << setw(12) << "Phone";
	cout << "| " << left << setw(12) << "Account Balance";
	cout << "\n_________________________________________________________________________________________________________\n";
	for (StClient clinet : VClient)
	{
		PrintClinetRecord(clinet);
		cout << endl;
	}
	cout << "\n_________________________________________________________________________________________________________\n";
	system("pause");
}

void showAddClient()
{
	cout << "================================================\n";
	cout << "\t\tAdd New Client Screen\n";
	cout << "================================================\n";
	vector<StClient> VClient = LoadClientDataFromFile(ClientFileName);
	AddNewClient(VClient);
	system("pause");
}

void showDeleteClient()
{
	cout << "================================================\n";
	cout << "\t\tDelete Client Screen\n";
	cout << "================================================\n";
	string AccountNum = ReadString("Enter Account Num: ");
	vector<StClient> VClient = LoadClientDataFromFile(ClientFileName);
	DeleteClientByAccountNum(AccountNum, VClient);
	system("pause");
}

void showUpdateClient()
{
	cout << "================================================\n";
	cout << "\t\tUpdate Client Screen\n";
	cout << "================================================\n";
	string AccountNum = ReadString("Enter Account Num: ");
	vector<StClient> VClient = LoadClientDataFromFile(ClientFileName);
	UpdateClient(AccountNum, VClient);
	system("pause");
}

void showFindClient()
{
	cout << "================================================\n";
	cout << "\t\tFind Client Screen\n";
	cout << "================================================\n";
	string AccountNum = ReadString("Enter Account Num: ");
	vector<StClient> VClient = LoadClientDataFromFile(ClientFileName);
	StClient client;
	if (FindClientByAccountNum(AccountNum, VClient, client))
	{
		PrintRecord(client);
	}
	else
	{
		cout << "\nClient is not found :(\n";
	}
	system("pause");
}

void ShowDeposite()
{
	cout << "================================================\n";
	cout << "\t\tDeposite Screen\n";
	cout << "================================================\n";
	StClient client;
	vector<StClient> VClient = LoadClientDataFromFile(ClientFileName);
	string AccountNum = ReadString("Enter Account Num: ");

	while (!FindClientByAccountNum(AccountNum, VClient, client))
	{
		cout << "\nClient is not found :(\n";
		AccountNum = ReadString("Enter Account Num: ");
	}
	PrintSmallRecrod(client);

	double	Amount = ReadDNum("Enter Amount to Deposite: ", 0);
	DepositeBalanceToClientByAccountNum(AccountNum, Amount, VClient);
	system("pause");
}

void ShowWithdraw()
{
	cout << "================================================\n";
	cout << "\t\tWithdraw Screen\n";
	cout << "================================================\n";
	StClient client;
	vector<StClient> VClient = LoadClientDataFromFile(ClientFileName);
	string AccountNum = ReadString("Enter Account Num: ");
	while (!FindClientByAccountNum(AccountNum, VClient, client))
	{
		cout << "\nClient is not found :(\n";
		AccountNum = ReadString("Enter Account Num: ");
	}
	PrintSmallRecrod(client);
	double Amount = ReadDNum("Enter Amount to Withdraw: ", 0);
	WithdrawBalanceToClientByAccountNum(AccountNum, Amount, VClient);
	system("pause");
}

void ShowTransfer()
{
	vector <StClient> vClient = LoadClientDataFromFile(ClientFileName);
	cout << "================================================\n";
	cout << "\t\tTransfer Screen\n";
	cout << "================================================\n";
	StClient client1;
	StClient client2;
	string AccountNum1 = ReadString("Enter Sender Account Num: ");
	while (!FindClientByAccountNum(AccountNum1, vClient, client1))
	{
		cout << "\nSender Client is not found :(\n";
		AccountNum1 = ReadString("Enter Sender Account Num: ");
	}
	cout << "\nSender Client: \n";
	string AccountNum2 = ReadString("Enter Reciver Account Num: ");
	while (!FindClientByAccountNum(AccountNum2, vClient, client2))
	{
		cout << "\nReciver Client is not found :(\n";
		AccountNum2 = ReadString("Enter Reciver Account Num: ");
	}
	PrintSmallRecrod(client1);
	PrintSmallRecrod(client2);
	double Amount = ReadDNum("Enter Amount to Transfer: ", 0);

	TransferFromToByAccountNum(AccountNum1, AccountNum2, Amount, vClient);
	system("pause");
}

void MakeMainMenu(EnMainOption Option)
{
	system("cls");
	switch (Option)
	{
	case Show:
		ShowClientList();
		ShowMainMenue();
		break;
	case Add:
		showAddClient();
		ShowMainMenue();
		break;
	case Delete:
		showDeleteClient();
		ShowMainMenue();

		break;
	case Update:
		UpdateClinetScreen();
		ShowMainMenue();
		break;
	case Find:
		showFindClient();
		ShowMainMenue();
		break;

	case Transction:
		ShowTransactionScreen();
		ShowMainMenue();
		break;
	case Exit:
		cout << "\n\n\t\t\tThank you for using our system.\n";
		break;
	default:

		break;
	}
}

void MakeTransctionMenu(EnTransctionOption Option)
{
	system("cls");
	switch (Option)
	{
	case Deposit:
		ShowDeposite();
		ShowTransactionScreen();
		break;
	case Withdraw:
		ShowWithdraw();
		ShowTransactionScreen();

		break;
	case Transfer:
		ShowTransfer();
		ShowTransactionScreen();
		break;
	case Back:
		ShowMainMenue();
		break;
	default:
		cout << "\n\n\t\t\tInvalid Option.\n";
		break;
	}
}

void ShowTransactionScreen()
{
	system("cls");
	cout << "================================================\n";
	cout << "\t\tTransaction Screen\n";
	cout << "================================================\n";
	cout << "\t[1] Deposit.\n";
	cout << "\t[2] Withdraw.\n";
	cout << "\t[3] Transfer.\n";
	cout << "\t[4] Back to Main Menue.\n";
	cout << "================================================\n";
	MakeTransctionMenu(ReadTransctionOption());
}

void ShowMainMenue()
{
	system("cls");
	cout << "================================================\n";
	cout << "\t\tMain Menue Screen\n";
	cout << "================================================\n";
	cout << "\t[1] Show Client List.\n";
	cout << "\t[2] Add New Client.\n";
	cout << "\t[3] Delete Client.\n";
	cout << "\t[4] Update Client.\n";
	cout << "\t[5] Find Client.\n";
	cout << "\t[6] Transction.\n";
	cout << "\t[7] Exit.\n";
	cout << "================================================\n";
	MakeMainMenu(ReadMenueOption());
}

int main()
{
	ShowMainMenue();
}

