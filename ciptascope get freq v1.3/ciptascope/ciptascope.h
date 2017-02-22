//#include "afxwin.h"
#include "stdafx.h"
#include <windows.h>
#include <string>
#include <stdlib.h>
#include "ftd2xx.h"

FT_HANDLE ftHandle;

#pragma once

const int Fimap[] = {372, 372, 558, 774, 1116, 1488, 1860, 0, 0, 512, 768, 1024, 1536, 2048, 0, 0};
const char Dimap[] = {0, 1, 2, 4, 8, 16, 32, 64, 12, 20, 0, 0, 0, 0 ,0, 0};
int reset_low;
int counter;
WORD freqDataBuffer[60];
byte command;
int globalIndex,phase;
DWORD assign, remaining;
unsigned char datalength ,start,stop;
unsigned char INSBefore;
int temp;
int updatebaudcounter;

//
//std::string hexStr(unsigned char *data, int len)
//{
//  std::string s(len * 2, ' ');
//  for (int i = 0; i < len; ++i) {
//    s[2 * i]     = hexmap[(data[i] & 0xF0) >> 4];
//    s[2 * i + 1] = hexmap[data[i] & 0x0F];
//  }
//  return s;
//}


namespace ciptascope {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for Form1
	///
	/// WARNING: If you change the name of this class, you will need to change the
	///          'Resource File Name' property for the managed resource compiler tool
	///          associated with all .resx files this class depends on.  Otherwise,
	///          the designers will not be able to interact properly with localized
	///          resources associated with this form.
	/// </summary>
	public ref class Form1 : public System::Windows::Forms::Form
	{
	public:
		Form1(void)
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
		~Form1()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Timer^  CardResetPoll;



	private: System::Windows::Forms::MenuStrip^  MainMenu;

	private: System::Windows::Forms::ToolStripMenuItem^  fileToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  openToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  exitToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  optionsToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  baudRateToolStripMenuItem;
	private: System::Windows::Forms::ToolStripComboBox^  m_baudrate;

	private: System::Windows::Forms::ToolStripMenuItem^  helpToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  aboutToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  deviceToolStripMenuItem;
	private: System::Windows::Forms::ToolStripComboBox^  m_devlist;

	private: System::Windows::Forms::StatusStrip^  statusStrip1;
	private: System::Windows::Forms::ToolStripStatusLabel^  toolStripStatusLabel1;


	private: System::Windows::Forms::ToolStripMenuItem^  closeToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  scanToolStripMenuItem;

	private: System::Windows::Forms::ToolStripMenuItem^  frequencyToolStripMenuItem;
	private: System::Windows::Forms::ToolStripComboBox^  m_FreqList;
	private: System::Windows::Forms::RichTextBox^  richTextBox1;

	private: System::Windows::Forms::ToolStripMenuItem^  cleanToolStripMenuItem;
	private: System::Windows::Forms::Timer^  pdupoll;
	private: System::Windows::Forms::ToolStripMenuItem^  scanFrequencyToolStripMenuItem;
	private: System::Windows::Forms::TextBox^  textBox1;

	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::ToolStripMenuItem^  helloToolStripMenuItem;
	private: System::Windows::Forms::TextBox^  textBox2;
	private: System::Windows::Forms::Timer^  timer1;
	private: System::Windows::Forms::ToolStripMenuItem^  printFreqBufferToolStripMenuItem;
	private: System::Windows::Forms::ToolStripStatusLabel^  toolStripStatusLabel2;
	private: System::Windows::Forms::Timer^  voltage;
	private: System::Windows::Forms::ToolStripMenuItem^  saveAsToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  openLogFileToolStripMenuItem;
















	protected: 

	protected: 

	protected: 

	protected: 
	private: System::ComponentModel::IContainer^  components;

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			this->CardResetPoll = (gcnew System::Windows::Forms::Timer(this->components));
			this->MainMenu = (gcnew System::Windows::Forms::MenuStrip());
			this->fileToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->openToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->closeToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->openLogFileToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->saveAsToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->cleanToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->exitToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->optionsToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->deviceToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->scanToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->m_devlist = (gcnew System::Windows::Forms::ToolStripComboBox());
			this->frequencyToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->m_FreqList = (gcnew System::Windows::Forms::ToolStripComboBox());
			this->scanFrequencyToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->printFreqBufferToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->helloToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->baudRateToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->m_baudrate = (gcnew System::Windows::Forms::ToolStripComboBox());
			this->helpToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->aboutToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->statusStrip1 = (gcnew System::Windows::Forms::StatusStrip());
			this->toolStripStatusLabel1 = (gcnew System::Windows::Forms::ToolStripStatusLabel());
			this->toolStripStatusLabel2 = (gcnew System::Windows::Forms::ToolStripStatusLabel());
			this->richTextBox1 = (gcnew System::Windows::Forms::RichTextBox());
			this->pdupoll = (gcnew System::Windows::Forms::Timer(this->components));
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->textBox2 = (gcnew System::Windows::Forms::TextBox());
			this->timer1 = (gcnew System::Windows::Forms::Timer(this->components));
			this->voltage = (gcnew System::Windows::Forms::Timer(this->components));
			this->MainMenu->SuspendLayout();
			this->statusStrip1->SuspendLayout();
			this->SuspendLayout();
			// 
			// CardResetPoll
			// 
			this->CardResetPoll->Interval = 1;
			this->CardResetPoll->Tick += gcnew System::EventHandler(this, &Form1::timer1_Tick);
			// 
			// MainMenu
			// 
			this->MainMenu->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(3) {this->fileToolStripMenuItem, 
				this->optionsToolStripMenuItem, this->helpToolStripMenuItem});
			this->MainMenu->Location = System::Drawing::Point(0, 0);
			this->MainMenu->Name = L"MainMenu";
			this->MainMenu->Size = System::Drawing::Size(839, 24);
			this->MainMenu->TabIndex = 4;
			this->MainMenu->ItemClicked += gcnew System::Windows::Forms::ToolStripItemClickedEventHandler(this, &Form1::MainMenu_ItemClicked);
			// 
			// fileToolStripMenuItem
			// 
			this->fileToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(6) {this->openToolStripMenuItem, 
				this->closeToolStripMenuItem, this->openLogFileToolStripMenuItem, this->saveAsToolStripMenuItem, this->cleanToolStripMenuItem, 
				this->exitToolStripMenuItem});
			this->fileToolStripMenuItem->Name = L"fileToolStripMenuItem";
			this->fileToolStripMenuItem->Size = System::Drawing::Size(37, 20);
			this->fileToolStripMenuItem->Text = L"File";
			// 
			// openToolStripMenuItem
			// 
			this->openToolStripMenuItem->Name = L"openToolStripMenuItem";
			this->openToolStripMenuItem->Size = System::Drawing::Size(147, 22);
			this->openToolStripMenuItem->Text = L"Connect";
			this->openToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::openToolStripMenuItem_Click);
			// 
			// closeToolStripMenuItem
			// 
			this->closeToolStripMenuItem->Name = L"closeToolStripMenuItem";
			this->closeToolStripMenuItem->Size = System::Drawing::Size(147, 22);
			this->closeToolStripMenuItem->Text = L"Disconnect";
			this->closeToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::closeToolStripMenuItem_Click);
			// 
			// openLogFileToolStripMenuItem
			// 
			this->openLogFileToolStripMenuItem->Name = L"openLogFileToolStripMenuItem";
			this->openLogFileToolStripMenuItem->Size = System::Drawing::Size(147, 22);
			this->openLogFileToolStripMenuItem->Text = L"Open Log File";
			this->openLogFileToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::openLogFileToolStripMenuItem_Click);
			// 
			// saveAsToolStripMenuItem
			// 
			this->saveAsToolStripMenuItem->Name = L"saveAsToolStripMenuItem";
			this->saveAsToolStripMenuItem->Size = System::Drawing::Size(147, 22);
			this->saveAsToolStripMenuItem->Text = L"Save As";
			this->saveAsToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::saveAsToolStripMenuItem_Click);
			// 
			// cleanToolStripMenuItem
			// 
			this->cleanToolStripMenuItem->Name = L"cleanToolStripMenuItem";
			this->cleanToolStripMenuItem->Size = System::Drawing::Size(147, 22);
			this->cleanToolStripMenuItem->Text = L"Clean";
			this->cleanToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::cleanToolStripMenuItem_Click);
			// 
			// exitToolStripMenuItem
			// 
			this->exitToolStripMenuItem->Name = L"exitToolStripMenuItem";
			this->exitToolStripMenuItem->Size = System::Drawing::Size(147, 22);
			this->exitToolStripMenuItem->Text = L"Exit";
			this->exitToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::exitToolStripMenuItem_Click);
			// 
			// optionsToolStripMenuItem
			// 
			this->optionsToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(3) {this->deviceToolStripMenuItem, 
				this->frequencyToolStripMenuItem, this->baudRateToolStripMenuItem});
			this->optionsToolStripMenuItem->Name = L"optionsToolStripMenuItem";
			this->optionsToolStripMenuItem->Size = System::Drawing::Size(61, 20);
			this->optionsToolStripMenuItem->Text = L"Options";
			// 
			// deviceToolStripMenuItem
			// 
			this->deviceToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {this->scanToolStripMenuItem, 
				this->m_devlist});
			this->deviceToolStripMenuItem->Name = L"deviceToolStripMenuItem";
			this->deviceToolStripMenuItem->Size = System::Drawing::Size(152, 22);
			this->deviceToolStripMenuItem->Text = L"Device";
			this->deviceToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::deviceToolStripMenuItem_Click);
			// 
			// scanToolStripMenuItem
			// 
			this->scanToolStripMenuItem->Name = L"scanToolStripMenuItem";
			this->scanToolStripMenuItem->Size = System::Drawing::Size(181, 22);
			this->scanToolStripMenuItem->Text = L"Scan";
			this->scanToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::scanToolStripMenuItem_Click);
			// 
			// m_devlist
			// 
			this->m_devlist->Name = L"m_devlist";
			this->m_devlist->Size = System::Drawing::Size(121, 23);
			this->m_devlist->Text = L"Select Device";
			this->m_devlist->Click += gcnew System::EventHandler(this, &Form1::m_devlist_Click);
			// 
			// frequencyToolStripMenuItem
			// 
			this->frequencyToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(4) {this->m_FreqList, 
				this->scanFrequencyToolStripMenuItem, this->printFreqBufferToolStripMenuItem, this->helloToolStripMenuItem});
			this->frequencyToolStripMenuItem->Name = L"frequencyToolStripMenuItem";
			this->frequencyToolStripMenuItem->Size = System::Drawing::Size(152, 22);
			this->frequencyToolStripMenuItem->Text = L"Show";
			this->frequencyToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::frequencyToolStripMenuItem_Click);
			// 
			// m_FreqList
			// 
			this->m_FreqList->Items->AddRange(gcnew cli::array< System::Object^  >(8) {L"1000000", L"2000000", L"3000000", L"3570000", 
				L"5000000", L"7000000", L"10000000", L"20000000"});
			this->m_FreqList->Name = L"m_FreqList";
			this->m_FreqList->Size = System::Drawing::Size(121, 23);
			this->m_FreqList->Text = L"5000000";
			this->m_FreqList->Visible = false;
			this->m_FreqList->Click += gcnew System::EventHandler(this, &Form1::m_FreqList_Click);
			// 
			// scanFrequencyToolStripMenuItem
			// 
			this->scanFrequencyToolStripMenuItem->Name = L"scanFrequencyToolStripMenuItem";
			this->scanFrequencyToolStripMenuItem->Size = System::Drawing::Size(181, 22);
			this->scanFrequencyToolStripMenuItem->Text = L"Scan Frequency";
			this->scanFrequencyToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::scanFrequencyToolStripMenuItem_Click);
			// 
			// printFreqBufferToolStripMenuItem
			// 
			this->printFreqBufferToolStripMenuItem->Name = L"printFreqBufferToolStripMenuItem";
			this->printFreqBufferToolStripMenuItem->Size = System::Drawing::Size(181, 22);
			this->printFreqBufferToolStripMenuItem->Text = L"Print Freq Buffer";
			this->printFreqBufferToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::printFreqBufferToolStripMenuItem_Click);
			// 
			// helloToolStripMenuItem
			// 
			this->helloToolStripMenuItem->Name = L"helloToolStripMenuItem";
			this->helloToolStripMenuItem->Size = System::Drawing::Size(181, 22);
			this->helloToolStripMenuItem->Text = L"Show Voltage";
			this->helloToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::helloToolStripMenuItem_Click);
			// 
			// baudRateToolStripMenuItem
			// 
			this->baudRateToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) {this->m_baudrate});
			this->baudRateToolStripMenuItem->Name = L"baudRateToolStripMenuItem";
			this->baudRateToolStripMenuItem->Size = System::Drawing::Size(152, 22);
			this->baudRateToolStripMenuItem->Text = L"BaudRate(bps)";
			// 
			// m_baudrate
			// 
			this->m_baudrate->Items->AddRange(gcnew cli::array< System::Object^  >(14) {L"300", L"600", L"1200", L"2400", L"4800", L"9600", 
				L"14400", L"19200", L"38400", L"57600", L"115200", L"230400", L"460800", L"921600"});
			this->m_baudrate->Name = L"m_baudrate";
			this->m_baudrate->Size = System::Drawing::Size(121, 23);
			this->m_baudrate->Text = L"9600";
			// 
			// helpToolStripMenuItem
			// 
			this->helpToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) {this->aboutToolStripMenuItem});
			this->helpToolStripMenuItem->Name = L"helpToolStripMenuItem";
			this->helpToolStripMenuItem->Size = System::Drawing::Size(44, 20);
			this->helpToolStripMenuItem->Text = L"Help";
			// 
			// aboutToolStripMenuItem
			// 
			this->aboutToolStripMenuItem->Name = L"aboutToolStripMenuItem";
			this->aboutToolStripMenuItem->Size = System::Drawing::Size(107, 22);
			this->aboutToolStripMenuItem->Text = L"About";
			this->aboutToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::aboutToolStripMenuItem_Click);
			// 
			// statusStrip1
			// 
			this->statusStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {this->toolStripStatusLabel1, 
				this->toolStripStatusLabel2});
			this->statusStrip1->Location = System::Drawing::Point(0, 401);
			this->statusStrip1->Name = L"statusStrip1";
			this->statusStrip1->Size = System::Drawing::Size(839, 22);
			this->statusStrip1->TabIndex = 5;
			this->statusStrip1->Text = L"statusStrip1";
			// 
			// toolStripStatusLabel1
			// 
			this->toolStripStatusLabel1->Name = L"toolStripStatusLabel1";
			this->toolStripStatusLabel1->Size = System::Drawing::Size(79, 17);
			this->toolStripStatusLabel1->Text = L"Disconnected";
			// 
			// toolStripStatusLabel2
			// 
			this->toolStripStatusLabel2->Name = L"toolStripStatusLabel2";
			this->toolStripStatusLabel2->Size = System::Drawing::Size(80, 17);
			this->toolStripStatusLabel2->Text = L"Card Voltage :";
			// 
			// richTextBox1
			// 
			this->richTextBox1->Dock = System::Windows::Forms::DockStyle::Fill;
			this->richTextBox1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->richTextBox1->Location = System::Drawing::Point(0, 24);
			this->richTextBox1->Name = L"richTextBox1";
			this->richTextBox1->Size = System::Drawing::Size(839, 377);
			this->richTextBox1->TabIndex = 6;
			this->richTextBox1->Text = L"";
			this->richTextBox1->Enter += gcnew System::EventHandler(this, &Form1::richTextBox1_TextChanged);
			this->richTextBox1->TextChanged += gcnew System::EventHandler(this, &Form1::richTextBox1_TextChanged);
			// 
			// pdupoll
			// 
			this->pdupoll->Interval = 1;
			this->pdupoll->Tick += gcnew System::EventHandler(this, &Form1::pduoll_Tick);
			// 
			// textBox1
			// 
			this->textBox1->Location = System::Drawing::Point(671, 3);
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(156, 20);
			this->textBox1->TabIndex = 7;
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(608, 6);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(57, 13);
			this->label1->TabIndex = 8;
			this->label1->Text = L"Frequency";
			// 
			// textBox2
			// 
			this->textBox2->Location = System::Drawing::Point(450, 3);
			this->textBox2->Name = L"textBox2";
			this->textBox2->Size = System::Drawing::Size(143, 20);
			this->textBox2->TabIndex = 9;
			this->textBox2->Visible = false;
			this->textBox2->TextChanged += gcnew System::EventHandler(this, &Form1::textBox2_TextChanged);
			// 
			// timer1
			// 
			this->timer1->Interval = 10;
			this->timer1->Tick += gcnew System::EventHandler(this, &Form1::timer1_Tick_1);
			// 
			// voltage
			// 
			this->voltage->Interval = 500;
			this->voltage->Tick += gcnew System::EventHandler(this, &Form1::voltage_Tick);
			// 
			// Form1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(839, 423);
			this->Controls->Add(this->textBox2);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->textBox1);
			this->Controls->Add(this->richTextBox1);
			this->Controls->Add(this->statusStrip1);
			this->Controls->Add(this->MainMenu);
			this->MainMenuStrip = this->MainMenu;
			this->MaximizeBox = false;
			this->Name = L"Form1";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"ciptascope 0.10b";
			this->Load += gcnew System::EventHandler(this, &Form1::Form1_Load);
			this->MainMenu->ResumeLayout(false);
			this->MainMenu->PerformLayout();
			this->statusStrip1->ResumeLayout(false);
			this->statusStrip1->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

private: System::Void timer1_Tick(System::Object^  sender, System::EventArgs^  e)  {
	FT_STATUS ftStatus;
	byte ucMask;
	byte index;
	DWORD RxBytes,i;
	DWORD BytesReceived,TotalBytesReceived; 
	char buffer[20];
	char RxBuffer[256];
	WORD baudbuf=0;

	ftStatus = FT_SetBitMode(ftHandle,0xCC,0x20);//11011100
	ftStatus = FT_GetBitMode(ftHandle, &ucMask);
	if (ftStatus != FT_OK) {
		
	}
	else
	{
		
		if (ucMask & 0x02){
		}
		else 
		{
			//pdupoll->Enabled="False";
			//set global index
			globalIndex =0;
			phase =1; //CLA
			assign =0;
			remaining=0;
			datalength = 0;
			updatebaudcounter = 0;
			//scanFrequencyToolStripMenuItem_Click(sender,e);
			//temp = 9600;
		
			//sprintf(&buffer[0], "%02d", temp);
			//textBox2->Text = gcnew String(buffer);
			FT_SetBaudRate(ftHandle, temp);//temp-300);//freqDataBuffer[0]*1000/372-300);
			FT_Purge (ftHandle, FT_PURGE_RX);
			//-----------------scan the frequency------------------//
			//counter =0;	//clear counter after reset
			//reset_low=1; //set flag for frequency timer sampling to work
			//timer1->Enabled="True"; //enable the timer
			//----------------------end---------------------------//
			RxBytes=0;

			HANDLE hEvent; 
			DWORD EventMask; 
			
			FT_SetChars (ftHandle, 0x3B, 1, NULL, NULL);

			hEvent = CreateEvent( NULL,false,false,NULL);
			EventMask = FT_EVENT_RXCHAR; 
			
			ftStatus = FT_SetEventNotification(ftHandle,EventMask,hEvent); 
			 
			//WaitForSingleObject(hEvent,INFINITE); 
			WaitForSingleObject(hEvent, 300); 
			DWORD EventDWord; 
			DWORD RxBytes; 
			DWORD TxBytes; 
			FT_GetStatus(ftHandle,&RxBytes,&TxBytes,&EventDWord); 

			
			TotalBytesReceived=0;
			if (RxBytes > 0) 
			{
				
				ftStatus = FT_Read(ftHandle, &RxBuffer[TotalBytesReceived], RxBytes, &BytesReceived);
				ftStatus = FT_Read(ftHandle, &RxBuffer[TotalBytesReceived], RxBytes, &BytesReceived);
			
				
				TotalBytesReceived+=BytesReceived;
				if (ftStatus == FT_OK) 
				{
					if(RxBuffer[0]==0x3B ||RxBuffer[0]==0x3F)
					//	if (RxBytes > 0) 
					{
						if(TotalBytesReceived==1)
						{
						//wait T0
							RxBytes=0;
							while(!RxBytes)
							{
								FT_GetQueueStatus(ftHandle, &RxBytes);
							}
							ftStatus = FT_Read(ftHandle, &RxBuffer[TotalBytesReceived], RxBytes, &BytesReceived);
							TotalBytesReceived+=BytesReceived;
						}
						//calculate atr length from T0
						unsigned char TOTAL_ATR_RECEIVED=TotalBytesReceived;
						unsigned char TCK_PRESENT=0;
						unsigned char TOTAL_ATR_LENGTH = 0;
						unsigned char T_LENTGH = (RxBuffer[1]&0x80)>>7; //TD1
						T_LENTGH += (RxBuffer[1]&0x40)>>6;	//TC1
						T_LENTGH += (RxBuffer[1]&0x20)>>5;	//TB1
						T_LENTGH += (RxBuffer[1]&0x10)>>4; //TA1
						
						TOTAL_ATR_LENGTH += (RxBuffer[1] & 0x0F) + 2;		//historical byte + TS + T0	
						if((RxBuffer[1] & 0x10) && TotalBytesReceived==((RxBuffer[1]&0x10)>>4)+1)
						{	//wait TA1
							RxBytes=0;
							while(!RxBytes)
							{
								FT_GetQueueStatus(ftHandle, &RxBytes);
							}
							ftStatus = FT_Read(ftHandle, &RxBuffer[TotalBytesReceived], RxBytes, &BytesReceived);
							TotalBytesReceived+=BytesReceived;
						}
						if((RxBuffer[1] & 0x20) && TotalBytesReceived==((RxBuffer[1]&0x10)>>4)+2)
						{	//wait TB1
							RxBytes=0;
							while(!RxBytes)
							{
								FT_GetQueueStatus(ftHandle, &RxBytes);
							}
							ftStatus = FT_Read(ftHandle, &RxBuffer[TotalBytesReceived], RxBytes, &BytesReceived);
							TotalBytesReceived+=BytesReceived;
						}
						if((RxBuffer[1] & 0x40) &&TotalBytesReceived== ((RxBuffer[1]&0x20)>>5)+((RxBuffer[1]&0x10)>>4)+2)
						{	//wait TC1
							RxBytes=0;
							while(!RxBytes)
							{
								FT_GetQueueStatus(ftHandle, &RxBytes);
							}
							ftStatus = FT_Read(ftHandle, &RxBuffer[TotalBytesReceived], RxBytes, &BytesReceived);
							TotalBytesReceived+=BytesReceived;
						}
						if(RxBuffer[1] & 0x80)
						{
							if(TotalBytesReceived==((RxBuffer[1]&0x40)>>6)+((RxBuffer[1]&0x20)>>5)+((RxBuffer[1]&0x10)>>4)+2)
							{	//wait TD1
								RxBytes=0;
								while(!RxBytes)
								{
									FT_GetQueueStatus(ftHandle, &RxBytes);
								}
								ftStatus = FT_Read(ftHandle, &RxBuffer[TotalBytesReceived], RxBytes, &BytesReceived);
								TotalBytesReceived+=BytesReceived;
							}
							//calculate atr length from TD1
							unsigned char TD1_POS=T_LENTGH + 1;
							T_LENTGH  += (RxBuffer[TD1_POS]&0x80)>>7; //TD2
							T_LENTGH  += (RxBuffer[TD1_POS]&0x40)>>6;	//TC2
							T_LENTGH  += (RxBuffer[TD1_POS]&0x20)>>5;	//TB2
							T_LENTGH  += (RxBuffer[TD1_POS]&0x10)>>4; //TA2
							
							if(RxBuffer[TD1_POS]&0x0F) TCK_PRESENT=1;
							//parsing TD1
							if((RxBuffer[TD1_POS] & 0x10) && TotalBytesReceived== TD1_POS + ((RxBuffer[TD1_POS]&0x10)>>4))
							{	//wait TA2
								RxBytes=0;
								while(!RxBytes)
								{
									FT_GetQueueStatus(ftHandle, &RxBytes);
								}
								ftStatus = FT_Read(ftHandle, &RxBuffer[TotalBytesReceived], RxBytes, &BytesReceived);
								TotalBytesReceived+=BytesReceived;
							}
							if((RxBuffer[TD1_POS] & 0x20) && TotalBytesReceived == TD1_POS + ((RxBuffer[TD1_POS]&0x10)>>4)+1)
							{	//wait TB2
								RxBytes=0;
								while(!RxBytes)
								{
									FT_GetQueueStatus(ftHandle, &RxBytes);
								}
								ftStatus = FT_Read(ftHandle, &RxBuffer[TotalBytesReceived], RxBytes, &BytesReceived);
								TotalBytesReceived+=BytesReceived;
							}
							if((RxBuffer[TD1_POS] & 0x40) &&TotalBytesReceived== TD1_POS +((RxBuffer[TD1_POS]&0x20)>>5)+((RxBuffer[TD1_POS]&0x10)>>4)+1)
							{	//wait TC2
								RxBytes=0;
								while(!RxBytes)
								{
									FT_GetQueueStatus(ftHandle, &RxBytes);
								}
								ftStatus = FT_Read(ftHandle, &RxBuffer[TotalBytesReceived], RxBytes, &BytesReceived);
								TotalBytesReceived+=BytesReceived;
							}
							if(RxBuffer[TD1_POS] & 0x80)
							{
								if(TotalBytesReceived==TD1_POS +((RxBuffer[TD1_POS]&0x40)>>6)+((RxBuffer[TD1_POS]&0x20)>>5)+((RxBuffer[TD1_POS]&0x10)>>4)+1)
								{	//wait TD2
									RxBytes=0;
									while(!RxBytes)
									{
										FT_GetQueueStatus(ftHandle, &RxBytes);
									}
									ftStatus = FT_Read(ftHandle, &RxBuffer[TotalBytesReceived], RxBytes, &BytesReceived);
									TotalBytesReceived+=BytesReceived;
								}
								//calculate atr length from TD2
								unsigned char TD2_POS=T_LENTGH + 1;
								T_LENTGH  += (RxBuffer[TD2_POS]&0x80)>>7; //TD3
								T_LENTGH  += (RxBuffer[TD2_POS]&0x40)>>6;	//TC3
								T_LENTGH  += (RxBuffer[TD2_POS]&0x20)>>5;	//TB3
								T_LENTGH  += (RxBuffer[TD2_POS]&0x10)>>4; //TA3
								
								if(RxBuffer[TD2_POS]&0x0F) TCK_PRESENT=1;
								//parsing TD2
								if((RxBuffer[TD2_POS] & 0x10) && TotalBytesReceived== TD2_POS + ((RxBuffer[TD2_POS]&0x10)>>4))
								{	//wait TA3
									RxBytes=0;
									while(!RxBytes)
									{
										FT_GetQueueStatus(ftHandle, &RxBytes);
									}
									ftStatus = FT_Read(ftHandle, &RxBuffer[TotalBytesReceived], RxBytes, &BytesReceived);
									TotalBytesReceived+=BytesReceived;
								}
								if((RxBuffer[TD2_POS] & 0x20) && TotalBytesReceived == TD2_POS + ((RxBuffer[TD2_POS]&0x10)>>4)+1)
								{	//wait TB3
									RxBytes=0;
									while(!RxBytes)
									{
										FT_GetQueueStatus(ftHandle, &RxBytes);
									}
									ftStatus = FT_Read(ftHandle, &RxBuffer[TotalBytesReceived], RxBytes, &BytesReceived);
									TotalBytesReceived+=BytesReceived;
								}
								if((RxBuffer[TD2_POS] & 0x40) &&TotalBytesReceived== TD2_POS +((RxBuffer[TD2_POS]&0x20)>>5)+((RxBuffer[TD2_POS]&0x10)>>4)+1)
								{	//wait TC3
									RxBytes=0;
									while(!RxBytes)
									{
										FT_GetQueueStatus(ftHandle, &RxBytes);
									}
									ftStatus = FT_Read(ftHandle, &RxBuffer[TotalBytesReceived], RxBytes, &BytesReceived);
									TotalBytesReceived+=BytesReceived;
								}
								if(RxBuffer[TD2_POS] & 0x80)
								{
									if(TotalBytesReceived==TD2_POS +((RxBuffer[TD2_POS]&0x40)>>6)+((RxBuffer[TD2_POS]&0x20)>>5)+((RxBuffer[TD2_POS]&0x10)>>4)+1)
									{	//wait TD3
										RxBytes=0;
										while(!RxBytes)
										{
											FT_GetQueueStatus(ftHandle, &RxBytes);
										}
										ftStatus = FT_Read(ftHandle, &RxBuffer[TotalBytesReceived], RxBytes, &BytesReceived);
										TotalBytesReceived+=BytesReceived;
									}
									//calculate atr length from TD3
									unsigned char TD3_POS=T_LENTGH + 1;
									T_LENTGH  += (RxBuffer[TD3_POS]&0x80)>>7; //TD4
									T_LENTGH  += (RxBuffer[TD3_POS]&0x40)>>6;	//TC4
									T_LENTGH  += (RxBuffer[TD3_POS]&0x20)>>5;	//TB4
									T_LENTGH  += (RxBuffer[TD3_POS]&0x10)>>4; //TA4
									
									if(RxBuffer[TD3_POS]&0x0F) TCK_PRESENT=1;
									//parsing TD3
									if((RxBuffer[TD3_POS] & 0x10) && TotalBytesReceived== TD3_POS + ((RxBuffer[TD3_POS]&0x10)>>4))
									{	//wait TA4
										RxBytes=0;
										while(!RxBytes)
										{
											FT_GetQueueStatus(ftHandle, &RxBytes);
										}
										ftStatus = FT_Read(ftHandle, &RxBuffer[TotalBytesReceived], RxBytes, &BytesReceived);
										TotalBytesReceived+=BytesReceived;
									}
									if((RxBuffer[TD3_POS] & 0x20) && TotalBytesReceived == TD3_POS + ((RxBuffer[TD3_POS]&0x10)>>4)+1)
									{	//wait TB4
										RxBytes=0;
										while(!RxBytes)
										{
											FT_GetQueueStatus(ftHandle, &RxBytes);
										}
										ftStatus = FT_Read(ftHandle, &RxBuffer[TotalBytesReceived], RxBytes, &BytesReceived);
										TotalBytesReceived+=BytesReceived;
									}
									if((RxBuffer[TD3_POS] & 0x40) &&TotalBytesReceived== TD3_POS +((RxBuffer[TD3_POS]&0x20)>>5)+((RxBuffer[TD3_POS]&0x10)>>4)+1)
									{	//wait TC4
										RxBytes=0;
										while(!RxBytes)
										{
											FT_GetQueueStatus(ftHandle, &RxBytes);
										}
										ftStatus = FT_Read(ftHandle, &RxBuffer[TotalBytesReceived], RxBytes, &BytesReceived);
										TotalBytesReceived+=BytesReceived;
									}
									if(RxBuffer[TD3_POS] & 0x80)
									{
										if(TotalBytesReceived==TD3_POS +((RxBuffer[TD3_POS]&0x40)>>6)+((RxBuffer[TD3_POS]&0x20)>>5)+((RxBuffer[TD3_POS]&0x10)>>4)+1)
										{	//wait TD4
											RxBytes=0;
											while(!RxBytes)
											{
												FT_GetQueueStatus(ftHandle, &RxBytes);
											}
											ftStatus = FT_Read(ftHandle, &RxBuffer[TotalBytesReceived], RxBytes, &BytesReceived);
											TotalBytesReceived+=BytesReceived;
										}
										//calculate atr length from TD4???
									}
								}
							}
						}
						//ATR LENGTH with T
						TOTAL_ATR_LENGTH += T_LENTGH;
						//ATR LENGTH with TCK present
						if(TCK_PRESENT)TOTAL_ATR_LENGTH +=1; 					

						//wait remaining ATR data  
						unsigned char Remaining_ATR = TOTAL_ATR_LENGTH-TotalBytesReceived;
						RxBytes=0;
						while(RxBytes<Remaining_ATR)
						{
							FT_GetQueueStatus(ftHandle, &RxBytes);
						}

						//----------set the baudrate according to frequency-----//
						index=0;//get the first one
						if (freqDataBuffer[index] <1000){
							sprintf(&buffer[0], "%02d", freqDataBuffer[index]*1000);//*1000 to get per second
							freqDataBuffer[index] = 3700;
						}
						else
							sprintf(&buffer[0], "%02d", freqDataBuffer[index]*1000);//*1000 to get per second
						textBox1->Text = gcnew String(buffer);
						
						
						baudbuf = freqDataBuffer[index]*1000 / 372;
						FT_SetBaudRate(ftHandle, baudbuf);//12674);	//set baudrate
						//FT_SetBaudRate(ftHandle, 12779);			
						//-----------------end of setting baud rate--------------//

						ftStatus = FT_Read(ftHandle, &RxBuffer[TotalBytesReceived], RxBytes, &BytesReceived);						
						//FT_Purge (ftHandle, FT_PURGE_RX);
						
						TotalBytesReceived+=BytesReceived;
						TOTAL_ATR_RECEIVED = TotalBytesReceived;
						//wait for PPS
						RxBytes=0;
						unsigned char TOTAL_PPS_LENGTH=0;
						unsigned char TOTAL_PPS_RECEIVED=0;
						TotalBytesReceived=0;
						hEvent = CreateEvent( NULL,false,false,NULL);
						FT_SetChars (ftHandle, 0xFF, 1, NULL, NULL);
						EventMask = FT_EVENT_RXCHAR; 
						ftStatus = FT_SetEventNotification(ftHandle,EventMask,hEvent); 
						WaitForSingleObject(hEvent,50); 
						FT_GetStatus(ftHandle,&RxBytes,&TxBytes,&EventDWord); 
						/*while(!RxBytes)
						{
							FT_GetQueueStatus(ftHandle, &RxBytes);
						}*/
						
						if (RxBytes > 0) 
						{
							ftStatus = FT_Read(ftHandle, &RxBuffer[TotalBytesReceived+32], RxBytes, &BytesReceived);
							TotalBytesReceived+=BytesReceived;
							
PPS_HANDLER:				if(RxBuffer[32]==(char)0xFF)
							{	
								//wait for pps0
								if(BytesReceived==1)
								{
									RxBytes=0;
									while(!RxBytes)
									{
										FT_GetQueueStatus(ftHandle, &RxBytes);
									}
									ftStatus = FT_Read(ftHandle, &RxBuffer[TotalBytesReceived+32], RxBytes, &BytesReceived);
									TotalBytesReceived+=BytesReceived;
								}
								//check pps1, pps2, pps3
								unsigned char PPS_LENGTH=((RxBuffer[33] & 0x40)>>6);
								PPS_LENGTH +=((RxBuffer[33] & 0x20)>>5);
								PPS_LENGTH +=((RxBuffer[33] & 0x10)>>4);
								TOTAL_PPS_LENGTH = (PPS_LENGTH+3);
								if(TotalBytesReceived<TOTAL_PPS_LENGTH)
								{
									RxBytes=0;
									while(RxBytes<(TOTAL_PPS_LENGTH-TotalBytesReceived))
									{
										FT_GetQueueStatus(ftHandle, &RxBytes);
									}
									ftStatus = FT_Read(ftHandle, &RxBuffer[TotalBytesReceived+32], RxBytes, &BytesReceived);
									TotalBytesReceived+=BytesReceived;
									//TODO expire timer if no pps response
									//wait for response pps from card
									if(TotalBytesReceived<(TOTAL_PPS_LENGTH*2))
									{
										RxBytes=0;									
										while(RxBytes<((TOTAL_PPS_LENGTH*2)-TotalBytesReceived))
										{
											FT_GetQueueStatus(ftHandle, &RxBytes);
										}

										if (RxBytes > 0){
											ftStatus = FT_Read(ftHandle, &RxBuffer[TotalBytesReceived+32], RxBytes, &BytesReceived);
											TotalBytesReceived+=BytesReceived;
										}
									}
									TOTAL_PPS_RECEIVED=TotalBytesReceived;
								}
								else
								{
									//if(BytesReceived < TOTAL_PPS_LENGTH*2)
									if(((TOTAL_PPS_LENGTH*2)-TotalBytesReceived)!=0)
									{
										//wait for last pps body
										RxBytes=0;
										while(RxBytes <((TOTAL_PPS_LENGTH*2)-TotalBytesReceived))
										{
											FT_GetQueueStatus(ftHandle, &RxBytes);
										}
										if (RxBytes > 0)
										{
											ftStatus = FT_Read(ftHandle, &RxBuffer[TotalBytesReceived+32], RxBytes, &BytesReceived);
											TotalBytesReceived+=BytesReceived;
										}
									}
									TOTAL_PPS_RECEIVED=TotalBytesReceived;
								}								
							}
							else
							{
								if(BytesReceived==1 && RxBuffer[32]==0x00)
								{
									RxBytes=0;
									TotalBytesReceived=0;
									
									while(RxBytes<TOTAL_ATR_RECEIVED)
									{
										FT_GetQueueStatus(ftHandle, &RxBytes);
									}
									
									if (RxBytes > 0) 
									{
										ftStatus = FT_Read(ftHandle, &RxBuffer[TotalBytesReceived+32], RxBytes, &BytesReceived);
										TotalBytesReceived+=BytesReceived;
									}
									i=0;
									for(i=0;i<TOTAL_ATR_RECEIVED;i++)
									{
										if(RxBuffer[i] != RxBuffer[32+i])
										{
											break;
										}		
									}
									if(i==TOTAL_ATR_RECEIVED)
									{
										RxBytes=0;
										TotalBytesReceived=0;
									
										while(!RxBytes)
										{
											FT_GetQueueStatus(ftHandle, &RxBytes);
										}
										if (RxBytes > 0) 
										{
											ftStatus = FT_Read(ftHandle, &RxBuffer[TotalBytesReceived+32], RxBytes, &BytesReceived);
											TotalBytesReceived+=BytesReceived;
											goto PPS_HANDLER;
										}
									}
								}
							}
						}
						else
						{

						}
						unsigned int baudrate;
						char hexStr[512];
						char sTmp[2];	

						array<Byte> ^chars = System::Text::Encoding::ASCII->GetBytes(m_FreqList->Text);
						pin_ptr<Byte> charsPointer = &(chars[0]);
						char *PChar = reinterpret_cast<char *>(static_cast<unsigned char *>(charsPointer));
						unsigned int f = freqDataBuffer[index]*1000;//atoi(PChar);
						baudrate = f/372;
						i=0;
						if(TOTAL_PPS_LENGTH *2 == TOTAL_PPS_RECEIVED)
						{
						//compare pps value
							for(i=0;i<TOTAL_PPS_LENGTH;i++)
							{
								if(RxBuffer[32+i] != RxBuffer[32+TOTAL_PPS_LENGTH+i])
								{
									break;
								}		
							}
						}
						//todo re-calculate baud rate if not macth with TA1 on PPS
						if(i==TOTAL_PPS_LENGTH && TOTAL_PPS_LENGTH)
						{
							unsigned int Fi = Fimap[(RxBuffer[34] & 0xF0) >> 4];
							unsigned char Di= Dimap[RxBuffer[34] & 0x0F];
							if(Fi ==0x00){
								baudrate =f*Di;
								richTextBox1->Text +="\n" +">>>> Fi=0" +"\n";
							}
							else{
								baudrate = f*Di/(Fi);
							}	
						}
						else if((RxBuffer[1]) & 0x10){	//T0
							unsigned int Fi = Fimap[(RxBuffer[2] & 0xF0) >> 4];
							unsigned char Di= Dimap[RxBuffer[2] & 0x0F];
								baudrate = f*Di/(Fi);							
						}
						//FT_ResetDevice(ftHandle);
						FT_SetChars (ftHandle, NULL, NULL, NULL, NULL);
						//FT_Purge (ftHandle, FT_PURGE_RX);
						//FT_SetDataCharacteristics(ftHandle, FT_BITS_8, FT_STOP_BITS_2, FT_PARITY_EVEN);
						ftStatus=FT_INVALID_BAUD_RATE;
						ftStatus = FT_SetBaudRate(ftHandle, baudrate);//59468+400); //baudrate);//59921+1000);// baudrate+200);
						//ftStatus = FT_SetDivisor(ftHandle,223.375);
						

						if (ftStatus == FT_OK) {
							itoa (baudrate,hexStr,10);
							m_baudrate->Text=(gcnew String(hexStr));
							//pdupoll->Enabled="True";
						}
						else
						{
							richTextBox1->Text +="\n" +">>>> Invalid Baudrate !!!" +"\n";
						}
						
						/*chars = System::Text::Encoding::ASCII->GetBytes(m_baudrate->Text);
						charsPointer = &(chars[0]);
						PChar = reinterpret_cast<char *>(static_cast<unsigned char *>(charsPointer));
						unsigned int Text_baudrate = atoi(PChar);
						while(baudrate!=Text_baudrate)
						{
							ftStatus=FT_INVALID_BAUD_RATE;
							ftStatus = FT_SetBaudRate(ftHandle, baudrate);
							if (ftStatus == FT_OK) 
							{
								itoa (baudrate,hexStr,10);
								m_baudrate->Text=(gcnew String(hexStr));
							}
						}*/

						for(i=0;i<512;i++){
							hexStr[i]=0x00;
						}

						for(i=0;i<TOTAL_ATR_RECEIVED;i++){
						sprintf(&sTmp[0], "%1X", (RxBuffer[i]& 0xF0) >> 4);
						sprintf(&sTmp[1], "%1X", (RxBuffer[i]& 0x0F));
						strcat(hexStr, sTmp);	
						}
						
						richTextBox1->Text +="\n" +">>>> Card Reset" +"\n";
						richTextBox1->Text +="ATR : " + gcnew String(hexStr) +"\n";
						if(TOTAL_ATR_RECEIVED!=TOTAL_ATR_LENGTH)
						{
							richTextBox1->Text +="ATR Length !!! " +"\n";
						}
						if(TOTAL_PPS_LENGTH)
						{
							for(i=0;i<512;i++){
								hexStr[i]=0x00;
							}
							for(i=0;i<(TOTAL_PPS_LENGTH);i++){
							sprintf(&sTmp[0], "%1X", (RxBuffer[32+i]& 0xF0) >> 4);
							sprintf(&sTmp[1], "%1X", (RxBuffer[32+i]& 0x0F));
							strcat(hexStr, sTmp);
							}
							richTextBox1->Text +="T_PPS : " + gcnew String(hexStr) +"\n";
							if(TOTAL_PPS_RECEIVED==(TOTAL_PPS_LENGTH*2))
							{
								for(i=0;i<512;i++){
									hexStr[i]=0x00;
								}
								for(i=0;i<(TOTAL_PPS_LENGTH);i++){
								sprintf(&sTmp[0], "%1X", (RxBuffer[32+TOTAL_PPS_LENGTH+i]& 0xF0) >> 4);
								sprintf(&sTmp[1], "%1X", (RxBuffer[32+TOTAL_PPS_LENGTH+i]& 0x0F));
								strcat(hexStr, sTmp);
								}
								richTextBox1->Text +="C_PPS : " + gcnew String(hexStr) +"\n";
							}
							else
							{
								richTextBox1->Text +="C_PPS : NONE"+"\n";
							}
						}
						else
						{
						}
						
					}
				}
			}

			//FT_GetQueueStatus(ftHandle, &RxBytes);
			//if (RxBytes > 0) {
			//	ftStatus = FT_Read(ftHandle, RxBuffer, RxBytes, &BytesReceived);
			//	if (ftStatus == FT_OK) {
			//		// FT_Read OK 
			//		char hexStr[512];
			//		char sTmp[2];
			//		unsigned int baudrate;
			//		for(i=0;i<512;i++){
			//			hexStr[i]=0x00;
			//		}
			//		for(i=0;i<BytesReceived;i++){
			//			if(RxBuffer[i]==0x3B ||RxBuffer[i]==0x3F){
			//				
			//				array<Byte> ^chars = System::Text::Encoding::ASCII->GetBytes(m_FreqList->Text);
			//				pin_ptr<Byte> charsPointer = &(chars[0]);
			//				char *PChar = reinterpret_cast<char *>(static_cast<unsigned char *>(charsPointer));
			//				unsigned int f = atoi(PChar);

			//				baudrate = f/372;
			//				if((RxBuffer[i+1]) & 0x10){	//T0
			//					unsigned int Fi = Fimap[(RxBuffer[i+2] & 0xF0) >> 4];
			//					unsigned char Di= Dimap[RxBuffer[i+2] & 0x0F];
			//					baudrate = f/(Fi/Di);
			//					
			//				}
			//				for(;i<BytesReceived;i++){
			//					sprintf(&sTmp[0], "%1X", (RxBuffer[i]& 0xF0) >> 4);
			//					sprintf(&sTmp[1], "%1X", (RxBuffer[i]& 0x0F));
			//					strcat(hexStr, sTmp);
			//					
			//				}
			//				break;
			//			}
			//		}
			//		richTextBox1->Text +="\n" +">>>> Card Reset" +"\n";
			//		richTextBox1->Text +="ATR : " + gcnew String(hexStr) +"\n";
			//		ftStatus = FT_SetBaudRate(ftHandle, baudrate);
			//		///ftStatus = FT_SetDivisor(ftHandle,223.375);
			//		if (ftStatus == FT_OK) {
			//			itoa (baudrate,hexStr,10);
			//			m_baudrate->Text=(gcnew String(hexStr));
			//			pdupoll->Enabled="True";
			//		}
			//	}
			else 
			{
				// FT_Read Failed
			}
			//}
			//Sleep(1000);
			//pdupoll->Enabled="True";
			counter=0;
		}
	}
}

private: System::Void frequencyToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
	 }
private: System::Void Form1_Load(System::Object^  sender, System::EventArgs^  e) {
		}
private: System::Void openToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
		char * PChar;
		FT_STATUS ftStatus;
		//byte ucMask;
		if(m_devlist->Text !="Select Device"){
			array<Byte> ^chars = System::Text::Encoding::ASCII->GetBytes(m_devlist->Text);
			pin_ptr<Byte> charsPointer = &(chars[0]);
			PChar = reinterpret_cast<char *>(static_cast<unsigned char *>(charsPointer));
			
			if (PChar != NULL) {
				// Open device
				ftStatus = FT_OpenEx(PChar, FT_OPEN_BY_SERIAL_NUMBER, &ftHandle);
				if (ftStatus == FT_OK) {
					// FT_Open OK 
					toolStripStatusLabel1->Text="Connected : " + m_devlist->Text;
					FT_SetDataCharacteristics(ftHandle, FT_BITS_8, FT_STOP_BITS_2, FT_PARITY_EVEN);
					FT_SetLatencyTimer (ftHandle, 2);
					FT_SetUSBParameters (ftHandle, 65535, 65535);
					array<Byte> ^chars = System::Text::Encoding::ASCII->GetBytes(m_baudrate->Text);
					pin_ptr<Byte> charsPointer = &(chars[0]);
					char *PChar = reinterpret_cast<char *>(static_cast<unsigned char *>(charsPointer));
					unsigned int baudrate = atoi(PChar);
					ftStatus = FT_SetBaudRate(ftHandle, baudrate);
					FT_Purge (ftHandle, FT_PURGE_RX);
					FT_Purge (ftHandle, FT_PURGE_TX);
					//freqDataBuffer[4] = 0x12bc;
					//FT_SetTimeouts (ftHandle,5000,5000);
					//FT_SetResetPipeRetryCount (ftHandle,100);
					//FT_SetDeadmanTimeout (ftHandle,6000);
					//set SS to HIGH,0b11001100
					ftStatus = FT_SetBitMode(ftHandle, 0xCC,0x20);
					ftStatus = FT_SetBaudRate(ftHandle, 10000);
					CardResetPoll->Enabled="True";
					pdupoll->Enabled="True";
					timer1->Enabled="True"; //enable the timer
					counter = 0;
					//voltage->Enabled="True";
				}
				else {
					// FT_Open Failed
				}
			}
		}
		else {
		
		}
	}
private: System::Void scanToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {

	FT_STATUS ftStatus;
	DWORD NumDevs;
	DWORD RCount;
	DWORD count;

	FT_DEVICE_LIST_INFO_NODE *DevInfo;
	FT_DEVICE_LIST_INFO_NODE *RDevsInfo;
	
	m_devlist->Items->Clear();
	// Get number of devices connected
	ftStatus = FT_CreateDeviceInfoList(&NumDevs);
	// Allocate storage
	DevInfo = (FT_DEVICE_LIST_INFO_NODE*)malloc(sizeof(FT_DEVICE_LIST_INFO_NODE)*NumDevs);
	// Get device list
	ftStatus = FT_GetDeviceInfoList(DevInfo,&NumDevs);
	// Get number of FT232R devices
	RCount = 0;
	for (count = 0; count < NumDevs; count++ ) {
		if (DevInfo[count].Type == 5) {
			RCount = RCount + 1;
			};
		}
	// Ensure at least 1 R chip available.  If not, show dialog
	if (RCount == 0) {
		MessageBox::Show("No FT232R or FT245R devices found.","Error", MessageBoxButtons::OK,MessageBoxIcon::Exclamation);
	}
	else {
		// Allocate storage for R chips
		RDevsInfo = (FT_DEVICE_LIST_INFO_NODE*)malloc(sizeof(FT_DEVICE_LIST_INFO_NODE)*RCount);
		// Get R chip device list
		RCount = 0;
		for (count = 0; count < NumDevs; count++ ) {
			if (DevInfo[count].Type = 6) {
				RDevsInfo[RCount] = DevInfo[count];
				RCount = RCount + 1;
				};
			}
		// Populate combobox
		for (count = 0; count < NumDevs; count++ ) {
			String ^tempstr= gcnew String(DevInfo[count].SerialNumber);//Description);
			m_devlist->Items->Add(tempstr);
			}
		// Free storage
		free(DevInfo);	
		free(RDevsInfo);
	}
}
private: System::Void closeToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
	FT_STATUS ftStatus;
	// Close device handle
	ftStatus = FT_Close(ftHandle);
	if (ftStatus == FT_OK) {
		// FT_Close OK 
		toolStripStatusLabel1->Text="Disconnected";
		CardResetPoll->Enabled="False";
		pdupoll->Enabled="False";
	}
	else {
		// FT_Close Failed
	}
}
private: System::Void exitToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
			exit(0);	 
		 }
private: System::Void pduoll_Tick(System::Object^  sender, System::EventArgs^  e)  {
	FT_STATUS ftStatus;	
	byte ucMask;
	DWORD RxBytes,i;
	DWORD BytesReceived; 
	char RxBuffer[1024];
	unsigned char CLA, INS, P1, P2, P3, ACK;
	unsigned char DT[256];
			for(i=0;i<1024;i++){
					RxBuffer[i]=0x00;
				}
			RxBytes=0;
			 //update baudrate counter
				/*updatebaudcounter++;
				if(updatebaudcounter >100){
					updatebaudcounter = 0;
					scanFrequencyToolStripMenuItem_Click(sender,e);
					//temp = freqDataBuffer[0]*1000/372;
					if(freqDataBuffer[0] > 3800){
						temp = 10000;
					}
					else {
						temp =9600;
					}
				}*/
			FT_GetQueueStatus(ftHandle, &RxBytes);
			if (RxBytes > 0) {
				ftStatus = FT_Read(ftHandle, RxBuffer, RxBytes, &BytesReceived);
				if (ftStatus == FT_OK) {
					// FT_Read OK 
					char hexStr[2500];
					char sTmp[256];
					for(i=0;i<2500;i++){
						hexStr[i]=0x00;
					}
					globalIndex=0;
					richTextBox1->SelectionStart = richTextBox1->Text->Length;
					richTextBox1->ScrollToCaret();
					//================= show data from buffer ===================//
						/*for(i=0;i<BytesReceived;i++){
							sprintf(&sTmp[0], "%02X",RxBuffer[i] & 0xFF);
							strcat(hexStr, sTmp);
						
						}
						sprintf(&sTmp[0], "\n");
						strcat(hexStr, sTmp);*/ 
					//=====================end of showing data from buffer ===========//
						if((0x3B ==RxBuffer[0] & 0xFF)){
							BytesReceived =0;
						}
					//============================= parsing =====================//
					while((BytesReceived > 0) && (BytesReceived <0x400)){
						if(phase == 1){ //CLA
							assign =5;
							if((BytesReceived <assign) && (remaining ==0)){
								remaining = assign-BytesReceived; //remaining =2
								assign = BytesReceived; //assign = 3
								//0 <= x < assign
								start = 0;
								stop = assign;
								phase =1;
							}
							else{
								if(remaining >0){
									assign =remaining;
									//5-remaining <= x < 5
									start = 5- remaining;
									stop = 5;
								}
								else{
									assign = 5;
									start = 0;
									stop =assign;
								}
								remaining = 0;
								phase++;
							}
							for(i=start;i<stop;i++){
								switch (i){
									case 0 : sprintf(&sTmp[0], "\nTerminal : \n  CLA : %02X\n",RxBuffer[globalIndex++] & 0xFF);
												strcat(hexStr, sTmp); break;
									case 1 : INSBefore =RxBuffer[globalIndex++] & 0xFF;
												sprintf(&sTmp[0], "   INS : %02X\n", INSBefore);
												strcat(hexStr, sTmp); break;
									case 2 : sprintf(&sTmp[0], "   P1 : %02X\n", RxBuffer[globalIndex++] & 0xFF);
												strcat(hexStr, sTmp); break;
									case 3 : sprintf(&sTmp[0], "   P2 : %02X\n", RxBuffer[globalIndex++] & 0xFF);
												strcat(hexStr, sTmp); break;
									case 4 : 
										datalength = RxBuffer[globalIndex++] & 0xFF;
										sprintf(&sTmp[0], "   P3 : %02X\n", datalength );
												
												strcat(hexStr, sTmp);
												if(datalength > 0x00){
													phase = 2;
												}
												else{
													phase = 4;
												}break;
									default : break;}
							}
							
							
							
						}
						else if (phase == 2){ //ACK
							assign =1;
							ACK = RxBuffer[globalIndex++] & 0xFF;
							if(ACK == INSBefore){
							sprintf(&sTmp[0], "Card:\n  ACK : %02X\n", ACK);
							strcat(hexStr, sTmp);
							phase++;
							}
							else{
								assign =2;
								sprintf(&sTmp[0], "Card:\n SW : ");
								strcat(hexStr, sTmp);
								globalIndex--;
								for(i=0;i<assign;i++){
									DT[i] = RxBuffer[globalIndex++] &0xFF;
									sprintf(&sTmp[0], "%02X", DT[i]);
									strcat(hexStr, sTmp);
								}
								sprintf(&sTmp[0], "\n");
							strcat(hexStr, sTmp);
								phase =1;
							}
						}
						else if(phase == 3){ //DATA
							if(remaining==0){
								sprintf(&sTmp[0], "T/C Data : ");
								strcat(hexStr, sTmp);
							}
							if((datalength > BytesReceived) && (remaining ==0)){
								assign = BytesReceived;
								remaining = datalength-BytesReceived;
								phase= 3;
							}
							else{
								if(remaining >0){
									if(remaining > BytesReceived){
										assign = BytesReceived;
										remaining = remaining - BytesReceived;
										phase=3;
									}
									else{
										assign =remaining;
										remaining =0;
										phase++;
									}
								}
								else{
									assign = datalength;
									remaining =0;
									phase++;
								}
							}
							for(i=0;i<assign;i++){
								DT[i] = RxBuffer[globalIndex++] &0xFF;
								sprintf(&sTmp[0], "%02X", DT[i]);
								strcat(hexStr, sTmp);
							}
							sprintf(&sTmp[0], "\n");
							strcat(hexStr, sTmp);
							
						}
						else if(phase == 4){ //SW
							if(remaining==0){
								sprintf(&sTmp[0], "Card\n SW : ");
								strcat(hexStr, sTmp);
							}
							if((2 > BytesReceived) && (remaining ==0)){
								remaining = 2-BytesReceived;
								assign = BytesReceived;
								phase= 4;
							}
							else{
								if(remaining >0){
									assign =remaining;
								}
								else{
									assign = 2;
								}
								remaining = 0;
								phase=1;
							}
							for(i=0;i<assign;i++){
								DT[i] = RxBuffer[globalIndex++] &0xFF;
								sprintf(&sTmp[0], "%02X", DT[i]);
								strcat(hexStr, sTmp);
							}
							sprintf(&sTmp[0], "\n");
							strcat(hexStr, sTmp);
						}
						else {
							assign = BytesReceived;
						}
						BytesReceived-= assign;
					}
					//======================end of parsing ========================//
					richTextBox1->Text += gcnew String(hexStr);
				}
			}
			

		 }
private: System::Void cleanToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {

			 richTextBox1->Clear();
		 }
private: System::Void deviceToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
		 }
private: System::Void richTextBox1_TextChanged(System::Object^  sender, System::EventArgs^  e) {
			richTextBox1->SelectionStart = richTextBox1->Text->Length;
					richTextBox1->ScrollToCaret();
		 }
private: System::Void m_FreqList_Click(System::Object^  sender, System::EventArgs^  e) {
		 }
private: System::Void scanFrequencyToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
		FT_STATUS ftStatus;	
		byte ucMask,i,mask;
		DWORD RxBytes;
		DWORD BytesReceived;
		WORD data = 0x55;
		char buffer[10];
			//tes baca byte
		
		//set SS to HIGH (active low) and MISO to low (input)
		//////setbit CBUS to 0b11001100
		ftStatus = FT_SetBitMode(ftHandle, 0xCC,0x20);
		//set SCK to LOW (setdtr, active low)
		ftStatus = FT_SetDtr(ftHandle);
		//set MOSI to low (setRts, active low)
		ftStatus = FT_SetRts(ftHandle);
		

		/////start reading byte 
		//set SS to low (CBUS to 0b11001000)
		ftStatus = FT_SetBitMode(ftHandle, 0xC8,0x20);
		//get MISO status
		for(i = 0;i<8;i++){
			ftStatus = FT_GetBitMode(ftHandle, &ucMask);
			mask = (ucMask & 0x01);
			data = (data << 1) | mask;
			//do clock
			//set SCK to HIGH (clrdtr)
			ftStatus = FT_ClrDtr(ftHandle);
			//set SCK to LOW (setdtr)
			ftStatus = FT_SetDtr(ftHandle);
		}
			//set SS to HIGH,0b11001100
			ftStatus = FT_SetBitMode(ftHandle, 0xCC,0x20);
			/////start reading byte 
		//set SS to low (CBUS to 0b11001000)
		ftStatus = FT_SetBitMode(ftHandle, 0xC8,0x20);
		//get MISO status
		for(i = 0;i<8;i++){
			ftStatus = FT_GetBitMode(ftHandle, &ucMask);
			mask = (ucMask & 0x01);
			data = (data << 1) | mask;
			//do clock
			//set SCK to HIGH (clrdtr)
			ftStatus = FT_ClrDtr(ftHandle);
			//set SCK to LOW (setdtr)
			ftStatus = FT_SetDtr(ftHandle);
		}
			//set SS to HIGH,0b11001100
			ftStatus = FT_SetBitMode(ftHandle, 0xCC,0x20);
			freqDataBuffer[counter] = data;
			/*if(counter ==0){
				sprintf(&buffer[0], "%02d", data*1000);
				textBox2->Text = gcnew String(buffer);
			}*/ 
			sprintf(&buffer[0], "%02d", data*1000);
			textBox1->Text = gcnew String(buffer);
		}
private: System::Void MainMenu_ItemClicked(System::Object^  sender, System::Windows::Forms::ToolStripItemClickedEventArgs^  e) {
		 }
private: System::Void clearToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
				FT_STATUS ftStatus;			
			 ftStatus = FT_ClrDtr(ftHandle);
			 ftStatus = FT_ClrRts(ftHandle);
		 }
private: System::Void helloToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
		FT_STATUS ftStatus;	
		byte ucMask,i,mask;
		DWORD RxBytes;
		DWORD BytesReceived;
		WORD data = 0x55;
		char buffer[10];
		voltage->Enabled="True";
		
		}

private: System::Void timer1_Tick_1(System::Object^  sender, System::EventArgs^  e) {
			 FT_STATUS ftStatus;	
			 byte ucMask,i,mask;
			/* if(counter<60{)
				 if(reset_low){
					//helloToolStripMenuItem_Click(sender,e);
					scanFrequencyToolStripMenuItem_Click(sender,e);
					counter++;
				}
			 }
			 else
			 {
				reset_low=0;
				counter =0;
				timer1->Enabled="False";
			 }*/
			 //scanFrequencyToolStripMenuItem_Click(sender,e);
			 ftStatus = FT_GetBitMode(ftHandle, &ucMask);
			 mask = (ucMask & 0x01) &&(ucMask & 0x04); //MISO ==1 and SS == 1
			 if(mask && (counter==0)){
				scanFrequencyToolStripMenuItem_Click(sender,e);
				//temp = freqDataBuffer[0]*1000/372;
				if(freqDataBuffer[0] > 3800){
					temp = 10000;
				}
				else {
					temp =9600;
				}
				counter=1;
			 }
		 }
private: System::Void printFreqBufferToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
			char buffer[10];
			richTextBox1 ->Clear();
			 for(int i=0;i<60;i++)
			{
				sprintf(&buffer[0], "%02x", freqDataBuffer[i]);
				richTextBox1->Text += gcnew String(buffer) + "\n";
			}
		 }
private: System::Void textBox2_TextChanged(System::Object^  sender, System::EventArgs^  e) {
		 }
private: System::Void m_devlist_Click(System::Object^  sender, System::EventArgs^  e) {
		 }
private: System::Void saveFile(void){
			 // Create a SaveFileDialog to request a path and file name to save to.
      SaveFileDialog^ saveFile1 = gcnew SaveFileDialog;

      // Initialize the SaveFileDialog to specify the RTF extention for the file.
      saveFile1->DefaultExt = "*.txt";
      saveFile1->Filter = "TXT Files|*.txt";

      // Determine whether the user selected a file name from the saveFileDialog. 
      if ( saveFile1->ShowDialog() == System::Windows::Forms::DialogResult::OK &&
         saveFile1->FileName->Length > 0 )
      {
         // Save the contents of the RichTextBox into the file.
         richTextBox1->SaveFile( saveFile1->FileName,RichTextBoxStreamType::PlainText );
      }
		 }
private: System::Void voltage_Tick(System::Object^  sender, System::EventArgs^  e) {
		FT_STATUS ftStatus;	
		byte ucMask,i,mask;
		byte data = 0x55;
		char buffer[30];
			 //ask for voltage data
			command =0x51; // this command to ask the voltage data
			byte command_array[8]; //command in bit array
			byte index; //bit
			// baca byte
		
		//============set command byte to command bit ==========//
			for(index=0;index<8;index++){
				command_array[index] = (command >> 7-index) & 0x01;
			}

		//set SS to HIGH (active low) and MISO to low (input)
		//////setbit CBUS to 0b1101100
		ftStatus = FT_SetBitMode(ftHandle, 0xCC,0x20);
		
		//set SCK to LOW (setdtr, active low)
		ftStatus = FT_SetDtr(ftHandle);
		
		/////start reading byte 
		//set SS to low (CBUS to 0b11001000)
		ftStatus = FT_SetBitMode(ftHandle, 0xC8,0x20);
		//set MOSI to low (setRts, active low)
		ftStatus = FT_SetRts(ftHandle);
		for(i = 0;i<8;i++){
			ftStatus = FT_GetBitMode(ftHandle, &ucMask);
			mask = (ucMask & 0x01);
			data = (data << 1) | mask;
			//set MOSI
			if(command_array[i] >0x00){
				ftStatus = FT_ClrRts(ftHandle);
			}
			else{
				ftStatus = FT_SetRts(ftHandle);
			}
			//Sleep(10);
			//do clock
			//set SCK to HIGH (clrdtr)
			ftStatus = FT_ClrDtr(ftHandle);
			//set SCK to LOW (setdtr)
			ftStatus = FT_SetDtr(ftHandle);
		}
			ftStatus = FT_SetRts(ftHandle);
			//set SS to HIGH,0b11001100
			ftStatus = FT_SetBitMode(ftHandle, 0xCC,0x20);
		
		//set SCK to LOW (setdtr, active low)
		ftStatus = FT_SetDtr(ftHandle);
		
		/////start reading byte 
		//set SS to low (CBUS to 0b11001000)
		ftStatus = FT_SetBitMode(ftHandle, 0xC8,0x20);
		//set MOSI to low (setRts, active low)
		ftStatus = FT_SetRts(ftHandle);
		for(i = 0;i<8;i++){
			ftStatus = FT_GetBitMode(ftHandle, &ucMask);
			mask = (ucMask & 0x01);
			data = (data << 1) | mask;
			//set MOSI ->0
				ftStatus = FT_SetRts(ftHandle);
			//Sleep(10);
			//do clock
			//set SCK to HIGH (clrdtr)
			ftStatus = FT_ClrDtr(ftHandle);
			//set SCK to LOW (setdtr)
			ftStatus = FT_SetDtr(ftHandle);
		}
			ftStatus = FT_SetRts(ftHandle);
			//set SS to HIGH,0b11001100
			ftStatus = FT_SetBitMode(ftHandle, 0xCC,0x20);
			/*if((data > 25) && (counter==0)){
				if(freqDataBuffer[0] < 1000){
				scanFrequencyToolStripMenuItem_Click(sender,e);
				}
				else{
					counter=1;
					voltage->Enabled="False";
				}
			}*/ 
			sprintf(&buffer[0], "Card Voltage : %02d mV", 600+(2*data*5060/256)); //ref voltage :5090mV
			toolStripStatusLabel2->Text = gcnew String(buffer);
		 }
private: System::Void aboutToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
			
		 }
private: System::Void saveAsToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
			 saveFile();
		 }
private: System::Void openLogFileToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
			  // Create an OpenFileDialog to request a file to open.
      OpenFileDialog^ openFile1 = gcnew OpenFileDialog;

      // Initialize the OpenFileDialog to look for RTF files.
      openFile1->DefaultExt = "*.txt";
      openFile1->Filter = "TXT Files|*.txt";

      // Determine whether the user selected a file from the OpenFileDialog.
      if ( openFile1->ShowDialog() == System::Windows::Forms::DialogResult::OK &&
         openFile1->FileName->Length > 0 )
      {
         // Load the contents of the file into the RichTextBox.
         richTextBox1->LoadFile( openFile1->FileName,RichTextBoxStreamType::PlainText );
      }
		 }
};
}

