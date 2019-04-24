
#ifndef __PEOPLE_HPP__
#define __PEOPLE_HPP__

#include "victor.h"
using namespace cv;
using namespace std;
using namespace dlib;

class people
{
	protected:
		double eye_rate_left;
		double eye_rate_right;
		double mouth_d;

	public:
		people()
		{
			cout<<"a people built"<<endl;
		}
		people(full_object_detection shape)
		{
			eye_cal(shape);
			mouth_cal(shape);
		}
		~people()
		{
			std::cout << "a people destroyed" << std::endl;
		}

		void eye_cal(full_object_detection shape)
		{
			double l_eye_xd, r_eye_xd; 
			double l_eye_yd1, l_eye_yd2, r_eye_yd1, r_eye_yd2;	
			l_eye_xd  = sqrt(pow(shape.part(39).x()-shape.part(36).x(),2)
							+pow(shape.part(39).y()-shape.part(36).y(),2));
			r_eye_xd  = sqrt(pow(shape.part(45).x()-shape.part(42).x(),2)
							+pow(shape.part(45).y()-shape.part(42).y(),2));
			l_eye_yd1 = sqrt(pow(shape.part(41).x()-shape.part(37).x(),2)
							+pow(shape.part(41).y()-shape.part(37).y(),2));
			l_eye_yd2 = sqrt(pow(shape.part(40).x()-shape.part(38).x(),2)
							+pow(shape.part(40).y()-shape.part(38).y(),2));
			r_eye_yd1 = sqrt(pow(shape.part(47).x()-shape.part(43).x(),2)
							+pow(shape.part(47).y()-shape.part(43).y(),2));
			r_eye_yd2 = sqrt(pow(shape.part(46).x()-shape.part(44).x(),2)
							+pow(shape.part(46).y()-shape.part(44).y(),2));
			eye_rate_left = (0.5*(l_eye_yd1+l_eye_yd2))/l_eye_xd;
			eye_rate_right= (0.5*(r_eye_yd1+r_eye_yd2))/r_eye_xd;
		}

		void mouth_cal(full_object_detection shape)
		{
			double mouth_yd, mouth_xd;
			mouth_yd   = sqrt(pow(shape.part(66).x()-shape.part(62).x(),2)
							+pow(shape.part(66).y()-shape.part(62).y(),2));
			mouth_xd   = sqrt(pow(shape.part(54).x()-shape.part(48).x(),2)
							+pow(shape.part(54).y()-shape.part(48).y(),2));
			mouth_d   =  mouth_yd/mouth_xd;
		}

};

class people_state:public people
{
	public:
		struct persondata
		{
			double e_left;
			double e_right;
			double m_d;
		};

	protected:
		persondata driver_data; 
		std::list<persondata> percode;
		int DETECT_FREQUENCY = 180;
		int count;
		double MAX_EYERATE = 0.3;
		double EYE_THRESHOLD = 0.8*MAX_EYERATE; //P80 principle
		double MOUTH_THRESHOLD = 0.3; 
		double f_perclos = 0;		//Perclos value	
		

	public:
		people_state():people(){};
		people_state(full_object_detection shape):people(shape)
		{
			number_trans();
		}
		
		bool data_deal(full_object_detection shape)
		{
			eye_cal(shape);
			mouth_cal(shape);
			number_trans();
			data_store();
			count++;
			if (count >= DETECT_FREQUENCY)
			{
				count = 1;
			}
		}
		
		bool is_tired()
		{
			if(is_PERCLOS()||is_yawn())
			{
				return true;
			}
			else 
				return false;
		}

		void number_trans()
		{
			driver_data.e_left = eye_rate_left;
			driver_data.e_right = eye_rate_right;
			driver_data.m_d = mouth_d;
		}
		void data_store()
		{
			if(percode.size()<DETECT_FREQUENCY)
				percode.push_front(driver_data);
			else
			{
				percode.push_front(driver_data);
				percode.pop_back();
			}
		}

		bool is_PERCLOS()
		{
			double tmp_test=1;
			if (percode.size()<DETECT_FREQUENCY)
				return false;
			else
			{
				std::list<persondata>::iterator check;
				for (check = percode.begin(); check != percode.end(); check++) {
					if ((*check).e_left < EYE_THRESHOLD) {
						tmp_test++;
					}
				}
				if(tmp_test/DETECT_FREQUENCY>0.16)
				{
					f_perclos = tmp_test/DETECT_FREQUENCY;
					return true;
				}
				else
					return false;
			}
		}
			
		bool is_yawn()
		{
			int tmp_test = 0;
			if (percode.size()<DETECT_FREQUENCY)
				return false;
			else
			{
				std::list<persondata>::iterator check;
				for (check = percode.begin(); check != percode.end(); check++) {
					if ((*check).m_d > MOUTH_THRESHOLD) {
						tmp_test++;
					}
				}
				if(tmp_test >= 3)
				{
					cout<<"-----<<<<<< mouth-rate!!!<<<"<<endl;
					return true;
				}
				else
					return false;
			}
		}

		void getdata()
		{
			cout << "==================================" << endl;
			cout << "eye_rate_left = "<< eye_rate_left << endl;
			cout << "eye_rate_right = "<< eye_rate_right << endl;
			cout << "mouth_d = "<< mouth_d << endl;
			cout << "==================================" <<endl;
		}
		void get_f_perclos()
		{
			cout << "PERCLOS value = "<<f_perclos<<endl;
		}

		void set_detect_period(int n)
		{
			DETECT_FREQUENCY = n;
		}

		void set_threshold(double a, double b)
		{
			MAX_EYERATE = a;
			EYE_THRESHOLD = 0.8*MAX_EYERATE; 
			MOUTH_THRESHOLD = b;
		}

		

};
	

#endif
