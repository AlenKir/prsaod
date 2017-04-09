#include <iostream>
#include <Windows.h>
#include <memory>
using namespace std;
//поиск SIM-карты по номеру SIM-карты
//место и дата выдачи паспорта
//ввод года рождения
//нормальный проход дерева
//сортировка
//уникальность паспорта
//общий ввод чаровского массива

const int SEG = 100;
int hash_func(char *str);

struct SIM
{
	/*№ SIM - карты – строка формата «NNN - NNN NNN N», где N –цифра;
	Тариф – строка;
	Год выпуска – целое;
	Признак наличия – логическое*/
	char SIM_num[12];
	char tarif[10];
	unsigned int year;
	bool isFree;
	bool isDeleted;
	int key;

	SIM()
	{	}

	SIM(char *n, char *t, int y, bool free)
	{
		for (int i = 0; i < 11; ++i)
			SIM_num[i] = n[i];
		SIM_num[11] = 0;
		int i = 0;
		for (int i = 0; i < 10; i++)
		{
			if (t[i])
				tarif[i] = t[i];
			else
			{
				tarif[i] = 0;
			}
		}
		year = y;
		isFree = free;
		isDeleted = false;
		key = hash_func(n);
	}
};

void printchar(char* m)
{
	int i = 0;
	while (m[i])
	{
		std::cout << m[i];
		i++;
		if (m[i] == '\n')
			m[i] = 0;

	}
	std::cout << endl;
}

char *enterNsim()
{
	char *num = new char[12];
	std::cout << "Введите номер в формате 10 цифр. Тире будет добавлено автоматически." << endl;
	for (int i = 0; i < 11; i++)
	{
		if (i == 3)
		{
			num[i] = '-'; i++;
		}
		cin >> num[i];
	}
	num[11] = 0;
	printchar(num);
	return num;
}

char *enterPasp()
{
	char *num = new char[12];
	std::cout << "Введите номер паспорта в формате 10 цифр. Тире будет добавлено автоматически." << endl;
	for (int i = 0; i < 11; i++)
	{
		if (i == 4)
		{
			num[i] = '-'; i++;
		}
		cin >> num[i];
	}
	num[11] = 0;
	printchar(num);
	return num;
}

char *enterTarif()
{
	char *t = new char[10];
	std::cout << "Введите тариф. Одно слово, без пробелов." << endl;
	getchar();
	for (int i = 0; i < 10; ++i)
		t[i] = 0;
	fgets(t, 10, stdin);
	return t;
}

int enterY()
{
	int y = 0;
	std::cout << "Введите год выпуска:" << endl;
	cin >> y;
	return y;
}

SIM *addSIM()
{
	SIM *newbie;
	char *num = new char[12]; num = enterNsim();
	char *t = new char[12]; t = enterTarif();
	int y = enterY();
	newbie = new SIM(num, t, y, true);
	return newbie;
}

char *enterPlaceNdate()
{
	char *num = new char[20];
	std::cout << "Здесь Вы можете указать данные о выдаче паспорта." << endl;
	cout << "Введите место выдачи паспорта." << endl;
	getchar();
	for (int i = 0; i < 10; ++i)
		num[i] = 0;
	fgets(num, 20, stdin);
	num[19] = 0;
	printchar(num);
	return num;
}

char *enterFIO()
{
	char *num = new char[10];
	std::cout << "Введите имя клиента." << endl;
	for (int i = 0; i < 10; ++i)
		num[i] = 0;
	fgets(num, 10, stdin);
	printchar(num);
	return num;
}

bool exists(SIM *s)
{
	if (s)
		if (!s->isDeleted)
			return true;
	return false;
}

bool samemas(char *a, char *b, int am)
{
	for (int i = 0; i < am; ++i)
	{
		if (a[i] != b[i])
			return false;
	}
	return true;
}

void printsim(SIM *sim)
{
	if (exists(sim))
	{
		printchar(sim->SIM_num);
		printchar(sim->tarif);
		std::cout << sim->year << endl;
		if (!sim->isFree && !sim->isDeleted)
			std::cout << "Карта находится в пользовании." << endl;
		else
			std::cout << "Карта свободна." << endl;
	}
}

int hash_func(char *str)
{
	int N = 0;
	N = str[0] + str[1] * 1.5 + str[2] * 3 + str[4] * 4 + str[5] * 5 + str[6] * 6 + str[7] * 7 + str[8] * 8 + str[9] * 9 + str[10] * 9.5;
	N = N * N;
	N = N % SEG;
	return N;
}

int hashplus(SIM *h[SEG], char *s)
{
	int i = hash_func(s);
	int j = 1;
	while (j<100)
	{
		if (!h[i])
		{
			return i;
		}
		else
		{
			if (samemas(s, h[i]->SIM_num, 12))
			{
				return -1;
			}
		}
		i += 3 * j;
	}
}

struct status
{
	char SIM_num[12];
	char pasport[12];
	unsigned int dateGiven[3];
	unsigned int dateEnd[3];
	status *next;

	status(char *s_num)
	{
		for (int i = 0; i < 11; ++i)
			SIM_num[i] = s_num[i];
		SIM_num[11] = '/0';

		for (int i = 0; i < 11; ++i)
			pasport[i] = 0;
		pasport[11] = '/0';

		dateGiven[0] = 0; dateGiven[1] = 0; dateGiven[2] = 0;
		dateEnd[0] = 0; dateEnd[1] = 0; dateEnd[2] = 0;
		next = 0;
	}

	status(char *s_num, char *pasp, int dg[3], int de[3])
	{
		for (int i = 0; i < 11; ++i)
			SIM_num[i] = s_num[i];
		SIM_num[11] = '/0';

		for (int i = 0; i < 11; ++i)
			pasport[i] = pasp[i];
		pasport[11] = '/0';

		dateGiven[0] = dg[0]; dateGiven[1] = dg[1]; dateGiven[2] = dg[2];
		dateEnd[0] = de[0]; dateEnd[1] = de[1]; dateEnd[2] = de[2];
		next = 0;
	}
};

struct Client
{
	// № паспорта – строка формата «NNNN - NNNNNN», где N –цифры;
	// Место и дата выдачи паспорта – строка;
	// ФИО – строка;
	// Год рождения – целое;
	// Адрес – строка;

	int  key;
	int  height;
	Client *left;
	Client *right;

	char pasport[12];
	char placeNdate[20];
	char FIO[10];
	int bdyear;
	char address[10];

	Client() {}

	Client(char *p, char *plNd, char *f, int y, char *ad)
	{
		for (int i = 0; i < 11; ++i)
			pasport[i] = p[i];
		pasport[11] = 0;
		std::hash<std::string> h;
		key = h(p);

		for (int i = 0; i < 20; i++)
		{
			if (plNd[i])
				placeNdate[i] = plNd[i];
			else
			{
				placeNdate[i] = 0;
			}
		}

		for (int i = 0; i < 10; i++)
		{
			if (f[i])
				FIO[i] = f[i];
			else
			{
				FIO[i] = 0;
			}
		}

		bdyear = y;

		for (int i = 0; i < 10; i++)
		{
			if (ad[i])
				address[i] = ad[i];
			else
			{
				address[i] = 0;
			}
		}
		left = right = 0;
		height = 1;
	}
};

int height(Client *p)
{
	if (p)
		return p->height;
	else
		return 0;
}

void cor_height(Client* p)
{
	int hleft = height(p->left);
	int hright = height(p->right);
	if (hleft > hright)
		p->height = hleft + 1;
	else
		p->height = hright + 1;
}

int bal_factor(Client *p)
{
	int factor = height(p->right) - height(p->left);
	return factor;
}

Client *rotateright(Client *p)
{
	Client* q = p->left;
	p->left = q->right;
	q->right = p;
	cor_height(p);
	cor_height(q);
	return q;
}
Client *rotateleft(Client *q)
{
	Client* p = q->right;
	q->right = p->left;
	p->left = q;
	cor_height(q);
	cor_height(p);
	return p;
}

Client *balance(Client *p)
{
	cor_height(p);
	if (bal_factor(p) == 2)
	{
		if (bal_factor(p->right) < 0)
			p->right = rotateright(p->right);
		return rotateleft(p);
	}
	if (bal_factor(p) == -2)
	{
		if (bal_factor(p->left) > 0)
			p->left = rotateleft(p->left);
		return rotateright(p);
	}
	return p;
}

Client *insert(Client *root, int key, Client *c)
{
	if (!root)
	{
		Client *t = new Client(c->pasport, c->placeNdate, c->FIO, c->bdyear, c->address);
		return t;
	}
	else
	{
		if (key < root->key)
			root->left = insert(root->left, key, c);
		else
			root->right = insert(root->right, key, c);
	}
	return balance(root);
}

void printClient(Client *c)
{
	printchar(c->pasport);
	printchar(c->placeNdate);
	printchar(c->FIO);
	cout << c->bdyear << endl;
	printchar(c->address);
}

void print(Client *p, int level)
{
	if (p)
	{
		print(p->left, level + 1);
		printClient(p);
		print(p->right, level + 1);
	}
}

Client *addClient()
{
	Client *c;
	char *pasport = new char[12]; pasport = enterPasp();
	char *placeNdate = new char[20]; placeNdate = enterPlaceNdate();
	char *FIO = new char[10]; FIO = enterFIO();
	int bdyear = 0;
	char address[10];
	c = new Client(pasport, placeNdate, FIO, bdyear, address);
	return c;
}

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	SIM *hlist[SEG];
	for (int i = 0; i < SEG; ++i)
	{
		hlist[i] = 0;
	}

	Client *tree = new Client("", "", "", 0, "");

	int item = -1;
	std::cout << "Добро пожаловать в систему обслуживания клиентов оператора сотовой связи!" << endl;
	while (item != 0)
	{
		std::cout << "Работа с данными о СИМ-картах:" << endl;
		std::cout << "\t 1. добавление новой SIM-карты" << endl;
		std::cout << "\t 2. удаление сведений о SIM-карте" << endl;
		std::cout << "\t 3. просмотр всех имеющихся SIM-карт" << endl;
		std::cout << "\t 4. очистка данных о SIM-картах" << endl;
		std::cout << "\t 5. поиск SIM-карты по номеру SIM-карты. " << endl;
		/* Результаты поиска – все сведения о найденной SIM - карте, а также ФИО и № паспорта
		клиента, которому выдана эта SIM - карта; " */
		std::cout << "\t 6. поиск SIM-карты по тарифу. " << endl;
		/*Результаты поиска – список найденных
		SIM - карт с указанием «№ SIM - карты», тарифа, года выпуска*/

		std::cout << "Работа с данными о клиентах:" << endl;
		std::cout << "\t 7. регистрация нового клиента" << endl;
		std::cout << "\t 8. снятие с обслуживания клиента" << endl;
		std::cout << "\t 9. просмотр всех зарегистрированных клиентов" << endl;
		std::cout << "\t 10. очистка данных о клиентах" << endl;
		std::cout << "\t 11. поиск клиента по номеру паспорта." << endl;
		/*Pезультаты поиска – все сведения о
		найденном клиенте и номера SIM - карт, которые ему выданы*/
		std::cout << "\t 12. поиск клиента по фрагментам ФИО или адреса" << endl;
		/*Результаты поиска –
		список найденных клиентов с указанием № паспорта, ФИО и адреса*/

		std::cout << "Часто исполняемые действия:" << endl;
		std::cout << "\t 13 - Регистрация выдачи клиенту SIM-карты" << endl;
		std::cout << "\t 14 - Регистрация возврата SIM-карты от клиента" << endl;
		std::cout << "Введите пункт меню." << endl;
		cin >> item;

		switch (item)
		{
		case 1:
		{
			std::cout << "Добавление новой SIM-карты:" << endl;
			SIM *newbie = addSIM();
			int j = -1;
			int am = 0;
			while (j == -1 && am < 100)
			{
				j = hashplus(hlist, newbie->SIM_num);
				if (j != -1)
					hlist[j] = newbie;
				else
				{
					cout << "Данная SIM-карта уже присутствует в базе." << endl; break;
				}
				am++;
			}
			if (am == 100)
				cout << "Невозможно добавление СИМ-карты с таким номером." << endl;
			break;
		}
		case 2:
		{
			std::cout << "Удаление сведений о SIM-карте:" << endl;
			char *n = new char[12]; n = enterNsim();
			bool found = false;
			int i = hash_func(n);
			int am = 0;
			for (int j = 1; am < SEG; i += 3 * j, ++j, ++am)
			{
				if (exists(hlist[i]))
					if (samemas(hlist[i]->SIM_num, n, 12))
					{
						hlist[i] = 0;
						found = true;
						cout << "Удаление произведено." << endl;
					}
				if (found)
					break;
				if (i >= SEG)
					i = i % SEG;
			}
			if (!found)
				cout << "Карты не обнаружено." << endl;
			break;
		}
		case 3:
		{
			bool found = false;
			std::cout << "Просмотр сведений о SIM-картах:" << endl;
			for (int i = 0; i < SEG; ++i)
			{
				printsim(hlist[i]);
				if (exists(hlist[i]))
					found = true;
			}
			if (!found)
				cout << "SIM-карт в базе не обнаружено." << endl;
			break;
		}
		case 4:
		{
			cout << "Oчистка данных о SIM-картах:" << endl;
			for (int i = 0; i < SEG; ++i)
			{
				hlist[i] = 0;
			}
			cout << "База SIM-карт пуста." << endl;
			break;
		}
		case 5:
		{
			cout << "Поиск SIM-карты по номеру SIM-карты:" << endl;
			char *n = new char[12]; n = enterNsim();
			bool found = false;
			int i = hash_func(n);
			int am = 0;
			for (int j = 1; am < SEG; i += 3 * j, ++j, ++am)
			{
				if (i >= SEG)
					i = i % SEG;
				if (exists(hlist[i]))
					if (samemas(hlist[i]->SIM_num, n, 12))
					{
						found = true;
						printsim(hlist[i]);
					}
				if (found)
					break;
			}
			if (!found)
				cout << "Карты не обнаружено." << endl;
			break;
		}
		case 6:
		{
			bool found = false;
			cout << "Поиск SIM-карты по тарифу:" << endl;
			char *t = new char[10]; t = enterTarif();
			for (int i = 0; i < SEG; ++i)
			{
				if (exists(hlist[i]))
					if (samemas(hlist[i]->tarif, t, 10))
						printsim(hlist[i]);
			}
			if (!found)
				cout << "Карт не обнаруженo." << endl;
			break;
		}
		case 7:
		{
			cout << "Регистрация нового клиента:" << endl;
			Client *c = addClient();

			tree = insert(tree, c->key, c);

			//tree = insert(tree, key);
			//tree = balance(tree);

			cout << "Невозможно добавление клиента с таким же номером паспорта." << endl;
			break;
		}
		case 8:
		{
			cout << "Снятие с обслуживания клиента" << endl;
			break;
		}
		case 9:
		{
			cout << "Просмотр всех зарегистрированных клиентов" << endl;
			print(tree, 0);
			break;
		}
		case 10:
		{
			cout << "Очистка данных о клиентах." << endl;
			Client *tree = new Client("", "", "", 0, "");
			break;
		}
		case 11:
		{
			cout << "Поиск клиента по номеру паспорта" << endl;
			break;
		}
		case 12:
		{
			cout << "Поиск клиента по фрагментам ФИО или адреса" << endl;
			break;
		}
		}
		cout << endl;
	}

	system("pause");
	return 0;
}

