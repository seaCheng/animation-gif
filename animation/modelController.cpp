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
    setOnItemInserted([this](SessionItem * item, TagRow row) { m_view->insertItem(item, row); });

    auto on_Item_remove = [this](SessionItem* item, const TagRow& row) {
        m_view->eraseItem(item, row);
    };
    setOnItemRemoved(on_Item_remove);
}

