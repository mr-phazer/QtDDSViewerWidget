#include "QtDDSViewerWidget.h"

QtDDSViewerWidget::QtDDSViewerWidget(QWidget* parent)
	: QWidget(parent)
{
	setupUi(this);

	poStatusBar = new QStatusBar(this);

	poStatusBar->insertWidget(1, new QLabel("BC1 UNORM RGBA", poStatusBar), 100);
	poStatusBar->addWidget(new QLabel("1024x1024", poStatusBar), 100);
	poStatusBar->addWidget(new QLabel("2D", poStatusBar), 100);
	poStatusBar->addWidget(new QCheckBox("R", poStatusBar), 100);
	poStatusBar->addWidget(new QCheckBox("G", poStatusBar), 100);
	poStatusBar->addWidget(new QCheckBox("B", poStatusBar), 100);
	poStatusBar->addWidget(new QCheckBox("A", poStatusBar), 100);

	horizontalLayout_StatusBar->addWidget(poStatusBar);

#pragma region unused

	//DirectX::ScratchImage scratchImage;
	//DirectX::TexMetadata metaData;

	//HRESULT hr = S_OK;

	//hr = DirectX::LoadFromDDSFile
	//(
	//	LR"(f:\Downloads\druchii_facemask1_normal.dds)",
	//	DirectX::DDS_FLAGS::DDS_FLAGS_NONE,
	//	&metaData,
	//	scratchImage

	//);

	//DirectX::ScratchImage scratchImageDemcomp;

	//hr = DirectX::Decompress(*scratchImage.GetImage(0, 0, 0), DXGI_FORMAT_R8G8B8A8_UNORM, scratchImageDemcomp);

	//const DirectX::Image* image = scratchImageDemcomp.GetImage(0, 0, 0);

	//QPixmap map1;
	//QImage* img = new QImage(metaData.width, metaData.height, QImage::Format_RGBA8888);

	//auto byte_per_line = img->bytesPerLine();
	//auto row_pith = image->rowPitch;

	//for (int y = 0; y < img->height(); y++) {
	//	memcpy(
	//		img->scanLine(y),
	//		&image->pixels[y * image->rowPitch],
	//		//image->width
	//		image->rowPitch

	//	);
	//}

	//auto p = img->scanLine(0);

	//auto imgScaled = img->scaled(this->size());
	//auto pixMap = QPixmap::fromImage(imgScaled);// , Qt::ImageConversionFlag::NoAlpha);

	//Imagelabel->setPixmap(pixMap);
	//Imagelabel->update();

	//int debug_1 = 1;

#pragma endregion unused
}

QtDDSViewerWidget::~QtDDSViewerWidget()
{
}

bool QModelDDS::loadPixMapFromDDS(QByteArray& qDDSData)
{
	// DirectXTex types
	DirectX::ScratchImage scratchImage;
	DirectX::TexMetadata metaData;
	DirectX::ScratchImage scratchImageDemcomp;
	DirectX::ScratchImage scratchImageConvert;

	// return value of DirectXTex ops
	HRESULT hr = S_OK;

	// use DirecXTex to load DDS File into memory, and get metadata
	hr = DirectX::LoadFromDDSMemory
	(
		qDDSData.constData(),
		qDDSData.size(),
		DirectX::DDS_FLAGS::DDS_FLAGS_NONE,
		&metaData,
		scratchImage
	);

	if (!SUCCEEDED(hr))
	{
		return false;
	}

	// set the image to be used, the unconverted, ´not decompressed data,
	// will be changed if data is compressed or needs conversion
	const DirectX::Image* image = scratchImage.GetImage(0, 0, 0);

	// check if compreesion is used, if it is, decompress the file
	if (DirectX::IsCompressed(metaData.format))
	{
		// decompress the blockcompressed DDS
		hr = DirectX::Decompress(*scratchImage.GetImage(0, 0, 0), DXGI_FORMAT_R8G8B8A8_UNORM, scratchImageDemcomp);
		if (!SUCCEEDED(hr))
		{
			return false;
		}
		// set Image ptr to decompressed image
		image = scratchImageDemcomp.GetImage(0, 0, 0);
		// set meta data to the converted format
		metaData = scratchImageDemcomp.GetMetadata();
	}

	//if (DirectX::BitsPerPixel(metaData.format) != 32)
	if (metaData.format != DXGI_FORMAT::DXGI_FORMAT_R8G8B8A8_UNORM) // if not the exact format
	{
		hr = DirectX::Convert(
			*scratchImage.GetImage(0, 0, 0),
			DXGI_FORMAT::DXGI_FORMAT_R8G8B8A8_UNORM,
			DirectX::TEX_FILTER_FLAGS::TEX_FILTER_DEFAULT,
			DirectX::TEX_THRESHOLD_DEFAULT,
			scratchImageConvert
		);

		if (!SUCCEEDED(hr))
		{
			return false;
		}
		// set Image ptr to decompressed image
		image = scratchImageConvert.GetImage(0, 0, 0);
	}

	// create a mew 32 bit RGBA QImage to the the pixel data
	m_qImageData = QImage(metaData.width, metaData.height, QImage::Format_RGBA8888);

	// get the row pitch for qt image and Tex image
	auto byte_per_line = m_qImageData.bytesPerLine();
	auto row_pith = image->rowPitch;

	// copy pixel data from Tex image into QPixmap
	for (int y = 0; y < m_qImageData.height(); y++) {
		memcpy(
			m_qImageData.scanLine(y),
			&image->pixels[y * image->rowPitch],
			//image->width
			image->rowPitch

		);
	}

	m_qPixMapData = QPixmap::fromImage(m_qImageData);// , Qt::ImageConversionFlag::NoAlpha);

	return true;
}

bool QModelDDS::loadPixMapFromDDS(std::wstring _path)
{
	QFile file(QString::fromStdWString(_path));
	if (!file.open(QIODevice::ReadOnly))
	{
		return false;
	}

	QByteArray qBytes = file.readAll();

	if (qBytes.isEmpty())
	{
		return false;
	}

	return loadPixMapFromDDS(qBytes);
}

// return the pixmap of the image in the desired size
QPixmap& QModelDDS::getPixmap(QSize& _qSize)
{
	auto m_qImageDataScaled = m_qImageData.scaled(_qSize);
	m_qPixMapDataScaled = QPixmap::fromImage(m_qImageDataScaled);// , Qt::ImageConversionFlag::NoAlpha);

	return m_qPixMapDataScaled;
}

/*-----------------------------------------------------
*
* Controller
*
------------------------------------------------------*/
bool QDDViewer_Controller::setModel(QModelDDS* _pModel)
{
	if (_pModel == nullptr)
	{
		return false;
	}

	m_pqModel = _pModel;

	if (_pModel->parent() == nullptr)
	{
		m_pqModel->setParent(this);
	}

	return true;
}

const bool QDDViewer_Controller::setDDS(std::wstring _wstrPath)
{
	bool bResult = m_pqModel->loadPixMapFromDDS(_wstrPath);

	QSize qViewSize = oView->size();

	QPixmap qPixMap = m_pqModel->getPixmap(qViewSize);

	if (qPixMap.isNull())
	{
		return false;
	}

	oView->Imagelabel->setPixmap(qPixMap);

	return true;
}