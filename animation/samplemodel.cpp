// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "samplemodel.h"
#include "connectableitem.h"
#include "mvvm/interfaces/undostackinterface.h"
#include "mvvm/model/modelutils.h"
#include "mvvm/factories/modeldocumentfactory.h"

#include <QDebug>
#include<QRandomGenerator>
#include <QPixmap>

using namespace ModelView;

SampleModel::SampleModel() : SessionModel("SampleModel")
{

    registerItem<ConnectableItem>();


    populateModel();

    setUndoRedoEnabled(true);
}

//! Inserts new item of given type at given position.

ConnectableItem * SampleModel::insertConnectableItem(const std::string& itemType, double xpos, double ypos)
{
    ConnectableItem * item;
    Utils::BeginMacros(this, "insertConnectableItem");

    if ( item = dynamic_cast<ConnectableItem*>(insertNewItem(itemType, rootItem())); item) {

        int iIndex = QRandomGenerator::global()->bounded(11) + 1;
        item->setQpixmap(QPixmap(QString(":/images/%1.bmp").arg(iIndex)));

        item->setX(xpos);
        item->setY(ypos);

    }else
    {
        qDebug()<<"insert failed....";
    }


    Utils::EndMacros(this);

    return item;
}

void SampleModel::loadFromFile(const std::string& name)
{
    if (name.empty())
        return;
    auto document = ModelView::CreateJsonDocument({this});
    document->load(name);
}

void SampleModel::saveToFile(const std::string& name)
{
    if (name.empty())
        return;
    auto document = ModelView::CreateJsonDocument({this});
    document->save(name);
}

//! Populates the model with an exemplary hierarchical structure representing an initial node editor
//! content.

void SampleModel::populateModel()
{
    //insertItem<ConnectableItem>();
    //auto layout = insertItem<ConnectableItem>();
    //layout->setPos(490, 30);
}
