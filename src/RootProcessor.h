#ifndef R_h
#define R_h
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <sstream>
#include <math.h>
#include <set>
#include "RGB.h"

using namespace cv;
//RNG rng(12345);

class RootProcessor
{
	public:
	vector<Point2f> cornerDetection(Mat,double,double,int,bool,double,int);
	double* make_ready(vector<Point2f> d);

	Point2f detector_L(vector<Point2f> candidate,Point2f p,double minD);
	Point2f detector_M(vector<Point2f> candidate,Point2f p,double minD);
	Point2f detector_R(vector<Point2f> candidate,Point2f p,double minD);

	Point2f sp_detector(vector<Point2f> candidate,Point2f p,double grade,double radius);

	double distanceCl(Point2f,Point2f);
	double gradient(Point2f s,Point2f e);
	
	Point2f* middle_detect(Mat,int);
	Mat local_filter(Mat,int,int,int,int,int,int);
	Mat filtering(Mat,int);
	bool img_subtr(Mat src,Size s,Point2f loc,int tr_dis,int sensitivy,int,int,int,int can_t1,int can_t2);
	Mat img_subtr(Mat src_f,Mat src_s,int&);
	
	void rotate(Mat& src,int angle,Mat& dst);
	
	vector<double> poly_detect(vector<Point2f> points,int n);
	
	Point2f* root_detection(Mat,Point2f,int,int);
	
	std::set<Point2f> complete_root_detectopm(Mat src,Point2f s);
	
};

#endif
