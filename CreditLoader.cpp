// CreditLoader.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include "Dbtor.h"
#include <clocale>
#include <string>
#include <cstdio>
#include <random>
#include <ctime>
#include <Windows.h>


#define VERSION 1.1

using namespace std;

Dbtor *Debs[100];
Dbtor *Creditors[100];

int Global_debs_counter = 0;
int MN_Global_debs_counter = 0;
bool isFirst = false;


string DefaultWay1 = "DEBPROFILES1.dat";
string  DefaultWay2 = "DEBPROFILES2.dat";


bool FILE_OP;


void StartSystem();

void MainMenu();
void Adddeb();
void DebList();
void ChangeInfo();
void ChangeInfo(int svp);
void OutputDebs();
void MyDebs();
void DelDebs();
int LoadDebs();
void WriteDebs();
void guide();
void AddCreditor();
void DelCreditor();
void OutputCreditors();
void CreditorsList();
void Statisitc();

void WriteDebs()         //Обьединил сохранение кредиторов и должников, так как нет функционального смысла их разделять
{
	ofstream Dataf;
	ofstream DataB;

	Dataf.open(DefaultWay1);
	Dataf << Global_debs_counter << "\n";                 //Сохраняю значения должников

	for (int i = 0; i < Global_debs_counter; i++)
	{
		Dataf << Debs[i]->GetNameValue() << "\n";
		Dataf << Debs[i]->GetSizeValue() << "\n";
	}



	Dataf.close();                                           //Сохраняю значение кредиторов

	DataB.open(DefaultWay2);
	DataB << MN_Global_debs_counter << "\n";

	for (int i = 0; i < MN_Global_debs_counter; i++)
	{
		DataB << Creditors[i]->GetNameValue() << "\n";
		DataB << Creditors[i]->GetSizeValue() << "\n";
	}


	DataB.close();

}

void guide()
{
	isFirst = false;

	system("cls");
	system("color 0a");
	char ch;
	int counter = 0;

	cout << "Рады приветствовать в программе CreditLoader\n\nЭтот обучающий гайд поможет освоиться в программе и привыкнуть к ее интерфейсу\n\n\nДля продолжения нажимайте любые клавиши:  ";
	cin >> ch;
	cout << "\n\nОтлично! Теперь приступим к основной части\n\nВсе управление в программе основавывается на работе с клавиатурой, навигация по программе осуществляется путем ввода цифр из предложенного перечня вариантов (Если вы выбирайте несуществующий вариант ответа, то автоматически попадайте в главное меню)\n\n";
	cout << "\n\nВведите что угодно, чтобы продолжить: ";
	cin >> ch;
	cout << "\n\nНе всегда в программе будут появляться сообщения вроде того, что было сверху - зачастую программа будет просто ожидать ввода символа\n\n";
	cout << "\n\nВ некоторых местах ввод для вас будет запрещен, вам придется подождать некоторое время (3 секунды), после чего программа сама отправит вас куда надо. Пример такой ситуации - возникновение ошибки\n\n";
	cin >> ch;
	system("color 0C");
	cout << "\n\nОшибка!!! Не волнуйтесь, это тестовая ошибка, таким выглядит ее возникновение - если ваш экран стал красным - знайте: где то вы ошиблись\n\nВам придется подождать 3 секунды прежде чем продолжить\n\n";
	Sleep(3000);
	system("color 0a");
	cout << "В программе есть ряд некоторых особенностей, например, периодически в ней возникают сообщения и примечания\nВсе примечания и сообщения помещаются в ***Примечание***\n\nСоветуем обращать внимание на такие сообщения\n\n";
	cin >> ch;
	cout << "\n\n\nНа этом наш гайд подходит к концу, но прежде чем закончить проведем небольшой тест: \n\n";

	int cho;
	for (int i = 0; i < 90; i++)
	{


		cout << "Что вы хотите сделать?\n1 - Попасть в главное меню\n2 - Просмотреть эту прекрасную инструкцию еще раз\n3 - Закрыть программу\n\n";
		cin >> cho;

		switch (cho)
		{
		case 1:
			MainMenu();
			break;
		case 2:
			if (i == 0)
			{
				cout << "Вы, по всей вероятности ошиблись, у вас есть второй шанс\n\n";
				Sleep(3000);
				system("cls");
			}
			else
			{
				cout << "Что же, выбор ваш\n\n";
				Sleep(3000);
				guide();
			}
			break;

		case 3:
			if (i == 0)
			{
				cout << "Вы ведь промахнулись?";
				Sleep(3000);
				system("cls");
			}

			else
			{
				cout << "Как знайте...";
				Sleep(3000);
				exit(0);
			}
			
			break;

		default:
			if (i == 0) { cout << "Упс, такого нет((("; Sleep(3000); system("cls"); }
			if(i == 1) { cout << "Ничего страшного, с кем не бывает, вторая попытка..."; Sleep(3000); system("cls"); }
			if (i == 2) { cout << "Неужели снова промахнулись?"; Sleep(3000); system("cls"); }
			if (i == 3) { cout << "Такое не может быть вечно"; Sleep(3000); system("cls"); }
			if (i == 4) { cout << "Это начинает надоедать..."; Sleep(3000); system("cls"); }
			if (i == 5) { cout << "Поверить не могу, мы потеряли уже 18 секунд"; Sleep(3000); system("cls"); }
			if (i == 6) { cout << "Довольно!"; Sleep(3000); MainMenu(); }
			
			break;
		}
	}
}

int MNDebSize()
{
	int mydebsize = 0;
	for (int i = 0; i < MN_Global_debs_counter; i++)
	{
		mydebsize += Creditors[i]->GetSizeValue();
	}

	return mydebsize;
}

int DebSize()
{
	int debsize = 0;
	for (int i = 0; i < Global_debs_counter; i++)
	{
		debsize += Debs[i]->GetSizeValue();
	}

	return debsize;
}

void Statisitc()
{
	system("cls");

	int s1 = 0, s2 = 0;

		for(int i = 0; i < Global_debs_counter; i++)
		{
			s1 += Debs[i]->GetSizeValue();
		}

		for (int i = 0; i < MN_Global_debs_counter; i++)
		{
			s2 += Creditors[i]->GetSizeValue();
		}

		cout << "Сумма, которую должны вам: " << s1 << "\n\nСумма, которую вы должны: " << s2 << "\n\n\n\nОбщая сумма: " << s1 - s2 << "\n";

		if (s1 == 0 || s2 == 0)
		{
			cout << "Суммы, которые вы должны и вам должны не конфликутют  (Один из показателей равен 0)\n\n";
		}

		else
		{

			if (s1 - s2 < 0)
			{
				cout << "\n\nВаш долг больше чем, чем сумма которую вам должны\n\n";
			}

			else
			{
				cout << "\n\nВаши долги полнустью окупаются долгами, которые должны вам\n\n";
			}
		}

		char ch;
		cin >> ch;

		MainMenu();

}

void AddCreditor()
{
	system("cls");
	system("color 0a");



	int load_tm = 1 + rand() % (4); // Задаем рандомное зерно загрузки
	load_tm * 1000; //Получем конечное время мс

	char ft_name_ch[60]; 
	string ft_name;
	float deb_sz; // Размер долга



	cout << "Введите размер вашего долга (Только цифры!): ";
	cin >> deb_sz;
	getchar();

	if (deb_sz <= 0)
	{
		cout << "\n\nОшибка! Нельзя вводить отрицательные числа или ноль!\n\n"; //Проверка на отрицательное значение
		system("color 0c");
		Sleep(3000);
		Adddeb(); // Вызов функции заново
	}



	cout << "\n\nВведите имя вашего Кредитора: "; // Ввод необходимых данных
	cin.getline(ft_name_ch, 50, '\n');

	ft_name = ft_name_ch;

	for (int i = 0; i < MN_Global_debs_counter; i++)
	{
		if (ft_name == Creditors[i]->GetNameValue())
		{
			cout << "\n\nОшибка! Такое имя уже есть в базе данных, пожалуйста, измените имя\n\n";  //Проверка на совпадение имен
			system("color 0c");
			Sleep(3000);

			Adddeb(); // Вызов функции заново
		}
	}




	cout << "Добавление Кредитора, ждите...\n\n";
	Sleep(load_tm);

	if (MN_Global_debs_counter == 0)
	{
		Creditors[0] = new Dbtor(ft_name); // Создание нового экемпляра с введенными характеристиками (если это первый кредитор)
		Creditors[0]->SetSizeValue(deb_sz);
	}

	else
	{
		Creditors[MN_Global_debs_counter] = new Dbtor(ft_name); // Создание нового экемпляра с введенными характеристиками
		Creditors[MN_Global_debs_counter]->SetSizeValue(deb_sz);
	}

	system("cls");
	cout << "Кредитор успешно добавлен\n\n";
	MN_Global_debs_counter++; //Увелечение числа кредиторов на один

	getchar();

	WriteDebs();

	MyDebs();
}

void OutputCreditors()
{
	for (int i = 0; i <= MN_Global_debs_counter - 1; i++)
	{
		cout << i + 1 << " - Имя: " << Creditors[i]->GetNameValue(); //Вывожу информацию о должнике
		cout << "\n";
		cout << "\nРазмер вашего долга: \n\n" << Creditors[i]->GetSizeValue();
		cout << " Руб\n\n\n";
	}
}

void CreditorsList()
{
	system("cls");
	system("color 0a");


	char cj;

	cout << "Список всех кредиторов: \n\n";

	if (MN_Global_debs_counter == 0)
	{
		cout << "***ПУСТО***\n\n\n";
	}

	for (int i = 0; i <= MN_Global_debs_counter - 1; i++)
	{
		cout << i + 1 << " - Имя: " << Creditors[i]->GetNameValue(); //Вывожу информацию о должнике
		cout << "\nРазмер вашего долга: " << Creditors[i]->GetSizeValue();
		cout << " Руб\n\n";
	}


	cin >> cj;

	getchar();

	WriteDebs();

	MyDebs();

}

void DelCreditor()
{
	system("color 0a");
	system("cls");
	int ch;
	int sv_par;
	int lscon = 0;
	int CreditList[100];

	if (MN_Global_debs_counter == 0)
	{
		cout << "Нет профилей, которые можно удалить!\n\nВозврат в главное меню...\n\n";
		Sleep(3000);
		MyDebs();
	}



	system("cls");
	cout << "Введите индекс кредитора, которого  вы хотите удалить (Введите 0, если не хотите никого удалять)\n\n" << endl;

	OutputCreditors();



	cin >> ch;

	if (ch == 0)
	{
		MyDebs();
	}
	ch--;

  

	if (ch > MN_Global_debs_counter || ch < 0)
	{
		cout << "Такого индекска не сущетсвует!\n\n";
		
		system("color 0c");
		Sleep(3000);
		DelCreditor();
	}

	sv_par = ch;

	system("cls");

	int i = MN_Global_debs_counter - ch;


	for (int j = 0; j < i; j++)
	{
		Creditors[ch + j] = Creditors[ch + j + 1];
	}

	delete Debs[MN_Global_debs_counter];

	MN_Global_debs_counter--;

	cout << "Удаление прошло успешно";

	Sleep(3000);

	WriteDebs();

	MyDebs();
	
}


int LoadDebs()
{
	ifstream spid;
	ifstream DataB;
	spid.open(DefaultWay1);
	bool b1, b2;

	if (!spid.is_open())
	{
		b1 = true;
	}

	char buffer[500];



	spid.getline(buffer, 4);

	Global_debs_counter = atoi(buffer);
	string nm;
	

	for (int i = 0; i < Global_debs_counter; i++)
	{
		spid.getline(buffer, 50);
		nm = buffer;
		Debs[i] = new Dbtor(nm);

		//cout << "Name: " << nm;

		spid.getline(buffer, 9);
		Debs[i]->SetSizeValue(atoi(buffer));

		//cout << "\nSize: " << atoi(buffer) << "\n\n";
	}

	spid.close();

	DataB.open(DefaultWay2);

	if (!DataB.is_open())
	{
		b2 = true;
	}

	DataB.getline(buffer, 4);

	MN_Global_debs_counter = atoi(buffer);
	for (int i = 0; i < MN_Global_debs_counter; i++)
	{
		DataB.getline(buffer, 50);
		nm = buffer;
		Creditors[i] = new Dbtor(nm);

		//cout << "Name: " << nm;

		DataB.getline(buffer, 9);
		Creditors[i]->SetSizeValue(atoi(buffer));

		//cout << "\nSize: " << atoi(buffer) << "\n\n";
	}


	DataB.close();

	if (b1 == 1 && b2 == 1)
	{
		return(1);
	}

	if (b1 == 1 || b2 == 1)
	{
		return(2);
	}

	return(0);

}

void MyDebs() //Параметры собственного долга
{
	int ch;
	system("cls");
	system("color 0a");

	cout << "Размер вашего суммарного долга: " << MNDebSize() << " Руб\n\n";

	cout << "\n1 - Добавить Кредитора\n2 - Вывести список всех кредиторов\n3 - Удалить кредиотора\n4 - Оннулирвоать долги\n5 - Вернуться в главное меню\n\n";
	cin >> ch;
	cout << "\n\n";

	switch (ch)
	{
	case 1:
		AddCreditor();
		break;

	case 2:
		CreditorsList();
		break;

	case 3:
		DelCreditor();
		break;
		
	case 4:
		MN_Global_debs_counter = 0;
		WriteDebs();
		MyDebs();
		break;

	default:
		MainMenu();
		break;

	}


}



void StartSystem()
{
	system("color 0a");
	cout << "VERSION: "<< VERSION << "                        STARTING SYSTEM...\n\n\n\n\n\n";
	Sleep(3000);
	cout << "- Load DATA BASE: \n\n\a";
	Sleep(100);
	cout << "  - PROFILES\n\n\n\n\n\n";
	Sleep(400);

	int code = LoadDebs();
	
	if (code == 1)
	{
		isFirst = true;
		WriteDebs();
	}

	if (code == 2)
	{
		system("color 0c");
		cout << "DANGER!!! YOUR DATA WAS DESTROYED!!!\n\nDiagnostic...\n\n";
		WriteDebs();
		Sleep(5000);
	}



	cout << "- PROCCESES:\n\n\a- ";
	Sleep(300);
	cout << " - SUBLIMITION\n- ";
	Sleep(300);
	cout << "  - CORE EMISSION\n- ";
	Sleep(300);
	cout << "   - SECURE CHECKING\n- ";
	Sleep(300);
	cout << "    - TEMPLATE BOX READING\n- ";
	Sleep(100);
	cout << "     - CHECKING SYMBOLS SETTINGS\n- ";
	Sleep(500);
	cout << "      - MATHLOGER\n- ";
	Sleep(100);
	cout << "       - STARTING MAIN PROCESS...\n- ";


	Sleep(1000);


	cout << "\n\n\n";
	for (int i = 0; i < 5000; i++)
	{
		cout << 0 + rand() % (9999 + 1) << " ";
	}


	system("cls");
}


void MainMenu() // Глваное меню программы
{
	system("cls");
	system("color 0a");
	if (isFirst == true)
	{
		guide();
	}

	int ch; // Управляющая переменная
	cout << "Выберите действие которое хотите совершить:\n\n\n1 - Добавить должника\n2 - Посмотреть список всех должников\n3 - Изменить информацию о должнике\n4 - Удалить должника\n5 - Удалить всех должников\n\n\n6 - Режим просмотра кредиторов\n\n7 - Статистика финансов\n8 - Инструкция по работе с программой\n\n";
	cin >> ch;
	switch (ch)
	{
	case 1: 
		Adddeb();
		break;
	case 2:
		system("cls");
		DebList();
		break;
	case 3:
		ChangeInfo();
		break;
	case 4:
		DelDebs();
		break;

	case 5:
		Global_debs_counter = 0;
		WriteDebs();
		MainMenu();

		break;
	case 6:
		MyDebs();
		break;
	case 7:
		Statisitc();
		break;
	case 8:
		guide();
		break;
	default:
		MainMenu();
		break;
	}
}

int main() // Main функция
{
	
	srand(time(0));
	system("color 0a");

	//LoadDebs();
	

	StartSystem();                      

	
	

	setlocale(LC_CTYPE, "Russian");
	
	MainMenu();
    

	getchar();
    return 0;
}

void DelDebs()
{
	system("color 0a");
	system("cls");
	int ch;
	int sv_par;
	int lscon = 0;
	int DelList[100];

	if (Global_debs_counter == 0)
	{
		cout << "Нет профилей, которые можно удалить!\n\nВозврат в главное меню...\n\n";
		Sleep(3000);
		MainMenu();
	}



	system("cls");
	cout << "Введите индекс должника, которого  вы хотите удалить (Введите 0, если не хотите никого удалять)\n\nЕсли вы хотите удалить сразу несколько должников, введите -1\n\n" << endl;

	OutputDebs();



	cin >> ch;
	if (ch == 0)
	{
		MainMenu();
	}
	ch--;

	if (ch == -1)
	{
		cout << "Введите количество должников, которое вы хотите удалить: ";
		cin >> lscon;
		if (lscon <= 0)
		{
			cout << "Error!";
			system("color 0c");
			DelDebs();
		}
	}
	


	if (ch > Global_debs_counter)
	{
		cout << "Error!\n\n";
		system("color 0c");
		DelDebs();
	}

	sv_par = ch;

	system("cls");

	int i;
    
	/*Debs[Global_debs_counter] = Debs[ch];
	delete Debs[Global_debs_counter];
	Global_debs_counter--;*/

	i = Global_debs_counter - ch;

	for (int j = 0; j < i; j++)
	{
		Debs[ch + j] = Debs[ch + j + 1];
	}

	delete Debs[Global_debs_counter];

	Global_debs_counter--;

	cout << "Удаление прошло успешно";

	Sleep(3000);

	WriteDebs();

	MainMenu();

}

void Adddeb() //Добавить должника
{
	system("cls");
	system("color 0a");

	

	int load_tm = 1 + rand() % (4); // Задаем рандомное зерно загрузки
	load_tm * 1000; //Получем конечное время мс

	char ft_name_ch[60]; //Переменные с временным именем и будущем. Вынужденная мера - gets_s() принимает только char, а в конструктор необходимо передать string
	string ft_name;
	float deb_sz; // Размер долга

	

	cout << "Введите размер текущего долга (Только цифры!): ";
	cin >> deb_sz;
	getchar();

	if (deb_sz <= 0)
	{
		cout << "\n\nОшибка! Нельзя вводить отрицательные числа или ноль!\n\n"; //Проверка на отрицательное значение
		system("color 0c");
		Sleep(3000);
		Adddeb(); // Вызов функции заново
	}



	cout << "\n\nВведите имя должника: "; // Ввод необходимых данных
	cin.getline(ft_name_ch, 50, '\n');

	ft_name = ft_name_ch;

	for (int i = 0; i < Global_debs_counter; i++)
	{
		if (ft_name == Debs[i]->GetNameValue())
		{
			cout << "\n\nОшибка! Такое имя уже есть в базе данных, пожалуйста, измените имя\n\n";  //Проверка на совпадение имен
			system("color 0c");
			Sleep(3000);

			Adddeb(); // Вызов функции заново
		}
	}
	

	

	cout << "Добавление должника, ждите...\n\n"; 
	Sleep(load_tm);

	if (Global_debs_counter == 0)
	{
		Debs[0] = new Dbtor(ft_name); // Создание нового экемпляра с введенными характеристиками (если это первый должник)
		Debs[0]->SetSizeValue(deb_sz);
	}

	else
	{
		Debs[Global_debs_counter] = new Dbtor(ft_name); // Создание нового экемпляра с введенными характеристиками
		Debs[Global_debs_counter]->SetSizeValue(deb_sz);
	}

	system("cls");
	cout << "Должник успешно добавлен\n\n";
	Global_debs_counter++; //Увелечение числа должников на один

	getchar();

	WriteDebs();

	MainMenu();
	
}

void ChangeInfo(int svp)
{
	system("cls");
	system("color 0a");

	int ch, par, nw_size, sv_par = svp;
	char nw_name[52];
	string nw_name_str;
	cout << "Имя: " << Debs[svp]->GetNameValue() << "\nРазмер долга: " << Debs[svp]->GetSizeValue() << "\n\n";

	cout << "Какой параметр вы хотите изменить ?\n\n1 - Имя\n2 - Размер долга\n\n\n";
	cin >> par;

	switch (par)
	{
	case 1:
		cout << "Введите новое имя: ";
		gets_s(nw_name);
		nw_name_str = nw_name;

		Debs[sv_par]->SetNameValue(nw_name_str);
		system("cls");
		cout << "\n\nИмя успешно изменено\n\nЧто вы хотите сделать дальше?\n\n1 - Продолжить изменение параметров\n2 - Выйти из этого меню\n\n" << endl;
		cin >> ch;
		switch (ch)
		{
		case 1:
			ChangeInfo();
			break;
		case 2:
			MainMenu();
			break;
		default:
			cout << "Неправильный ввод!\n\n";
			system("color 0c");
			ChangeInfo();
			break;
		}
		break;

	case 2:
		cout << "Введите размер нового долга: ";
		cin >> nw_size;
		Debs[sv_par]->SetSizeValue(nw_size);
		system("cls");
		cout << "\n\nРазмер долга успешно изменен\n\nЧто вы хотите сделать дальше?\n\n1 - Продолжить изменение параметров\n2 - Выйти из этого меню\n\n" << endl;
		cin >> ch;
		switch (ch)
		{
		case 1:
			ChangeInfo();
			break;
		case 2:
			MainMenu();
			break;
		default:
			cout << "Неправильный ввод!\n\n";
			ChangeInfo();
			break;
		}
		break;

	default:
		cout << "Неправильный ввод!\n\n";
		system("color 0c");
		ChangeInfo();
		break;

	}

	WriteDebs();
}

void ChangeInfo()
{
	system("color 0a");
	int ch, par,  nw_size, sv_par;
	char nw_name[52];
	string nw_name_str;
	system("cls");


	if (Global_debs_counter == 0)
	{
		cout << "Нет профилей, которые можно изменить!\n\nВозврат в главное меню...\n\n";
		Sleep(3000);
		MainMenu();
	}

	cout << "Введите индекс должника, ифнормацию о котором вы хотите изменить : \n\n" << endl;

	OutputDebs();

	

	cin >> ch;
	if (ch == 0)
	{
		cout << "Error!\n\n";
		system("color 0c");
		ChangeInfo();
	}
	ch--;


	

	if (ch > Global_debs_counter)
	{
		cout << "Error!\n\n";
		system("color 0c");
		ChangeInfo();
	}

	sv_par = ch;

	system("cls");
    
	cout << "Имя: " << Debs[ch]->GetNameValue() << "\nРазмер долга: " << Debs[ch]->GetSizeValue() << "\n\n";

	cout << "Какой параметр вы хотите изменить ?\n\n1 - Имя\n2 - Размер долга\n\n\n";
	cin >> par;

	switch (par)
	{
	case 1:
		cout << "Введите новое имя: ";
		gets_s(nw_name);
		system("cls");
		nw_name_str = nw_name;

		Debs[sv_par]->SetNameValue(nw_name_str);

		cout << "\n\nИмя успешно изменено\n\nЧто вы хотите сделать дальше?\n\n1 - Продолжить изменение параметров\n2 - Выйти из этого меню\n\n" << endl;
		cin >> ch;

		WriteDebs();

		switch (ch)
		{
		case 1:
			ChangeInfo(sv_par);
			break;
		case 2:
			MainMenu();
			break;
		default:
			cout << "Неправильный ввод!\n\n";
			system("color 0c");
			ChangeInfo(sv_par);
			break;
		}
		break;

	case 2:
		cout << "Введите размер нового долга: ";
		cin >> nw_size;
		system("cls");
		Debs[sv_par]->SetSizeValue(nw_size);
		cout << "\n\nРазмер долга успешно изменен\n\nЧто вы хотите сделать дальше?\n\n1 - Продолжить изменение параметров\n2 - Выйти из этого меню\n\n" << endl;
		WriteDebs();
		cin >> ch;
		switch (ch)
		{
		case 1:
			ChangeInfo(sv_par);
			break;
		case 2:
			MainMenu();
			break;
		default:
			cout << "Неправильный ввод!\n\n";
			system("color 0c");
			ChangeInfo(sv_par);
			break;
		}
		break;

	default:
		cout << "Неправильный ввод!\n\n";
		system("color 0c");
		ChangeInfo(sv_par);
		break;

	}

	

}

void DebList()
{

	char cj;

	cout << "Список всех должников (" << Global_debs_counter << "):\n\n\n";

	if (Global_debs_counter == 0)
	{
		cout << "***ПУСТО***\n\n\n";
	}

	for (int i = 0; i <= Global_debs_counter - 1; i++)
	{
		cout << i + 1 << " - Имя: " << Debs[i]->GetNameValue(); //Вывожу информацию о должнике
		cout << "\nРазмер долга: " << Debs[i]->GetSizeValue();
		cout << " Руб\n\n";

		
	}

	
	cin >> cj;

	getchar();

	MainMenu();

	

}

void OutputDebs()
{
	for (int i = 0; i <= Global_debs_counter - 1; i++)
	{
		cout << i + 1 << " - Имя: " << Debs[i]->GetNameValue(); //Вывожу информацию о должнике
		cout << "\n";
		cout << "\nРазмер долга: \n\n" << Debs[i]->GetSizeValue();
		cout << " Руб\n\n\n";
	}
}