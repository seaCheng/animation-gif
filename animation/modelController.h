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
class PicScaleViewComp;


class GraphicsScene;
class PictureModel;

//! Provides update of graphics scene, when SampleModel changes.

class ModelController : public ModelView::ModelListener<PictureModel> {
public:
    ModelController(PictureModel* model, PicScaleViewComp* view);

private:
    //GraphicsScene* m_scene{nullptr};
    PicScaleViewComp * m_view;
};


#endif // NODEEDITORCORE_GRAPHICSSCENECONTROLLER_H
