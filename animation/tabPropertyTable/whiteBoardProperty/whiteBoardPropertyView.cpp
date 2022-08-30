﻿#include "WhiteBoardPropertyView.h"

#include <QToolButton>
#include <QButtonGroup>
#include <QGridLayout>
#include <QLabel>

WhiteBoardPropertyView::WhiteBoardPropertyView()
{
    initial();
    setConnect();
}

void WhiteBoardPropertyView::setConnect()
{
    //
}
void WhiteBoardPropertyView::initial()
{
    setObjectName("WhiteBoardPropertyView");
    buttonGroup = new QButtonGroup;
    buttonGroup->setExclusive(false);
    connect(buttonGroup, QOverload<QAbstractButton *>::of(&QButtonGroup::buttonClicked),
            this, &WhiteBoardPropertyView::buttonGroupClicked);

    QGridLayout *layout = new QGridLayout;
    layout->addWidget(createCellWidget(tr("Text"), DiagramType::Diagram_Text), 0, 0);
    layout->addWidget(createCellWidget(tr("Conditional"), DiagramType::Diagram_Conditional), 0, 1);
    layout->addWidget(createCellWidget(tr("Process"), DiagramType::Diagram_Step),1, 0);
    layout->addWidget(createCellWidget(tr("Input"), DiagramType::Diagram_Io), 1, 1);

    layout->setRowStretch(3, 10);
    layout->setColumnStretch(2, 10);

    setLayout(layout);

}

QWidget * WhiteBoardPropertyView::createCellWidget(const QString &text, DiagramType type)
{

    QToolButton *button = new QToolButton;
    button->setCheckable(true);
    button->setObjectName(text);
    button->setFixedSize(50,50);
    button->setIconSize(QSize(45,45));
    buttonGroup->addButton(button, int(type));

    QGridLayout *layout = new QGridLayout;
    layout->addWidget(button, 0, 0, Qt::AlignHCenter);
    layout->addWidget(new QLabel(text), 1, 0, Qt::AlignCenter);

    QWidget *widget = new QWidget;
    widget->setLayout(layout);

    return widget;
}

void WhiteBoardPropertyView::buttonGroupClicked(QAbstractButton *button)
{
    const QList<QAbstractButton *> buttons = buttonGroup->buttons();
    for (QAbstractButton *myButton : buttons) {
        if (myButton != button)
            button->setChecked(false);
    }
    const int id = buttonGroup->id(button);
    emit s_sceneItemInsert((DiagramType)id);
}
