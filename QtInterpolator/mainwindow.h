#pragma once
#pragma execution_character_set("utf-8")

#include <QtWidgets/QMainWindow>
#include <QGraphicsView>
#include <QPushButton>
#include <QLineEdit>
#include <QTextEdit>
#include <QLabel>
#include <QComboBox>

#include <vector>

#include "CustomGraphicsView.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

private:
    void configureView();
    std::string prepareFile();
    bool getInitialData();

private slots:
    void updateSetMethod(int index);
    void setSourceFilePath();
    void startInterpolation();

private:
    //QGraphicsView* graphicsView;
    CustomGraphicsView* graphicsView;
    QLabel* interpolationLbl;
    QPushButton* linearBtn;
    QPushButton* squareBtn;
    QPushButton* splineBtn;
    QPushButton* clearBtn;
    QLabel* methodLbl;
    QComboBox* selectMethodComboBox;
    QPushButton* selectFilePathBtn;
    QLineEdit* filePathLineEdt;
    QTextEdit* fileTextEdt;

    std::vector<double> initialData;
    std::vector<double> preparedData;
};
