//多线程调用
#include"victor.h"
cv::Mat frame1;
cv::Mat frame2;//
cv::Mat face;
cv::Mat eye;
victor data;
std::mutex rw;
std::mutex store;
std::vector<cv::Rect> faces;
cv::Mat gray;
using namespace std;
using namespace cv;
bool flag;
long int clocks;
int flowcatch();
CascadeClassifier cascade; //声明级联分类器cascade作为CascadeClassifier类的一个对象
CascadeClassifier procascade;//类似于上面
//victor a;
//a.read();

int main()
{
	bool flag=true;
	time_t sta,end;//建立计时的变量
	double diff;//时间差计算
	int r1;
	time(NULL)>>sta;
	
	r1 = data.read();
	//r1=(victor()).read(); //调用read函数并且返回值给r1
	
//	(victor()).show();//调用show函数
	
	time(NULL)>>end;
	diff = difftime(sta,end);
	cout <<"共用时  "<<diff<<'s'<<endl;
	return 0;
}


