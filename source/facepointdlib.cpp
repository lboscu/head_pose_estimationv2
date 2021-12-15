#include "facepointdlib.h"

FacePointDlib::FacePointDlib()
{
    dlib::deserialize("./shape_predictor_68_face_landmarks.dat")>>pose_model;  // 反序列化传入标准关键点位置
}

void FacePointDlib::detectFacePoint(cv::Mat& img,faceDatas& datas)
{
     datas.clear(); // 清楚旧数据

    dlib::cv_image<dlib::rgb_pixel> cimg(img);
    std::vector<dlib::rectangle> faces = detector(cimg);
    objects shapes;
    for (unsigned long i = 0; i < faces.size(); ++i)
        shapes.push_back(pose_model(cimg, faces[i]));

    if (!shapes.empty()) {
        for(size_t i=0;i<shapes.size();i++) {
            std::vector<cv::Point2d> points;
            for(int j=0;j<68;j++) {
                points.push_back(cv::Point2d(shapes[i].part(j).x(),shapes[i].part(j).y()));
            }
            datas.push_back(points);
        }
    }
}
