#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "opencv2/opencv.hpp"
#include<iostream>
#include<string>
using namespace std;


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QString button = "QPushButton {\
            border-radius:11;\
            border:2px solid #333;\
            color:#333;\
        }\
        QPushButton:pressed{\
            border-radius:11;\
            border:3px solid #222;\
            color:#222;\
        }";
    ui->pushButton->setStyleSheet(button);
    ui->pushButton_2->setStyleSheet(button);
    ui->pushButton_3->setStyleSheet(button);

    // 初始化卡尔曼滤波器
    this->initKalmanFilter();

    connect(ui->pushButton,&QPushButton::clicked,ui->openGLWidget,&QMatOpenGl::startTimer); // 连接启动按钮和定时器启动
    connect(ui->pushButton_2,&QPushButton::clicked,this,[=](){
        ui->openGLWidget->stopTimer();
        // 写入文件

        QFile file("allAngle.log");
        if(file.open(QIODevice::WriteOnly | QIODevice::ReadWrite)) {
            QJsonDocument jdc =  QJsonDocument::fromJson(file.readAll());
            QJsonArray jarray = jdc.array();
            if((allAngle->size() + jarray.size())>1000) {  // 保持文件中不超过1000条记录
                int num = allAngle->size() + jarray.size() - 1000;
                for(int i=0;i<num;i++) {
                    jarray.removeFirst();
                }
            }
            jarray = jarray + *allAngle;
            QJsonDocument jsonDoc(jarray);
            QByteArray ba = jsonDoc.toJson();
            file.write(ba); //写入
            file.close();
        }
    }); //连接停止按钮和定时器停止
    connect(ui->openGLWidget,&QMatOpenGl::getEulerAngle,this,[=](double yaw,double roll,double pitch){
        cv::Point3d measure(yaw,roll,pitch);
        cv::Point3d pred = this->getKalmanPred(measure);
        yaw = pred.x;
        roll = pred.y;
        pitch = pred.z;

        ui->label->setText("向右偏：" + QString::number(std::round(roll)) + "°");
        ui->label_2->setText("向左转：" + QString::number(std::round(yaw)) + "°");
        ui->label_3->setText("向上仰：" + QString::number(std::round(pitch)) + "°");

        //数据存储
        QJsonObject obj;
        obj.insert("roll",roll);
        obj.insert("yaw",yaw);
        obj.insert("pitch",pitch);
        obj.insert("dateTime",QDateTime::currentDateTime().toString("yyyy.MM.dd hh:mm:ss"));
        allAngle->push_back(obj);
        if(allAngle->size()>1000) { // 如果数据大于1000条，就清空数组,保持为1000条
            long size = allAngle->size();
            for(int i=0;i < size-1000;i++) {
                allAngle->removeFirst();
            }
        }
    });
    connect(ui->pushButton_3,&QPushButton::clicked,this,[=](){
        cv::Mat img = ui->openGLWidget->getFrame();
        // 截图保存图像
        if(!img.empty()) {
            QDir dir("./images/");  //imwrite需要路径文件夹存在，才能保存
            if(!dir.exists()) {
                system("mkdir images");
            }
            std::string filename = "./images/"+QDateTime::currentDateTime().toString("yyyy-MM-dd-hh-mm-ss").toStdString() +".jpg";
            cv::imwrite(filename,img);
        }
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionkaishi_triggered()
{
    ui->openGLWidget->startTimer(); // 启动定时器
}

void MainWindow::on_actiontingzhi_triggered()
{
    ui->openGLWidget->stopTimer(); //停止定时器
}

void MainWindow::on_actionrizhi_triggered()
{
    // 日志
    system("start /b notepad ./allAngle.log");
}

void MainWindow::initKalmanFilter()
{
    kf.init(6,3,0); // 3个观测值，变化量包括速度
    cv::Mat state (6, 1, CV_32FC1);         //  state(x,y,detaX,detaY)
    cv::Mat processNoise(6, 1, CV_32F); //  processNoise(x,y,detaX,detaY)
    cv::Mat measurement = cv::Mat::zeros(3, 1, CV_32F); //measurement(x,y)
    kf.transitionMatrix = (cv::Mat_<float>(6, 6) <<
                            1,0,0,1,0,0,
                            0,1,0,0,1,0,
                            0,0,1,0,0,1,
                            0,0,0,1,0,0,
                            0,0,0,0,1,0,
                            0,0,0,0,0,1);//元素导入矩阵，按行;
    setIdentity(kf.measurementMatrix);
    setIdentity(kf.processNoiseCov, cv::Scalar::all(1e-5));
    setIdentity(kf.measurementNoiseCov, cv::Scalar::all(1e-1));
    setIdentity(kf.errorCovPost, cv::Scalar::all(1));

    //
//    cv::Point3d statePt = cv::Point3d( (int)kf.statePost.at<float>(0), (int)kf.statePost.at<float>(1),(int)kf.statePost.at<float>(2));
}

// 传入观测数据，返回卡尔曼滤波器的估计值
cv::Point3d MainWindow::getKalmanPred(cv::Point3d measure)
{
    //2.kalman prediction
    cv::Mat prediction = kf.predict();
    cv::Point3d predictPt = cv::Point3d((int)prediction.at<float>(0), (int)prediction.at<float>(1),(int)prediction.at<float>(2));
//    //3.update measurement
    cv::Mat measurement = cv::Mat::zeros(3, 1, CV_32F);
    measurement.at<float>(0)= (float)measure.x;
    measurement.at<float>(1) = (float)measure.y;
    measurement.at<float>(2) = (float)measure.z;
    this->kf.correct(measurement);
    return predictPt;
}

void MainWindow::on_checkBox_stateChanged(int arg1)
{
    if(arg1 == 2) { // checkBox有0,1,2三种状态
        ui->openGLWidget->drawKeyPoint(true); //
    }
    else {
        ui->openGLWidget->drawKeyPoint(false);
    }
}
