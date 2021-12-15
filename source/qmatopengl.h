#ifndef QMATOPENGL_H
#define QMATOPENGL_H

#include <QWidget>
#include <QOpenGLWidget>
#include<QPainter>
#include<QImage>
#include "opencv2/opencv.hpp"
#include<QTimer>
#include "facepointdlib.h"
#include<qdebug.h>

#define PI 3.1415926

class QMatOpenGl : public QOpenGLWidget
{
    Q_OBJECT
public:
    explicit QMatOpenGl(QWidget *parent = nullptr);
    ~QMatOpenGl();
    void paintEvent(QPaintEvent *e); // 重点
    void imgProcess(cv::Mat& img);
    void rvec2Euler(cv::Mat& rvec,double& yaw,double& roll,double& pitch); //revc转成欧拉角
    cv::Mat getFrame(); // 抓取帧
    void drawKeyPoint(bool draw);

private:
    // opengl显示图像
    cv::Mat frame;
    cv::VideoCapture video;
    QTimer* timer1 = new QTimer;
    // dlib检测人脸关键点
    FacePointDlib fpd;
    faceDatas datas;
    // 三维坐标系下的人脸模型相对坐标
    std::vector<cv::Point3d> face3D;
    std::vector<cv::Point2d> face2D;
    cv::Mat camera_matrix; // 相机内参矩阵
    cv::Mat dist_coeffs; // 距离系数，畸变系数
    // 旋转矩阵和平移矩阵
    cv::Mat rvec,tvec;
    // 欧拉角
    double yaw = 0; //左右转动
    double roll = 0; //左右偏头
    double pitch = 0; //上下点头
    // 是否显示关键点
    bool drawKP=true;
signals:
    void getEulerAngle(double yaw,double roll,double pitch);
public slots:
    void grabFrame();
    void startTimer();
    void stopTimer();
};

#endif // QMATOPENGL_H
