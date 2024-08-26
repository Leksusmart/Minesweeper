#pragma once
#include "GameWindow.h";
namespace Сапёр2 {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	
	/*
	Сложно
	Экстрим
	Безумие
	*/
	/// <summary>
	/// Сводка для WelcomeWindow
	/// </summary>
	public ref class WelcomeWindow : public System::Windows::Forms::Form
	{
	public:
		WelcomeWindow(void)
		{
			InitializeComponent();
			//
			//TODO: добавьте код конструктора
			//
		}
	protected:
		/// <summary>
		/// Освободить все используемые ресурсы.
		/// </summary>
		~WelcomeWindow()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::ComboBox^ chooseDifficult;
	private: System::Windows::Forms::Label^ label_difficult;
	private: System::Windows::Forms::Label^ label_gamename;
	private: System::Windows::Forms::Label^ label_Welcome;
	private: System::Windows::Forms::Button^ btn_Welcome_start;
	private: System::Windows::Forms::Button^ button1;
	private: 
		   /// <summary>
		   /// Обязательная переменная конструктора.
		   /// </summary>
		   System::ComponentModel::Container^ components;

#pragma region Windows Form Designer generated code
		   /// <summary>
		   /// Требуемый метод для поддержки конструктора — не изменяйте 
		   /// содержимое этого метода с помощью редактора кода.
		   /// </summary>
		   void InitializeComponent(void)
		   {
			   System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(WelcomeWindow::typeid));
			   this->chooseDifficult = (gcnew System::Windows::Forms::ComboBox());
			   this->label_difficult = (gcnew System::Windows::Forms::Label());
			   this->label_gamename = (gcnew System::Windows::Forms::Label());
			   this->label_Welcome = (gcnew System::Windows::Forms::Label());
			   this->btn_Welcome_start = (gcnew System::Windows::Forms::Button());
			   this->button1 = (gcnew System::Windows::Forms::Button());
			   this->SuspendLayout();
			   // 
			   // chooseDifficult
			   // 
			   this->chooseDifficult->BackColor = System::Drawing::Color::Silver;
			   this->chooseDifficult->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			   this->chooseDifficult->FlatStyle = System::Windows::Forms::FlatStyle::Popup;
			   this->chooseDifficult->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 13.875F, System::Drawing::FontStyle::Regular,
				   System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(204)));
			   this->chooseDifficult->FormattingEnabled = true;
			   this->chooseDifficult->Items->AddRange(gcnew cli::array< System::Object^  >(2) { L"Легко", L"Средне" });
			   this->chooseDifficult->Location = System::Drawing::Point(64, 163);
			   this->chooseDifficult->Margin = System::Windows::Forms::Padding(2);
			   this->chooseDifficult->Name = L"chooseDifficult";
			   this->chooseDifficult->Size = System::Drawing::Size(204, 50);
			   this->chooseDifficult->TabIndex = 3;
			   this->chooseDifficult->SelectionChangeCommitted += gcnew System::EventHandler(this, &WelcomeWindow::comboBox1_SelectionChangeCommitted);
			   // 
			   // label_difficult
			   // 
			   this->label_difficult->BackColor = System::Drawing::Color::Transparent;
			   this->label_difficult->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.875F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				   static_cast<System::Byte>(204)));
			   this->label_difficult->Location = System::Drawing::Point(66, 164);
			   this->label_difficult->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			   this->label_difficult->Name = L"label_difficult";
			   this->label_difficult->Size = System::Drawing::Size(182, 27);
			   this->label_difficult->TabIndex = 4;
			   this->label_difficult->Text = L"Выберите сложность:";
			   this->label_difficult->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			   // 
			   // label_gamename
			   // 
			   this->label_gamename->BackColor = System::Drawing::Color::Transparent;
			   this->label_gamename->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 36, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				   static_cast<System::Byte>(204)));
			   this->label_gamename->Location = System::Drawing::Point(6, 20);
			   this->label_gamename->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			   this->label_gamename->Name = L"label_gamename";
			   this->label_gamename->Size = System::Drawing::Size(322, 59);
			   this->label_gamename->TabIndex = 5;
			   this->label_gamename->Text = L"Minesweeper";
			   this->label_gamename->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			   // 
			   // label_Welcome
			   // 
			   this->label_Welcome->BackColor = System::Drawing::Color::Transparent;
			   this->label_Welcome->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 24, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				   static_cast<System::Byte>(204)));
			   this->label_Welcome->Location = System::Drawing::Point(9, 95);
			   this->label_Welcome->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			   this->label_Welcome->Name = L"label_Welcome";
			   this->label_Welcome->Size = System::Drawing::Size(310, 38);
			   this->label_Welcome->TabIndex = 0;
			   this->label_Welcome->Text = L"Добро пожаловать!";
			   this->label_Welcome->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			   // 
			   // btn_Welcome_start
			   // 
			   this->btn_Welcome_start->BackColor = System::Drawing::Color::DarkSeaGreen;
			   this->btn_Welcome_start->Cursor = System::Windows::Forms::Cursors::Default;
			   this->btn_Welcome_start->Enabled = false;
			   this->btn_Welcome_start->FlatStyle = System::Windows::Forms::FlatStyle::Popup;
			   this->btn_Welcome_start->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				   static_cast<System::Byte>(204)));
			   this->btn_Welcome_start->Location = System::Drawing::Point(62, 366);
			   this->btn_Welcome_start->Margin = System::Windows::Forms::Padding(2);
			   this->btn_Welcome_start->Name = L"btn_Welcome_start";
			   this->btn_Welcome_start->Size = System::Drawing::Size(202, 67);
			   this->btn_Welcome_start->TabIndex = 1;
			   this->btn_Welcome_start->Text = L"Играть";
			   this->btn_Welcome_start->UseVisualStyleBackColor = false;
			   this->btn_Welcome_start->Click += gcnew System::EventHandler(this, &WelcomeWindow::btn_Welcome_start_Click);
			   // 
			   // button1
			   // 
			   this->button1->BackColor = System::Drawing::Color::Red;
			   this->button1->FlatStyle = System::Windows::Forms::FlatStyle::Popup;
			   this->button1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 16.125F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				   static_cast<System::Byte>(204)));
			   this->button1->ForeColor = System::Drawing::SystemColors::Control;
			   this->button1->Location = System::Drawing::Point(113, 464);
			   this->button1->Margin = System::Windows::Forms::Padding(2);
			   this->button1->Name = L"button1";
			   this->button1->Size = System::Drawing::Size(98, 34);
			   this->button1->TabIndex = 2;
			   this->button1->Text = L"Выйти";
			   this->button1->UseVisualStyleBackColor = false;
			   this->button1->Click += gcnew System::EventHandler(this, &WelcomeWindow::button1_Click);
			   // 
			   // WelcomeWindow
			   // 
			   this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			   this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			   this->BackColor = System::Drawing::SystemColors::ControlDarkDark;
			   this->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"$this.BackgroundImage")));
			   this->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			   this->ClientSize = System::Drawing::Size(325, 520);
			   this->Controls->Add(this->label_gamename);
			   this->Controls->Add(this->label_difficult);
			   this->Controls->Add(this->chooseDifficult);
			   this->Controls->Add(this->button1);
			   this->Controls->Add(this->btn_Welcome_start);
			   this->Controls->Add(this->label_Welcome);
			   this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::None;
			   this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
			   this->Margin = System::Windows::Forms::Padding(2);
			   this->MaximumSize = System::Drawing::Size(325, 520);
			   this->MinimumSize = System::Drawing::Size(325, 520);
			   this->Name = L"WelcomeWindow";
			   this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			   this->Text = L"WelcomeWindow";
			   this->ResumeLayout(false);

		   }
#pragma endregion
	private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e) {
		Close();
	}
	private: System::Void btn_Welcome_start_Click(System::Object^ sender, System::EventArgs^ e)
	{
		if (label_difficult->Visible == false) {
			GameWindow^ Game = gcnew GameWindow;
			once = true;
			if (chooseDifficult->Text == "Легко") {
				difficult = 1;
				Game->fieldBox->Location = Point(225 + 12, 200 - 12);
				Game->fieldBox->Width = 125 + 1;
				Game->fieldBox->Height = 125 + 1;
			}
			if (chooseDifficult->Text == "Средне") {
				difficult = 2;
				Game->fieldBox->Location = Point(175, 150);
				Game->fieldBox->Width = 250 + 1;
				Game->fieldBox->Height = 250 + 1;
				Game->btn_close->Location = Point(225, 10);
			}
			if (chooseDifficult->Text == "Сложно") {
				difficult = 3;

			}
			if (chooseDifficult->Text == "Экстрим") {
				difficult = 4;

			}
			if (chooseDifficult->Text == "Безумие") {
				difficult = 5;

			}
			Game->marked = 0;
			this->Hide();
			Game->ShowDialog();
			this->Show();
		}
	}
	private: System::Void comboBox1_SelectionChangeCommitted(System::Object^ sender, System::EventArgs^ e) {
		label_difficult->Hide();
		btn_Welcome_start->BackColor = Color::LightGreen;
		btn_Welcome_start->Enabled = true;
	}
	};
}