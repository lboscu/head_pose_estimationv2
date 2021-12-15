#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "qmatopengl.h"
#include<QJsonDocument>
#include<QJsonObject>
#include<QJsonArray>
#include<QFile>
#include<QDateTime>
#include<QDir>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void initKalmanFilter();
    cv::Point3d getKalmanPred(cv::Point3d measure);

private slots:
    void on_actionkaishi_triggered();

    void on_actiontingzhi_triggered();

    void on_actionrizhi_triggered();

    void on_checkBox_stateChanged(int arg1);

private:
    Ui::MainWindow *ui;
    // 存储json数据
    QJsonArray* allAngle = new QJsonArray;
    // 卡尔曼滤波
    cv::KalmanFilter kf;

};
#endif // MAINWINDOW_H
