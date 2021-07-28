#include "QtDDSViewerWidget.h"
#include <QtWidgets/QApplication>

int main(int argc, char* argv[])
{
	QApplication a(argc, argv);
	QtDDSViewerWidget w;
	w.show();
	return a.exec();
}