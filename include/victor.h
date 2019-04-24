//头文件

#ifndef VICTOR_H_
#define VICTOR_H_

#include <iostream>
#include <string>

#include <cv.h>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <highgui.h>

#include <time.h> //

#include <unistd.h>
#include <thread>//线程库
#include <mutex> //互斥保护,c++11标准

#include <dlib/image_processing/frontal_face_detector.h>
#include <dlib/image_processing/render_face_detections.h>
#include <dlib/data_io.h>
#include <dlib/image_io.h>
#include <dlib/image_processing.h>
#include <dlib/gui_widgets.h>
#include <dlib/image_io.h>
#include <dlib/opencv.h>
#include <vector>
#include <cmath>
#include <queue>
#include <list>
#include "people.hpp"


class victor
{
   private:
	//bool flag;
	bool faceflag;
		
	

	time_t start, end;  //计时
   public:
	int read();
	void show();
	int face_d();//
	void detect();
	void eyedetect();
	int readsenior();
	void point_extract();
	
	
	
};

int flowcatch();

#endif

