#include "WelcomeWindow.h"
#include "GameWindow.h"
#include <Windows.h>
static bool buf = FreeConsole();//��������� �������, ����� �� ������

using namespace System;
using namespace System::Windows::Forms;

[STAThreadAttribute]//main ����� ����������� � ��������� ������ ������
int main(array<String^>^ args) {
	srand(time(NULL));
	Application::SetCompatibleTextRenderingDefault(false);//���������� ��� ��������� ��������� ������
	Application::EnableVisualStyles();//���������� ��������� ���������� �����
		
	����2::WelcomeWindow Welcomeform;
	Application::Run(% Welcomeform);
}