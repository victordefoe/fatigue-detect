//根据标志判断从frame1或frame2中复制帧到Tem上进行处理，返回进行滤波，结果存到到deal
//对deal内的图像结果进行人脸检测，检测的结果存到faces
#include "victor.h"
using namespace std;
using namespace cv;
using namespace dlib;
int test = 1;

image_window win;

int victor::face_d()
  {
	extern Mat face; //全局变量face
	extern Mat eyes; //全局变量eyes
	extern Mat frame1;
	extern Mat frame2;
	extern victor data;
	extern std::mutex rw;
	extern std::mutex store;
	extern bool flag;
	extern long int clocks;
	extern 	std::vector<Rect> faces;//建立用于存放人脸的向量容器
	extern CascadeClassifier cascade; //声明级联分类器cascade作为CascadeClassifier类的一个对象
	extern CascadeClassifier procascade;//类似于上面
	Mat gauss(Mat src,Mat dst);//定义高斯函数，输入输出都是Mat类型
    int face_detection(Mat Tem);//把检测过程封装成一个函数
//	void point_extract(shape_predictor pose_model);
	cascade.load("haarcascade_frontalface_alt.xml");//训练器名称指针（只读）
	procascade.load("haarcascade_profileface.xml");

	Mat Tem;  //把之前读取到的帧放到Tem里面
	Rect rect;
	rect.x = 0;
	rect.y = 0;
	rect.height = 0;
	rect.width = 0;
	faces.push_back(rect);
	while(1)
	{
		if (flag==true)	//如果data.flag的值是ture，
			frame2.copyTo(Tem);	//就复制frame1内的帧到Tem
		else 				//否则，
			frame1.copyTo(Tem);	//复制frame2的内容到Tem
		
	/*	if(face_detection(Tem)>0) 
		{
		//	point_extract(pose_model,faces);
			cout << "脸检测成功";
		}*/
		face_detection(Tem);
	}
	return 0;
  }

	int face_detection(Mat Tem)
	{
		extern std::mutex rw;
	//	cout<<"thread 1----------------------------------------------"<<endl;
		extern Mat face;
		extern std::vector<Rect> faces;//建立用于存放人脸的向量容器
		extern int test;
		extern CascadeClassifier cascade; //声明级联分类器cascade作为CascadeClassifier类的一个对象
		extern CascadeClassifier procascade;//类似于上面
		
		size_t i;
		Mat deal;
		extern Mat gray;
		medianBlur(Tem,deal,3);	//中值滤波，结果存到deal
		//cvtColor(deal, gray, CV_BGR2GRAY); //把存在deal内的图转化为灰度图，存在gray
		deal.copyTo(gray);
			//resize(gray, smallImg, smallImg.size(), 0, 0, INTER_LINEAR);//改变图像大小，使用双线性差值
		//equalizeHist(gray, gray);//变换后的图像进行直方图均值化处理
		rw.lock();//（上锁&执行）or阻塞             
		cascade.detectMultiScale(gray, faces,  //--------------------------------------------(1)
				1.1, 2, 0  
				//|CV_HAAR_FIND_BIGGEST_OBJECT
				//|CV_HAAR_DO_ROUGH_SEARCH
				| CV_HAAR_SCALE_IMAGE,
				Size(30, 30));			//检测人脸，并把信息存在faces容器内
			
				if (faces[0].height > 0 && faces[0].width > 0)
				{
				//	face = gray(faces[0]);//faces表示不同脸的灰度图 
					face = Tem;
				}
		
			if(faces.size()<1)  //如果检测到脸部，则显示出来,否则进行下一项检测
			{	rw.unlock();
			//	cout<<"..................."<<endl;
				return 0;
			}
			else
				{
				//	imshow("faces",face);
				//	waitKey(10);
			//		waitKey(10);
				//	face=0;
					rw.unlock();
				//	cout<<"detect suceed id:"<<test<<endl;
					test++;
					if (test>=100) {
						test = 1;
					}
		//			(victor()).point_extract();
					return 1;
				}	

	}
  			
Mat gauss(Mat src,Mat dst)		//gauss函数
  {
	Mat dst1;
	float k[9]={1.f/16, 2.f/16, 1.f/16,
                    2.f/16, 4.f/16, 2.f/16,
                    1.f/16, 2.f/16, 1.f/16};
	Mat Km;
	Km=Mat(3,3,CV_32F,k);
	GaussianBlur(src,dst,Size(3,3),0,0);
	return dst;
    
  }

void victor::point_extract()
{
	extern std::mutex rw;
	rw.lock();
	extern std::vector<Rect> faces;
	extern Mat face;
	extern image_window win;
	extern Mat frame1;
	cout<<"========================================";
	int tmp;
	tmp = test;
	std::vector<Rect> facess(faces);
//	facess = faces;
	rw.unlock();
	people_state driver;
	driver.set_detect_period(100);
	driver.set_threshold(0.3,0.3);

	shape_predictor pose_model;
	deserialize("shape_predictor_68_face_landmarks.dat") >> pose_model;
	cout << "线程2开始";
	
    while(!win.is_closed())
	//  while(true)
	  {
		if (tmp==test) {
			waitKey(10);
			continue;
		}
		else
		{
			tmp = test;
			rw.lock();
			facess.assign(faces.begin(),faces.end());
			rw.unlock();
					
			dlib::rectangle det;
			if(facess.size()>0)
			{
			/*	cout<<" face[0].x= "<<facess[0].x<<endl;
				cout<<" face[0].y= "<<facess[0].y<<endl;
				cout<<" face[0].width= "<<facess[0].width<<endl;
				cout<<" face[0].height= "<<facess[0].height<<endl;
			*/	
				det.set_left(facess[0].x);
				det.set_top(facess[0].y);
				det.set_right(facess[0].x+facess[0].width);
				det.set_bottom(facess[0].y+facess[0].height);
			}
			else continue;
				
	        std::vector<full_object_detection> shapes;
	        cv_image<bgr_pixel> cimg(face); //把face的类型转化为dlib可处理的类型

			full_object_detection shape=pose_model(cimg, det);
			/*
			for(int k=0;k<shape.num_parts();k++)
			{
				cout <<"pixel position of No."<< k <<" part: " << shape.part(k) << endl;
			}*/
			shapes.push_back(shape);
			for(int k=0;k<68;k++)
			{
				circle(face,cvPoint(shape.part(k).x(),shape.part(k).y()), 3, cv::Scalar(0,0,255), -1);
			}
		//	cout <<"pixel position of No."<< 5 <<" part: " << shape.part(5) << endl;
			
			driver.data_deal(shape);
		//	driver.getdata();
			if(driver.is_tired())
			{
			//	for (int i = 0; i < 20; i++)
				{	
					cout<<"warning!You are tired"<<endl;
					driver.get_f_perclos();
				}
			}
			
	        win.clear_overlay();
	        win.set_image(cimg);
	        win.add_overlay(render_face_detections(shapes));
			cv::waitKey(10);
		}
	  }	  
}	
 
