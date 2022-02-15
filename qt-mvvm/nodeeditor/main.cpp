// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

//#include "nodeeditorcore/mainwindow.h"
#include "saveloadprojectcore/mainwindow.h"
#include <QApplication>
#include <QLocale>

#include <QApplication>
#include <QLocale>
#include <QTreeView>

#include "mvvm/model/compounditem.h"
#include "mvvm/model/sessionmodel.h"
#include "mvvm/signals/itemmapper.h"
#include "mvvm/viewmodel/defaultviewmodel.h"
#include "mvvm/viewmodel/viewmodeldelegate.h"

//#include "treeviewscore/mainwindow.h"

int main(int argc, char** argv)
{
    QLocale::setDefault(QLocale(QLocale::English, QLocale::UnitedStates));

    QApplication app(argc, argv);
    /*
    NodeEditor::MainWindow win;
    win.show();
    */

    /*
    ModelView::SessionModel model;
    auto item = model.insertItem<ModelView::CompoundItem>();
    item->setDisplayName("Item11");

    item->addProperty("Hello", "World!");
    item->addProperty("Your answer is", true);

    auto on_property = [](ModelView::SessionItem* item, const std::string& name) {
        if (name == "Hello")
            item->setProperty("Your answer is", item->property<std::string>("Hello") == "World!");
    };
    item->mapper()->setOnPropertyChange(on_property, nullptr);

    ModelView::DefaultViewModel viewmodel(&model);
    ModelView::ViewModelDelegate delegate;

    QTreeView view;
    view.setModel(&viewmodel);
    view.setItemDelegate(&delegate);
    view.expandAll();
    view.show();
    */

    /*
    TreeViews::MainWindow win;
    win.show();
    */

    MainWindow m;
    m.show();
    return app.exec();
}
