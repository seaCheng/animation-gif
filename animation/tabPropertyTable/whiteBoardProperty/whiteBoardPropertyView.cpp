#include "WhiteBoardPropertyView.h"

#include <QToolButton>
#include <QButtonGroup>
#include <QGridLayout>
#include <QLabel>
#include <QGroupBox>
#include <QFontComboBox>
#include <QMenu>
#include <QPainter>
#include <QAction>

WhiteBoardPropertyView::WhiteBoardPropertyView(std::shared_ptr<whiteBoardProInf> pro)
    :QFrame(),
      proInf(pro)
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

    QLabel *lFontColor = new QLabel;
    lFontColor->setText(QStringLiteral("颜色:"));
    lFontColor->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    lFontColor->setFixedWidth(100);

    fontColorToolButton = new QToolButton;
    fontColorToolButton->setMinimumWidth(100);
    fontColorToolButton->setPopupMode(QToolButton::InstantPopup);
    fontColorToolButton->setToolButtonStyle(Qt::ToolButtonIconOnly);
    fontColorToolButton->setArrowType(Qt::NoArrow);
    fontColorToolButton->setMenu(createColorMenu(SLOT(textColorChanged()), Qt::black));
    textAction = fontColorToolButton->menu()->defaultAction();
    fontColorToolButton->setIcon(createColorToolButtonIcon(":images/text.png", Qt::black));
    fontColorToolButton->setAutoFillBackground(true);
    fontColorToolButton->setStyleSheet("\
        QToolButton::menu-indicator{\
        image: none;\
    }");

    connect(fontColorToolButton, &QAbstractButton::clicked,
            this, &WhiteBoardPropertyView::textButtonTriggered);

    QHBoxLayout * FontColorLay = new QHBoxLayout;
    FontColorLay->setContentsMargins(0,0,0,0);
    FontColorLay->setSpacing(5);

    FontColorLay->addWidget(lFontColor);
    FontColorLay->addWidget(fontColorToolButton);
    FontColorLay->addStretch(1);
    vProlay->addItem(FontColorLay);

    groupBoxProperty->setLayout(vProlay);
    vlay->addWidget(groupBoxProperty);
    vlay->addStretch(1);

    handleFontChange();
}

void WhiteBoardPropertyView::textColorChanged()
{
    textAction = qobject_cast<QAction *>(sender());
    fontColorToolButton->setIcon(createColorToolButtonIcon(
                                     ":images/text.png",
                                     qvariant_cast<QColor>(textAction->data())));
    textButtonTriggered();
}

QMenu *WhiteBoardPropertyView::createColorMenu(const char *slot, QColor defaultColor)
{
    QList<QColor> colors;
    colors << Qt::black << Qt::white << Qt::red << Qt::blue << Qt::yellow;
    QStringList names;
    names << tr("black") << tr("white") << tr("red") << tr("blue")
          << tr("yellow");

    QMenu *colorMenu = new QMenu(this);
    for (int i = 0; i < colors.count(); ++i) {
        QAction *action = new QAction(names.at(i), this);
        action->setData(colors.at(i));
        action->setIcon(createColorIcon(colors.at(i)));
        connect(action, SIGNAL(triggered()), this, slot);
        colorMenu->addAction(action);
        if (colors.at(i) == defaultColor)
            colorMenu->setDefaultAction(action);
    }
    return colorMenu;
}

QIcon WhiteBoardPropertyView::createColorIcon(QColor color)
{
    QPixmap pixmap(20, 20);
    QPainter painter(&pixmap);
    painter.setPen(Qt::NoPen);
    painter.fillRect(QRect(0, 0, 20, 20), color);

    return QIcon(pixmap);
}

QIcon WhiteBoardPropertyView::createColorToolButtonIcon(const QString &imageFile, QColor color)
{
    QPixmap pixmap(50, 80);
    pixmap.fill(Qt::transparent);
    QPainter painter(&pixmap);
    QPixmap image(imageFile);
    // Draw icon centred horizontally on button.
    QRect target(4, 0, 42, 43);
    QRect source(0, 0, 42, 43);
    painter.fillRect(QRect(0, 60, 50, 80), color);
    painter.drawPixmap(target, image, source);

    return QIcon(pixmap);
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
    handleFontChange();
}

void WhiteBoardPropertyView::fontSizeChanged(const QString &)
{
    handleFontChange();
}

void WhiteBoardPropertyView::textButtonTriggered()
{
    proInf->textColor = qvariant_cast<QColor>(textAction->data());
    emit s_whiteBoardProFresh();
}

void WhiteBoardPropertyView::handleFontChange()
{
    QFont nfont = fontCombo->currentFont();
    nfont.setPointSize(fontSizeCombo->currentText().toInt());
    //font.setWeight(boldAction->isChecked() ? QFont::Bold : QFont::Normal);
    //font.setItalic(italicAction->isChecked());
    //font.setUnderline(underlineAction->isChecked());

    proInf->font =  nfont;

    emit s_whiteBoardProFresh();
}
