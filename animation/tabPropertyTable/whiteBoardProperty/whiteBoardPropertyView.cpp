#include "WhiteBoardPropertyView.h"

#include <QToolButton>
#include <QButtonGroup>
#include <QGridLayout>
#include <QLabel>
#include <QGroupBox>
#include <QFontComboBox>

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
    QGroupBox *groupBoxItems = new QGroupBox(tr("Items"));
    QVBoxLayout * vlay = new QVBoxLayout(this);
    vlay->setContentsMargins(10,5,10,5);
    vlay->addWidget(groupBoxItems);
    setObjectName("WhiteBoardPropertyView");
    buttonGroup = new QButtonGroup;
    buttonGroup->setExclusive(false);
    connect(buttonGroup, QOverload<QAbstractButton *>::of(&QButtonGroup::buttonClicked),
            this, &WhiteBoardPropertyView::buttonGroupClicked);

    QGridLayout *layout = new QGridLayout;
    layout->addWidget(createCellWidget(tr("Text"), DiagramType::Diagram_Text), 0, 0);
    layout->addWidget(createCellWidget(tr("pen"), DiagramType::Diagram_Pen), 0, 1);
    layout->addWidget(createCellWidget(tr("Process"), DiagramType::Diagram_Step),0, 2);
    layout->addWidget(createCellWidget(tr("Input"), DiagramType::Diagram_Io), 1, 0);
    layout->addWidget(createCellWidget(tr("oval"), DiagramType::Diagram_Oval), 1, 1);
    layout->addWidget(createCellWidget(tr("triangle"), DiagramType::Diagram_Triangle), 1, 2);

    layout->addWidget(createCellWidget(tr("Conditional"), DiagramType::Diagram_Conditional), 2, 0);
    layout->addWidget(createCellWidget(tr("Line"), DiagramType::Diagram_StartEnd), 2, 1);
    layout->addWidget(createCellWidget(tr("Picture"), DiagramType::Diagram_Pic), 2, 2);
    layout->addWidget(createCellWidget(tr("Select"), DiagramType::Diagram_Sel), 3, 0);
    layout->addWidget(createCellWidget(tr("Delete"), DiagramType::Diagram_Del), 3, 1);

    layout->setRowStretch(4, 10);
    layout->setColumnStretch(3, 10);

    groupBoxItems->setLayout(layout);

    QGroupBox *groupBoxProperty= new QGroupBox(tr("Propertys"));
    QVBoxLayout * vProlay = new QVBoxLayout(this);
    vProlay->setContentsMargins(10,5,10,5);


    QLabel *lText = new QLabel;
    lText->setText(QStringLiteral("文字"));
    lText->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    lText->setFixedWidth(150);

    vProlay->addWidget(lText);
    QFrame *fLineT = new QFrame;
    fLineT->setStyleSheet("border:1px solid rgba(10,10,10, 30);");
    fLineT->setFixedHeight(1);
    vProlay->addWidget(fLineT);

    QLabel *lFont = new QLabel;
    lFont->setText(QStringLiteral("字体:"));
    lFont->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    lFont->setFixedWidth(100);

    fontCombo = new QFontComboBox();
    fontCombo->setMinimumWidth(200);
    fontCombo->setEditable(false);
    connect(fontCombo, &QFontComboBox::currentFontChanged,
            this, &WhiteBoardPropertyView::currentFontChanged);

    QHBoxLayout * FontLay = new QHBoxLayout;
    FontLay->setContentsMargins(0,0,0,0);
    FontLay->setSpacing(5);

    FontLay->addWidget(lFont);
    FontLay->addWidget(fontCombo);
    FontLay->addStretch(1);
    vProlay->addItem(FontLay);

    QLabel *lFontSize = new QLabel;
    lFontSize->setText(QStringLiteral("字体大小:"));
    lFontSize->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    lFontSize->setFixedWidth(100);
    fontSizeCombo = new QComboBox;
    fontSizeCombo->setMinimumWidth(200);
    fontSizeCombo->setEditable(false);
    for (int i = 8; i < 30; i = i + 2)
        fontSizeCombo->addItem(QString().setNum(i));
    QIntValidator *validator = new QIntValidator(2, 64, this);
    fontSizeCombo->setValidator(validator);
    connect(fontSizeCombo, &QComboBox::currentTextChanged,
            this, &WhiteBoardPropertyView::fontSizeChanged);
    QHBoxLayout * FontSizeLay = new QHBoxLayout;
    FontSizeLay->setContentsMargins(0,0,0,0);
    FontSizeLay->setSpacing(5);

    FontSizeLay->addWidget(lFontSize);
    FontSizeLay->addWidget(fontSizeCombo);
    FontSizeLay->addStretch(1);
    vProlay->addItem(FontSizeLay);


    groupBoxProperty->setLayout(vProlay);
    vlay->addWidget(groupBoxProperty);
    vlay->addStretch(1);


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

void WhiteBoardPropertyView::currentFontChanged(const QFont &f)
{
    //
}

void WhiteBoardPropertyView::fontSizeChanged(const QString &)
{
    handleFontChange();
}

void WhiteBoardPropertyView::handleFontChange()
{
    QFont font = fontCombo->currentFont();
    font.setPointSize(fontSizeCombo->currentText().toInt());
    //font.setWeight(boldAction->isChecked() ? QFont::Bold : QFont::Normal);
    //font.setItalic(italicAction->isChecked());
    //font.setUnderline(underlineAction->isChecked());

    //scene->setFont(font);
}
