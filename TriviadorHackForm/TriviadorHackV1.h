#pragma once
#include "Wrapper.h"
#include <codecvt> // wstring read from file encoding
#include "AdditionalDependencies.h"
//#include "processthreadsapi.h"

#include <msclr/marshal.h>            // marshalling -> converting from String^ to
#include <msclr/marshal_cppstd.h>       // std::basic_string for richTextBox1 writing
using namespace msclr::interop;

using namespace System::IO; // console output 

namespace TriviadorHackForm {

	//using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Threading; // threads
	using namespace System::Diagnostics; // console output

	/// <summary>
	/// Summary for TriviadorHackV1
	/// </summary>
	public ref class TriviadorHackV1 : public System::Windows::Forms::Form
	{
	public:
		TriviadorHackV1(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~TriviadorHackV1()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^ button1;
	private: System::Windows::Forms::Label^ label1;

	private: System::Windows::Forms::RichTextBox^ richTextBox1;
	private: System::Windows::Forms::TabControl^ tabControl1;




	private: System::Windows::Forms::TabPage^ tabPage1;
	private: System::Windows::Forms::TabPage^ tabPage2;
	private: System::Windows::Forms::Button^ button3;
	private: System::Windows::Forms::RichTextBox^ richTextBox2;
	private: System::Windows::Forms::RichTextBox^ richTextBox3;
	private: System::Windows::Forms::PictureBox^ pictureBox1;
	private: System::Windows::Forms::TabPage^ tabPage3;
	private: System::Windows::Forms::Button^ button4;
	private: System::Windows::Forms::PictureBox^ pictureBox2;
	private: System::Windows::Forms::PictureBox^ pictureBox3;
	private: System::Windows::Forms::Button^ button13;
	private: System::Windows::Forms::Button^ button12;
	private: System::Windows::Forms::Button^ button11;
	private: System::Windows::Forms::Button^ button10;
	private: System::Windows::Forms::Button^ button9;
	private: System::Windows::Forms::Button^ button8;
	private: System::Windows::Forms::Button^ button7;
	private: System::Windows::Forms::Button^ button6;
	private: System::Windows::Forms::Button^ button5;

	private: System::Windows::Forms::Button^ button23;
	private: System::Windows::Forms::Button^ button22;
	private: System::Windows::Forms::Button^ button21;
	private: System::Windows::Forms::Button^ button20;
	private: System::Windows::Forms::Button^ button19;
	private: System::Windows::Forms::Button^ button18;
	private: System::Windows::Forms::Button^ button17;
	private: System::Windows::Forms::Button^ button16;
	private: System::Windows::Forms::Button^ button15;
	private: System::Windows::Forms::Button^ button14;
	private: System::Windows::Forms::TabPage^ tabPage4;
	private: System::Windows::Forms::Label^ label3;
	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::Label^ label4;
	private: System::Windows::Forms::CheckBox^ checkBox5;
	private: System::Windows::Forms::CheckBox^ checkBox4;
	private: System::Windows::Forms::CheckBox^ checkBox3;
	private: System::Windows::Forms::CheckBox^ checkBox2;
	private: System::Windows::Forms::CheckBox^ checkBox1;
	private: System::Windows::Forms::CheckBox^ checkBox10;
	private: System::Windows::Forms::CheckBox^ checkBox9;
	private: System::Windows::Forms::CheckBox^ checkBox8;
	private: System::Windows::Forms::CheckBox^ checkBox7;
	private: System::Windows::Forms::CheckBox^ checkBox6;
	private: System::Windows::Forms::Label^ label5;
	private: System::Windows::Forms::Label^ label6;
	private: System::Windows::Forms::Label^ label7;
	private: System::Windows::Forms::Label^ label8;
	private: System::Windows::Forms::Button^ button25;
	private: System::Windows::Forms::Button^ button24;
	private: System::Windows::Forms::Label^ label9;
	private: System::Windows::Forms::Label^ label10;
	private: System::Windows::Forms::Button^ button2;
	protected:
		void ThreadProc()
		{
			try
			{
				Wrapper wr;	

				Thread^ readLogThread = gcnew Thread(gcnew ThreadStart(this, &TriviadorHackV1::ReadOutput));
				readLogThread->IsBackground = true;
				readLogThread->Start();

				pin_ptr<bool> boolRef = &goOn;
				wr.triviadorHack(*boolRef);
				if (readLogThread->ThreadState != System::Threading::ThreadState::Unstarted) {
					readLogThread->Join();
				}

			}
			catch (ThreadAbortException^ e)
			{
				Thread::ResetAbort();
			}
		}
		delegate void SetTextCallback(System::String^ sstr);
		void setText(System::String^ sstr) {
			if (richTextBox1->InvokeRequired) {
				SetTextCallback^ d = gcnew SetTextCallback(this, &TriviadorHackV1::setText);
				this->Invoke(d, sstr);
			}
			else {
				richTextBox1->Text += sstr;

				richTextBox1->Invalidate();
				richTextBox1->Update();
				richTextBox1->SelectionStart = richTextBox1->Text->Length;
				// scroll it automatically
				richTextBox1->ScrollToCaret();
			}
		}
		void ReadOutput() {
			std::wifstream readLog;

			readLog.imbue(std::locale(std::locale::empty(), new std::codecvt_utf8<wchar_t>));
			readLog.open(log_filename, std::ios::in);
			if (!readLog) {
				label1->Text = "Could not open log!";
			}

			readLog.seekg(0, std::ios::end);
			std::wstring str;

			while (goOn) {

				getline(readLog, str);
				readLog.clear();

				if (str != L"") {
					str += L"\n";
					setText(gcnew System::String(str.c_str()));
				}
				sleep_until(system_clock::now() + milliseconds(100));
			}
		}
		int coordInd = -1;
		void setPictureBox(PictureBox^ picBox, const char* filename) {
			Stream^ imageStreamSource = gcnew FileStream(gcnew System::String(std::string(filename).c_str()), FileMode::Open, FileAccess::Read, FileShare::Read);
			picBox->SizeMode = PictureBoxSizeMode::Zoom;
			picBox->Image = System::Drawing::Image::FromStream(imageStreamSource);
			imageStreamSource->Close();
		}
		void setChangeAnchorQuestionAnswerButton(int coordIndex) {

			label10->Text = L"Изчакай за да въведеш!";
			coordInd = coordIndex;
			Thread^ setCoordAnchorThread = gcnew Thread(gcnew ThreadStart(this, &TriviadorHackV1::setCoordAnchor));
			setCoordAnchorThread->IsBackground = true;
			setCoordAnchorThread->Start();
		}
		void setGuideImages(PictureBox^ picBox, const char* filename, PictureBox^ picBox2, const char* filename2) {
			setPictureBox(picBox, filename);
			setPictureBox(picBox2, filename2);
		}
		void setCoordAnchor() {
			int x, y;
			Wrapper wr;
			
			wr.mouseButtonPressed(x, y);

			label10->Text = L"Може да въвеждаш.";
			Coordinates newCoord;
			bool leftClickOnce = false, leftClickTwice = false;

			while (!leftClickTwice) {
				if (!leftClickOnce) {
					if (wr.mouseButtonPressed(newCoord.x, newCoord.y)) {
						leftClickOnce = true;
					}
				}
				else if (wr.mouseButtonPressed(newCoord.width, newCoord.height)) {
					newCoord.width = abs(newCoord.width - newCoord.x);
					newCoord.height = abs(newCoord.height - newCoord.y);
					leftClickTwice = true;
				}
			}
			//cout << newCoord.x << " " << newCoord.y << " " << newCoord.width << " " << newCoord.height << endl;
			//cout << sameRatioCoef << " " << diffRatioCoef << endl;

			newCoord.x *= diffRatioCoef;
			newCoord.y *= diffRatioCoef;
			newCoord.width *= diffRatioCoef;
			newCoord.height *= diffRatioCoef;

			switch (coordInd) {
			case questionCoordInd: wr.changeAnchorQuestionAnswer(newCoord, buff_filename, coordInd); break;
			case answerCoordInd: wr.changeAnchorQuestionAnswer(newCoord, buff_filename, coordInd); break;
			case AnchorHintInd: wr.changeAnchorQuestionAnswer(newCoord, anchorHint_filename, coordInd); break;
			case AnchorHintUsedInd: wr.changeAnchorQuestionAnswer(newCoord, anchorHintUsed_filename, coordInd); break;
			case AnchorTargetCoordInd: wr.changeAnchorQuestionAnswer(newCoord, anchorTarget_filename, coordInd); break;
			case anchorHintSecondCoordInd: wr.changeAnchorQuestionAnswer(newCoord, anchorHintSecond_filename, coordInd); break;
			case anchorHintUsedSecondCoordInd: wr.changeAnchorQuestionAnswer(newCoord, anchorHintUsedSecond_filename, coordInd); break;
			case anchorLikeQuestionCoordInd: wr.changeAnchorQuestionAnswer(newCoord, anchorLikeQuestion_filename, coordInd); break;
			case answersQuestionSecondInd: wr.changeAnchorQuestionAnswer(newCoord, buff_filename, coordInd); break;
			case answerFirstQuestionSecondInd: wr.changeAnchorQuestionAnswer(newCoord, buff_filename, coordInd); break;
			default:;
			}

			setPictureBox(pictureBox1, "./tessinput.png");

			label10->Text = L"Кликни изън бутоните за да откриеш цялата фунцкионалност.\\nКликни на подсказка за да видиш какво трябва да въведеш.\\nКликни на съседните бутони за въвеждане.";
		}
		bool isResized = false;
		void resizeForm(bool toResize) {
			//TriviadorHackV1::Size = System::Drawing::Size(width * sameRatioCoef, height * sameRatioCoef);
			if (toResize && !isResized) {
				TriviadorHackV1::Size = System::Drawing::Size(resizeCoef * TriviadorHackV1::Size.Width, TriviadorHackV1::Size.Height);
				isResized = true;
			}
			else if (!toResize && isResized) {
				TriviadorHackV1::Size = System::Drawing::Size(TriviadorHackV1::Size.Width / resizeCoef, TriviadorHackV1::Size.Height);
				isResized = false;
			}
			TriviadorHackV1::Invalidate();
			TriviadorHackV1::Update();

		}
	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(TriviadorHackV1::typeid));
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->richTextBox1 = (gcnew System::Windows::Forms::RichTextBox());
			this->tabControl1 = (gcnew System::Windows::Forms::TabControl());
			this->tabPage1 = (gcnew System::Windows::Forms::TabPage());
			this->tabPage2 = (gcnew System::Windows::Forms::TabPage());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->richTextBox3 = (gcnew System::Windows::Forms::RichTextBox());
			this->button3 = (gcnew System::Windows::Forms::Button());
			this->richTextBox2 = (gcnew System::Windows::Forms::RichTextBox());
			this->tabPage3 = (gcnew System::Windows::Forms::TabPage());
			this->label10 = (gcnew System::Windows::Forms::Label());
			this->checkBox10 = (gcnew System::Windows::Forms::CheckBox());
			this->checkBox9 = (gcnew System::Windows::Forms::CheckBox());
			this->checkBox8 = (gcnew System::Windows::Forms::CheckBox());
			this->checkBox7 = (gcnew System::Windows::Forms::CheckBox());
			this->checkBox6 = (gcnew System::Windows::Forms::CheckBox());
			this->checkBox5 = (gcnew System::Windows::Forms::CheckBox());
			this->checkBox4 = (gcnew System::Windows::Forms::CheckBox());
			this->checkBox3 = (gcnew System::Windows::Forms::CheckBox());
			this->checkBox2 = (gcnew System::Windows::Forms::CheckBox());
			this->checkBox1 = (gcnew System::Windows::Forms::CheckBox());
			this->button23 = (gcnew System::Windows::Forms::Button());
			this->button22 = (gcnew System::Windows::Forms::Button());
			this->button21 = (gcnew System::Windows::Forms::Button());
			this->button20 = (gcnew System::Windows::Forms::Button());
			this->button19 = (gcnew System::Windows::Forms::Button());
			this->button18 = (gcnew System::Windows::Forms::Button());
			this->button17 = (gcnew System::Windows::Forms::Button());
			this->button16 = (gcnew System::Windows::Forms::Button());
			this->button15 = (gcnew System::Windows::Forms::Button());
			this->button14 = (gcnew System::Windows::Forms::Button());
			this->button13 = (gcnew System::Windows::Forms::Button());
			this->button12 = (gcnew System::Windows::Forms::Button());
			this->button11 = (gcnew System::Windows::Forms::Button());
			this->button10 = (gcnew System::Windows::Forms::Button());
			this->button9 = (gcnew System::Windows::Forms::Button());
			this->button8 = (gcnew System::Windows::Forms::Button());
			this->button7 = (gcnew System::Windows::Forms::Button());
			this->button6 = (gcnew System::Windows::Forms::Button());
			this->button5 = (gcnew System::Windows::Forms::Button());
			this->button4 = (gcnew System::Windows::Forms::Button());
			this->tabPage4 = (gcnew System::Windows::Forms::TabPage());
			this->label9 = (gcnew System::Windows::Forms::Label());
			this->label8 = (gcnew System::Windows::Forms::Label());
			this->button25 = (gcnew System::Windows::Forms::Button());
			this->button24 = (gcnew System::Windows::Forms::Button());
			this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox2 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox3 = (gcnew System::Windows::Forms::PictureBox());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->label6 = (gcnew System::Windows::Forms::Label());
			this->label7 = (gcnew System::Windows::Forms::Label());
			this->tabControl1->SuspendLayout();
			this->tabPage1->SuspendLayout();
			this->tabPage2->SuspendLayout();
			this->tabPage3->SuspendLayout();
			this->tabPage4->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox2))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox3))->BeginInit();
			this->SuspendLayout();
			// 
			// button1
			// 
			this->button1->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(34)), static_cast<System::Int32>(static_cast<System::Byte>(34)),
				static_cast<System::Int32>(static_cast<System::Byte>(34)));
			this->button1->Location = System::Drawing::Point(25, 11);
			this->button1->Margin = System::Windows::Forms::Padding(1, 2, 1, 2);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(97, 59);
			this->button1->TabIndex = 0;
			this->button1->Text = L"СТАРТ/\r\nСТОП";
			this->button1->UseVisualStyleBackColor = false;
			this->button1->Click += gcnew System::EventHandler(this, &TriviadorHackV1::button1_Click);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->ForeColor = System::Drawing::Color::OrangeRed;
			this->label1->Location = System::Drawing::Point(135, 33);
			this->label1->Margin = System::Windows::Forms::Padding(1, 0, 1, 0);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(334, 20);
			this->label1->TabIndex = 1;
			this->label1->Text = L"Натисни \"СТАРТ\" за да пуснеш хака!";
			this->label1->Click += gcnew System::EventHandler(this, &TriviadorHackV1::label1_Click);
			// 
			// button2
			// 
			this->button2->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(34)), static_cast<System::Int32>(static_cast<System::Byte>(34)),
				static_cast<System::Int32>(static_cast<System::Byte>(34)));
			this->button2->Location = System::Drawing::Point(425, 208);
			this->button2->Margin = System::Windows::Forms::Padding(1, 2, 1, 2);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(97, 48);
			this->button2->TabIndex = 2;
			this->button2->Tag = L"";
			this->button2->Text = L"Грешен отговор!";
			this->button2->UseVisualStyleBackColor = false;
			this->button2->Click += gcnew System::EventHandler(this, &TriviadorHackV1::button2_Click);
			// 
			// richTextBox1
			// 
			this->richTextBox1->BackColor = System::Drawing::SystemColors::Desktop;
			this->richTextBox1->ForeColor = System::Drawing::Color::OrangeRed;
			this->richTextBox1->Location = System::Drawing::Point(25, 74);
			this->richTextBox1->Margin = System::Windows::Forms::Padding(1, 2, 1, 2);
			this->richTextBox1->Name = L"richTextBox1";
			this->richTextBox1->Size = System::Drawing::Size(381, 182);
			this->richTextBox1->TabIndex = 4;
			this->richTextBox1->Text = L"";
			this->richTextBox1->TextChanged += gcnew System::EventHandler(this, &TriviadorHackV1::richTextBox1_TextChanged);
			// 
			// tabControl1
			// 
			this->tabControl1->Appearance = System::Windows::Forms::TabAppearance::FlatButtons;
			this->tabControl1->Controls->Add(this->tabPage1);
			this->tabControl1->Controls->Add(this->tabPage2);
			this->tabControl1->Controls->Add(this->tabPage3);
			this->tabControl1->Controls->Add(this->tabPage4);
			this->tabControl1->Location = System::Drawing::Point(1, 2);
			this->tabControl1->Margin = System::Windows::Forms::Padding(1, 2, 1, 2);
			this->tabControl1->Name = L"tabControl1";
			this->tabControl1->SelectedIndex = 0;
			this->tabControl1->Size = System::Drawing::Size(531, 304);
			this->tabControl1->TabIndex = 5;
			// 
			// tabPage1
			// 
			this->tabPage1->BackColor = System::Drawing::SystemColors::MenuText;
			this->tabPage1->Controls->Add(this->button2);
			this->tabPage1->Controls->Add(this->button1);
			this->tabPage1->Controls->Add(this->richTextBox1);
			this->tabPage1->Controls->Add(this->label1);
			this->tabPage1->Location = System::Drawing::Point(4, 30);
			this->tabPage1->Margin = System::Windows::Forms::Padding(1, 2, 1, 2);
			this->tabPage1->Name = L"tabPage1";
			this->tabPage1->Padding = System::Windows::Forms::Padding(1, 2, 1, 2);
			this->tabPage1->Size = System::Drawing::Size(523, 270);
			this->tabPage1->TabIndex = 0;
			this->tabPage1->Text = L"Хак";
			this->tabPage1->Click += gcnew System::EventHandler(this, &TriviadorHackV1::HackTest_Click);
			// 
			// tabPage2
			// 
			this->tabPage2->BackColor = System::Drawing::Color::Black;
			this->tabPage2->Controls->Add(this->label4);
			this->tabPage2->Controls->Add(this->label3);
			this->tabPage2->Controls->Add(this->label2);
			this->tabPage2->Controls->Add(this->richTextBox3);
			this->tabPage2->Controls->Add(this->button3);
			this->tabPage2->Controls->Add(this->richTextBox2);
			this->tabPage2->Location = System::Drawing::Point(4, 30);
			this->tabPage2->Margin = System::Windows::Forms::Padding(1, 2, 1, 2);
			this->tabPage2->Name = L"tabPage2";
			this->tabPage2->Padding = System::Windows::Forms::Padding(1, 2, 1, 2);
			this->tabPage2->Size = System::Drawing::Size(523, 270);
			this->tabPage2->TabIndex = 1;
			this->tabPage2->Text = L"Промени въпрос";
			this->tabPage2->Click += gcnew System::EventHandler(this, &TriviadorHackV1::tabPage2_Click);
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Location = System::Drawing::Point(137, 236);
			this->label4->Margin = System::Windows::Forms::Padding(1, 0, 1, 0);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(0, 20);
			this->label4->TabIndex = 5;
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(25, 130);
			this->label3->Margin = System::Windows::Forms::Padding(1, 0, 1, 0);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(383, 40);
			this->label3->TabIndex = 4;
			this->label3->Text = L"Въведи отговор\r\n(остави празно за изтриване на въпроса):";
			this->label3->Click += gcnew System::EventHandler(this, &TriviadorHackV1::label3_Click);
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(25, 18);
			this->label2->Margin = System::Windows::Forms::Padding(1, 0, 1, 0);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(150, 20);
			this->label2->TabIndex = 3;
			this->label2->Text = L"Въведи въпрос:";
			// 
			// richTextBox3
			// 
			this->richTextBox3->BackColor = System::Drawing::Color::Black;
			this->richTextBox3->ForeColor = System::Drawing::Color::OrangeRed;
			this->richTextBox3->Location = System::Drawing::Point(32, 171);
			this->richTextBox3->Margin = System::Windows::Forms::Padding(1, 2, 1, 2);
			this->richTextBox3->Name = L"richTextBox3";
			this->richTextBox3->Size = System::Drawing::Size(301, 41);
			this->richTextBox3->TabIndex = 2;
			this->richTextBox3->Text = L"";
			// 
			// button3
			// 
			this->button3->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(34)), static_cast<System::Int32>(static_cast<System::Byte>(34)),
				static_cast<System::Int32>(static_cast<System::Byte>(34)));
			this->button3->Location = System::Drawing::Point(32, 219);
			this->button3->Margin = System::Windows::Forms::Padding(1, 2, 1, 2);
			this->button3->Name = L"button3";
			this->button3->Size = System::Drawing::Size(97, 49);
			this->button3->TabIndex = 1;
			this->button3->Text = L"Промени въпроса";
			this->button3->UseVisualStyleBackColor = false;
			this->button3->Click += gcnew System::EventHandler(this, &TriviadorHackV1::button3_Click);
			// 
			// richTextBox2
			// 
			this->richTextBox2->BackColor = System::Drawing::Color::Black;
			this->richTextBox2->ForeColor = System::Drawing::Color::OrangeRed;
			this->richTextBox2->Location = System::Drawing::Point(32, 34);
			this->richTextBox2->Margin = System::Windows::Forms::Padding(1, 2, 1, 2);
			this->richTextBox2->Name = L"richTextBox2";
			this->richTextBox2->Size = System::Drawing::Size(301, 95);
			this->richTextBox2->TabIndex = 0;
			this->richTextBox2->Text = L"";
			// 
			// tabPage3
			// 
			this->tabPage3->BackColor = System::Drawing::Color::Black;
			this->tabPage3->Controls->Add(this->label10);
			this->tabPage3->Controls->Add(this->checkBox10);
			this->tabPage3->Controls->Add(this->checkBox9);
			this->tabPage3->Controls->Add(this->checkBox8);
			this->tabPage3->Controls->Add(this->checkBox7);
			this->tabPage3->Controls->Add(this->checkBox6);
			this->tabPage3->Controls->Add(this->checkBox5);
			this->tabPage3->Controls->Add(this->checkBox4);
			this->tabPage3->Controls->Add(this->checkBox3);
			this->tabPage3->Controls->Add(this->checkBox2);
			this->tabPage3->Controls->Add(this->checkBox1);
			this->tabPage3->Controls->Add(this->button23);
			this->tabPage3->Controls->Add(this->button22);
			this->tabPage3->Controls->Add(this->button21);
			this->tabPage3->Controls->Add(this->button20);
			this->tabPage3->Controls->Add(this->button19);
			this->tabPage3->Controls->Add(this->button18);
			this->tabPage3->Controls->Add(this->button17);
			this->tabPage3->Controls->Add(this->button16);
			this->tabPage3->Controls->Add(this->button15);
			this->tabPage3->Controls->Add(this->button14);
			this->tabPage3->Controls->Add(this->button13);
			this->tabPage3->Controls->Add(this->button12);
			this->tabPage3->Controls->Add(this->button11);
			this->tabPage3->Controls->Add(this->button10);
			this->tabPage3->Controls->Add(this->button9);
			this->tabPage3->Controls->Add(this->button8);
			this->tabPage3->Controls->Add(this->button7);
			this->tabPage3->Controls->Add(this->button6);
			this->tabPage3->Controls->Add(this->button5);
			this->tabPage3->Controls->Add(this->button4);
			this->tabPage3->Location = System::Drawing::Point(4, 30);
			this->tabPage3->Margin = System::Windows::Forms::Padding(1, 2, 1, 2);
			this->tabPage3->Name = L"tabPage3";
			this->tabPage3->Padding = System::Windows::Forms::Padding(1, 2, 1, 2);
			this->tabPage3->Size = System::Drawing::Size(523, 270);
			this->tabPage3->TabIndex = 2;
			this->tabPage3->Text = L"Инициализация";
			this->tabPage3->Click += gcnew System::EventHandler(this, &TriviadorHackV1::tabPage3_Click);
			// 
			// label10
			// 
			this->label10->AutoSize = true;
			this->label10->Location = System::Drawing::Point(9, 223);
			this->label10->Margin = System::Windows::Forms::Padding(1, 0, 1, 0);
			this->label10->Name = L"label10";
			this->label10->Size = System::Drawing::Size(564, 60);
			this->label10->TabIndex = 31;
			this->label10->Text = L"Кликни изън бутоните за да откриеш цялата фунцкионалност.\r\nКликни на подсказка за"
				L" да видиш какво трябва да въведеш.\r\nКликни на съседните бутони за въвеждане.";
			// 
			// checkBox10
			// 
			this->checkBox10->AutoSize = true;
			this->checkBox10->Location = System::Drawing::Point(489, 187);
			this->checkBox10->Margin = System::Windows::Forms::Padding(1, 2, 1, 2);
			this->checkBox10->Name = L"checkBox10";
			this->checkBox10->Size = System::Drawing::Size(18, 17);
			this->checkBox10->TabIndex = 30;
			this->checkBox10->UseVisualStyleBackColor = true;
			this->checkBox10->CheckedChanged += gcnew System::EventHandler(this, &TriviadorHackV1::checkBox10_CheckedChanged);
			// 
			// checkBox9
			// 
			this->checkBox9->AutoSize = true;
			this->checkBox9->Location = System::Drawing::Point(489, 139);
			this->checkBox9->Margin = System::Windows::Forms::Padding(1, 2, 1, 2);
			this->checkBox9->Name = L"checkBox9";
			this->checkBox9->Size = System::Drawing::Size(18, 17);
			this->checkBox9->TabIndex = 29;
			this->checkBox9->UseVisualStyleBackColor = true;
			this->checkBox9->CheckedChanged += gcnew System::EventHandler(this, &TriviadorHackV1::checkBox9_CheckedChanged);
			// 
			// checkBox8
			// 
			this->checkBox8->AutoSize = true;
			this->checkBox8->Location = System::Drawing::Point(489, 98);
			this->checkBox8->Margin = System::Windows::Forms::Padding(1, 2, 1, 2);
			this->checkBox8->Name = L"checkBox8";
			this->checkBox8->Size = System::Drawing::Size(18, 17);
			this->checkBox8->TabIndex = 28;
			this->checkBox8->UseVisualStyleBackColor = true;
			this->checkBox8->CheckedChanged += gcnew System::EventHandler(this, &TriviadorHackV1::checkBox8_CheckedChanged);
			// 
			// checkBox7
			// 
			this->checkBox7->AutoSize = true;
			this->checkBox7->Location = System::Drawing::Point(489, 64);
			this->checkBox7->Margin = System::Windows::Forms::Padding(1, 2, 1, 2);
			this->checkBox7->Name = L"checkBox7";
			this->checkBox7->Size = System::Drawing::Size(18, 17);
			this->checkBox7->TabIndex = 27;
			this->checkBox7->UseVisualStyleBackColor = true;
			this->checkBox7->CheckedChanged += gcnew System::EventHandler(this, &TriviadorHackV1::checkBox7_CheckedChanged);
			// 
			// checkBox6
			// 
			this->checkBox6->AutoSize = true;
			this->checkBox6->Location = System::Drawing::Point(489, 18);
			this->checkBox6->Margin = System::Windows::Forms::Padding(1, 2, 1, 2);
			this->checkBox6->Name = L"checkBox6";
			this->checkBox6->Size = System::Drawing::Size(18, 17);
			this->checkBox6->TabIndex = 26;
			this->checkBox6->UseVisualStyleBackColor = true;
			this->checkBox6->CheckedChanged += gcnew System::EventHandler(this, &TriviadorHackV1::checkBox6_CheckedChanged);
			// 
			// checkBox5
			// 
			this->checkBox5->AutoSize = true;
			this->checkBox5->Location = System::Drawing::Point(231, 187);
			this->checkBox5->Margin = System::Windows::Forms::Padding(1, 2, 1, 2);
			this->checkBox5->Name = L"checkBox5";
			this->checkBox5->Size = System::Drawing::Size(18, 17);
			this->checkBox5->TabIndex = 25;
			this->checkBox5->UseVisualStyleBackColor = true;
			this->checkBox5->CheckedChanged += gcnew System::EventHandler(this, &TriviadorHackV1::checkBox5_CheckedChanged);
			// 
			// checkBox4
			// 
			this->checkBox4->AutoSize = true;
			this->checkBox4->Location = System::Drawing::Point(231, 142);
			this->checkBox4->Margin = System::Windows::Forms::Padding(1, 2, 1, 2);
			this->checkBox4->Name = L"checkBox4";
			this->checkBox4->Size = System::Drawing::Size(18, 17);
			this->checkBox4->TabIndex = 24;
			this->checkBox4->UseVisualStyleBackColor = true;
			this->checkBox4->CheckedChanged += gcnew System::EventHandler(this, &TriviadorHackV1::checkBox4_CheckedChanged);
			// 
			// checkBox3
			// 
			this->checkBox3->AutoSize = true;
			this->checkBox3->Location = System::Drawing::Point(231, 107);
			this->checkBox3->Margin = System::Windows::Forms::Padding(1, 2, 1, 2);
			this->checkBox3->Name = L"checkBox3";
			this->checkBox3->Size = System::Drawing::Size(18, 17);
			this->checkBox3->TabIndex = 23;
			this->checkBox3->UseVisualStyleBackColor = true;
			this->checkBox3->CheckedChanged += gcnew System::EventHandler(this, &TriviadorHackV1::checkBox3_CheckedChanged);
			// 
			// checkBox2
			// 
			this->checkBox2->AutoSize = true;
			this->checkBox2->Location = System::Drawing::Point(231, 68);
			this->checkBox2->Margin = System::Windows::Forms::Padding(1, 2, 1, 2);
			this->checkBox2->Name = L"checkBox2";
			this->checkBox2->Size = System::Drawing::Size(18, 17);
			this->checkBox2->TabIndex = 22;
			this->checkBox2->UseVisualStyleBackColor = true;
			this->checkBox2->CheckedChanged += gcnew System::EventHandler(this, &TriviadorHackV1::checkBox2_CheckedChanged);
			// 
			// checkBox1
			// 
			this->checkBox1->AutoSize = true;
			this->checkBox1->Location = System::Drawing::Point(231, 18);
			this->checkBox1->Margin = System::Windows::Forms::Padding(1, 2, 1, 2);
			this->checkBox1->Name = L"checkBox1";
			this->checkBox1->Size = System::Drawing::Size(18, 17);
			this->checkBox1->TabIndex = 21;
			this->checkBox1->UseVisualStyleBackColor = true;
			this->checkBox1->CheckedChanged += gcnew System::EventHandler(this, &TriviadorHackV1::checkBox1_CheckedChanged);
			// 
			// button23
			// 
			this->button23->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(34)), static_cast<System::Int32>(static_cast<System::Byte>(34)),
				static_cast<System::Int32>(static_cast<System::Byte>(34)));
			this->button23->Location = System::Drawing::Point(264, 171);
			this->button23->Margin = System::Windows::Forms::Padding(1, 2, 1, 2);
			this->button23->Name = L"button23";
			this->button23->Size = System::Drawing::Size(97, 50);
			this->button23->TabIndex = 19;
			this->button23->Text = L"Подсказка";
			this->button23->UseVisualStyleBackColor = false;
			this->button23->Click += gcnew System::EventHandler(this, &TriviadorHackV1::button23_Click);
			// 
			// button22
			// 
			this->button22->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(34)), static_cast<System::Int32>(static_cast<System::Byte>(34)),
				static_cast<System::Int32>(static_cast<System::Byte>(34)));
			this->button22->Location = System::Drawing::Point(15, 171);
			this->button22->Margin = System::Windows::Forms::Padding(1, 2, 1, 2);
			this->button22->Name = L"button22";
			this->button22->Size = System::Drawing::Size(97, 50);
			this->button22->TabIndex = 18;
			this->button22->Text = L"Подсказка";
			this->button22->UseVisualStyleBackColor = false;
			this->button22->Click += gcnew System::EventHandler(this, &TriviadorHackV1::button22_Click);
			// 
			// button21
			// 
			this->button21->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(34)), static_cast<System::Int32>(static_cast<System::Byte>(34)),
				static_cast<System::Int32>(static_cast<System::Byte>(34)));
			this->button21->Location = System::Drawing::Point(264, 98);
			this->button21->Margin = System::Windows::Forms::Padding(1, 2, 1, 2);
			this->button21->Name = L"button21";
			this->button21->Size = System::Drawing::Size(97, 30);
			this->button21->TabIndex = 17;
			this->button21->Text = L"Подксазка";
			this->button21->UseVisualStyleBackColor = false;
			this->button21->Click += gcnew System::EventHandler(this, &TriviadorHackV1::button21_Click);
			// 
			// button20
			// 
			this->button20->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(34)), static_cast<System::Int32>(static_cast<System::Byte>(34)),
				static_cast<System::Int32>(static_cast<System::Byte>(34)));
			this->button20->Location = System::Drawing::Point(264, 50);
			this->button20->Margin = System::Windows::Forms::Padding(1, 2, 1, 2);
			this->button20->Name = L"button20";
			this->button20->Size = System::Drawing::Size(97, 43);
			this->button20->TabIndex = 16;
			this->button20->Text = L"Подсказка";
			this->button20->UseVisualStyleBackColor = false;
			this->button20->Click += gcnew System::EventHandler(this, &TriviadorHackV1::button20_Click);
			// 
			// button19
			// 
			this->button19->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(34)), static_cast<System::Int32>(static_cast<System::Byte>(34)),
				static_cast<System::Int32>(static_cast<System::Byte>(34)));
			this->button19->Location = System::Drawing::Point(264, 15);
			this->button19->Margin = System::Windows::Forms::Padding(1, 2, 1, 2);
			this->button19->Name = L"button19";
			this->button19->Size = System::Drawing::Size(97, 30);
			this->button19->TabIndex = 15;
			this->button19->Text = L"Подсказка";
			this->button19->UseVisualStyleBackColor = false;
			this->button19->Click += gcnew System::EventHandler(this, &TriviadorHackV1::button19_Click);
			// 
			// button18
			// 
			this->button18->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(34)), static_cast<System::Int32>(static_cast<System::Byte>(34)),
				static_cast<System::Int32>(static_cast<System::Byte>(34)));
			this->button18->Location = System::Drawing::Point(264, 133);
			this->button18->Margin = System::Windows::Forms::Padding(1, 2, 1, 2);
			this->button18->Name = L"button18";
			this->button18->Size = System::Drawing::Size(97, 30);
			this->button18->TabIndex = 14;
			this->button18->Text = L"Подсказка";
			this->button18->UseVisualStyleBackColor = false;
			this->button18->Click += gcnew System::EventHandler(this, &TriviadorHackV1::button18_Click);
			// 
			// button17
			// 
			this->button17->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(34)), static_cast<System::Int32>(static_cast<System::Byte>(34)),
				static_cast<System::Int32>(static_cast<System::Byte>(34)));
			this->button17->Location = System::Drawing::Point(15, 133);
			this->button17->Margin = System::Windows::Forms::Padding(1, 2, 1, 2);
			this->button17->Name = L"button17";
			this->button17->Size = System::Drawing::Size(97, 30);
			this->button17->TabIndex = 13;
			this->button17->Text = L"Подсказка";
			this->button17->UseVisualStyleBackColor = false;
			this->button17->Click += gcnew System::EventHandler(this, &TriviadorHackV1::button17_Click);
			// 
			// button16
			// 
			this->button16->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(34)), static_cast<System::Int32>(static_cast<System::Byte>(34)),
				static_cast<System::Int32>(static_cast<System::Byte>(34)));
			this->button16->Location = System::Drawing::Point(15, 98);
			this->button16->Margin = System::Windows::Forms::Padding(1, 2, 1, 2);
			this->button16->Name = L"button16";
			this->button16->Size = System::Drawing::Size(97, 30);
			this->button16->TabIndex = 12;
			this->button16->Text = L"Подсказка";
			this->button16->UseVisualStyleBackColor = false;
			this->button16->Click += gcnew System::EventHandler(this, &TriviadorHackV1::button16_Click);
			// 
			// button15
			// 
			this->button15->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(34)), static_cast<System::Int32>(static_cast<System::Byte>(34)),
				static_cast<System::Int32>(static_cast<System::Byte>(34)));
			this->button15->Location = System::Drawing::Point(15, 49);
			this->button15->Margin = System::Windows::Forms::Padding(1, 2, 1, 2);
			this->button15->Name = L"button15";
			this->button15->Size = System::Drawing::Size(97, 43);
			this->button15->TabIndex = 11;
			this->button15->Text = L"Подсказка";
			this->button15->UseVisualStyleBackColor = false;
			this->button15->Click += gcnew System::EventHandler(this, &TriviadorHackV1::button15_Click);
			// 
			// button14
			// 
			this->button14->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(34)), static_cast<System::Int32>(static_cast<System::Byte>(34)),
				static_cast<System::Int32>(static_cast<System::Byte>(34)));
			this->button14->Location = System::Drawing::Point(15, 14);
			this->button14->Margin = System::Windows::Forms::Padding(1, 2, 1, 2);
			this->button14->Name = L"button14";
			this->button14->Size = System::Drawing::Size(97, 30);
			this->button14->TabIndex = 10;
			this->button14->Text = L"Подсказка";
			this->button14->UseVisualStyleBackColor = false;
			this->button14->Click += gcnew System::EventHandler(this, &TriviadorHackV1::button14_Click);
			// 
			// button13
			// 
			this->button13->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(34)), static_cast<System::Int32>(static_cast<System::Byte>(34)),
				static_cast<System::Int32>(static_cast<System::Byte>(34)));
			this->button13->Location = System::Drawing::Point(377, 171);
			this->button13->Margin = System::Windows::Forms::Padding(1, 2, 1, 2);
			this->button13->Name = L"button13";
			this->button13->Size = System::Drawing::Size(97, 50);
			this->button13->TabIndex = 9;
			this->button13->Text = L"Всички отговори";
			this->button13->UseVisualStyleBackColor = false;
			this->button13->Click += gcnew System::EventHandler(this, &TriviadorHackV1::button13_Click);
			// 
			// button12
			// 
			this->button12->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(34)), static_cast<System::Int32>(static_cast<System::Byte>(34)),
				static_cast<System::Int32>(static_cast<System::Byte>(34)));
			this->button12->Location = System::Drawing::Point(121, 171);
			this->button12->Margin = System::Windows::Forms::Padding(1, 2, 1, 2);
			this->button12->Name = L"button12";
			this->button12->Size = System::Drawing::Size(97, 50);
			this->button12->TabIndex = 8;
			this->button12->Text = L"Първи отговор";
			this->button12->UseVisualStyleBackColor = false;
			this->button12->Click += gcnew System::EventHandler(this, &TriviadorHackV1::button12_Click);
			// 
			// button11
			// 
			this->button11->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(34)), static_cast<System::Int32>(static_cast<System::Byte>(34)),
				static_cast<System::Int32>(static_cast<System::Byte>(34)));
			this->button11->Location = System::Drawing::Point(377, 98);
			this->button11->Margin = System::Windows::Forms::Padding(1, 2, 1, 2);
			this->button11->Name = L"button11";
			this->button11->Size = System::Drawing::Size(97, 30);
			this->button11->TabIndex = 7;
			this->button11->Text = L"Харесване";
			this->button11->UseVisualStyleBackColor = false;
			this->button11->Click += gcnew System::EventHandler(this, &TriviadorHackV1::button11_Click);
			// 
			// button10
			// 
			this->button10->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(34)), static_cast<System::Int32>(static_cast<System::Byte>(34)),
				static_cast<System::Int32>(static_cast<System::Byte>(34)));
			this->button10->Location = System::Drawing::Point(377, 49);
			this->button10->Margin = System::Windows::Forms::Padding(1, 2, 1, 2);
			this->button10->Name = L"button10";
			this->button10->Size = System::Drawing::Size(97, 43);
			this->button10->TabIndex = 6;
			this->button10->Text = L"Използвана тълпа";
			this->button10->UseVisualStyleBackColor = false;
			this->button10->Click += gcnew System::EventHandler(this, &TriviadorHackV1::button10_Click);
			// 
			// button9
			// 
			this->button9->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(34)), static_cast<System::Int32>(static_cast<System::Byte>(34)),
				static_cast<System::Int32>(static_cast<System::Byte>(34)));
			this->button9->Location = System::Drawing::Point(377, 14);
			this->button9->Margin = System::Windows::Forms::Padding(1, 2, 1, 2);
			this->button9->Name = L"button9";
			this->button9->Size = System::Drawing::Size(97, 30);
			this->button9->TabIndex = 5;
			this->button9->Text = L"Тълпа";
			this->button9->UseVisualStyleBackColor = false;
			this->button9->Click += gcnew System::EventHandler(this, &TriviadorHackV1::button9_Click);
			// 
			// button8
			// 
			this->button8->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(34)), static_cast<System::Int32>(static_cast<System::Byte>(34)),
				static_cast<System::Int32>(static_cast<System::Byte>(34)));
			this->button8->Location = System::Drawing::Point(377, 133);
			this->button8->Margin = System::Windows::Forms::Padding(1, 2, 1, 2);
			this->button8->Name = L"button8";
			this->button8->Size = System::Drawing::Size(97, 30);
			this->button8->TabIndex = 4;
			this->button8->Text = L"Мишена";
			this->button8->UseVisualStyleBackColor = false;
			this->button8->Click += gcnew System::EventHandler(this, &TriviadorHackV1::button8_Click);
			// 
			// button7
			// 
			this->button7->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(34)), static_cast<System::Int32>(static_cast<System::Byte>(34)),
				static_cast<System::Int32>(static_cast<System::Byte>(34)));
			this->button7->Location = System::Drawing::Point(121, 133);
			this->button7->Margin = System::Windows::Forms::Padding(1, 2, 1, 2);
			this->button7->Name = L"button7";
			this->button7->Size = System::Drawing::Size(97, 30);
			this->button7->TabIndex = 3;
			this->button7->Text = L"Отговор";
			this->button7->UseVisualStyleBackColor = false;
			this->button7->Click += gcnew System::EventHandler(this, &TriviadorHackV1::button7_Click);
			// 
			// button6
			// 
			this->button6->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(34)), static_cast<System::Int32>(static_cast<System::Byte>(34)),
				static_cast<System::Int32>(static_cast<System::Byte>(34)));
			this->button6->Location = System::Drawing::Point(121, 98);
			this->button6->Margin = System::Windows::Forms::Padding(1, 2, 1, 2);
			this->button6->Name = L"button6";
			this->button6->Size = System::Drawing::Size(97, 30);
			this->button6->TabIndex = 2;
			this->button6->Text = L"Въпрос";
			this->button6->UseVisualStyleBackColor = false;
			this->button6->Click += gcnew System::EventHandler(this, &TriviadorHackV1::button6_Click);
			// 
			// button5
			// 
			this->button5->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(34)), static_cast<System::Int32>(static_cast<System::Byte>(34)),
				static_cast<System::Int32>(static_cast<System::Byte>(34)));
			this->button5->Location = System::Drawing::Point(121, 49);
			this->button5->Margin = System::Windows::Forms::Padding(1, 2, 1, 2);
			this->button5->Name = L"button5";
			this->button5->Size = System::Drawing::Size(97, 43);
			this->button5->TabIndex = 1;
			this->button5->Text = L"Използван бинокал";
			this->button5->UseVisualStyleBackColor = false;
			this->button5->Click += gcnew System::EventHandler(this, &TriviadorHackV1::button5_Click);
			// 
			// button4
			// 
			this->button4->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(34)), static_cast<System::Int32>(static_cast<System::Byte>(34)),
				static_cast<System::Int32>(static_cast<System::Byte>(34)));
			this->button4->Location = System::Drawing::Point(121, 14);
			this->button4->Margin = System::Windows::Forms::Padding(1, 2, 1, 2);
			this->button4->Name = L"button4";
			this->button4->Size = System::Drawing::Size(97, 30);
			this->button4->TabIndex = 0;
			this->button4->Text = L"Бинокал";
			this->button4->UseVisualStyleBackColor = false;
			this->button4->Click += gcnew System::EventHandler(this, &TriviadorHackV1::button4_Click);
			// 
			// tabPage4
			// 
			this->tabPage4->BackColor = System::Drawing::Color::Black;
			this->tabPage4->Controls->Add(this->label9);
			this->tabPage4->Controls->Add(this->label8);
			this->tabPage4->Controls->Add(this->button25);
			this->tabPage4->Controls->Add(this->button24);
			this->tabPage4->Location = System::Drawing::Point(4, 30);
			this->tabPage4->Margin = System::Windows::Forms::Padding(1, 2, 1, 2);
			this->tabPage4->Name = L"tabPage4";
			this->tabPage4->Padding = System::Windows::Forms::Padding(1, 2, 1, 2);
			this->tabPage4->Size = System::Drawing::Size(523, 270);
			this->tabPage4->TabIndex = 3;
			this->tabPage4->Text = L"Други";
			this->tabPage4->Click += gcnew System::EventHandler(this, &TriviadorHackV1::tabPage4_Click);
			// 
			// label9
			// 
			this->label9->AutoSize = true;
			this->label9->Location = System::Drawing::Point(137, 124);
			this->label9->Margin = System::Windows::Forms::Padding(1, 0, 1, 0);
			this->label9->Name = L"label9";
			this->label9->Size = System::Drawing::Size(424, 40);
			this->label9->TabIndex = 3;
			this->label9->Text = L"Всички въпроси ще бъдат \r\nзаписани в папка \"see_questions\" на \"IOFiles\".";
			// 
			// label8
			// 
			this->label8->AutoSize = true;
			this->label8->Location = System::Drawing::Point(137, 44);
			this->label8->Margin = System::Windows::Forms::Padding(1, 0, 1, 0);
			this->label8->Name = L"label8";
			this->label8->Size = System::Drawing::Size(346, 40);
			this->label8->TabIndex = 2;
			this->label8->Text = L"Трябва да сте сложили файлове с \r\nвъпроси в папка \"questions_to_copy\".";
			// 
			// button25
			// 
			this->button25->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(34)), static_cast<System::Int32>(static_cast<System::Byte>(34)),
				static_cast<System::Int32>(static_cast<System::Byte>(34)));
			this->button25->Location = System::Drawing::Point(31, 107);
			this->button25->Margin = System::Windows::Forms::Padding(1, 2, 1, 2);
			this->button25->Name = L"button25";
			this->button25->Size = System::Drawing::Size(97, 49);
			this->button25->TabIndex = 1;
			this->button25->Text = L"Виж въпросите";
			this->button25->UseVisualStyleBackColor = false;
			this->button25->Click += gcnew System::EventHandler(this, &TriviadorHackV1::button25_Click);
			// 
			// button24
			// 
			this->button24->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(34)), static_cast<System::Int32>(static_cast<System::Byte>(34)),
				static_cast<System::Int32>(static_cast<System::Byte>(34)));
			this->button24->Location = System::Drawing::Point(31, 27);
			this->button24->Margin = System::Windows::Forms::Padding(1, 2, 1, 2);
			this->button24->Name = L"button24";
			this->button24->Size = System::Drawing::Size(97, 50);
			this->button24->TabIndex = 0;
			this->button24->Text = L"Добави въпроси";
			this->button24->UseVisualStyleBackColor = false;
			this->button24->Click += gcnew System::EventHandler(this, &TriviadorHackV1::button24_Click);
			// 
			// pictureBox1
			// 
			this->pictureBox1->Location = System::Drawing::Point(553, 41);
			this->pictureBox1->Margin = System::Windows::Forms::Padding(1, 2, 1, 2);
			this->pictureBox1->Name = L"pictureBox1";
			this->pictureBox1->Size = System::Drawing::Size(367, 256);
			this->pictureBox1->TabIndex = 6;
			this->pictureBox1->TabStop = false;
			// 
			// pictureBox2
			// 
			this->pictureBox2->Location = System::Drawing::Point(937, 41);
			this->pictureBox2->Margin = System::Windows::Forms::Padding(1, 2, 1, 2);
			this->pictureBox2->Name = L"pictureBox2";
			this->pictureBox2->Size = System::Drawing::Size(378, 256);
			this->pictureBox2->TabIndex = 7;
			this->pictureBox2->TabStop = false;
			// 
			// pictureBox3
			// 
			this->pictureBox3->Location = System::Drawing::Point(1333, 41);
			this->pictureBox3->Margin = System::Windows::Forms::Padding(1, 2, 1, 2);
			this->pictureBox3->Name = L"pictureBox3";
			this->pictureBox3->Size = System::Drawing::Size(357, 256);
			this->pictureBox3->TabIndex = 8;
			this->pictureBox3->TabStop = false;
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->Location = System::Drawing::Point(550, 10);
			this->label5->Margin = System::Windows::Forms::Padding(1, 0, 1, 0);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(169, 20);
			this->label5->TabIndex = 9;
			this->label5->Text = L"Последна снимка.";
			// 
			// label6
			// 
			this->label6->AutoSize = true;
			this->label6->Location = System::Drawing::Point(934, 9);
			this->label6->Margin = System::Windows::Forms::Padding(1, 0, 1, 0);
			this->label6->Name = L"label6";
			this->label6->Size = System::Drawing::Size(231, 20);
			this->label6->TabIndex = 10;
			this->label6->Text = L"Как трябва да изглежда\?";
			this->label6->Click += gcnew System::EventHandler(this, &TriviadorHackV1::label6_Click);
			// 
			// label7
			// 
			this->label7->AutoSize = true;
			this->label7->Location = System::Drawing::Point(1330, 9);
			this->label7->Margin = System::Windows::Forms::Padding(1, 0, 1, 0);
			this->label7->Name = L"label7";
			this->label7->Size = System::Drawing::Size(170, 20);
			this->label7->TabIndex = 11;
			this->label7->Text = L"Къде да се търси\?";
			this->label7->Click += gcnew System::EventHandler(this, &TriviadorHackV1::label7_Click);
			// 
			// TriviadorHackV1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(10, 18);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::Color::Black;
			this->ClientSize = System::Drawing::Size(536, 308);
			this->Controls->Add(this->label7);
			this->Controls->Add(this->label6);
			this->Controls->Add(this->label5);
			this->Controls->Add(this->pictureBox3);
			this->Controls->Add(this->pictureBox2);
			this->Controls->Add(this->pictureBox1);
			this->Controls->Add(this->tabControl1);
			this->Font = (gcnew System::Drawing::Font(L"Verdana", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->ForeColor = System::Drawing::Color::OrangeRed;
			this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
			this->Margin = System::Windows::Forms::Padding(1, 2, 1, 2);
			this->Name = L"TriviadorHackV1";
			this->Text = L"TriviadorHackV1";
			this->Load += gcnew System::EventHandler(this, &TriviadorHackV1::TriviadorHackV1_Load);
			this->tabControl1->ResumeLayout(false);
			this->tabPage1->ResumeLayout(false);
			this->tabPage1->PerformLayout();
			this->tabPage2->ResumeLayout(false);
			this->tabPage2->PerformLayout();
			this->tabPage3->ResumeLayout(false);
			this->tabPage3->PerformLayout();
			this->tabPage4->ResumeLayout(false);
			this->tabPage4->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox2))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox3))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}

#pragma endregion


		Thread^ oThread;
		bool isStarted = false;// , isSuspended = false;
		bool goOn = true;
	private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e) {
		if (!isStarted) {
			oThread = gcnew Thread(gcnew ThreadStart(this, &TriviadorHackV1::ThreadProc));
			isStarted = true;
			goOn = true;
			oThread->IsBackground = true;
			oThread->Start();
			label1->Text = L"Хакът работи!";
		}
		else {
			label1->Text = L"Изчакай хака да спре!";
			label1->Invalidate();
			label1->Update();
			sleep_until(system_clock::now() + milliseconds(waitToCloseHack));
			goOn = false;
			isStarted = false;
			if (oThread->ThreadState != System::Threading::ThreadState::Unstarted) {
				oThread->Join();
			}
			label1->Text = L"Натисни \"СТАРТ\" за да пуснеш хака!";
		}
		
	}		   
	private: System::Void button2_Click(System::Object^ sender, System::EventArgs^ e) {

		//ofstream writeLog;
		//writeLog.open(log_filename, std::ios::out | std::ios::app);
		//if (!writeLog) {
		//	cout << "Opening " << log_filename << " failed" << endl;
		//}

		//writeLog << "Wrong answer!" << endl;
		//writeLog.flush();
		//writeLog.close();

		std::wofstream writeLog;
		writeLog.imbue(std::locale(std::locale::empty(), new std::codecvt_utf8<wchar_t, 0x10ffff, std::generate_header>));
		writeLog.open(log_filename, std::ios::out | std::ios::app);
		writeLog << L"Грешен отговор!\n";
		writeLog.close();
	}
private: System::Void textBox1_TextChanged(System::Object^ sender, System::EventArgs^ e) {
}
private: System::Void richTextBox1_TextChanged(System::Object^ sender, System::EventArgs^ e) {
}
private: System::Void tabPage1_Click(System::Object^ sender, System::EventArgs^ e) {
}
private: System::Void tabPage2_Click(System::Object^ sender, System::EventArgs^ e) {
	resizeForm(!resizeConst);
}
private: System::Void button3_Click(System::Object^ sender, System::EventArgs^ e) {

	label4->Text = L"Въпросът се търси. Моля изчакайте.";
	std::wstring strQuestion = msclr::interop::marshal_as<std::wstring>(richTextBox2->Text);
	std::wstring strAnswer = msclr::interop::marshal_as<std::wstring>(richTextBox3->Text);

	//setup converter
	using convert_type = std::codecvt_utf8<wchar_t>;
	std::wstring_convert<convert_type, wchar_t> converter;

	//use converter (.to_bytes: wstr->str, .from_bytes: str->wstr)
	std::string converted_strQuestion = converter.to_bytes(strQuestion);
	std::string converted_strAnswer = converter.to_bytes(strAnswer);

	char question[questionSize] = { 0 };
	char answer[answerSizeSecond] = { 0 };
	strncpy_s(question, questionSize, converted_strQuestion.c_str(), converted_strQuestion.length());
	strncpy_s(answer, answerSizeSecond, converted_strAnswer.c_str(), converted_strAnswer.length());

	Wrapper wr;
	if (wr.changeQuestion(question, answer)) {
		label4->Text = L"Отговорът беше успешно записан!\n\\Въпросът беше успешно изтрит!";
	}
	else {
		label4->Text = L"Въпросът не беше намерен! \nОпитайте пак!";
	}

}
private: System::Void button4_Click(System::Object^ sender, System::EventArgs^ e) {
	setChangeAnchorQuestionAnswerButton(AnchorHintInd);
}
private: System::Void button5_Click(System::Object^ sender, System::EventArgs^ e) {
	setChangeAnchorQuestionAnswerButton(AnchorHintUsedInd);
}
private: System::Void button6_Click(System::Object^ sender, System::EventArgs^ e) {
	setChangeAnchorQuestionAnswerButton(questionCoordInd);
}
private: System::Void button7_Click(System::Object^ sender, System::EventArgs^ e) {
	setChangeAnchorQuestionAnswerButton(answerCoordInd);
}
private: System::Void button8_Click(System::Object^ sender, System::EventArgs^ e) {
	setChangeAnchorQuestionAnswerButton(AnchorTargetCoordInd);
}
private: System::Void button9_Click(System::Object^ sender, System::EventArgs^ e) {
	setChangeAnchorQuestionAnswerButton(anchorHintSecondCoordInd);
}
private: System::Void button10_Click(System::Object^ sender, System::EventArgs^ e) {
	setChangeAnchorQuestionAnswerButton(anchorHintUsedSecondCoordInd);
}
private: System::Void button11_Click(System::Object^ sender, System::EventArgs^ e) {
	setChangeAnchorQuestionAnswerButton(anchorLikeQuestionCoordInd);
}
private: System::Void button12_Click(System::Object^ sender, System::EventArgs^ e) {
	setChangeAnchorQuestionAnswerButton(answerFirstQuestionSecondInd);
}
private: System::Void button13_Click(System::Object^ sender, System::EventArgs^ e) {
	setChangeAnchorQuestionAnswerButton(answersQuestionSecondInd);

}
private: System::Void button14_Click(System::Object^ sender, System::EventArgs^ e) {
	setGuideImages(pictureBox2, hint_filename, pictureBox3, hintBig_filename);
}
private: System::Void button15_Click(System::Object^ sender, System::EventArgs^ e) {
	setGuideImages(pictureBox2, hintUsed_filename, pictureBox3, hintUsedBig_filename);
}
private: System::Void button16_Click(System::Object^ sender, System::EventArgs^ e) {
	setGuideImages(pictureBox2, question_filename, pictureBox3, questionBig_filename);
}
private: System::Void button17_Click(System::Object^ sender, System::EventArgs^ e) {
	setGuideImages(pictureBox2, answer_filename, pictureBox3, answerBig_filename);
}
private: System::Void button18_Click(System::Object^ sender, System::EventArgs^ e) {
	setGuideImages(pictureBox2, target_filename, pictureBox3, targetBig_filename);
}
private: System::Void button19_Click(System::Object^ sender, System::EventArgs^ e) {
	setGuideImages(pictureBox2, hintSecond_filename, pictureBox3, hintSecondBig_filename);
}
private: System::Void button20_Click(System::Object^ sender, System::EventArgs^ e) {
	setGuideImages(pictureBox2, hintSecondUsed_filename, pictureBox3, hintSecondUsedBig_filename);
}
private: System::Void button21_Click(System::Object^ sender, System::EventArgs^ e) {
	setGuideImages(pictureBox2, likeQuestion_filename, pictureBox3, likeQuestionBig_filename);
}
private: System::Void button22_Click(System::Object^ sender, System::EventArgs^ e) {
	setGuideImages(pictureBox2, answerFirstQuestionSecond_filename, pictureBox3, answerFirstQuestionSecondBig_filename);
}
private: System::Void button23_Click(System::Object^ sender, System::EventArgs^ e) {
	setGuideImages(pictureBox2, answersQuestionSecond_filename, pictureBox3, answersQuestionSecondBig_filename);
}
private: System::Void tabPage3_Click(System::Object^ sender, System::EventArgs^ e) {
	resizeForm(resizeConst);
}
private: System::Void HackTest_Click(System::Object^ sender, System::EventArgs^ e) {
	resizeForm(!resizeConst);
}
private: System::Void label1_Click(System::Object^ sender, System::EventArgs^ e) {
}
private: System::Void label3_Click(System::Object^ sender, System::EventArgs^ e) {
}
private: System::Void TriviadorHackV1_Load(System::Object^ sender, System::EventArgs^ e) {
}
private: System::Void checkBox6_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
}
private: System::Void checkBox7_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
}
private: System::Void checkBox8_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
}
private: System::Void checkBox9_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
}
private: System::Void checkBox10_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
}
private: System::Void checkBox1_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
}
private: System::Void checkBox2_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
}
private: System::Void checkBox3_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
}
private: System::Void checkBox4_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
}
private: System::Void checkBox5_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
}
private: System::Void label6_Click(System::Object^ sender, System::EventArgs^ e) {
}
private: System::Void label7_Click(System::Object^ sender, System::EventArgs^ e) {
}
private: System::Void tabPage4_Click(System::Object^ sender, System::EventArgs^ e) {
	resizeForm(!resizeConst);
}
private: System::Void button24_Click(System::Object^ sender, System::EventArgs^ e) {
	label8->Text = L"Въпросите се добавят. Моля изчакайте.";
	Wrapper  wr;
	if (wr.addQuestions()) {
		label8->Text = L"Въпросите бяха добавени успешно!";
	}
	else {
		label8->Text = L"Грешка при прочитането на файловете.\\n Уверете се, че сте добавили правилните файлове.";
	}
}
private: System::Void button25_Click(System::Object^ sender, System::EventArgs^ e) {
	label9->Text = L"Въпросите се записват. Моля изчакайте.";
	Wrapper wr;
	wr.readQuestions();
	label9->Text = L"Въпросите бяха записани успешно за преглед.";
}
};
}

