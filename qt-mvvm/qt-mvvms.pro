######################################################################
# Automatically generated by qmake (3.1) Fri Jan 7 15:12:34 2022
######################################################################

TEMPLATE = lib
CONFIG += staticlib

DEFINES += MVVM_MODEL_STATIC_DEFINE \
    MVVM_VIEW_STATIC_DEFINE \
    MVVM_VIEWMODEL_STATIC_DEFINE

QT += printsupport
#TEMPLATE = app
TARGET = qtMvvm


CONFIG(debug, debug|release) {
    DESTDIR = $$PWD/../lib/debug
}
else {
    DESTDIR = $$PWD/../lib/release
}

INCLUDEPATH += .

CONFIG += c++17

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

INCLUDEPATH += \
$$PWD/source/libmvvm_model \
$$PWD/source/libmvvm_view \
$$PWD/source/libmvvm_viewmodel \
$$PWD/mples/modelinqml \
$$PWD/thirdparty/qcustomplot \
$$PWD/thirdparty/gtest/googletest/googletest/include  \
$$PWD/autogen/mvvm

# You can make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# Please consult the documentation of the deprecated API in order to know
# how to port your code away from it.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

# Input
HEADERS += \
           autogen/mvvm/testconfig.h \
           autogen/mvvm/mvvm/model_export.h \
           autogen/mvvm/mvvm/view_export.h \
           autogen/mvvm/mvvm/viewmodel_export.h \
           source/libmvvm_model/mvvm/commands/abstractitemcommand.h \
           source/libmvvm_model/mvvm/commands/commandadapter.h \
           source/libmvvm_model/mvvm/commands/commandresult.h \
           source/libmvvm_model/mvvm/commands/commandservice.h \
           source/libmvvm_model/mvvm/commands/commandutils.h \
           source/libmvvm_model/mvvm/commands/copyitemcommand.h \
           source/libmvvm_model/mvvm/commands/insertnewitemcommand.h \
           source/libmvvm_model/mvvm/commands/moveitemcommand.h \
           source/libmvvm_model/mvvm/commands/removeitemcommand.h \
           source/libmvvm_model/mvvm/commands/setvaluecommand.h \
           source/libmvvm_model/mvvm/commands/undostack.h \
           source/libmvvm_model/mvvm/core/filesystem.h \
           source/libmvvm_model/mvvm/core/types.h \
           source/libmvvm_model/mvvm/core/uniqueidgenerator.h \
           source/libmvvm_model/mvvm/core/variant.h \
           source/libmvvm_model/mvvm/core/version.h \
           source/libmvvm_model/mvvm/factories/itemcataloguefactory.h \
           source/libmvvm_model/mvvm/factories/itemconverterfactory.h \
           source/libmvvm_model/mvvm/factories/modelconverterfactory.h \
           source/libmvvm_model/mvvm/factories/modeldocumentfactory.h \
           source/libmvvm_model/mvvm/factories/projectmanagerfactory.h \
           source/libmvvm_model/mvvm/interfaces/applicationmodelsinterface.h \
           source/libmvvm_model/mvvm/interfaces/itembackupstrategy.h \
           source/libmvvm_model/mvvm/interfaces/itemcopystrategy.h \
           source/libmvvm_model/mvvm/interfaces/itemfactoryinterface.h \
           source/libmvvm_model/mvvm/interfaces/itemlistenerinterface.h \
           source/libmvvm_model/mvvm/interfaces/modeldocumentinterface.h \
           source/libmvvm_model/mvvm/interfaces/modellistenerinterface.h \
           source/libmvvm_model/mvvm/interfaces/projectinterface.h \
           source/libmvvm_model/mvvm/interfaces/projectmanagerinterface.h \
           source/libmvvm_model/mvvm/interfaces/undostackinterface.h \
           source/libmvvm_model/mvvm/model/comboproperty.h \
           source/libmvvm_model/mvvm/model/comparators.h \
           source/libmvvm_model/mvvm/model/compounditem.h \
           source/libmvvm_model/mvvm/model/customvariants.h \
           source/libmvvm_model/mvvm/model/datarole.h \
           source/libmvvm_model/mvvm/model/externalproperty.h \
           source/libmvvm_model/mvvm/model/function_types.h \
           source/libmvvm_model/mvvm/model/groupitem.h \
           source/libmvvm_model/mvvm/model/itemcatalogue.h \
           source/libmvvm_model/mvvm/model/itemfactory.h \
           source/libmvvm_model/mvvm/model/itemmanager.h \
           source/libmvvm_model/mvvm/model/itempool.h \
           source/libmvvm_model/mvvm/model/itemutils.h \
           source/libmvvm_model/mvvm/model/modelutils.h \
           source/libmvvm_model/mvvm/model/mvvm_types.h \
           source/libmvvm_model/mvvm/model/path.h \
           source/libmvvm_model/mvvm/model/propertyitem.h \
           source/libmvvm_model/mvvm/model/sessionitem.h \
           source/libmvvm_model/mvvm/model/sessionitemcontainer.h \
           source/libmvvm_model/mvvm/model/sessionitemdata.h \
           source/libmvvm_model/mvvm/model/sessionitemtags.h \
           source/libmvvm_model/mvvm/model/sessionmodel.h \
           source/libmvvm_model/mvvm/model/taginfo.h \
           source/libmvvm_model/mvvm/model/tagrow.h \
           source/libmvvm_model/mvvm/model/variant_constants.h \
           source/libmvvm_model/mvvm/project/modelhaschangedcontroller.h \
           source/libmvvm_model/mvvm/project/project.h \
           source/libmvvm_model/mvvm/project/project_types.h \
           source/libmvvm_model/mvvm/project/projectchangecontroller.h \
           source/libmvvm_model/mvvm/project/projectmanager.h \
           source/libmvvm_model/mvvm/project/projectmanagerdecorator.h \
           source/libmvvm_model/mvvm/project/projectutils.h \
           source/libmvvm_model/mvvm/serialization/compatibilityutils.h \
           source/libmvvm_model/mvvm/serialization/jsonconverterinterfaces.h \
           source/libmvvm_model/mvvm/serialization/jsondocument.h \
           source/libmvvm_model/mvvm/serialization/jsonitem_types.h \
           source/libmvvm_model/mvvm/serialization/jsonitembackupstrategy.h \
           source/libmvvm_model/mvvm/serialization/jsonitemcontainerconverter.h \
           source/libmvvm_model/mvvm/serialization/jsonitemconverter.h \
           source/libmvvm_model/mvvm/serialization/jsonitemconverterinterface.h \
           source/libmvvm_model/mvvm/serialization/jsonitemcopystrategy.h \
           source/libmvvm_model/mvvm/serialization/jsonitemdataconverter.h \
           source/libmvvm_model/mvvm/serialization/jsonitemdataconverterinterface.h \
           source/libmvvm_model/mvvm/serialization/jsonitemformatassistant.h \
           source/libmvvm_model/mvvm/serialization/jsonitemtagsconverter.h \
           source/libmvvm_model/mvvm/serialization/jsonmodelconverter.h \
           source/libmvvm_model/mvvm/serialization/jsonmodelconverterinterface.h \
           source/libmvvm_model/mvvm/serialization/jsontaginfoconverter.h \
           source/libmvvm_model/mvvm/serialization/jsontaginfoconverterinterface.h \
           source/libmvvm_model/mvvm/serialization/jsonutils.h \
           source/libmvvm_model/mvvm/serialization/jsonvariantconverter.h \
           source/libmvvm_model/mvvm/serialization/jsonvariantconverterinterface.h \
           source/libmvvm_model/mvvm/signals/callback_types.h \
           source/libmvvm_model/mvvm/signals/callbackcontainer.h \
           source/libmvvm_model/mvvm/signals/itemlistener.h \
           source/libmvvm_model/mvvm/signals/itemlistenerbase.h \
           source/libmvvm_model/mvvm/signals/itemmapper.h \
           source/libmvvm_model/mvvm/signals/modellistener.h \
           source/libmvvm_model/mvvm/signals/modellistenerbase.h \
           source/libmvvm_model/mvvm/signals/modelmapper.h \
           source/libmvvm_model/mvvm/standarditems/axisitems.h \
           source/libmvvm_model/mvvm/standarditems/colormapitem.h \
           source/libmvvm_model/mvvm/standarditems/colormapviewportitem.h \
           source/libmvvm_model/mvvm/standarditems/containeritem.h \
           source/libmvvm_model/mvvm/standarditems/data1ditem.h \
           source/libmvvm_model/mvvm/standarditems/data2ditem.h \
           source/libmvvm_model/mvvm/standarditems/graphitem.h \
           source/libmvvm_model/mvvm/standarditems/graphviewportitem.h \
           source/libmvvm_model/mvvm/standarditems/linkeditem.h \
           source/libmvvm_model/mvvm/standarditems/plottableitems.h \
           source/libmvvm_model/mvvm/standarditems/standarditemincludes.h \
           source/libmvvm_model/mvvm/standarditems/vectoritem.h \
           source/libmvvm_model/mvvm/standarditems/viewportitem.h \
           source/libmvvm_model/mvvm/utils/binutils.h \
           source/libmvvm_model/mvvm/utils/containerutils.h \
           source/libmvvm_model/mvvm/utils/fileutils.h \
           source/libmvvm_model/mvvm/utils/ifactory.h \
           source/libmvvm_model/mvvm/utils/mathconstants.h \
           source/libmvvm_model/mvvm/utils/numericutils.h \
           source/libmvvm_model/mvvm/utils/progresshandler.h \
           source/libmvvm_model/mvvm/utils/reallimits.h \
           source/libmvvm_model/mvvm/utils/stringutils.h \
           source/libmvvm_model/mvvm/utils/threadsafestack.h \
           source/libmvvm_view/mvvm/plotting/axistitlecontroller.h \
           source/libmvvm_view/mvvm/plotting/colormapcanvas.h \
           source/libmvvm_view/mvvm/plotting/colormapinfoformatter.h \
           source/libmvvm_view/mvvm/plotting/colormapplotcontroller.h \
           source/libmvvm_view/mvvm/plotting/colormapviewportplotcontroller.h \
           source/libmvvm_view/mvvm/plotting/colorscaleplotcontroller.h \
           source/libmvvm_view/mvvm/plotting/customplotproxywidget.h \
           source/libmvvm_view/mvvm/plotting/customplotsceneadapter.h \
           source/libmvvm_view/mvvm/plotting/customplotutils.h \
           source/libmvvm_view/mvvm/plotting/data1dplotcontroller.h \
           source/libmvvm_view/mvvm/plotting/data2dplotcontroller.h \
           source/libmvvm_view/mvvm/plotting/graphcanvas.h \
           source/libmvvm_view/mvvm/plotting/graphinfoformatter.h \
           source/libmvvm_view/mvvm/plotting/graphplotcontroller.h \
           source/libmvvm_view/mvvm/plotting/graphviewportplotcontroller.h \
           source/libmvvm_view/mvvm/plotting/mousemovereporter.h \
           source/libmvvm_view/mvvm/plotting/mouseposinfo.h \
           source/libmvvm_view/mvvm/plotting/pencontroller.h \
           source/libmvvm_view/mvvm/plotting/sceneadapterinterface.h \
           source/libmvvm_view/mvvm/plotting/statusstringformatterinterface.h \
           source/libmvvm_view/mvvm/plotting/statusstringreporter.h \
           source/libmvvm_view/mvvm/plotting/statusstringreporterfactory.h \
           source/libmvvm_view/mvvm/plotting/viewportaxisplotcontroller.h \
           source/libmvvm_view/mvvm/widgets/adjustingscrollarea.h \
           source/libmvvm_view/mvvm/widgets/allitemstreeview.h \
           source/libmvvm_view/mvvm/widgets/collapsiblebar.h \
           source/libmvvm_view/mvvm/widgets/collapsiblelistwidget.h \
           source/libmvvm_view/mvvm/widgets/itemstreeview.h \
           source/libmvvm_view/mvvm/widgets/itemstreeviewinterface.h \
           source/libmvvm_view/mvvm/widgets/layoututils.h \
           source/libmvvm_view/mvvm/widgets/propertyflatview.h \
           source/libmvvm_view/mvvm/widgets/propertytreeview.h \
           source/libmvvm_view/mvvm/widgets/standardtreeviews.h \
           source/libmvvm_view/mvvm/widgets/statuslabel.h \
           source/libmvvm_view/mvvm/widgets/topitemstreeview.h \
           source/libmvvm_view/mvvm/widgets/widgetutils.h \
           source/libmvvm_viewmodel/mvvm/editors/booleditor.h \
           source/libmvvm_viewmodel/mvvm/editors/coloreditor.h \
           source/libmvvm_viewmodel/mvvm/editors/combopropertyeditor.h \
           source/libmvvm_viewmodel/mvvm/editors/customeditor.h \
           source/libmvvm_viewmodel/mvvm/editors/customeventfilters.h \
           source/libmvvm_viewmodel/mvvm/editors/defaulteditorfactory.h \
           source/libmvvm_viewmodel/mvvm/editors/doubleeditor.h \
           source/libmvvm_viewmodel/mvvm/editors/editor_constants.h \
           source/libmvvm_viewmodel/mvvm/editors/editorbuilders.h \
           source/libmvvm_viewmodel/mvvm/editors/externalpropertycomboeditor.h \
           source/libmvvm_viewmodel/mvvm/editors/externalpropertyeditor.h \
           source/libmvvm_viewmodel/mvvm/editors/integereditor.h \
           source/libmvvm_viewmodel/mvvm/editors/scientificdoubleeditor.h \
           source/libmvvm_viewmodel/mvvm/editors/scientificspinbox.h \
           source/libmvvm_viewmodel/mvvm/editors/scientificspinboxeditor.h \
           source/libmvvm_viewmodel/mvvm/editors/selectablecomboboxeditor.h \
           source/libmvvm_viewmodel/mvvm/editors/styleutils.h \
           source/libmvvm_viewmodel/mvvm/factories/viewmodelcontrollerbuilder.h \
           source/libmvvm_viewmodel/mvvm/factories/viewmodelcontrollerfactory.h \
           source/libmvvm_viewmodel/mvvm/factories/viewmodelfactory.h \
           source/libmvvm_viewmodel/mvvm/interfaces/celldecoratorinterface.h \
           source/libmvvm_viewmodel/mvvm/interfaces/childrenstrategyinterface.h \
           source/libmvvm_viewmodel/mvvm/interfaces/editorfactoryinterface.h \
           source/libmvvm_viewmodel/mvvm/interfaces/rowstrategyinterface.h \
           source/libmvvm_viewmodel/mvvm/viewmodel/defaultcelldecorator.h \
           source/libmvvm_viewmodel/mvvm/viewmodel/defaultviewmodel.h \
           source/libmvvm_viewmodel/mvvm/viewmodel/labeldatarowstrategy.h \
           source/libmvvm_viewmodel/mvvm/viewmodel/propertiesrowstrategy.h \
           source/libmvvm_viewmodel/mvvm/viewmodel/propertyflatviewmodel.h \
           source/libmvvm_viewmodel/mvvm/viewmodel/propertytableviewmodel.h \
           source/libmvvm_viewmodel/mvvm/viewmodel/propertyviewmodel.h \
           source/libmvvm_viewmodel/mvvm/viewmodel/standardchildrenstrategies.h \
           source/libmvvm_viewmodel/mvvm/viewmodel/standardviewitems.h \
           source/libmvvm_viewmodel/mvvm/viewmodel/standardviewmodelcontrollers.h \
           source/libmvvm_viewmodel/mvvm/viewmodel/topitemsviewmodel.h \
           source/libmvvm_viewmodel/mvvm/viewmodel/viewitem.h \
           source/libmvvm_viewmodel/mvvm/viewmodel/viewmodel.h \
           source/libmvvm_viewmodel/mvvm/viewmodel/viewmodelbase.h \
           source/libmvvm_viewmodel/mvvm/viewmodel/viewmodelcontroller.h \
           source/libmvvm_viewmodel/mvvm/viewmodel/viewmodeldelegate.h \
           source/libmvvm_viewmodel/mvvm/viewmodel/viewmodelutils.h \
           thirdparty/qcustomplot/qcustomplot.h
SOURCES +=  \
           source/libmvvm_model/mvvm/commands/abstractitemcommand.cpp \
           source/libmvvm_model/mvvm/commands/commandadapter.cpp \
           source/libmvvm_model/mvvm/commands/commandservice.cpp \
           source/libmvvm_model/mvvm/commands/commandutils.cpp \
           source/libmvvm_model/mvvm/commands/copyitemcommand.cpp \
           source/libmvvm_model/mvvm/commands/insertnewitemcommand.cpp \
           source/libmvvm_model/mvvm/commands/moveitemcommand.cpp \
           source/libmvvm_model/mvvm/commands/removeitemcommand.cpp \
           source/libmvvm_model/mvvm/commands/setvaluecommand.cpp \
           source/libmvvm_model/mvvm/commands/undostack.cpp \
           source/libmvvm_model/mvvm/core/uniqueidgenerator.cpp \
           source/libmvvm_model/mvvm/factories/itemcataloguefactory.cpp \
           source/libmvvm_model/mvvm/factories/itemconverterfactory.cpp \
           source/libmvvm_model/mvvm/factories/modelconverterfactory.cpp \
           source/libmvvm_model/mvvm/factories/modeldocumentfactory.cpp \
           source/libmvvm_model/mvvm/factories/projectmanagerfactory.cpp \
           source/libmvvm_model/mvvm/model/comboproperty.cpp \
           source/libmvvm_model/mvvm/model/comparators.cpp \
           source/libmvvm_model/mvvm/model/compounditem.cpp \
           source/libmvvm_model/mvvm/model/customvariants.cpp \
           source/libmvvm_model/mvvm/model/datarole.cpp \
           source/libmvvm_model/mvvm/model/externalproperty.cpp \
           source/libmvvm_model/mvvm/model/groupitem.cpp \
           source/libmvvm_model/mvvm/model/itemcatalogue.cpp \
           source/libmvvm_model/mvvm/model/itemfactory.cpp \
           source/libmvvm_model/mvvm/model/itemmanager.cpp \
           source/libmvvm_model/mvvm/model/itempool.cpp \
           source/libmvvm_model/mvvm/model/itemutils.cpp \
           source/libmvvm_model/mvvm/model/modelutils.cpp \
           source/libmvvm_model/mvvm/model/path.cpp \
           source/libmvvm_model/mvvm/model/propertyitem.cpp \
           source/libmvvm_model/mvvm/model/sessionitem.cpp \
           source/libmvvm_model/mvvm/model/sessionitemcontainer.cpp \
           source/libmvvm_model/mvvm/model/sessionitemdata.cpp \
           source/libmvvm_model/mvvm/model/sessionitemtags.cpp \
           source/libmvvm_model/mvvm/model/sessionmodel.cpp \
           source/libmvvm_model/mvvm/model/taginfo.cpp \
           source/libmvvm_model/mvvm/model/tagrow.cpp \
           source/libmvvm_model/mvvm/project/modelhaschangedcontroller.cpp \
           source/libmvvm_model/mvvm/project/project.cpp \
           source/libmvvm_model/mvvm/project/projectchangecontroller.cpp \
           source/libmvvm_model/mvvm/project/projectmanager.cpp \
           source/libmvvm_model/mvvm/project/projectmanagerdecorator.cpp \
           source/libmvvm_model/mvvm/project/projectutils.cpp \
           source/libmvvm_model/mvvm/serialization/compatibilityutils.cpp \
           source/libmvvm_model/mvvm/serialization/jsondocument.cpp \
           source/libmvvm_model/mvvm/serialization/jsonitembackupstrategy.cpp \
           source/libmvvm_model/mvvm/serialization/jsonitemcontainerconverter.cpp \
           source/libmvvm_model/mvvm/serialization/jsonitemconverter.cpp \
           source/libmvvm_model/mvvm/serialization/jsonitemcopystrategy.cpp \
           source/libmvvm_model/mvvm/serialization/jsonitemdataconverter.cpp \
           source/libmvvm_model/mvvm/serialization/jsonitemformatassistant.cpp \
           source/libmvvm_model/mvvm/serialization/jsonitemtagsconverter.cpp \
           source/libmvvm_model/mvvm/serialization/jsonmodelconverter.cpp \
           source/libmvvm_model/mvvm/serialization/jsontaginfoconverter.cpp \
           source/libmvvm_model/mvvm/serialization/jsonutils.cpp \
           source/libmvvm_model/mvvm/serialization/jsonvariantconverter.cpp \
           source/libmvvm_model/mvvm/signals/itemlistenerbase.cpp \
           source/libmvvm_model/mvvm/signals/itemmapper.cpp \
           source/libmvvm_model/mvvm/signals/modellistenerbase.cpp \
           source/libmvvm_model/mvvm/signals/modelmapper.cpp \
           source/libmvvm_model/mvvm/standarditems/axisitems.cpp \
           source/libmvvm_model/mvvm/standarditems/colormapitem.cpp \
           source/libmvvm_model/mvvm/standarditems/colormapviewportitem.cpp \
           source/libmvvm_model/mvvm/standarditems/containeritem.cpp \
           source/libmvvm_model/mvvm/standarditems/data1ditem.cpp \
           source/libmvvm_model/mvvm/standarditems/data2ditem.cpp \
           source/libmvvm_model/mvvm/standarditems/graphitem.cpp \
           source/libmvvm_model/mvvm/standarditems/graphviewportitem.cpp \
           source/libmvvm_model/mvvm/standarditems/linkeditem.cpp \
           source/libmvvm_model/mvvm/standarditems/plottableitems.cpp \
           source/libmvvm_model/mvvm/standarditems/vectoritem.cpp \
           source/libmvvm_model/mvvm/standarditems/viewportitem.cpp \
           source/libmvvm_model/mvvm/utils/binutils.cpp \
           source/libmvvm_model/mvvm/utils/containerutils.cpp \
           source/libmvvm_model/mvvm/utils/fileutils.cpp \
           source/libmvvm_model/mvvm/utils/numericutils.cpp \
           source/libmvvm_model/mvvm/utils/progresshandler.cpp \
           source/libmvvm_model/mvvm/utils/reallimits.cpp \
           source/libmvvm_model/mvvm/utils/stringutils.cpp \
           source/libmvvm_view/mvvm/plotting/axistitlecontroller.cpp \
           source/libmvvm_view/mvvm/plotting/colormapcanvas.cpp \
           source/libmvvm_view/mvvm/plotting/colormapinfoformatter.cpp \
           source/libmvvm_view/mvvm/plotting/colormapplotcontroller.cpp \
           source/libmvvm_view/mvvm/plotting/colormapviewportplotcontroller.cpp \
           source/libmvvm_view/mvvm/plotting/colorscaleplotcontroller.cpp \
           source/libmvvm_view/mvvm/plotting/customplotproxywidget.cpp \
           source/libmvvm_view/mvvm/plotting/customplotsceneadapter.cpp \
           source/libmvvm_view/mvvm/plotting/customplotutils.cpp \
           source/libmvvm_view/mvvm/plotting/data1dplotcontroller.cpp \
           source/libmvvm_view/mvvm/plotting/data2dplotcontroller.cpp \
           source/libmvvm_view/mvvm/plotting/graphcanvas.cpp \
           source/libmvvm_view/mvvm/plotting/graphinfoformatter.cpp \
           source/libmvvm_view/mvvm/plotting/graphplotcontroller.cpp \
           source/libmvvm_view/mvvm/plotting/graphviewportplotcontroller.cpp \
           source/libmvvm_view/mvvm/plotting/mousemovereporter.cpp \
           source/libmvvm_view/mvvm/plotting/pencontroller.cpp \
           source/libmvvm_view/mvvm/plotting/statusstringreporter.cpp \
           source/libmvvm_view/mvvm/plotting/statusstringreporterfactory.cpp \
           source/libmvvm_view/mvvm/plotting/viewportaxisplotcontroller.cpp \
           source/libmvvm_view/mvvm/widgets/adjustingscrollarea.cpp \
           source/libmvvm_view/mvvm/widgets/allitemstreeview.cpp \
           source/libmvvm_view/mvvm/widgets/collapsiblebar.cpp \
           source/libmvvm_view/mvvm/widgets/collapsiblelistwidget.cpp \
           source/libmvvm_view/mvvm/widgets/itemstreeview.cpp \
           source/libmvvm_view/mvvm/widgets/layoututils.cpp \
           source/libmvvm_view/mvvm/widgets/propertyflatview.cpp \
           source/libmvvm_view/mvvm/widgets/propertytreeview.cpp \
           source/libmvvm_view/mvvm/widgets/statuslabel.cpp \
           source/libmvvm_view/mvvm/widgets/topitemstreeview.cpp \
           source/libmvvm_view/mvvm/widgets/widgetutils.cpp \
           source/libmvvm_viewmodel/mvvm/editors/booleditor.cpp \
           source/libmvvm_viewmodel/mvvm/editors/coloreditor.cpp \
           source/libmvvm_viewmodel/mvvm/editors/combopropertyeditor.cpp \
           source/libmvvm_viewmodel/mvvm/editors/customeditor.cpp \
           source/libmvvm_viewmodel/mvvm/editors/customeventfilters.cpp \
           source/libmvvm_viewmodel/mvvm/editors/defaulteditorfactory.cpp \
           source/libmvvm_viewmodel/mvvm/editors/doubleeditor.cpp \
           source/libmvvm_viewmodel/mvvm/editors/editorbuilders.cpp \
           source/libmvvm_viewmodel/mvvm/editors/externalpropertycomboeditor.cpp \
           source/libmvvm_viewmodel/mvvm/editors/externalpropertyeditor.cpp \
           source/libmvvm_viewmodel/mvvm/editors/integereditor.cpp \
           source/libmvvm_viewmodel/mvvm/editors/scientificdoubleeditor.cpp \
           source/libmvvm_viewmodel/mvvm/editors/scientificspinbox.cpp \
           source/libmvvm_viewmodel/mvvm/editors/scientificspinboxeditor.cpp \
           source/libmvvm_viewmodel/mvvm/editors/selectablecomboboxeditor.cpp \
           source/libmvvm_viewmodel/mvvm/editors/styleutils.cpp \
           source/libmvvm_viewmodel/mvvm/factories/viewmodelcontrollerbuilder.cpp \
           source/libmvvm_viewmodel/mvvm/factories/viewmodelfactory.cpp \
           source/libmvvm_viewmodel/mvvm/viewmodel/defaultcelldecorator.cpp \
           source/libmvvm_viewmodel/mvvm/viewmodel/defaultviewmodel.cpp \
           source/libmvvm_viewmodel/mvvm/viewmodel/labeldatarowstrategy.cpp \
           source/libmvvm_viewmodel/mvvm/viewmodel/propertiesrowstrategy.cpp \
           source/libmvvm_viewmodel/mvvm/viewmodel/propertyflatviewmodel.cpp \
           source/libmvvm_viewmodel/mvvm/viewmodel/propertytableviewmodel.cpp \
           source/libmvvm_viewmodel/mvvm/viewmodel/propertyviewmodel.cpp \
           source/libmvvm_viewmodel/mvvm/viewmodel/standardchildrenstrategies.cpp \
           source/libmvvm_viewmodel/mvvm/viewmodel/standardviewitems.cpp \
           source/libmvvm_viewmodel/mvvm/viewmodel/standardviewmodelcontrollers.cpp \
           source/libmvvm_viewmodel/mvvm/viewmodel/topitemsviewmodel.cpp \
           source/libmvvm_viewmodel/mvvm/viewmodel/viewitem.cpp \
           source/libmvvm_viewmodel/mvvm/viewmodel/viewmodel.cpp \
           source/libmvvm_viewmodel/mvvm/viewmodel/viewmodelbase.cpp \
           source/libmvvm_viewmodel/mvvm/viewmodel/viewmodelcontroller.cpp \
           source/libmvvm_viewmodel/mvvm/viewmodel/viewmodeldelegate.cpp \
           source/libmvvm_viewmodel/mvvm/viewmodel/viewmodelutils.cpp \
           thirdparty/qcustomplot/qcustomplot.cpp
