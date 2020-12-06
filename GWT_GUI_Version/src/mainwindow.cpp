#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <iostream>
#include <QGraphicsPixmapItem>
#include <QPicture>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QPixmap pix("test-pattern-tv.jpg");
    ui->label->setPixmap(pix);
}

void MainWindow::update() {
    if (ui->input_german->text() == "hallo") {
        std::cout << "fine" << std::endl;
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

