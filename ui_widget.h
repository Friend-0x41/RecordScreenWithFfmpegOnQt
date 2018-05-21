/********************************************************************************
** Form generated from reading UI file 'widget.ui'
**
** Created by: Qt User Interface Compiler version 5.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGET_H
#define UI_WIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Widget
{
public:
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout_2;
    QVBoxLayout *verticalLayout_2;
    QPushButton *startBtn;
    QPushButton *selectRectBtn;
    QPushButton *stopBtn;
    QVBoxLayout *verticalLayout;
    QCheckBox *hideCheckBox;
    QCheckBox *infoCheckBox;
    QCheckBox *passCheckBox;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLabel *pathLabel;
    QPushButton *randBtn;
    QPushButton *pathBtn;
    QTextEdit *textEdit;

    void setupUi(QWidget *Widget)
    {
        if (Widget->objectName().isEmpty())
            Widget->setObjectName(QStringLiteral("Widget"));
        Widget->setEnabled(true);
        Widget->resize(338, 254);
        verticalLayout_3 = new QVBoxLayout(Widget);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        startBtn = new QPushButton(Widget);
        startBtn->setObjectName(QStringLiteral("startBtn"));

        verticalLayout_2->addWidget(startBtn);

        selectRectBtn = new QPushButton(Widget);
        selectRectBtn->setObjectName(QStringLiteral("selectRectBtn"));

        verticalLayout_2->addWidget(selectRectBtn);

        stopBtn = new QPushButton(Widget);
        stopBtn->setObjectName(QStringLiteral("stopBtn"));
        stopBtn->setEnabled(false);

        verticalLayout_2->addWidget(stopBtn);


        horizontalLayout_2->addLayout(verticalLayout_2);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        hideCheckBox = new QCheckBox(Widget);
        hideCheckBox->setObjectName(QStringLiteral("hideCheckBox"));

        verticalLayout->addWidget(hideCheckBox);

        infoCheckBox = new QCheckBox(Widget);
        infoCheckBox->setObjectName(QStringLiteral("infoCheckBox"));
        infoCheckBox->setChecked(true);

        verticalLayout->addWidget(infoCheckBox);

        passCheckBox = new QCheckBox(Widget);
        passCheckBox->setObjectName(QStringLiteral("passCheckBox"));
        passCheckBox->setEnabled(true);
        passCheckBox->setChecked(true);

        verticalLayout->addWidget(passCheckBox);


        horizontalLayout_2->addLayout(verticalLayout);


        verticalLayout_3->addLayout(horizontalLayout_2);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label = new QLabel(Widget);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout->addWidget(label);

        pathLabel = new QLabel(Widget);
        pathLabel->setObjectName(QStringLiteral("pathLabel"));

        horizontalLayout->addWidget(pathLabel);

        randBtn = new QPushButton(Widget);
        randBtn->setObjectName(QStringLiteral("randBtn"));

        horizontalLayout->addWidget(randBtn);

        pathBtn = new QPushButton(Widget);
        pathBtn->setObjectName(QStringLiteral("pathBtn"));

        horizontalLayout->addWidget(pathBtn);


        verticalLayout_3->addLayout(horizontalLayout);

        textEdit = new QTextEdit(Widget);
        textEdit->setObjectName(QStringLiteral("textEdit"));
        textEdit->setEnabled(true);
        textEdit->setReadOnly(true);

        verticalLayout_3->addWidget(textEdit);


        retranslateUi(Widget);

        QMetaObject::connectSlotsByName(Widget);
    } // setupUi

    void retranslateUi(QWidget *Widget)
    {
        Widget->setWindowTitle(QApplication::translate("Widget", "\345\275\225\345\210\266\345\261\217\345\271\225", nullptr));
        startBtn->setText(QApplication::translate("Widget", "\345\274\200\345\247\213\345\275\225\345\210\266", nullptr));
        selectRectBtn->setText(QApplication::translate("Widget", "\351\200\211\346\213\251\345\275\225\345\210\266\345\214\272\345\237\237", nullptr));
        stopBtn->setText(QApplication::translate("Widget", "\345\201\234\346\255\242\345\275\225\345\210\266", nullptr));
        hideCheckBox->setText(QApplication::translate("Widget", "\350\207\252\345\212\250\351\232\220\350\227\217", nullptr));
        infoCheckBox->setText(QApplication::translate("Widget", "\345\256\214\346\210\220\346\217\220\347\244\272", nullptr));
        passCheckBox->setText(QApplication::translate("Widget", "\345\216\213\347\274\251", nullptr));
        label->setText(QApplication::translate("Widget", "\344\277\235\345\255\230\350\267\257\345\276\204", nullptr));
        pathLabel->setText(QApplication::translate("Widget", "./Save/", nullptr));
        randBtn->setText(QApplication::translate("Widget", "\351\232\217\344\276\277", nullptr));
        pathBtn->setText(QApplication::translate("Widget", "\346\233\264\346\224\271", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Widget: public Ui_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H
