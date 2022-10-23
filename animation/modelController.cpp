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

    qRegisterMetaType<ModelView::SessionItem>("SessionItem");
    qRegisterMetaType<std::vector<ModelView::TagRow>>("TagRow");

    connect(this, &ModelController::s_insertItem, this, &ModelController::slot_insertItem);
    connect(this, &ModelController::s_removeItem, this, &ModelController::slot_removeItem);
    connect(this, &ModelController::s_aboutremoveItem, this, &ModelController::slot_aboutremoveItem);


    setOnItemInserted([this](ModelView::SessionItem * parentItem, TagRow tagrow) {

        ModelView::SessionItem * item = parentItem->getItem(tagrow.tag, tagrow.row);
        emit s_insertItem(item, tagrow);
    });

    auto on_Item_about_remove = [this](ModelView::SessionItem* parentItem, const TagRow& tagrow) {

        ModelView::SessionItem * item = parentItem->getItem(tagrow.tag, tagrow.row);
        emit s_aboutremoveItem(item, tagrow);
        //m_view->aboutEraseItem(item, tagrow);
    };
    setOnAboutToRemoveItem(on_Item_about_remove);

    auto on_Item_remove = [this](ModelView::SessionItem* parentItem, const TagRow& tagrow) {

        emit s_removeItem(parentItem, tagrow);
        //m_view->eraseItem(parentItem, tagrow);
    };
    setOnItemRemoved(on_Item_remove);


}

void ModelController::slot_insertItem(ModelView::SessionItem * item, ModelView::TagRow tagrow)
{
    m_view->insertItem(item, tagrow);
}

void ModelController::slot_aboutremoveItem(ModelView::SessionItem * item, ModelView::TagRow tagrow)
{
    m_view->aboutEraseItem(item, tagrow);
}

void ModelController::slot_removeItem(ModelView::SessionItem * item, ModelView::TagRow tagrow)
{
    m_view->eraseItem(item, tagrow);
}
