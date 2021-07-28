#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_QtDDSViewerWidget_TesterMain.h"

#include "..\QtDDSViewerWidget\QtDDSViewerWidget\QtDDSViewerWidget.h"

class QtDDSViewerWidget_Tester : public QMainWindow, Ui::QtDDSViewerWidgetClass
{
	Q_OBJECT

public:
	QtDDSViewerWidget_Tester(QWidget* parent = Q_NULLPTR);
};
