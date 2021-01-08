#include "RootProcessor.h"
#include <queue>
using namespace std;

set<Point2f> RootProcessor::complete_root_detectopm(Mat src,Point2f s)
{
	Mat visited=Mat::zeros(src.size(),CV_8UC1);
		
}

Mat RootProcessor::img_subtr(Mat src_f,Mat src_s,int& S)
{
	Mat src_res;
	src_s.copyTo(src_res);
	cvtColor(src_res,src_res,CV_GRAY2BGR);
	
	for(int i=0;i<src_s.rows;i++)
	{
		for(int j=0;j<src_s.cols;j++)
		{
			if(src_s.at<uchar>(i,j)==255&&src_f.at<uchar>(i,j)==0)
			{
				RGB& colors=src_res.at<RGB>(i,j);
				colors.blue=0;
				colors.green=0;
				colors.red=255;
				S++;
			}
		}
	}
	
	return src_res;
}
