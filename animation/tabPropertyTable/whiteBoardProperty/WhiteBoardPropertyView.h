﻿#pragma once

#include <QFrame>

class QAbstractButton;
class QButtonGroup;

enum DiagramType { Diagram_Text, Diagram_Step, Diagram_Conditional, Diagram_StartEnd, Diagram_Io };
Q_DECLARE_METATYPE(DiagramType)

class WhiteBoardPropertyView :public QFrame
{
    Q_OBJECT
public:
    WhiteBoardPropertyView();
    void setConnect();
    void initial();

    QWidget * createCellWidget(const QString &text, DiagramType type);
signals:
    void s_sceneItemInsert(DiagramType);
protected:


public slots:
    void buttonGroupClicked(QAbstractButton *button);
private:
    QButtonGroup *buttonGroup;
};
