/********************************************************************************
** Form generated from reading UI file 'Encrytor.ui'
**
** Created by: Qt User Interface Compiler version 5.11.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ENCRYTOR_H
#define UI_ENCRYTOR_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_EncrytorClass
{
public:
    QAction *actionOpen;
    QAction *actionHelp;
    QAction *actionAbout;
    QAction *actionClose;
    QAction *actionChangelog;
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QTextBrowser *textBrowser;
    QHBoxLayout *horizontalLayout;
    QLineEdit *lineEdit;
    QPushButton *pushButton;
    QPushButton *pushButton_3;
    QPushButton *pushButton_2;
    QPushButton *pushButton_4;
    QMenuBar *menuBar;
    QMenu *menu;
    QMenu *menu_2;

    void setupUi(QMainWindow *EncrytorClass)
    {
        if (EncrytorClass->objectName().isEmpty())
            EncrytorClass->setObjectName(QStringLiteral("EncrytorClass"));
        EncrytorClass->resize(600, 400);
        actionOpen = new QAction(EncrytorClass);
        actionOpen->setObjectName(QStringLiteral("actionOpen"));
        actionHelp = new QAction(EncrytorClass);
        actionHelp->setObjectName(QStringLiteral("actionHelp"));
        actionAbout = new QAction(EncrytorClass);
        actionAbout->setObjectName(QStringLiteral("actionAbout"));
        actionClose = new QAction(EncrytorClass);
        actionClose->setObjectName(QStringLiteral("actionClose"));
        actionChangelog = new QAction(EncrytorClass);
        actionChangelog->setObjectName(QStringLiteral("actionChangelog"));
        centralWidget = new QWidget(EncrytorClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        verticalLayout = new QVBoxLayout(centralWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));

        verticalLayout->addWidget(label);

        textBrowser = new QTextBrowser(centralWidget);
        textBrowser->setObjectName(QStringLiteral("textBrowser"));

        verticalLayout->addWidget(textBrowser);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        lineEdit = new QLineEdit(centralWidget);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));
        QFont font;
        font.setFamily(QStringLiteral("Consolas"));
        lineEdit->setFont(font);

        horizontalLayout->addWidget(lineEdit);

        pushButton = new QPushButton(centralWidget);
        pushButton->setObjectName(QStringLiteral("pushButton"));

        horizontalLayout->addWidget(pushButton);

        pushButton_3 = new QPushButton(centralWidget);
        pushButton_3->setObjectName(QStringLiteral("pushButton_3"));

        horizontalLayout->addWidget(pushButton_3);

        pushButton_2 = new QPushButton(centralWidget);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));

        horizontalLayout->addWidget(pushButton_2);

        pushButton_4 = new QPushButton(centralWidget);
        pushButton_4->setObjectName(QStringLiteral("pushButton_4"));

        horizontalLayout->addWidget(pushButton_4);


        verticalLayout->addLayout(horizontalLayout);

        EncrytorClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(EncrytorClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 600, 23));
        menu = new QMenu(menuBar);
        menu->setObjectName(QStringLiteral("menu"));
        menu_2 = new QMenu(menuBar);
        menu_2->setObjectName(QStringLiteral("menu_2"));
        EncrytorClass->setMenuBar(menuBar);

        menuBar->addAction(menu->menuAction());
        menuBar->addAction(menu_2->menuAction());
        menu->addAction(actionOpen);
        menu->addAction(actionClose);
        menu_2->addAction(actionHelp);
        menu_2->addAction(actionAbout);
        menu_2->addAction(actionChangelog);

        retranslateUi(EncrytorClass);

        QMetaObject::connectSlotsByName(EncrytorClass);
    } // setupUi

    void retranslateUi(QMainWindow *EncrytorClass)
    {
        EncrytorClass->setWindowTitle(QApplication::translate("EncrytorClass", "Encrytor", nullptr));
        actionOpen->setText(QApplication::translate("EncrytorClass", "Open...", nullptr));
        actionHelp->setText(QApplication::translate("EncrytorClass", "Help...", nullptr));
        actionAbout->setText(QApplication::translate("EncrytorClass", "About...", nullptr));
        actionClose->setText(QApplication::translate("EncrytorClass", "Close...", nullptr));
        actionChangelog->setText(QApplication::translate("EncrytorClass", "Changelog", nullptr));
        label->setText(QApplication::translate("EncrytorClass", "<html><head/><body><p align=\"center\"><span style=\" font-size:14pt; font-weight:600; color:#55aaff;\">\346\207\222\344\272\272\345\212\240\345\257\206</span></p></body></html>", nullptr));
        lineEdit->setText(QString());
        pushButton->setText(QApplication::translate("EncrytorClass", "...", nullptr));
        pushButton_3->setText(QApplication::translate("EncrytorClass", "\350\247\243\345\257\206", nullptr));
        pushButton_2->setText(QApplication::translate("EncrytorClass", "\345\212\240\345\257\206", nullptr));
        pushButton_4->setText(QApplication::translate("EncrytorClass", "\346\232\202\345\201\234BGM", nullptr));
        menu->setTitle(QApplication::translate("EncrytorClass", "\346\226\207\344\273\266", nullptr));
        menu_2->setTitle(QApplication::translate("EncrytorClass", "\345\270\256\345\212\251", nullptr));
    } // retranslateUi

};

namespace Ui {
    class EncrytorClass: public Ui_EncrytorClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ENCRYTOR_H
