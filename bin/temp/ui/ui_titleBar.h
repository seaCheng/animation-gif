/********************************************************************************
** Form generated from reading UI file 'titleBar.ui'
**
** Created by: Qt User Interface Compiler version 6.3.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TITLEBAR_H
#define UI_TITLEBAR_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_titleWid
{
public:
    QVBoxLayout *verticalLayout;
    QFrame *frameSystem;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacerLeft;
    QLabel *labelTitle;
    QSpacerItem *horizontalSpacerRight;
    QPushButton *minimizeButton;
    QPushButton *maximizeButton;
    QPushButton *closeButton;
    QFrame *frameCtrl;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer;

    void setupUi(QWidget *titleWid)
    {
        if (titleWid->objectName().isEmpty())
            titleWid->setObjectName(QString::fromUtf8("titleWid"));
        titleWid->resize(829, 80);
        titleWid->setMinimumSize(QSize(0, 80));
        titleWid->setMaximumSize(QSize(16777215, 80));
        titleWid->setStyleSheet(QString::fromUtf8("\n"
"\n"
"#titleWid{\n"
"background-color:  rgba(185, 185, 185,125);\n"
"color: rgba(185, 185, 185,125);\n"
"border.width:0\n"
"}\n"
"\n"
" #frameCtrl, #frameSystem{\n"
" background-color: transparent;\n"
"}\n"
"\n"
"#minimizeButton {\n"
"  image: url(\":/images/minimum@3x.png\");\n"
"  border-radius: 3px;\n"
"}\n"
"\n"
"\n"
"#minimizeButton, #maximizeButton {\n"
"  background-color:transparent;\n"
"  border-radius: 3px;\n"
"}\n"
"\n"
"#maximizeButton {\n"
"  image: url(\":/images/maximum@3x.png\");\n"
"  \n"
"}\n"
"\n"
"#maximizeButton[max=\"false\"] {\n"
"  image: url(\":/images/maximum@3x.png\");\n"
"  \n"
"}\n"
"\n"
"#maximizeButton[max=\"true\"] {\n"
"  image: url(\":/images/maxOut@3x.png\");\n"
"  \n"
"}\n"
"\n"
"#minimizeButton:hover, #maximizeButton:hover {\n"
"  border-style: none;\n"
"  background-color: #70b7b7c7;\n"
"}\n"
"\n"
"#minimizeButton:pressed, #maximizeButton:pressed {\n"
"  border-style: none;\n"
"  background-color: #80808080;\n"
"}\n"
"\n"
"#maximizeButton:pressed {\n"
"   \n"
"   backg"
                        "round-color: #80808080;\n"
"}\n"
"#closeButton {\n"
"  image: url(\":/images/closeWin@3x.png\");\n"
"  background-color: transparent;\n"
"  border-radius: 3px;\n"
"}\n"
"\n"
"#closeButton:hover {\n"
"  border-style: none;\n"
"  background-color: #e81123;\n"
"}\n"
"\n"
"#closeButton:pressed {\n"
"  border-style: none;\n"
"  background-color: #8c0a15;\n"
"}\n"
""));
        verticalLayout = new QVBoxLayout(titleWid);
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        frameSystem = new QFrame(titleWid);
        frameSystem->setObjectName(QString::fromUtf8("frameSystem"));
        frameSystem->setMinimumSize(QSize(0, 40));
        frameSystem->setMaximumSize(QSize(16777215, 40));
        frameSystem->setFrameShape(QFrame::NoFrame);
        frameSystem->setFrameShadow(QFrame::Plain);
        frameSystem->setLineWidth(0);
        horizontalLayout = new QHBoxLayout(frameSystem);
        horizontalLayout->setSpacing(2);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(140, 4, 2, 4);
        horizontalSpacerLeft = new QSpacerItem(200, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacerLeft);

        labelTitle = new QLabel(frameSystem);
        labelTitle->setObjectName(QString::fromUtf8("labelTitle"));
        labelTitle->setStyleSheet(QString::fromUtf8("font-size: 18px;\n"
"background-color: rgba(0, 0, 0, 0);\n"
"  font-weight: 500;\n"
"  text-align: center;\n"
"  color: #fff;\n"
""));

        horizontalLayout->addWidget(labelTitle);

        horizontalSpacerRight = new QSpacerItem(200, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacerRight);

        minimizeButton = new QPushButton(frameSystem);
        minimizeButton->setObjectName(QString::fromUtf8("minimizeButton"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(minimizeButton->sizePolicy().hasHeightForWidth());
        minimizeButton->setSizePolicy(sizePolicy);
        minimizeButton->setMinimumSize(QSize(45, 26));
        minimizeButton->setMaximumSize(QSize(45, 26));
        minimizeButton->setFocusPolicy(Qt::NoFocus);
        minimizeButton->setContextMenuPolicy(Qt::NoContextMenu);
        minimizeButton->setIconSize(QSize(34, 26));

        horizontalLayout->addWidget(minimizeButton);

        maximizeButton = new QPushButton(frameSystem);
        maximizeButton->setObjectName(QString::fromUtf8("maximizeButton"));
        sizePolicy.setHeightForWidth(maximizeButton->sizePolicy().hasHeightForWidth());
        maximizeButton->setSizePolicy(sizePolicy);
        maximizeButton->setMinimumSize(QSize(45, 26));
        maximizeButton->setMaximumSize(QSize(45, 26));
        maximizeButton->setFocusPolicy(Qt::NoFocus);
        maximizeButton->setContextMenuPolicy(Qt::NoContextMenu);
        maximizeButton->setIconSize(QSize(34, 26));

        horizontalLayout->addWidget(maximizeButton);

        closeButton = new QPushButton(frameSystem);
        closeButton->setObjectName(QString::fromUtf8("closeButton"));
        sizePolicy.setHeightForWidth(closeButton->sizePolicy().hasHeightForWidth());
        closeButton->setSizePolicy(sizePolicy);
        closeButton->setMinimumSize(QSize(45, 26));
        closeButton->setMaximumSize(QSize(45, 26));
        closeButton->setFocusPolicy(Qt::NoFocus);
        closeButton->setContextMenuPolicy(Qt::NoContextMenu);
        closeButton->setIconSize(QSize(34, 26));

        horizontalLayout->addWidget(closeButton);


        verticalLayout->addWidget(frameSystem);

        frameCtrl = new QFrame(titleWid);
        frameCtrl->setObjectName(QString::fromUtf8("frameCtrl"));
        frameCtrl->setMinimumSize(QSize(0, 40));
        frameCtrl->setMaximumSize(QSize(16777215, 40));
        frameCtrl->setStyleSheet(QString::fromUtf8(""));
        frameCtrl->setFrameShape(QFrame::NoFrame);
        frameCtrl->setFrameShadow(QFrame::Plain);
        frameCtrl->setLineWidth(0);
        frameCtrl->setMidLineWidth(0);
        horizontalLayout_2 = new QHBoxLayout(frameCtrl);
        horizontalLayout_2->setSpacing(8);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setSizeConstraint(QLayout::SetDefaultConstraint);
        horizontalLayout_2->setContentsMargins(2, 2, 2, 2);
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);


        verticalLayout->addWidget(frameCtrl);


        retranslateUi(titleWid);

        QMetaObject::connectSlotsByName(titleWid);
    } // setupUi

    void retranslateUi(QWidget *titleWid)
    {
        titleWid->setWindowTitle(QCoreApplication::translate("titleWid", "Form", nullptr));
        labelTitle->setText(QCoreApplication::translate("titleWid", "AnimationGif", nullptr));
#if QT_CONFIG(tooltip)
        minimizeButton->setToolTip(QString());
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        maximizeButton->setToolTip(QString());
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        closeButton->setToolTip(QString());
#endif // QT_CONFIG(tooltip)
    } // retranslateUi

};

namespace Ui {
    class titleWid: public Ui_titleWid {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TITLEBAR_H
