/********************************************************************************
** Form generated from reading UI file 'QtDDSViewerWidget.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QTDDSVIEWERWIDGET_H
#define UI_QTDDSVIEWERWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_QtDDSViewerWidget
{
public:
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout;
    QLabel *Imagelabel;
    QHBoxLayout *horizontalLayout_StatusBar;

    void setupUi(QWidget *QtDDSViewerWidget)
    {
        if (QtDDSViewerWidget->objectName().isEmpty())
            QtDDSViewerWidget->setObjectName(QString::fromUtf8("QtDDSViewerWidget"));
        QtDDSViewerWidget->resize(528, 391);
        verticalLayout_2 = new QVBoxLayout(QtDDSViewerWidget);
        verticalLayout_2->setSpacing(3);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(3, 3, 3, 3);
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        Imagelabel = new QLabel(QtDDSViewerWidget);
        Imagelabel->setObjectName(QString::fromUtf8("Imagelabel"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(Imagelabel->sizePolicy().hasHeightForWidth());
        Imagelabel->setSizePolicy(sizePolicy);

        verticalLayout->addWidget(Imagelabel);


        verticalLayout_2->addLayout(verticalLayout);

        horizontalLayout_StatusBar = new QHBoxLayout();
        horizontalLayout_StatusBar->setSpacing(6);
        horizontalLayout_StatusBar->setObjectName(QString::fromUtf8("horizontalLayout_StatusBar"));

        verticalLayout_2->addLayout(horizontalLayout_StatusBar);


        retranslateUi(QtDDSViewerWidget);

        QMetaObject::connectSlotsByName(QtDDSViewerWidget);
    } // setupUi

    void retranslateUi(QWidget *QtDDSViewerWidget)
    {
        QtDDSViewerWidget->setWindowTitle(QCoreApplication::translate("QtDDSViewerWidget", "QtDDSViewerWidget", nullptr));
        Imagelabel->setText(QCoreApplication::translate("QtDDSViewerWidget", "ImageLabel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class QtDDSViewerWidget: public Ui_QtDDSViewerWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QTDDSVIEWERWIDGET_H
