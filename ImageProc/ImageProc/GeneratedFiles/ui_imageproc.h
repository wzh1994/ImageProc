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
#include <QtWidgets/QPushButton>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ImageProcClass
{
public:
    QWidget *centralWidget;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *v1;
    QPushButton *b1;
    QPushButton *b2;
    QPushButton *b3;
    QPushButton *b4;
    QPushButton *b5;
    QWidget *verticalLayoutWidget_2;
    QVBoxLayout *verticalLayout;
    QPushButton *b6;
    QPushButton *b7;
    QPushButton *b8;
    QPushButton *b9;
    QWidget *verticalLayoutWidget_3;
    QVBoxLayout *verticalLayout_2;
    QPushButton *b10;
    QPushButton *b11;
    QPushButton *b12;
    QPushButton *b13;
    QToolBar *mainToolBar;

    void setupUi(QMainWindow *ImageProcClass)
    {
        if (ImageProcClass->objectName().isEmpty())
            ImageProcClass->setObjectName(QStringLiteral("ImageProcClass"));
        ImageProcClass->resize(675, 326);
        centralWidget = new QWidget(ImageProcClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        verticalLayoutWidget = new QWidget(centralWidget);
        verticalLayoutWidget->setObjectName(QStringLiteral("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(10, 0, 231, 301));
        v1 = new QVBoxLayout(verticalLayoutWidget);
        v1->setSpacing(6);
        v1->setContentsMargins(11, 11, 11, 11);
        v1->setObjectName(QStringLiteral("v1"));
        v1->setContentsMargins(0, 0, 0, 0);
        b1 = new QPushButton(verticalLayoutWidget);
        b1->setObjectName(QStringLiteral("b1"));

        v1->addWidget(b1);

        b2 = new QPushButton(verticalLayoutWidget);
        b2->setObjectName(QStringLiteral("b2"));

        v1->addWidget(b2);

        b3 = new QPushButton(verticalLayoutWidget);
        b3->setObjectName(QStringLiteral("b3"));

        v1->addWidget(b3);

        b4 = new QPushButton(verticalLayoutWidget);
        b4->setObjectName(QStringLiteral("b4"));

        v1->addWidget(b4);

        b5 = new QPushButton(verticalLayoutWidget);
        b5->setObjectName(QStringLiteral("b5"));

        v1->addWidget(b5);

        verticalLayoutWidget_2 = new QWidget(centralWidget);
        verticalLayoutWidget_2->setObjectName(QStringLiteral("verticalLayoutWidget_2"));
        verticalLayoutWidget_2->setGeometry(QRect(240, 0, 211, 301));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget_2);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        b6 = new QPushButton(verticalLayoutWidget_2);
        b6->setObjectName(QStringLiteral("b6"));

        verticalLayout->addWidget(b6);

        b7 = new QPushButton(verticalLayoutWidget_2);
        b7->setObjectName(QStringLiteral("b7"));

        verticalLayout->addWidget(b7);

        b8 = new QPushButton(verticalLayoutWidget_2);
        b8->setObjectName(QStringLiteral("b8"));

        verticalLayout->addWidget(b8);

        b9 = new QPushButton(verticalLayoutWidget_2);
        b9->setObjectName(QStringLiteral("b9"));

        verticalLayout->addWidget(b9);

        verticalLayoutWidget_3 = new QWidget(centralWidget);
        verticalLayoutWidget_3->setObjectName(QStringLiteral("verticalLayoutWidget_3"));
        verticalLayoutWidget_3->setGeometry(QRect(450, 0, 247, 301));
        verticalLayout_2 = new QVBoxLayout(verticalLayoutWidget_3);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        b10 = new QPushButton(verticalLayoutWidget_3);
        b10->setObjectName(QStringLiteral("b10"));

        verticalLayout_2->addWidget(b10);

        b11 = new QPushButton(verticalLayoutWidget_3);
        b11->setObjectName(QStringLiteral("b11"));

        verticalLayout_2->addWidget(b11);

        b12 = new QPushButton(verticalLayoutWidget_3);
        b12->setObjectName(QStringLiteral("b12"));

        verticalLayout_2->addWidget(b12);

        b13 = new QPushButton(verticalLayoutWidget_3);
        b13->setObjectName(QStringLiteral("b13"));

        verticalLayout_2->addWidget(b13);

        ImageProcClass->setCentralWidget(centralWidget);
        mainToolBar = new QToolBar(ImageProcClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        ImageProcClass->addToolBar(Qt::TopToolBarArea, mainToolBar);

        retranslateUi(ImageProcClass);

        QMetaObject::connectSlotsByName(ImageProcClass);
    } // setupUi

    void retranslateUi(QMainWindow *ImageProcClass)
    {
        ImageProcClass->setWindowTitle(QApplication::translate("ImageProcClass", "ImageProc", Q_NULLPTR));
        b1->setText(QApplication::translate("ImageProcClass", "\350\257\273BMP\346\226\207\344\273\266", Q_NULLPTR));
        b2->setText(QApplication::translate("ImageProcClass", "\345\233\276\345\203\217\345\212\240", Q_NULLPTR));
        b3->setText(QApplication::translate("ImageProcClass", "\345\217\226\345\217\215\345\222\214\345\271\263\347\247\273", Q_NULLPTR));
        b4->setText(QApplication::translate("ImageProcClass", "\346\227\213\350\275\254", Q_NULLPTR));
        b5->setText(QApplication::translate("ImageProcClass", "\351\225\234\345\203\217", Q_NULLPTR));
        b6->setText(QApplication::translate("ImageProcClass", "\347\274\251\346\224\276\345\222\214\346\213\211\344\274\270", Q_NULLPTR));
        b7->setText(QApplication::translate("ImageProcClass", "\345\202\205\351\207\214\345\217\266\345\217\230\346\215\242", Q_NULLPTR));
        b8->setText(QApplication::translate("ImageProcClass", "\347\233\264\346\226\271\345\233\276\345\235\207\350\241\241\345\214\226", Q_NULLPTR));
        b9->setText(QApplication::translate("ImageProcClass", "\346\214\207\346\225\260\345\242\236\345\274\272", Q_NULLPTR));
        b10->setText(QApplication::translate("ImageProcClass", "Sobel\347\256\227\345\255\220\345\222\214laplace\351\224\220\345\214\226", Q_NULLPTR));
        b11->setText(QApplication::translate("ImageProcClass", "\345\223\210\345\244\253\346\233\274\347\274\226\347\240\201", Q_NULLPTR));
        b12->setText(QApplication::translate("ImageProcClass", "\345\233\233\347\247\215\347\256\227\345\255\220\347\232\204\350\276\271\347\274\230\346\243\200\346\265\213", Q_NULLPTR));
        b13->setText(QApplication::translate("ImageProcClass", "\351\234\215\345\244\253\345\217\230\346\215\242(\346\257\224\350\276\203\346\205\242)", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class ImageProcClass: public Ui_ImageProcClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_IMAGEPROC_H
