#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QCamera>
#include <QCameraInfo>
#include <QCameraViewfinder>
#include <QCameraImageCapture>
#include <QMediaRecorder>
#include <QFileDialog>
#include <QDebug>

bool checkCameraAvailability(){

    if (QCameraInfo::availableCameras().count() > 0)
        return true;
    else
        return false;

}

void listCameras () {

    QList<QCameraInfo> cameras = QCameraInfo::availableCameras();

    foreach (const QCameraInfo &cameraInfo, cameras) {

        qDebug() << cameraInfo.deviceName();

    }

}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    checkCameraAvailability();
    listCameras();
    cam = new QCamera(QCamera::FrontFace);
    camViewfinder = new QCameraViewfinder;
    camImage = new QCameraImageCapture(cam,this);
    camRec = new QMediaRecorder(cam,this);
    cam->setViewfinder(camViewfinder);

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_camOnPushButton_clicked(){
    cam->start();
}

void MainWindow::on_camOffPushButton_clicked(){
    cam->stop();
}

void MainWindow::on_camRecPushButton_clicked(){
    auto filename = QFileDialog::getSaveFileName(this,"Escolha onde deseja salvar a foto","/","Imagem (*.jpg;*.jpeg)");
    if (filename.isEmpty()) return;
    camRec->setContainerFormat();
    QImageEncoderSettings imgEncSet;
    imgEncSet.setCodec("image/jpeg");
    imgEncSet.setResolution(1600,1200);
    camImage->setEncodingSettings(imgEncSet);
    cam->setCaptureMode(QCamera::CaptureStillImage);
    cam->start();
    cam->searchAndLock();
    camImage->capture(filename);
    cam->unlock();
}

void MainWindow::on_PausePushButton_clicked()
{

}

void MainWindow::on_camStopRecPushButton_clicked(){

}

void MainWindow::on_camCapturePushButton_clicked(){
    auto filename = QFileDialog::getSaveFileName(this,"Escolha onde deseja salvar a foto","/","Imagem (*.jpg;*.jpeg)");
    if (filename.isEmpty()) return;
    camImage->setCaptureDestination(QCameraImageCapture::CaptureToFile);
    QImageEncoderSettings imgEncSet;
    imgEncSet.setCodec("image/jpeg");
    imgEncSet.setResolution(1600,1200);
    camImage->setEncodingSettings(imgEncSet);
    cam->setCaptureMode(QCamera::CaptureStillImage);
    cam->start();
    cam->searchAndLock();
    camImage->capture(filename);
    cam->unlock();
}

void MainWindow::on_BrightnessHorizontalSlider_valueChanged(int value){
    ui->BrightnessValLabel->setText(QString::number(value));
}

void MainWindow::on_ContrastHorizontalSlider_valueChanged(int value){
    ui->ContrastValLabel->setText(QString::number(value));
}

void MainWindow::on_SaturationHorizontalSlider_valueChanged(int value){
    ui->SaturationValLabel->setText(QString::number(value));
}
