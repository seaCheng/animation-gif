// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "modelController.h"
#include "mvvm/model/sessionitem.h"
#include "picScaleViewComp.h"
#include "pictureModel.h"

#include <QDebug>

using namespace ModelView;


ModelController::ModelController(PictureModel* model, PicScaleViewComp* scene)
    : ModelView::ModelListener<PictureModel>(model), m_view(scene)
{
    setOnItemInserted([this](SessionItem * parentItem, TagRow tagrow) {

        SessionItem * item = parentItem->getItem(tagrow.tag, tagrow.row);
        m_view->insertItem(item, tagrow);
    });

    auto on_Item_about_remove = [this](SessionItem* parentItem, const TagRow& tagrow) {

        SessionItem * item = parentItem->getItem(tagrow.tag, tagrow.row);
        m_view->aboutEraseItem(item, tagrow);
    };
    setOnAboutToRemoveItem(on_Item_about_remove);

    auto on_Item_remove = [this](SessionItem* parentItem, const TagRow& tagrow) {

        m_view->eraseItem(parentItem, tagrow);
    };
    setOnItemRemoved(on_Item_remove);

}

