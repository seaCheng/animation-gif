﻿#include "WhiteBoardPropertyView.h"
#include "commonPropertyView.h"

#include "utils.h"
#include "dpi.h"

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
#include <QRadioButton>
#include <QTextEdit>

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
        emit s_whiteBoardProFresh(pro_pen);
    });

    connect(joinStyles, &QComboBox::currentIndexChanged,
            this, [&](int index){
        proInf->pathInfmation.joinStyle = (Qt::PenJoinStyle)joinStyles->currentData().toInt();
        emit s_whiteBoardProFresh(pro_pen);
    });

    connect(penStyles, &QComboBox::currentIndexChanged,
            this, [&](int index){
        proInf->pathInfmation.penStyle = (Qt::PenStyle)penStyles->currentData().toInt();
        emit s_whiteBoardProFresh(pro_pen);
    });

    connect(penPathWidth, &QComboBox::currentIndexChanged,
            this, [&](int index){
        proInf->pathInfmation.penPathWidth = penPathWidth->currentText().toInt();
        emit s_whiteBoardProFresh(pro_pen);
    });

    connect(penPathcontourWidth, &QComboBox::currentIndexChanged,
            this, [&](int index){
        proInf->pathInfmation.penPathcontourWidth = penPathcontourWidth->currentText().toInt();
        emit s_whiteBoardProFresh(pro_pen);
    });

    connect(fontComboHandWrite, &QFontComboBox::currentFontChanged,
            this, [=](){
            handleFontChangeHandWrite();
    });

    connect(fontSizeComboHandWrite, &QComboBox::currentTextChanged,
            this, [=](){
            handleFontChangeHandWrite();
    });

    /*
    connect(handWriteTextEdit, &QTextEdit::textChanged,
            this, [&](){
        proInf->pathInfmation.text = handWriteTextEdit->toPlainText();
        emit s_whiteBoardProFresh(pro_pen);
    });


    connect(handWritRad, &QRadioButton::toggled,
            this, [&](bool checked){
        proInf->pathInfmation.bHandWriting = checked;
        emit s_whiteBoardProFresh(pro_pen);

        lFontHandWrite->setEnabled(false);
        lFontSizeHandWrite->setEnabled(false);
        ltextHandWrite->setEnabled(false);
        fontComboHandWrite->setEnabled(false);
        fontSizeComboHandWrite->setEnabled(false);
        handWriteTextEdit->setEnabled(false);
    });

    connect(textRad, &QRadioButton::toggled,
            this, [&](bool checked){
        proInf->pathInfmation.bHandWriting = !checked;
        emit s_whiteBoardProFresh(pro_pen);

        lFontHandWrite->setEnabled(true);
        lFontSizeHandWrite->setEnabled(true);
        ltextHandWrite->setEnabled(true);
        fontComboHandWrite->setEnabled(true);
        fontSizeComboHandWrite->setEnabled(true);
        handWriteTextEdit->setEnabled(true);

        update();
    });
    */

    connect(withShadowRad, &QRadioButton::toggled,
            this, [&](bool checked){
        proInf->pathInfmation.bShadow = checked;
        emit s_whiteBoardProFresh(pro_pen);
    });

    connect(withoutShadowRad, &QRadioButton::toggled,
            this, [&](bool checked){
        proInf->pathInfmation.bShadow = !checked;
        emit s_whiteBoardProFresh(pro_pen);
    });

    connect(penItemWidth, &QComboBox::currentIndexChanged,
            this, [&](int index){
        proInf->itemInfmation.penBoardWidth = penItemWidth->currentText().toInt();
        emit s_whiteBoardProFresh(pro_item);
    });

    connect(penItemStyles, &QComboBox::currentIndexChanged,
            this, [&](int index){
        proInf->itemInfmation.penStyle = (Qt::PenStyle)penItemStyles->currentData().toInt();
        emit s_whiteBoardProFresh(pro_item);
    });

    connect(penArrowWidth, &QComboBox::currentIndexChanged,
            this, [&](int index){
        proInf->arrowInformation.penWidth = penArrowWidth->currentText().toInt();
        emit s_whiteBoardProFresh(pro_arrow);
    });

    connect(fArrowColor, &QColorFrame::s_clicked,
            this, [&](){
        colorType = color_arrow;
        colorDialog->setCurrentColor(proInf->arrowInformation.arrowColor);
        colorDialog->exec();
    });

    connect(colorDialog, &QColorDialog::currentColorChanged, this, [&](const QColor &color){

        if (color.isValid())
        {
            switch (colorType) {
            case color_path:
            {
                fPathColor->setGifColor(color);
                proInf->pathInfmation.pathColor = color;
                emit s_whiteBoardProFresh(pro_pen);
                break;
            }
            case color_pathContour:
            {
                fPathcontourColor->setGifColor(color);
                proInf->pathInfmation.pathContourcolor = color;
                emit s_whiteBoardProFresh(pro_pen);
                break;
            }
            case color_item:
            {
                fItemColor->setGifColor(color);
                proInf->itemInfmation.itemColor = color;
                emit s_whiteBoardProFresh(pro_item);
                break;
            }
            case color_itemBoard:
            {
                fItemBoardColor->setGifColor(color);
                proInf->itemInfmation.itemBoardcolor = color;
                emit s_whiteBoardProFresh(pro_item);
                break;
            }
            case color_arrow:
            {
                QColor tcolor = color;
                tcolor.setAlpha(255);
                fArrowColor->setGifColor(tcolor);
                proInf->arrowInformation.arrowColor = tcolor;
                emit s_whiteBoardProFresh(pro_arrow);
                break;
            }
            default:
                break;
            }
        }

    });

    connect(saveCurrentToolButton, &QToolButton::clicked,
            this, [&](){
        emit s_saveToCurrentPicture();
    });

    connect(saveAllToolButton, &QToolButton::clicked,
            this, [&](){
        emit s_saveToAllPictures();
    });

    connect(clearToolButton, &QToolButton::clicked,
            this, [&](){
        emit s_clearGraphicsItems();
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
    vlay->setContentsMargins(DPI::getScaleUI(10),DPI::getScaleUI(5),DPI::getScaleUI(10),DPI::getScaleUI(5));
    vlay->setSpacing(DPI::getScaleUI(10));
    vlay->addWidget(groupBoxItems);
    setObjectName("WhiteBoardPropertyView");
    buttonGroup = new QButtonGroup;
    buttonGroup->setExclusive(false);

    QGridLayout *layout = new QGridLayout;
    //第一个参数为按钮文本，第二参数为样式标记
    layout->addWidget(createCellWidget(tr("Text"),"Text", DiagramType::Diagram_Text), 0, 0);
    layout->addWidget(createCellWidget(tr("ColorText"),"ColorText", DiagramType::Diagram_ColorText), 0, 1);
    layout->addWidget(createCellWidget(tr("pen"),"pen", DiagramType::Diagram_Pen), 0, 2);
    layout->addWidget(createCellWidget(tr("Process"), "Process",DiagramType::Diagram_Step),0, 3);
    layout->addWidget(createCellWidget(tr("Input"),"Input", DiagramType::Diagram_Io), 1, 0);
    layout->addWidget(createCellWidget(tr("oval"), "oval",DiagramType::Diagram_Oval), 1, 1);
    layout->addWidget(createCellWidget(tr("triangle"),"triangle", DiagramType::Diagram_Triangle), 1, 2);

    layout->addWidget(createCellWidget(tr("Conditional"),"Conditional", DiagramType::Diagram_Conditional), 1, 3);
    layout->addWidget(createCellWidget(tr("Line"), "Line",DiagramType::Diagram_StartEnd), 2, 0);
    layout->addWidget(createCellWidget(tr("Picture"), "Picture",DiagramType::Diagram_Pic), 2, 1);
    layout->addWidget(createCellWidget(tr("Select"),"Select", DiagramType::Diagram_Sel), 2, 2);
    layout->addWidget(createCellWidget(tr("Delete"),"Delete", DiagramType::Diagram_Del), 2, 3);

    layout->setRowStretch(3, DPI::getScaleUI(10));
    layout->setColumnStretch(4, DPI::getScaleUI(10));

    groupBoxItems->setLayout(layout);

    QGroupBox *groupBoxProperty= new QGroupBox(tr("Propertys"));
    QVBoxLayout * vProlay = new QVBoxLayout(this);
    vProlay->setContentsMargins(DPI::getScaleUI(10),DPI::getScaleUI(5),DPI::getScaleUI(10),DPI::getScaleUI(5));

    QLabel *lText = new QLabel;
    lText->setText(tr("Text"));
    lText->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    lText->setFixedWidth(DPI::getScaleUI(150));

    vProlay->addWidget(lText);
    QFrame *fLineT = new QFrame;
    fLineT->setStyleSheet("border:1px solid rgba(10,10,10, 30);");
    fLineT->setFixedHeight(1);
    vProlay->addWidget(fLineT);

    QLabel *lFont = new QLabel;
    lFont->setText(tr("Font:"));
    lFont->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    lFont->setFixedWidth(DPI::getScaleUI(100));

    fontCombo = new QFontComboBox();
    fontCombo->setFixedWidth(DPI::getScaleUI(200));
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
    lFontSize->setText(tr("Font size:"));
    lFontSize->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    lFontSize->setFixedWidth(DPI::getScaleUI(100));
    fontSizeCombo = new QComboBox;
    fontSizeCombo->setFixedWidth(DPI::getScaleUI(200));
    fontSizeCombo->setEditable(false);
    for (int i = 8; i < 100; i = i + 2)
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
    lFontColor->setText(tr("Color:"));
    lFontColor->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    lFontColor->setFixedWidth(DPI::getScaleUI(100));

    fontColorToolButton = new QToolButton;
    fontColorToolButton->setFixedSize(DPI::getScaleUI(60),DPI::getScaleUI(30));
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
    lFontStyle->setText(tr("Style:"));
    lFontStyle->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    lFontStyle->setFixedWidth(DPI::getScaleUI(100));

    ckBold = new QCheckBox;
    ckBold->setText(tr("Bold"));

    ckItalic = new QCheckBox;
    ckItalic->setText(tr("Italic"));

    ckUnderLine = new QCheckBox;
    ckUnderLine->setText(tr("UnderLine"));

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
    lColoredPen->setText(tr("ColorText & HandWring"));
    lColoredPen->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    lColoredPen->setFixedWidth(DPI::getScaleUI(200));

    vProlay->addWidget(lColoredPen);
    QFrame *fLineCP = new QFrame;
    fLineCP->setStyleSheet("border:1px solid rgba(10,10,10, 30);");
    fLineCP->setFixedHeight(1);
    vProlay->addWidget(fLineCP);

    QLabel *lCapStyle = new QLabel;
    lCapStyle->setText(tr("Pen cap:"));
    lCapStyle->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    lCapStyle->setFixedWidth(DPI::getScaleUI(100));
    capStyles = new QComboBox;
    capStyles->setFixedWidth(DPI::getScaleUI(200));
    capStyles->setEditable(false);

    capStyles->addItem(tr("FlatCap"), (int)Qt::FlatCap);
    capStyles->addItem(tr("SquareCap"), (int)Qt::SquareCap);
    capStyles->addItem(tr("RoundCap"), (int)Qt::RoundCap);
    capStyles->setCurrentIndex(2);

    QHBoxLayout * capStyleLay = new QHBoxLayout;
    capStyleLay->setContentsMargins(0,0,0,0);
    capStyleLay->setSpacing(5);

    capStyleLay->addWidget(lCapStyle);
    capStyleLay->addWidget(capStyles);

    capStyleLay->addStretch(1);
    vProlay->addItem(capStyleLay);

    QLabel *lJoinStyle = new QLabel;
    lJoinStyle->setText(tr("Link:"));
    lJoinStyle->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    lJoinStyle->setFixedWidth(DPI::getScaleUI(100));
    joinStyles = new QComboBox;
    joinStyles->setFixedWidth(DPI::getScaleUI(200));
    joinStyles->setEditable(false);

    joinStyles->addItem(tr("MiterJoin"), (int)Qt::MiterJoin);
    joinStyles->addItem(tr("BevelJoin"), (int)Qt::BevelJoin);
    joinStyles->addItem(tr("RoundJoin"), (int)Qt::RoundJoin);
    joinStyles->addItem(tr("SvgMiterJoin"), (int)Qt::SvgMiterJoin);
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
    lPenStyle->setText(tr("Dotted line:"));
    lPenStyle->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    lPenStyle->setFixedWidth(DPI::getScaleUI(100));
    penStyles = new QComboBox;
    penStyles->setFixedWidth(DPI::getScaleUI(200));
    penStyles->setEditable(false);

    penStyles->addItem(tr("NoPen"), (int)Qt::NoPen);
    penStyles->addItem(tr("SolidLine"), (int)Qt::SolidLine);
    penStyles->addItem(tr("DashLine"), (int)Qt::DashLine);
    penStyles->addItem(tr("DotLine"), (int)Qt::DotLine);
    penStyles->addItem(tr("DashDotLine"), (int)Qt::DashDotLine);
    penStyles->addItem(tr("DashDotDotLine"), (int)Qt::DashDotDotLine);
    penStyles->addItem(tr("CustomDashLine"), (int)Qt::CustomDashLine);
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
    lPenPath->setText(tr("Path width:"));
    lPenPath->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    lPenPath->setFixedWidth(DPI::getScaleUI(100));
    penPathWidth = new QComboBox;
    penPathWidth->setFixedWidth(DPI::getScaleUI(200));
    penPathWidth->setEditable(false);

    for (int iPathwidth = 0; iPathwidth < 20; iPathwidth = iPathwidth + 1)
        penPathWidth->addItem(QString().setNum(iPathwidth));
    penPathWidth->setCurrentIndex(2);
    proInf->pathInfmation.penPathWidth = 2;

    QHBoxLayout * penPathWidthLay = new QHBoxLayout;
    penPathWidthLay->setContentsMargins(0,0,0,0);
    penPathWidthLay->setSpacing(5);

    penPathWidthLay->addWidget(lPenPath);
    penPathWidthLay->addWidget(penPathWidth);

    penPathWidthLay->addStretch(1);
    vProlay->addItem(penPathWidthLay);

    //路径颜色
    QLabel *lPathColor = new QLabel;
    lPathColor->setText(tr("Path color:"));
    lPathColor->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    lPathColor->setFixedWidth(DPI::getScaleUI(100));

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
    lPathcontour->setText(tr("Contour width:"));
    lPathcontour->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    lPathcontour->setFixedWidth(DPI::getScaleUI(100));
    penPathcontourWidth = new QComboBox;
    penPathcontourWidth->setFixedWidth(DPI::getScaleUI(200));
    penPathcontourWidth->setEditable(false);

    for (int iPathwidth = 0; iPathwidth < 20; iPathwidth = iPathwidth + 1)
        penPathcontourWidth->addItem(QString().setNum(iPathwidth));
    penPathcontourWidth->setCurrentIndex(4);
    proInf->pathInfmation.penPathcontourWidth = 4;

    QHBoxLayout * penPathcontourWidthLay = new QHBoxLayout;
    penPathcontourWidthLay->setContentsMargins(0,0,0,0);
    penPathcontourWidthLay->setSpacing(5);

    penPathcontourWidthLay->addWidget(lPathcontour);
    penPathcontourWidthLay->addWidget(penPathcontourWidth);

    penPathcontourWidthLay->addStretch(1);
    vProlay->addItem(penPathcontourWidthLay);

    //路径轮廓颜色
    QLabel *lPathcontourColor = new QLabel;
    lPathcontourColor->setText(tr("Contour color:"));
    lPathcontourColor->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    lPathcontourColor->setFixedWidth(DPI::getScaleUI(100));

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

    //阴影
    QLabel *lShadow = new QLabel;
    lShadow->setText(tr("Shadow:"));
    lShadow->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    lShadow->setFixedWidth(DPI::getScaleUI(100));

    shadowGrp = new QButtonGroup(this);
    shadowGrp->setExclusive(true);
    withoutShadowRad = new QRadioButton;
    withoutShadowRad->setChecked(true);
    proInf->pathInfmation.bShadow = false;

    withoutShadowRad->setText(tr("None"));
    shadowGrp->addButton(withoutShadowRad);

    withShadowRad = new QRadioButton;
    withShadowRad->setText(tr("Yes"));
    shadowGrp->addButton(withShadowRad);

    QHBoxLayout * hShadowRadLay = new QHBoxLayout;
    hShadowRadLay->setContentsMargins(0,0,0,0);
    hShadowRadLay->setSpacing(DPI::getScaleUI(24));
    hShadowRadLay->addWidget(lShadow);
    hShadowRadLay->addWidget(withoutShadowRad);
    hShadowRadLay->addWidget(withShadowRad);

    hShadowRadLay->addStretch(1);
    vProlay->addItem(hShadowRadLay);

    //手写，或编辑
    /*
    QLabel *lScreen = new QLabel;
    lScreen->setText(tr("Text editing:"));
    lScreen->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    lScreen->setFixedWidth(DPI::getScaleUI(100));

    handWritingGrp = new QButtonGroup(this);
    handWritingGrp->setExclusive(true);
    handWritRad = new QRadioButton;
    handWritRad->setChecked(true);
    proInf->pathInfmation.bHandWriting = true;

    handWritRad->setText(tr("Hand write"));
    handWritingGrp->addButton(handWritRad);

    textRad = new QRadioButton;
    textRad->setText(tr("Edit"));
    handWritingGrp->addButton(textRad);

    QHBoxLayout * hRadLay = new QHBoxLayout;
    hRadLay->setContentsMargins(0,0,0,0);
    hRadLay->setSpacing(24);
    hRadLay->addWidget(lScreen);
    hRadLay->addWidget(handWritRad);
    hRadLay->addWidget(textRad);

    hRadLay->addStretch(1);
    vProlay->addItem(hRadLay);
    */

    lFontHandWrite = new QLabel;
    lFontHandWrite->setText(tr("Font:"));
    lFontHandWrite->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    lFontHandWrite->setFixedWidth(DPI::getScaleUI(100));

    fontComboHandWrite = new QFontComboBox();
    fontComboHandWrite->setFixedWidth(DPI::getScaleUI(200));
    fontComboHandWrite->setEditable(false);
    fontComboHandWrite->setCurrentIndex(10);

    QHBoxLayout * FontLayHandWrite = new QHBoxLayout;
    FontLayHandWrite->setContentsMargins(0,0,0,0);
    FontLayHandWrite->setSpacing(5);

    FontLayHandWrite->addWidget(lFontHandWrite);
    FontLayHandWrite->addWidget(fontComboHandWrite);
    FontLayHandWrite->addStretch(1);
    vProlay->addItem(FontLayHandWrite);

    lFontSizeHandWrite = new QLabel;
    lFontSizeHandWrite->setText(tr("Font size:"));
    lFontSizeHandWrite->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    lFontSizeHandWrite->setFixedWidth(DPI::getScaleUI(100));
    fontSizeComboHandWrite = new QComboBox;
    fontSizeComboHandWrite->setFixedWidth(DPI::getScaleUI(200));
    fontSizeComboHandWrite->setEditable(false);
    for (int i = 8; i < 100; i = i + 2)
        fontSizeComboHandWrite->addItem(QString().setNum(i));
    QIntValidator *validatorHandWrite = new QIntValidator(2, 64, this);
    fontSizeComboHandWrite->setValidator(validatorHandWrite);

    fontSizeComboHandWrite->setCurrentIndex(5);
    QHBoxLayout * FontSizeLayHandWrite = new QHBoxLayout;
    FontSizeLayHandWrite->setContentsMargins(0,0,0,0);
    FontSizeLayHandWrite->setSpacing(5);

    FontSizeLayHandWrite->addWidget(lFontSizeHandWrite);
    FontSizeLayHandWrite->addWidget(fontSizeComboHandWrite);
    FontSizeLayHandWrite->addStretch(1);
    vProlay->addItem(FontSizeLayHandWrite);

    /*
    ltextHandWrite = new QLabel;
    ltextHandWrite->setText(tr("Text:"));
    ltextHandWrite->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    ltextHandWrite->setFixedWidth(DPI::getScaleUI(100));
    handWriteTextEdit = new QTextEdit;
    handWriteTextEdit->setFixedWidth(DPI::getScaleUI(200));
    handWriteTextEdit->setFixedHeight(DPI::getScaleUI(60));
    handWriteTextEdit->setText("Edit text via text edit box");
    proInf->pathInfmation.text = "Edit text via text edit box";


    QHBoxLayout * textEditHandWriteLay = new QHBoxLayout;
    textEditHandWriteLay->setContentsMargins(0,0,0,0);
    textEditHandWriteLay->setSpacing(5);

    textEditHandWriteLay->addWidget(ltextHandWrite);
    textEditHandWriteLay->addWidget(handWriteTextEdit);
    textEditHandWriteLay->addStretch(1);
    vProlay->addItem(textEditHandWriteLay);
    */

    //lFontHandWrite->setEnabled(false);
    //lFontSizeHandWrite->setEnabled(false);
    //ltextHandWrite->setEnabled(false);
    //fontComboHandWrite->setEnabled(false);
    //fontSizeComboHandWrite->setEnabled(false);
    //handWriteTextEdit->setEnabled(false);

    //图元
    QLabel *lGraphicItem = new QLabel;
    lGraphicItem->setText(tr("Graph element"));
    lGraphicItem->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    lGraphicItem->setFixedWidth(DPI::getScaleUI(150));

    vProlay->addWidget(lGraphicItem);
    QFrame *fLineGI = new QFrame;
    fLineGI->setStyleSheet("border:1px solid rgba(10,10,10, 30);");
    fLineGI->setFixedHeight(1);
    vProlay->addWidget(fLineGI);

    //虚线
    QLabel *lItemPenStyle = new QLabel;
    lItemPenStyle->setText(tr("Dotted line:"));
    lItemPenStyle->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    lItemPenStyle->setFixedWidth(DPI::getScaleUI(100));
    penItemStyles = new QComboBox;
    penItemStyles->setFixedWidth(DPI::getScaleUI(200));
    penItemStyles->setEditable(false);

    penItemStyles->addItem(tr("NoPen"), (int)Qt::NoPen);
    penItemStyles->addItem(tr("SolidLine"), (int)Qt::SolidLine);
    penItemStyles->addItem(tr("DashLine"), (int)Qt::DashLine);
    penItemStyles->addItem(tr("DotLine"), (int)Qt::DotLine);
    penItemStyles->addItem(tr("DashDotLine"), (int)Qt::DashDotLine);
    penItemStyles->addItem(tr("DashDotDotLine"), (int)Qt::DashDotDotLine);
    penItemStyles->addItem(tr("CustomDashLine"), (int)Qt::CustomDashLine);
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
    lItemPenWidth->setText(tr("Border width:"));
    lItemPenWidth->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    lItemPenWidth->setFixedWidth(DPI::getScaleUI(100));
    penItemWidth = new QComboBox;
    penItemWidth->setFixedWidth(DPI::getScaleUI(200));
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
    lItemBorderColor->setText(tr("Border color:"));
    lItemBorderColor->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    lItemBorderColor->setFixedWidth(DPI::getScaleUI(100));

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
    lItemColor->setText(tr("Element color:"));
    lItemColor->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    lItemColor->setFixedWidth(DPI::getScaleUI(100));

    fItemColor = new QColorFrame;
    fItemColor->setGifColor(QColor(0, 160, 230, 125));
    proInf->itemInfmation.itemColor = QColor(0, 160, 230, 125);

    QHBoxLayout * itemColorLay = new QHBoxLayout;
    itemColorLay->setContentsMargins(0,0,0,0);
    itemColorLay->setSpacing(5);

    itemColorLay->addWidget(lItemColor);
    itemColorLay->addWidget(fItemColor);

    itemColorLay->addStretch(1);
    vProlay->addItem(itemColorLay);

    //箭头
    QLabel *lArrow = new QLabel;
    lArrow->setText(tr("Arrow"));
    lArrow->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    lArrow->setFixedWidth(DPI::getScaleUI(150));

    vProlay->addWidget(lArrow);
    QFrame *fLineArrow = new QFrame;
    fLineArrow->setStyleSheet("border:1px solid rgba(10,10,10, 30);");
    fLineArrow->setFixedHeight(1);
    vProlay->addWidget(fLineArrow);

    //宽度
    QLabel *lArrowPenWidth = new QLabel;
    lArrowPenWidth->setText(tr("Width:"));
    lArrowPenWidth->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    lArrowPenWidth->setFixedWidth(DPI::getScaleUI(100));
    penArrowWidth = new QComboBox;
    penArrowWidth->setFixedWidth(DPI::getScaleUI(200));
    penArrowWidth->setEditable(false);

    for (int iItemwidth = 0; iItemwidth < 20; iItemwidth = iItemwidth + 1)
        penArrowWidth->addItem(QString().setNum(iItemwidth));
    penArrowWidth->setCurrentIndex(2);
    proInf->arrowInformation.penWidth = 2;

    QHBoxLayout * arrowPenWidthLay = new QHBoxLayout;
    arrowPenWidthLay->setContentsMargins(0,0,0,0);
    arrowPenWidthLay->setSpacing(5);

    arrowPenWidthLay->addWidget(lArrowPenWidth);
    arrowPenWidthLay->addWidget(penArrowWidth);

    arrowPenWidthLay->addStretch(1);
    vProlay->addItem(arrowPenWidthLay);

    //颜色
    QLabel *lArrowColor = new QLabel;
    lArrowColor->setText(tr("Color:"));
    lArrowColor->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    lArrowColor->setFixedWidth(DPI::getScaleUI(100));

    fArrowColor = new QColorFrame;
    fArrowColor->setGifColor(QColor(Qt::blue));
    proInf->arrowInformation.arrowColor = QColor(Qt::blue);

    QHBoxLayout * arrowColorLay = new QHBoxLayout;
    arrowColorLay->setContentsMargins(0,0,0,0);
    arrowColorLay->setSpacing(DPI::getScaleUI(5));

    arrowColorLay->addWidget(lArrowColor);
    arrowColorLay->addWidget(fArrowColor);

    arrowColorLay->addStretch(1);
    vProlay->addItem(arrowColorLay);

    groupBoxProperty->setLayout(vProlay);
    vlay->addWidget(groupBoxProperty);

    QGroupBox *groupBoxOperation= new QGroupBox(tr("Operation"));
    QGridLayout * vOprlay = new QGridLayout(this);
    vOprlay->setContentsMargins(DPI::getScaleUI(10),DPI::getScaleUI(5),DPI::getScaleUI(15),DPI::getScaleUI(15));
    vOprlay->setSpacing(DPI::getScaleUI(12));

    groupBoxProperty->setLayout(vProlay);
    vlay->addWidget(groupBoxProperty);

    groupBoxOperation->setLayout(vOprlay);
    vlay->addWidget(groupBoxOperation);

    saveCurrentToolButton = new QToolButton;
    saveCurrentToolButton->setObjectName("saveCurrentToolButton");
    saveCurrentToolButton->setFixedSize(Utils::getInstance()->autoW(260),Utils::getInstance()->autoH(30));
    saveCurrentToolButton->setToolButtonStyle(Qt::ToolButtonTextOnly);
    saveCurrentToolButton->setArrowType(Qt::NoArrow);
    saveCurrentToolButton->setText(tr("save to current picture"));
    vOprlay->addWidget(saveCurrentToolButton, 0,0);

    saveAllToolButton = new QToolButton;
    saveAllToolButton->setObjectName("saveAllToolButton");
    saveAllToolButton->setFixedSize(Utils::getInstance()->autoW(260),Utils::getInstance()->autoH(30));
    saveAllToolButton->setToolButtonStyle(Qt::ToolButtonTextOnly);
    saveAllToolButton->setArrowType(Qt::NoArrow);
    saveAllToolButton->setText(tr("save to all pictures"));
    vOprlay->addWidget(saveAllToolButton,1,0);

    clearToolButton = new QToolButton;
    clearToolButton->setObjectName("clearToolButton");
    clearToolButton->setFixedSize(Utils::getInstance()->autoW(260),Utils::getInstance()->autoH(30));
    clearToolButton->setToolButtonStyle(Qt::ToolButtonTextOnly);
    clearToolButton->setArrowType(Qt::NoArrow);
    clearToolButton->setText(tr("clear white board"));
    vOprlay->addWidget(clearToolButton,2,0);

    vProlay->setContentsMargins(DPI::getScaleUI(10),DPI::getScaleUI(5),DPI::getScaleUI(10),DPI::getScaleUI(10));
    vlay->addStretch(1);

    handleFontChange();
    handleFontChangeHandWrite();
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
    QPixmap pixmap(DPI::getScaleUI(20), DPI::getScaleUI(20));
    QPainter painter(&pixmap);
    painter.setPen(Qt::NoPen);
    painter.fillRect(QRect(0, 0, DPI::getScaleUI(20), DPI::getScaleUI(20)), color);

    return QIcon(pixmap);
}

QIcon WhiteBoardPropertyView::createColorToolButtonIcon(const QString &imageFile, QColor color)
{
    QPixmap pixmap(DPI::getScaleUI(50), DPI::getScaleUI(80));
    pixmap.fill(Qt::transparent);
    QPainter painter(&pixmap);
    QPixmap image(imageFile);
    // Draw icon centred horizontally on button.
    QRect target(DPI::getScaleUI(4), 0, DPI::getScaleUI(42), DPI::getScaleUI(43));
    QRect source(0, 0, DPI::getScaleUI(42), DPI::getScaleUI(43));
    painter.fillRect(QRect(0, DPI::getScaleUI(60), DPI::getScaleUI(50), DPI::getScaleUI(80)), color);
    painter.drawPixmap(target, image, source);

    return QIcon(pixmap);
}

QWidget * WhiteBoardPropertyView::createCellWidget(const QString &text,const QString &textObJ, DiagramType type)
{

    QToolButton *button = new QToolButton;
    button->setCheckable(true);
    button->setObjectName(textObJ);
    button->setFixedSize(DPI::getScaleUI(50),DPI::getScaleUI(50));
    button->setIconSize(QSize(DPI::getScaleUI(45),DPI::getScaleUI(45)));
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
    emit s_whiteBoardProFresh(pro_text);
}

void WhiteBoardPropertyView::handleFontChangeHandWrite()
{
    QFont nfont = fontComboHandWrite->currentFont();
    nfont.setPointSize(fontSizeComboHandWrite->currentText().toInt());
    proInf->pathInfmation.textFont =  nfont;

    emit s_whiteBoardProFresh(pro_pen);
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

    emit s_whiteBoardProFresh(pro_text);
}
