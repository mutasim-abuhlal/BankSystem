#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <iomanip>
#include <conio.h>

using namespace std;

const string BankSystemName = "BankSystem.text";

struct stClientData
{
	string AccountNumber = "";
	string PinCode = "";
	string Name = "";
	string Phone = "";
	float AccountBalance = 0;
	bool MarkClient = false;
};

enum enChooice { ShowClientList = 1, AddNewClient = 2, DeleteClient = 3, UpdateClientInfo = 4, FindClient = 5, Exit = 6 };

void CheckOnUserChoose(enChooice Choose);

int UserChooice();

void BankSystemMenue()
{
	system("cls");
	cout << "====================================================\n";
	cout << "\t\t\tMain Menue Screen\t\t\n";
	cout << "====================================================\n";
	cout << "\t\t[1] Show Client List.\n";
	cout << "\t\t[2] Add New Client.\n";
	cout << "\t\t[3] Delete Client.\n";
	cout << "\t\t[4] Update Client Info.\n";
	cout << "\t\t[5] Find Client.\n";
	cout << "\t\t[6] Exit.\n";
	cout << "====================================================\n";
	CheckOnUserChoose(enChooice(UserChooice()));
}

void PauseProjcet();

stClientData FillClientData(string AccountNumber)
{
	stClientData PersonData;

	PersonData.AccountNumber = AccountNumber;

	cout << "Enter PinCode? ";
	getline(cin >> ws, PersonData.PinCode);

	cout << "Enter Name ? ";
	getline(cin, PersonData.Name);

	cout << "Enter Phone ? ";
	getline(cin, PersonData.Phone);

	cout << "Enter AccountBalance ? ";
	cin >> PersonData.AccountBalance;

	cin.ignore(numeric_limits <streamsize>::max(), '\n');

	return PersonData;
}

int UserChooice()
{
	int Select = 0;

	cout << "Choose What do you want to do? [1 to 6]? ";
	cin >> Select;

	return Select;
}

char DoYouWantDelete()
{
	char Delete = 'y';


	cout << "Are you sure you want delete this client? Y/N ?";
	cin >> Delete;

	return Delete;


}

stClientData FillClientData()
{
	stClientData PersonData;

	cout << "Enter Account Number ? ";
	getline(cin >> ws, PersonData.AccountNumber);

	cout << "Enter PinCode? ";
	getline(cin, PersonData.PinCode);

	cout << "Enter Name ? ";
	getline(cin, PersonData.Name);

	cout << "Enter Phone ? ";
	getline(cin, PersonData.Phone);

	cout << "Enter AccountBalance ? ";
	cin >> PersonData.AccountBalance;

	return PersonData;
}

string ConvertRecordToLine(stClientData ClinetData, string delm = "#//#")
{
	string s2 = "";

	s2 = ClinetData.AccountNumber + delm + ClinetData.PinCode + delm + ClinetData.Name + delm + ClinetData.Phone + delm + to_string(ClinetData.AccountBalance);

	return s2;
}

bool IsClientExits(vector <stClientData> vClients, string AccountNumber)
{
	for (int i = 0; i < vClients.size(); i++)
	{
		if (vClients[i].AccountNumber == AccountNumber)
			return true;
	}

	return false;
}

void AddDatatoLine(string FileName, string Line)
{
	fstream Myfile;

	Myfile.open(FileName, ios::out | ios::app);

	if (Myfile.is_open())
	{
		Myfile << Line << endl;
		Myfile.close();
	}
}

stClientData FillClientData(vector <stClientData> vClient)
{
	stClientData PersonData;

	do
	{
		cout << "Enter Account Number?";
		getline(cin >> ws, PersonData.AccountNumber);

		if (!IsClientExits(vClient, PersonData.AccountNumber))
			break;
		cout << "\n\nClient with [" << PersonData.AccountNumber << "] already exists Enter another Account Number? ";
	} while (IsClientExits(vClient, PersonData.AccountNumber));


	cout << "\n\nEnter PinCode? ";
	getline(cin , PersonData.PinCode);

	cout << "Enter Name ? ";
	getline(cin, PersonData.Name);

	cout << "Enter Phone ? ";
	getline(cin, PersonData.Phone);

	cout << "Enter AccountBalance ? ";
	cin >> PersonData.AccountBalance;

	cin.ignore(numeric_limits <streamsize>::max(), '\n');

	return PersonData;

}

void NewClient(vector <stClientData> vClients)
{
	stClientData Client = FillClientData(vClients);

		string ClientLine = ConvertRecordToLine(Client);
		AddDatatoLine(BankSystemName, ClientLine);
	
}

void AddClientsToFile(vector <stClientData> vClients)
{
	char AddMore = 'Y';
	
		
		cout << "Adding New Client:\n\n";

		NewClient(vClients);

		cout << "Cleint Added Successfully, do you want to add more clients? Y/N? ";
		cin >> AddMore;

}

void Intro(int HowManyClient)
{
	cout << "                                           Client List (" << HowManyClient << ") Clinet(s).                            ";
	cout << "\n_________________________________________________________________________________________________________________\n";
	cout << "\n| Account Number   | Pin Code  | Client Name                                 | Phone        | Balance  ";
	cout << "\n_________________________________________________________________________________________________________________\n";

}

vector <string> ToVector(string line, string delm = "#//#")
{
	vector <string> vString;
	string s2 = "";
	short pos = 0;

	while ((pos = line.find(delm)) != string::npos)
	{
		s2 = line.substr(0, pos);
		if (s2 != "")
			vString.push_back(s2);

		line.erase(0, pos + delm.length());

	}
	if (!line.empty())
		vString.push_back(line);


	return vString;
}

stClientData ConvertToRecord(string line)
{
	vector <string> vString = ToVector(line);
	stClientData Client;

	Client.AccountNumber = vString[0];
	Client.PinCode = vString[1];
	Client.Name = vString[2];
	Client.Phone = vString[3];
	Client.AccountBalance = stod(vString[4]);

	return Client;

}

vector <stClientData> ReadClientData()
{
	fstream MyFile;
	string line = "";
	vector < stClientData > ReadFromFile;
	stClientData Client;

	MyFile.open(BankSystemName, ios::in);

	if (MyFile.is_open())
	{
		while (getline(MyFile, line))
		{

			Client = ConvertToRecord(line);
			ReadFromFile.push_back(Client);

		}
		MyFile.close();

	}

	return ReadFromFile;
}

void ShowAllClient(stClientData Client)
{

	cout << "| " << setw(17) << left << Client.AccountNumber;
	cout << "| " << setw(10) << left << Client.PinCode;
	cout << "| " << setw(44) << left << Client.Name;
	cout << "| " << setw(13) << left << Client.Phone;
	cout << "| " << setw(7) << left << Client.AccountBalance << endl;
}

void PrintAllClientData()
{
	vector <stClientData> vFileClientData = ReadClientData();
	 
	Intro(vFileClientData.size());

	for (int i = 0; i < vFileClientData.size(); i++)
	{
		ShowAllClient(vFileClientData[i]);
	}
	cout << "_________________________________________________________________________________________________________________\n";

	PauseProjcet();

	BankSystemMenue();
}

string ReadAccountNumber()
{
	string AccountNumber = "";

	cout << "Please Enter AccountNumber? ";
	cin.ignore(1, '\n');
	getline(cin , AccountNumber);

	return AccountNumber;
}

bool IsClientEixts(vector <stClientData> vClientData, string AccountNumber, stClientData& ClientInfo)
{
	for (int i = 0; i < vClientData.size(); i++)
	{
		if (vClientData[i].AccountNumber == AccountNumber)
		{
			ClientInfo = vClientData[i];

			return true;
		}
	}

	return false;
}

void PrintSingleClientInfo(stClientData Client)
{
	cout << "\n\nThe following are the client detalis:\n\n";

	cout << "Account Number : " << Client.AccountNumber << endl;
	cout << "Pin Codde      : " << Client.PinCode << endl;
	cout << "Name           : " << Client.Name << endl;
	cout << "Phone          : " << Client.Phone << endl;
	cout << "Account Balance : " << Client.AccountBalance;
}

void FindClientByAccountNumber(vector <stClientData> ClientsData)
{
	string AccountNumber = ReadAccountNumber();
	stClientData ClientInfo;
	bool IsExits = IsClientEixts(ClientsData, AccountNumber, ClientInfo);

	if (IsExits)
		PrintSingleClientInfo(ClientInfo);
	else
		cout << "\nClient with Account number (" << AccountNumber << ") Not Found!";




}

bool MarkClientByAccountNumber(vector <stClientData>& vClients, string AccountNumber)
{
	for (int i = 0; i < vClients.size(); i++)
	{
		if (vClients[i].AccountNumber == AccountNumber)
		{
			vClients[i].MarkClient = true;
			return true;
		}
	}

	return false;
}

void SaveDataToFile(vector <stClientData> vClients)
{
	fstream MyFile;

	MyFile.open(BankSystemName, ios::out);

	if (MyFile.is_open())
	{

		for (int i = 0; i < vClients.size(); i++)
		{
			if (vClients[i].MarkClient == false)
				MyFile << ConvertRecordToLine(vClients[i]) << endl;
		}

		MyFile.close();

	}

}

void DeleteDataByAccountNumber(vector <stClientData>& ClientsData)
{
	string AccountNumber = ReadAccountNumber();
	stClientData ClientInfo;
	bool IsExits = IsClientEixts(ClientsData, AccountNumber, ClientInfo);

	if (IsExits)
	{
		PrintSingleClientInfo(ClientInfo);

		cout << endl << endl;
		char Del = DoYouWantDelete();

		if (Del == 'y')
		{
			MarkClientByAccountNumber(ClientsData, AccountNumber);
			SaveDataToFile(ClientsData);

			ClientsData = ReadClientData();

			cout << "\n\nClient deleted succussfelly\n\n";
		}
		else
			cout << "\n\nClient didn't Deleted.\n\n";

	}
	else
		cout << "\nClient with Account number (" << AccountNumber << ") Not Found!";

}

void UpdateVectorElements(vector <stClientData>& vClients, string  AccountNumber)
{

	for (int i = 0; i < vClients.size(); i++)
	{
		if (vClients[i].MarkClient == true)
			vClients[i] = FillClientData(AccountNumber);

	}
}

void SaveToFile(vector <stClientData> vClients, string AccountNumber)
{
	fstream Myfile;
	string DataLine;

	Myfile.open(BankSystemName, ios::out);

	if (Myfile.is_open())
	{

		for (int i = 0; i < vClients.size(); i++)
		{
			DataLine = ConvertRecordToLine(vClients[i]);
			Myfile << DataLine << endl;
		}
	}

}

void UpdateClientByAccountNumber(vector <stClientData>& ClientsData)
{
	string AccountNumber = ReadAccountNumber();
	stClientData ClientInfo;
	bool IsExits = IsClientEixts(ClientsData, AccountNumber, ClientInfo);

	if (IsExits)
	{
		PrintSingleClientInfo(ClientInfo);
		char ToUpdate = 'y';
		cout << "\n\nAre you sure you ant update this client? Y/N? ";
		cin >> ToUpdate;
		if (tolower(ToUpdate) == 'y')
		{
			for (stClientData& C : ClientsData)
			{
				if (C.AccountNumber == AccountNumber)
					C = FillClientData(AccountNumber);
			}
			SaveToFile(ClientsData, AccountNumber);

		ClientsData = ReadClientData();// refresh the vector recored

			cout << "\n\nUpdated Client successfully\n";
		}
	}
	else
		cout << "\nClient with Account number (" << AccountNumber << ") Not Found!";




}

void PauseProjcet()
{
	cout << "\n\nPress any key to go back to Main Menue...";
	system("pause>0");
}

void GoToUpdateSecreen()
{
	vector <stClientData> vClients = ReadClientData();
	cout << "--------------------------------------------\n";
	cout << "\t\tUpdate Secreen\n";
	cout << "--------------------------------------------\n";

	UpdateClientByAccountNumber(vClients);

	PauseProjcet();

	BankSystemMenue();
}

void GoToAddNewClientScreen()
{
	vector <stClientData> vClients = ReadClientData();
	cout << "--------------------------------------------\n";
	cout << "\t\tAdd New Clients Screen\n";
	cout << "--------------------------------------------\n";

	AddClientsToFile(vClients);

	PauseProjcet();

	BankSystemMenue();
}

void GoToDeleteScreen()
{
	vector <stClientData> vClients = ReadClientData();
	cout << "\n-------------------------------------------------\n";
	cout << "\t\tDelete Client Screen\n";
	cout << "---------------------------------------------------\n";


	DeleteDataByAccountNumber(vClients);

	PauseProjcet();

	BankSystemMenue();
}

void GoToFindClientScreen()
{
	vector <stClientData> vClients = ReadClientData();

	cout << "\n---------------------------------------\n";
	cout << "\t\tFind Screen\n";
	cout << "---------------------------------------\n";

	FindClientByAccountNumber(vClients);

	PauseProjcet();

	BankSystemMenue();
}

void GoToEixtScreen()
{
	cout << "\n---------------------------------------------\n";
	cout << "\t\tProgram Ends :-)\n";
	cout << "---------------------------------------------\n";
}

void CheckOnUserChoose(enChooice Choose)
{
	switch (Choose)
	{
	case enChooice::ShowClientList:
		system("cls");
		PrintAllClientData();
		PauseProjcet();
		break;
	case enChooice::AddNewClient:
		system("cls");
		GoToAddNewClientScreen();
		break;
	case enChooice::DeleteClient:
		system("cls");
		GoToDeleteScreen();
		break;
	case enChooice::UpdateClientInfo:
		system("cls");
		GoToUpdateSecreen();
		break;
	case enChooice::FindClient:
		system("cls");
		GoToFindClientScreen();
		break;
	default:
		system("cls");
		GoToEixtScreen();
	

	}
}


int main()
{
	BankSystemMenue();
	system("pause>0");



    return 0;
}


