#pragma once

#include <QFrame>

class QAbstractButton;
class QButtonGroup;

enum DiagramType { Diagram_Text, Diagram_Step, Diagram_Conditional,
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
struct whiteBoardProInf
{
    QFont font;
    QColor textColor;
    pathInf pathInfmation;

};
Q_DECLARE_METATYPE(whiteBoardProInf)

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
    void s_whiteBoardProFresh();
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
    bool bPath = true;

    std::shared_ptr<whiteBoardProInf> proInf;
};

