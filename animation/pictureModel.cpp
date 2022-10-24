// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "pictureModel.h"
#include "pictureItem.h"
#include "mvvm/interfaces/undostackinterface.h"
#include "mvvm/model/modelutils.h"
#include "mvvm/factories/modeldocumentfactory.h"


#include <QDebug>
#include<QRandomGenerator>
#include <QPixmap>
#include <QThread>

using namespace ModelView;
ModelWrape::ModelWrape()
{
    m_subThread = new QThread;
    moveToThread(m_subThread);
    m_subThread->start();

    qRegisterMetaType<QPixmap>("QPixmap");
    qRegisterMetaType<std::vector<QPixmap>>("vector<QPixmap>");
    qRegisterMetaType<std::vector<ModelView::SessionItem *>>("vector<ModelView::SessionItem *>");

    connect(this, &ModelWrape::s_insertConnectItemsVec, this, &ModelWrape::slot_insertConnectItemsVec);
    connect(this, &ModelWrape::s_insertConnectItemsLst, this, &ModelWrape::slot_insertConnectItemsLst);

    //视频导入特殊处理
    connect(this, &ModelWrape::s_insertConnectItemImg, this, &ModelWrape::slot_insertConnectItemImg, Qt::BlockingQueuedConnection);
    connect(this, &ModelWrape::s_eraseConnectItem, this, &ModelWrape::slot_eraseConnectItem);
    connect(this, &ModelWrape::s_eraseConnectItems, this, &ModelWrape::slot_eraseConnectItems);
    connect(this, &ModelWrape::s_insertEmptyPicture, this, &ModelWrape::slot_insertEmptyPicture);
    connect(this, &ModelWrape::s_loadFromFile, this, &ModelWrape::slot_loadFromFile);
    connect(this, &ModelWrape::s_saveToFile, this, &ModelWrape::slot_saveToFile);

}

ModelWrape::~ModelWrape()
{
    m_subThread->quit();
    m_subThread->wait();
}

void ModelWrape::insertConnectItemsVec(const std::vector<QPixmap> lst)
{
    emit s_insertConnectItemsVec(lst);
}
void ModelWrape::insertConnectItemsLst(QStringList lst)
{
    emit s_insertConnectItemsLst(lst);
}

void ModelWrape::insertConnectItemImg(QPixmap pix)
{
    emit s_insertConnectItemImg(pix);
}
void ModelWrape::eraseConnectItem(ModelView::SessionItem * item)
{
    emit s_eraseConnectItem(item);
}
void ModelWrape::eraseConnectItems(const std::vector<ModelView::SessionItem *> lst)
{
    emit s_eraseConnectItems(lst);
}

void ModelWrape::insertEmptyPicture()
{
    emit s_insertEmptyPicture();
}

void ModelWrape::loadFromFile(const std::string& name)
{
    emit s_loadFromFile(name);
}
void ModelWrape::saveToFile(const std::string& name)
{
    emit s_saveToFile(name);
}

void ModelWrape::slot_insertConnectItemsVec(const std::vector<QPixmap> lst)
{
    m_model->insertConnectItemsVec(lst);
}

void ModelWrape::slot_insertConnectItemsLst(QStringList lst)
{
    m_model->insertConnectItemsLst(lst);
}

void ModelWrape::slot_insertConnectItemImg(QPixmap pix)
{
    m_model->insertConnectItemImg(pix);
}
void ModelWrape::slot_eraseConnectItem(ModelView::SessionItem * item)
{
    m_model->eraseConnectItem(item);
}

void ModelWrape::slot_eraseConnectItems(const std::vector<ModelView::SessionItem *> lst)
{
    m_model->eraseConnectItems(lst);
}

void ModelWrape::slot_insertEmptyPicture()
{
    m_model->insertEmptyPicture();
}

void ModelWrape::slot_loadFromFile(const std::string& name)
{
    m_model->loadFromFile(name);
}

void ModelWrape::slot_saveToFile(const std::string& name)
{
    m_model->saveToFile(name);
}

/*----------------PictureModel--------------------------------*/
PictureModel::PictureModel() : SessionModel("PictureModel")
{
    registerItem<PictureItem>();

    populateModel();
    setUndoRedoEnabled(true);
}

PictureModel::~PictureModel()
{

}

void PictureModel::insertConnectItemImg(QPixmap pix)
{
    PictureItem * item;
    Utils::BeginMacros(this, "insertConnectItemImg");

    if ( item = dynamic_cast<PictureItem*>(insertItem<PictureItem>()); item) {

        item->setQpixmap(pix);

    }else
    {
        qDebug()<<"insert failed....";
    }


    Utils::EndMacros(this);
}

void PictureModel::insertConnectItemsLst(QStringList lst)
{
    Utils::BeginMacros(this, "insertConnectableItems");
    for(auto file : lst)
    {
        PictureItem * item;
        if ( item = dynamic_cast<PictureItem*>(insertItem<PictureItem>()); item) {

            QImage pix = QImage(file);

            QPixmap pi;
            pi.convertFromImage(pix);
            item->setX(pix.width());
            item->setY(pix.height());
            item->setQpixmap(pi);


        }else
        {
            qDebug()<<"insert failed....";
        }

    }

    Utils::EndMacros(this);
}

void PictureModel::insertEmptyPicture()
{
    QImage img(300,300,QImage::Format_ARGB32);
    img.fill(QColor(255,255,255,0));
    PictureItem * item;
    Utils::BeginMacros(this, "insertEmptyPicture");

    if ( item = dynamic_cast<PictureItem*>(insertItem<PictureItem>()); item) {

        item->setQpixmap(QPixmap::fromImage(img));
        item->setX(0);
        item->setY(0);

    }else
    {
        qDebug()<<"insert failed....";
    }


    Utils::EndMacros(this);

}

void PictureModel::insertConnectItemsVec(const std::vector<QPixmap> lst)
{
    Utils::BeginMacros(this, "insertConnectableItemVec");
    for(auto file : lst)
    {
        PictureItem * item;
        if ( item = dynamic_cast<PictureItem*>(insertItem<PictureItem>()); item) {

            item->setX(file.toImage().width());
            item->setY(file.toImage().height());
            item->setQpixmap(file);

        }else
        {
            qDebug()<<"insert failed....";
        }

    }

    Utils::EndMacros(this);
}

void PictureModel::eraseConnectItem(ModelView::SessionItem * item)
{
    Utils::DeleteItemFromModel(item);
}

void PictureModel::eraseConnectItems(const std::vector<ModelView::SessionItem *> lst)
{
    Utils::BeginMacros(this, "eraseConnectItems");
    for(auto item : lst)
    {

        Utils::DeleteItemFromModel(item);
    }

    Utils::EndMacros(this);
}

void PictureModel::loadFromFile(const std::string& name)
{
    if (name.empty())
        return;
    auto document = ModelView::CreateJsonDocument({this});
    document->load(name);
}

void PictureModel::saveToFile(const std::string& name)
{
    if (name.empty())
        return;
    auto document = ModelView::CreateJsonDocument({this});
    document->save(name);
}

//! Populates the model with an exemplary hierarchical structure representing an initial node editor
//! content.

void PictureModel::populateModel()
{
    //
}

