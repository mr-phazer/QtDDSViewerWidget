#include "QtDDSViewerWidget_Tester.h"

QtDDSViewerWidget_Tester::QtDDSViewerWidget_Tester(QWidget* parent)
	: QMainWindow(parent)
{
	this->setupUi(this);

	QtDDSViewerWidget* po = new QtDDSViewerWidget(this);
	po->setWindowFlags(po->windowFlags().setFlag(Qt::WindowType::Window));

	QModelDDS* poModel = new QModelDDS();
	QDDViewer_Controller* poControl = new QDDViewer_Controller(this);
	poControl->setModel(poModel);
	poControl->oView = po;

	poControl->setDDS(LR"(f:\Downloads\druchii_facemask1_normal.dds)");

	po->show();
}