/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.2.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QTreeWidget *treeWidget_parameters;
    QGroupBox *groupBox_Input;
    QLabel *label_InputName;
    QLineEdit *lineEdit_Input;
    QGroupBox *groupBox_FileStream;
    QPushButton *pushButton_create_File;
    QPushButton *pushButton_load_File;
    QLabel *label_FileName;
    QLineEdit *lineEdit_FileName;
    QGroupBox *groupBox_Plot;
    QLineEdit *lineEdit_maxIterations;
    QLabel *label_maxIterations;
    QPushButton *pushButton_plot;
    QCheckBox *checkBox_range;
    QTableWidget *tableWidget_Fitness;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(658, 367);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        treeWidget_parameters = new QTreeWidget(centralWidget);
        QTreeWidgetItem *__qtreewidgetitem = new QTreeWidgetItem();
        __qtreewidgetitem->setText(0, QStringLiteral("Properties"));
        treeWidget_parameters->setHeaderItem(__qtreewidgetitem);
        treeWidget_parameters->setObjectName(QStringLiteral("treeWidget_parameters"));
        treeWidget_parameters->setEnabled(false);
        treeWidget_parameters->setGeometry(QRect(20, 10, 211, 241));
        groupBox_Input = new QGroupBox(centralWidget);
        groupBox_Input->setObjectName(QStringLiteral("groupBox_Input"));
        groupBox_Input->setEnabled(false);
        groupBox_Input->setGeometry(QRect(450, 10, 191, 81));
        label_InputName = new QLabel(groupBox_Input);
        label_InputName->setObjectName(QStringLiteral("label_InputName"));
        label_InputName->setGeometry(QRect(20, 20, 131, 20));
        lineEdit_Input = new QLineEdit(groupBox_Input);
        lineEdit_Input->setObjectName(QStringLiteral("lineEdit_Input"));
        lineEdit_Input->setGeometry(QRect(50, 40, 91, 20));
        groupBox_FileStream = new QGroupBox(centralWidget);
        groupBox_FileStream->setObjectName(QStringLiteral("groupBox_FileStream"));
        groupBox_FileStream->setGeometry(QRect(240, 10, 191, 81));
        pushButton_create_File = new QPushButton(groupBox_FileStream);
        pushButton_create_File->setObjectName(QStringLiteral("pushButton_create_File"));
        pushButton_create_File->setGeometry(QRect(100, 50, 75, 23));
        pushButton_load_File = new QPushButton(groupBox_FileStream);
        pushButton_load_File->setObjectName(QStringLiteral("pushButton_load_File"));
        pushButton_load_File->setGeometry(QRect(10, 50, 81, 23));
        label_FileName = new QLabel(groupBox_FileStream);
        label_FileName->setObjectName(QStringLiteral("label_FileName"));
        label_FileName->setGeometry(QRect(10, 20, 46, 21));
        lineEdit_FileName = new QLineEdit(groupBox_FileStream);
        lineEdit_FileName->setObjectName(QStringLiteral("lineEdit_FileName"));
        lineEdit_FileName->setGeometry(QRect(60, 20, 121, 20));
        groupBox_Plot = new QGroupBox(centralWidget);
        groupBox_Plot->setObjectName(QStringLiteral("groupBox_Plot"));
        groupBox_Plot->setEnabled(false);
        groupBox_Plot->setGeometry(QRect(30, 260, 191, 80));
        lineEdit_maxIterations = new QLineEdit(groupBox_Plot);
        lineEdit_maxIterations->setObjectName(QStringLiteral("lineEdit_maxIterations"));
        lineEdit_maxIterations->setGeometry(QRect(110, 50, 71, 20));
        label_maxIterations = new QLabel(groupBox_Plot);
        label_maxIterations->setObjectName(QStringLiteral("label_maxIterations"));
        label_maxIterations->setGeometry(QRect(10, 50, 81, 16));
        pushButton_plot = new QPushButton(groupBox_Plot);
        pushButton_plot->setObjectName(QStringLiteral("pushButton_plot"));
        pushButton_plot->setEnabled(false);
        pushButton_plot->setGeometry(QRect(10, 20, 75, 23));
        checkBox_range = new QCheckBox(groupBox_Plot);
        checkBox_range->setObjectName(QStringLiteral("checkBox_range"));
        checkBox_range->setGeometry(QRect(90, 20, 91, 21));
        checkBox_range->setChecked(false);
        checkBox_range->setTristate(false);
        tableWidget_Fitness = new QTableWidget(centralWidget);
        tableWidget_Fitness->setObjectName(QStringLiteral("tableWidget_Fitness"));
        tableWidget_Fitness->setEnabled(true);
        tableWidget_Fitness->setGeometry(QRect(240, 100, 401, 241));
        tableWidget_Fitness->setMouseTracking(false);
        tableWidget_Fitness->setEditTriggers(QAbstractItemView::NoEditTriggers);
        tableWidget_Fitness->setDragEnabled(false);
        tableWidget_Fitness->setAlternatingRowColors(true);
        MainWindow->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);
        QWidget::setTabOrder(pushButton_plot, pushButton_load_File);
        QWidget::setTabOrder(pushButton_load_File, lineEdit_FileName);
        QWidget::setTabOrder(lineEdit_FileName, treeWidget_parameters);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        groupBox_Input->setTitle(QApplication::translate("MainWindow", "Input", 0));
        label_InputName->setText(QApplication::translate("MainWindow", "Input Name:", 0));
        groupBox_FileStream->setTitle(QApplication::translate("MainWindow", "File Stream", 0));
        pushButton_create_File->setText(QApplication::translate("MainWindow", "create File", 0));
        pushButton_load_File->setText(QApplication::translate("MainWindow", "load File", 0));
        label_FileName->setText(QApplication::translate("MainWindow", "Filename:", 0));
        lineEdit_FileName->setText(QApplication::translate("MainWindow", "TSS2", 0));
        groupBox_Plot->setTitle(QApplication::translate("MainWindow", "Plot", 0));
        lineEdit_maxIterations->setText(QApplication::translate("MainWindow", "1000000", 0));
        label_maxIterations->setText(QApplication::translate("MainWindow", "max. Iterations:", 0));
        pushButton_plot->setText(QApplication::translate("MainWindow", "Plot", 0));
        checkBox_range->setText(QApplication::translate("MainWindow", "range Check", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
