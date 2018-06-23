#ifndef DLIB_GrayscaleImageTmp_H_
#define DLIB_GrayscaleImageTmp_H_

#include <dlib/pixel.h>
#include <dlib/image_processing/generic_image.h>

namespace dlib
{

template <>
struct image_traits<GrayscaleImageTmp>
{
    typedef uint8_t pixel_type;
};

class GrayscaleImageTmp
{
  public:
    long nr;
    long nc;

    void *img;
    const void *c_img;

    long ws;

    GrayscaleImageTmp() = default;

    GrayscaleImageTmp(long nr_, long nc_, void *img_, const void *c_img_, long ws_)
    {
        nr = nr_;
        nc = nc_;
        img = img_;
        c_img = c_img_;
        ws = ws_;
    }

    long num_rows(const GrayscaleImageTmp &img)
    {
        return img.nr;
    }

    long num_columns(const GrayscaleImageTmp &img)
    {
        return img.nc;
    }

    void set_image_size(GrayscaleImageTmp &img, long rows, long cols)
    {
        img.nr = rows;
        img.nc = cols;
    }

    void *image_data(GrayscaleImageTmp &img)
    {
        return img.img;
    }

    const void *image_data(const GrayscaleImageTmp &img)
    {
        return img.c_img;
    }

    long width_step(const GrayscaleImageTmp &img)
    {
        return img.ws;
    }

    void swap(GrayscaleImageTmp &a, GrayscaleImageTmp &b)
    {
        long nr = a.nr;
        long nc = a.nc;
        void *img = a.img;
        const void *c_img = a.c_img;
        long ws = a.ws;

        a.nr = b.nr;
        a.nc = b.nc;
        a.img = b.img;
        a.c_img = b.c_img;
        a.ws = b.ws;

        b.nr = nr;
        b.nc = nc;
        b.img = img;
        b.c_img = c_img;
        b.ws = ws;
    }
};

} // namespace dlib

#endif