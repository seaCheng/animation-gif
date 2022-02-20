/********************************************************************************
** Form generated from reading UI file 'animationMW.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
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
#include <picScaleViewComp.h>
#include "graphicsViewComp.h"

QT_BEGIN_NAMESPACE

class Ui_animationMW
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QFrame *topView;
    QHBoxLayout *horizontalLayout;
    GraphicsViewComp *leftView;
    QFrame *rightView;
    QScrollArea *scrollAreaPicScal;
    PicScaleViewComp *scrollAreaWidgetContents;

    void setupUi(QMainWindow *animationMW)
    {
        if (animationMW->objectName().isEmpty())
            animationMW->setObjectName(QString::fromUtf8("animationMW"));
        animationMW->resize(800, 543);
        centralwidget = new QWidget(animationMW);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        topView = new QFrame(centralwidget);
        topView->setObjectName(QString::fromUtf8("topView"));
        topView->setFrameShape(QFrame::NoFrame);
        topView->setFrameShadow(QFrame::Raised);
        topView->setLineWidth(0);
        horizontalLayout = new QHBoxLayout(topView);
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        leftView = new GraphicsViewComp(topView);
        leftView->setObjectName(QString::fromUtf8("leftView"));

        horizontalLayout->addWidget(leftView);

        rightView = new QFrame(topView);
        rightView->setObjectName(QString::fromUtf8("rightView"));
        rightView->setMinimumSize(QSize(220, 0));
        rightView->setMaximumSize(QSize(220, 16777215));
        rightView->setFrameShape(QFrame::NoFrame);
        rightView->setFrameShadow(QFrame::Raised);
        rightView->setLineWidth(0);

        horizontalLayout->addWidget(rightView);


        verticalLayout->addWidget(topView);

        scrollAreaPicScal = new QScrollArea(centralwidget);
        scrollAreaPicScal->setObjectName(QString::fromUtf8("scrollAreaPicScal"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(scrollAreaPicScal->sizePolicy().hasHeightForWidth());
        scrollAreaPicScal->setSizePolicy(sizePolicy);
        scrollAreaPicScal->setMinimumSize(QSize(0, 200));
        scrollAreaPicScal->setMaximumSize(QSize(16777215, 200));
        scrollAreaPicScal->setStyleSheet(QString::fromUtf8(""));
        scrollAreaPicScal->setFrameShape(QFrame::NoFrame);
        scrollAreaPicScal->setLineWidth(0);
        scrollAreaPicScal->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        scrollAreaPicScal->setWidgetResizable(true);
        scrollAreaWidgetContents = new PicScaleViewComp();
        scrollAreaWidgetContents->setObjectName(QString::fromUtf8("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 800, 180));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(scrollAreaWidgetContents->sizePolicy().hasHeightForWidth());
        scrollAreaWidgetContents->setSizePolicy(sizePolicy1);
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
        animationMW->setWindowTitle(QCoreApplication::translate("animationMW", "MainWindow", nullptr));
    } // retranslateUi

};

namespace Ui {
    class animationMW: public Ui_animationMW {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ANIMATIONMW_H
