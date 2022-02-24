// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef NODEEDITORCORE_CONNECTABLEITEMCONTROLLER_H
#define NODEEDITORCORE_CONNECTABLEITEMCONTROLLER_H

#include "mvvm/signals/itemlistener.h"
#include <memory>

class PicScaleComp;

class PictureItem;

//! Establishes communications between PictureItem and ConnectableView.
//! Provides updates of view position/appearance on graphics scene, when underlying item changes.
//! Similarly, provides update of item's properties while view is moving on the scene.

class PictureItemController : public ModelView::ItemListener<PictureItem> {
public:
    PictureItemController(PictureItem* item, PicScaleComp* view);
    ~PictureItemController() override;

    void updateItemFromView();
    void updateViewFromItem();

protected:
    void subscribe() override;

private:
    struct PictureItemControllerImpl;
    std::unique_ptr<PictureItemControllerImpl> p_impl;
};


#endif // NODEEDITORCORE_CONNECTABLEITEMCONTROLLER_H
