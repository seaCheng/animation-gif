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
class PictureItem;
class PictureModel;
class QThread;

class ModelWrape: public QObject
{
    Q_OBJECT
public:

    ModelWrape();
    ~ModelWrape();

    void setModel(PictureModel * _model)
    {
        m_model = _model;
    }
    void insertConnectItemsVec(const std::vector<QPixmap> lst);
    void insertConnectItemsLst(QStringList lst);

    void insertConnectItemImg(QPixmap pix);
    void eraseConnectItem(ModelView::SessionItem * item);
    void eraseConnectItems(const std::vector<ModelView::SessionItem *> lst);
    void insertEmptyPicture();
    void loadFromFile(const std::string& name);
    void saveToFile(const std::string& name);

signals:
    void s_insertConnectItemsVec(const std::vector<QPixmap> lst);
    void s_insertConnectItemsLst(QStringList lst);

    void s_insertConnectItemImg(QPixmap pix);
    void s_eraseConnectItem(ModelView::SessionItem * item);
    void s_eraseConnectItems(const std::vector<ModelView::SessionItem *> lst);
    void s_insertEmptyPicture();
    void s_loadFromFile(const std::string& name);
    void s_saveToFile(const std::string& name);

private slots:
    void slot_insertConnectItemsVec(const std::vector<QPixmap> lst);
    void slot_insertConnectItemsLst(QStringList lst);

    void slot_insertConnectItemImg(QPixmap pix);
    void slot_eraseConnectItem(ModelView::SessionItem * item);
    void slot_eraseConnectItems(const std::vector<ModelView::SessionItem *> lst);
    void slot_insertEmptyPicture();
    void slot_loadFromFile(const std::string& name);
    void slot_saveToFile(const std::string& name);

private:
    PictureModel * m_model;
    QThread  * m_subThread = nullptr;
};

class PictureModel : public ModelView::SessionModel {

public:
    PictureModel();
    ~PictureModel();

    void insertConnectItemsLst(QStringList lst);
    void insertConnectItemsVec(const std::vector<QPixmap> lst);
    void insertConnectItemImg(QPixmap pix);
    void eraseConnectItem(ModelView::SessionItem * item);
    void eraseConnectItems(const std::vector<ModelView::SessionItem *> lst);

    void insertEmptyPicture();

    void loadFromFile(const std::string& name);

    void saveToFile(const std::string& name);

signals:
    //void s_insertConnectItemsVec(const std::vector<QPixmap> lst);
    //void s_insertConnectItemsLst(QStringList lst);

private slots:
    //void slot_insertConnectItemsVec(const std::vector<QPixmap> lst);
    //void slot_insertConnectItemsLst(QStringList lst);
private:
    void populateModel();
};


#endif // NODEEDITORCORE_SAMPLEMODEL_H
