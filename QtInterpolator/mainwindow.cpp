#include "mainwindow.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFileDialog>
#include <QTextStream>
#include <iostream>
#include "FileReader.h"
#include <QMessageBox>
#include "Interpolator.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    //Initializing widgets
    graphicsView = new CustomGraphicsView(this);
    interpolationLbl = new QLabel("Интерполяция:", this);
    linearBtn = new QPushButton("Линейная", this);
    squareBtn = new QPushButton("Квадратичная", this);
    splineBtn = new QPushButton("Кубическим сплайном", this);
    clearBtn = new QPushButton("Очистить поле", this);
    methodLbl = new QLabel("Значения из:", this);
    selectMethodComboBox = new QComboBox(this);
    selectFilePathBtn = new QPushButton("Выбрать файл", this);
    filePathLineEdt = new QLineEdit(this);
    fileTextEdt = new QTextEdit(this);

    configureView();

    //Connections
    connect(selectMethodComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &MainWindow::updateSetMethod);
    connect(selectFilePathBtn, &QPushButton::clicked, this, &MainWindow::setSourceFilePath);
    
    connect(linearBtn, &QPushButton::clicked, this, &MainWindow::startInterpolation);
    connect(squareBtn, &QPushButton::clicked, this, &MainWindow::startInterpolation);
    connect(splineBtn, &QPushButton::clicked, this, &MainWindow::startInterpolation);
    connect(clearBtn, &QPushButton::clicked, graphicsView, &CustomGraphicsView::clearScene);
}

void MainWindow::configureView() {

    //Interpolation buttons
    QVBoxLayout* vboxButtons = new QVBoxLayout();

    vboxButtons->addStretch();
    interpolationLbl->setAlignment(Qt::AlignHCenter);
    vboxButtons->addWidget(interpolationLbl);

    linearBtn->setObjectName("Linear");
    vboxButtons->addWidget(linearBtn);
    squareBtn->setObjectName("Square");
    vboxButtons->addWidget(squareBtn);
    splineBtn->setObjectName("Spline");
    vboxButtons->addWidget(splineBtn);

    QFont clearBtnFont = clearBtn->font();
    clearBtnFont.setBold(true);
    clearBtn->setFont(clearBtnFont);
    vboxButtons->addWidget(clearBtn);
    vboxButtons->addStretch();

    //GraphicsView
    QHBoxLayout* hboxTop = new QHBoxLayout();
    hboxTop->addWidget(graphicsView);
    hboxTop->addLayout(vboxButtons);

    //Setting method
    QHBoxLayout* hboxMethod = new QHBoxLayout();
    hboxMethod->addWidget(methodLbl);

    selectMethodComboBox->addItem("Файл");
    selectMethodComboBox->addItem("Текстовое поле");
    hboxMethod->addWidget(selectMethodComboBox);
    hboxMethod->addStretch();

    //File selection
    QHBoxLayout* hboxFile = new QHBoxLayout();

    filePathLineEdt->setPlaceholderText("Путь к файлу...");
    hboxFile->addWidget(filePathLineEdt);
    hboxFile->addWidget(selectFilePathBtn);

    //Text editing
    fileTextEdt->setSizePolicy(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Fixed);
    fileTextEdt->setPlaceholderText("Введите значения через пробел...");
    fileTextEdt->setEnabled(false);

    //Final configuration
    QVBoxLayout* finalLayout = new QVBoxLayout();
    finalLayout->addLayout(hboxTop);
    finalLayout->addLayout(hboxMethod);
    finalLayout->addLayout(hboxFile);
    finalLayout->addWidget(fileTextEdt);

    QWidget* window = new QWidget(this);
    window->setLayout(finalLayout);
    setCentralWidget(window);
}

void MainWindow::updateSetMethod(int index) {
    switch (index) {
    case 0:
        fileTextEdt->setEnabled(false);
        selectFilePathBtn->setEnabled(true);
        filePathLineEdt->setEnabled(true);
        break;
    case 1:
        fileTextEdt->setEnabled(true);
        selectFilePathBtn->setEnabled(false);
        filePathLineEdt->setEnabled(false);
        break;
    default:
        qDebug("Unknown case from QComboBox");
    }
}

void MainWindow::setSourceFilePath() {
    QString filePath = QFileDialog::getOpenFileName(this, "Выберите файл");
    filePathLineEdt->setText(filePath);
}

std::string MainWindow::prepareFile() {
    std::string filePath = "input_from_textedit.txt";
    QFile file(&filePath[0]);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        file.close();
        throw std::runtime_error("Failed to create file.");
    }
    else {
        QTextStream out(&file);
        out << fileTextEdt->toPlainText();
        file.close();
        return filePath;
    }
}

bool MainWindow::getInitialData() {
    std::string filePath = "";
    switch (selectMethodComboBox->currentIndex()) {
    case 0:
        filePath = filePathLineEdt->text().toLocal8Bit().constData();
        break;
    case 1:
        filePath = prepareFile();
        break;
    }
    FileReader fileReader(filePath);
    try {
        initialData = fileReader.getData();
        return true;
    }
    catch (std::exception& ex) {
        QMessageBox::critical(this, "Interpolator", QString(ex.what()));
        return false;
    }
}

void MainWindow::startInterpolation() {
    if (getInitialData()) {
        Interpolator interpolator(initialData, 20);
        QString senderName = sender()->objectName();
        if (senderName == "Linear") {
            preparedData = interpolator.interpolate(InterpolationType::LINEAR);
        }
        else if (senderName == "Square") {
            preparedData = interpolator.interpolate(InterpolationType::SQUARE);
        }
        else if (senderName == "Spline") {
            QMessageBox::information(this, "Interpolator", "Данный функционал пока недоступен");
            //preparedData = interpolator.interpolate(InterpolationType::SPLINE);
        }
        else {
            QMessageBox::critical(this, "Interpolator", "Unknown command.");
            return;
        }
        graphicsView->setData(preparedData);
        graphicsView->startPainting();
    }
}


