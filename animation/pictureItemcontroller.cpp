// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "pictureItemcontroller.h"
//#include "connectableview.h"
#include "pictureItem.h"
#include "picScaleComp.h"

#include <QDebug>

using namespace ModelView;

struct PictureItemController::PictureItemControllerImpl {
    PictureItem* m_item{nullptr};
    PicScaleComp* m_view{nullptr};
    bool m_blockOnPropertyChanged{false};

    PictureItemControllerImpl(PictureItem* item, PicScaleComp* view)
        : m_item(item), m_view(view)
    {
    }

    //! Updates item properties from the current view position.

    void updateItemFromView()
    {
        m_blockOnPropertyChanged = true;
        //m_item->setPos(m_view->x(), m_view->y());
        m_blockOnPropertyChanged = false;
    }

    //! Updates view position and appearance using current values of item properties.

    void updateViewFromItem()
    {
        //m_view->setX(m_item->x());
        //m_view->setY(m_item->y());

        qDebug()<<"updateViewFromItem x:"<<m_item->x()<<" updateViewFromItem y:"<<m_item->y();
        //m_view->update();

    }

    void updateViewFromItemdata()
    {
        if(m_item->pic().isNull() == true)
        {
            return;
        }

        m_view->setPic(m_item->pic());
        m_view->update();

    }
};

PictureItemController::PictureItemController(PictureItem* item, PicScaleComp* view)
    : p_impl(std::make_unique<PictureItemControllerImpl>(item, view))
{
    setItem(item);

}

//! Updates item properties from the current view position.

void PictureItemController::updateItemFromView()
{
    p_impl->updateItemFromView();
}

void PictureItemController::updateViewFromItem()
{
    p_impl->updateViewFromItem();
}

PictureItemController::~PictureItemController() = default;

void PictureItemController::subscribe()
{
    //qDebug()<<"on_property_change subscribe....";

    auto on_property_change = [this](auto, auto) {

        qDebug()<<"on_property_change...";

        if (p_impl->m_blockOnPropertyChanged)
            return;

        p_impl->updateViewFromItem();
    };
    setOnPropertyChange(on_property_change);

    auto on_data_change = [this](auto, auto) {

        qDebug()<<"on_data_change...";
        p_impl->updateViewFromItemdata();
    };

    setOnDataChange(on_data_change);
    p_impl->updateViewFromItem();
}

