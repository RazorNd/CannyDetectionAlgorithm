#ifndef CANNYWIDGET_H
#define CANNYWIDGET_H

#include <QWidget>
#include <QGraphicsPixmapItem>
#include <QThread>

namespace Ui {
class CannyWidget;
}

class CannyWidget : public QWidget
{
    Q_OBJECT

public:
    explicit CannyWidget(QWidget *parent = 0);
    ~CannyWidget();

public slots:
    void loadInputImage();
    void saveOutputImage();

protected slots:
    void setOutputImage(QImage image);

signals:
    void inputImageChanged(QImage);

private:
    Ui::CannyWidget *ui;
    QGraphicsPixmapItem *inputItem;
    QGraphicsPixmapItem *outputItem;
    QImage input;
    QThread cannyCalculateThread;
};

#endif // CANNYWIDGET_H
