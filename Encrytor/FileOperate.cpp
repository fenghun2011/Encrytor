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
	
	m_Data->m_Name = QFileDialog::getOpenFileName(ui.centralWidget, QString::fromLocal8Bit("��һ�����ܻ������ļ�"), ".",
		QString::fromLocal8Bit("�����ļ�(*.Enc);;�����ļ�(*.Dnc);;�����ļ�(*.*)"));
	if (!m_Data->m_Name.isEmpty())
	{
		SetFileName(m_Data->m_Name);
		FileOperate::SendInfo(QString::fromLocal8Bit("���ļ���"), m_Data->m_Name);
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
	m_Data->enc.centerwidget->setWindowTitle(QString::fromLocal8Bit("����"));
	m_Data->enc.centerwidget->resize(225, 125);
	m_Data->enc.label->setText(QString::fromLocal8Bit("���������룺"));
	m_Data->enc.lineEdit->clear();
	if (m_Data->m_Name.isEmpty())
	{
		m_Data->msgbox.setWindowIcon(QIcon(":/Encrytor/Resources/entryt.ico"));
		m_Data->msgbox.setWindowTitle(QString::fromLocal8Bit("�ļ�����"));
		m_Data->msgbox.setInformativeText(QString::fromLocal8Bit("�ļ�����Ч��·������"));
		m_Data->msgbox.setIcon(QMessageBox::Critical);
		m_Data->msgbox.setStandardButtons(QMessageBox::Ok);
		m_Data->msgbox.setButtonText(QMessageBox::Ok, QString::fromLocal8Bit("ȷ��"));
		m_Data->msgbox.exec();
		FileOperate::SendInfo(QString::fromLocal8Bit("����"), QString::fromLocal8Bit("����ǰδѡ����Ч���ļ�"));
	}
	else
	{
		m_Data->enc.centerwidget->show();
	}
	
}

void FileOperate::DncrytFile()
{
	m_Data->dnc.centerwidget->setWindowTitle(QString::fromLocal8Bit("����"));
	m_Data->dnc.centerwidget->resize(225, 125);
	m_Data->dnc.label->setText(QString::fromLocal8Bit("���������룺"));
	m_Data->dnc.lineEdit->clear();
	if (m_Data->m_Name.isEmpty())
	{
		m_Data->msgbox.setWindowIcon(QIcon(":/Encrytor/Resources/dnteyt.ico"));
		m_Data->msgbox.setWindowTitle(QString::fromLocal8Bit("�ļ�����"));
		m_Data->msgbox.setInformativeText(QString::fromLocal8Bit("�ļ�����Ч��·������"));
		m_Data->msgbox.setIcon(QMessageBox::Critical);
		m_Data->msgbox.setStandardButtons(QMessageBox::Ok);
		m_Data->msgbox.setButtonText(QMessageBox::Ok, QString::fromLocal8Bit("ȷ��"));
		m_Data->msgbox.exec();
		FileOperate::SendInfo(QString::fromLocal8Bit("����"), QString::fromLocal8Bit("����ǰδѡ����Ч���ļ�"));
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
		m_Data->msgbox.setWindowTitle(QString::fromLocal8Bit("�ļ�����"));
		m_Data->msgbox.setInformativeText(QString::fromLocal8Bit("�ļ�����Ч��·������"));
		m_Data->msgbox.setIcon(QMessageBox::Critical);
		m_Data->msgbox.setStandardButtons(QMessageBox::Ok);
		m_Data->msgbox.setButtonText(QMessageBox::Ok, QString::fromLocal8Bit("ȷ��"));
		m_Data->msgbox.exec();
		FileOperate::SendInfo(QString::fromLocal8Bit("����"), QString::fromLocal8Bit("����ǰδѡ����Ч���ļ�"));
	}
	else
	{
		QFileInfo fileinfo(m_Data->m_Name);
		m_Data->filestream = new QFile(m_Data->m_Name);
		if (!m_Data->filestream->open(QIODevice::ReadOnly))
		{
			m_Data->msgbox.setWindowIcon(QIcon(":/Encrytor/Resources/entryt.ico"));
			m_Data->msgbox.setWindowTitle(QString::fromLocal8Bit("�ļ�����"));
			m_Data->msgbox.setInformativeText(QString::fromLocal8Bit("Դ�ļ��򿪴���"));
			m_Data->msgbox.setIcon(QMessageBox::Critical);
			m_Data->msgbox.setStandardButtons(QMessageBox::Ok);
			m_Data->msgbox.setButtonText(QMessageBox::Ok, QString::fromLocal8Bit("ȷ��"));
			m_Data->msgbox.exec();
			m_Data->filestream->close();
			FileOperate::SendInfo(QString::fromLocal8Bit("�����ļ���ʧ��->"), m_Data->m_Name);
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
				m_Data->msgbox.setWindowTitle(QString::fromLocal8Bit("�ļ�����"));
				m_Data->msgbox.setInformativeText(QString::fromLocal8Bit("�ļ�����ʧ��"));
				m_Data->msgbox.setIcon(QMessageBox::Critical);
				m_Data->msgbox.setStandardButtons(QMessageBox::Ok);
				m_Data->msgbox.setButtonText(QMessageBox::Ok, QString::fromLocal8Bit("ȷ��"));
				m_Data->msgbox.exec();
				m_Data->filestream->close();
				FileOperate::SendInfo(QString::fromLocal8Bit("���󣺼����ļ�����ʧ��"));
				delete m_Data->filestream;
				return;
			}
			else
			{
				handlefile.write(savefile.data(), savefile.size());
				FileOperate::SendInfo(QString::fromLocal8Bit("���ܳɹ�������ļ���"), name);
				QThread::msleep(1);
				handlefile.close();
				QMessageBox::StandardButton reply;
				reply = QMessageBox::question(nullptr, QString::fromLocal8Bit("ɾ���ļ�"), QString::fromLocal8Bit("ɾ��ԭ�ļ�?"),
											QMessageBox::Yes | QMessageBox::No);
				if (reply == QMessageBox::Yes)
				{
					if (handlefile.fileName() == m_Data->filestream->fileName())
					{
						FileOperate::SendInfo(QString::fromLocal8Bit("ѡ��ɾ���ļ�������δɾ����"), QString::fromLocal8Bit("�����ļ���Դ�ļ�����"));
					}
					else
					{
						m_Data->filestream->remove();
						FileOperate::SendInfo(QString::fromLocal8Bit("ɾ����Դ�ļ�"), m_Data->m_Name);
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
		m_Data->msgbox.setWindowTitle(QString::fromLocal8Bit("�ļ�����"));
		m_Data->msgbox.setInformativeText(QString::fromLocal8Bit("�ļ�����Ч��·������"));
		m_Data->msgbox.setIcon(QMessageBox::Critical);
		m_Data->msgbox.setStandardButtons(QMessageBox::Ok);
		m_Data->msgbox.setButtonText(QMessageBox::Ok, QString::fromLocal8Bit("ȷ��"));
		m_Data->msgbox.exec();
		FileOperate::SendInfo(QString::fromLocal8Bit("����"), QString::fromLocal8Bit("����ǰδѡ����Ч���ļ�"));
	}
	else
	{
		QFileInfo fileinfo(m_Data->m_Name);
		m_Data->filestream = new QFile(m_Data->m_Name);
		if (!m_Data->filestream->open(QIODevice::ReadOnly))
		{
			m_Data->msgbox.setWindowIcon(QIcon(":/Encrytor/Resources/dnteyt.ico"));
			m_Data->msgbox.setWindowTitle(QString::fromLocal8Bit("�ļ�����"));
			m_Data->msgbox.setInformativeText(QString::fromLocal8Bit("Դ�ļ��򿪴���"));
			m_Data->msgbox.setIcon(QMessageBox::Critical);
			m_Data->msgbox.setStandardButtons(QMessageBox::Ok);
			m_Data->msgbox.setButtonText(QMessageBox::Ok, QString::fromLocal8Bit("ȷ��"));
			m_Data->msgbox.exec();
			FileOperate::SendInfo(QString::fromLocal8Bit("����Դ�ļ���ʧ��"), m_Data->m_Name);
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
						m_Data->msgbox.setWindowTitle(QString::fromLocal8Bit("�������"));
						m_Data->msgbox.setInformativeText(QString::fromLocal8Bit("��Ҳ��֪��������ʲô���������Ǵ���"));
						m_Data->msgbox.setIcon(QMessageBox::Critical);
						m_Data->msgbox.setStandardButtons(QMessageBox::Ok);
						m_Data->msgbox.setButtonText(QMessageBox::Ok, QString::fromLocal8Bit("ȷ��"));
						m_Data->msgbox.exec();
						m_Data->dnc.centerwidget->close();
						FileOperate::SendInfo(QString::fromLocal8Bit("����"), QString::fromLocal8Bit("����Ǵ�����"));
						delete m_Data->filestream;
						return;
					}
				}
				
			}
			QFile handlefile(fileinfo.absolutePath() + "/" + savefiletemp);
			if (!handlefile.open(QIODevice::ReadWrite | QIODevice::Truncate /*| QIODevice::Text*/))
			{
				m_Data->msgbox.setWindowIcon(QIcon(":/Encrytor/Resources/dnteyt.ico"));
				m_Data->msgbox.setWindowTitle(QString::fromLocal8Bit("�ļ�����"));
				m_Data->msgbox.setInformativeText(QString::fromLocal8Bit("�ļ�����ʧ�ܻ��������"));
				m_Data->msgbox.setIcon(QMessageBox::Critical);
				m_Data->msgbox.setStandardButtons(QMessageBox::Ok);
				m_Data->msgbox.setButtonText(QMessageBox::Ok, QString::fromLocal8Bit("ȷ��"));
				m_Data->msgbox.exec();
				m_Data->filestream->close();
				FileOperate::SendInfo(QString::fromLocal8Bit("����"), QString::fromLocal8Bit("����ʧ�ܣ����������Ƿ���ȷ�����ļ��Ƿ�����"));
				delete m_Data->filestream;
				return;
			}
			else
			{
				handlefile.write(savefile.data(), savefile.size());
				m_Data->filestream->close();
				FileOperate::SendInfo(QString::fromLocal8Bit("���ܳɹ�������ļ���"), fileinfo.absolutePath() + "/" + savefiletemp);
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
	m_Data->about.centerwidget->setWindowTitle(QString::fromLocal8Bit("����"));
	m_Data->about.centerwidget->resize(225, 125);
	m_Data->about.label->setText(QString::fromLocal8Bit(VERSION));
	QDialog::connect(m_Data->about.pushbutton, &QAbstractButton::clicked, m_Data->about.centerwidget, &QDialog::close);
	m_Data->about.centerwidget->show();
}

void FileOperate::help()
{
	m_Data->help.centerwidget->setWindowIcon(QIcon(":/Encrytor/Resources/help.ico"));
	m_Data->help.centerwidget->setWindowTitle(QString::fromLocal8Bit("����"));
	m_Data->help.centerwidget->resize(225, 125);
	m_Data->help.label->setText(QString::fromLocal8Bit("��ѡ���ļ���Ȼ��ѡ�����/����"));
	QDialog::connect(m_Data->help.pushbutton, &QAbstractButton::clicked, m_Data->help.centerwidget, &QDialog::close);
	m_Data->help.centerwidget->show();
}

void FileOperate::error(QString msg)
{
	m_Data->error.centerwidget->setWindowTitle(QString::fromLocal8Bit("����"));
	m_Data->error.centerwidget->resize(225, 125);
	m_Data->error.label->setText(QString::fromLocal8Bit(msg.toLatin1()));
	QDialog::connect(m_Data->error.pushbutton, &QAbstractButton::clicked, m_Data->error.centerwidget, &QDialog::close);
	m_Data->help.centerwidget->show();
}

void FileOperate::changelog()
{
	FileOperate::SendInfo(QString::fromLocal8Bit("\r\n****************************������ʷ**************************"));
	FileOperate::SendInfo(QString::fromLocal8Bit("V0.0.0"));
	FileOperate::SendInfo(QString::fromLocal8Bit("���汾���������ļ���UI�ͼ���/����ͼ�ꡣ\r\n"));
	FileOperate::SendInfo(QString::fromLocal8Bit("V0.0.1"));
	FileOperate::SendInfo(QString::fromLocal8Bit("1.����ļ��˵���\r\n2.�����ļ����ܺͽ��ܹ��ܡ�\r\n"));
	FileOperate::SendInfo(QString::fromLocal8Bit("V0.1.0"));
	FileOperate::SendInfo(QString::fromLocal8Bit("1.�����ļ�·����ʾ���ܣ�\r\n2.���ӡ����������ܣ�\r\n3.���ӡ����ڡ����ܡ�\r\n"));
	FileOperate::SendInfo(QString::fromLocal8Bit("V0.2.0"));
	FileOperate::SendInfo(QString::fromLocal8Bit("���ӽ����ļ���ָ�����ǰ�ļ������ܡ�\r\n"));
	FileOperate::SendInfo(QString::fromLocal8Bit("V0.2.1"));
	FileOperate::SendInfo(QString::fromLocal8Bit("�޸��ļ�������Ϊ���ĵ�bug��\r\n"));
	FileOperate::SendInfo(QString::fromLocal8Bit("V1.0.0"));
	FileOperate::SendInfo(QString::fromLocal8Bit("1.���Ӳ˵�ͼ�꣬�������ۣ�\r\n2.������־���ܡ�\r\n"));
	FileOperate::SendInfo(QString::fromLocal8Bit("V1.0.1"));
	FileOperate::SendInfo(QString::fromLocal8Bit("1.�޸���־�ж��ļ��򿪵��������\r\n2.���ӡ�������ʷ�����ܡ�\r\n"));
	FileOperate::SendInfo(QString::fromLocal8Bit("V1.0.2"));
	FileOperate::SendInfo(QString::fromLocal8Bit("�����һ����ɧ����BGM��\r\n"));
}

void FileOperate::Play()
{
	m_Data->player.play();
	ui.pushButton_4->setText(QString::fromLocal8Bit("��ͣBGM"));
	QDialog::disconnect(ui.pushButton_4, &QAbstractButton::clicked, this, &FileOperate::Play);
	QDialog::connect(ui.pushButton_4, &QAbstractButton::clicked, this, &FileOperate::Pause);
	FileOperate::SendInfo(QString::fromLocal8Bit("���ű�������"));
}

void FileOperate::Pause()
{
	m_Data->player.pause();
	ui.pushButton_4->setText(QString::fromLocal8Bit("����BGM"));
	QDialog::disconnect(ui.pushButton_4, &QAbstractButton::clicked, this, &FileOperate::Pause);
	QDialog::connect(ui.pushButton_4, &QAbstractButton::clicked, this, &FileOperate::Play);
	FileOperate::SendInfo(QString::fromLocal8Bit("��ͣ��������"));
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
	pushbutton = new QPushButton(QString::fromLocal8Bit("ȷ��"));
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
	pushbutton = new QPushButton(QString::fromLocal8Bit("ȷ��"));
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
