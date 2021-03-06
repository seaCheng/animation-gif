// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "mvvm/standarditems/vectoritem.h"
#include "mvvm/signals/itemmapper.h"
#include <sstream>

using namespace ModelView;

VectorItem::VectorItem() : CompoundItem(Constants::VectorItemType)
{
    addProperty(P_X, 0.0)->setDisplayName("X");
    addProperty(P_Y, 0.0)->setDisplayName("Y");
    addProperty(P_Z, 0.0)->setDisplayName("Z");

    setEditable(false);

    update_label();
}

void VectorItem::activate()
{
    auto on_property_change = [this](SessionItem*, const std::string&) { update_label(); };
    mapper()->setOnPropertyChange(on_property_change, this);
}

double VectorItem::x() const
{
    return property<double>(P_X);
}

void VectorItem::setX(double value)
{
    setProperty(P_X, value);
}

double VectorItem::y() const
{
    return property<double>(P_Y);
}

void VectorItem::setY(double value)
{
    setProperty(P_Y, value);
}

double VectorItem::z() const
{
    return property<double>(P_Z);
}

void VectorItem::setZ(double value)
{
    setProperty(P_Z, value);
}

void VectorItem::update_label()
{
    std::ostringstream ostr;
    ostr << "(1" << x() << ", " << y() << ", " << z() << "1)";
    setData(Variant::fromValue(ostr.str()), ItemDataRole::DATA, /*direct*/ true);
}
