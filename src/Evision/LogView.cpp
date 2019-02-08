#include "LogView.h"
#include <corecrt_wstdio.h>
#include <stdio.h>
#include <iostream>
#include <QTimer>
#include <qDebug>
#include <QDateTime>
LogView::LogView(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	this->setWindowFlags(this->windowFlags() &~Qt::WindowMinMaxButtonsHint);//��ֹ������С��
	this->setWindowFlags(this->windowFlags() | Qt::WindowStaysOnTopHint);

	redirector = new StdoutRedirector(this, StdoutRedirector::StandardOutput | StdoutRedirector::StandardError);
	connect(redirector, SIGNAL(readyRead()), this, SLOT(readData()));

}

LogView::~LogView()
{
}
//��ȡʵ��
LogView* LogView::getInstance()
{
	static LogView * m_pInstance;
	if (m_pInstance == NULL) //�ж��Ƿ��һ�ε���
		m_pInstance = new LogView();
	return m_pInstance;
}

void LogView::readData()
{
	ui.textEdit->append(QString::fromLocal8Bit(redirector->read(1024)));
}