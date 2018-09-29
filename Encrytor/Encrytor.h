#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Encrytor.h"

class Encrytor : public QMainWindow
{
	Q_OBJECT

public:
	Encrytor(QWidget *parent = Q_NULLPTR);
	Ui::EncrytorClass ui;
};
