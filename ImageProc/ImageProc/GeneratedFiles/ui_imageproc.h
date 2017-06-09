/********************************************************************************
** Form generated from reading UI file 'imageproc.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_IMAGEPROC_H
#define UI_IMAGEPROC_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ImageProcClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *ImageProcClass)
    {
        if (ImageProcClass->objectName().isEmpty())
            ImageProcClass->setObjectName(QStringLiteral("ImageProcClass"));
        ImageProcClass->resize(600, 400);
        menuBar = new QMenuBar(ImageProcClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        ImageProcClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(ImageProcClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        ImageProcClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(ImageProcClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        ImageProcClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(ImageProcClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        ImageProcClass->setStatusBar(statusBar);

        retranslateUi(ImageProcClass);

        QMetaObject::connectSlotsByName(ImageProcClass);
    } // setupUi

    void retranslateUi(QMainWindow *ImageProcClass)
    {
        ImageProcClass->setWindowTitle(QApplication::translate("ImageProcClass", "ImageProc", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class ImageProcClass: public Ui_ImageProcClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_IMAGEPROC_H
