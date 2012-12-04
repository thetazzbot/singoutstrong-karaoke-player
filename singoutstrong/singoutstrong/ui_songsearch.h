/********************************************************************************
** Form generated from reading UI file 'songsearch.ui'
**
** Created: Tue 4. Dec 20:25:43 2012
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
#include "windowbar.h"

QT_BEGIN_NAMESPACE

class Ui_SongSearch
{
public:
    QWidget *content;
    QGridLayout *gridLayout;
    QLabel *label_2;
    QRadioButton *titleButton;
    QRadioButton *midiButton;
    QRadioButton *ultraStarButton;
    QPushButton *pushButton;
    QRadioButton *searchInAllButton;
    QRadioButton *anyTypeButton;
    QLabel *label;
    QLineEdit *lineEdit;
    QRadioButton *artistButton;
    QLabel *label_3;
    SoS::QtGui::WindowBar *windowBar;

    void setupUi(QWidget *SongSearch)
    {
        if (SongSearch->objectName().isEmpty())
            SongSearch->setObjectName(QString::fromUtf8("SongSearch"));
        SongSearch->resize(351, 311);
        content = new QWidget(SongSearch);
        content->setObjectName(QString::fromUtf8("content"));
        content->setGeometry(QRect(0, 20, 351, 291));
        gridLayout = new QGridLayout(content);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label_2 = new QLabel(content);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout->addWidget(label_2, 1, 0, 1, 1);

        titleButton = new QRadioButton(content);
        titleButton->setObjectName(QString::fromUtf8("titleButton"));
        titleButton->setAutoExclusive(false);

        gridLayout->addWidget(titleButton, 1, 1, 1, 1);

        midiButton = new QRadioButton(content);
        midiButton->setObjectName(QString::fromUtf8("midiButton"));
        midiButton->setAutoExclusive(false);

        gridLayout->addWidget(midiButton, 2, 2, 1, 1);

        ultraStarButton = new QRadioButton(content);
        ultraStarButton->setObjectName(QString::fromUtf8("ultraStarButton"));
        ultraStarButton->setAutoExclusive(false);

        gridLayout->addWidget(ultraStarButton, 2, 1, 1, 1);

        pushButton = new QPushButton(content);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));

        gridLayout->addWidget(pushButton, 0, 3, 1, 1);

        searchInAllButton = new QRadioButton(content);
        searchInAllButton->setObjectName(QString::fromUtf8("searchInAllButton"));
        searchInAllButton->setChecked(true);
        searchInAllButton->setAutoExclusive(false);

        gridLayout->addWidget(searchInAllButton, 1, 3, 1, 1);

        anyTypeButton = new QRadioButton(content);
        anyTypeButton->setObjectName(QString::fromUtf8("anyTypeButton"));
        anyTypeButton->setChecked(true);
        anyTypeButton->setAutoExclusive(false);

        gridLayout->addWidget(anyTypeButton, 2, 3, 1, 1);

        label = new QLabel(content);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout->addWidget(label, 3, 0, 1, 4);

        lineEdit = new QLineEdit(content);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));

        gridLayout->addWidget(lineEdit, 0, 0, 1, 3);

        artistButton = new QRadioButton(content);
        artistButton->setObjectName(QString::fromUtf8("artistButton"));
        artistButton->setAutoExclusive(false);

        gridLayout->addWidget(artistButton, 1, 2, 1, 1);

        label_3 = new QLabel(content);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout->addWidget(label_3, 2, 0, 1, 1);

        windowBar = new SoS::QtGui::WindowBar(SongSearch);
        windowBar->setObjectName(QString::fromUtf8("windowBar"));
        windowBar->setGeometry(QRect(0, 0, 351, 21));
        windowBar->setFrameShape(QFrame::StyledPanel);
        windowBar->setFrameShadow(QFrame::Raised);

        retranslateUi(SongSearch);

        QMetaObject::connectSlotsByName(SongSearch);
    } // setupUi

    void retranslateUi(QWidget *SongSearch)
    {
        SongSearch->setWindowTitle(QApplication::translate("SongSearch", "Form", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("SongSearch", "Search for:", 0, QApplication::UnicodeUTF8));
        titleButton->setText(QApplication::translate("SongSearch", "Title", 0, QApplication::UnicodeUTF8));
        midiButton->setText(QApplication::translate("SongSearch", "Midi/kar", 0, QApplication::UnicodeUTF8));
        ultraStarButton->setText(QApplication::translate("SongSearch", "UltraStar", 0, QApplication::UnicodeUTF8));
        pushButton->setText(QApplication::translate("SongSearch", "PushButton", 0, QApplication::UnicodeUTF8));
        searchInAllButton->setText(QApplication::translate("SongSearch", "Both", 0, QApplication::UnicodeUTF8));
        anyTypeButton->setText(QApplication::translate("SongSearch", "Any", 0, QApplication::UnicodeUTF8));
        label->setText(QString());
        artistButton->setText(QApplication::translate("SongSearch", "Artist", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("SongSearch", "Song type:", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class SongSearch: public Ui_SongSearch {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SONGSEARCH_H
