//检测人眼区域并保存到eye
//设置线程互斥锁机制，保护face的读写。


#include"victor.h"

using namespace std;
using namespace cv;




void victor::eyedetect()
{
	extern victor data;
	extern std::mutex rw;
	extern cv::Mat frame1;
	extern cv::Mat frame2;
	extern cv::Mat deal;
	extern cv::Mat eye;
	extern cv::Mat face;

	Mat Tem;
	
	CascadeClassifier eyecascade;
	
	size_t i;
	while(1)
	   { 
			rw.lock();//（上锁&执行）or阻塞
			face.copyTo(Tem);	//就复制face内的帧到Tem
			if(Tem.rows<10&&Tem.cols<10)
				{
					rw.unlock();
					waitKey(30);
					continue;
				}

			
		//	equalizeHist(Tem, Tem);//变换后的图像进行直方图均值化处理
		
			
			for(int i=0;i<Tem.rows;i++)  //二值化处理，阈值45
				{
					uchar* data= Tem.ptr<uchar>(i);
					for(int j=0;j<Tem.cols;j++)
					{	
			
						if(data[j]<45) {data[j]=1;}
						else	{data[j]=255;}
				
				
					}	
				}	
			
			

			rw.unlock();//解锁face资源
		
			imshow("eyesdetect",Tem);
			//cout<<"眼睛检测正确"<<endl;
			waitKey(10);
			continue;
		  
		cout<<"眼睛检测失败！"<<endl;
			
		 
		
		
          }
}
