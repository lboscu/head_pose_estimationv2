#ifndef FACEPOINTDLIB_H
#define FACEPOINTDLIB_H

#include "dlib/opencv.h"
#include "dlib/image_processing/frontal_face_detector.h"
#include "dlib/image_processing/render_face_detections.h"
#include "dlib/image_processing.h"
#include "opencv2/opencv.hpp"

typedef std::vector<dlib::full_object_detection> objects;
typedef dlib::frontal_face_detector faceDetector;
typedef std::vector<std::vector<cv::Point2d>> faceDatas;

class FacePointDlib
{
public:
    FacePointDlib();
    void detectFacePoint(cv::Mat& img,faceDatas& datas);

    faceDetector detector = dlib::get_frontal_face_detector(); // 人脸检测器
    dlib::shape_predictor pose_model; // 人脸模型关键点估计
};

#endif // FACEPOINTDLIB_H
