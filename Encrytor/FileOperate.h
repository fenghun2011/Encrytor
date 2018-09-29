#pragma once
#include "Encrytor.h"
#include "QLabel"
#include "QLineEdit"
#define VERSION "¿¡»Àº”√‹ Released V1.0.2"
class subWidget
{
public:
	subWidget();
	~subWidget();
public:
	QVBoxLayout * verticalLayout;
	QWidget *centerwidget;
	QLabel* label;
	QPushButton *pushbutton;
};
class encWidget
{
public:
	encWidget();
	~encWidget();
public:
	QVBoxLayout * verticalLayout;
	QWidget *centerwidget;
	QLabel* label;
	QPushButton *pushbutton;
	QLineEdit *lineEdit;
};
class FileOperate : public Encrytor
{
public:
	FileOperate();
	~FileOperate();
public:
	void OpenFile();
	void SaveFile();
	void SetFileName(QString name);
	void EncrytFile();
	void DncrytFile();
	void DoEncrytFile();
	void DoDncrytFile();
	QString GetFileName();
	void about();
	void help();
	void error(QString msg);
	void changelog();
	void Play();
	void Pause();
public:
	static FileOperate* Instance();
	static void SendInfo(QString info1, QString info2=0);
	class PriviteData;
private:
	PriviteData * m_Data;
};

