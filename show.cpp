
#include"victor.h"

using namespace std;
using namespace cv;

extern victor data;

extern cv::Mat frame1;
extern cv::Mat frame2;
extern bool flag;
extern long int clocks;

void victor::show()
{
	imshow("第1个",frame1);
	cout<<"clocks: "<<clocks<<endl
	    <<"flag: "<<flag<<endl;
	
	imshow("第2个",frame2);
	
	
	cout<<"clocks: "<<clocks<<endl
	    <<"flag: "<<flag<<endl<<endl;
	//waitKey();
	cout << "这是opencv的 " << CV_VERSION "版本" <<endl;
	
}
