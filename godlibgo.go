package godlibgo

// #cgo pkg-config: opencv
// #cgo CXXFLAGS: -std=c++11 -O3 -I/dlib/ -I/dlib/all/ -DUSE_AVX_INSTRUCTIONS=ON
// #include <godlibgo.h>
// #include <stdlib.h>
import "C"

import (
	"gocv.io/x/gocv"
	"image"
	"unsafe"
)

type Mat struct {
	p C.Mat
}

func InitShapePredictor(path string) {
	cstr := C.CString(path)
	C.ShapePredictor_Init(cstr)
	defer C.free(unsafe.Pointer(cstr))
}

func DetectFaceFeatures(img gocv.Mat, rect image.Rectangle) []image.Point {
	m := Mat{p: _Ctype_Mat(img.Ptr())}

	cRect := _Ctype_struct_Rect{_Ctype_long(rect.Min.X), _Ctype_long(rect.Min.Y), _Ctype_long(rect.Max.X), _Ctype_long(rect.Max.Y)}

	cPoints := C.ShapePredictor_Detect(m.p, cRect)
	length := cPoints.length
	cArray := cPoints.points

	original := (*[1 << 30]C.Point)(unsafe.Pointer(cArray))[:length:length]
	result := make([]image.Point, length)

	for i, cPoint := range original {
		result[i] = image.Point{int(cPoint.x), int(cPoint.y)}
	}

	return result
}

func DetectFaces(img gocv.Mat) []image.Rectangle {
	m := Mat{p: _Ctype_Mat(img.Ptr())}

	cRects := C.FaceDetector_Detect(m.p)
	length := cRects.length
	cArray := cRects.rects

	original := (*[1 << 30]C.Rect)(unsafe.Pointer(cArray))[:length:length]
	result := make([]image.Rectangle, length)

	for i, cRect := range original {
		result[i] = image.Rect(int(cRect.left), int(cRect.top), int(cRect.right), int(cRect.bottom))
	}

	return result
}
