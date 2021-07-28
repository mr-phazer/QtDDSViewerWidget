#pragma once

#include <QWidget>
#include <qstatusbar.h>
#include <qlabel.h>
#include <qpixmap.h>
#include <qimage.h>
#include <qfile.h>
#include <qcheckbox.h>

#include "ui_QtDDSViewerWidget.h"

#include "..\..\DirectXTex\DirectXTex.h"

class QtDDSViewerWidget : public QWidget, public Ui::QtDDSViewerWidget
{
	Q_OBJECT

public:
	QtDDSViewerWidget(QWidget* parent = Q_NULLPTR);
	~QtDDSViewerWidget();

	QStatusBar* poStatusBar = nullptr;
};

/*=====================================
* Model
*=====================================*/
class QModelDDS : public QObject
{
	Q_OBJECT
public:
	Q_INVOKABLE explicit QModelDDS(QObject* parent = nullptr)
		: QObject(parent) {};

	bool loadPixMapFromDDS(QByteArray& qDDSData);
	bool loadPixMapFromDDS(std::wstring _path);

	QPixmap& getPixmap(QSize& _qSize);

	// model data
	QImage m_qImageData;
	QImage m_qImageDataScaled;

	QPixmap m_qPixMapData;
	QPixmap m_qPixMapDataScaled;
};

class QDDViewer_Controller : public QObject
{
	Q_OBJECT
public:
	Q_INVOKABLE explicit QDDViewer_Controller(QObject* parent = nullptr)
		: QObject(parent) {};

	bool setModel(QModelDDS* _pModel);
	bool setView(QtDDSViewerWidget* _pView);

	const bool setDDS(std::wstring _wstrPath);
	const bool setDDS(const QByteArray& _qBytes);

	bool updateViewAfterResize();

	bool sendPixMapToView() const;

	QtDDSViewerWidget* oView = nullptr;
	QModelDDS* m_pqModel = nullptr;
};