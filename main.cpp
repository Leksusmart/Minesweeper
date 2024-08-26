#include "WelcomeWindow.h"
#include "GameWindow.h"
#include <Windows.h>
static bool buf = FreeConsole();//Закрываем консоль, чтобы не мешала

using namespace System;
using namespace System::Windows::Forms;

[STAThreadAttribute]//main будет запускаться в отдельном потоке данных
int main(array<String^>^ args) {
	srand(time(NULL));
	Application::SetCompatibleTextRenderingDefault(false);//Необходима для коректрой обработки текста
	Application::EnableVisualStyles();//Подключаем различные визуальные стили
		
	Сапёр2::WelcomeWindow Welcomeform;
	Application::Run(% Welcomeform);
}