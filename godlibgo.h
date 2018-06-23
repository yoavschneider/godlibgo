
#ifndef _GODLIBGO_H_
#define _GODLIBGO_H_

#ifdef __cplusplus

#include <dlib/opencv.h>
#include "dlib/opencv/cv_image.h"
#include <dlib/image_processing/frontal_face_detector.h>
#include <dlib/image_processing/render_face_detections.h>
#include <dlib/image_processing.h>
#include <dlib/gui_widgets.h>
#include <dlib/image_io.h>

static dlib::frontal_face_detector detector = dlib::get_frontal_face_detector();
static dlib::shape_predictor sp;

extern "C"
{
#endif
    typedef struct Rect
    {
        long int left;
        long int top;
        long int right;
        long int bottom;
    } Rect;

    typedef struct Point
    {
        long x;
        long y;
    } Point;


#ifdef __cplusplus
    typedef cv::Mat Mat;
#else
    typedef void *Mat;
#endif

    typedef struct Rects
    {
        Rect *rects;
        int length;
    } Rects;

    typedef struct Points
    {
        Point *points;
        int length;
    } Points;

    void ShapePredictor_Init(char *path);
    Points ShapePredictor_Detect(Mat img, Rect rect);
    Rects FaceDetector_Detect(Mat img);

#ifdef __cplusplus
}
#endif
#endif