#include <iostream>
#include <Windows.h>
#include <vector>
#include <string>
using namespace std;



void printField(short int**);
void color(short int**, short int, short int);
void createFieldInfo(short int** &, short int);
bool checkEnd(short int**);
bool playerMove(short int**, short int** &, short int, short int);
void endGame(short int**, short int**);

short int fieldSize;//Размер поля
short int bombs;//Количество бомб
short int marked;//Помечено
bool Alive = true;

int main() {
	setlocale(LC_ALL, "ru");
	string difficultChoose;
	short int difficult;
	bool once = false;
	string endChoose;
	string move;
	cout << "Добро пожаловать в \"Сапёр\"!\nВ этой игре вам предстоит открыть все клетки не задев спрятанные бомбы.\n";

	do {
		if (once) cout << "Выберите КОРРЕКТНЫЙ уровень сложности:\n";
		else cout << "Выберите уровень сложности:\n"
			<< "1.Легко\n"
			<< "2.Средне\n"
			<< "3.Сложно\n"
			<< "4.Экстрим\n"
			<< "5.Безумие...\n";
		cin >> difficultChoose;
		once = true;
	} while (difficultChoose.size() != 1 || !(
		difficultChoose[0] == '1' ||
		difficultChoose[0] == '2' ||
		difficultChoose[0] == '3' ||
		difficultChoose[0] == '4' ||
		difficultChoose[0] == '5'));
	system("cls");
	difficult = stoi(difficultChoose);
	//Разный размер поля зависит от сложности
	if (difficult == 1)fieldSize = 5;
	else if (difficult == 2)fieldSize = 10;
	else if (difficult == 3)fieldSize = 15;
	else if (difficult == 4)fieldSize = 20;
	else if (difficult == 5)fieldSize = 37;
	//Создание поля
	short int** FieldInfo = new short int* [fieldSize];
	for (int i = 0; i < fieldSize; i++)FieldInfo[i] = new short int[fieldSize];

	//Создание видимого поля
	short int** showedField = new short int* [fieldSize];
	for (int i = 0; i < fieldSize; i++)showedField[i] = new short int[fieldSize];
	

	while (true) {
		//Установка значений массива в 0
		for (int y = 0; y < fieldSize; y++)
			for (int x = 0; x < fieldSize; x++) {
				showedField[y][x] = -1;//Скрытые ячейки
				FieldInfo[y][x] = 0;
			}
		//Заполнение бомбами и цифрами
		createFieldInfo(FieldInfo, difficult);
		once = true;
		bool once2 = false;
		while (Alive) {
			int x, y;
			if (once == false)system("cls");
			printField(showedField);
			if (once2) {
				cout << "Ход запрещён, клетка уже открыта!\n";
				once2 = false;
			}
			if (once) {
				once = false;
			moveErr:
				cout << "Выберите клетку(Сначала букву потом цифры СЛИТНО ПО-АНГЛИЙСКИ): ";
			}
			else cout << "Выберите клетку: ";
			cin >> move;
			//Проверка на дурака
			if (move.size() == 2 || move.size() == 3) {
				if (move[0] >= 97 && move[0] <= 122)x = move[0] - 97;
				else if (move[0] >= 65 && move[0] <= 90)x = move[0] - 65 + 26;
				else goto moveErr;
				bool checkx = false;
				short int counter = 0;
				short int u = 65;
				short int mod = 65;
				while (counter < fieldSize) {
					if (x == u - mod)checkx = true;
					if (u == 90) {
						u = 96 + 26;
						mod = 97;
					}
					counter++;
					u++;
				}
				if (checkx == false)goto moveErr;

				if ((move.size() == 2 && move[1] >= 49 && move[1] <= 57) || (move.size() == 3 && move[1] >= 49 && move[1] <= 57 && move[2] >= 48 && move[2] <= 57)) {
					string buf;
					for (int i = 1; i < move.size(); i++) {
						buf.push_back(move[i]);
					}
					y = stoi(buf) - 1;
					if (y > fieldSize || y < 0)goto moveErr;
				}
				else goto moveErr;
			}
			else goto moveErr;
			if (FieldInfo[y][x] == showedField[y][x])once2 = true;
			do {
				cout << "Открыть - 1\t Отметить - 2\n\tВыбираю ";
				cin >> move;
			} while (!(move.size() == 1 && (move[0] == '1' || move[0] == '2')));
			if (move[0] == '2') {
				if (FieldInfo[y][x] == showedField[y][x])once2 = true;
				else showedField[y][x] = 10;
			}
			else {
				if (playerMove(FieldInfo, showedField, x, y)) {//Если наступил на мину
					cout << "\n\n\n\n\t\t\t\tВы ";
					HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
					SetConsoleTextAttribute(console, ((0 << 4) | 4));
					cout << "проиграли";
					SetConsoleTextAttribute(console, ((0 << 4) | 7));
					cout << "...\n\n\n\n\n";
					Alive = false;
					endGame(FieldInfo, showedField);
				}
			}
		}

		cout << "\t\tЖелаете начать заново?(y)  Ответ: ";
		cin >> endChoose;
		if ((endChoose.size() == 1 && endChoose[0] == 'y') || endChoose == "yes") {
			Alive = true;
			system("cls");
			cout << endl;
		}
		else {
			cout << "\t\tНет так нет. Спасибо за игру!\n";
			system("pause");
			for (int i = 0; i < fieldSize; i++) {
				delete[] FieldInfo[i];
				delete[] showedField[i];
			}
			delete [] FieldInfo;
			delete [] showedField;
			return 0;
		}
	}
}
void printField(short int** Field) {
	marked = 0;
	for (int i = 0; i < fieldSize; i++)
		for (int j = 0; j < fieldSize; j++)
			if (Field[i][j] == 10)marked++;
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(console, ((0 << 4) | 7));
	cout << "     " << "Всего бомб\t\tПомечено" << endl;
	SetConsoleTextAttribute(console, ((0 << 4) | 12));
	cout << "     \t" << bombs << "\t\t   " << marked << endl;
	SetConsoleTextAttribute(console, ((0 << 4) | 7));
	cout << "     ";
	short int counter = 0;
	short int x = 97;
	while (counter < fieldSize) {
		char n = x;
		cout << ' ' << n << ' ';
		if (x >= 122)x = 64;
		counter++;
		x++;
	}

	cout << endl;
	for (int y = 0; y < fieldSize; y++) {
		if (y + 1 >= 10)cout << "   " << y + 1;
		else cout << "   " << y + 1 << " ";
		SetConsoleTextAttribute(console, ((7 << 4) | 0));
		for (int x = 0; x < fieldSize; x++) {
			color(Field, x, y);
			SetConsoleTextAttribute(console, ((7 << 4) | 0));
		}
		SetConsoleTextAttribute(console, ((0 << 4) | 7));
		cout << endl;
	}

	if (checkEnd(Field)) {//Если конец
		cout << "\n\n\n\n\t\t\t\tВы ";
		HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(console, ((0 << 4) | 2));
		cout << "победили";
		SetConsoleTextAttribute(console, ((0 << 4) | 7));
		cout << "...\n\n\n\n\n";
		Alive = false;
	}
}
void color(short int** Field, short int x, short int y) {
	short int state = Field[y][x];
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	if (state == -1) {//Скрытая ячейка
		cout << "[?]";
	}
	else if (state == 0) {//Открытая ячейка
		SetConsoleTextAttribute(console, ((8 << 4) | 0));
		cout << "   ";
	}
	else if (state == 1) {//Рядом 1 бомба
		SetConsoleTextAttribute(console, ((8 << 4) | 9));
		cout << ' ';
		cout << '1';//(синяя)
		cout << ' ';
	}
	else if (state == 2) {//Рядом 2 бомбы
		SetConsoleTextAttribute(console, ((8 << 4) | 2));
		cout << ' ';
		cout << '2';//(зелёная)
		cout << ' ';
	}
	else if (state == 3) {//Рядом 3 бомбы
		SetConsoleTextAttribute(console, ((8 << 4) | 4));
		cout << ' ';
		cout << '3';//(красная)
		cout << ' ';
	}
	else if (state == 4) {//Рядом 4 бомбы
		SetConsoleTextAttribute(console, ((8 << 4) | 1));
		cout << ' ';
		cout << '4';//(тёмно-синяя)
		cout << ' ';
	}
	else if (state == 5) {//Рядом 5 бомб
		SetConsoleTextAttribute(console, ((8 << 4) | 12));
		cout << ' ';
		cout << '5';//(коричневая)
		cout << ' ';
	}
	else if (state == 6) {//Рядом 6 бомб
		SetConsoleTextAttribute(console, ((8 << 4) | 11));
		cout << ' ';
		cout << '6';//(бирюзовая)
		cout << ' ';
	}
	else if (state == 7) {//Рядом 7 бомб
		SetConsoleTextAttribute(console, ((8 << 4) | 5));
		cout << ' ';
		cout << '7';//(фиолетовая)
		cout << ' ';
	}
	else if (state == 8) {//Рядом 8 бомб
		SetConsoleTextAttribute(console, ((8 << 4) | 0));
		cout << ' ';
		cout << '8';//(чёрная)
		cout << ' ';
	}
	else if (state == 9) {//Бомба
		SetConsoleTextAttribute(console, ((12 << 4) | 0));
		cout << ' ';
		cout << '*';//(чёрная)
		cout << ' ';
	}
	else if (state == 10) {
		cout << '[';
		SetConsoleTextAttribute(console, ((7 << 4) | 4));
		cout << '!';//(красный)
		SetConsoleTextAttribute(console, ((7 << 4) | 0));
		cout << ']';
	}
}
void createFieldInfo(short int** &Field, short int difficult) {
	//Разное количество мин зависит от сложности
	if (difficult == 1)bombs = 5;
	else if (difficult == 2)bombs = 20;
	else if (difficult == 3)bombs = 45;
	else if (difficult == 4)bombs = 80;
	else if (difficult == 5)bombs = 275;
	srand(time(NULL));
	short int counter = 0;
	while (counter < bombs) {
		short int x, y;
		x = rand() % fieldSize;
		y = rand() % fieldSize;
		if (Field[y][x] != 9) {
			Field[y][x] = 9;
			counter++;
		}
	}

	//Дальше генерим цифры
	for(int i = 0; i < fieldSize; i++)
		for (int j = 0; j < fieldSize; j++) {
			short int bombCounter = 0;
			if (Field[i][j] != 9) {
				if (i - 1 >= 0 && j - 1 >= 0)if (Field[i - 1][j - 1] == 9)bombCounter++;
				if (i - 1 >= 0)if (Field[i - 1][j] == 9)bombCounter++;
				if (i - 1 >= 0 && j + 1 < fieldSize)if (Field[i - 1][j + 1] == 9)bombCounter++;
				if (j - 1 >= 0)if (Field[i][j - 1] == 9)bombCounter++;
				if (j + 1 < fieldSize)if (Field[i][j + 1] == 9)bombCounter++;
				if (i + 1 < fieldSize && j - 1 >= 0)if (Field[i + 1][j - 1] == 9)bombCounter++;
				if (i + 1 < fieldSize)if (Field[i + 1][j] == 9)bombCounter++;
				if (i + 1 < fieldSize && j + 1 < fieldSize)if (Field[i + 1][j + 1] == 9)bombCounter++;
				Field[i][j] = bombCounter;
			}
		}
}
bool checkEnd(short int** Field) {
	int counter = 0;
	for (int i = 0; i < fieldSize; i++)
		for (int j = 0; j < fieldSize; j++)
			if (Field[i][j] == -1)counter++;
	if (counter + marked == bombs)return true;
	return false;
}
bool playerMove(short int** FieldInfo, short int** &Field,short int x, short int y) {
	if(FieldInfo[y][x] == 9)return true;
	if (FieldInfo[y][x] == Field[y][x])return false;//Если клетка уже открыта
	Field[y][x] = FieldInfo[y][x];

	//Если открылось пустое поле то открываем все рядом
	if (Field[y][x] == 0) {
		if (y - 1 >= 0 && x - 1 >= 0) {
			playerMove(FieldInfo, Field, x - 1, y - 1);
		}
		if (y - 1 >= 0) {
			playerMove(FieldInfo, Field, x, y - 1);
		}
		if (y - 1 >= 0 && x + 1 < fieldSize) {
			playerMove(FieldInfo, Field, x + 1, y - 1);
		}
		if (x - 1 >= 0) {
			playerMove(FieldInfo, Field, x - 1, y);
		}
		if (x + 1 < fieldSize) {
			playerMove(FieldInfo, Field, x + 1, y);
		}
		if (y + 1 < fieldSize && x - 1 >= 0) {
			playerMove(FieldInfo, Field, x - 1, y + 1);
		}
		if (y + 1 < fieldSize) {
			playerMove(FieldInfo, Field, x, y + 1);
		}
		if (y + 1 < fieldSize && x + 1 < fieldSize) {
			playerMove(FieldInfo, Field, x + 1, y + 1);
		}
	}
	return false;
}
void endGame(short int** FieldInfo, short int** Field) {
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	for(int i = 0; i < fieldSize; i++)//Вскрытие всех бомб
		for (int j = 0; j < fieldSize; j++) {
			if (FieldInfo[i][j] == 9) Field[i][j] = 9;
		}
	printField(Field);
}