#include "FileOperate.h"
#include "QFileDialog"
#include "QMessageBox"
#include "QFile"
#include "QFileInfo"
#include "QByteArray"
#include "QThread"
#include "QString"
#include "QDir"
#include "QMediaPlayer"
class FileOperate::PriviteData
{
public:
	QString m_Name;
	encWidget enc;
	encWidget dnc;
	subWidget about; 
	subWidget help;
	subWidget error;
	QMessageBox msgbox;
	QFile *filestream;
	QMediaPlayer player;
};
FileOperate::FileOperate()
{
	m_Data = new PriviteData;
	m_Data->filestream = nullptr;
	QDialog::connect(m_Data->dnc.pushbutton, &QAbstractButton::clicked, this, &FileOperate::DoDncrytFile);
	m_Data->dnc.centerwidget->setWindowIcon(QIcon(":/Encrytor/Resources/dnteyt.ico"));
	QDialog::connect(m_Data->enc.pushbutton, &QAbstractButton::clicked, this, &FileOperate::DoEncrytFile);
	QDialog::connect(ui.pushButton_4, &QAbstractButton::clicked, this, &FileOperate::Pause);
	m_Data->enc.centerwidget->setWindowIcon(QIcon(":/Encrytor/Resources/entryt.ico"));

	m_Data->player.setMedia(QUrl("qrc:/Encrytor/Resources/KeilGenericKeygen-EDGE.mp3"));
	m_Data->player.setVolume(100);
	m_Data->player.play();
}
FileOperate::~FileOperate()
{
	delete m_Data;
}

void FileOperate::OpenFile()
{
	
	m_Data->m_Name = QFileDialog::getOpenFileName(ui.centralWidget, QString::fromLocal8Bit("打开一个加密或密码文件"), ".",
		QString::fromLocal8Bit("加密文件(*.Enc);;密码文件(*.Dnc);;所有文件(*.*)"));
	if (!m_Data->m_Name.isEmpty())
	{
		SetFileName(m_Data->m_Name);
		FileOperate::SendInfo(QString::fromLocal8Bit("打开文件："), m_Data->m_Name);
	}
	
}

void FileOperate::SaveFile()
{
}

void FileOperate::SetFileName(QString name)
{
	m_Data->m_Name = name;
	ui.lineEdit->setText(name);
}

void FileOperate::EncrytFile()
{
	m_Data->enc.centerwidget->setWindowTitle(QString::fromLocal8Bit("加密"));
	m_Data->enc.centerwidget->resize(225, 125);
	m_Data->enc.label->setText(QString::fromLocal8Bit("请输入密码："));
	m_Data->enc.lineEdit->clear();
	if (m_Data->m_Name.isEmpty())
	{
		m_Data->msgbox.setWindowIcon(QIcon(":/Encrytor/Resources/entryt.ico"));
		m_Data->msgbox.setWindowTitle(QString::fromLocal8Bit("文件错误"));
		m_Data->msgbox.setInformativeText(QString::fromLocal8Bit("文件名无效或路径错误"));
		m_Data->msgbox.setIcon(QMessageBox::Critical);
		m_Data->msgbox.setStandardButtons(QMessageBox::Ok);
		m_Data->msgbox.setButtonText(QMessageBox::Ok, QString::fromLocal8Bit("确定"));
		m_Data->msgbox.exec();
		FileOperate::SendInfo(QString::fromLocal8Bit("错误："), QString::fromLocal8Bit("加密前未选择有效的文件"));
	}
	else
	{
		m_Data->enc.centerwidget->show();
	}
	
}

void FileOperate::DncrytFile()
{
	m_Data->dnc.centerwidget->setWindowTitle(QString::fromLocal8Bit("解密"));
	m_Data->dnc.centerwidget->resize(225, 125);
	m_Data->dnc.label->setText(QString::fromLocal8Bit("请输入密码："));
	m_Data->dnc.lineEdit->clear();
	if (m_Data->m_Name.isEmpty())
	{
		m_Data->msgbox.setWindowIcon(QIcon(":/Encrytor/Resources/dnteyt.ico"));
		m_Data->msgbox.setWindowTitle(QString::fromLocal8Bit("文件错误"));
		m_Data->msgbox.setInformativeText(QString::fromLocal8Bit("文件名无效或路径错误"));
		m_Data->msgbox.setIcon(QMessageBox::Critical);
		m_Data->msgbox.setStandardButtons(QMessageBox::Ok);
		m_Data->msgbox.setButtonText(QMessageBox::Ok, QString::fromLocal8Bit("确定"));
		m_Data->msgbox.exec();
		FileOperate::SendInfo(QString::fromLocal8Bit("错误："), QString::fromLocal8Bit("解密前未选择有效的文件"));
	}
	else
	{
		m_Data->dnc.centerwidget->show();
	}
}

void FileOperate::DoEncrytFile()
{
	if (m_Data->m_Name.isEmpty())
	{
		m_Data->msgbox.setWindowIcon(QIcon(":/Encrytor/Resources/entryt.ico"));
		m_Data->msgbox.setWindowTitle(QString::fromLocal8Bit("文件错误"));
		m_Data->msgbox.setInformativeText(QString::fromLocal8Bit("文件名无效或路径错误"));
		m_Data->msgbox.setIcon(QMessageBox::Critical);
		m_Data->msgbox.setStandardButtons(QMessageBox::Ok);
		m_Data->msgbox.setButtonText(QMessageBox::Ok, QString::fromLocal8Bit("确定"));
		m_Data->msgbox.exec();
		FileOperate::SendInfo(QString::fromLocal8Bit("错误："), QString::fromLocal8Bit("加密前未选择有效的文件"));
	}
	else
	{
		QFileInfo fileinfo(m_Data->m_Name);
		m_Data->filestream = new QFile(m_Data->m_Name);
		if (!m_Data->filestream->open(QIODevice::ReadOnly))
		{
			m_Data->msgbox.setWindowIcon(QIcon(":/Encrytor/Resources/entryt.ico"));
			m_Data->msgbox.setWindowTitle(QString::fromLocal8Bit("文件错误"));
			m_Data->msgbox.setInformativeText(QString::fromLocal8Bit("源文件打开错误"));
			m_Data->msgbox.setIcon(QMessageBox::Critical);
			m_Data->msgbox.setStandardButtons(QMessageBox::Ok);
			m_Data->msgbox.setButtonText(QMessageBox::Ok, QString::fromLocal8Bit("确定"));
			m_Data->msgbox.exec();
			m_Data->filestream->close();
			FileOperate::SendInfo(QString::fromLocal8Bit("错误：文件打开失败->"), m_Data->m_Name);
			delete m_Data->filestream;
			return;
		}
		else
		{
			QByteArray pfile;
			QString name;
			name = fileinfo.absolutePath() + "/" + fileinfo.baseName() + ".Enc";
			QFile handlefile(name);
			char data;
			int i = 0,count;
			unsigned char magic1 = 0, magic2 = 0;
			QString pswd = m_Data->enc.lineEdit->text();
			count = pswd.count();
			for (i = 0;i < count/2;i++)
			{
				magic1 += pswd.at(i).toLatin1();
			}
			for (i = count / 2; i < count; i++)
			{
				magic2 += pswd.at(i).toLatin1();
			}
			i = m_Data->filestream->size();
			QByteArray savefile,savefiletemp;
			pfile = m_Data->filestream->readAll();
			
			savefiletemp = "<";
			savefiletemp += m_Data->m_Name.split('/').at(m_Data->m_Name.split("/").size() - 1);
			savefiletemp += ">";
			count = savefiletemp.size();
			for (int j=0; j < count;j++)
			{
				data = savefiletemp.at(j);
				data += magic1;
				data ^= magic2;
				savefile += data;

			}
			for (int j = 0; j < i; j++)
			{
				data = pfile.at(j);
				data += magic1;
				data ^= magic2;
				savefile += data;
			}
			if (!handlefile.open(QIODevice::ReadWrite | QIODevice::Truncate /*| QIODevice::Text*/))
			{
				m_Data->msgbox.setWindowIcon(QIcon(":/Encrytor/Resources/entryt.ico"));
				m_Data->msgbox.setWindowTitle(QString::fromLocal8Bit("文件错误"));
				m_Data->msgbox.setInformativeText(QString::fromLocal8Bit("文件创建失败"));
				m_Data->msgbox.setIcon(QMessageBox::Critical);
				m_Data->msgbox.setStandardButtons(QMessageBox::Ok);
				m_Data->msgbox.setButtonText(QMessageBox::Ok, QString::fromLocal8Bit("确定"));
				m_Data->msgbox.exec();
				m_Data->filestream->close();
				FileOperate::SendInfo(QString::fromLocal8Bit("错误：加密文件创建失败"));
				delete m_Data->filestream;
				return;
			}
			else
			{
				handlefile.write(savefile.data(), savefile.size());
				FileOperate::SendInfo(QString::fromLocal8Bit("加密成功！输出文件："), name);
				QThread::msleep(1);
				handlefile.close();
				QMessageBox::StandardButton reply;
				reply = QMessageBox::question(nullptr, QString::fromLocal8Bit("删除文件"), QString::fromLocal8Bit("删除原文件?"),
											QMessageBox::Yes | QMessageBox::No);
				if (reply == QMessageBox::Yes)
				{
					if (handlefile.fileName() == m_Data->filestream->fileName())
					{
						FileOperate::SendInfo(QString::fromLocal8Bit("选择删除文件，但是未删除："), QString::fromLocal8Bit("生成文件和源文件重名"));
					}
					else
					{
						m_Data->filestream->remove();
						FileOperate::SendInfo(QString::fromLocal8Bit("删除了源文件"), m_Data->m_Name);
					}
				}
				else if (reply == QMessageBox::No)
					;
				else
					;
			}
		}
	}
	m_Data->filestream->close();
	delete m_Data->filestream;
	m_Data->enc.centerwidget->close();
	return;
}

void FileOperate::DoDncrytFile()
{
	if (m_Data->m_Name.isEmpty())
	{
		m_Data->msgbox.setWindowIcon(QIcon(":/Encrytor/Resources/dnteyt.ico"));
		m_Data->msgbox.setWindowTitle(QString::fromLocal8Bit("文件错误"));
		m_Data->msgbox.setInformativeText(QString::fromLocal8Bit("文件名无效或路径错误"));
		m_Data->msgbox.setIcon(QMessageBox::Critical);
		m_Data->msgbox.setStandardButtons(QMessageBox::Ok);
		m_Data->msgbox.setButtonText(QMessageBox::Ok, QString::fromLocal8Bit("确定"));
		m_Data->msgbox.exec();
		FileOperate::SendInfo(QString::fromLocal8Bit("错误："), QString::fromLocal8Bit("解密前未选择有效的文件"));
	}
	else
	{
		QFileInfo fileinfo(m_Data->m_Name);
		m_Data->filestream = new QFile(m_Data->m_Name);
		if (!m_Data->filestream->open(QIODevice::ReadOnly))
		{
			m_Data->msgbox.setWindowIcon(QIcon(":/Encrytor/Resources/dnteyt.ico"));
			m_Data->msgbox.setWindowTitle(QString::fromLocal8Bit("文件错误"));
			m_Data->msgbox.setInformativeText(QString::fromLocal8Bit("源文件打开错误"));
			m_Data->msgbox.setIcon(QMessageBox::Critical);
			m_Data->msgbox.setStandardButtons(QMessageBox::Ok);
			m_Data->msgbox.setButtonText(QMessageBox::Ok, QString::fromLocal8Bit("确定"));
			m_Data->msgbox.exec();
			FileOperate::SendInfo(QString::fromLocal8Bit("错误：源文件打开失败"), m_Data->m_Name);
			delete m_Data->filestream;
			return;
		}
		else
		{
			QByteArray pfile;
			char data;
			int i = 0, count;
			unsigned char magic1 = 0, magic2 = 0;
			QString pswd = m_Data->dnc.lineEdit->text();
			count = pswd.count();
			for (i = 0; i < count / 2; i++)
			{
				magic1 += pswd.at(i).toLatin1();
			}
			for (i = count / 2; i < count; i++)
			{
				magic2 += pswd.at(i).toLatin1();
			}
			i = m_Data->filestream->size();
			QByteArray savefile, savefiletemp;
			pfile = m_Data->filestream->readAll();
//			i = pfile.size();
			int Foundf = 0, Founde = 0;
			for (int j = 0; j < i; j++)
			{
				data = pfile.at(j);
				data ^= magic2;
				data -= magic1;
				if (data == '<')
				{
					if ((Foundf == 0))
					{
						Foundf = 1;
						continue;
					}
				}
				if (data == '>')
				{
					if ((Founde == 0))
					{
						Founde = 1;
						continue;
					}
				}
				if ((Foundf == 1) && (Founde == 0))
				{
					savefiletemp += data;
					continue;
				}
				else if ((Foundf == 1) && (Founde == 1))
				{
					savefile += data;
				}
				else
				{
					if ((j == (i - 1)) && (savefiletemp.size() == 0))
					{
						m_Data->msgbox.setWindowIcon(QIcon(":/Encrytor/Resources/dnteyt.ico"));
						m_Data->msgbox.setWindowTitle(QString::fromLocal8Bit("密码错误"));
						m_Data->msgbox.setInformativeText(QString::fromLocal8Bit("我也不知道发生了什么，反正就是错了"));
						m_Data->msgbox.setIcon(QMessageBox::Critical);
						m_Data->msgbox.setStandardButtons(QMessageBox::Ok);
						m_Data->msgbox.setButtonText(QMessageBox::Ok, QString::fromLocal8Bit("确定"));
						m_Data->msgbox.exec();
						m_Data->dnc.centerwidget->close();
						FileOperate::SendInfo(QString::fromLocal8Bit("错误："), QString::fromLocal8Bit("密码记错了吗？"));
						delete m_Data->filestream;
						return;
					}
				}
				
			}
			QFile handlefile(fileinfo.absolutePath() + "/" + savefiletemp);
			if (!handlefile.open(QIODevice::ReadWrite | QIODevice::Truncate /*| QIODevice::Text*/))
			{
				m_Data->msgbox.setWindowIcon(QIcon(":/Encrytor/Resources/dnteyt.ico"));
				m_Data->msgbox.setWindowTitle(QString::fromLocal8Bit("文件错误"));
				m_Data->msgbox.setInformativeText(QString::fromLocal8Bit("文件创建失败或密码错误"));
				m_Data->msgbox.setIcon(QMessageBox::Critical);
				m_Data->msgbox.setStandardButtons(QMessageBox::Ok);
				m_Data->msgbox.setButtonText(QMessageBox::Ok, QString::fromLocal8Bit("确定"));
				m_Data->msgbox.exec();
				m_Data->filestream->close();
				FileOperate::SendInfo(QString::fromLocal8Bit("错误："), QString::fromLocal8Bit("解密失败，请检查密码是否正确或者文件是否完整"));
				delete m_Data->filestream;
				return;
			}
			else
			{
				handlefile.write(savefile.data(), savefile.size());
				m_Data->filestream->close();
				FileOperate::SendInfo(QString::fromLocal8Bit("解密成功！输出文件："), fileinfo.absolutePath() + "/" + savefiletemp);
				handlefile.close();
			}
		}
	}
	m_Data->dnc.centerwidget->close();
	delete m_Data->filestream;
}

QString FileOperate::GetFileName()
{
	return m_Data->m_Name;
}

void FileOperate::about()
{
	m_Data->about.centerwidget->setWindowIcon(QIcon(":/Encrytor/Resources/about.ico"));
	m_Data->about.centerwidget->setWindowTitle(QString::fromLocal8Bit("关于"));
	m_Data->about.centerwidget->resize(225, 125);
	m_Data->about.label->setText(QString::fromLocal8Bit(VERSION));
	QDialog::connect(m_Data->about.pushbutton, &QAbstractButton::clicked, m_Data->about.centerwidget, &QDialog::close);
	m_Data->about.centerwidget->show();
}

void FileOperate::help()
{
	m_Data->help.centerwidget->setWindowIcon(QIcon(":/Encrytor/Resources/help.ico"));
	m_Data->help.centerwidget->setWindowTitle(QString::fromLocal8Bit("帮助"));
	m_Data->help.centerwidget->resize(225, 125);
	m_Data->help.label->setText(QString::fromLocal8Bit("先选择文件，然后选择加密/解密"));
	QDialog::connect(m_Data->help.pushbutton, &QAbstractButton::clicked, m_Data->help.centerwidget, &QDialog::close);
	m_Data->help.centerwidget->show();
}

void FileOperate::error(QString msg)
{
	m_Data->error.centerwidget->setWindowTitle(QString::fromLocal8Bit("帮助"));
	m_Data->error.centerwidget->resize(225, 125);
	m_Data->error.label->setText(QString::fromLocal8Bit(msg.toLatin1()));
	QDialog::connect(m_Data->error.pushbutton, &QAbstractButton::clicked, m_Data->error.centerwidget, &QDialog::close);
	m_Data->help.centerwidget->show();
}

void FileOperate::changelog()
{
	FileOperate::SendInfo(QString::fromLocal8Bit("\r\n****************************更新历史**************************"));
	FileOperate::SendInfo(QString::fromLocal8Bit("V0.0.0"));
	FileOperate::SendInfo(QString::fromLocal8Bit("初版本，仅包含文件打开UI和加密/解密图标。\r\n"));
	FileOperate::SendInfo(QString::fromLocal8Bit("V0.0.1"));
	FileOperate::SendInfo(QString::fromLocal8Bit("1.添加文件菜单；\r\n2.增加文件加密和解密功能。\r\n"));
	FileOperate::SendInfo(QString::fromLocal8Bit("V0.1.0"));
	FileOperate::SendInfo(QString::fromLocal8Bit("1.增加文件路径显示功能；\r\n2.增加“帮助”功能；\r\n3.增加“关于”功能。\r\n"));
	FileOperate::SendInfo(QString::fromLocal8Bit("V0.2.0"));
	FileOperate::SendInfo(QString::fromLocal8Bit("增加解密文件后恢复加密前文件名功能。\r\n"));
	FileOperate::SendInfo(QString::fromLocal8Bit("V0.2.1"));
	FileOperate::SendInfo(QString::fromLocal8Bit("修复文件名不能为中文的bug。\r\n"));
	FileOperate::SendInfo(QString::fromLocal8Bit("V1.0.0"));
	FileOperate::SendInfo(QString::fromLocal8Bit("1.增加菜单图标，更加美观；\r\n2.增加日志功能。\r\n"));
	FileOperate::SendInfo(QString::fromLocal8Bit("V1.0.1"));
	FileOperate::SendInfo(QString::fromLocal8Bit("1.修复日志中对文件打开的输出错误；\r\n2.增加“更新历史”功能。\r\n"));
	FileOperate::SendInfo(QString::fromLocal8Bit("V1.0.2"));
	FileOperate::SendInfo(QString::fromLocal8Bit("添加了一个很骚气的BGM。\r\n"));
}

void FileOperate::Play()
{
	m_Data->player.play();
	ui.pushButton_4->setText(QString::fromLocal8Bit("暂停BGM"));
	QDialog::disconnect(ui.pushButton_4, &QAbstractButton::clicked, this, &FileOperate::Play);
	QDialog::connect(ui.pushButton_4, &QAbstractButton::clicked, this, &FileOperate::Pause);
	FileOperate::SendInfo(QString::fromLocal8Bit("播放背景音乐"));
}

void FileOperate::Pause()
{
	m_Data->player.pause();
	ui.pushButton_4->setText(QString::fromLocal8Bit("播放BGM"));
	QDialog::disconnect(ui.pushButton_4, &QAbstractButton::clicked, this, &FileOperate::Pause);
	QDialog::connect(ui.pushButton_4, &QAbstractButton::clicked, this, &FileOperate::Play);
	FileOperate::SendInfo(QString::fromLocal8Bit("暂停背景音乐"));
}

FileOperate * FileOperate::Instance()
{
	static FileOperate* handle = NULL;
	if (!handle)
	{
		handle = new FileOperate;
	}
	return handle;
}

void FileOperate::SendInfo(QString info1, QString info2)
{
	QString Info = info1;
	Info += info2;
	FileOperate::Instance()->ui.textBrowser->append(Info);
}

subWidget::subWidget()
{
	centerwidget = new QWidget;
	label = new QLabel();
	pushbutton = new QPushButton(QString::fromLocal8Bit("确定"));
	verticalLayout = new QVBoxLayout(centerwidget);
	verticalLayout->addWidget(label);
	verticalLayout->addWidget(pushbutton);
	pushbutton->setShortcut(Qt::Key_Enter);
}

subWidget::~subWidget()
{
	delete centerwidget;
	delete label;
	delete pushbutton;
	delete verticalLayout;
}
encWidget::encWidget()
{
	centerwidget = new QWidget;
	label = new QLabel();
	pushbutton = new QPushButton(QString::fromLocal8Bit("确定"));
	lineEdit = new QLineEdit;
	lineEdit->setEchoMode(QLineEdit::Password);
	verticalLayout = new QVBoxLayout(centerwidget);
	verticalLayout->addWidget(label);
	verticalLayout->addWidget(lineEdit);
	verticalLayout->addWidget(pushbutton);
	pushbutton->setShortcut(Qt::Key_Enter);
}

encWidget::~encWidget()
{
	delete centerwidget;
	delete label;
	delete pushbutton;
	delete verticalLayout;
}
