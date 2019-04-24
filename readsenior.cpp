//该程序只用于摄像机读取当前每一帧的图像，并交替保存在缓冲内存L1和L2中（设置flag）
//在缓冲区内存中分配一(32字节）的地址段记录当前编号（每24小时清零）
//存储每一帧，程序执行的时间应远小于0.04s(40ms)
//内调用滤波子线程

#include"victor.h"

using namespace std;
using namespace cv;

extern victor data;
extern std::mutex store;	
extern bool flag;
extern long int clocks;
extern std::vector<cv::Rect> faces;

int victor::read()
{
	
	//Mat tem;
	extern cv::Mat frame1;//声明外部变量（储存的地方）
	extern cv::Mat frame2;
	extern Mat face;

	VideoCapture source(0);
	if (!source.isOpened())
	    {
		cout<<"调取摄像机出错"<<endl;
		return -1;
	    }
	source >> frame1;
	source >> frame2;
	
	frame1.copyTo(face);

//启动子线程滤波+检测人脸
	std::thread  mythread(	
				[]{
			//	store.lock();
				data.face_d();
			//	store.unlock();
				}
				);	//线程函数filter
		if(mythread.joinable())
			mythread.detach();		//主线程在等待该子线程完成后才销毁内存
	
	waitKey(100);

	std::thread	 dlibthread([]{
			//	store.lock();
				data.point_extract();
			//	store.unlock();
				});	//线程函数eyedetect
	
		if(dlibthread.joinable())
			dlibthread.detach();


	while(1)
	{
		if (flag==true)
		   {	
			
			
			source >> frame1;
			flag=!flag;//flag设置
			clocks++;//时间编号
	//	imshow("L1",frame1);
		waitKey(30);
	//	cout<<"clocks: "<<clocks<<endl
	//	    <<"flag: "<<flag<<endl;
		
			
		   }
		else if(flag==false)
		   {	
			source >> frame2;
			flag=!flag;
			clocks++;
	//	imshow("L2",frame2);
		waitKey(30);
	//	cout<<"clocks: "<<clocks<<endl
	//	    <<"flag: "<<flag<<endl;
			
		   }
	}
		return 0;
}







