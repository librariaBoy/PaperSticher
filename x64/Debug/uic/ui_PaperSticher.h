/********************************************************************************
** Form generated from reading UI file 'PaperSticher.ui'
**
** Created by: Qt User Interface Compiler version 6.5.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PAPERSTICHER_H
#define UI_PAPERSTICHER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_PaperSticherClass
{
public:
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QLineEdit *address;
    QLabel *label_2;
    QLineEdit *pic_num;
    QLabel *label_3;
    QLineEdit *file_NO;
    QPushButton *stichButton;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *PaperSticherClass)
    {
        if (PaperSticherClass->objectName().isEmpty())
            PaperSticherClass->setObjectName("PaperSticherClass");
        PaperSticherClass->resize(246, 312);
        centralWidget = new QWidget(PaperSticherClass);
        centralWidget->setObjectName("centralWidget");
        verticalLayout = new QVBoxLayout(centralWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName("verticalLayout");
        label = new QLabel(centralWidget);
        label->setObjectName("label");

        verticalLayout->addWidget(label);

        address = new QLineEdit(centralWidget);
        address->setObjectName("address");

        verticalLayout->addWidget(address);

        label_2 = new QLabel(centralWidget);
        label_2->setObjectName("label_2");

        verticalLayout->addWidget(label_2);

        pic_num = new QLineEdit(centralWidget);
        pic_num->setObjectName("pic_num");

        verticalLayout->addWidget(pic_num);

        label_3 = new QLabel(centralWidget);
        label_3->setObjectName("label_3");

        verticalLayout->addWidget(label_3);

        file_NO = new QLineEdit(centralWidget);
        file_NO->setObjectName("file_NO");

        verticalLayout->addWidget(file_NO);

        stichButton = new QPushButton(centralWidget);
        stichButton->setObjectName("stichButton");

        verticalLayout->addWidget(stichButton);

        PaperSticherClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(PaperSticherClass);
        menuBar->setObjectName("menuBar");
        menuBar->setGeometry(QRect(0, 0, 246, 22));
        PaperSticherClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(PaperSticherClass);
        mainToolBar->setObjectName("mainToolBar");
        PaperSticherClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(PaperSticherClass);
        statusBar->setObjectName("statusBar");
        PaperSticherClass->setStatusBar(statusBar);

        retranslateUi(PaperSticherClass);
        QObject::connect(stichButton, SIGNAL(clicked()), PaperSticherClass, SLOT(on_stich_btn_clicked()));

        QMetaObject::connectSlotsByName(PaperSticherClass);
    } // setupUi

    void retranslateUi(QMainWindow *PaperSticherClass)
    {
        PaperSticherClass->setWindowTitle(QCoreApplication::translate("PaperSticherClass", "PaperSticher", nullptr));
        label->setText(QCoreApplication::translate("PaperSticherClass", "\346\226\207\344\273\266\345\234\260\345\235\200", nullptr));
        label_2->setText(QCoreApplication::translate("PaperSticherClass", "\345\233\276\347\211\207\344\270\252\346\225\260", nullptr));
        label_3->setText(QCoreApplication::translate("PaperSticherClass", "\346\226\207\344\273\266\347\274\226\345\217\267", nullptr));
        stichButton->setText(QCoreApplication::translate("PaperSticherClass", "\345\274\200\345\247\213\346\213\274\346\216\245", nullptr));
    } // retranslateUi

};

namespace Ui {
    class PaperSticherClass: public Ui_PaperSticherClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PAPERSTICHER_H
