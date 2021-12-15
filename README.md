# 基于图像识别的头部姿态估计

<img  src="https://img.shields.io/badge/build-passing-green.svg"><img  src="https://img.shields.io/badge/version-2.0-blue.svg"><img  src="https://img.shields.io/badge/HEAD-POSE-orange.svg">

​	头部姿态估计可用于基于头部运动的游戏、重要考试监控、与人身安全相关活动等场景中。

## 上手指南

以下指南将帮助你在本地机器上安装和运行该项目，进行开发和测试。

#### 使用方式

1. 免编译方式：在win10环境下，可直接运行package文件夹中的exe程序

2. 编译方式：安装编译环境，在IDE中编译运行。接下来的库和IDE版本等可以作为参考。

#### 安装要求

+ opencv 3.4.1

+ dlib 19.17

+ QT5.9.9，使用Mingw5.3.0 32bit编译

+ win10运行环境

#### 安装步骤

1. 首先你需要

+ 下载安装Qt5。参考

  <a href="https://blog.csdn.net/airt_xiang/article/details/83060225">Qt5.10.1在Windows10下的安装与配置</a>

+ 下载opencv源码，然后使用Qt中的Mingw编译器编译。参考

  <a href="https://blog.csdn.net/zbw1185/article/details/82469496">Qt之CMake和MinGW编译OpenCV </a>

+ 下载<a href="http://dlib.net/files/">dlib</a>，并解压。dlib不需要提前编译成库，使用scoure.cpp和头文件，在Qt中的Mingw可以在项目中编译。

2. 然后

​	在本地克隆该项目

```git clone  https://github.com/lboscu/head_pose_estimationv2.git ```

​	或者下载zip，然后解压。

3. 进入source源码文件夹下。在Qt中“打开文件或项目”，选择source文件夹中的head_estimationv2.pro文件。
4.  修改项目的配置文件head_estimationv2.pro。

``````
#1.修改opencv的头文件和库路径,更换opencv的目录为自己编译的opencv的目录。即是替换下面的 D:\Program Files\opencv3_lib\opencv_mingw32_with_contrib
################################################################################################################
#opencv配置

INCLUDEPATH += "D:\Program Files\opencv3_lib\opencv_mingw32_with_contrib\include"

LIBS += "D:/Program Files/opencv3_lib/opencv_mingw32_with_contrib/x86/mingw/bin/libopencv_aruco341.dll"
LIBS += "D:/Program Files/opencv3_lib/opencv_mingw32_with_contrib/x86/mingw/bin/libopencv_bgsegm341.dll"
# ...下面的都替换
######################################################################################################################

#2.修改dlib的头文件和源码路径，即是替换下面的 D:\Program Files\opencv_Dlib\dlib_uncmake\dlib-19.17 
######################################################################################################################
#dlib配置
SOURCES += "D:\Program Files\opencv_Dlib\dlib_uncmake\dlib-19.17\dlib\all\source.cpp"
LIBS += -lwsock32  -lws2_32 -limm32  -luser32 -lgdi32 -lcomctl32 -lwinmm

INCLUDEPATH += "D:\Program Files\opencv_Dlib\dlib_uncmake\dlib-19.17"
``````

5. 这时环境搭建完成，Qt中可以选择Mingw的编译环境release运行本项目。

> note: 该项目在Qt中只能release运行，debug会崩溃。

## 测试

​	界面中包含的控件及功能如下

 ├── 工具
 |   ├── 启动：从摄像头的视频流中捕获帧，显示捕获图像
 |   ├── 停止：停止捕获，图像静止
 |   └── 日志：触发会打开日志文件，json格式数据，记录了不超过1000条数据。当"停止"被触发时，会写入数据到allAngel.log文件中。

 ├── 启动

 ├── 停止

 ├── 截图：将当前画面中的图像保存到images/文件夹下。

 ├── 关键点：是否显示检测到的关键点。

<img src="https://github.com/lboscu/head_pose_estimationv2/blob/main/%E5%B1%8F%E5%B9%95%E6%88%AA%E5%9B%BE.png">

## 存在问题

​	使用卡尔曼滤波后数据跳跃稳定了一些，但仍存在跳动，需要使用合适的转移矩阵，建模观测量。需要根据相机的位置和具体使用功能，对头部姿态角度进行校准。存在一些参数的假设，需要根据实际情况修改参数。

## 相关技术

1. 人脸识别和人脸关键点检测
2. PNP(Perspective N Point)问题求解，solvePNPRansac方法
3. Kalman Filter

## 参考文献

One Millisecond Face Alignment with an Ensemble of Regression Trees

A new approach to linear filtering and prediction problems
