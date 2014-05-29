#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtCore>
#include <QtGui>
#include "plotwindow.h"
#include "ui_mainwindow.h"
#include <QTextStream>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    void readFileContent(QString Filename);
    void addRootItem(QString value);
    void addChildItem(QTreeWidgetItem* parent, QString value);
    ~MainWindow();

    void addTreePopulationProperties();
    void addTreeTraitProperties(TraitEventManager Parameters);
    void setFileInput(/*QString Filename, */TraitEventManager Parameters, bool isFound);
    void iterateInputParameter();
    bool iterateTraitProperties(QString StepName, int size);
    void iterateMembers(QString StepName, int size);
    void iterateBirths(QString StepName, int size);
    void iterateDeaths(QString StepName, int size);
private slots:
    void on_pushButton_plot_clicked();

    void on_pushButton_load_File_clicked();

    void on_pushButton_create_File_clicked();

    void on_lineEdit_Input_returnPressed();

    void enablePlotButton();

private:
    Ui::MainWindow *ui;
//    std::vector<PlotWindow> Plot;
    PlotWindow * Plot;
};

#endif // MAINWINDOW_H
