#include "RootProcessor.h"
#include "Counter.h"
#include <bits/stdc++.h>

#define SSTR( x ) dynamic_cast< std::ostringstream & >( ( std::ostringstream() << std::dec << x ) ).str()

RNG rng(12345);

using namespace std;
int main()
{
	RootProcessor RP;
	int numberOfRoots;
	vector<vector<Point2f> > pre;
	vector<vector<Point2f> > pre_r;
	vector<string> his;
	
	vector<Point2f> Xp;
	vector<Point2f> Yp;
	
	vector<Point2f> center_root;
	vector<Size> root_length;
	
	cerr<<"loding setting..."<<endl;
	ifstream SET("SETTING",ios::in);
	string a;
	string src_addres,load_addres,save_addres,results,start_point,end_point;
	int mood,len,stime,checker,sensitivy,red_s,green_s,blue_s,can_t1,can_t2,his_chek,len_his,his_tr,rotate_angel,numbers;
	double dis_tr_min,dis_tr_max,dis_tr_y;
	SET>>a;
	SET>>src_addres;
	SET>>a;
	SET>>start_point;
	SET>>a;
	SET>>end_point;
	SET>>a;
	SET>>numbers;
	SET>>a;
	SET>>checker;
	SET>>a;
	SET>>stime;
	SET>>a;
	SET>>sensitivy>>red_s>>green_s>>blue_s;
	SET>>a;
	SET>>rotate_angel;
	SET>>a;
	SET>>his_chek>>len_his>>his_tr;
	SET>>a;
	SET>>can_t1>>can_t2;												//canny treshholds
	SET>>a;
	SET>>dis_tr_min>>dis_tr_max>>dis_tr_y;						//distance treshholds
	SET>>a;
	SET>>save_addres;
	SET>>a;
	SET>>results;
	SET>>a;
	SET>>len;
	SET>>a;
	SET>>mood;
	SET>>a;
	
	Size s(len,len);
	
	cerr<<mood<<endl;
	vector<string> names;
	Counter counter_string(4,atoi(start_point.c_str()));
	if(mood==1)
	{
		SET>>load_addres;
		ifstream read_from_file(load_addres.c_str(),ios::in);
		read_from_file>>numberOfRoots;
		for(int i=0;i<numberOfRoots;i++)
		{
			vector<Point2f> prr;
			for(int j=0;j<1;j++)
			{
				Point2f t;
				read_from_file>>t.x>>t.y;
				prr.push_back(t);
				Point2f ee;
				read_from_file>>ee.x>>ee.y;
				Point2f c;
				c.x=(t.x+ee.x)/2;
				c.y=(t.y+ee.y)/2+5;
				center_root.push_back(c);
				Size ss(len*3,abs(t.y-ee.y)+10);
				root_length.push_back(ss);
				
				string name_handler="S"+start_point+"_E"+end_point+"_["+SSTR(t.x)+","+SSTR(t.y)+"]_["+SSTR(ee.x)+","+SSTR(ee.y)+"]";
				names.push_back(name_handler);
			}
			pre.push_back(prr);
			Point2f st(1,1);
			vector<Point2f> prr_r;
			prr_r.push_back(st);
			pre_r.push_back(prr_r);
		}
		
	}
	else
	{
		cerr<<"please enter number of roots:";
		cin>>numberOfRoots;
		for(int i=0;i<numberOfRoots;i++)
		{
			vector<Point2f> prr;
			for(int j=0;j<1;j++)
			{
				Point2f t;
				cin>>t.x>>t.y;
				prr.push_back(t);
			}
			pre.push_back(prr);
		}
	}
	cerr<<"making file.."<<endl;
	system(("mkdir "+save_addres+results).c_str());
	
	for(int i=0;i<numberOfRoots;i++)
	{
		system(("mkdir "+save_addres+results+"/results"+SSTR(i)).c_str());
		system(("mkdir "+save_addres+results+"/results"+SSTR(i)+"/locations").c_str());
		system(("mkdir "+save_addres+results+"/results"+SSTR(i)+"/roots").c_str());
	}
	cout<<src_addres<<endl<<save_addres<<endl<<load_addres<<endl<<mood<<endl<<len;
	
	fstream** output_handler=new fstream*[numberOfRoots];
	vector<bool> root_av(numberOfRoots,true);
	for(int i=0;i<numberOfRoots;i++)
	{
		string ad=save_addres+results+"/results"+SSTR(i)+"/root_"+SSTR(i)+".txt";
		output_handler[i]=new fstream(ad.c_str(),ios::out);
	}
	
	int counter=0;
	int check_counter=1;
	
	
	int last_edge;
	his.push_back(counter_string.now());
	
	
	string src_name_re=src_addres+"IMG_"+start_point+".JPG";
	vector<Mat> src_his;
	Mat src_his_m=imread(src_name_re);
	if(!src_his_m.data)
	{
		cerr<<"something is wrong"<<endl;
		return 1;
	}
	RP.rotate(src_his_m,rotate_angel,src_his_m);
	cerr<<"about to begin process..."<<endl;
	for(int i=0;i<numberOfRoots;i++)
	{
		getRectSubPix(src_his_m,root_length[i],center_root[i],src_his_m);
		Mat past_handler;
		past_handler=RP.filtering(src_his_m,sensitivy);
		src_his.push_back(past_handler);		
	}
	//imwrite("history.jpg",src_his[0]);
	
	counter++;
	counter_string.plus();
	while(counter<numbers)
	{
		
		string src_name=src_addres+"IMG_"+counter_string.now()+".JPG";
		cerr<<"counter is:"<<counter<<"~"<<counter_string.now()<<endl;
		Mat src=imread(src_name);
		if(!src.data)
			counter++;
		else
		{
			
			cerr<<"======================================="<<endl;
			his.push_back(counter_string.now());
			if(his.size()>=his_chek)
				his.erase(his.begin());
				
			
			string src_name_his=src_addres+"IMG_"+his[0]+".JPG";
			cerr<<"processing"<<counter_string.now()<<endl;
			cerr<<"extracting taken time.."<<endl;
			system(("./Data_Time/demo "+src_name+">data_res").c_str());
			string dt_t,t_t;
			ifstream dt_file("data_res",ios::in);
			dt_file>>dt_t>>t_t;
			cerr<<dt_t<<" "<<t_t<<endl;
			RP.rotate(src,rotate_angel,src);
			imwrite("rotated_pic.jpg",src);
			for(int r=0;r<numberOfRoots;r++)
			{
				//pre process
				if(root_av[r]==true)
				{
					cerr<<"pre process"<<endl<<"#"<<pre.at(r).size()<<endl;
					Point2f l(pre.at(r).at(pre.at(r).size()-1));
					last_edge=len/2-2*dis_tr_min;
					Mat subsrc,src_gray,src_edge;
				
					cerr<<"working at: "<<src_name<<endl;
					getRectSubPix(src,s,l,subsrc);
					
					src_edge=RP.local_filter(subsrc,sensitivy,red_s,green_s,blue_s,can_t1,can_t2);
				
					//main process
					cerr<<"main process"<<endl;
					
					double* redu=RP.make_ready(pre_r.at(r));
					double rr=redu[3]+redu[2]*(counter);
					
					Point2f* res_a=RP.middle_detect(src_edge,last_edge);
					Point2f res=res_a[0];
					Point2f res_p;		
					
					Point2f ps(len/2,len/2);
					Point2f* res_ap=RP.root_detection(src_edge,ps,last_edge,5);			
					
					if(res.x==0&&res.y==0)
						res_a=RP.middle_detect(src_edge,0);
					///cerr<<"~~~~~~"<<res_a[0]<<res_a[1]<<"|||"<<res_ap[0]<<res_ap[1]<<endl;
					res_a[0].x=res_a[0].x-len/2+l.x;
					res_a[0].y=res_a[0].y-len/2+l.y;
					res_a[1].x=res_a[1].x-len/2+l.x;
					res_a[1].y=res_a[1].y-len/2+l.y;
					
					res_ap[0].x=res_ap[0].x-len/2+l.x;
					res_ap[0].y=res_ap[0].y-len/2+l.y;
					res_ap[1].x=res_ap[1].x-len/2+l.x;
					res_ap[1].y=res_ap[1].y-len/2+l.y;
					
					res=res_a[0];
					double dist_n=RP.distanceCl( res_ap[1] , res_ap[0] );
					double dist_l=RP.distanceCl( l , res_a[0] );
					
					cerr<<"results -> "<<res_a[0]<<res_a[1]<<" ~ "<<res_ap[0]<<res_ap[1]<<endl<<"current distance: "<<dist_n<<endl<<"max width of root is: "<<res_ap[2].x<<endl;
					
					if(res_ap[2].x==0)
						res_ap[2].x=5;
					if(dist_n>dis_tr_min&&dist_n<=dis_tr_max&&abs(res_ap[0].x-res_ap[1].x)<=dis_tr_y/*&&abs(res_ap[0].x-res_ap[1].x)<=0.5*res_ap[2].x*/)
					{
						Mat src_hist=imread(src_name_his);
						Size sh(len_his,len_his);
						cerr<<">|< we needed subtraction: "
						<<(RP.img_subtr(src_hist,sh,res_ap[1],his_tr,sensitivy,red_s,green_s,blue_s,can_t1,can_t2))<<endl;
						if(RP.img_subtr(src_hist,sh,res_ap[1],his_tr,sensitivy,red_s,green_s,blue_s,can_t1,can_t2))
							res=res_ap[1];
						
					}
					
					res_p.x=res.x+len/2-l.x;
					res_p.y=res.y+len/2-l.y;
					
					/*if(dist_n==0&&dist_l<=dis_tr_min)
					{
						Mat src_hist=imread(src_name_his);
						Size sh(len_his,len_his);
						cerr<<"!!!!!!!!!!!!!!!!!!!!!!!!!!subtraction2: "
						<<(RP.img_subtr(src_hist,sh,res_a[1],his_tr,sensitivy,red_s,green_s,blue_s,can_t1,can_t2))<<endl;
						int chek;
						//cin>>chek;
						Size s2(len,2*len);
						getRectSubPix(src,s2,l,subsrc);
						src_edge=RP.local_filter(subsrc,sensitivy,red_s,green_s,blue_s,can_t1,can_t2);
						res_a=RP.middle_detect(src_edge,0);
						res_a[0].x=res_a[0].x-len/2+l.x;
						res_a[0].y=res_a[0].y-len+l.y;
						res_a[1].x=res_a[1].x-len/2+l.x;
						res_a[1].y=res_a[1].y-len+l.y;
						
						res=res_a[1];
					
						res_p.x=res.x+len/2-l.x;
						res_p.y=res.y+len-l.y;
						cerr<<"WARNING WARNING"<<endl;
						//int chek;cin>>chek;
					}*/
					
					
					
					//prepering resualts
					circle(src_edge,res_p,3,Scalar(255,255,255),-1,8,0 );
					
					pre.at(r).push_back(res);
					
					Point2f points_part(counter,res.x);
					Xp.push_back(points_part);
					
					Point2f rredius(counter+2,RP.distanceCl( pre.at(r).at(pre.at(r).size()-1) , pre.at(r).at(pre.at(r).size()-2) ) );
					pre_r.at(r).push_back(rredius);
					
					//cerr<<"*****distance: "<<rr<<"~"<<rredius<<"~"<<rr-rredius.y<<endl;
					
					//Point2f rredius(counter_time,distanceCl( pre.at(r).at(pre.at(r).size()-1) , pre.at(r).at(pre.at(r).size()-2) ) );
					//pre_r.at(r).push_back(rredius);
					//pre.at(r).erase(pre.at(r).begin());
					//string name_res_line=res_ad+"res1"+SSTR(r)+"/"+SSTR(counter)+"#"+SSTR(res.x)+"_"+SSTR(res.y)+"line.jpg";
					//imwrite(name_res_line,src_edge);
				
					//Point2f h(res.x+MD-l.x,res.y+MD-l.y);
					string name_res=save_addres+results+"/results"+SSTR(r)+"/locations/"+dt_t+"#"+t_t+"#"+counter_string.now()+"#"+SSTR(res.x)+"_"+SSTR(res.y)+".jpg";
					cerr<<name_res<<endl;
					imwrite(name_res,src_edge);
					/*int n;
					cin>>n;*/
					
					//src_his[r];
					Mat src_hand;
					getRectSubPix(src,root_length[r],center_root[r],src_hand);
					src_hand=RP.filtering(src_hand,sensitivy);
					int S=0;
					Mat growth=RP.img_subtr(src_his[r],src_hand,S);
					src_hand.copyTo(src_his[r]);
					
					string name_res_co_root=save_addres+results+"/results"+SSTR(r)+"/roots/"+dt_t+"#"+t_t+"#"+counter_string.now()+"#"+SSTR(res.x)+"_"+SSTR(res.y)+"_"+SSTR(S)+".jpg";
					imwrite(name_res_co_root,growth);
					
					(*output_handler[r])<<counter_string.now()<<" "<<dt_t<<" "<<t_t<<" "<<res.x<<" "<<res.y<<" "<<S<<endl;
				}
			}
			counter++;
			check_counter++;
			counter_string.plus();
		}
		if(check_counter%checker==0)
		{
			cerr<<"please check the results..."<<endl;
			cerr<<"if there is something wrong with specific roots,enter number of them\nand then enter the their codes"<<endl;
			int n;
			cin>>n;
			for(int i=0;i<n;i++)
			{
				int m;
				cin>>m;
				root_av[m]=false;
			}
		}
		//counter_time++;
		//cerr<<pre.at(r).at(2).x<<" "<<pre.at(r).at(2).y<<"\n"<<pre.at(r).at().x
	}
	cerr<<"root detection has been done\nif you want to save data on XML file press 1"<<endl;
	int cheking_xml;
	cin>>cheking_xml;
	if(cheking_xml==1)
	{
		cerr<<"starting making XML files..."<<endl;

		for(int i=0;i<numberOfRoots;i++)
		{
			string ad=save_addres+results+"/results"+SSTR(i)+"/root_"+SSTR(i)+".txt";
			string tar=save_addres+results+"/results"+SSTR(i)+"/"+names[i]+".xml";
		
			system(("java XMLFileManager "+ad+" "+tar+" "+SSTR(numbers)+" "+names[i]+" "+names[i]+".xml").c_str());
		}
	}
	//RP.poly_detect(Xp,Xp.size());
	//system("mkdir result/root1");
	//cerr<<c_ad<<endl;
	/*Mat src;
	src=imread("p2_e.jpg");
	RP.middle_detect(src);
	int chek=system("mkdir test1");
	cout<<"system er     "<<chek<<endl;
	cout<<"recheck"<<endl;*/
	return 0;
}
