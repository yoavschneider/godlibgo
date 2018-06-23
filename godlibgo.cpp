#include "godlibgo.h"

using namespace dlib;
using namespace std;

void ShapePredictor_Init(char *path)
{
    dlib::deserialize(std::string(path)) >> sp;
}

Points ShapePredictor_Detect(Mat img, Rect rect)
{
    cv_image<unsigned char> cimg(img);

    dlib::rectangle face = rectangle(rect.left, rect.top, rect.right, rect.bottom);

    full_object_detection shape = sp(cimg, face);
    unsigned long length = shape.num_parts();

    Point points[length];

    for (unsigned i = 0; i < length; i++)
    {
        dlib::point cPoint = shape.part(i);
        long x = cPoint.x();
        long y = cPoint.y();

        points[i] = Point{x, y};
    }

    return Points{points, (int)length};
}

Rects FaceDetector_Detect(Mat img)
{
    cv_image<unsigned char> cimg(img);

    std::vector<rectangle> faces = detector(cimg);
    size_t length = faces.size();

    Rect rects[length];

    for (unsigned i = 0; i < length; i++)
    {
        dlib::rectangle rect = faces[i];
        rects[i] = Rect{rect.left(), rect.top(), rect.right(), rect.bottom()};
    }

    return Rects{rects, (int)length};
}
