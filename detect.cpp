//检测人眼区域并保存到eye
//设置线程互斥锁机制，保护face的读写。


#include"victor.h"

using namespace std;
using namespace cv;




void victor::detect()
{
	extern victor data;
	extern mutex rw;
	extern cv::Mat frame1;
	extern cv::Mat frame2;
	extern cv::Mat deal;
	extern cv::Mat eye;
	extern cv::Mat face;

	Mat Tem;
	
	CascadeClassifier eyecascade;
	eyecascade.load("haarcascade_eye_tree_eyeglasses.xml");
	
	size_t i;
	while(1)
	   { 
	   		rw.lock();//（上锁&执行）or阻塞
			face.copyTo(Tem);	//就复制face内的帧到Tem
			
			vector<Rect> eyes(0);//建立用于存放人脸的向量容器
			
			
			equalizeHist(Tem, Tem);//变换后的图像进行直方图均值化处理
		
			eyecascade.detectMultiScale(Tem, eyes,
				1.1, 2, 0,
				//|CV_HAAR_FIND_BIGGEST_OBJECT
				//|CV_HAAR_DO_ROUGH_SEARCH
				//| CV_HAAR_SCALE_IMAGE,
				Size(30, 30));			//检测人脸，并把信息存在eyes容器内

			
			for (i = 0; i < eyes.size(); i++)//遍历整个区域
			{
				if (eyes[i].height > 0 && eyes[i].width > 0)
				{
					eye = deal(eyes[i]);
					
				}
			
			}
			rw.unlock();//解锁face资源
		if(eye.rows>0&&eye.cols>0) 
		   {
			imshow("eyesdetect",eye);
			cout<<"眼睛检测正确"<<endl;
			waitKey(10);
			continue;
		   }
		cout<<"眼睛检测失败！"<<endl;
			
		 
		
		//else if(data.flag==false)
		
			
			waitKey(10);
          }
}
