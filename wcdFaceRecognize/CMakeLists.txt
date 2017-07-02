set(LIB_SRC wcdFaceRecognize.h wcdFaceRecognize.cpp)
add_library(wcdFaceRecognize ${LIB_SRC})
TARGET_LINK_LIBRARIES( wcdFaceRecognize 
	libfacedetect
	${OpenCV_LIBS}
)
