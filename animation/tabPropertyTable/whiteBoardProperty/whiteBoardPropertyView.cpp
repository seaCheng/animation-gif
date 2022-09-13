#include "WhiteBoardPropertyView.h"

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
    layout->addWidget(createCellWidget(tr("Process"), DiagramType::Diagram_Step),0, 2);
    layout->addWidget(createCellWidget(tr("Input"), DiagramType::Diagram_Io), 1, 0);
    layout->addWidget(createCellWidget(tr("oval"), DiagramType::Diagram_Oval), 1, 1);
    layout->addWidget(createCellWidget(tr("triangle"), DiagramType::Diagram_Triangle), 1, 2);
    layout->addWidget(createCellWidget(tr("pen"), DiagramType::Diagram_Pen), 2, 0);
    layout->addWidget(createCellWidget(tr("Line"), DiagramType::Diagram_StartEnd), 2, 1);
    layout->addWidget(createCellWidget(tr("Select"), DiagramType::Diagram_Sel), 2, 2);

    layout->setRowStretch(3, 10);
    layout->setColumnStretch(3, 10);

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
        {
            myButton->setChecked(false);
        }
    }

    button->setChecked(true);
    const int id = buttonGroup->id(button);
    emit s_sceneItemInsert((DiagramType)id);
}

