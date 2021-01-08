#include "RootProcessor.h"
using namespace std;



Point2f* RootProcessor::middle_detect(Mat src_m,int last_edge)
{
	Mat src;
	src_m.copyTo(src);
	Mat src_res;
	src_m.copyTo(src_res);
	Mat src_fill;
	src_m.copyTo(src_fill);
	//cvtColor(src,src,CV_BGR2GRAY);
	//cvtColor(src_fill,src_fill,CV_BGR2GRAY);
	int lf=0,rf=src_fill.cols;
	Point2f resl;
	bool repaint=false;
	int ed;
	//kind 1----based on edge
	for(int i=last_edge;i<src_fill.rows;i++)
	{
		lf=0;
		rf=src_fill.cols;
		for(int j=0;j<src_fill.cols;j++)
		{
			if(src_fill.at<uchar>(i,j)>150)
			{
				lf=j;
				break;
			}
			else
				src_fill.at<uchar>(i,j)=0;
		}
		for(int j=src_fill.cols;j>=0;j--)
		{
			if(src_fill.at<uchar>(i,j)>150)
			{
				rf=j;
				break;
			}
			else
				src_fill.at<uchar>(i,j)=0;
		}
		if((lf!=0||rf!=src_fill.cols)&&lf!=rf)
		{
			resl.y=i;
			resl.x=(lf+rf)/2;
			for(int j=lf;j<rf;j++)
				src_fill.at<uchar>(i,j)=255;
		}
		else if(i>last_edge+25||(lf==0&&rf==src_fill.cols))
		{
			break;
		}
		
		
	}
	
	/*for(int i=ed;i<src_fill.rows;i++)
		for(int j=0;j<src_fill.cols;j++)
			src_fill.at<uchar>(i,j)=0;*/
			
	/*for(int i=0;i<src_fill.rows;i++)
	{
		for(int j=0;j<src_fill.cols;j++)
		{
			if(src_fill.at<uchar>(i,j)>200)
				cout<<1;
			else
				cout<<" ";
		}
		cout<<endl;
	}
	cout<<"=================================="<<endl;*/
	/*cout<<"=================================="<<endl;
	for(int i=0;i<src.rows;i++)
	{
		for(int j=0;j<src.cols;j++)
		{
			if(src.at<uchar>(i,j)>200)
				cout<<1;
			else
				cout<<" ";
		}
		cout<<endl;
	}*/
	//cout<<"=================================="<<endl;
	//kind2---based on middle
	
	Point2f resl2;
	for(int i=last_edge;i<src.rows;i++)
	{
		bool l=false,r=false;
		int l_index=-1,r_index=-1;
		for(int j=0;j<src.cols&&l==false;j++)
		{
			if(src.at<uchar>(i,j)>0)
			{
				l_index=j;
				l=true;
				break;
			}
		}
		for(int j=src.cols-1;j>=0&&r==false;j--)
		{
			if(src.at<uchar>(i,j)>0)
			{
				r_index=j;
				r=true;
				break;
			}
		}
		if(l&&r)
		{
			if(l_index!=r_index&&l_index!=-1&&r_index!=-1)
			{
				int m=((l_index+r_index)/2);
				src.at<uchar>(i,l_index)=0;
				src.at<uchar>(i,r_index)=0;
				src.at<uchar>(i,m)=255;
				resl2.x=m;
				resl2.y=i;
				i--;
			}
		}
	} 
	
	Mat res(src);
	bool find=false;
	
	/*for(int i=0;i<src.rows;i++)
	{
		for(int j=0;j<src.cols;j++)
		{
			if(src.at<uchar>(i,j)==255)
				cout<<1;
			else
				cout<<" ";
		}
		cout<<endl;
	}
	cout<<"=================================="<<endl;*/
	//circle(src_res,resl,5,Scalar(rng.uniform(0,255),rng.uniform(0,255),rng.uniform(0,255)),-1,8,0 );
	//imwrite("resOne.jpg",res);
	//imwrite("newOne.jpg",src_res);
	//cerr<<"edge base:("<<resl.x<<","<<resl.y<<") midlle base:("<<resl2.x<<","<<resl2.y<<")"<<endl;
	Point2f* res_a=new Point2f[2];
	res_a[0]=resl;
	res_a[1]=resl2;
	return res_a;
}

Mat RootProcessor::local_filter(Mat src_m,int sensitivy,int red_s,int green_s,int blue_s,int can_t1,int can_t2)
{
	Mat src_gray,src,src_edge;
	
	src_m.copyTo(src);	
	
	/*for(int i=0;i<src.rows;i++)
	{
		for(int j=0;j<src.cols;j++)
		{
			RGB& colors=src.at<RGB>(i,j);
			//colors.green=0;
			colors.blue=0;
			colors.red=0;
			/*if(colors.red>red_s)
				colors.red=255;
			else
				colors.red=0;
			if(colors.green>green_s)
				colors.green=255;
			else
				colors.green=0;
			if(colors.blue>blue_s)
				colors.blue=255;
			else
				colors.blue=0;
			
		}
	}
	
	imwrite("check_filter_RGB.jpg",src);*/
	
	
	cvtColor(src,src_gray,CV_BGR2GRAY);
	
	double my_chance=0;
	int cont=0;
	double max=0;
	for(int i=0;i<src_gray.rows;i++)
	{
		for(int j=0;j<src_gray.cols;j++)
		{
			my_chance+=src_gray.at<uchar>(i,j);
			if(src_gray.at<uchar>(i,j)>max)
				max=src_gray.at<uchar>(i,j);
			cont++;
		}
	}
	
	my_chance/=cont;
	
	my_chance=(my_chance+max)/2;
	
	cerr<<"(((( "<<my_chance<<" ))))"<<endl;	
	for(int i=0;i<src_gray.rows;i++)
	{
		for(int j=0;j<src_gray.cols;j++)
		{
			if(src_gray.at<uchar>(i,j)>my_chance)
				src_gray.at<uchar>(i,j)=255;
			else
				src_gray.at<uchar>(i,j)=0;
		}
	}
	
	imwrite("check_filter.jpg",src_gray);
	
	Canny(src_gray,src_edge,can_t1,can_t2,3,true);
	
	return src_edge;
}

Mat RootProcessor::filtering(Mat src_m,int sensitivy)
{
	Mat src_gray,src,src_edge;
	
	src_m.copyTo(src);
	
	cvtColor(src,src_gray,CV_BGR2GRAY);

	for(int i=0;i<src_gray.rows;i++)
	{
		for(int j=0;j<src_gray.cols;j++)
		{
			if(src_gray.at<uchar>(i,j)>sensitivy)
				src_gray.at<uchar>(i,j)=255;
			else
				src_gray.at<uchar>(i,j)=0;
		}
	}
	
	return src_gray;
}

bool RootProcessor::img_subtr(Mat src,Size s,Point2f loc,int tr_dis,int sensitivy,int red_s,int green_s,int blue_s,int can_t1,int can_t2)
{
	Mat subsrc,src_new;
	getRectSubPix(src,s,loc,subsrc);
	src_new=local_filter(subsrc,sensitivy,red_s,green_s,blue_s,can_t1,can_t2);
	Point2f pt(s.width,0);
	Point2f* res=root_detection(src_new,pt,0,0);
	if(res[1].x==0&&res[1].y==0)
		return true;
	res[1].x=res[1].x-s.height+loc.x;
	res[1].y=res[1].y-s.height+loc.y;
	double dist_tr=distanceCl(res[1],loc);
	cerr<<res[1]<<"|"<<loc<<"subtraction is equals:"<<dist_tr<<endl;
	if(dist_tr<tr_dis)
		return true;
	else
		return false;
	
}
