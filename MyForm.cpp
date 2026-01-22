#include "MyForm.h"

using namespace System;
using namespace System::Windows::Forms;

int main() {
	Application::SetCompatibleTextRenderingDefault(false);
	Application::EnableVisualStyles();
	TourAgency::MyForm form;
	Application::Run(% form);

}