#include "Encrytor.h"
#include <QtWidgets/QApplication>
#include "FileOperate.h"
#include "QDialog"
#include <QAction>
#include "QPushButton"
#include "QWidget"
#include "QMessageBox"
#include "QIcon"
#include "QTextCodec"
#include <QPalette> 
#include <QMediaPlayer>
int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

	a.setWindowIcon(QIcon(":/Encrytor/Resources/icon.ico"));
	FileOperate::Instance()->setWindowTitle(QString::fromLocal8Bit("懒人加密"));
	FileOperate::SendInfo(QString::fromLocal8Bit("**************************************************************"));
	FileOperate::SendInfo(QString::fromLocal8Bit("                            懒人加密                           "));
	                       FileOperate::SendInfo("                Build time:", __TIMESTAMP__);
	FileOperate::SendInfo(QString::fromLocal8Bit("**************************************************************"));
	
	FileOperate::Instance()->setWindowIcon(QIcon(":/Encrytor/Resources/icon.ico"));
	FileOperate::Instance()->ui.actionOpen->setText(QString::fromLocal8Bit("打开..."));
	FileOperate::Instance()->ui.actionOpen->setIcon(QIcon(":/Encrytor/Resources/open.ico"));
	FileOperate::Instance()->ui.actionHelp->setText(QString::fromLocal8Bit("帮助..."));
	FileOperate::Instance()->ui.actionHelp->setIcon(QIcon(":/Encrytor/Resources/help.ico"));
	FileOperate::Instance()->ui.actionAbout->setText(QString::fromLocal8Bit("关于..."));
	FileOperate::Instance()->ui.actionAbout->setIcon(QIcon(":/Encrytor/Resources/about.ico"));
	FileOperate::Instance()->ui.actionClose->setText(QString::fromLocal8Bit("关闭"));
	FileOperate::Instance()->ui.actionClose->setIcon(QIcon(":/Encrytor/Resources/closeico.ico"));
	FileOperate::Instance()->ui.actionChangelog->setText(QString::fromLocal8Bit("更新历史"));
	FileOperate::Instance()->ui.actionChangelog->setIcon(QIcon(":/Encrytor/Resources/changelog.ico"));

	QWidget::connect(FileOperate::Instance()->ui.actionOpen, &QAction::triggered, FileOperate::Instance(), &FileOperate::OpenFile);
	QWidget::connect(FileOperate::Instance()->ui.pushButton, &QAbstractButton::clicked, FileOperate::Instance(), &FileOperate::OpenFile);
	QWidget::connect(FileOperate::Instance()->ui.actionAbout, &QAction::triggered, FileOperate::Instance(), &FileOperate::about);
	QWidget::connect(FileOperate::Instance()->ui.actionHelp, &QAction::triggered, FileOperate::Instance(), &FileOperate::help);
	QWidget::connect(FileOperate::Instance()->ui.actionClose, &QAction::triggered, FileOperate::Instance(), &QDialog::close);
	QWidget::connect(FileOperate::Instance()->ui.pushButton_2, &QAbstractButton::clicked, FileOperate::Instance(), &FileOperate::EncrytFile);
	QWidget::connect(FileOperate::Instance()->ui.pushButton_3, &QAbstractButton::clicked, FileOperate::Instance(), &FileOperate::DncrytFile);
	QWidget::connect(FileOperate::Instance()->ui.actionChangelog, &QAction::triggered, FileOperate::Instance(), &FileOperate::changelog);
	FileOperate::Instance()->show();
	return a.exec();
}
