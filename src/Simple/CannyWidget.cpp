#include "CannyWidget.h"
#include "ui_CannyWidget.h"
#include "CannyDetectionAlgorithm.h"
#include <QSize>
#include <QImage>
#include <QFileDialog>



CannyWidget::CannyWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CannyWidget)
{
    ui->setupUi(this);
    QGraphicsScene *inputScene = new QGraphicsScene(this);
    QGraphicsScene *outputScene = new QGraphicsScene(this);

    CannyDetectionAlgorithm *algorithm = new CannyDetectionAlgorithm();

    algorithm->moveToThread(&cannyCalculateThread);

    connect(this, &CannyWidget::inputImageChanged, algorithm, &CannyDetectionAlgorithm::setInputImage);
    connect(ui->tMin, SIGNAL(valueChanged(int)), algorithm, SLOT(setTMin(int)));
    connect(ui->tMax, SIGNAL(valueChanged(int)), algorithm, SLOT(setTMax(int)));
    connect(ui->sigma, SIGNAL(valueChanged(double)), algorithm, SLOT(setSigma(double)));
    connect(algorithm, &CannyDetectionAlgorithm::outputImageChanged, this, &CannyWidget::setOutputImage);

    ui->input->setScene(inputScene);
    ui->output->setScene(outputScene);

    inputItem = inputScene->addPixmap(QPixmap());
    outputItem = outputScene->addPixmap(QPixmap());

    cannyCalculateThread.start();
}

CannyWidget::~CannyWidget()
{
    delete ui;
    cannyCalculateThread.quit();
    cannyCalculateThread.wait();
}

void CannyWidget::loadInputImage()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Входное изображение", QString(), "Изображения (*.png *.bmp *.jpg)");
    if (fileName.isEmpty())
    {
        return;
    }
    input.load(fileName);
    if (!input.isNull())
    {
        inputItem->setPixmap(QPixmap::fromImage(input));
        emit inputImageChanged(input);
    }
}

void CannyWidget::saveOutputImage()
{
    QString fileName = QFileDialog::getSaveFileName(this, "Файл для сохранения", QString(), "Изображения (*.png *.bmp *.jpg)");
    if (fileName.isEmpty())
    {
        return;
    }
    outputItem->pixmap().save(fileName, 0, 100);
}


void CannyWidget::setOutputImage(QImage image)
{
    outputItem->setPixmap(QPixmap::fromImage(image));
}
