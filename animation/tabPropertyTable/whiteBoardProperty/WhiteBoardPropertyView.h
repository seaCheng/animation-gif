#pragma once

#include <QFrame>

class QAbstractButton;
class QButtonGroup;

enum DiagramType { Diagram_Text, Diagram_Step, Diagram_Conditional,  \
                   Diagram_StartEnd, Diagram_Io, Diagram_Oval, Diagram_Triangle, Diagram_Pen, Diagram_Pic,Diagram_Sel,Diagram_Del };
Q_DECLARE_METATYPE(DiagramType)

struct pathInf
{
    QColor pathColor = QColor(0, 160, 230);
    QColor pathContourcolor = Qt::yellow;
    Qt::PenCapStyle capStyle = Qt::RoundCap;
    Qt::PenJoinStyle joinStyle = Qt::RoundJoin;
    Qt::PenStyle penStyle = Qt::SolidLine;
    int penPathWidth = 10;
    int penPathcontourWidth = 10;
};
Q_DECLARE_METATYPE(pathInf)

struct itemInf
{
    QColor itemColor = QColor(0, 160, 230);
    QColor itemBoardcolor = Qt::blue;
    Qt::PenStyle penStyle = Qt::SolidLine;
    int penBoardWidth = 2;

};
Q_DECLARE_METATYPE(itemInf)

struct arrowInf
{
    QColor arrowColor = QColor(0, 160, 230);
    Qt::PenStyle penStyle = Qt::SolidLine;
    int penWidth = 2;

};
Q_DECLARE_METATYPE(arrowInf)

struct whiteBoardProInf
{
    QFont font;
    QColor textColor;
    pathInf pathInfmation;
    itemInf itemInfmation;
    arrowInf arrowInformation;
};
Q_DECLARE_METATYPE(whiteBoardProInf)

enum colorPenType{color_path,color_pathContour, color_item, color_itemBoard, color_arrow};
Q_DECLARE_METATYPE(colorPenType)

enum refreashProType{pro_none,pro_text,pro_pen, pro_item, pro_arrow};
Q_DECLARE_METATYPE(refreashProType)

class QFontComboBox;
class QComboBox;
class QMenu;
class QToolButton;
class QCheckBox;
class QColorFrame;
class QColorDialog;

class WhiteBoardPropertyView :public QFrame
{
    Q_OBJECT
public:
    WhiteBoardPropertyView(std::shared_ptr<whiteBoardProInf> pro);
    void setConnect();
    void initial();

    QWidget * createCellWidget(const QString &text, DiagramType type);

    QMenu *createColorMenu(const char *slot, QColor defaultColor);
    QIcon createColorIcon(QColor color);
    QIcon createColorToolButtonIcon(const QString &imageFile, QColor color);

    void handleFontChange();

signals:
    void s_sceneItemInsert(DiagramType);
    void s_whiteBoardProFresh(refreashProType);

    void s_saveToCurrentPicture();
    void s_saveToAllPictures();
    void s_clearGraphicsItems();
protected:


public slots:
    void buttonGroupClicked(QAbstractButton *button);

    void currentFontChanged(const QFont &f);

    void fontSizeChanged(const QString &);

    void textButtonTriggered();
    void textColorChanged();
private:
    QButtonGroup *buttonGroup;

    QFontComboBox * fontCombo = nullptr;
    QComboBox * fontSizeCombo = nullptr;

    QToolButton * fontColorToolButton = nullptr;
    QAction *textAction = nullptr;

    QCheckBox * ckBold = nullptr;
    QCheckBox * ckItalic = nullptr;
    QCheckBox * ckUnderLine = nullptr;

    QComboBox * capStyles = nullptr;
    QComboBox * joinStyles = nullptr;
    QComboBox * penStyles = nullptr;

    QComboBox * penPathWidth = nullptr;
    QColorFrame * fPathColor = nullptr;

    QComboBox * penPathcontourWidth = nullptr;
    QColorFrame * fPathcontourColor = nullptr;

    QColorDialog * colorDialog;
    colorPenType colorType = color_path;

    QComboBox * penItemWidth = nullptr;
    QComboBox * penItemStyles = nullptr;
    QColorFrame * fItemBoardColor = nullptr;
    QColorFrame * fItemColor = nullptr;

    QComboBox * penArrowWidth = nullptr;
    QComboBox * penArrowStyles = nullptr;
    QColorFrame * fArrowColor = nullptr;

    QToolButton * saveCurrentToolButton = nullptr;
    QToolButton * saveAllToolButton = nullptr;
    QToolButton * clearToolButton = nullptr;

    std::shared_ptr<whiteBoardProInf> proInf;
};

