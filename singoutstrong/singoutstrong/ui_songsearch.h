/********************************************************************************
** Form generated from reading UI file 'songsearch.ui'
**
** Created: Sat 1. Dec 17:57:50 2012
**      by: Qt User Interface Compiler version 4.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SONGSEARCH_H
#define UI_SONGSEARCH_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QGridLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QRadioButton>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SongSearch
{
public:
    QWidget *windowBar;
    QWidget *content;
    QGridLayout *gridLayout;
    QPushButton *pushButton;
    QLabel *label_2;
    QRadioButton *radioButton;
    QRadioButton *radioButton_2;
    QRadioButton *radioButton_3;
    QLabel *label_3;
    QRadioButton *radioButton_4;
    QRadioButton *radioButton_5;
    QRadioButton *radioButton_6;
    QLabel *label;
    QLineEdit *lineEdit;

    void setupUi(QWidget *SongSearch)
    {
        if (SongSearch->objectName().isEmpty())
            SongSearch->setObjectName(QString::fromUtf8("SongSearch"));
        SongSearch->resize(351, 311);
        windowBar = new QWidget(SongSearch);
        windowBar->setObjectName(QString::fromUtf8("windowBar"));
        windowBar->setGeometry(QRect(0, 0, 351, 21));
        content = new QWidget(SongSearch);
        content->setObjectName(QString::fromUtf8("content"));
        content->setGeometry(QRect(0, 20, 351, 291));
        gridLayout = new QGridLayout(content);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        pushButton = new QPushButton(content);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));

        gridLayout->addWidget(pushButton, 0, 3, 1, 1);

        label_2 = new QLabel(content);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout->addWidget(label_2, 1, 0, 1, 1);

        radioButton = new QRadioButton(content);
        radioButton->setObjectName(QString::fromUtf8("radioButton"));

        gridLayout->addWidget(radioButton, 1, 1, 1, 1);

        radioButton_2 = new QRadioButton(content);
        radioButton_2->setObjectName(QString::fromUtf8("radioButton_2"));

        gridLayout->addWidget(radioButton_2, 1, 2, 1, 1);

        radioButton_3 = new QRadioButton(content);
        radioButton_3->setObjectName(QString::fromUtf8("radioButton_3"));

        gridLayout->addWidget(radioButton_3, 1, 3, 1, 1);

        label_3 = new QLabel(content);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout->addWidget(label_3, 2, 0, 1, 1);

        radioButton_4 = new QRadioButton(content);
        radioButton_4->setObjectName(QString::fromUtf8("radioButton_4"));

        gridLayout->addWidget(radioButton_4, 2, 1, 1, 1);

        radioButton_5 = new QRadioButton(content);
        radioButton_5->setObjectName(QString::fromUtf8("radioButton_5"));

        gridLayout->addWidget(radioButton_5, 2, 2, 1, 1);

        radioButton_6 = new QRadioButton(content);
        radioButton_6->setObjectName(QString::fromUtf8("radioButton_6"));

        gridLayout->addWidget(radioButton_6, 2, 3, 1, 1);

        label = new QLabel(content);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout->addWidget(label, 3, 0, 1, 4);

        lineEdit = new QLineEdit(content);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));

        gridLayout->addWidget(lineEdit, 0, 0, 1, 3);


        retranslateUi(SongSearch);

        QMetaObject::connectSlotsByName(SongSearch);
    } // setupUi

    void retranslateUi(QWidget *SongSearch)
    {
        SongSearch->setWindowTitle(QApplication::translate("SongSearch", "Form", 0, QApplication::UnicodeUTF8));
        pushButton->setText(QApplication::translate("SongSearch", "PushButton", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("SongSearch", "Search for:", 0, QApplication::UnicodeUTF8));
        radioButton->setText(QApplication::translate("SongSearch", "Title", 0, QApplication::UnicodeUTF8));
        radioButton_2->setText(QApplication::translate("SongSearch", "Artist", 0, QApplication::UnicodeUTF8));
        radioButton_3->setText(QApplication::translate("SongSearch", "Both", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("SongSearch", "Song type:", 0, QApplication::UnicodeUTF8));
        radioButton_4->setText(QApplication::translate("SongSearch", "UltraStar", 0, QApplication::UnicodeUTF8));
        radioButton_5->setText(QApplication::translate("SongSearch", "Midi/kar", 0, QApplication::UnicodeUTF8));
        radioButton_6->setText(QApplication::translate("SongSearch", "Any", 0, QApplication::UnicodeUTF8));
        label->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class SongSearch: public Ui_SongSearch {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SONGSEARCH_H
