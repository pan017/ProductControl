// team.cpp : Defines the entry point for the console application.
//
#define _CRT_SECURE_NO_WARNINGS
#include "stdafx.h"
#include <iostream>
#include "productInfo.h"
#include "user.h"
#include "Date.h"
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <stdio.h>  // for printf
#include <windows.h>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <time.h>


using namespace std;

int mainMenu();
void viewMainMenu();
bool sortByIdUp(const TProductInfo& left, const TProductInfo& right)
{
	return left.id < right.id;
}
bool sortByIdLow(const TProductInfo& left, const TProductInfo& right)
{
	return left.id > right.id;
}
bool sortByNameUp(const TProductInfo& left, const TProductInfo& right)
{
	return strcmp(left.name.c_str(), right.name.c_str()) < 0;
}
bool sortByNameLow(const TProductInfo& left, const TProductInfo& right)
{
	return strcmp(left.name.c_str(), right.name.c_str()) > 0;
}

bool sortByCountsUp(const TProductInfo& left, const TProductInfo& right)
{
	return left.count < right.count;
}
bool sortByCountLow(const TProductInfo& left, const TProductInfo& right)
{
	return left.count > right.count;
}
void viewProducts(vector<TProductInfo>);
int �ontextMenu();
void viewContextMenu();
void getInfoFromShop();
void readProductFile();
void addNewProductInfo();
void viewInfo(vector<TProductInfo>);
void deleteProduct();
void readUsersFile();
void addNewUser();
void viewUsers();
void renderUserList();
void authorize();
int selectMenuItem();
int selectFindMenuItem();
bool isValidLoginAndPassword(std::string, std::string);
void deleteUser();

void viewFindMenu();
void viewFindMenuItems();
vector<TProductInfo> findByName(string);
vector<TProductInfo> findById(string);
vector<TProductInfo> findByProductName(string);
TUser tempUser;
TUser currentUser;
TProductInfo tempProduct;
const char *USER_PATH = "user.dat";
const char *PRODUCT_INFO_PATH = "productInfos.dat";
FILE *userFile;
FILE *productInfoFile;
vector<int>::iterator it;
vector<TUser> users;
vector<TProductInfo> productInfoList;
bool isAuthorize;

typedef struct
{
	std::string name;
	int count;
}TInfo;


int main()
{
	setlocale(LC_ALL, "Russian");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	readUsersFile();
	readProductFile();
	authorize();
	viewMainMenu();
	return 0;
}

int mainMenu() // ����
{
	system("cls");
	cout << "����:" << endl;
	if (currentUser.role == "admin")
	{

		cout << "1. ���������� � ���������" << endl;
		cout << "2. ����� ������" << endl;
		cout << "3. ����� �� ���� � ����" << endl;
		cout << "4. ������� �������" << endl;
		cout << "5. ���� ������" << endl;
		cout << "6. ������ �������������" << endl;
		cout << "7. �������� ������������" << endl;
		cout << "8. ������� ������������" << endl;
		cout << "9. �����" << endl;
		int i;
		cin >> i;
		return i;
	}
	else
	{
		cout << "1. ���������� � ���������" << endl;
		cout << "2. ����� �� ���� � ����" << endl;
		cout << "3. ���� ������" << endl;
		cout << "4. �����" << endl;
		int i;
		cin >> i;
		return i;
	}
}
void viewMainMenu()
{
	if (currentUser.role == "admin")
	{
		switch (mainMenu())
		{
		case 1: viewInfo(productInfoList); break;
		case 2: addNewProductInfo(); break;

		case 3:  getInfoFromShop(); break;
		case 4:  deleteProduct(); break;
		case 5:  viewFindMenu(); break;
		case 6: viewUsers();break;
		case 7: addNewUser();break;
		case 8: deleteUser(); break;
		case 9: ExitProcess(1); break;
		default: viewMainMenu(); break;
		}
	}
	else
	{
		switch (mainMenu())
		{
		case 1: viewInfo(productInfoList); break;
		case 2: getInfoFromShop(); break;
		case 3: viewFindMenu(); break;
		case 4: ExitProcess(1); break;
		default: viewMainMenu(); break;
		}
	}
}
int �ontextMenu()
{
	cout << endl;
	cout << "��� ���������� �� �/� � ������� ����������� ������� 1.\n";
	cout << "��� ���������� �� �/� � ������� �������� ������� 2.\n";
	cout << "��� ���������� �� ������� �� ����������� ������� 3.\n";
	cout << "��� ���������� �� ������� �� �������� ������� 4.\n";
	cout << "��� ���������� �� ���������� ��������� �� ������������ ������� 5.\n";
	cout << "��� ���������� �� ���������� ��������� �� �������� ������� 6.\n";
	cout << "��� ������ � ������� ���� ������� Esc\n";
	int i;
	i = _getch(); // ���� ���������� ������ ����
	if (i != 27)
		i -= 48;
	return i;
}

void viewContextMenu()
{
	vector<TProductInfo> sortsProductInfoList = productInfoList;
	switch (�ontextMenu())
	{
	case 1:
		sort(sortsProductInfoList.begin(), sortsProductInfoList.end(), sortByIdUp);
		break;
	case 2:
		sort(sortsProductInfoList.begin(), sortsProductInfoList.end(), sortByIdLow);		
		break;
	case 3:
		sort(sortsProductInfoList.begin(), sortsProductInfoList.end(), sortByNameUp);

		break;
	case 4:
		sort(sortsProductInfoList.begin(), sortsProductInfoList.end(), sortByNameLow);
		break;
	case 5:
		sort(sortsProductInfoList.begin(), sortsProductInfoList.end(), sortByCountsUp);
		break;
	case 6:
		sort(sortsProductInfoList.begin(), sortsProductInfoList.end(), sortByCountLow);
		break;
	case 27: viewMainMenu(); break;
	default:
		viewInfo(productInfoList);
		break;
	}
	viewInfo(sortsProductInfoList);
}
void authorize()
{
	do
	{
		system("cls");
		cout << "�����������\n�����:";
		cin >> tempUser.login;
		cout << "������:";
		cin >> tempUser.password;

		if (!isValidLoginAndPassword(tempUser.login, tempUser.password))
		{
			cout << "\n������. �������� ����� ��� ������\n";
			system("pause");

		}
		else
		{
			break;
			
		}
	} while (true);

}

bool isValidLoginAndPassword(string login, string password)
{

	for (size_t i = 0; i < users.size(); i++)
	{
		if (login == users[i].login && password == users[i].password)
		{
			currentUser = users[i];
			return true;
		}
	}
	return false;
}
void renderUserList()
{
	cout << "********* - ������ ������������� - *********\n";
	for (size_t i = 0; i < 44; cout << "-", i++);
	cout << endl;
	cout << setw(3) << "| �" << setw(12) << "�����" << setw(14) << "������";
	cout << setw(16) << "����   |" << endl;
	for (int i = 0; i < users.size(); i++)
	{



		cout << "|" << setw(2) << i+1 << " |";
		cout << setw(10) << users[i].login << " | ";
		cout << setw(10) << users[i].password << " |    ";
		cout << setw(7) << users[i].role << "   | ";
		cout << endl;
	}
}
void viewUsers()
{
	system("cls");
	renderUserList();
	cout << "������� ������� ��� �������� � ����...";
	int q;
	cin >> q;
	viewMainMenu();

}

void deleteUser()
{
	system("cls");
	renderUserList();
	cout << "\n������� � �/� ��� ��������. ��� ������ � ���� ������� 0" << endl;
	int deleteNumber = 0;
	cin >> deleteNumber;
	if (deleteNumber == 0)
		viewMainMenu();
	if (deleteNumber > users.size())
	{
		cout << "\n������ ����� ������. ������� ������� ��� �������� � ����...";
		_getch();
		viewMainMenu();
	}

	users.erase(users.begin() + deleteNumber - 1);
	if ((userFile = fopen(USER_PATH, "wb")) == NULL)
	{
		cout << "Oshibka pri sozdanii" << endl;
		exit(1);
	}
	for (size_t i = 0; i < users.size(); i++)
	{
		fwrite(&users[i], sizeof(TUser), 1, userFile);
	}
	fclose(userFile);
	viewMainMenu();
}
void viewInfo(vector<TProductInfo> productInfosList)
{
	viewProducts(productInfosList);
	viewContextMenu();
	char c = _getch();
	if (c == 27)
		viewMainMenu();
	_getch();
	viewMainMenu();
}
void readProductFile()
{
	if ((productInfoFile = fopen(PRODUCT_INFO_PATH, "rb")) == NULL)
	{
		cout << "Oshibka pri otkritii" << endl;
		exit(1);
	}
	int id = 1;
	while (true)
	{
		int nwrt = fread(&tempProduct, sizeof(TProductInfo), 1, productInfoFile);
		if (nwrt != 1) break;
		tempProduct.id = id;
		productInfoList.insert(productInfoList.end(), tempProduct);
		id++;
	}
	fclose(productInfoFile);
}
void readUsersFile() // �������� ��������� �����
{
	if ((userFile = fopen(USER_PATH, "rb")) == NULL)
	{
		cout << "Oshibka pri otkritii" << endl;
		exit(1);
	}
	int nst = 0;
	while (true)
	{

		int nwrt = fread(&tempUser, sizeof(TUser), 1, userFile);
		if (nwrt != 1) break;

		users.insert(users.end(), tempUser);
		nst++;
	}
	fclose(userFile);
}
void viewFindMenuItems()
{
	cout << "��� ������ �� id ������� 1\n";
	cout << "��� ������ �� ������� ������������� ������� 2\n";
	cout << "��� ������ �� ������������ ������ 3\n";
}
void viewFindMenu()
{
	int findType = selectFindMenuItem();
	if (findType > 3 || findType < 1)
	{
		cout << "������ ����� ������\n";
		system("pause");
		viewMainMenu();
	}
	string query;
	cout << "������� ������: ";
	cin >> query;
	switch (findType)
	{

	case 1: viewInfo(findById(query)); break;
	case 2: viewInfo(findByName(query)); break;
	case 3: viewInfo(findByProductName(query));  break;
	default:
		break;
	}

}
vector<TProductInfo> findById(string query)
{
	vector<TProductInfo> resultOfFind;
	resultOfFind.insert(resultOfFind.end(), productInfoList[std::stoi(query) - 1]);
	return resultOfFind;
}
vector<TProductInfo> findByName(string query)
{
	vector<TProductInfo> resultOfFind;
	for (int i = 0; i < productInfoList.size(); i++)
	{
		if (productInfoList[i].name == query)
			resultOfFind.insert(resultOfFind.end(), productInfoList[i]);
	}
	return resultOfFind;
}
vector<TProductInfo> findByProductName(string query)
{
	vector<TProductInfo> resultOfFind;
	for (int i = 0; i < productInfoList.size(); i++)
	{
		if (productInfoList[i].productName == query)
			resultOfFind.insert(resultOfFind.end(), productInfoList[i]);
	}
	return resultOfFind;
}
int selectMenuItem()
{
	int menuItem;
	cin >> menuItem;
	return menuItem;
}
int selectFindMenuItem()
{
	system("cls");
	cout << "�������� �������� ������\n";
	viewFindMenuItems();
	return selectMenuItem();
}
void addNewProductInfo()
{
	system("cls");
	int nst = 0;

	TProductInfo newProduct;
	cout << "������� �������������: ";
	cin >> newProduct.name;
	cout << "��� ��������������: ";
	cin >> newProduct.firstName;
	cout << "�������� ��������������: ";
	cin >> newProduct.lastname;
	cout << "���� ������������: ";
	cin >> newProduct.day;
	cout << "����� ������������: ";
	cin >> newProduct.month;
	cout << "��� ������������: ";
	cin >> newProduct.year;
	cout << "����� ����: ";
	cin >> newProduct.number;
	cout << "������������ ���������: ";
	cin.ignore();
	getline(cin, newProduct.productName);
	cout << "���������� ������: ";
	cin >> newProduct.count;
	productInfoList.insert(productInfoList.end(), newProduct);
	if ((productInfoFile = fopen(PRODUCT_INFO_PATH, "wb")) == NULL)
	{
		cout << "Oshibka pri sozdanii" << endl;
		exit(1);
	}
	for (size_t i = 0; i < productInfoList.size(); i++)
	{
		fwrite(&productInfoList[i], sizeof(TProductInfo), 1, productInfoFile);
	}
	fclose(productInfoFile);
	if (productInfoList.size() == 1)
		productInfoList[productInfoList.size() - 1].id = 1;
	else
	{
		productInfoList[productInfoList.size() - 1].id = productInfoList[productInfoList.size() - 2].id + 1;
	}
	
	viewMainMenu();
}
void addNewUser() // ���� ������ � �����
{
	system("cls");
	int nst = 0;

	TUser newUser;
	cout << "������� �����: ";
	cin >> newUser.login;
	cout << "������� ������: ";
	cin >> newUser.password;
	cout << "�������� ����: ";
	cin >> newUser.role;
	users.insert(users.end(), newUser);
	if ((userFile = fopen(USER_PATH, "wb")) == NULL)
	{
		cout << "Oshibka pri sozdanii" << endl;
		exit(1);
	}
	for (int i = 0; i < users.size(); i++)
		fwrite(&users[i], sizeof(TUser), 1, userFile);

	fclose(userFile);
	cout << "������� ������� ��� �������� � ����...";
	_getch();
	viewMainMenu();
}

void getInfoFromShop()
{
	system("cls");
	cout << "������� ����� ����" << endl;
	TProductInfo tempProduct;
	cin >> tempProduct.number;
	vector<TProductInfo> result;
	TDate begin, end;
	cout << "������ �������:" << endl;
	cout << "������� ����" << endl;
	cin >> begin.day;
	cout << "������� �����" << endl;
	cin >> begin.month;
	cout << "������� ���" << endl;
	cin >> begin.year;
	cout << "����� �������:" << endl;
	cout << "������� ����" << endl;
	cin >> end.day;
	cout << "������� �����" << endl;
	cin >> end.month;
	cout << "������� ���" << endl;
	cin >> end.year;
	int beginDate, endDate, tempDate;
	beginDate = std::stoi(begin.year + begin.month + begin.day);
	endDate = std::stoi(end.year + end.month + end.day);
	
	for (int i = 0; i < productInfoList.size(); i++)
	{
		tempDate = std::stoi(productInfoList[i].year + productInfoList[i].month + productInfoList[i].day);
		if (productInfoList[i].number == tempProduct.number)
			if (tempDate >= beginDate && tempDate <= endDate )
				result.insert(result.end(), productInfoList[i]);
	}
	vector<TInfo> infos;
	TInfo tempInfo;
	bool flag;
	if (result.size() > 0)
	{
		tempInfo.count = result[0].count;
		tempInfo.name = result[0].productName;
		for (int i = 1; i < result.size(); i++)
		{
			flag = false;
			tempInfo.count = result[i].count;
			tempInfo.name = result[i].productName;
			for (int j = 0; j < infos.size(); j++)
			{
				if (tempInfo.name == infos[j].name)
				{
					infos[j].count += tempInfo.count;
					flag = true;
				}
			}
			if (!flag)
				infos.insert(infos.end(), tempInfo);
		}
		cout << "***************************************\n";
		cout  << "| ������������ |" << setw(15) << "���������� |\n";
		for (int i = 0; i < infos.size(); i++)
		{
			cout << "| ";
			cout << setw(7) << infos[i].name;
			cout << setw(7) << "|" << setw(7) <<infos[i].count << setw(9) << "  | \n";
		}
	}
	else
		cout << "������ �� �������" << endl;
	cout << "������� ������� ��� �������� � ����...";
	int q;
	cin >> q;
	viewMainMenu();

}
void viewProducts(vector<TProductInfo> products)
{
	system("cls");
	cout << "*************************************** - ������ ��������� - ****************************************\n";
	for (size_t i = 0; i < 99; cout << "-", i++);
	cout << endl;
	cout << setw(3) << "| �" << setw(12) << "�������" << setw(14) << "���";
	cout << setw(16) << "��������" << setw(12) << "����" << setw(12) << "���";
	cout << setw(17) << "������������" << setw(15) << "���������� |";
	cout << endl;
	for (size_t i = 0; i < 99; cout << "-", i++);
	cout << endl;
	for (int i = 0; i < products.size(); i++)
	{
		cout << "|" << setw(2) << products[i].id << "|";
		cout << setw(12) << products[i].name << " | ";
		cout << setw(12) << products[i].firstName << " | ";
		cout << setw(12) << products[i].lastname << " |  ";
		cout << products[i].day << ".";
		cout << products[i].month << ".";
		cout << products[i].year << "  | ";
		cout << setw(5) << products[i].number << "   |   ";
		cout << setw(7) << products[i].productName << "   | ";
		cout << setw(5) << products[i].count << "    | \n";
		for (size_t j = 0; j < 99; cout << "-", j++);
		cout << endl;
	}
	for (size_t j = 0; j < 99; cout << "*", j++);
}
void deleteProduct()
{
	
	system("cls");
	cout << "*************************************** - ������ ��������� - ****************************************\n";
	for (size_t i = 0; i < 99; cout << "-", i++);
	cout << endl;
	cout << setw(3) << "| �" << setw(12) << "�������" << setw(14) << "���";
	cout << setw(16) << "��������" << setw(12) << "����" << setw(12) << "���";
	cout << setw(17) << "������������" << setw(15) << "���������� |";
	cout << endl;
	for (size_t i = 0; i < 99; cout << "-", i++);
	cout << endl;
	for (int i = 0; i < productInfoList.size(); i++)
	{
		cout << "|" << setw(2) << i + 1 << "|";
		cout << setw(12) << productInfoList[i].name << " | ";
		cout << setw(12) << productInfoList[i].firstName << " | ";
		cout << setw(12) << productInfoList[i].lastname << " |  ";
		cout << productInfoList[i].day << ".";
		cout << productInfoList[i].month << ".";
		cout << productInfoList[i].year << "  | ";
		cout << setw(5) << productInfoList[i].number << "   |   ";
		cout << setw(7) << productInfoList[i].productName << "   | ";
		cout << setw(5) << productInfoList[i].count << "    | \n";
		for (size_t j = 0; j < 99; cout << "-", j++);
		cout << endl;
	}
	for (size_t j = 0; j < 99; cout << "*", j++);
	cout << "\n������� � �/� ��� ��������. ��� ������ � ���� ������� 0 " << endl;
	int deleteNumber = 0;
	cin >> deleteNumber;
	if (deleteNumber == 0)
		viewMainMenu();
	if (deleteNumber > productInfoList.size())
	{
		cout << "\n������ ����� ������. ������� ������� ��� �������� � ����...";
		_getch();
		viewMainMenu();
	}

	productInfoList.erase(productInfoList.begin() + deleteNumber - 1);
	if ((productInfoFile = fopen(PRODUCT_INFO_PATH, "wb")) == NULL)
	{
		cout << "Oshibka pri sozdanii" << endl;
		exit(1);
	}
	for (size_t i = 0; i < productInfoList.size(); i++)
	{
		fwrite(&productInfoList[i], sizeof(TProductInfo), 1, productInfoFile);
	}
	fclose(productInfoFile);
	viewMainMenu();
}