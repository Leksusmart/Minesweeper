#pragma once
#include <Windows.h>
#include <stdlib.h>
#include <time.h>
namespace Сапёр2 {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	short int fieldSize;//Размер поля
	short int bombs;//Количество бомб
	short int difficult = 2;
	bool once = true;
	short int** FieldInfo;
	const short int maxfieldSize = 10;
	/// <summary>
	/// Сводка для GameWindow
	/// </summary>
	public ref class GameWindow : public System::Windows::Forms::Form
	{
	public:
		GameWindow(void)
		{
			InitializeComponent();
		}
	public:
		short int marked = 0;//Помечено
	protected:
		/// <summary>
		/// Освободить все используемые ресурсы.
		/// </summary>
		~GameWindow()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::ComponentModel::IContainer^ components;
	private: int openFieldCounter = 0;
		   System::Windows::Forms::ImageList^ button_imageList16;
		   System::Windows::Forms::ImageList^ button_imageList25;
	private: System::Windows::Forms::Button^ x0y0; System::Windows::Forms::Button^ x2y0; System::Windows::Forms::Button^ x1y0; System::Windows::Forms::Button^ x4y4; System::Windows::Forms::Button^ x3y4; System::Windows::Forms::Button^ x2y4; System::Windows::Forms::Button^ x1y4; System::Windows::Forms::Button^ x0y4; System::Windows::Forms::Button^ x4y3; System::Windows::Forms::Button^ x3y3; System::Windows::Forms::Button^ x2y3; System::Windows::Forms::Button^ x1y3; System::Windows::Forms::Button^ x0y3; System::Windows::Forms::Button^ x4y2; System::Windows::Forms::Button^ x3y2; System::Windows::Forms::Button^ x2y2; System::Windows::Forms::Button^ x1y2; System::Windows::Forms::Button^ x0y2; System::Windows::Forms::Button^ x4y1; System::Windows::Forms::Button^ x3y1; System::Windows::Forms::Button^ x2y1; System::Windows::Forms::Button^ x1y1; System::Windows::Forms::Button^ x0y1; System::Windows::Forms::Button^ x4y0; System::Windows::Forms::Button^ x3y0; System::Windows::Forms::Button^ x9y9; System::Windows::Forms::Button^ x5y5; System::Windows::Forms::Button^ x7y6; System::Windows::Forms::Button^ x8y9; System::Windows::Forms::Button^ x6y6; System::Windows::Forms::Button^ x8y6; System::Windows::Forms::Button^ x7y9; System::Windows::Forms::Button^ x5y6; System::Windows::Forms::Button^ x9y6; System::Windows::Forms::Button^ x6y9; System::Windows::Forms::Button^ x9y5; System::Windows::Forms::Button^ x5y7; System::Windows::Forms::Button^ x5y9; System::Windows::Forms::Button^ x8y5; System::Windows::Forms::Button^ x6y7; System::Windows::Forms::Button^ x9y8; System::Windows::Forms::Button^ x7y5; System::Windows::Forms::Button^ x7y7; System::Windows::Forms::Button^ x8y8; System::Windows::Forms::Button^ x6y5; System::Windows::Forms::Button^ x8y7; System::Windows::Forms::Button^ x7y8; System::Windows::Forms::Button^ x9y7; System::Windows::Forms::Button^ x5y8; System::Windows::Forms::Button^ x6y8; System::Windows::Forms::Button^ x9y4; System::Windows::Forms::Button^ x5y0; System::Windows::Forms::Button^ x7y1; System::Windows::Forms::Button^ x8y4; System::Windows::Forms::Button^ x6y1; System::Windows::Forms::Button^ x8y1; System::Windows::Forms::Button^ x7y4; System::Windows::Forms::Button^ x5y1; System::Windows::Forms::Button^ x9y1; System::Windows::Forms::Button^ x6y4; System::Windows::Forms::Button^ x9y0; System::Windows::Forms::Button^ x5y2; System::Windows::Forms::Button^ x5y4; System::Windows::Forms::Button^ x8y0; System::Windows::Forms::Button^ x6y2; System::Windows::Forms::Button^ x9y3; System::Windows::Forms::Button^ x7y0; System::Windows::Forms::Button^ x7y2; System::Windows::Forms::Button^ x8y3; System::Windows::Forms::Button^ x6y0; System::Windows::Forms::Button^ x8y2; System::Windows::Forms::Button^ x7y3; System::Windows::Forms::Button^ x9y2; System::Windows::Forms::Button^ x5y3; System::Windows::Forms::Button^ x6y3; System::Windows::Forms::Button^ x4y9; System::Windows::Forms::Button^ x0y5; System::Windows::Forms::Button^ x2y6; System::Windows::Forms::Button^ x3y9; System::Windows::Forms::Button^ x1y6; System::Windows::Forms::Button^ x3y6; System::Windows::Forms::Button^ x2y9; System::Windows::Forms::Button^ x0y6; System::Windows::Forms::Button^ x4y6; System::Windows::Forms::Button^ x1y9; System::Windows::Forms::Button^ x4y5; System::Windows::Forms::Button^ x0y7; System::Windows::Forms::Button^ x0y9; System::Windows::Forms::Button^ x3y5; System::Windows::Forms::Button^ x1y7; System::Windows::Forms::Button^ x4y8; System::Windows::Forms::Button^ x2y5; System::Windows::Forms::Button^ x2y7; System::Windows::Forms::Button^ x3y8; System::Windows::Forms::Button^ x1y5; System::Windows::Forms::Button^ x3y7; System::Windows::Forms::Button^ x2y8; System::Windows::Forms::Button^ x4y7; System::Windows::Forms::Button^ x0y8; System::Windows::Forms::Button^ x1y8;


	public:
		System::Windows::Forms::Label^ label_marked;
		System::Windows::Forms::Label^ label_markedCounter;
		System::Windows::Forms::Label^ label_bombs;
		System::Windows::Forms::Label^ label_bombCounter;
		System::Windows::Forms::Button^ btn_close;
		System::Windows::Forms::GroupBox^ fieldBox;
		System::Windows::Forms::Button^ find(String^ name) {
			if (x0y0->Name == name)return x0y0;
			if (x0y1->Name == name)return x0y1;
			if (x0y2->Name == name)return x0y2;
			if (x0y3->Name == name)return x0y3;
			if (x0y4->Name == name)return x0y4;
			if (x0y5->Name == name)return x0y5;
			if (x0y6->Name == name)return x0y6;
			if (x0y7->Name == name)return x0y7;
			if (x0y8->Name == name)return x0y8;
			if (x0y9->Name == name)return x0y9;

			if (x1y0->Name == name)return x1y0;
			if (x1y1->Name == name)return x1y1;
			if (x1y2->Name == name)return x1y2;
			if (x1y3->Name == name)return x1y3;
			if (x1y4->Name == name)return x1y4;
			if (x1y5->Name == name)return x1y5;
			if (x1y6->Name == name)return x1y6;
			if (x1y7->Name == name)return x1y7;
			if (x1y8->Name == name)return x1y8;
			if (x1y9->Name == name)return x1y9;

			if (x2y0->Name == name)return x2y0;
			if (x2y1->Name == name)return x2y1;
			if (x2y2->Name == name)return x2y2;
			if (x2y3->Name == name)return x2y3;
			if (x2y4->Name == name)return x2y4;
			if (x2y5->Name == name)return x2y5;
			if (x2y6->Name == name)return x2y6;
			if (x2y7->Name == name)return x2y7;
			if (x2y8->Name == name)return x2y8;
			if (x2y9->Name == name)return x2y9;

			if (x3y0->Name == name)return x3y0;
			if (x3y1->Name == name)return x3y1;
			if (x3y2->Name == name)return x3y2;
			if (x3y3->Name == name)return x3y3;
			if (x3y4->Name == name)return x3y4;
			if (x3y5->Name == name)return x3y5;
			if (x3y6->Name == name)return x3y6;
			if (x3y7->Name == name)return x3y7;
			if (x3y8->Name == name)return x3y8;
			if (x3y9->Name == name)return x3y9;

			if (x4y0->Name == name)return x4y0;
			if (x4y1->Name == name)return x4y1;
			if (x4y2->Name == name)return x4y2;
			if (x4y3->Name == name)return x4y3;
			if (x4y4->Name == name)return x4y4;
			if (x4y5->Name == name)return x4y5;
			if (x4y6->Name == name)return x4y6;
			if (x4y7->Name == name)return x4y7;
			if (x4y8->Name == name)return x4y8;
			if (x4y9->Name == name)return x4y9;

			if (x5y0->Name == name)return x5y0;
			if (x5y1->Name == name)return x5y1;
			if (x5y2->Name == name)return x5y2;
			if (x5y3->Name == name)return x5y3;
			if (x5y4->Name == name)return x5y4;
			if (x5y5->Name == name)return x5y5;
			if (x5y6->Name == name)return x5y6;
			if (x5y7->Name == name)return x5y7;
			if (x5y8->Name == name)return x5y8;
			if (x5y9->Name == name)return x5y9;

			if (x6y0->Name == name)return x6y0;
			if (x6y1->Name == name)return x6y1;
			if (x6y2->Name == name)return x6y2;
			if (x6y3->Name == name)return x6y3;
			if (x6y4->Name == name)return x6y4;
			if (x6y5->Name == name)return x6y5;
			if (x6y6->Name == name)return x6y6;
			if (x6y7->Name == name)return x6y7;
			if (x6y8->Name == name)return x6y8;
			if (x6y9->Name == name)return x6y9;

			if (x7y0->Name == name)return x7y0;
			if (x7y1->Name == name)return x7y1;
			if (x7y2->Name == name)return x7y2;
			if (x7y3->Name == name)return x7y3;
			if (x7y4->Name == name)return x7y4;
			if (x7y5->Name == name)return x7y5;
			if (x7y6->Name == name)return x7y6;
			if (x7y7->Name == name)return x7y7;
			if (x7y8->Name == name)return x7y8;
			if (x7y9->Name == name)return x7y9;


			if (x8y0->Name == name)return x8y0;
			if (x8y1->Name == name)return x8y1;
			if (x8y2->Name == name)return x8y2;
			if (x8y3->Name == name)return x8y3;
			if (x8y4->Name == name)return x8y4;
			if (x8y5->Name == name)return x8y5;
			if (x8y6->Name == name)return x8y6;
			if (x8y7->Name == name)return x8y7;
			if (x8y8->Name == name)return x8y8;
			if (x8y9->Name == name)return x8y9;


			if (x9y0->Name == name)return x9y0;
			if (x9y1->Name == name)return x9y1;
			if (x9y2->Name == name)return x9y2;
			if (x9y3->Name == name)return x9y3;
			if (x9y4->Name == name)return x9y4;
			if (x9y5->Name == name)return x9y5;
			if (x9y6->Name == name)return x9y6;
			if (x9y7->Name == name)return x9y7;
			if (x9y8->Name == name)return x9y8;
			if (x9y9->Name == name)return x9y9;

			return nullptr;
		}
		void createFieldInfo(short int**& Field, int startx, int starty) {
			short int counter = 0;
			while (counter < bombs) {
				short int x, y;
				x = rand() % fieldSize;
				y = rand() % fieldSize;
				if (Field[y][x] != 9 &&
					startx != x &&
					starty != y) {
					Field[y][x] = 9;
					counter++;
				}
			}

			//Дальше генерим цифры
			for (int i = 0; i < fieldSize; i++)
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
		void endGame(short int** FieldInfo, bool win) {
			for (int i = 0; i < fieldSize; i++)//Вскрытие всех бомб
				for (int j = 0; j < fieldSize; j++) {
					String^ name = Convert::ToChar('x') + Convert::ToString(j) + Convert::ToChar('y') + Convert::ToString(i);
					System::Windows::Forms::Button^ button;
					button = find(name);
					button->MouseDown -= gcnew System::Windows::Forms::MouseEventHandler(this, &GameWindow::MouseDown);
					if (FieldInfo[i][j] == 9) {
						if (win) button->ImageIndex = 12;
						else button->ImageIndex = 9;
					}
				}
			btn_close->Text = "Закрыть";
			if (win)btn_close->BackColor = Color::Green;
		}
		bool isDigit(char G) {
			if (G >= '0' && G <= '9') {
				return true;
			}
			return false;
		}
#pragma region Windows Form Designer generated code
		/// <summary>
		/// Требуемый метод для поддержки конструктора — не изменяйте 
		/// содержимое этого метода с помощью редактора кода.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(GameWindow::typeid));
			this->btn_close = (gcnew System::Windows::Forms::Button());
			this->x0y0 = (gcnew System::Windows::Forms::Button());
			this->button_imageList25 = (gcnew System::Windows::Forms::ImageList(this->components));
			this->button_imageList16 = (gcnew System::Windows::Forms::ImageList(this->components));
			this->label_bombs = (gcnew System::Windows::Forms::Label());
			this->label_marked = (gcnew System::Windows::Forms::Label());
			this->label_bombCounter = (gcnew System::Windows::Forms::Label());
			this->label_markedCounter = (gcnew System::Windows::Forms::Label());
			this->fieldBox = (gcnew System::Windows::Forms::GroupBox());
			this->x9y9 = (gcnew System::Windows::Forms::Button());
			this->x5y5 = (gcnew System::Windows::Forms::Button());
			this->x7y6 = (gcnew System::Windows::Forms::Button());
			this->x8y9 = (gcnew System::Windows::Forms::Button());
			this->x6y6 = (gcnew System::Windows::Forms::Button());
			this->x8y6 = (gcnew System::Windows::Forms::Button());
			this->x7y9 = (gcnew System::Windows::Forms::Button());
			this->x5y6 = (gcnew System::Windows::Forms::Button());
			this->x9y6 = (gcnew System::Windows::Forms::Button());
			this->x6y9 = (gcnew System::Windows::Forms::Button());
			this->x9y5 = (gcnew System::Windows::Forms::Button());
			this->x5y7 = (gcnew System::Windows::Forms::Button());
			this->x5y9 = (gcnew System::Windows::Forms::Button());
			this->x8y5 = (gcnew System::Windows::Forms::Button());
			this->x6y7 = (gcnew System::Windows::Forms::Button());
			this->x9y8 = (gcnew System::Windows::Forms::Button());
			this->x7y5 = (gcnew System::Windows::Forms::Button());
			this->x7y7 = (gcnew System::Windows::Forms::Button());
			this->x8y8 = (gcnew System::Windows::Forms::Button());
			this->x6y5 = (gcnew System::Windows::Forms::Button());
			this->x8y7 = (gcnew System::Windows::Forms::Button());
			this->x7y8 = (gcnew System::Windows::Forms::Button());
			this->x9y7 = (gcnew System::Windows::Forms::Button());
			this->x5y8 = (gcnew System::Windows::Forms::Button());
			this->x6y8 = (gcnew System::Windows::Forms::Button());
			this->x9y4 = (gcnew System::Windows::Forms::Button());
			this->x5y0 = (gcnew System::Windows::Forms::Button());
			this->x7y1 = (gcnew System::Windows::Forms::Button());
			this->x8y4 = (gcnew System::Windows::Forms::Button());
			this->x6y1 = (gcnew System::Windows::Forms::Button());
			this->x8y1 = (gcnew System::Windows::Forms::Button());
			this->x7y4 = (gcnew System::Windows::Forms::Button());
			this->x5y1 = (gcnew System::Windows::Forms::Button());
			this->x9y1 = (gcnew System::Windows::Forms::Button());
			this->x6y4 = (gcnew System::Windows::Forms::Button());
			this->x9y0 = (gcnew System::Windows::Forms::Button());
			this->x5y2 = (gcnew System::Windows::Forms::Button());
			this->x5y4 = (gcnew System::Windows::Forms::Button());
			this->x8y0 = (gcnew System::Windows::Forms::Button());
			this->x6y2 = (gcnew System::Windows::Forms::Button());
			this->x9y3 = (gcnew System::Windows::Forms::Button());
			this->x7y0 = (gcnew System::Windows::Forms::Button());
			this->x7y2 = (gcnew System::Windows::Forms::Button());
			this->x8y3 = (gcnew System::Windows::Forms::Button());
			this->x6y0 = (gcnew System::Windows::Forms::Button());
			this->x8y2 = (gcnew System::Windows::Forms::Button());
			this->x7y3 = (gcnew System::Windows::Forms::Button());
			this->x9y2 = (gcnew System::Windows::Forms::Button());
			this->x5y3 = (gcnew System::Windows::Forms::Button());
			this->x6y3 = (gcnew System::Windows::Forms::Button());
			this->x4y9 = (gcnew System::Windows::Forms::Button());
			this->x0y5 = (gcnew System::Windows::Forms::Button());
			this->x2y6 = (gcnew System::Windows::Forms::Button());
			this->x3y9 = (gcnew System::Windows::Forms::Button());
			this->x1y6 = (gcnew System::Windows::Forms::Button());
			this->x3y6 = (gcnew System::Windows::Forms::Button());
			this->x2y9 = (gcnew System::Windows::Forms::Button());
			this->x0y6 = (gcnew System::Windows::Forms::Button());
			this->x4y6 = (gcnew System::Windows::Forms::Button());
			this->x1y9 = (gcnew System::Windows::Forms::Button());
			this->x4y5 = (gcnew System::Windows::Forms::Button());
			this->x0y7 = (gcnew System::Windows::Forms::Button());
			this->x0y9 = (gcnew System::Windows::Forms::Button());
			this->x3y5 = (gcnew System::Windows::Forms::Button());
			this->x1y7 = (gcnew System::Windows::Forms::Button());
			this->x4y8 = (gcnew System::Windows::Forms::Button());
			this->x2y5 = (gcnew System::Windows::Forms::Button());
			this->x2y7 = (gcnew System::Windows::Forms::Button());
			this->x3y8 = (gcnew System::Windows::Forms::Button());
			this->x1y5 = (gcnew System::Windows::Forms::Button());
			this->x3y7 = (gcnew System::Windows::Forms::Button());
			this->x2y8 = (gcnew System::Windows::Forms::Button());
			this->x4y7 = (gcnew System::Windows::Forms::Button());
			this->x0y8 = (gcnew System::Windows::Forms::Button());
			this->x1y8 = (gcnew System::Windows::Forms::Button());
			this->x4y4 = (gcnew System::Windows::Forms::Button());
			this->x2y1 = (gcnew System::Windows::Forms::Button());
			this->x3y4 = (gcnew System::Windows::Forms::Button());
			this->x1y1 = (gcnew System::Windows::Forms::Button());
			this->x3y1 = (gcnew System::Windows::Forms::Button());
			this->x2y4 = (gcnew System::Windows::Forms::Button());
			this->x0y1 = (gcnew System::Windows::Forms::Button());
			this->x4y1 = (gcnew System::Windows::Forms::Button());
			this->x1y4 = (gcnew System::Windows::Forms::Button());
			this->x4y0 = (gcnew System::Windows::Forms::Button());
			this->x0y2 = (gcnew System::Windows::Forms::Button());
			this->x0y4 = (gcnew System::Windows::Forms::Button());
			this->x3y0 = (gcnew System::Windows::Forms::Button());
			this->x1y2 = (gcnew System::Windows::Forms::Button());
			this->x4y3 = (gcnew System::Windows::Forms::Button());
			this->x2y0 = (gcnew System::Windows::Forms::Button());
			this->x2y2 = (gcnew System::Windows::Forms::Button());
			this->x3y3 = (gcnew System::Windows::Forms::Button());
			this->x1y0 = (gcnew System::Windows::Forms::Button());
			this->x3y2 = (gcnew System::Windows::Forms::Button());
			this->x2y3 = (gcnew System::Windows::Forms::Button());
			this->x4y2 = (gcnew System::Windows::Forms::Button());
			this->x0y3 = (gcnew System::Windows::Forms::Button());
			this->x1y3 = (gcnew System::Windows::Forms::Button());

			this->fieldBox->SuspendLayout();
			this->SuspendLayout();
			// 
			// btn_close
			// 
			this->btn_close->BackColor = System::Drawing::Color::Red;
			this->btn_close->FlatStyle = System::Windows::Forms::FlatStyle::Popup;
			this->btn_close->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 20.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->btn_close->ForeColor = System::Drawing::SystemColors::Control;
			this->btn_close->Location = System::Drawing::Point(225, 10);
			this->btn_close->Name = L"btn_close";
			this->btn_close->Size = System::Drawing::Size(150, 60);
			this->btn_close->TabIndex = 0;
			this->btn_close->Text = L"Сдаться";
			this->btn_close->UseVisualStyleBackColor = false;
			this->btn_close->Click += gcnew System::EventHandler(this, &GameWindow::btn_close_Click);
			// 
			// x0y0
			// 
			this->x0y0->BackColor = System::Drawing::Color::Transparent;
			this->x0y0->Cursor = System::Windows::Forms::Cursors::Hand;
			this->x0y0->FlatAppearance->BorderSize = 0;
			this->x0y0->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->x0y0->ImageIndex = 11;
			this->x0y0->ImageList = this->button_imageList25;
			this->x0y0->Location = System::Drawing::Point(0, 0);
			this->x0y0->Margin = System::Windows::Forms::Padding(0);
			this->x0y0->Name = L"x0y0";
			this->x0y0->Size = System::Drawing::Size(25, 25);
			this->x0y0->TabIndex = 1;
			this->x0y0->TabStop = false;
			this->x0y0->UseVisualStyleBackColor = false;
			this->x0y0->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &GameWindow::MouseDown);
			// 
			// button_imageList25
			// 
			this->button_imageList25->ImageStream = (cli::safe_cast<System::Windows::Forms::ImageListStreamer^>(resources->GetObject(L"button_imageList25.ImageStream")));
			this->button_imageList25->TransparentColor = System::Drawing::Color::Transparent;
			this->button_imageList25->Images->SetKeyName(0, L"button_pressed.bmp");
			this->button_imageList25->Images->SetKeyName(1, L"button1.bmp");
			this->button_imageList25->Images->SetKeyName(2, L"button2.bmp");
			this->button_imageList25->Images->SetKeyName(3, L"button3.bmp");
			this->button_imageList25->Images->SetKeyName(4, L"button4.bmp");
			this->button_imageList25->Images->SetKeyName(5, L"button5.bmp");
			this->button_imageList25->Images->SetKeyName(6, L"button6.bmp");
			this->button_imageList25->Images->SetKeyName(7, L"button7.bmp");
			this->button_imageList25->Images->SetKeyName(8, L"button8.bmp");
			this->button_imageList25->Images->SetKeyName(9, L"button_bomb.bmp");
			this->button_imageList25->Images->SetKeyName(10, L"button_flag.bmp");
			this->button_imageList25->Images->SetKeyName(11, L"button.bmp");
			this->button_imageList25->Images->SetKeyName(12, L"button_bombcheked.bmp");
			// 
			// button_imageList16
			// 
			this->button_imageList16->ImageStream = (cli::safe_cast<System::Windows::Forms::ImageListStreamer^>(resources->GetObject(L"button_imageList16.ImageStream")));
			this->button_imageList16->TransparentColor = System::Drawing::Color::Transparent;
			this->button_imageList16->Images->SetKeyName(0, L"button_pressed.bmp");
			this->button_imageList16->Images->SetKeyName(1, L"x0y0.bmp");
			this->button_imageList16->Images->SetKeyName(2, L"button2.bmp");
			this->button_imageList16->Images->SetKeyName(3, L"button3.bmp");
			this->button_imageList16->Images->SetKeyName(4, L"button4.bmp");
			this->button_imageList16->Images->SetKeyName(5, L"button5.bmp");
			this->button_imageList16->Images->SetKeyName(6, L"button6.bmp");
			this->button_imageList16->Images->SetKeyName(7, L"button7.bmp");
			this->button_imageList16->Images->SetKeyName(8, L"button8.bmp");
			this->button_imageList16->Images->SetKeyName(9, L"button_bomb.bmp");
			this->button_imageList16->Images->SetKeyName(10, L"button_flag.bmp");
			this->button_imageList16->Images->SetKeyName(11, L"button.bmp");
			this->button_imageList16->Images->SetKeyName(12, L"button_bombcheked.bmp");
			// 
			// label_bombs
			// 
			this->label_bombs->AutoSize = true;
			this->label_bombs->BackColor = System::Drawing::Color::Transparent;
			this->label_bombs->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 16.125F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label_bombs->ForeColor = System::Drawing::Color::Firebrick;
			this->label_bombs->Location = System::Drawing::Point(7, 10);
			this->label_bombs->Name = L"label_bombs";
			this->label_bombs->Size = System::Drawing::Size(140, 26);
			this->label_bombs->TabIndex = 2;
			this->label_bombs->Text = L"Всего бомб";
			// 
			// label_marked
			// 
			this->label_marked->AutoSize = true;
			this->label_marked->BackColor = System::Drawing::Color::Transparent;
			this->label_marked->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 16.125F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label_marked->ForeColor = System::Drawing::Color::Firebrick;
			this->label_marked->Location = System::Drawing::Point(452, 10);
			this->label_marked->Name = L"label_marked";
			this->label_marked->Size = System::Drawing::Size(124, 26);
			this->label_marked->TabIndex = 2;
			this->label_marked->Text = L"Помечено";
			// 
			// label_bombCounter
			// 
			this->label_bombCounter->BackColor = System::Drawing::Color::Black;
			this->label_bombCounter->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->label_bombCounter->Font = (gcnew System::Drawing::Font(L"MOSCOW2024", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label_bombCounter->ForeColor = System::Drawing::Color::Firebrick;
			this->label_bombCounter->Location = System::Drawing::Point(51, 36);
			this->label_bombCounter->Name = L"label_bombCounter";
			this->label_bombCounter->Size = System::Drawing::Size(50, 27);
			this->label_bombCounter->TabIndex = 3;
			this->label_bombCounter->Text = L"\?";
			this->label_bombCounter->TextAlign = System::Drawing::ContentAlignment::MiddleRight;
			// 
			// label_markedCounter
			// 
			this->label_markedCounter->BackColor = System::Drawing::Color::Black;
			this->label_markedCounter->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->label_markedCounter->Font = (gcnew System::Drawing::Font(L"MOSCOW2024", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label_markedCounter->ForeColor = System::Drawing::Color::Firebrick;
			this->label_markedCounter->Location = System::Drawing::Point(489, 36);
			this->label_markedCounter->Name = L"label_markedCounter";
			this->label_markedCounter->Size = System::Drawing::Size(50, 27);
			this->label_markedCounter->TabIndex = 3;
			this->label_markedCounter->Text = L"0";
			this->label_markedCounter->TextAlign = System::Drawing::ContentAlignment::MiddleRight;
			// 
			// fieldBox
			// 
			this->fieldBox->BackColor = System::Drawing::Color::LightGray;
			this->fieldBox->Controls->Add(this->x0y0);
			this->fieldBox->Controls->Add(this->x0y1);
			this->fieldBox->Controls->Add(this->x0y2);
			this->fieldBox->Controls->Add(this->x0y3);
			this->fieldBox->Controls->Add(this->x0y4);
			this->fieldBox->Controls->Add(this->x0y5);
			this->fieldBox->Controls->Add(this->x0y6);
			this->fieldBox->Controls->Add(this->x0y7);
			this->fieldBox->Controls->Add(this->x0y8);
			this->fieldBox->Controls->Add(this->x0y9);
			this->fieldBox->Controls->Add(this->x1y0);
			this->fieldBox->Controls->Add(this->x1y1);
			this->fieldBox->Controls->Add(this->x1y2);
			this->fieldBox->Controls->Add(this->x1y3);
			this->fieldBox->Controls->Add(this->x1y4);
			this->fieldBox->Controls->Add(this->x1y5);
			this->fieldBox->Controls->Add(this->x1y6);
			this->fieldBox->Controls->Add(this->x1y7);
			this->fieldBox->Controls->Add(this->x1y8);
			this->fieldBox->Controls->Add(this->x1y9);
			this->fieldBox->Controls->Add(this->x2y0);
			this->fieldBox->Controls->Add(this->x2y1);
			this->fieldBox->Controls->Add(this->x2y2);
			this->fieldBox->Controls->Add(this->x2y3);
			this->fieldBox->Controls->Add(this->x2y4);
			this->fieldBox->Controls->Add(this->x2y5);
			this->fieldBox->Controls->Add(this->x2y6);
			this->fieldBox->Controls->Add(this->x2y7);
			this->fieldBox->Controls->Add(this->x2y8);
			this->fieldBox->Controls->Add(this->x2y9);
			this->fieldBox->Controls->Add(this->x3y0);
			this->fieldBox->Controls->Add(this->x3y1);
			this->fieldBox->Controls->Add(this->x3y2);
			this->fieldBox->Controls->Add(this->x3y3);
			this->fieldBox->Controls->Add(this->x3y4);
			this->fieldBox->Controls->Add(this->x3y5);
			this->fieldBox->Controls->Add(this->x3y6);
			this->fieldBox->Controls->Add(this->x3y7);
			this->fieldBox->Controls->Add(this->x3y8);
			this->fieldBox->Controls->Add(this->x3y9);
			this->fieldBox->Controls->Add(this->x4y0);
			this->fieldBox->Controls->Add(this->x4y1);
			this->fieldBox->Controls->Add(this->x4y2);
			this->fieldBox->Controls->Add(this->x4y3);
			this->fieldBox->Controls->Add(this->x4y4);
			this->fieldBox->Controls->Add(this->x4y5);
			this->fieldBox->Controls->Add(this->x4y6);
			this->fieldBox->Controls->Add(this->x4y7);
			this->fieldBox->Controls->Add(this->x4y8);
			this->fieldBox->Controls->Add(this->x4y9);
			this->fieldBox->Controls->Add(this->x5y0);
			this->fieldBox->Controls->Add(this->x5y1);
			this->fieldBox->Controls->Add(this->x5y2);
			this->fieldBox->Controls->Add(this->x5y3);
			this->fieldBox->Controls->Add(this->x5y4);
			this->fieldBox->Controls->Add(this->x5y5);
			this->fieldBox->Controls->Add(this->x5y6);
			this->fieldBox->Controls->Add(this->x5y7);
			this->fieldBox->Controls->Add(this->x5y8);
			this->fieldBox->Controls->Add(this->x5y9);
			this->fieldBox->Controls->Add(this->x6y0);
			this->fieldBox->Controls->Add(this->x6y1);
			this->fieldBox->Controls->Add(this->x6y2);
			this->fieldBox->Controls->Add(this->x6y3);
			this->fieldBox->Controls->Add(this->x6y4);
			this->fieldBox->Controls->Add(this->x6y5);
			this->fieldBox->Controls->Add(this->x6y6);
			this->fieldBox->Controls->Add(this->x6y7);
			this->fieldBox->Controls->Add(this->x6y8);
			this->fieldBox->Controls->Add(this->x6y9);
			this->fieldBox->Controls->Add(this->x7y0);
			this->fieldBox->Controls->Add(this->x7y1);
			this->fieldBox->Controls->Add(this->x7y2);
			this->fieldBox->Controls->Add(this->x7y3);
			this->fieldBox->Controls->Add(this->x7y4);
			this->fieldBox->Controls->Add(this->x7y5);
			this->fieldBox->Controls->Add(this->x7y6);
			this->fieldBox->Controls->Add(this->x7y7);
			this->fieldBox->Controls->Add(this->x7y8);
			this->fieldBox->Controls->Add(this->x7y9);
			this->fieldBox->Controls->Add(this->x8y0);
			this->fieldBox->Controls->Add(this->x8y1);
			this->fieldBox->Controls->Add(this->x8y2);
			this->fieldBox->Controls->Add(this->x8y3);
			this->fieldBox->Controls->Add(this->x8y4);
			this->fieldBox->Controls->Add(this->x8y5);
			this->fieldBox->Controls->Add(this->x8y6);
			this->fieldBox->Controls->Add(this->x8y7);
			this->fieldBox->Controls->Add(this->x8y8);
			this->fieldBox->Controls->Add(this->x8y9);
			this->fieldBox->Controls->Add(this->x9y0);
			this->fieldBox->Controls->Add(this->x9y1);
			this->fieldBox->Controls->Add(this->x9y2);
			this->fieldBox->Controls->Add(this->x9y3);
			this->fieldBox->Controls->Add(this->x9y4);
			this->fieldBox->Controls->Add(this->x9y5);
			this->fieldBox->Controls->Add(this->x9y6);
			this->fieldBox->Controls->Add(this->x9y7);
			this->fieldBox->Controls->Add(this->x9y8);
			this->fieldBox->Controls->Add(this->x9y9);
			this->fieldBox->Location = System::Drawing::Point(175, 150);
			this->fieldBox->Name = L"fieldBox";
			this->fieldBox->Size = System::Drawing::Size(251, 251);
			this->fieldBox->TabIndex = 4;
			this->fieldBox->TabStop = false;
			// 
			// x9y9
			// 
			this->x9y9->BackColor = System::Drawing::Color::Transparent;
			this->x9y9->Cursor = System::Windows::Forms::Cursors::Hand;
			this->x9y9->FlatAppearance->BorderSize = 0;
			this->x9y9->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->x9y9->ImageIndex = 11;
			this->x9y9->ImageList = this->button_imageList25;
			this->x9y9->Location = System::Drawing::Point(225, 225);
			this->x9y9->Margin = System::Windows::Forms::Padding(0);
			this->x9y9->Name = L"x9y9";
			this->x9y9->Size = System::Drawing::Size(25, 25);
			this->x9y9->TabIndex = 100;
			this->x9y9->TabStop = false;
			this->x9y9->UseVisualStyleBackColor = false;
			this->x9y9->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &GameWindow::MouseDown);
			// 
			// x5y5
			// 
			this->x5y5->BackColor = System::Drawing::Color::Transparent;
			this->x5y5->Cursor = System::Windows::Forms::Cursors::Hand;
			this->x5y5->FlatAppearance->BorderSize = 0;
			this->x5y5->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->x5y5->ImageIndex = 11;
			this->x5y5->ImageList = this->button_imageList25;
			this->x5y5->Location = System::Drawing::Point(125, 125);
			this->x5y5->Margin = System::Windows::Forms::Padding(0);
			this->x5y5->Name = L"x5y5";
			this->x5y5->Size = System::Drawing::Size(25, 25);
			this->x5y5->TabIndex = 76;
			this->x5y5->TabStop = false;
			this->x5y5->UseVisualStyleBackColor = false;
			this->x5y5->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &GameWindow::MouseDown);
			// 
			// x7y6
			// 
			this->x7y6->BackColor = System::Drawing::Color::Transparent;
			this->x7y6->Cursor = System::Windows::Forms::Cursors::Hand;
			this->x7y6->FlatAppearance->BorderSize = 0;
			this->x7y6->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->x7y6->ImageIndex = 11;
			this->x7y6->ImageList = this->button_imageList25;
			this->x7y6->Location = System::Drawing::Point(175, 150);
			this->x7y6->Margin = System::Windows::Forms::Padding(0);
			this->x7y6->Name = L"x7y6";
			this->x7y6->Size = System::Drawing::Size(25, 25);
			this->x7y6->TabIndex = 83;
			this->x7y6->TabStop = false;
			this->x7y6->UseVisualStyleBackColor = false;
			this->x7y6->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &GameWindow::MouseDown);
			// 
			// x8y9
			// 
			this->x8y9->BackColor = System::Drawing::Color::Transparent;
			this->x8y9->Cursor = System::Windows::Forms::Cursors::Hand;
			this->x8y9->FlatAppearance->BorderSize = 0;
			this->x8y9->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->x8y9->ImageIndex = 11;
			this->x8y9->ImageList = this->button_imageList25;
			this->x8y9->Location = System::Drawing::Point(200, 225);
			this->x8y9->Margin = System::Windows::Forms::Padding(0);
			this->x8y9->Name = L"x8y9";
			this->x8y9->Size = System::Drawing::Size(25, 25);
			this->x8y9->TabIndex = 99;
			this->x8y9->TabStop = false;
			this->x8y9->UseVisualStyleBackColor = false;
			this->x8y9->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &GameWindow::MouseDown);
			// 
			// x6y6
			// 
			this->x6y6->BackColor = System::Drawing::Color::Transparent;
			this->x6y6->Cursor = System::Windows::Forms::Cursors::Hand;
			this->x6y6->FlatAppearance->BorderSize = 0;
			this->x6y6->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->x6y6->ImageIndex = 11;
			this->x6y6->ImageList = this->button_imageList25;
			this->x6y6->Location = System::Drawing::Point(150, 150);
			this->x6y6->Margin = System::Windows::Forms::Padding(0);
			this->x6y6->Name = L"x6y6";
			this->x6y6->Size = System::Drawing::Size(25, 25);
			this->x6y6->TabIndex = 82;
			this->x6y6->TabStop = false;
			this->x6y6->UseVisualStyleBackColor = false;
			this->x6y6->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &GameWindow::MouseDown);
			// 
			// x8y6
			// 
			this->x8y6->BackColor = System::Drawing::Color::Transparent;
			this->x8y6->Cursor = System::Windows::Forms::Cursors::Hand;
			this->x8y6->FlatAppearance->BorderSize = 0;
			this->x8y6->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->x8y6->ImageIndex = 11;
			this->x8y6->ImageList = this->button_imageList25;
			this->x8y6->Location = System::Drawing::Point(200, 150);
			this->x8y6->Margin = System::Windows::Forms::Padding(0);
			this->x8y6->Name = L"x8y6";
			this->x8y6->Size = System::Drawing::Size(25, 25);
			this->x8y6->TabIndex = 84;
			this->x8y6->TabStop = false;
			this->x8y6->UseVisualStyleBackColor = false;
			this->x8y6->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &GameWindow::MouseDown);
			// 
			// x7y9
			// 
			this->x7y9->BackColor = System::Drawing::Color::Transparent;
			this->x7y9->Cursor = System::Windows::Forms::Cursors::Hand;
			this->x7y9->FlatAppearance->BorderSize = 0;
			this->x7y9->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->x7y9->ImageIndex = 11;
			this->x7y9->ImageList = this->button_imageList25;
			this->x7y9->Location = System::Drawing::Point(175, 225);
			this->x7y9->Margin = System::Windows::Forms::Padding(0);
			this->x7y9->Name = L"x7y9";
			this->x7y9->Size = System::Drawing::Size(25, 25);
			this->x7y9->TabIndex = 98;
			this->x7y9->TabStop = false;
			this->x7y9->UseVisualStyleBackColor = false;
			this->x7y9->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &GameWindow::MouseDown);
			// 
			// x5y6
			// 
			this->x5y6->BackColor = System::Drawing::Color::Transparent;
			this->x5y6->Cursor = System::Windows::Forms::Cursors::Hand;
			this->x5y6->FlatAppearance->BorderSize = 0;
			this->x5y6->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->x5y6->ImageIndex = 11;
			this->x5y6->ImageList = this->button_imageList25;
			this->x5y6->Location = System::Drawing::Point(125, 150);
			this->x5y6->Margin = System::Windows::Forms::Padding(0);
			this->x5y6->Name = L"x5y6";
			this->x5y6->Size = System::Drawing::Size(25, 25);
			this->x5y6->TabIndex = 81;
			this->x5y6->TabStop = false;
			this->x5y6->UseVisualStyleBackColor = false;
			this->x5y6->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &GameWindow::MouseDown);
			// 
			// x9y6
			// 
			this->x9y6->BackColor = System::Drawing::Color::Transparent;
			this->x9y6->Cursor = System::Windows::Forms::Cursors::Hand;
			this->x9y6->FlatAppearance->BorderSize = 0;
			this->x9y6->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->x9y6->ImageIndex = 11;
			this->x9y6->ImageList = this->button_imageList25;
			this->x9y6->Location = System::Drawing::Point(225, 150);
			this->x9y6->Margin = System::Windows::Forms::Padding(0);
			this->x9y6->Name = L"x9y6";
			this->x9y6->Size = System::Drawing::Size(25, 25);
			this->x9y6->TabIndex = 85;
			this->x9y6->TabStop = false;
			this->x9y6->UseVisualStyleBackColor = false;
			this->x9y6->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &GameWindow::MouseDown);
			// 
			// x6y9
			// 
			this->x6y9->BackColor = System::Drawing::Color::Transparent;
			this->x6y9->Cursor = System::Windows::Forms::Cursors::Hand;
			this->x6y9->FlatAppearance->BorderSize = 0;
			this->x6y9->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->x6y9->ImageIndex = 11;
			this->x6y9->ImageList = this->button_imageList25;
			this->x6y9->Location = System::Drawing::Point(150, 225);
			this->x6y9->Margin = System::Windows::Forms::Padding(0);
			this->x6y9->Name = L"x6y9";
			this->x6y9->Size = System::Drawing::Size(25, 25);
			this->x6y9->TabIndex = 97;
			this->x6y9->TabStop = false;
			this->x6y9->UseVisualStyleBackColor = false;
			this->x6y9->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &GameWindow::MouseDown);
			// 
			// x9y5
			// 
			this->x9y5->BackColor = System::Drawing::Color::Transparent;
			this->x9y5->Cursor = System::Windows::Forms::Cursors::Hand;
			this->x9y5->FlatAppearance->BorderSize = 0;
			this->x9y5->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->x9y5->ImageIndex = 11;
			this->x9y5->ImageList = this->button_imageList25;
			this->x9y5->Location = System::Drawing::Point(225, 125);
			this->x9y5->Margin = System::Windows::Forms::Padding(0);
			this->x9y5->Name = L"x9y5";
			this->x9y5->Size = System::Drawing::Size(25, 25);
			this->x9y5->TabIndex = 80;
			this->x9y5->TabStop = false;
			this->x9y5->UseVisualStyleBackColor = false;
			this->x9y5->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &GameWindow::MouseDown);
			// 
			// x5y7
			// 
			this->x5y7->BackColor = System::Drawing::Color::Transparent;
			this->x5y7->Cursor = System::Windows::Forms::Cursors::Hand;
			this->x5y7->FlatAppearance->BorderSize = 0;
			this->x5y7->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->x5y7->ImageIndex = 11;
			this->x5y7->ImageList = this->button_imageList25;
			this->x5y7->Location = System::Drawing::Point(125, 175);
			this->x5y7->Margin = System::Windows::Forms::Padding(0);
			this->x5y7->Name = L"x5y7";
			this->x5y7->Size = System::Drawing::Size(25, 25);
			this->x5y7->TabIndex = 86;
			this->x5y7->TabStop = false;
			this->x5y7->UseVisualStyleBackColor = false;
			this->x5y7->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &GameWindow::MouseDown);
			// 
			// x5y9
			// 
			this->x5y9->BackColor = System::Drawing::Color::Transparent;
			this->x5y9->Cursor = System::Windows::Forms::Cursors::Hand;
			this->x5y9->FlatAppearance->BorderSize = 0;
			this->x5y9->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->x5y9->ImageIndex = 11;
			this->x5y9->ImageList = this->button_imageList25;
			this->x5y9->Location = System::Drawing::Point(125, 225);
			this->x5y9->Margin = System::Windows::Forms::Padding(0);
			this->x5y9->Name = L"x5y9";
			this->x5y9->Size = System::Drawing::Size(25, 25);
			this->x5y9->TabIndex = 96;
			this->x5y9->TabStop = false;
			this->x5y9->UseVisualStyleBackColor = false;
			this->x5y9->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &GameWindow::MouseDown);
			// 
			// x8y5
			// 
			this->x8y5->BackColor = System::Drawing::Color::Transparent;
			this->x8y5->Cursor = System::Windows::Forms::Cursors::Hand;
			this->x8y5->FlatAppearance->BorderSize = 0;
			this->x8y5->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->x8y5->ImageIndex = 11;
			this->x8y5->ImageList = this->button_imageList25;
			this->x8y5->Location = System::Drawing::Point(200, 125);
			this->x8y5->Margin = System::Windows::Forms::Padding(0);
			this->x8y5->Name = L"x8y5";
			this->x8y5->Size = System::Drawing::Size(25, 25);
			this->x8y5->TabIndex = 79;
			this->x8y5->TabStop = false;
			this->x8y5->UseVisualStyleBackColor = false;
			this->x8y5->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &GameWindow::MouseDown);
			// 
			// x6y7
			// 
			this->x6y7->BackColor = System::Drawing::Color::Transparent;
			this->x6y7->Cursor = System::Windows::Forms::Cursors::Hand;
			this->x6y7->FlatAppearance->BorderSize = 0;
			this->x6y7->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->x6y7->ImageIndex = 11;
			this->x6y7->ImageList = this->button_imageList25;
			this->x6y7->Location = System::Drawing::Point(150, 175);
			this->x6y7->Margin = System::Windows::Forms::Padding(0);
			this->x6y7->Name = L"x6y7";
			this->x6y7->Size = System::Drawing::Size(25, 25);
			this->x6y7->TabIndex = 87;
			this->x6y7->TabStop = false;
			this->x6y7->UseVisualStyleBackColor = false;
			this->x6y7->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &GameWindow::MouseDown);
			// 
			// x9y8
			// 
			this->x9y8->BackColor = System::Drawing::Color::Transparent;
			this->x9y8->Cursor = System::Windows::Forms::Cursors::Hand;
			this->x9y8->FlatAppearance->BorderSize = 0;
			this->x9y8->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->x9y8->ImageIndex = 11;
			this->x9y8->ImageList = this->button_imageList25;
			this->x9y8->Location = System::Drawing::Point(225, 200);
			this->x9y8->Margin = System::Windows::Forms::Padding(0);
			this->x9y8->Name = L"x9y8";
			this->x9y8->Size = System::Drawing::Size(25, 25);
			this->x9y8->TabIndex = 95;
			this->x9y8->TabStop = false;
			this->x9y8->UseVisualStyleBackColor = false;
			this->x9y8->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &GameWindow::MouseDown);
			// 
			// x7y5
			// 
			this->x7y5->BackColor = System::Drawing::Color::Transparent;
			this->x7y5->Cursor = System::Windows::Forms::Cursors::Hand;
			this->x7y5->FlatAppearance->BorderSize = 0;
			this->x7y5->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->x7y5->ImageIndex = 11;
			this->x7y5->ImageList = this->button_imageList25;
			this->x7y5->Location = System::Drawing::Point(175, 125);
			this->x7y5->Margin = System::Windows::Forms::Padding(0);
			this->x7y5->Name = L"x7y5";
			this->x7y5->Size = System::Drawing::Size(25, 25);
			this->x7y5->TabIndex = 78;
			this->x7y5->TabStop = false;
			this->x7y5->UseVisualStyleBackColor = false;
			this->x7y5->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &GameWindow::MouseDown);
			// 
			// x7y7
			// 
			this->x7y7->BackColor = System::Drawing::Color::Transparent;
			this->x7y7->Cursor = System::Windows::Forms::Cursors::Hand;
			this->x7y7->FlatAppearance->BorderSize = 0;
			this->x7y7->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->x7y7->ImageIndex = 11;
			this->x7y7->ImageList = this->button_imageList25;
			this->x7y7->Location = System::Drawing::Point(175, 175);
			this->x7y7->Margin = System::Windows::Forms::Padding(0);
			this->x7y7->Name = L"x7y7";
			this->x7y7->Size = System::Drawing::Size(25, 25);
			this->x7y7->TabIndex = 88;
			this->x7y7->TabStop = false;
			this->x7y7->UseVisualStyleBackColor = false;
			this->x7y7->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &GameWindow::MouseDown);
			// 
			// x8y8
			// 
			this->x8y8->BackColor = System::Drawing::Color::Transparent;
			this->x8y8->Cursor = System::Windows::Forms::Cursors::Hand;
			this->x8y8->FlatAppearance->BorderSize = 0;
			this->x8y8->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->x8y8->ImageIndex = 11;
			this->x8y8->ImageList = this->button_imageList25;
			this->x8y8->Location = System::Drawing::Point(200, 200);
			this->x8y8->Margin = System::Windows::Forms::Padding(0);
			this->x8y8->Name = L"x8y8";
			this->x8y8->Size = System::Drawing::Size(25, 25);
			this->x8y8->TabIndex = 94;
			this->x8y8->TabStop = false;
			this->x8y8->UseVisualStyleBackColor = false;
			this->x8y8->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &GameWindow::MouseDown);
			// 
			// x6y5
			// 
			this->x6y5->BackColor = System::Drawing::Color::Transparent;
			this->x6y5->Cursor = System::Windows::Forms::Cursors::Hand;
			this->x6y5->FlatAppearance->BorderSize = 0;
			this->x6y5->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->x6y5->ImageIndex = 11;
			this->x6y5->ImageList = this->button_imageList25;
			this->x6y5->Location = System::Drawing::Point(150, 125);
			this->x6y5->Margin = System::Windows::Forms::Padding(0);
			this->x6y5->Name = L"x6y5";
			this->x6y5->Size = System::Drawing::Size(25, 25);
			this->x6y5->TabIndex = 77;
			this->x6y5->TabStop = false;
			this->x6y5->UseVisualStyleBackColor = false;
			this->x6y5->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &GameWindow::MouseDown);
			// 
			// x8y7
			// 
			this->x8y7->BackColor = System::Drawing::Color::Transparent;
			this->x8y7->Cursor = System::Windows::Forms::Cursors::Hand;
			this->x8y7->FlatAppearance->BorderSize = 0;
			this->x8y7->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->x8y7->ImageIndex = 11;
			this->x8y7->ImageList = this->button_imageList25;
			this->x8y7->Location = System::Drawing::Point(200, 175);
			this->x8y7->Margin = System::Windows::Forms::Padding(0);
			this->x8y7->Name = L"x8y7";
			this->x8y7->Size = System::Drawing::Size(25, 25);
			this->x8y7->TabIndex = 89;
			this->x8y7->TabStop = false;
			this->x8y7->UseVisualStyleBackColor = false;
			this->x8y7->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &GameWindow::MouseDown);
			// 
			// x7y8
			// 
			this->x7y8->BackColor = System::Drawing::Color::Transparent;
			this->x7y8->Cursor = System::Windows::Forms::Cursors::Hand;
			this->x7y8->FlatAppearance->BorderSize = 0;
			this->x7y8->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->x7y8->ImageIndex = 11;
			this->x7y8->ImageList = this->button_imageList25;
			this->x7y8->Location = System::Drawing::Point(175, 200);
			this->x7y8->Margin = System::Windows::Forms::Padding(0);
			this->x7y8->Name = L"x7y8";
			this->x7y8->Size = System::Drawing::Size(25, 25);
			this->x7y8->TabIndex = 93;
			this->x7y8->TabStop = false;
			this->x7y8->UseVisualStyleBackColor = false;
			this->x7y8->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &GameWindow::MouseDown);
			// 
			// x9y7
			// 
			this->x9y7->BackColor = System::Drawing::Color::Transparent;
			this->x9y7->Cursor = System::Windows::Forms::Cursors::Hand;
			this->x9y7->FlatAppearance->BorderSize = 0;
			this->x9y7->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->x9y7->ImageIndex = 11;
			this->x9y7->ImageList = this->button_imageList25;
			this->x9y7->Location = System::Drawing::Point(225, 175);
			this->x9y7->Margin = System::Windows::Forms::Padding(0);
			this->x9y7->Name = L"x9y7";
			this->x9y7->Size = System::Drawing::Size(25, 25);
			this->x9y7->TabIndex = 90;
			this->x9y7->TabStop = false;
			this->x9y7->UseVisualStyleBackColor = false;
			this->x9y7->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &GameWindow::MouseDown);
			// 
			// x5y8
			// 
			this->x5y8->BackColor = System::Drawing::Color::Transparent;
			this->x5y8->Cursor = System::Windows::Forms::Cursors::Hand;
			this->x5y8->FlatAppearance->BorderSize = 0;
			this->x5y8->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->x5y8->ImageIndex = 11;
			this->x5y8->ImageList = this->button_imageList25;
			this->x5y8->Location = System::Drawing::Point(125, 200);
			this->x5y8->Margin = System::Windows::Forms::Padding(0);
			this->x5y8->Name = L"x5y8";
			this->x5y8->Size = System::Drawing::Size(25, 25);
			this->x5y8->TabIndex = 91;
			this->x5y8->TabStop = false;
			this->x5y8->UseVisualStyleBackColor = false;
			this->x5y8->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &GameWindow::MouseDown);
			// 
			// x6y8
			// 
			this->x6y8->BackColor = System::Drawing::Color::Transparent;
			this->x6y8->Cursor = System::Windows::Forms::Cursors::Hand;
			this->x6y8->FlatAppearance->BorderSize = 0;
			this->x6y8->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->x6y8->ImageIndex = 11;
			this->x6y8->ImageList = this->button_imageList25;
			this->x6y8->Location = System::Drawing::Point(150, 200);
			this->x6y8->Margin = System::Windows::Forms::Padding(0);
			this->x6y8->Name = L"x6y8";
			this->x6y8->Size = System::Drawing::Size(25, 25);
			this->x6y8->TabIndex = 92;
			this->x6y8->TabStop = false;
			this->x6y8->UseVisualStyleBackColor = false;
			this->x6y8->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &GameWindow::MouseDown);
			// 
			// x9y4
			// 
			this->x9y4->BackColor = System::Drawing::Color::Transparent;
			this->x9y4->Cursor = System::Windows::Forms::Cursors::Hand;
			this->x9y4->FlatAppearance->BorderSize = 0;
			this->x9y4->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->x9y4->ImageIndex = 11;
			this->x9y4->ImageList = this->button_imageList25;
			this->x9y4->Location = System::Drawing::Point(225, 100);
			this->x9y4->Margin = System::Windows::Forms::Padding(0);
			this->x9y4->Name = L"x9y4";
			this->x9y4->Size = System::Drawing::Size(25, 25);
			this->x9y4->TabIndex = 75;
			this->x9y4->TabStop = false;
			this->x9y4->UseVisualStyleBackColor = false;
			this->x9y4->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &GameWindow::MouseDown);
			// 
			// x5y0
			// 
			this->x5y0->BackColor = System::Drawing::Color::Transparent;
			this->x5y0->Cursor = System::Windows::Forms::Cursors::Hand;
			this->x5y0->FlatAppearance->BorderSize = 0;
			this->x5y0->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->x5y0->ImageIndex = 11;
			this->x5y0->ImageList = this->button_imageList25;
			this->x5y0->Location = System::Drawing::Point(125, 0);
			this->x5y0->Margin = System::Windows::Forms::Padding(0);
			this->x5y0->Name = L"x5y0";
			this->x5y0->Size = System::Drawing::Size(25, 25);
			this->x5y0->TabIndex = 51;
			this->x5y0->TabStop = false;
			this->x5y0->UseVisualStyleBackColor = false;
			this->x5y0->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &GameWindow::MouseDown);
			// 
			// x7y1
			// 
			this->x7y1->BackColor = System::Drawing::Color::Transparent;
			this->x7y1->Cursor = System::Windows::Forms::Cursors::Hand;
			this->x7y1->FlatAppearance->BorderSize = 0;
			this->x7y1->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->x7y1->ImageIndex = 11;
			this->x7y1->ImageList = this->button_imageList25;
			this->x7y1->Location = System::Drawing::Point(175, 25);
			this->x7y1->Margin = System::Windows::Forms::Padding(0);
			this->x7y1->Name = L"x7y1";
			this->x7y1->Size = System::Drawing::Size(25, 25);
			this->x7y1->TabIndex = 58;
			this->x7y1->TabStop = false;
			this->x7y1->UseVisualStyleBackColor = false;
			this->x7y1->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &GameWindow::MouseDown);
			// 
			// x8y4
			// 
			this->x8y4->BackColor = System::Drawing::Color::Transparent;
			this->x8y4->Cursor = System::Windows::Forms::Cursors::Hand;
			this->x8y4->FlatAppearance->BorderSize = 0;
			this->x8y4->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->x8y4->ImageIndex = 11;
			this->x8y4->ImageList = this->button_imageList25;
			this->x8y4->Location = System::Drawing::Point(200, 100);
			this->x8y4->Margin = System::Windows::Forms::Padding(0);
			this->x8y4->Name = L"x8y4";
			this->x8y4->Size = System::Drawing::Size(25, 25);
			this->x8y4->TabIndex = 74;
			this->x8y4->TabStop = false;
			this->x8y4->UseVisualStyleBackColor = false;
			this->x8y4->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &GameWindow::MouseDown);
			// 
			// x6y1
			// 
			this->x6y1->BackColor = System::Drawing::Color::Transparent;
			this->x6y1->Cursor = System::Windows::Forms::Cursors::Hand;
			this->x6y1->FlatAppearance->BorderSize = 0;
			this->x6y1->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->x6y1->ImageIndex = 11;
			this->x6y1->ImageList = this->button_imageList25;
			this->x6y1->Location = System::Drawing::Point(150, 25);
			this->x6y1->Margin = System::Windows::Forms::Padding(0);
			this->x6y1->Name = L"x6y1";
			this->x6y1->Size = System::Drawing::Size(25, 25);
			this->x6y1->TabIndex = 57;
			this->x6y1->TabStop = false;
			this->x6y1->UseVisualStyleBackColor = false;
			this->x6y1->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &GameWindow::MouseDown);
			// 
			// x8y1
			// 
			this->x8y1->BackColor = System::Drawing::Color::Transparent;
			this->x8y1->Cursor = System::Windows::Forms::Cursors::Hand;
			this->x8y1->FlatAppearance->BorderSize = 0;
			this->x8y1->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->x8y1->ImageIndex = 11;
			this->x8y1->ImageList = this->button_imageList25;
			this->x8y1->Location = System::Drawing::Point(200, 25);
			this->x8y1->Margin = System::Windows::Forms::Padding(0);
			this->x8y1->Name = L"x8y1";
			this->x8y1->Size = System::Drawing::Size(25, 25);
			this->x8y1->TabIndex = 59;
			this->x8y1->TabStop = false;
			this->x8y1->UseVisualStyleBackColor = false;
			this->x8y1->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &GameWindow::MouseDown);
			// 
			// x7y4
			// 
			this->x7y4->BackColor = System::Drawing::Color::Transparent;
			this->x7y4->Cursor = System::Windows::Forms::Cursors::Hand;
			this->x7y4->FlatAppearance->BorderSize = 0;
			this->x7y4->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->x7y4->ImageIndex = 11;
			this->x7y4->ImageList = this->button_imageList25;
			this->x7y4->Location = System::Drawing::Point(175, 100);
			this->x7y4->Margin = System::Windows::Forms::Padding(0);
			this->x7y4->Name = L"x7y4";
			this->x7y4->Size = System::Drawing::Size(25, 25);
			this->x7y4->TabIndex = 73;
			this->x7y4->TabStop = false;
			this->x7y4->UseVisualStyleBackColor = false;
			this->x7y4->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &GameWindow::MouseDown);
			// 
			// x5y1
			// 
			this->x5y1->BackColor = System::Drawing::Color::Transparent;
			this->x5y1->Cursor = System::Windows::Forms::Cursors::Hand;
			this->x5y1->FlatAppearance->BorderSize = 0;
			this->x5y1->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->x5y1->ImageIndex = 11;
			this->x5y1->ImageList = this->button_imageList25;
			this->x5y1->Location = System::Drawing::Point(125, 25);
			this->x5y1->Margin = System::Windows::Forms::Padding(0);
			this->x5y1->Name = L"x5y1";
			this->x5y1->Size = System::Drawing::Size(25, 25);
			this->x5y1->TabIndex = 56;
			this->x5y1->TabStop = false;
			this->x5y1->UseVisualStyleBackColor = false;
			this->x5y1->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &GameWindow::MouseDown);
			// 
			// x9y1
			// 
			this->x9y1->BackColor = System::Drawing::Color::Transparent;
			this->x9y1->Cursor = System::Windows::Forms::Cursors::Hand;
			this->x9y1->FlatAppearance->BorderSize = 0;
			this->x9y1->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->x9y1->ImageIndex = 11;
			this->x9y1->ImageList = this->button_imageList25;
			this->x9y1->Location = System::Drawing::Point(225, 25);
			this->x9y1->Margin = System::Windows::Forms::Padding(0);
			this->x9y1->Name = L"x9y1";
			this->x9y1->Size = System::Drawing::Size(25, 25);
			this->x9y1->TabIndex = 60;
			this->x9y1->TabStop = false;
			this->x9y1->UseVisualStyleBackColor = false;
			this->x9y1->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &GameWindow::MouseDown);
			// 
			// x6y4
			// 
			this->x6y4->BackColor = System::Drawing::Color::Transparent;
			this->x6y4->Cursor = System::Windows::Forms::Cursors::Hand;
			this->x6y4->FlatAppearance->BorderSize = 0;
			this->x6y4->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->x6y4->ImageIndex = 11;
			this->x6y4->ImageList = this->button_imageList25;
			this->x6y4->Location = System::Drawing::Point(150, 100);
			this->x6y4->Margin = System::Windows::Forms::Padding(0);
			this->x6y4->Name = L"x6y4";
			this->x6y4->Size = System::Drawing::Size(25, 25);
			this->x6y4->TabIndex = 72;
			this->x6y4->TabStop = false;
			this->x6y4->UseVisualStyleBackColor = false;
			this->x6y4->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &GameWindow::MouseDown);
			// 
			// x9y0
			// 
			this->x9y0->BackColor = System::Drawing::Color::Transparent;
			this->x9y0->Cursor = System::Windows::Forms::Cursors::Hand;
			this->x9y0->FlatAppearance->BorderSize = 0;
			this->x9y0->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->x9y0->ImageIndex = 11;
			this->x9y0->ImageList = this->button_imageList25;
			this->x9y0->Location = System::Drawing::Point(225, 0);
			this->x9y0->Margin = System::Windows::Forms::Padding(0);
			this->x9y0->Name = L"x9y0";
			this->x9y0->Size = System::Drawing::Size(25, 25);
			this->x9y0->TabIndex = 55;
			this->x9y0->TabStop = false;
			this->x9y0->UseVisualStyleBackColor = false;
			this->x9y0->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &GameWindow::MouseDown);
			// 
			// x5y2
			// 
			this->x5y2->BackColor = System::Drawing::Color::Transparent;
			this->x5y2->Cursor = System::Windows::Forms::Cursors::Hand;
			this->x5y2->FlatAppearance->BorderSize = 0;
			this->x5y2->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->x5y2->ImageIndex = 11;
			this->x5y2->ImageList = this->button_imageList25;
			this->x5y2->Location = System::Drawing::Point(125, 50);
			this->x5y2->Margin = System::Windows::Forms::Padding(0);
			this->x5y2->Name = L"x5y2";
			this->x5y2->Size = System::Drawing::Size(25, 25);
			this->x5y2->TabIndex = 61;
			this->x5y2->TabStop = false;
			this->x5y2->UseVisualStyleBackColor = false;
			this->x5y2->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &GameWindow::MouseDown);
			// 
			// x5y4
			// 
			this->x5y4->BackColor = System::Drawing::Color::Transparent;
			this->x5y4->Cursor = System::Windows::Forms::Cursors::Hand;
			this->x5y4->FlatAppearance->BorderSize = 0;
			this->x5y4->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->x5y4->ImageIndex = 11;
			this->x5y4->ImageList = this->button_imageList25;
			this->x5y4->Location = System::Drawing::Point(125, 100);
			this->x5y4->Margin = System::Windows::Forms::Padding(0);
			this->x5y4->Name = L"x5y4";
			this->x5y4->Size = System::Drawing::Size(25, 25);
			this->x5y4->TabIndex = 71;
			this->x5y4->TabStop = false;
			this->x5y4->UseVisualStyleBackColor = false;
			this->x5y4->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &GameWindow::MouseDown);
			// 
			// x8y0
			// 
			this->x8y0->BackColor = System::Drawing::Color::Transparent;
			this->x8y0->Cursor = System::Windows::Forms::Cursors::Hand;
			this->x8y0->FlatAppearance->BorderSize = 0;
			this->x8y0->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->x8y0->ImageIndex = 11;
			this->x8y0->ImageList = this->button_imageList25;
			this->x8y0->Location = System::Drawing::Point(200, 0);
			this->x8y0->Margin = System::Windows::Forms::Padding(0);
			this->x8y0->Name = L"x8y0";
			this->x8y0->Size = System::Drawing::Size(25, 25);
			this->x8y0->TabIndex = 54;
			this->x8y0->TabStop = false;
			this->x8y0->UseVisualStyleBackColor = false;
			this->x8y0->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &GameWindow::MouseDown);
			// 
			// x6y2
			// 
			this->x6y2->BackColor = System::Drawing::Color::Transparent;
			this->x6y2->Cursor = System::Windows::Forms::Cursors::Hand;
			this->x6y2->FlatAppearance->BorderSize = 0;
			this->x6y2->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->x6y2->ImageIndex = 11;
			this->x6y2->ImageList = this->button_imageList25;
			this->x6y2->Location = System::Drawing::Point(150, 50);
			this->x6y2->Margin = System::Windows::Forms::Padding(0);
			this->x6y2->Name = L"x6y2";
			this->x6y2->Size = System::Drawing::Size(25, 25);
			this->x6y2->TabIndex = 62;
			this->x6y2->TabStop = false;
			this->x6y2->UseVisualStyleBackColor = false;
			this->x6y2->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &GameWindow::MouseDown);
			// 
			// x9y3
			// 
			this->x9y3->BackColor = System::Drawing::Color::Transparent;
			this->x9y3->Cursor = System::Windows::Forms::Cursors::Hand;
			this->x9y3->FlatAppearance->BorderSize = 0;
			this->x9y3->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->x9y3->ImageIndex = 11;
			this->x9y3->ImageList = this->button_imageList25;
			this->x9y3->Location = System::Drawing::Point(225, 75);
			this->x9y3->Margin = System::Windows::Forms::Padding(0);
			this->x9y3->Name = L"x9y3";
			this->x9y3->Size = System::Drawing::Size(25, 25);
			this->x9y3->TabIndex = 70;
			this->x9y3->TabStop = false;
			this->x9y3->UseVisualStyleBackColor = false;
			this->x9y3->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &GameWindow::MouseDown);
			// 
			// x7y0
			// 
			this->x7y0->BackColor = System::Drawing::Color::Transparent;
			this->x7y0->Cursor = System::Windows::Forms::Cursors::Hand;
			this->x7y0->FlatAppearance->BorderSize = 0;
			this->x7y0->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->x7y0->ImageIndex = 11;
			this->x7y0->ImageList = this->button_imageList25;
			this->x7y0->Location = System::Drawing::Point(175, 0);
			this->x7y0->Margin = System::Windows::Forms::Padding(0);
			this->x7y0->Name = L"x7y0";
			this->x7y0->Size = System::Drawing::Size(25, 25);
			this->x7y0->TabIndex = 53;
			this->x7y0->TabStop = false;
			this->x7y0->UseVisualStyleBackColor = false;
			this->x7y0->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &GameWindow::MouseDown);
			// 
			// x7y2
			// 
			this->x7y2->BackColor = System::Drawing::Color::Transparent;
			this->x7y2->Cursor = System::Windows::Forms::Cursors::Hand;
			this->x7y2->FlatAppearance->BorderSize = 0;
			this->x7y2->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->x7y2->ImageIndex = 11;
			this->x7y2->ImageList = this->button_imageList25;
			this->x7y2->Location = System::Drawing::Point(175, 50);
			this->x7y2->Margin = System::Windows::Forms::Padding(0);
			this->x7y2->Name = L"x7y2";
			this->x7y2->Size = System::Drawing::Size(25, 25);
			this->x7y2->TabIndex = 63;
			this->x7y2->TabStop = false;
			this->x7y2->UseVisualStyleBackColor = false;
			this->x7y2->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &GameWindow::MouseDown);
			// 
			// x8y3
			// 
			this->x8y3->BackColor = System::Drawing::Color::Transparent;
			this->x8y3->Cursor = System::Windows::Forms::Cursors::Hand;
			this->x8y3->FlatAppearance->BorderSize = 0;
			this->x8y3->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->x8y3->ImageIndex = 11;
			this->x8y3->ImageList = this->button_imageList25;
			this->x8y3->Location = System::Drawing::Point(200, 75);
			this->x8y3->Margin = System::Windows::Forms::Padding(0);
			this->x8y3->Name = L"x8y3";
			this->x8y3->Size = System::Drawing::Size(25, 25);
			this->x8y3->TabIndex = 69;
			this->x8y3->TabStop = false;
			this->x8y3->UseVisualStyleBackColor = false;
			this->x8y3->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &GameWindow::MouseDown);
			// 
			// x6y0
			// 
			this->x6y0->BackColor = System::Drawing::Color::Transparent;
			this->x6y0->Cursor = System::Windows::Forms::Cursors::Hand;
			this->x6y0->FlatAppearance->BorderSize = 0;
			this->x6y0->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->x6y0->ImageIndex = 11;
			this->x6y0->ImageList = this->button_imageList25;
			this->x6y0->Location = System::Drawing::Point(150, 0);
			this->x6y0->Margin = System::Windows::Forms::Padding(0);
			this->x6y0->Name = L"x6y0";
			this->x6y0->Size = System::Drawing::Size(25, 25);
			this->x6y0->TabIndex = 52;
			this->x6y0->TabStop = false;
			this->x6y0->UseVisualStyleBackColor = false;
			this->x6y0->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &GameWindow::MouseDown);
			// 
			// x8y2
			// 
			this->x8y2->BackColor = System::Drawing::Color::Transparent;
			this->x8y2->Cursor = System::Windows::Forms::Cursors::Hand;
			this->x8y2->FlatAppearance->BorderSize = 0;
			this->x8y2->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->x8y2->ImageIndex = 11;
			this->x8y2->ImageList = this->button_imageList25;
			this->x8y2->Location = System::Drawing::Point(200, 50);
			this->x8y2->Margin = System::Windows::Forms::Padding(0);
			this->x8y2->Name = L"x8y2";
			this->x8y2->Size = System::Drawing::Size(25, 25);
			this->x8y2->TabIndex = 64;
			this->x8y2->TabStop = false;
			this->x8y2->UseVisualStyleBackColor = false;
			this->x8y2->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &GameWindow::MouseDown);
			// 
			// x7y3
			// 
			this->x7y3->BackColor = System::Drawing::Color::Transparent;
			this->x7y3->Cursor = System::Windows::Forms::Cursors::Hand;
			this->x7y3->FlatAppearance->BorderSize = 0;
			this->x7y3->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->x7y3->ImageIndex = 11;
			this->x7y3->ImageList = this->button_imageList25;
			this->x7y3->Location = System::Drawing::Point(175, 75);
			this->x7y3->Margin = System::Windows::Forms::Padding(0);
			this->x7y3->Name = L"x7y3";
			this->x7y3->Size = System::Drawing::Size(25, 25);
			this->x7y3->TabIndex = 68;
			this->x7y3->TabStop = false;
			this->x7y3->UseVisualStyleBackColor = false;
			this->x7y3->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &GameWindow::MouseDown);
			// 
			// x9y2
			// 
			this->x9y2->BackColor = System::Drawing::Color::Transparent;
			this->x9y2->Cursor = System::Windows::Forms::Cursors::Hand;
			this->x9y2->FlatAppearance->BorderSize = 0;
			this->x9y2->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->x9y2->ImageIndex = 11;
			this->x9y2->ImageList = this->button_imageList25;
			this->x9y2->Location = System::Drawing::Point(225, 50);
			this->x9y2->Margin = System::Windows::Forms::Padding(0);
			this->x9y2->Name = L"x9y2";
			this->x9y2->Size = System::Drawing::Size(25, 25);
			this->x9y2->TabIndex = 65;
			this->x9y2->TabStop = false;
			this->x9y2->UseVisualStyleBackColor = false;
			this->x9y2->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &GameWindow::MouseDown);
			// 
			// x5y3
			// 
			this->x5y3->BackColor = System::Drawing::Color::Transparent;
			this->x5y3->Cursor = System::Windows::Forms::Cursors::Hand;
			this->x5y3->FlatAppearance->BorderSize = 0;
			this->x5y3->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->x5y3->ImageIndex = 11;
			this->x5y3->ImageList = this->button_imageList25;
			this->x5y3->Location = System::Drawing::Point(125, 75);
			this->x5y3->Margin = System::Windows::Forms::Padding(0);
			this->x5y3->Name = L"x5y3";
			this->x5y3->Size = System::Drawing::Size(25, 25);
			this->x5y3->TabIndex = 66;
			this->x5y3->TabStop = false;
			this->x5y3->UseVisualStyleBackColor = false;
			this->x5y3->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &GameWindow::MouseDown);
			// 
			// x6y3
			// 
			this->x6y3->BackColor = System::Drawing::Color::Transparent;
			this->x6y3->Cursor = System::Windows::Forms::Cursors::Hand;
			this->x6y3->FlatAppearance->BorderSize = 0;
			this->x6y3->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->x6y3->ImageIndex = 11;
			this->x6y3->ImageList = this->button_imageList25;
			this->x6y3->Location = System::Drawing::Point(150, 75);
			this->x6y3->Margin = System::Windows::Forms::Padding(0);
			this->x6y3->Name = L"x6y3";
			this->x6y3->Size = System::Drawing::Size(25, 25);
			this->x6y3->TabIndex = 67;
			this->x6y3->TabStop = false;
			this->x6y3->UseVisualStyleBackColor = false;
			this->x6y3->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &GameWindow::MouseDown);
			// 
			// x4y9
			// 
			this->x4y9->BackColor = System::Drawing::Color::Transparent;
			this->x4y9->Cursor = System::Windows::Forms::Cursors::Hand;
			this->x4y9->FlatAppearance->BorderSize = 0;
			this->x4y9->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->x4y9->ImageIndex = 11;
			this->x4y9->ImageList = this->button_imageList25;
			this->x4y9->Location = System::Drawing::Point(100, 225);
			this->x4y9->Margin = System::Windows::Forms::Padding(0);
			this->x4y9->Name = L"x4y9";
			this->x4y9->Size = System::Drawing::Size(25, 25);
			this->x4y9->TabIndex = 50;
			this->x4y9->TabStop = false;
			this->x4y9->UseVisualStyleBackColor = false;
			this->x4y9->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &GameWindow::MouseDown);
			// 
			// x0y5
			// 
			this->x0y5->BackColor = System::Drawing::Color::Transparent;
			this->x0y5->Cursor = System::Windows::Forms::Cursors::Hand;
			this->x0y5->FlatAppearance->BorderSize = 0;
			this->x0y5->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->x0y5->ImageIndex = 11;
			this->x0y5->ImageList = this->button_imageList25;
			this->x0y5->Location = System::Drawing::Point(0, 125);
			this->x0y5->Margin = System::Windows::Forms::Padding(0);
			this->x0y5->Name = L"x0y5";
			this->x0y5->Size = System::Drawing::Size(25, 25);
			this->x0y5->TabIndex = 26;
			this->x0y5->TabStop = false;
			this->x0y5->UseVisualStyleBackColor = false;
			this->x0y5->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &GameWindow::MouseDown);
			// 
			// x2y6
			// 
			this->x2y6->BackColor = System::Drawing::Color::Transparent;
			this->x2y6->Cursor = System::Windows::Forms::Cursors::Hand;
			this->x2y6->FlatAppearance->BorderSize = 0;
			this->x2y6->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->x2y6->ImageIndex = 11;
			this->x2y6->ImageList = this->button_imageList25;
			this->x2y6->Location = System::Drawing::Point(50, 150);
			this->x2y6->Margin = System::Windows::Forms::Padding(0);
			this->x2y6->Name = L"x2y6";
			this->x2y6->Size = System::Drawing::Size(25, 25);
			this->x2y6->TabIndex = 33;
			this->x2y6->TabStop = false;
			this->x2y6->UseVisualStyleBackColor = false;
			this->x2y6->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &GameWindow::MouseDown);
			// 
			// x3y9
			// 
			this->x3y9->BackColor = System::Drawing::Color::Transparent;
			this->x3y9->Cursor = System::Windows::Forms::Cursors::Hand;
			this->x3y9->FlatAppearance->BorderSize = 0;
			this->x3y9->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->x3y9->ImageIndex = 11;
			this->x3y9->ImageList = this->button_imageList25;
			this->x3y9->Location = System::Drawing::Point(75, 225);
			this->x3y9->Margin = System::Windows::Forms::Padding(0);
			this->x3y9->Name = L"x3y9";
			this->x3y9->Size = System::Drawing::Size(25, 25);
			this->x3y9->TabIndex = 49;
			this->x3y9->TabStop = false;
			this->x3y9->UseVisualStyleBackColor = false;
			this->x3y9->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &GameWindow::MouseDown);
			// 
			// x1y6
			// 
			this->x1y6->BackColor = System::Drawing::Color::Transparent;
			this->x1y6->Cursor = System::Windows::Forms::Cursors::Hand;
			this->x1y6->FlatAppearance->BorderSize = 0;
			this->x1y6->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->x1y6->ImageIndex = 11;
			this->x1y6->ImageList = this->button_imageList25;
			this->x1y6->Location = System::Drawing::Point(25, 150);
			this->x1y6->Margin = System::Windows::Forms::Padding(0);
			this->x1y6->Name = L"x1y6";
			this->x1y6->Size = System::Drawing::Size(25, 25);
			this->x1y6->TabIndex = 32;
			this->x1y6->TabStop = false;
			this->x1y6->UseVisualStyleBackColor = false;
			this->x1y6->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &GameWindow::MouseDown);
			// 
			// x3y6
			// 
			this->x3y6->BackColor = System::Drawing::Color::Transparent;
			this->x3y6->Cursor = System::Windows::Forms::Cursors::Hand;
			this->x3y6->FlatAppearance->BorderSize = 0;
			this->x3y6->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->x3y6->ImageIndex = 11;
			this->x3y6->ImageList = this->button_imageList25;
			this->x3y6->Location = System::Drawing::Point(75, 150);
			this->x3y6->Margin = System::Windows::Forms::Padding(0);
			this->x3y6->Name = L"x3y6";
			this->x3y6->Size = System::Drawing::Size(25, 25);
			this->x3y6->TabIndex = 34;
			this->x3y6->TabStop = false;
			this->x3y6->UseVisualStyleBackColor = false;
			this->x3y6->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &GameWindow::MouseDown);
			// 
			// x2y9
			// 
			this->x2y9->BackColor = System::Drawing::Color::Transparent;
			this->x2y9->Cursor = System::Windows::Forms::Cursors::Hand;
			this->x2y9->FlatAppearance->BorderSize = 0;
			this->x2y9->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->x2y9->ImageIndex = 11;
			this->x2y9->ImageList = this->button_imageList25;
			this->x2y9->Location = System::Drawing::Point(50, 225);
			this->x2y9->Margin = System::Windows::Forms::Padding(0);
			this->x2y9->Name = L"x2y9";
			this->x2y9->Size = System::Drawing::Size(25, 25);
			this->x2y9->TabIndex = 48;
			this->x2y9->TabStop = false;
			this->x2y9->UseVisualStyleBackColor = false;
			this->x2y9->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &GameWindow::MouseDown);
			// 
			// x0y6
			// 
			this->x0y6->BackColor = System::Drawing::Color::Transparent;
			this->x0y6->Cursor = System::Windows::Forms::Cursors::Hand;
			this->x0y6->FlatAppearance->BorderSize = 0;
			this->x0y6->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->x0y6->ImageIndex = 11;
			this->x0y6->ImageList = this->button_imageList25;
			this->x0y6->Location = System::Drawing::Point(0, 150);
			this->x0y6->Margin = System::Windows::Forms::Padding(0);
			this->x0y6->Name = L"x0y6";
			this->x0y6->Size = System::Drawing::Size(25, 25);
			this->x0y6->TabIndex = 31;
			this->x0y6->TabStop = false;
			this->x0y6->UseVisualStyleBackColor = false;
			this->x0y6->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &GameWindow::MouseDown);
			// 
			// x4y6
			// 
			this->x4y6->BackColor = System::Drawing::Color::Transparent;
			this->x4y6->Cursor = System::Windows::Forms::Cursors::Hand;
			this->x4y6->FlatAppearance->BorderSize = 0;
			this->x4y6->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->x4y6->ImageIndex = 11;
			this->x4y6->ImageList = this->button_imageList25;
			this->x4y6->Location = System::Drawing::Point(100, 150);
			this->x4y6->Margin = System::Windows::Forms::Padding(0);
			this->x4y6->Name = L"x4y6";
			this->x4y6->Size = System::Drawing::Size(25, 25);
			this->x4y6->TabIndex = 35;
			this->x4y6->TabStop = false;
			this->x4y6->UseVisualStyleBackColor = false;
			this->x4y6->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &GameWindow::MouseDown);
			// 
			// x1y9
			// 
			this->x1y9->BackColor = System::Drawing::Color::Transparent;
			this->x1y9->Cursor = System::Windows::Forms::Cursors::Hand;
			this->x1y9->FlatAppearance->BorderSize = 0;
			this->x1y9->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->x1y9->ImageIndex = 11;
			this->x1y9->ImageList = this->button_imageList25;
			this->x1y9->Location = System::Drawing::Point(25, 225);
			this->x1y9->Margin = System::Windows::Forms::Padding(0);
			this->x1y9->Name = L"x1y9";
			this->x1y9->Size = System::Drawing::Size(25, 25);
			this->x1y9->TabIndex = 47;
			this->x1y9->TabStop = false;
			this->x1y9->UseVisualStyleBackColor = false;
			this->x1y9->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &GameWindow::MouseDown);
			// 
			// x4y5
			// 
			this->x4y5->BackColor = System::Drawing::Color::Transparent;
			this->x4y5->Cursor = System::Windows::Forms::Cursors::Hand;
			this->x4y5->FlatAppearance->BorderSize = 0;
			this->x4y5->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->x4y5->ImageIndex = 11;
			this->x4y5->ImageList = this->button_imageList25;
			this->x4y5->Location = System::Drawing::Point(100, 125);
			this->x4y5->Margin = System::Windows::Forms::Padding(0);
			this->x4y5->Name = L"x4y5";
			this->x4y5->Size = System::Drawing::Size(25, 25);
			this->x4y5->TabIndex = 30;
			this->x4y5->TabStop = false;
			this->x4y5->UseVisualStyleBackColor = false;
			this->x4y5->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &GameWindow::MouseDown);
			// 
			// x0y7
			// 
			this->x0y7->BackColor = System::Drawing::Color::Transparent;
			this->x0y7->Cursor = System::Windows::Forms::Cursors::Hand;
			this->x0y7->FlatAppearance->BorderSize = 0;
			this->x0y7->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->x0y7->ImageIndex = 11;
			this->x0y7->ImageList = this->button_imageList25;
			this->x0y7->Location = System::Drawing::Point(0, 175);
			this->x0y7->Margin = System::Windows::Forms::Padding(0);
			this->x0y7->Name = L"x0y7";
			this->x0y7->Size = System::Drawing::Size(25, 25);
			this->x0y7->TabIndex = 36;
			this->x0y7->TabStop = false;
			this->x0y7->UseVisualStyleBackColor = false;
			this->x0y7->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &GameWindow::MouseDown);
			// 
			// x0y9
			// 
			this->x0y9->BackColor = System::Drawing::Color::Transparent;
			this->x0y9->Cursor = System::Windows::Forms::Cursors::Hand;
			this->x0y9->FlatAppearance->BorderSize = 0;
			this->x0y9->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->x0y9->ImageIndex = 11;
			this->x0y9->ImageList = this->button_imageList25;
			this->x0y9->Location = System::Drawing::Point(0, 225);
			this->x0y9->Margin = System::Windows::Forms::Padding(0);
			this->x0y9->Name = L"x0y9";
			this->x0y9->Size = System::Drawing::Size(25, 25);
			this->x0y9->TabIndex = 46;
			this->x0y9->TabStop = false;
			this->x0y9->UseVisualStyleBackColor = false;
			this->x0y9->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &GameWindow::MouseDown);
			// 
			// x3y5
			// 
			this->x3y5->BackColor = System::Drawing::Color::Transparent;
			this->x3y5->Cursor = System::Windows::Forms::Cursors::Hand;
			this->x3y5->FlatAppearance->BorderSize = 0;
			this->x3y5->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->x3y5->ImageIndex = 11;
			this->x3y5->ImageList = this->button_imageList25;
			this->x3y5->Location = System::Drawing::Point(75, 125);
			this->x3y5->Margin = System::Windows::Forms::Padding(0);
			this->x3y5->Name = L"x3y5";
			this->x3y5->Size = System::Drawing::Size(25, 25);
			this->x3y5->TabIndex = 29;
			this->x3y5->TabStop = false;
			this->x3y5->UseVisualStyleBackColor = false;
			this->x3y5->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &GameWindow::MouseDown);
			// 
			// x1y7
			// 
			this->x1y7->BackColor = System::Drawing::Color::Transparent;
			this->x1y7->Cursor = System::Windows::Forms::Cursors::Hand;
			this->x1y7->FlatAppearance->BorderSize = 0;
			this->x1y7->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->x1y7->ImageIndex = 11;
			this->x1y7->ImageList = this->button_imageList25;
			this->x1y7->Location = System::Drawing::Point(25, 175);
			this->x1y7->Margin = System::Windows::Forms::Padding(0);
			this->x1y7->Name = L"x1y7";
			this->x1y7->Size = System::Drawing::Size(25, 25);
			this->x1y7->TabIndex = 37;
			this->x1y7->TabStop = false;
			this->x1y7->UseVisualStyleBackColor = false;
			this->x1y7->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &GameWindow::MouseDown);
			// 
			// x4y8
			// 
			this->x4y8->BackColor = System::Drawing::Color::Transparent;
			this->x4y8->Cursor = System::Windows::Forms::Cursors::Hand;
			this->x4y8->FlatAppearance->BorderSize = 0;
			this->x4y8->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->x4y8->ImageIndex = 11;
			this->x4y8->ImageList = this->button_imageList25;
			this->x4y8->Location = System::Drawing::Point(100, 200);
			this->x4y8->Margin = System::Windows::Forms::Padding(0);
			this->x4y8->Name = L"x4y8";
			this->x4y8->Size = System::Drawing::Size(25, 25);
			this->x4y8->TabIndex = 45;
			this->x4y8->TabStop = false;
			this->x4y8->UseVisualStyleBackColor = false;
			this->x4y8->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &GameWindow::MouseDown);
			// 
			// x2y5
			// 
			this->x2y5->BackColor = System::Drawing::Color::Transparent;
			this->x2y5->Cursor = System::Windows::Forms::Cursors::Hand;
			this->x2y5->FlatAppearance->BorderSize = 0;
			this->x2y5->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->x2y5->ImageIndex = 11;
			this->x2y5->ImageList = this->button_imageList25;
			this->x2y5->Location = System::Drawing::Point(50, 125);
			this->x2y5->Margin = System::Windows::Forms::Padding(0);
			this->x2y5->Name = L"x2y5";
			this->x2y5->Size = System::Drawing::Size(25, 25);
			this->x2y5->TabIndex = 28;
			this->x2y5->TabStop = false;
			this->x2y5->UseVisualStyleBackColor = false;
			this->x2y5->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &GameWindow::MouseDown);
			// 
			// x2y7
			// 
			this->x2y7->BackColor = System::Drawing::Color::Transparent;
			this->x2y7->Cursor = System::Windows::Forms::Cursors::Hand;
			this->x2y7->FlatAppearance->BorderSize = 0;
			this->x2y7->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->x2y7->ImageIndex = 11;
			this->x2y7->ImageList = this->button_imageList25;
			this->x2y7->Location = System::Drawing::Point(50, 175);
			this->x2y7->Margin = System::Windows::Forms::Padding(0);
			this->x2y7->Name = L"x2y7";
			this->x2y7->Size = System::Drawing::Size(25, 25);
			this->x2y7->TabIndex = 38;
			this->x2y7->TabStop = false;
			this->x2y7->UseVisualStyleBackColor = false;
			this->x2y7->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &GameWindow::MouseDown);
			// 
			// x3y8
			// 
			this->x3y8->BackColor = System::Drawing::Color::Transparent;
			this->x3y8->Cursor = System::Windows::Forms::Cursors::Hand;
			this->x3y8->FlatAppearance->BorderSize = 0;
			this->x3y8->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->x3y8->ImageIndex = 11;
			this->x3y8->ImageList = this->button_imageList25;
			this->x3y8->Location = System::Drawing::Point(75, 200);
			this->x3y8->Margin = System::Windows::Forms::Padding(0);
			this->x3y8->Name = L"x3y8";
			this->x3y8->Size = System::Drawing::Size(25, 25);
			this->x3y8->TabIndex = 44;
			this->x3y8->TabStop = false;
			this->x3y8->UseVisualStyleBackColor = false;
			this->x3y8->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &GameWindow::MouseDown);
			// 
			// x1y5
			// 
			this->x1y5->BackColor = System::Drawing::Color::Transparent;
			this->x1y5->Cursor = System::Windows::Forms::Cursors::Hand;
			this->x1y5->FlatAppearance->BorderSize = 0;
			this->x1y5->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->x1y5->ImageIndex = 11;
			this->x1y5->ImageList = this->button_imageList25;
			this->x1y5->Location = System::Drawing::Point(25, 125);
			this->x1y5->Margin = System::Windows::Forms::Padding(0);
			this->x1y5->Name = L"x1y5";
			this->x1y5->Size = System::Drawing::Size(25, 25);
			this->x1y5->TabIndex = 27;
			this->x1y5->TabStop = false;
			this->x1y5->UseVisualStyleBackColor = false;
			this->x1y5->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &GameWindow::MouseDown);
			// 
			// x3y7
			// 
			this->x3y7->BackColor = System::Drawing::Color::Transparent;
			this->x3y7->Cursor = System::Windows::Forms::Cursors::Hand;
			this->x3y7->FlatAppearance->BorderSize = 0;
			this->x3y7->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->x3y7->ImageIndex = 11;
			this->x3y7->ImageList = this->button_imageList25;
			this->x3y7->Location = System::Drawing::Point(75, 175);
			this->x3y7->Margin = System::Windows::Forms::Padding(0);
			this->x3y7->Name = L"x3y7";
			this->x3y7->Size = System::Drawing::Size(25, 25);
			this->x3y7->TabIndex = 39;
			this->x3y7->TabStop = false;
			this->x3y7->UseVisualStyleBackColor = false;
			this->x3y7->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &GameWindow::MouseDown);
			// 
			// x2y8
			// 
			this->x2y8->BackColor = System::Drawing::Color::Transparent;
			this->x2y8->Cursor = System::Windows::Forms::Cursors::Hand;
			this->x2y8->FlatAppearance->BorderSize = 0;
			this->x2y8->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->x2y8->ImageIndex = 11;
			this->x2y8->ImageList = this->button_imageList25;
			this->x2y8->Location = System::Drawing::Point(50, 200);
			this->x2y8->Margin = System::Windows::Forms::Padding(0);
			this->x2y8->Name = L"x2y8";
			this->x2y8->Size = System::Drawing::Size(25, 25);
			this->x2y8->TabIndex = 43;
			this->x2y8->TabStop = false;
			this->x2y8->UseVisualStyleBackColor = false;
			this->x2y8->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &GameWindow::MouseDown);
			// 
			// x4y7
			// 
			this->x4y7->BackColor = System::Drawing::Color::Transparent;
			this->x4y7->Cursor = System::Windows::Forms::Cursors::Hand;
			this->x4y7->FlatAppearance->BorderSize = 0;
			this->x4y7->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->x4y7->ImageIndex = 11;
			this->x4y7->ImageList = this->button_imageList25;
			this->x4y7->Location = System::Drawing::Point(100, 175);
			this->x4y7->Margin = System::Windows::Forms::Padding(0);
			this->x4y7->Name = L"x4y7";
			this->x4y7->Size = System::Drawing::Size(25, 25);
			this->x4y7->TabIndex = 40;
			this->x4y7->TabStop = false;
			this->x4y7->UseVisualStyleBackColor = false;
			this->x4y7->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &GameWindow::MouseDown);
			// 
			// x0y8
			// 
			this->x0y8->BackColor = System::Drawing::Color::Transparent;
			this->x0y8->Cursor = System::Windows::Forms::Cursors::Hand;
			this->x0y8->FlatAppearance->BorderSize = 0;
			this->x0y8->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->x0y8->ImageIndex = 11;
			this->x0y8->ImageList = this->button_imageList25;
			this->x0y8->Location = System::Drawing::Point(0, 200);
			this->x0y8->Margin = System::Windows::Forms::Padding(0);
			this->x0y8->Name = L"x0y8";
			this->x0y8->Size = System::Drawing::Size(25, 25);
			this->x0y8->TabIndex = 41;
			this->x0y8->TabStop = false;
			this->x0y8->UseVisualStyleBackColor = false;
			this->x0y8->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &GameWindow::MouseDown);
			// 
			// x1y8
			// 
			this->x1y8->BackColor = System::Drawing::Color::Transparent;
			this->x1y8->Cursor = System::Windows::Forms::Cursors::Hand;
			this->x1y8->FlatAppearance->BorderSize = 0;
			this->x1y8->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->x1y8->ImageIndex = 11;
			this->x1y8->ImageList = this->button_imageList25;
			this->x1y8->Location = System::Drawing::Point(25, 200);
			this->x1y8->Margin = System::Windows::Forms::Padding(0);
			this->x1y8->Name = L"x1y8";
			this->x1y8->Size = System::Drawing::Size(25, 25);
			this->x1y8->TabIndex = 42;
			this->x1y8->TabStop = false;
			this->x1y8->UseVisualStyleBackColor = false;
			this->x1y8->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &GameWindow::MouseDown);
			// 
			// x4y4
			// 
			this->x4y4->BackColor = System::Drawing::Color::Transparent;
			this->x4y4->Cursor = System::Windows::Forms::Cursors::Hand;
			this->x4y4->FlatAppearance->BorderSize = 0;
			this->x4y4->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->x4y4->ImageIndex = 11;
			this->x4y4->ImageList = this->button_imageList25;
			this->x4y4->Location = System::Drawing::Point(100, 100);
			this->x4y4->Margin = System::Windows::Forms::Padding(0);
			this->x4y4->Name = L"x4y4";
			this->x4y4->Size = System::Drawing::Size(25, 25);
			this->x4y4->TabIndex = 25;
			this->x4y4->TabStop = false;
			this->x4y4->UseVisualStyleBackColor = false;
			this->x4y4->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &GameWindow::MouseDown);
			// 
			// x2y1
			// 
			this->x2y1->BackColor = System::Drawing::Color::Transparent;
			this->x2y1->Cursor = System::Windows::Forms::Cursors::Hand;
			this->x2y1->FlatAppearance->BorderSize = 0;
			this->x2y1->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->x2y1->ImageIndex = 11;
			this->x2y1->ImageList = this->button_imageList25;
			this->x2y1->Location = System::Drawing::Point(50, 25);
			this->x2y1->Margin = System::Windows::Forms::Padding(0);
			this->x2y1->Name = L"x2y1";
			this->x2y1->Size = System::Drawing::Size(25, 25);
			this->x2y1->TabIndex = 8;
			this->x2y1->TabStop = false;
			this->x2y1->UseVisualStyleBackColor = false;
			this->x2y1->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &GameWindow::MouseDown);
			// 
			// x3y4
			// 
			this->x3y4->BackColor = System::Drawing::Color::Transparent;
			this->x3y4->Cursor = System::Windows::Forms::Cursors::Hand;
			this->x3y4->FlatAppearance->BorderSize = 0;
			this->x3y4->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->x3y4->ImageIndex = 11;
			this->x3y4->ImageList = this->button_imageList25;
			this->x3y4->Location = System::Drawing::Point(75, 100);
			this->x3y4->Margin = System::Windows::Forms::Padding(0);
			this->x3y4->Name = L"x3y4";
			this->x3y4->Size = System::Drawing::Size(25, 25);
			this->x3y4->TabIndex = 24;
			this->x3y4->TabStop = false;
			this->x3y4->UseVisualStyleBackColor = false;
			this->x3y4->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &GameWindow::MouseDown);
			// 
			// x1y1
			// 
			this->x1y1->BackColor = System::Drawing::Color::Transparent;
			this->x1y1->Cursor = System::Windows::Forms::Cursors::Hand;
			this->x1y1->FlatAppearance->BorderSize = 0;
			this->x1y1->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->x1y1->ImageIndex = 11;
			this->x1y1->ImageList = this->button_imageList25;
			this->x1y1->Location = System::Drawing::Point(25, 25);
			this->x1y1->Margin = System::Windows::Forms::Padding(0);
			this->x1y1->Name = L"x1y1";
			this->x1y1->Size = System::Drawing::Size(25, 25);
			this->x1y1->TabIndex = 7;
			this->x1y1->TabStop = false;
			this->x1y1->UseVisualStyleBackColor = false;
			this->x1y1->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &GameWindow::MouseDown);
			// 
			// x3y1
			// 
			this->x3y1->BackColor = System::Drawing::Color::Transparent;
			this->x3y1->Cursor = System::Windows::Forms::Cursors::Hand;
			this->x3y1->FlatAppearance->BorderSize = 0;
			this->x3y1->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->x3y1->ImageIndex = 11;
			this->x3y1->ImageList = this->button_imageList25;
			this->x3y1->Location = System::Drawing::Point(75, 25);
			this->x3y1->Margin = System::Windows::Forms::Padding(0);
			this->x3y1->Name = L"x3y1";
			this->x3y1->Size = System::Drawing::Size(25, 25);
			this->x3y1->TabIndex = 9;
			this->x3y1->TabStop = false;
			this->x3y1->UseVisualStyleBackColor = false;
			this->x3y1->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &GameWindow::MouseDown);
			// 
			// x2y4
			// 
			this->x2y4->BackColor = System::Drawing::Color::Transparent;
			this->x2y4->Cursor = System::Windows::Forms::Cursors::Hand;
			this->x2y4->FlatAppearance->BorderSize = 0;
			this->x2y4->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->x2y4->ImageIndex = 11;
			this->x2y4->ImageList = this->button_imageList25;
			this->x2y4->Location = System::Drawing::Point(50, 100);
			this->x2y4->Margin = System::Windows::Forms::Padding(0);
			this->x2y4->Name = L"x2y4";
			this->x2y4->Size = System::Drawing::Size(25, 25);
			this->x2y4->TabIndex = 23;
			this->x2y4->TabStop = false;
			this->x2y4->UseVisualStyleBackColor = false;
			this->x2y4->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &GameWindow::MouseDown);
			// 
			// x0y1
			// 
			this->x0y1->BackColor = System::Drawing::Color::Transparent;
			this->x0y1->Cursor = System::Windows::Forms::Cursors::Hand;
			this->x0y1->FlatAppearance->BorderSize = 0;
			this->x0y1->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->x0y1->ImageIndex = 11;
			this->x0y1->ImageList = this->button_imageList25;
			this->x0y1->Location = System::Drawing::Point(0, 25);
			this->x0y1->Margin = System::Windows::Forms::Padding(0);
			this->x0y1->Name = L"x0y1";
			this->x0y1->Size = System::Drawing::Size(25, 25);
			this->x0y1->TabIndex = 6;
			this->x0y1->TabStop = false;
			this->x0y1->UseVisualStyleBackColor = false;
			this->x0y1->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &GameWindow::MouseDown);
			// 
			// x4y1
			// 
			this->x4y1->BackColor = System::Drawing::Color::Transparent;
			this->x4y1->Cursor = System::Windows::Forms::Cursors::Hand;
			this->x4y1->FlatAppearance->BorderSize = 0;
			this->x4y1->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->x4y1->ImageIndex = 11;
			this->x4y1->ImageList = this->button_imageList25;
			this->x4y1->Location = System::Drawing::Point(100, 25);
			this->x4y1->Margin = System::Windows::Forms::Padding(0);
			this->x4y1->Name = L"x4y1";
			this->x4y1->Size = System::Drawing::Size(25, 25);
			this->x4y1->TabIndex = 10;
			this->x4y1->TabStop = false;
			this->x4y1->UseVisualStyleBackColor = false;
			this->x4y1->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &GameWindow::MouseDown);
			// 
			// x1y4
			// 
			this->x1y4->BackColor = System::Drawing::Color::Transparent;
			this->x1y4->Cursor = System::Windows::Forms::Cursors::Hand;
			this->x1y4->FlatAppearance->BorderSize = 0;
			this->x1y4->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->x1y4->ImageIndex = 11;
			this->x1y4->ImageList = this->button_imageList25;
			this->x1y4->Location = System::Drawing::Point(25, 100);
			this->x1y4->Margin = System::Windows::Forms::Padding(0);
			this->x1y4->Name = L"x1y4";
			this->x1y4->Size = System::Drawing::Size(25, 25);
			this->x1y4->TabIndex = 22;
			this->x1y4->TabStop = false;
			this->x1y4->UseVisualStyleBackColor = false;
			this->x1y4->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &GameWindow::MouseDown);
			// 
			// x4y0
			// 
			this->x4y0->BackColor = System::Drawing::Color::Transparent;
			this->x4y0->Cursor = System::Windows::Forms::Cursors::Hand;
			this->x4y0->FlatAppearance->BorderSize = 0;
			this->x4y0->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->x4y0->ImageIndex = 11;
			this->x4y0->ImageList = this->button_imageList25;
			this->x4y0->Location = System::Drawing::Point(100, 0);
			this->x4y0->Margin = System::Windows::Forms::Padding(0);
			this->x4y0->Name = L"x4y0";
			this->x4y0->Size = System::Drawing::Size(25, 25);
			this->x4y0->TabIndex = 5;
			this->x4y0->TabStop = false;
			this->x4y0->UseVisualStyleBackColor = false;
			this->x4y0->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &GameWindow::MouseDown);
			// 
			// x0y2
			// 
			this->x0y2->BackColor = System::Drawing::Color::Transparent;
			this->x0y2->Cursor = System::Windows::Forms::Cursors::Hand;
			this->x0y2->FlatAppearance->BorderSize = 0;
			this->x0y2->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->x0y2->ImageIndex = 11;
			this->x0y2->ImageList = this->button_imageList25;
			this->x0y2->Location = System::Drawing::Point(0, 50);
			this->x0y2->Margin = System::Windows::Forms::Padding(0);
			this->x0y2->Name = L"x0y2";
			this->x0y2->Size = System::Drawing::Size(25, 25);
			this->x0y2->TabIndex = 11;
			this->x0y2->TabStop = false;
			this->x0y2->UseVisualStyleBackColor = false;
			this->x0y2->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &GameWindow::MouseDown);
			// 
			// x0y4
			// 
			this->x0y4->BackColor = System::Drawing::Color::Transparent;
			this->x0y4->Cursor = System::Windows::Forms::Cursors::Hand;
			this->x0y4->FlatAppearance->BorderSize = 0;
			this->x0y4->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->x0y4->ImageIndex = 11;
			this->x0y4->ImageList = this->button_imageList25;
			this->x0y4->Location = System::Drawing::Point(0, 100);
			this->x0y4->Margin = System::Windows::Forms::Padding(0);
			this->x0y4->Name = L"x0y4";
			this->x0y4->Size = System::Drawing::Size(25, 25);
			this->x0y4->TabIndex = 21;
			this->x0y4->TabStop = false;
			this->x0y4->UseVisualStyleBackColor = false;
			this->x0y4->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &GameWindow::MouseDown);
			// 
			// x3y0
			// 
			this->x3y0->BackColor = System::Drawing::Color::Transparent;
			this->x3y0->Cursor = System::Windows::Forms::Cursors::Hand;
			this->x3y0->FlatAppearance->BorderSize = 0;
			this->x3y0->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->x3y0->ImageIndex = 11;
			this->x3y0->ImageList = this->button_imageList25;
			this->x3y0->Location = System::Drawing::Point(75, 0);
			this->x3y0->Margin = System::Windows::Forms::Padding(0);
			this->x3y0->Name = L"x3y0";
			this->x3y0->Size = System::Drawing::Size(25, 25);
			this->x3y0->TabIndex = 4;
			this->x3y0->TabStop = false;
			this->x3y0->UseVisualStyleBackColor = false;
			this->x3y0->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &GameWindow::MouseDown);
			// 
			// x1y2
			// 
			this->x1y2->BackColor = System::Drawing::Color::Transparent;
			this->x1y2->Cursor = System::Windows::Forms::Cursors::Hand;
			this->x1y2->FlatAppearance->BorderSize = 0;
			this->x1y2->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->x1y2->ImageIndex = 11;
			this->x1y2->ImageList = this->button_imageList25;
			this->x1y2->Location = System::Drawing::Point(25, 50);
			this->x1y2->Margin = System::Windows::Forms::Padding(0);
			this->x1y2->Name = L"x1y2";
			this->x1y2->Size = System::Drawing::Size(25, 25);
			this->x1y2->TabIndex = 12;
			this->x1y2->TabStop = false;
			this->x1y2->UseVisualStyleBackColor = false;
			this->x1y2->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &GameWindow::MouseDown);
			// 
			// x4y3
			// 
			this->x4y3->BackColor = System::Drawing::Color::Transparent;
			this->x4y3->Cursor = System::Windows::Forms::Cursors::Hand;
			this->x4y3->FlatAppearance->BorderSize = 0;
			this->x4y3->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->x4y3->ImageIndex = 11;
			this->x4y3->ImageList = this->button_imageList25;
			this->x4y3->Location = System::Drawing::Point(100, 75);
			this->x4y3->Margin = System::Windows::Forms::Padding(0);
			this->x4y3->Name = L"x4y3";
			this->x4y3->Size = System::Drawing::Size(25, 25);
			this->x4y3->TabIndex = 20;
			this->x4y3->TabStop = false;
			this->x4y3->UseVisualStyleBackColor = false;
			this->x4y3->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &GameWindow::MouseDown);
			// 
			// x2y0
			// 
			this->x2y0->BackColor = System::Drawing::Color::Transparent;
			this->x2y0->Cursor = System::Windows::Forms::Cursors::Hand;
			this->x2y0->FlatAppearance->BorderSize = 0;
			this->x2y0->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->x2y0->ImageIndex = 11;
			this->x2y0->ImageList = this->button_imageList25;
			this->x2y0->Location = System::Drawing::Point(50, 0);
			this->x2y0->Margin = System::Windows::Forms::Padding(0);
			this->x2y0->Name = L"x2y0";
			this->x2y0->Size = System::Drawing::Size(25, 25);
			this->x2y0->TabIndex = 3;
			this->x2y0->TabStop = false;
			this->x2y0->UseVisualStyleBackColor = false;
			this->x2y0->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &GameWindow::MouseDown);
			// 
			// x2y2
			// 
			this->x2y2->BackColor = System::Drawing::Color::Transparent;
			this->x2y2->Cursor = System::Windows::Forms::Cursors::Hand;
			this->x2y2->FlatAppearance->BorderSize = 0;
			this->x2y2->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->x2y2->ImageIndex = 11;
			this->x2y2->ImageList = this->button_imageList25;
			this->x2y2->Location = System::Drawing::Point(50, 50);
			this->x2y2->Margin = System::Windows::Forms::Padding(0);
			this->x2y2->Name = L"x2y2";
			this->x2y2->Size = System::Drawing::Size(25, 25);
			this->x2y2->TabIndex = 13;
			this->x2y2->TabStop = false;
			this->x2y2->UseVisualStyleBackColor = false;
			this->x2y2->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &GameWindow::MouseDown);
			// 
			// x3y3
			// 
			this->x3y3->BackColor = System::Drawing::Color::Transparent;
			this->x3y3->Cursor = System::Windows::Forms::Cursors::Hand;
			this->x3y3->FlatAppearance->BorderSize = 0;
			this->x3y3->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->x3y3->ImageIndex = 11;
			this->x3y3->ImageList = this->button_imageList25;
			this->x3y3->Location = System::Drawing::Point(75, 75);
			this->x3y3->Margin = System::Windows::Forms::Padding(0);
			this->x3y3->Name = L"x3y3";
			this->x3y3->Size = System::Drawing::Size(25, 25);
			this->x3y3->TabIndex = 19;
			this->x3y3->TabStop = false;
			this->x3y3->UseVisualStyleBackColor = false;
			this->x3y3->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &GameWindow::MouseDown);
			// 
			// x1y0
			// 
			this->x1y0->BackColor = System::Drawing::Color::Transparent;
			this->x1y0->Cursor = System::Windows::Forms::Cursors::Hand;
			this->x1y0->FlatAppearance->BorderSize = 0;
			this->x1y0->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->x1y0->ImageIndex = 11;
			this->x1y0->ImageList = this->button_imageList25;
			this->x1y0->Location = System::Drawing::Point(25, 0);
			this->x1y0->Margin = System::Windows::Forms::Padding(0);
			this->x1y0->Name = L"x1y0";
			this->x1y0->Size = System::Drawing::Size(25, 25);
			this->x1y0->TabIndex = 2;
			this->x1y0->TabStop = false;
			this->x1y0->UseVisualStyleBackColor = false;
			this->x1y0->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &GameWindow::MouseDown);
			// 
			// x3y2
			// 
			this->x3y2->BackColor = System::Drawing::Color::Transparent;
			this->x3y2->Cursor = System::Windows::Forms::Cursors::Hand;
			this->x3y2->FlatAppearance->BorderSize = 0;
			this->x3y2->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->x3y2->ImageIndex = 11;
			this->x3y2->ImageList = this->button_imageList25;
			this->x3y2->Location = System::Drawing::Point(75, 50);
			this->x3y2->Margin = System::Windows::Forms::Padding(0);
			this->x3y2->Name = L"x3y2";
			this->x3y2->Size = System::Drawing::Size(25, 25);
			this->x3y2->TabIndex = 14;
			this->x3y2->TabStop = false;
			this->x3y2->UseVisualStyleBackColor = false;
			this->x3y2->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &GameWindow::MouseDown);
			// 
			// x2y3
			// 
			this->x2y3->BackColor = System::Drawing::Color::Transparent;
			this->x2y3->Cursor = System::Windows::Forms::Cursors::Hand;
			this->x2y3->FlatAppearance->BorderSize = 0;
			this->x2y3->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->x2y3->ImageIndex = 11;
			this->x2y3->ImageList = this->button_imageList25;
			this->x2y3->Location = System::Drawing::Point(50, 75);
			this->x2y3->Margin = System::Windows::Forms::Padding(0);
			this->x2y3->Name = L"x2y3";
			this->x2y3->Size = System::Drawing::Size(25, 25);
			this->x2y3->TabIndex = 18;
			this->x2y3->TabStop = false;
			this->x2y3->UseVisualStyleBackColor = false;
			this->x2y3->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &GameWindow::MouseDown);
			// 
			// x4y2
			// 
			this->x4y2->BackColor = System::Drawing::Color::Transparent;
			this->x4y2->Cursor = System::Windows::Forms::Cursors::Hand;
			this->x4y2->FlatAppearance->BorderSize = 0;
			this->x4y2->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->x4y2->ImageIndex = 11;
			this->x4y2->ImageList = this->button_imageList25;
			this->x4y2->Location = System::Drawing::Point(100, 50);
			this->x4y2->Margin = System::Windows::Forms::Padding(0);
			this->x4y2->Name = L"x4y2";
			this->x4y2->Size = System::Drawing::Size(25, 25);
			this->x4y2->TabIndex = 15;
			this->x4y2->TabStop = false;
			this->x4y2->UseVisualStyleBackColor = false;
			this->x4y2->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &GameWindow::MouseDown);
			// 
			// x0y3
			// 
			this->x0y3->BackColor = System::Drawing::Color::Transparent;
			this->x0y3->Cursor = System::Windows::Forms::Cursors::Hand;
			this->x0y3->FlatAppearance->BorderSize = 0;
			this->x0y3->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->x0y3->ImageIndex = 11;
			this->x0y3->ImageList = this->button_imageList25;
			this->x0y3->Location = System::Drawing::Point(0, 75);
			this->x0y3->Margin = System::Windows::Forms::Padding(0);
			this->x0y3->Name = L"x0y3";
			this->x0y3->Size = System::Drawing::Size(25, 25);
			this->x0y3->TabIndex = 16;
			this->x0y3->TabStop = false;
			this->x0y3->UseVisualStyleBackColor = false;
			this->x0y3->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &GameWindow::MouseDown);
			// 
			// x1y3
			// 
			this->x1y3->BackColor = System::Drawing::Color::Transparent;
			this->x1y3->Cursor = System::Windows::Forms::Cursors::Hand;
			this->x1y3->FlatAppearance->BorderSize = 0;
			this->x1y3->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->x1y3->ImageIndex = 11;
			this->x1y3->ImageList = this->button_imageList25;
			this->x1y3->Location = System::Drawing::Point(25, 75);
			this->x1y3->Margin = System::Windows::Forms::Padding(0);
			this->x1y3->Name = L"x1y3";
			this->x1y3->Size = System::Drawing::Size(25, 25);
			this->x1y3->TabIndex = 17;
			this->x1y3->TabStop = false;
			this->x1y3->UseVisualStyleBackColor = false;
			this->x1y3->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &GameWindow::MouseDown);
			// 
			// GameWindow
			// 
			//this->AutoScaleDimensions = System::Drawing::SizeF(7, 9);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::Color::DarkGray;
			this->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"$this.BackgroundImage")));
			this->ClientSize = System::Drawing::Size(600, 418);
			this->Controls->Add(this->fieldBox);
			this->Controls->Add(this->label_markedCounter);
			this->Controls->Add(this->label_bombCounter);
			this->Controls->Add(this->label_marked);
			this->Controls->Add(this->label_bombs);
			this->Controls->Add(this->btn_close);
			this->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedToolWindow;
			this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
			this->MaximizeBox = false;
			//this->MaximumSize = System::Drawing::Size(1200, 800);
			//this->MinimumSize = System::Drawing::Size(600, 120);
			this->Name = L"GameWindow";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Load += gcnew System::EventHandler(this, &GameWindow::GameWindow_Load);
			this->fieldBox->ResumeLayout(false);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void btn_close_Click(System::Object^ sender, System::EventArgs^ e) {
		this->Close();
	}
	private: System::Void MouseDown(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e) {
		Button^ button = (Button^)sender;
		if (e->Button == System::Windows::Forms::MouseButtons::Right) {
			if (openFieldCounter >= (fieldSize * fieldSize) - bombs) {
				endGame(FieldInfo, true);
				MessageBox::Show(this, "Вы победили!", "", MessageBoxButtons::OK);
			}
			if (button->ImageIndex == 10) {
				button->ImageIndex = 11;
				marked--;
			}
			else if (button->ImageIndex == 11) {
				button->ImageIndex = 10;
				marked++;
			}
			this->label_markedCounter->Text = Convert::ToString(marked);
		}
		else {
			if (button->ImageIndex != 10) {
				String^ name = button->Name;
				if (once) {
					once = false;
					//Разный размер поля зависит от сложности
					if (difficult == 1)fieldSize = 5;
					else if (difficult == 2)fieldSize = 10;
					else if (difficult == 3)fieldSize = 15;
					else if (difficult == 4)fieldSize = 20;
					else if (difficult == 5)fieldSize = 37;
					//Создание поля
					FieldInfo = new short int* [maxfieldSize];
					for (int i = 0; i < maxfieldSize; i++)FieldInfo[i] = new short int[maxfieldSize];
					//Установка значений массива в 0
					for (int y = 0; y < fieldSize; y++)
						for (int x = 0; x < fieldSize; x++) {
							FieldInfo[y][x] = 0;
						}
					//Выключение недействующего поля
					for (int y = 0; y < maxfieldSize; y++)
						for (int x = 0; x < maxfieldSize; x++) {
							if (x >= fieldSize || y >= fieldSize)
							{
								String^ bufname = Convert::ToChar('x') + Convert::ToString(x) + Convert::ToChar('y') + Convert::ToString(y);
								Button^ bufbutton = find(bufname);
								bufbutton->Enabled = false;
							}
						}
					//Заполнение бомбами и цифрами
					String^ buf = "";
					int lasti;
					for (int i = 1; isDigit(name[i]); i++) {
						buf += name[i];
						lasti = i;
					}
					int x = Convert::ToInt16(buf);
					buf = "";
					for (int i = lasti + 2; i < name->Length; i++) {
						buf += name[i];
					}
					int y = Convert::ToInt16(buf);

					createFieldInfo(FieldInfo, x, y);
				}
				String^ buf = "";
				int lasti = 0;
				for (int i = 1; isDigit(name[i]); i++) {
					buf += name[i];
					lasti = i;
				}
				int x = Convert::ToInt16(buf);
				buf = "";
				for (int i = lasti + 2; i < name->Length; i++) {
					buf += name[i];
				}
				int y = Convert::ToInt16(buf);

				if (button->ImageIndex != FieldInfo[y][x]) openFieldCounter++;
				button->ImageIndex = FieldInfo[y][x];
				button->MouseDown -= gcnew System::Windows::Forms::MouseEventHandler(this, &GameWindow::MouseDown);
				if (button->ImageIndex == 9) {
					endGame(FieldInfo, false);
					MessageBox::Show(this, "Вам придётся начать заново", "Вы подорвались на мине!", MessageBoxButtons::OK);
				}
				else if (openFieldCounter >= (fieldSize * fieldSize) - bombs) {
					endGame(FieldInfo, true);
					MessageBox::Show(this, "Вы победили!", "", MessageBoxButtons::OK);
				}
				if (button->ImageIndex == 0) {
					int mainx = x, mainy = y;
					y = mainy - 1; x = mainx - 1;
					name = Convert::ToChar('x') + Convert::ToString(x) + Convert::ToChar('y') + Convert::ToString(y);
					button = find(name);
					if (button != nullptr && button->ImageIndex == 11 && button->Enabled) {
						openFieldCounter++;
						button->ImageIndex = FieldInfo[y][x];
						button->MouseDown -= gcnew System::Windows::Forms::MouseEventHandler(this, &GameWindow::MouseDown);
						if (button->ImageIndex == 0)MouseDown(button, e);
					}
					y = mainy - 1; x = mainx;
					name = Convert::ToChar('x') + Convert::ToString(x) + Convert::ToChar('y') + Convert::ToString(y);
					button = find(name);
					if (button != nullptr && button->ImageIndex == 11 && button->Enabled) {
						openFieldCounter++;
						button->ImageIndex = FieldInfo[y][x];
						button->MouseDown -= gcnew System::Windows::Forms::MouseEventHandler(this, &GameWindow::MouseDown);
						if (button->ImageIndex == 0)MouseDown(button, e);
					}
					y = mainy - 1; x = mainx + 1;
					name = Convert::ToChar('x') + Convert::ToString(x) + Convert::ToChar('y') + Convert::ToString(y);
					button = find(name);
					if (button != nullptr && button->ImageIndex == 11 && button->Enabled) {
						openFieldCounter++;
						button->ImageIndex = FieldInfo[y][x];
						button->MouseDown -= gcnew System::Windows::Forms::MouseEventHandler(this, &GameWindow::MouseDown);
						if (button->ImageIndex == 0)MouseDown(button, e);
					}
					y = mainy; x = mainx - 1;
					name = Convert::ToChar('x') + Convert::ToString(x) + Convert::ToChar('y') + Convert::ToString(y);
					button = find(name);
					if (button != nullptr && button->ImageIndex == 11 && button->Enabled) {
						openFieldCounter++;
						button->ImageIndex = FieldInfo[y][x];
						button->MouseDown -= gcnew System::Windows::Forms::MouseEventHandler(this, &GameWindow::MouseDown);
						if (button->ImageIndex == 0)MouseDown(button, e);
					}
					y = mainy; x = mainx + 1;
					name = Convert::ToChar('x') + Convert::ToString(x) + Convert::ToChar('y') + Convert::ToString(y);
					button = find(name);
					if (button != nullptr && button->ImageIndex == 11 && button->Enabled) {
						openFieldCounter++;
						button->ImageIndex = FieldInfo[y][x];
						button->MouseDown -= gcnew System::Windows::Forms::MouseEventHandler(this, &GameWindow::MouseDown);
						if (button->ImageIndex == 0)MouseDown(button, e);
					}
					y = mainy + 1; x = mainx - 1;
					name = Convert::ToChar('x') + Convert::ToString(x) + Convert::ToChar('y') + Convert::ToString(y);
					button = find(name);
					if (button != nullptr && button->ImageIndex == 11 && button->Enabled) {
						openFieldCounter++;
						button->ImageIndex = FieldInfo[y][x];
						button->MouseDown -= gcnew System::Windows::Forms::MouseEventHandler(this, &GameWindow::MouseDown);
						if (button->ImageIndex == 0)MouseDown(button, e);
					}
					y = mainy + 1; x = mainx;
					name = Convert::ToChar('x') + Convert::ToString(x) + Convert::ToChar('y') + Convert::ToString(y);
					button = find(name);
					if (button != nullptr && button->ImageIndex == 11 && button->Enabled) {
						openFieldCounter++;
						button->ImageIndex = FieldInfo[y][x];
						button->MouseDown -= gcnew System::Windows::Forms::MouseEventHandler(this, &GameWindow::MouseDown);
						if (button->ImageIndex == 0)MouseDown(button, e);
					}
					y = mainy + 1; x = mainx + 1;
					name = Convert::ToChar('x') + Convert::ToString(x) + Convert::ToChar('y') + Convert::ToString(y);
					button = find(name);
					if (button != nullptr && button->ImageIndex == 11 && button->Enabled) {
						openFieldCounter++;
						button->ImageIndex = FieldInfo[y][x];
						button->MouseDown -= gcnew System::Windows::Forms::MouseEventHandler(this, &GameWindow::MouseDown);
						if (button->ImageIndex == 0)MouseDown(button, e);
					}
				}
			}
		}
	}
	private: System::Void GameWindow_Load(System::Object^ sender, System::EventArgs^ e) {
		//Разное количество мин зависит от сложности
		if (difficult == 1)bombs = 5;
		else if (difficult == 2)bombs = 20;
		else if (difficult == 3)bombs = 45;
		else if (difficult == 4)bombs = 80;
		else if (difficult == 5)bombs = 275;
		this->label_bombCounter->Text = Convert::ToString(bombs);
	}
	};
}