// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef NODEEDITORCORE_CONNECTABLEITEM_H
#define NODEEDITORCORE_CONNECTABLEITEM_H

#include "mvvm/model/compounditem.h"

class QColor;


//! Base class for all node editor items.

class ConnectableItem : public ModelView::CompoundItem {
public:
    static inline const std::string P_XPOS = "P_XPOS";
    static inline const std::string P_YPOS = "P_YPOS";
    static inline const std::string P_COLOR = "P_COLOR";

    explicit ConnectableItem(const std::string& modelType);
    explicit ConnectableItem();
    QColor color() const;

    double x() const;
    void setX(double x);

    double y() const;
    void setY(double y);

    void setPos(double x, double y);

    void setNamedColor(const std::string& named_color);

    QPixmap pic();
    void setQpixmap( QPixmap pix);
};


#endif // NODEEDITORCORE_CONNECTABLEITEM_H
