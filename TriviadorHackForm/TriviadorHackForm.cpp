#include "pch.h"

using namespace System;
using namespace System::Windows::Forms;

int main(array<System::String ^> ^args)
{
    Application::EnableVisualStyles();
    Application::SetCompatibleTextRenderingDefault(false);
    TriviadorHackForm::TriviadorHackV1 main_form;
    main_form.Show();
    //main_form.WindowState = FormWindowState::Normal;
    //main_form.BringToFront();
    //main_form.Activate();
    //main_form.TopLevel = true;
    main_form.TopMost = true;
    //main_form.Focus();
    //main_form.Scale(1, 1);
    main_form.AutoScaleMode = AutoScaleMode::Font;
    main_form.Font = gcnew System::Drawing::Font("Verdana", 9.75 * sameRatioCoef * getResizeOtherResolutionCoef());
    getResizeOtherResolutionCoef();

    Application::Run(%main_form);

    return 0;
}
