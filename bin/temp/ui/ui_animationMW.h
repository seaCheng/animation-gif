/********************************************************************************
** Form generated from reading UI file 'animationMW.ui'
**
** Created by: Qt User Interface Compiler version 6.3.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ANIMATIONMW_H
#define UI_ANIMATIONMW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "picScaleViewComp.h"

QT_BEGIN_NAMESPACE

class Ui_animationMW
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QFrame *titleBar;
    QHBoxLayout *titleLayout;
    QFrame *topView;
    QHBoxLayout *horizontalLayout;
    QWidget *leftView;
    QFrame *rightView;
    QScrollArea *scrollAreaPicScal;
    PicScaleViewComp *scrollAreaWidgetContents;

    void setupUi(QMainWindow *animationMW)
    {
        if (animationMW->objectName().isEmpty())
            animationMW->setObjectName(QString::fromUtf8("animationMW"));
        animationMW->resize(525, 404);
        animationMW->setStyleSheet(QString::fromUtf8(""));
        centralwidget = new QWidget(animationMW);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        titleBar = new QFrame(centralwidget);
        titleBar->setObjectName(QString::fromUtf8("titleBar"));
        titleBar->setMinimumSize(QSize(0, 85));
        titleBar->setMaximumSize(QSize(16777215, 85));
        titleBar->setStyleSheet(QString::fromUtf8("background-color: rgba(185, 185, 185,125);"));
        titleBar->setFrameShape(QFrame::NoFrame);
        titleBar->setFrameShadow(QFrame::Plain);
        titleBar->setLineWidth(0);
        titleLayout = new QHBoxLayout(titleBar);
        titleLayout->setSpacing(0);
        titleLayout->setObjectName(QString::fromUtf8("titleLayout"));
        titleLayout->setContentsMargins(0, 0, 0, 0);

        verticalLayout->addWidget(titleBar);

        topView = new QFrame(centralwidget);
        topView->setObjectName(QString::fromUtf8("topView"));
        topView->setFrameShape(QFrame::NoFrame);
        topView->setFrameShadow(QFrame::Raised);
        topView->setLineWidth(0);
        horizontalLayout = new QHBoxLayout(topView);
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        leftView = new QWidget(topView);
        leftView->setObjectName(QString::fromUtf8("leftView"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(leftView->sizePolicy().hasHeightForWidth());
        leftView->setSizePolicy(sizePolicy);

        horizontalLayout->addWidget(leftView);

        rightView = new QFrame(topView);
        rightView->setObjectName(QString::fromUtf8("rightView"));
        QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(rightView->sizePolicy().hasHeightForWidth());
        rightView->setSizePolicy(sizePolicy1);
        rightView->setMinimumSize(QSize(120, 0));
        rightView->setMaximumSize(QSize(16777215, 16777215));
        rightView->setStyleSheet(QString::fromUtf8(""));
        rightView->setFrameShape(QFrame::NoFrame);
        rightView->setFrameShadow(QFrame::Raised);
        rightView->setLineWidth(0);

        horizontalLayout->addWidget(rightView);


        verticalLayout->addWidget(topView);

        scrollAreaPicScal = new QScrollArea(centralwidget);
        scrollAreaPicScal->setObjectName(QString::fromUtf8("scrollAreaPicScal"));
        QSizePolicy sizePolicy2(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(scrollAreaPicScal->sizePolicy().hasHeightForWidth());
        scrollAreaPicScal->setSizePolicy(sizePolicy2);
        scrollAreaPicScal->setMinimumSize(QSize(0, 200));
        scrollAreaPicScal->setMaximumSize(QSize(16777215, 200));
        scrollAreaPicScal->setStyleSheet(QString::fromUtf8(""));
        scrollAreaPicScal->setFrameShape(QFrame::NoFrame);
        scrollAreaPicScal->setLineWidth(0);
        scrollAreaPicScal->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        scrollAreaPicScal->setWidgetResizable(true);
        scrollAreaWidgetContents = new PicScaleViewComp();
        scrollAreaWidgetContents->setObjectName(QString::fromUtf8("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 525, 180));
        QSizePolicy sizePolicy3(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(scrollAreaWidgetContents->sizePolicy().hasHeightForWidth());
        scrollAreaWidgetContents->setSizePolicy(sizePolicy3);
        scrollAreaWidgetContents->setMinimumSize(QSize(0, 180));
        scrollAreaWidgetContents->setMaximumSize(QSize(16777215, 180));
        scrollAreaPicScal->setWidget(scrollAreaWidgetContents);

        verticalLayout->addWidget(scrollAreaPicScal);

        animationMW->setCentralWidget(centralwidget);

        retranslateUi(animationMW);

        QMetaObject::connectSlotsByName(animationMW);
    } // setupUi

    void retranslateUi(QMainWindow *animationMW)
    {
        animationMW->setWindowTitle(QCoreApplication::translate("animationMW", "AnimationGif", nullptr));
    } // retranslateUi

};

namespace Ui {
    class animationMW: public Ui_animationMW {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ANIMATIONMW_H
