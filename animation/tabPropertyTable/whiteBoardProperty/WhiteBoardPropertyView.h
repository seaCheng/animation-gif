#pragma once

#include <QFrame>

class QAbstractButton;
class QButtonGroup;

enum DiagramType { Diagram_Text, Diagram_Step, Diagram_Conditional,
                   Diagram_StartEnd, Diagram_Io, Diagram_Oval, Diagram_Triangle, Diagram_Pen, Diagram_Pic,Diagram_Sel,Diagram_Del };
Q_DECLARE_METATYPE(DiagramType)

struct whiteBoardProInf
{
    QFont font;
    QColor textColor;
};
Q_DECLARE_METATYPE(whiteBoardProInf)

class QFontComboBox;
class QComboBox;
class QMenu;
class QToolButton;

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
    QAction *textAction;

    std::shared_ptr<whiteBoardProInf> proInf;
};

