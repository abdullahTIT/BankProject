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
	Show = 1, Add = 2, Delete = 3, Update = 4, Find = 5, Exit = 6
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

StClient ReadUpdateClient(string AccountNum, bool isNew = true)
{
	StClient client;
	if (isNew)
		client.AccountNum = ReadString("Enter Account Num: ");
	else
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
	StClient client = ReadUpdateClient("", true);
	VClient.push_back(client);
	SaveClientsDataToFile(ClientFileName, VClient);
	VClient = LoadClientDataFromFile(ClientFileName);
	cout << "\nNew Client added successfully\n";
}

void UpdateClient(string AccountNum, vector<StClient>& VClient)
{
	StClient client;
	if (FindClientByAccountNum(AccountNum, VClient, client))
	{
		client = ReadUpdateClient(AccountNum, false);
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

string Tap()
{
	return "\t\t\t\t";
}

EnMainOption ReadMenueOption()
{
	return EnMainOption(ReadNumCon("Choese what do you want to do: [1 to 6]: ", 1, 6));
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
	case Exit:
		cout << "\n\n\t\t\tThank you for using our system.\n";
		break;
	default:

		break;
	}
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
	cout << "\t[6] Exit.\n";
	cout << "================================================\n";
	MakeMainMenu(ReadMenueOption());
}

int main()
{
	ShowMainMenue();
}