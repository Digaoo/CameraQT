#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class QCamera;
class QCameraInfo;
class QCameraViewfinder;
class QCameraImageCapture;
class QMediaRecorder;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_camOnPushButton_clicked();

    void on_camOffPushButton_clicked();

    void on_camRecPushButton_clicked();

    void on_camStopRecPushButton_clicked();

    void on_camCapturePushButton_clicked();

    void on_BrightnessHorizontalSlider_valueChanged(int value);

    void on_ContrastHorizontalSlider_valueChanged(int value);

    void on_SaturationHorizontalSlider_valueChanged(int value);

    void on_PausePushButton_clicked();

private:
    Ui::MainWindow *ui;
    QCamera *cam;
    QCameraInfo *camInfo;
    QCameraViewfinder *camViewfinder;
    QCameraImageCapture *camImage;
    QMediaRecorder *camRec;

};

#endif // MAINWINDOW_H
