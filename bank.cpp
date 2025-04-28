
#include <iostream>
#include <string>
#include <iomanip>
#include <vector>
#include <fstream>
#include <limits>
using namespace std;
string ClientFileName = "Client.txt";
string UserFileName = "User.txt";

enum EnMainOption
{
	Show = 1,
	Add = 2,
	Delete = 3,
	Update = 4,
	Find = 5,
	TransctionsScreen = 6,
	MangeUserScreen = 7,
	LogOut = 8
};

enum EnUserMainOption
{
	ShowUser = 1,
	AddUser = 2,
	DeleteUser = 3,
	UpdateUser = 4,
	Goback = 5
};

enum EnTransctionOption
{
	Deposit = 1,
	Withdraw = 2,
	Transfer = 3,
	Back = 4
};

enum EnUserPermission
{
	all = -1,
	ShowClientList = 1,
	AddClient = 2,
	DeleteClinet = 4,
	UpdateClinet = 8,
	FindClient = 16,
	TransctionsS = 32,
	MangeUser = 64
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

struct StUser
{
	string UserName = "";
	string Password = "";
	int Permission = 0;
	bool MarkForDelete = false;
};

StUser CurrentUser;

void ShowMainMenue();
void ShowUserMenue();
void ShowTransactionScreen();
void LoginScreen();

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
		cin.clear();										 // „”Õ Õ«·… «·Œÿ√
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
		cin.clear();										 // „”Õ Õ«·… «·Œÿ√
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

StUser ConvertUserLineToRecord(string Line, string Sepereter = "#//#")
{
	vector<string> vUser = SplitString(Line, Sepereter);
	StUser user;
	user.UserName = vUser[0];
	user.Password = vUser[1];
	user.Permission = stoi(vUser[2]);
	return user;
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

string ConvertUserRecordToLine(StUser User, string Sepereter = "#//#")
{
	string line = "";
	line += User.UserName + Sepereter;
	line += User.Password + Sepereter;
	line += to_string(User.Permission);
	return line;
}

void SaveClientsDataToFile(string FileName, vector<StClient>& VClient)
{
	fstream myFile;
	myFile.open(FileName, ios::out);
	if (myFile.is_open())
	{
		for (StClient& client : VClient)
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

void SaveUsersDataToFile(string FileName, vector<StUser>& VUser)
{
	fstream myFile;
	myFile.open(FileName, ios::out);
	if (myFile.is_open())
	{
		for (StUser& user : VUser)
		{
			if (user.MarkForDelete == false)
				myFile << ConvertUserRecordToLine(user) << endl;
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

vector<StUser> LoadUserDataFromFile(string FileName)
{
	vector<StUser> vUser;
	fstream myFile;
	myFile.open(FileName, ios::in);
	if (myFile.is_open())
	{
		string line;
		StUser user;
		while (getline(myFile, line))
		{
			user = ConvertUserLineToRecord(line);
			vUser.push_back(user);
		}
		myFile.close();
	}
	return vUser;
}

bool CheckPermission(EnUserPermission Permission, short UserPermission)
{
	if (UserPermission == -1)
		return true;
	else
	{
		if ((UserPermission & Permission) == Permission)
			return true;
		else
			return false;
	}
}

void PrintClientRecord(StClient Client)
{
	cout << "AccountNum     : " << Client.AccountNum << endl;
	cout << "PinCode        : " << Client.PinCode << endl;
	cout << "First Name     : " << Client.FirstName << endl;
	cout << "Last Nmae      : " << Client.LastName << endl;
	cout << "Phone          : " << Client.Phone << endl;
	cout << "Account Balance: " << Client.AccountBalance << endl;
}
void PrintUseRecord(StUser User)
{
	cout << "UserName       : " << User.UserName << endl;
	cout << "Password       : " << User.Password << endl;
	cout << "Permission     : " << User.Permission << endl;
}

void PrintSmallRecrod(StClient Client)
{
	cout << "AccountNum     : " << Client.AccountNum << endl;
	cout << "First Name     : " << Client.FirstName << endl;
	cout << "Account Balance: " << Client.AccountBalance << endl;
}
void PrintSmallRecrod(StUser User)
{
	cout << "UserName       : " << User.UserName << endl;
	cout << "Permission     : " << User.Permission << endl;
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
bool FindUserByUserName(string UserName, vector<StUser> vUser, StUser& User)
{
	for (StUser u : vUser)
	{
		if (u.UserName == UserName)
		{
			User = u;
			return true;
		}
	}
	return false;
}
bool FindUserByUserNameAndPassword(string UserName, string Password, vector<StUser> vUser, StUser& User)
{
	for (StUser u : vUser)
	{
		if (u.UserName == UserName && u.Password == Password)
		{
			User = u;
			return true;
		}
	}
	return false;
}

bool MarkClinetForDeleteByAccountNum(string AccountNum, vector<StClient>& VClient)
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
bool MarkUserForDeleteByUserName(string UserName, vector<StUser>& VUser)
{
	for (StUser& u : VUser)
	{
		if (u.UserName == UserName)
		{
			u.MarkForDelete = true;
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
		PrintClientRecord(client);
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
bool DeleteUserByUserName(string UserName, vector<StUser>& VUser)
{
	StUser user;
	char Answer = 'n';
	if (FindUserByUserName(UserName, VUser, user))
	{
		PrintUseRecord(user);
		cout << "\nAre you sure to delete: y/n: ";
		cin >> Answer;
		if (tolower(Answer) == 'y')
		{
			MarkUserForDeleteByUserName(UserName, VUser);
			SaveUsersDataToFile(UserFileName, VUser);
			VUser = LoadUserDataFromFile(UserFileName);
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
short ReadPermission()
{
	short Permission = 0;
	if (ReadAnswer("Do you want to give full access y/n: "))
	{
		return -1;
	}
	else
	{
		if (ReadAnswer("Do you want to show client list y/n: "))
			Permission += EnUserPermission::ShowClientList;
		if (ReadAnswer("Do you want to add client y/n: "))
			Permission += EnUserPermission::AddClient;
		if (ReadAnswer("Do you want to delete client y/n: "))
			Permission += EnUserPermission::DeleteClinet;
		if (ReadAnswer("Do you want to update client y/n: "))
			Permission += EnUserPermission::UpdateClinet;
		if (ReadAnswer("Do you want to find client y/n: "))
			Permission += EnUserPermission::FindClient;
		if (ReadAnswer("Do you want to do transction y/n: "))
			Permission += EnUserPermission::TransctionsS;
		if (ReadAnswer("Do you want to mange user y/n: "))
			Permission += EnUserPermission::MangeUser;
	}
	return Permission;
}
StUser ReadUpdateUser(string UserName)
{
	StUser user;
	user.UserName = UserName;
	user.Password = ReadString("Enter Password: ");
	user.Permission = ReadPermission();
	return user;
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
void AddNewUser(vector<StUser>& VUser)
{
	string UserName = ReadString("Enter User Name: ");
	StUser user;
	while (FindUserByUserName(UserName, VUser, user))
	{
		cout << "\nUser Name is already exist, please enter new one: ";
		UserName = ReadString("Enter User Name: ");
	}
	user = ReadUpdateUser(UserName);
	VUser.push_back(user);
	SaveUsersDataToFile(UserFileName, VUser);
	cout << "\nNew User added successfully\n";
	VUser = LoadUserDataFromFile(UserFileName);
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
void UpdateUserV(string UserName, vector<StUser>& VUser)
{
	StUser user;
	if (FindUserByUserName(UserName, VUser, user))
	{
		user = ReadUpdateUser(UserName);
		for (int i = 0; i < VUser.size(); i++)
		{
			if (VUser[i].UserName == UserName)
			{
				VUser[i] = user;
				break;
			}
		}
		SaveUsersDataToFile(UserFileName, VUser);
		VUser = LoadUserDataFromFile(UserFileName);
		cout << "\nClient updated successfully\n";
	}
	else
	{
		cout << "\nClient is not found :(\n";
	}
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
	return EnMainOption(ReadNumCon("Choese what do you want to do: [1 to 8]: ", 1, 8));
}
EnUserMainOption ReadUserMenueOption()
{
	return EnUserMainOption(ReadNumCon("Choese what do you want to do: [1 to 5]: ", 1, 5));
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

void PrintUseRecordLine(StUser User)
{
	cout << "| " << setw(15) << left << User.UserName;
	cout << "| " << setw(10) << left << User.Password;
	cout << "| " << setw(40) << left << User.Permission;
}

void ShowClientListV()
{
	if (!CheckPermission(EnUserPermission::ShowClientList, CurrentUser.Permission))
	{
		cout << "Access Denied. You don't have permission to show client list.\n";
		system("pause");
		return;
	}
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
void ShowUserList()
{
	vector<StUser> VUser = LoadUserDataFromFile(UserFileName);
	cout << "\n_________________________________________________________________________________________________________\n";
	cout << "\n\t\tUser List (" << VUser.size() << ") User(s).";
	cout << "\n_________________________________________________________________________________________________________\n";
	cout << "\n_________________________________________________________________________________________________________\n";
	cout << "| " << left << setw(15) << "User Name";
	cout << "| " << left << setw(10) << "Password";
	cout << "| " << left << setw(40) << "Permission";
	cout << "\n_________________________________________________________________________________________________________\n";
	for (StUser user : VUser)
	{
		PrintUseRecordLine(user);
		cout << endl;
	}
	cout << "\n_________________________________________________________________________________________________________\n";
	system("pause");
}

void showAddClient()
{
	if (!CheckPermission(EnUserPermission::AddClient, CurrentUser.Permission))
	{
		cout << "Access Denied. You don't have permission to show client list.\n";
		system("pause");

		return;
	}
	cout << "================================================\n";
	cout << "\t\tAdd New Client Screen\n";
	cout << "================================================\n";
	vector<StClient> VClient = LoadClientDataFromFile(ClientFileName);
	AddNewClient(VClient);
	system("pause");
}
void showAddUser()
{
	cout << "================================================\n";
	cout << "\t\tAdd New User Screen\n";
	cout << "================================================\n";
	vector<StUser> VUser = LoadUserDataFromFile(UserFileName);
	AddNewUser(VUser);
	system("pause");
}

void showDeleteClient()
{
	if (!CheckPermission(EnUserPermission::DeleteClinet, CurrentUser.Permission))
	{
		cout << "Access Denied. You don't have permission to show client list.\n";
		system("pause");
		return;
	}
	cout << "================================================\n";
	cout << "\t\tDelete Client Screen\n";
	cout << "================================================\n";
	string AccountNum = ReadString("Enter Account Num: ");
	vector<StClient> VClient = LoadClientDataFromFile(ClientFileName);
	DeleteClientByAccountNum(AccountNum, VClient);
	system("pause");
}
void showDeleteUser()
{
	cout << "================================================\n";
	cout << "\t\tDelete User Screen\n";
	cout << "================================================\n";
	string UserName = ReadString("Enter User Name: ");
	vector<StUser> VUser = LoadUserDataFromFile(UserFileName);
	DeleteUserByUserName(UserName, VUser);
	system("pause");
}

void showUpdateClient()
{
	if (!CheckPermission(EnUserPermission::UpdateClinet, CurrentUser.Permission))
	{
		cout << "Access Denied. You don't have permission to show client list.\n";
		system("pause");
		return;
	}
	cout << "================================================\n";
	cout << "\t\tUpdate Client Screen\n";
	cout << "================================================\n";
	string AccountNum = ReadString("Enter Account Num: ");
	vector<StClient> VClient = LoadClientDataFromFile(ClientFileName);
	UpdateClient(AccountNum, VClient);
	system("pause");
}
void showUpdateUser()
{
	cout << "================================================\n";
	cout << "\t\tUpdate User Screen\n";
	cout << "================================================\n";
	string UserName = ReadString("Enter User Name: ");
	vector<StUser> VUser = LoadUserDataFromFile(UserFileName);
	UpdateUserV(UserName, VUser);
	system("pause");
}

void showFindClient()
{
	if (!CheckPermission(EnUserPermission::FindClient, CurrentUser.Permission))
	{
		cout << "Access Denied. You don't have permission to show client list.\n";
		system("pause");
		return;
	}
	cout << "================================================\n";
	cout << "\t\tFind Client Screen\n";
	cout << "================================================\n";
	string AccountNum = ReadString("Enter Account Num: ");
	vector<StClient> VClient = LoadClientDataFromFile(ClientFileName);
	StClient client;
	if (FindClientByAccountNum(AccountNum, VClient, client))
	{
		PrintClientRecord(client);
	}
	else
	{
		cout << "\nClient is not found :(\n";
	}
	system("pause");
}
void showFindUser()
{
	cout << "================================================\n";
	cout << "\t\tFind User Screen\n";
	cout << "================================================\n";
	string UserName = ReadString("Enter User Name: ");
	vector<StUser> VUser = LoadUserDataFromFile(UserFileName);
	StUser user;
	if (FindUserByUserName(UserName, VUser, user))
	{
		PrintUseRecord(user);
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

	double Amount = ReadDNum("Enter Amount to Deposite: ", 0);
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
	vector<StClient> vClient = LoadClientDataFromFile(ClientFileName);
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
		ShowClientListV();
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
		showUpdateClient();
		ShowMainMenue();
		break;
	case Find:
		showFindClient();
		ShowMainMenue();
		break;

	case TransctionsScreen:
		ShowTransactionScreen();
		ShowMainMenue();
		break;
	case MangeUserScreen:
		ShowUserMenue();
		ShowMainMenue();
		break;
	case LogOut:
		LoginScreen();
		break;
	default:

		break;
	}
}

void MakeUserMenu(EnUserMainOption Option)
{
	system("cls");
	switch (Option)
	{
	case ShowUser:
		ShowUserList();
		ShowUserMenue();
		break;
	case AddUser:
		showAddUser();
		ShowUserMenue();
		break;
	case DeleteUser:
		showDeleteUser();
		ShowUserMenue();
		break;
	case UpdateUser:
		showUpdateUser();
		ShowUserMenue();
		break;
	case Goback:
		system("pause");
		break;
	default:
		cout << "\n\n\t\t\tInvalid Option.\n";
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
	if (!CheckPermission(EnUserPermission::TransctionsS, CurrentUser.Permission))
	{
		cout << "Access Denied. You don't have permission to show client list.\n";
		system("pause");
		return;
	}
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
	cout << "\t[7] User Menue.\n";
	cout << "\t[8] Exit.\n";
	cout << "================================================\n";
	MakeMainMenu(ReadMenueOption());
}

void ShowUserMenue()
{
	if (!CheckPermission(EnUserPermission::MangeUser, CurrentUser.Permission))
	{
		cout << "Access Denied. You don't have permission to show client list.\n";
		system("pause");
		return;
	}

	system("cls");
	cout << "================================================\n";
	cout << "\t\tUser Menue Screen\n";
	cout << "================================================\n";
	cout << "\t[1] Show User List.\n";
	cout << "\t[2] Add New User.\n";
	cout << "\t[3] Delete User.\n";
	cout << "\t[4] Update User.\n";
	cout << "\t[5] back.\n";
	cout << "================================================\n";
	MakeUserMenu(ReadUserMenueOption());
}

void LoginScreen()
{
	system("cls");
	cout << "================================================\n";
	cout << "\t\tLogin Screen\n";
	cout << "================================================\n";
	short treshould = 3;
	do
	{
		string UserName = ReadString("Enter User Name: ");
		string Password = ReadString("Enter Password: ");
		vector<StUser> VUser = LoadUserDataFromFile(UserFileName);
		StUser user;
		if (FindUserByUserNameAndPassword(UserName, Password, VUser, user))
		{
			cout << "\nLogin successfully\n";
			CurrentUser = user;
			ShowMainMenue();
			break;
		}
		else
		{
			cout << "\nInvalid User Name or Password\n";
			treshould--;
			if (treshould == 0)
				cout << "\nYou have entered wrong password 3 times. Please try again later.\n";
		}
		if (treshould > 0)
		{
			cout << "\nYou have " << treshould << " attempts left.\n";
			system("pause");
		}
		else
		{
			cout << "\nExiting the program...\n";
			break;
		}

	} while (treshould > 0);
	system("pause");
}

int main()
{
	LoginScreen();
	return 0;
}