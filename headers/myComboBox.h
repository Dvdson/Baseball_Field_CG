//
// Created by wmarques on 25/08/16.
//
//myComboBox.h File

#ifndef MYCOMBOBOX_H
#define MYCOMBOBOX_H

#include <QtGui>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QMessageBox>

//Derived Class from QComboBox
class MyComboBox: public QComboBox
{
  public:
	bool test = false;

    Q_OBJECT
  public:
	MyComboBox(QWidget* parent):QComboBox(parent)
	{
	  this->setParent(parent);
	  connect(this , SIGNAL(currentIndexChanged(int)),this,SLOT(handleSelectionChanged(int)));
	};
	~ MyComboBox(){};

  public slots:
	//Slot that is called when QComboBox selection is changed
	void handleSelectionChanged(int index)
	{
        if (index == 1) {
            test = true;
        }

		/*QMessageBox* msg = new QMessageBox();
	    msg->setWindowTitle("Hello !");
	    msg->setText("Selected Index is :"+QString::number(index));
	    msg->show();*/
	};

};
#endif