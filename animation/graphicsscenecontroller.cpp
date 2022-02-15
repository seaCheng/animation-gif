// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "graphicsscenecontroller.h"
#include "mvvm/model/sessionitem.h"
#include "picScaleViewComp.h"
#include "samplemodel.h"

#include <QDebug>

using namespace ModelView;


GraphicsSceneController::GraphicsSceneController(SampleModel* model, PicScaleViewComp* scene)
    : ModelView::ModelListener<SampleModel>(model), m_view(scene)
{
    setOnItemInserted([this](SessionItem * item, TagRow row) { m_view->insertItem(item, row); });

    auto on_Item_remove = [this](SessionItem* item, const TagRow& row) {
        m_view->eraseItem(item, row);
    };
    setOnItemRemoved(on_Item_remove);
}

