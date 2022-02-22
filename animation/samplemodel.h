// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef NODEEDITORCORE_SAMPLEMODEL_H
#define NODEEDITORCORE_SAMPLEMODEL_H

#include "mvvm/model/sessionmodel.h"
#include "mvvm/model/sessionitem.h"
#include <string>
#include <vector>
#include <QPixmap>


//! Main application model.
class ConnectableItem;

class SampleModel : public ModelView::SessionModel {
public:
    SampleModel();

    ConnectableItem * insertConnectableItem(const std::string& itemType, double xpos, double ypos, const QPixmap & pix);

    void insertConnectItems(QStringList lst);
    void insertConnectItems(const std::vector<QPixmap> lst);
    void eraseConnectItem(ModelView::SessionItem * item);

    void loadFromFile(const std::string& name);

    void saveToFile(const std::string& name);

private:
    void populateModel();
};


#endif // NODEEDITORCORE_SAMPLEMODEL_H
