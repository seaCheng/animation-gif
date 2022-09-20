#pragma once

#include <QFrame>

class QAbstractButton;
class QButtonGroup;

enum DiagramType { Diagram_Text, Diagram_Step, Diagram_Conditional,
                   Diagram_StartEnd, Diagram_Io, Diagram_Oval, Diagram_Triangle, Diagram_Pen, Diagram_Pic,Diagram_Sel,Diagram_Del };
Q_DECLARE_METATYPE(DiagramType)


class QFontComboBox;
class QComboBox;
class WhiteBoardPropertyView :public QFrame
{
    Q_OBJECT
public:
    WhiteBoardPropertyView();
    void setConnect();
    void initial();

    QWidget * createCellWidget(const QString &text, DiagramType type);

    void handleFontChange();
signals:
    void s_sceneItemInsert(DiagramType);
protected:


public slots:
    void buttonGroupClicked(QAbstractButton *button);

    void currentFontChanged(const QFont &f);

    void fontSizeChanged(const QString &);
private:
    QButtonGroup *buttonGroup;

    QFontComboBox * fontCombo = nullptr;
    QComboBox * fontSizeCombo = nullptr;
};

