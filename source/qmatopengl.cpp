#include "qmatopengl.h"

QMatOpenGl::QMatOpenGl(QWidget *parent) : QOpenGLWidget(parent)
{
    video.open(0);

//    timer1->start(50); // 每秒20帧，就是50ms一帧
    connect(timer1,&QTimer::timeout,this,&QMatOpenGl::grabFrame); // 定时器，定时获取图像

    // 3D 人脸相对坐标
    face3D.push_back(cv::Point3d(0.0,0.0,0.0)); // noise tip
    face3D.push_back(cv::Point3d(0.0,-330.0,-65.0)); // chin
    face3D.push_back(cv::Point3d(-225.0,170.0,-135.0)); // left eye left corner
    face3D.push_back(cv::Point3d(225.0,170.0,-135.0)); // right eye right corner
    face3D.push_back(cv::Point3d(-150.0,-150.0,-125.0)); // left mouth corner
    face3D.push_back(cv::Point3d(150.0,-150.0,-125.0)); // right mouth corner
    // 相机初始化
    cv::Point2d center(380.0/2,320.0/2);
    size_t focal_length = center.x / std::tan(60/2*PI/180);
    camera_matrix = (cv::Mat_<double>(3,3)<<focal_length,0,center.x,0,focal_length,center.y,
                     0,0,1); // 假设的一个矩阵
    dist_coeffs = cv::Mat_<double>::zeros(4,1); // 畸变系数，假设为0
    // 36,45,30,48,54,8
}

QMatOpenGl::~QMatOpenGl()
{
    delete timer1;
    video.release();
}

void QMatOpenGl::paintEvent(QPaintEvent *e)
{
    if(!frame.empty()) {
//        cv::cvtColor(frame, frame, cv::COLOR_BGR2RGB);
        QImage img(frame.data, frame.cols, frame.rows, QImage::Format_RGB888);

        QPainter painter;
        painter.begin(this);
        painter.drawImage(QPoint(0,0),img);
    }
}

void QMatOpenGl::grabFrame()
{
    this->video>>frame;
    if(!frame.empty()) {
    }
        this->imgProcess(frame); // 处理图像
        this->update(); // 更新，会调用paintEvent事件
}

void QMatOpenGl::imgProcess(cv::Mat& img)
{
    cv::cvtColor(img, img, cv::COLOR_BGR2RGB); // 调整顺序
//    qDebug()<<img.rows<<","<<img.cols; // 480,640
    cv::resize(img,img,cv::Size(380,320));
    cv::flip(img,img,1); // 左右翻转，相当于镜像
    // 1.检测人脸的68个关键点
    fpd.detectFacePoint(img,datas);
    if(!datas.empty()) {
//        qDebug()<<datas[0][1].x<<","<<datas[0][1].y;
        face2D.clear();
        face2D.push_back(datas[0][30]); // noise tip
        face2D.push_back(datas[0][8]); //chin
        face2D.push_back(datas[0][36]); //left eye left corner
        face2D.push_back(datas[0][45]); //right eye right corner
        face2D.push_back(datas[0][48]);// left mouth corner
        face2D.push_back(datas[0][54]);// right mouth corner

        if(drawKP) { // 绘制关键点
            for(int i=0;i<6;i++) {
                cv::circle(frame,face2D[i],3,cv::Scalar(0,0,255),cv::FILLED);
            }
        }
    }

    // 2. SolvePnPRANSAC方法估计姿态
    if(!face3D.empty() && !face2D.empty()) {
        cv::solvePnPRansac(face3D,face2D,camera_matrix,dist_coeffs,rvec,tvec,false,200,2);
        rvec2Euler(rvec,yaw,roll,pitch); //旋转向量转为欧拉角
        // 根据摄像头,实验校准
//        yaw -= 35;
//        roll -= -5;
//        pitch -= 165;
//        qDebug()<<yaw<<","<<roll<<","<<pitch;
    }
    // 3.发送信号
    emit getEulerAngle(yaw,roll,pitch);
}

void QMatOpenGl::startTimer()
{
    this->timer1->start(50);
}

void QMatOpenGl::stopTimer()
{
    this->timer1->stop();
}

void QMatOpenGl::rvec2Euler(cv::Mat& rvec,double& yaw,double& roll,double& pitch)
{
    // 转为4元数，即是旋量
    double theta = cv::norm(rvec);
    double w = std::cos(theta/2);
    double x = std::sin(theta / 2) * rvec.at<double>(0) / theta;
    double y = std::sin(theta / 2) * rvec.at<double>(1) / theta;
    double z = std::sin(theta / 2) * rvec.at<double>(2) / theta;
    // 转为欧拉角
    double ysqr = y * y;
    double xsqr = x * x;
    double zsqr = z * z;

    double t0 = 2.0 * (w * x + y * z);
    double t1 = 1.0 - 2.0 * (xsqr + ysqr);
    pitch = std::atan2(t0, t1);
    pitch = pitch * 180 / PI;

    double t2 = 2.0 * (w * y - z * x);
    t2 = t2 > 1.0 ? 1.0 : t2;
    t2 = t2 < -1.0 ? -1.0 : t2;
    yaw = std::asin(t2);
    yaw = yaw * 180 / PI;

    double t3 = 2.0 * (w * z + x * y);
    double t4 = 1.0 - 2.0 * (ysqr + zsqr);
    roll = std::atan2(t3, t4);
    roll = roll * 180 / PI;
    if(roll > 90)
        roll = std::fmod(roll - 180,180.0);
    if(roll < -90)
        roll = std::fmod(roll + 180, 180.0);
}

cv::Mat QMatOpenGl::getFrame()
{
    return cv::Mat(this->frame);
}

void QMatOpenGl::drawKeyPoint(bool draw) //绘制关键点
{
    this->drawKP = draw;
}
