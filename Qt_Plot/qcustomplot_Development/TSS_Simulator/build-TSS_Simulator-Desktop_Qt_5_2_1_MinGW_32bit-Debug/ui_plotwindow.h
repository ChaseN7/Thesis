/********************************************************************************
** Form generated from reading UI file 'plotwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.2.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PLOTWINDOW_H
#define UI_PLOTWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>
#include <qcustomplot.h>

QT_BEGIN_NAMESPACE

class Ui_PlotWindow
{
public:
    QHBoxLayout *horizontalLayout;
    QCustomPlot *customPlot;
    QPushButton *pushButton_saveImage;
    QLineEdit *lineEdit_ImageName;
    QLabel *label_iterations;

    void setupUi(QWidget *PlotWindow)
    {
        if (PlotWindow->objectName().isEmpty())
            PlotWindow->setObjectName(QStringLiteral("PlotWindow"));
        PlotWindow->resize(713, 396);
        horizontalLayout = new QHBoxLayout(PlotWindow);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        customPlot = new QCustomPlot(PlotWindow);
        customPlot->setObjectName(QStringLiteral("customPlot"));
        pushButton_saveImage = new QPushButton(customPlot);
        pushButton_saveImage->setObjectName(QStringLiteral("pushButton_saveImage"));
        pushButton_saveImage->setGeometry(QRect(170, 30, 71, 23));
        lineEdit_ImageName = new QLineEdit(customPlot);
        lineEdit_ImageName->setObjectName(QStringLiteral("lineEdit_ImageName"));
        lineEdit_ImageName->setGeometry(QRect(170, 10, 113, 21));
        label_iterations = new QLabel(customPlot);
        label_iterations->setObjectName(QStringLiteral("label_iterations"));
        label_iterations->setGeometry(QRect(290, 10, 111, 21));

        horizontalLayout->addWidget(customPlot);


        retranslateUi(PlotWindow);

        QMetaObject::connectSlotsByName(PlotWindow);
    } // setupUi

    void retranslateUi(QWidget *PlotWindow)
    {
        PlotWindow->setWindowTitle(QApplication::translate("PlotWindow", "Form", 0));
        pushButton_saveImage->setText(QApplication::translate("PlotWindow", "save Image", 0));
        lineEdit_ImageName->setText(QApplication::translate("PlotWindow", "Image Name", 0));
        label_iterations->setText(QApplication::translate("PlotWindow", "Iterations made", 0));
    } // retranslateUi

};

namespace Ui {
    class PlotWindow: public Ui_PlotWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PLOTWINDOW_H
