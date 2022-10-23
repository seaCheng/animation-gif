// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef NODEEDITORCORE_GRAPHICSSCENECONTROLLER_H
#define NODEEDITORCORE_GRAPHICSSCENECONTROLLER_H

#include "mvvm/signals/modellistener.h"
#include "mvvm/model/sessionitem.h"
#include <QObject>
class PicScaleViewComp;

class GraphicsScene;
class PictureModel;
class SessionItem;


//! Provides update of graphics scene, when SampleModel changes.

class ModelController : public ModelView::ModelListener<PictureModel>{
    Q_OBJECT
public:
    ModelController(PictureModel* model, PicScaleViewComp* view);
signals:
    void s_insertItem(ModelView::SessionItem * item, ModelView::TagRow tagrow);
    void s_aboutremoveItem(ModelView::SessionItem * item, ModelView::TagRow tagrow);
    void s_removeItem(ModelView::SessionItem * item, ModelView::TagRow tagrow);

private slots:
    void slot_insertItem(ModelView::SessionItem * item, ModelView::TagRow tagrow);
    void slot_aboutremoveItem(ModelView::SessionItem * item, ModelView::TagRow tagrow);
    void slot_removeItem(ModelView::SessionItem * item, ModelView::TagRow tagrow);

private:
    //GraphicsScene* m_scene{nullptr};
    PicScaleViewComp * m_view;
};


#endif // NODEEDITORCORE_GRAPHICSSCENECONTROLLER_H
