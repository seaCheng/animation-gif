#include "WhiteBoardPropertyView.h"
#include "commonPropertyView.h"

#include <QToolButton>
#include <QButtonGroup>
#include <QGridLayout>
#include <QLabel>
#include <QGroupBox>
#include <QFontComboBox>
#include <QMenu>
#include <QPainter>
#include <QAction>
#include <QCheckBox>
#include <Qt>
#include <QColorDialog>

WhiteBoardPropertyView::WhiteBoardPropertyView(std::shared_ptr<whiteBoardProInf> pro)
    :QFrame(),
      proInf(pro)
{
    initial();
    setConnect();
}

void WhiteBoardPropertyView::setConnect()
{
    connect(buttonGroup, QOverload<QAbstractButton *>::of(&QButtonGroup::buttonClicked),
            this, &WhiteBoardPropertyView::buttonGroupClicked);

    connect(fontCombo, &QFontComboBox::currentFontChanged,
            this, &WhiteBoardPropertyView::currentFontChanged);

    connect(fontSizeCombo, &QComboBox::currentTextChanged,
            this, &WhiteBoardPropertyView::fontSizeChanged);

    connect(fontColorToolButton, &QAbstractButton::clicked,
            this, &WhiteBoardPropertyView::textButtonTriggered);

    connect(ckBold, &QCheckBox::clicked,
            this, [=](){
        handleFontChange();
    });

    connect(ckItalic, &QCheckBox::clicked,
            this, [=](){
        handleFontChange();
    });

    connect(ckUnderLine, &QCheckBox::clicked,
            this, [=](){
        handleFontChange();
    });

    connect(fPathColor, &QColorFrame::s_clicked,
            this, [&](){
        colorType = color_path;
        colorDialog->setCurrentColor(proInf->pathInfmation.pathColor);
        colorDialog->exec();
    });

    connect(fPathcontourColor, &QColorFrame::s_clicked,
            this, [&](){
        colorType = color_pathContour;
        colorDialog->setCurrentColor(proInf->pathInfmation.pathContourcolor);
        colorDialog->exec();
    });

    connect(fItemBoardColor, &QColorFrame::s_clicked,
            this, [&](){
        colorType = color_itemBoard;
        colorDialog->setCurrentColor(proInf->itemInfmation.itemBoardcolor);
        colorDialog->exec();
    });

    connect(fItemColor, &QColorFrame::s_clicked,
            this, [&](){
        colorType = color_item;
        colorDialog->setCurrentColor(proInf->itemInfmation.itemColor);
        colorDialog->exec();
    });

    connect(capStyles, &QComboBox::currentIndexChanged,
            this, [&](int index){
        proInf->pathInfmation.capStyle = (Qt::PenCapStyle)capStyles->currentData().toInt();
        emit s_whiteBoardProFresh();
    });

    connect(joinStyles, &QComboBox::currentIndexChanged,
            this, [&](int index){
        proInf->pathInfmation.joinStyle = (Qt::PenJoinStyle)joinStyles->currentData().toInt();
        emit s_whiteBoardProFresh();
    });

    connect(penStyles, &QComboBox::currentIndexChanged,
            this, [&](int index){
        proInf->pathInfmation.penStyle = (Qt::PenStyle)penStyles->currentData().toInt();
        emit s_whiteBoardProFresh();
    });

    connect(penPathWidth, &QComboBox::currentIndexChanged,
            this, [&](int index){
        proInf->pathInfmation.penPathWidth = penPathWidth->currentText().toInt();
        emit s_whiteBoardProFresh();
    });

    connect(penPathcontourWidth, &QComboBox::currentIndexChanged,
            this, [&](int index){
        proInf->pathInfmation.penPathcontourWidth = penPathcontourWidth->currentText().toInt();
        emit s_whiteBoardProFresh();
    });

    connect(penItemWidth, &QComboBox::currentIndexChanged,
            this, [&](int index){
        proInf->itemInfmation.penBoardWidth = penItemWidth->currentText().toInt();
        emit s_whiteBoardProFresh();
    });

    connect(penItemStyles, &QComboBox::currentIndexChanged,
            this, [&](int index){
        proInf->itemInfmation.penStyle = (Qt::PenStyle)penItemStyles->currentData().toInt();
        emit s_whiteBoardProFresh();
    });

    connect(colorDialog, &QColorDialog::currentColorChanged, this, [&](const QColor &color){

        if (color.isValid())
        {
            switch (colorType) {
            case color_path:
                fPathColor->setGifColor(color);
                proInf->pathInfmation.pathColor = color;
                break;
            case color_pathContour:
                fPathcontourColor->setGifColor(color);
                proInf->pathInfmation.pathContourcolor = color;
                break;
            case color_item:
                fItemColor->setGifColor(color);
                proInf->itemInfmation.itemColor = color;
                break;
            case color_itemBoard:
                fItemBoardColor->setGifColor(color);
                proInf->itemInfmation.itemBoardcolor = color;
                break;
            default:
                break;
            }

            emit s_whiteBoardProFresh();

        }

    });


}
void WhiteBoardPropertyView::initial()
{
    const QColorDialog::ColorDialogOptions options = QFlag(QColorDialog::ShowAlphaChannel | QColorDialog::NoButtons);
    colorDialog = new QColorDialog(this);
    colorDialog->setCurrentColor(Qt::white);
    colorDialog->setOptions(options);

    QGroupBox *groupBoxItems = new QGroupBox(tr("Items"));
    QVBoxLayout * vlay = new QVBoxLayout(this);
    vlay->setContentsMargins(10,5,10,5);
    vlay->addWidget(groupBoxItems);
    setObjectName("WhiteBoardPropertyView");
    buttonGroup = new QButtonGroup;
    buttonGroup->setExclusive(false);

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
    fontCombo->setFixedWidth(200);
    fontCombo->setEditable(false);
    fontCombo->setCurrentIndex(10);

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
    fontSizeCombo->setFixedWidth(200);
    fontSizeCombo->setEditable(false);
    for (int i = 8; i < 30; i = i + 2)
        fontSizeCombo->addItem(QString().setNum(i));
    QIntValidator *validator = new QIntValidator(2, 64, this);
    fontSizeCombo->setValidator(validator);

    fontSizeCombo->setCurrentIndex(5);
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
    fontColorToolButton->setFixedSize(60,30);
    fontColorToolButton->setPopupMode(QToolButton::InstantPopup);
    fontColorToolButton->setToolButtonStyle(Qt::ToolButtonIconOnly);
    fontColorToolButton->setArrowType(Qt::NoArrow);
    fontColorToolButton->setMenu(createColorMenu(SLOT(textColorChanged()), Qt::blue));
    textAction = fontColorToolButton->menu()->defaultAction();
    fontColorToolButton->setIcon(createColorToolButtonIcon(":images/text.png", Qt::blue));
    fontColorToolButton->setAutoFillBackground(true);
    fontColorToolButton->setStyleSheet("\
        QToolButton::menu-indicator{\
        image: none;\
    }");

    QHBoxLayout * FontColorLay = new QHBoxLayout;
    FontColorLay->setContentsMargins(0,0,0,0);
    FontColorLay->setSpacing(5);

    FontColorLay->addWidget(lFontColor);
    FontColorLay->addWidget(fontColorToolButton);
    FontColorLay->addStretch(1);
    vProlay->addItem(FontColorLay);

    QLabel *lFontStyle = new QLabel;
    lFontStyle->setText(QStringLiteral("样式:"));
    lFontStyle->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    lFontStyle->setFixedWidth(100);

    ckBold = new QCheckBox;
    ckBold->setText(QStringLiteral("Bold"));

    ckItalic = new QCheckBox;
    ckItalic->setText(QStringLiteral("Italic"));

    ckUnderLine = new QCheckBox;
    ckUnderLine->setText(QStringLiteral("UnderLine"));

    QHBoxLayout * FontStyleLay = new QHBoxLayout;
    FontStyleLay->setContentsMargins(0,0,0,0);
    FontStyleLay->setSpacing(5);

    FontStyleLay->addWidget(lFontStyle);
    FontStyleLay->addWidget(ckBold);
    FontStyleLay->addSpacing(5);
    FontStyleLay->addWidget(ckItalic);
    FontStyleLay->addSpacing(5);
    FontStyleLay->addWidget(ckUnderLine);
    FontStyleLay->addStretch(1);
    vProlay->addItem(FontStyleLay);
    vProlay->addSpacing(5);

    //画笔
    QLabel *lColoredPen = new QLabel;
    lColoredPen->setText(QStringLiteral("画笔"));
    lColoredPen->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    lColoredPen->setFixedWidth(150);

    vProlay->addWidget(lColoredPen);
    QFrame *fLineCP = new QFrame;
    fLineCP->setStyleSheet("border:1px solid rgba(10,10,10, 30);");
    fLineCP->setFixedHeight(1);
    vProlay->addWidget(fLineCP);

    QLabel *lCapStyle = new QLabel;
    lCapStyle->setText(QStringLiteral("笔帽:"));
    lCapStyle->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    lCapStyle->setFixedWidth(100);
    capStyles = new QComboBox;
    capStyles->setFixedWidth(200);
    capStyles->setEditable(false);

    capStyles->addItem(QStringLiteral("FlatCap"), (int)Qt::FlatCap);
    capStyles->addItem(QStringLiteral("SquareCap"), (int)Qt::SquareCap);
    capStyles->addItem(QStringLiteral("RoundCap"), (int)Qt::RoundCap);
    capStyles->setCurrentIndex(2);

    QHBoxLayout * capStyleLay = new QHBoxLayout;
    capStyleLay->setContentsMargins(0,0,0,0);
    capStyleLay->setSpacing(5);

    capStyleLay->addWidget(lCapStyle);
    capStyleLay->addWidget(capStyles);

    capStyleLay->addStretch(1);
    vProlay->addItem(capStyleLay);

    QLabel *lJoinStyle = new QLabel;
    lJoinStyle->setText(QStringLiteral("连接:"));
    lJoinStyle->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    lJoinStyle->setFixedWidth(100);
    joinStyles = new QComboBox;
    joinStyles->setFixedWidth(200);
    joinStyles->setEditable(false);

    joinStyles->addItem(QStringLiteral("MiterJoin"), (int)Qt::MiterJoin);
    joinStyles->addItem(QStringLiteral("BevelJoin"), (int)Qt::BevelJoin);
    joinStyles->addItem(QStringLiteral("RoundJoin"), (int)Qt::RoundJoin);
    joinStyles->addItem(QStringLiteral("SvgMiterJoin"), (int)Qt::SvgMiterJoin);
    joinStyles->setCurrentIndex(2);

    QHBoxLayout * joinStyleLay = new QHBoxLayout;
    joinStyleLay->setContentsMargins(0,0,0,0);
    joinStyleLay->setSpacing(5);

    joinStyleLay->addWidget(lJoinStyle);
    joinStyleLay->addWidget(joinStyles);

    joinStyleLay->addStretch(1);
    vProlay->addItem(joinStyleLay);

    //虚线
    QLabel *lPenStyle = new QLabel;
    lPenStyle->setText(QStringLiteral("虚线:"));
    lPenStyle->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    lPenStyle->setFixedWidth(100);
    penStyles = new QComboBox;
    penStyles->setFixedWidth(200);
    penStyles->setEditable(false);

    penStyles->addItem(QStringLiteral("NoPen"), (int)Qt::NoPen);
    penStyles->addItem(QStringLiteral("SolidLine"), (int)Qt::SolidLine);
    penStyles->addItem(QStringLiteral("DashLine"), (int)Qt::DashLine);
    penStyles->addItem(QStringLiteral("DotLine"), (int)Qt::DotLine);
    penStyles->addItem(QStringLiteral("DashDotLine"), (int)Qt::DashDotLine);
    penStyles->addItem(QStringLiteral("DashDotDotLine"), (int)Qt::DashDotDotLine);
    penStyles->addItem(QStringLiteral("CustomDashLine"), (int)Qt::CustomDashLine);
    penStyles->setCurrentIndex(1);

    QHBoxLayout * penStyleLay = new QHBoxLayout;
    penStyleLay->setContentsMargins(0,0,0,0);
    penStyleLay->setSpacing(5);

    penStyleLay->addWidget(lPenStyle);
    penStyleLay->addWidget(penStyles);

    penStyleLay->addStretch(1);
    vProlay->addItem(penStyleLay);

    //路径
    QLabel *lPenPath = new QLabel;
    lPenPath->setText(QStringLiteral("路径宽度:"));
    lPenPath->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    lPenPath->setFixedWidth(100);
    penPathWidth = new QComboBox;
    penPathWidth->setFixedWidth(200);
    penPathWidth->setEditable(false);

    for (int iPathwidth = 0; iPathwidth < 20; iPathwidth = iPathwidth + 1)
        penPathWidth->addItem(QString().setNum(iPathwidth));
    penPathWidth->setCurrentIndex(10);

    QHBoxLayout * penPathWidthLay = new QHBoxLayout;
    penPathWidthLay->setContentsMargins(0,0,0,0);
    penPathWidthLay->setSpacing(5);

    penPathWidthLay->addWidget(lPenPath);
    penPathWidthLay->addWidget(penPathWidth);

    penPathWidthLay->addStretch(1);
    vProlay->addItem(penPathWidthLay);

    //路径颜色
    QLabel *lPathColor = new QLabel;
    lPathColor->setText(QStringLiteral("路径颜色:"));
    lPathColor->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    lPathColor->setFixedWidth(100);

    fPathColor = new QColorFrame;
    fPathColor->setGifColor(Qt::yellow);
    proInf->pathInfmation.pathColor = Qt::yellow;

    QHBoxLayout * PathColorLay = new QHBoxLayout;
    PathColorLay->setContentsMargins(0,0,0,0);
    PathColorLay->setSpacing(5);

    PathColorLay->addWidget(lPathColor);
    PathColorLay->addWidget(fPathColor);

    PathColorLay->addStretch(1);
    vProlay->addItem(PathColorLay);

    //路径轮廓
    QLabel *lPathcontour = new QLabel;
    lPathcontour->setText(QStringLiteral("轮廓宽度:"));
    lPathcontour->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    lPathcontour->setFixedWidth(100);
    penPathcontourWidth = new QComboBox;
    penPathcontourWidth->setFixedWidth(200);
    penPathcontourWidth->setEditable(false);

    for (int iPathwidth = 0; iPathwidth < 20; iPathwidth = iPathwidth + 1)
        penPathcontourWidth->addItem(QString().setNum(iPathwidth));
    penPathcontourWidth->setCurrentIndex(10);

    QHBoxLayout * penPathcontourWidthLay = new QHBoxLayout;
    penPathcontourWidthLay->setContentsMargins(0,0,0,0);
    penPathcontourWidthLay->setSpacing(5);

    penPathcontourWidthLay->addWidget(lPathcontour);
    penPathcontourWidthLay->addWidget(penPathcontourWidth);

    penPathcontourWidthLay->addStretch(1);
    vProlay->addItem(penPathcontourWidthLay);

    //路径轮廓颜色
    QLabel *lPathcontourColor = new QLabel;
    lPathcontourColor->setText(QStringLiteral("轮廓颜色:"));
    lPathcontourColor->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    lPathcontourColor->setFixedWidth(100);

    fPathcontourColor = new QColorFrame;
    fPathcontourColor->setGifColor(QColor(0, 160, 230));
    proInf->pathInfmation.pathContourcolor = QColor(0, 160, 230);

    QHBoxLayout * PathcontourColorLay = new QHBoxLayout;
    PathcontourColorLay->setContentsMargins(0,0,0,0);
    PathcontourColorLay->setSpacing(5);

    PathcontourColorLay->addWidget(lPathcontourColor);
    PathcontourColorLay->addWidget(fPathcontourColor);

    PathcontourColorLay->addStretch(1);
    vProlay->addItem(PathcontourColorLay);

    //图元
    QLabel *lGraphicItem = new QLabel;
    lGraphicItem->setText(QStringLiteral("图元"));
    lGraphicItem->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    lGraphicItem->setFixedWidth(150);

    vProlay->addWidget(lGraphicItem);
    QFrame *fLineGI = new QFrame;
    fLineGI->setStyleSheet("border:1px solid rgba(10,10,10, 30);");
    fLineGI->setFixedHeight(1);
    vProlay->addWidget(fLineGI);

    //虚线
    QLabel *lItemPenStyle = new QLabel;
    lItemPenStyle->setText(QStringLiteral("虚线:"));
    lItemPenStyle->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    lItemPenStyle->setFixedWidth(100);
    penItemStyles = new QComboBox;
    penItemStyles->setFixedWidth(200);
    penItemStyles->setEditable(false);

    penItemStyles->addItem(QStringLiteral("NoPen"), (int)Qt::NoPen);
    penItemStyles->addItem(QStringLiteral("SolidLine"), (int)Qt::SolidLine);
    penItemStyles->addItem(QStringLiteral("DashLine"), (int)Qt::DashLine);
    penItemStyles->addItem(QStringLiteral("DotLine"), (int)Qt::DotLine);
    penItemStyles->addItem(QStringLiteral("DashDotLine"), (int)Qt::DashDotLine);
    penItemStyles->addItem(QStringLiteral("DashDotDotLine"), (int)Qt::DashDotDotLine);
    penItemStyles->addItem(QStringLiteral("CustomDashLine"), (int)Qt::CustomDashLine);
    penItemStyles->setCurrentIndex(1);

    QHBoxLayout * penItemStyleLay = new QHBoxLayout;
    penItemStyleLay->setContentsMargins(0,0,0,0);
    penItemStyleLay->setSpacing(5);

    penItemStyleLay->addWidget(lItemPenStyle);
    penItemStyleLay->addWidget(penItemStyles);

    penItemStyleLay->addStretch(1);
    vProlay->addItem(penItemStyleLay);

    //边框
    QLabel *lItemPenWidth = new QLabel;
    lItemPenWidth->setText(QStringLiteral("边框宽度:"));
    lItemPenWidth->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    lItemPenWidth->setFixedWidth(100);
    penItemWidth = new QComboBox;
    penItemWidth->setFixedWidth(200);
    penItemWidth->setEditable(false);

    for (int iItemwidth = 0; iItemwidth < 20; iItemwidth = iItemwidth + 1)
        penItemWidth->addItem(QString().setNum(iItemwidth));
    penItemWidth->setCurrentIndex(2);
    proInf->itemInfmation.penBoardWidth = 2;

    QHBoxLayout * itemPenWidthLay = new QHBoxLayout;
    itemPenWidthLay->setContentsMargins(0,0,0,0);
    itemPenWidthLay->setSpacing(5);

    itemPenWidthLay->addWidget(lItemPenWidth);
    itemPenWidthLay->addWidget(penItemWidth);

    itemPenWidthLay->addStretch(1);
    vProlay->addItem(itemPenWidthLay);

    //边框颜色
    QLabel *lItemBorderColor = new QLabel;
    lItemBorderColor->setText(QStringLiteral("边框颜色:"));
    lItemBorderColor->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    lItemBorderColor->setFixedWidth(100);

    fItemBoardColor = new QColorFrame;
    fItemBoardColor->setGifColor(QColor(Qt::blue));
    proInf->itemInfmation.itemBoardcolor = QColor(Qt::blue);

    QHBoxLayout * itemBoardColorLay = new QHBoxLayout;
    itemBoardColorLay->setContentsMargins(0,0,0,0);
    itemBoardColorLay->setSpacing(5);

    itemBoardColorLay->addWidget(lItemBorderColor);
    itemBoardColorLay->addWidget(fItemBoardColor);

    itemBoardColorLay->addStretch(1);
    vProlay->addItem(itemBoardColorLay);

    //图元颜色
    QLabel *lItemColor = new QLabel;
    lItemColor->setText(QStringLiteral("图元颜色:"));
    lItemColor->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    lItemColor->setFixedWidth(100);

    fItemColor = new QColorFrame;
    fItemColor->setGifColor(QColor(0, 160, 230));
    proInf->itemInfmation.itemColor = QColor(0, 160, 230);

    QHBoxLayout * itemColorLay = new QHBoxLayout;
    itemColorLay->setContentsMargins(0,0,0,0);
    itemColorLay->setSpacing(5);

    itemColorLay->addWidget(lItemColor);
    itemColorLay->addWidget(fItemColor);

    itemColorLay->addStretch(1);
    vProlay->addItem(itemColorLay);

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
    if(ckBold)
    {
        nfont.setWeight(ckBold->isChecked() ? QFont::Bold : QFont::Normal);
    }

    if(ckItalic)
    {
        nfont.setItalic(ckItalic->isChecked());
    }

    if(ckUnderLine)
    {
        nfont.setUnderline(ckUnderLine->isChecked());
    }

    if(textAction)
    {
        proInf->textColor = qvariant_cast<QColor>(textAction->data());
    }

    proInf->font =  nfont;

    emit s_whiteBoardProFresh();
}
