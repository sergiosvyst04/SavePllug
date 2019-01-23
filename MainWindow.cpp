#include "MainWindow.hpp"
#include "ui_MainWindow.h"
#include <QMessageBox>
#include <QDebug>
#include <QTextStream>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->readfile, &QPushButton::clicked, this, &MainWindow::onReadButtonPressed);
}

void MainWindow::onReadButtonPressed()
{

    auto filePath = ui->lineEdit->text();
    QFile file;
    file.setFileName(filePath);
    if(filePath.isEmpty())
    {
        QMessageBox::information(this, "ERROR", "File wasn't opened!!!\nWrite file path om line edit");
        return;
    }
    else{
        file.open(QFile::ReadOnly);
        if(file.isOpen())
        {
            QTextStream in(&file);
            while(!in.atEnd())
            {
                qDebug() << in.readLine();
            }
        }
        else if (!file.isOpen())
        {
            qFatal("Error during the opening file");
        }

        if(!QFile::exists(filePath))
        {
            qFatal("File not exists", qPrintable(filePath));
        }
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}
