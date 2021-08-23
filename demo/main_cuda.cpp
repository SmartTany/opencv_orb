//#include "common.hpp"
#include <stdio.h>
#include "ffmpeg.h"
#include <sys/time.h>
#include "mat_code_charge.hpp"

using namespace cv;
//using namespace cuda;
bool test=false;


/*void OpenCL_Init(void)
{
  OpenCL::startup  opencl;
  opencl.Check_OpenCL_Model();
  opencl.Check_devices_Model();
  opencl.Create_Context_Transfer();
}

void Parallel_Count(char *kernelfilename,char *codefilename)
{
  OpenCL::startup  opencl;
  opencl.Create_Kernel_Method(kernelfilename);
  opencl.Mem_Write_Kernel(codefilename);
  opencl.Mem_Read_Kernel();
}*/

/*void FFMPEG_Decode_H264(char *videofilename)
{
  ffmpegDecode decode=ffmpegDecode(videofilename);
}*/



int main()
{
  //OpenCL_Init();
  long tv_usec; /* 微秒数 */
  struct timeval tpstart,tpend;
  float timeuse;

  cuda::GpuMat Gframe,Glocal;
  cuda::GpuMat Gframeray,Glocalray;

  Mat dis_local,dis_frame;
  
  ffmpegDecode decode=ffmpegDecode("/home/tany/download/input.mp4");
  Mat local = imread("/home/tany/download/local.jpg");

  Mat reSize = Mat::zeros(368, 640,CV_8UC3);
  resize(local,local,reSize.size());
  Glocal.upload(local);
  cv::cuda::cvtColor(Glocal,Glocalray,COLOR_BGR2GRAY);       //covert ray format
  Ptr<cuda::ORB> d_orb =cuda::ORB::create();  //create a ORB NN
  vector<KeyPoint> Keypointlocal,Keypointframe;
  cuda::GpuMat d_Keypointlocal,d_Keypointframe;
  cuda::GpuMat d_descriptorlocal,d_descriptorframe,d_descriptorlocal_format,d_descriptorframe_format;
  Ptr<cuda::DescriptorMatcher> d_matcher =cuda::DescriptorMatcher::createBFMatcher(NORM_L2);

  std::vector<DMatch> matches;
  std::vector<DMatch> good_matches;
  d_orb->detectAndComputeAsync(Glocalray,cuda::GpuMat(),d_Keypointlocal,d_descriptorlocal);
  d_orb->convert(d_Keypointlocal,Keypointlocal);
  d_descriptorlocal.convertTo(d_descriptorlocal_format, CV_32F);

  Mat ShowMatches;
  clock_t begin,end;
  //ocl::setUseOpenCL(true);
  //cvNamedWindow("DECODE", CV_WINDOW_AUTOSIZE);  //创建一个OpenCV窗口，自动大小
  //cvNamedWindow("DECODE",1);  //创建一个OpenCV窗口，自动大小
  /*
   *   Author:tany
   *   idea:the best compare match image,all keypoint distance size total is smallest
   */        
  double total_min_distance;
  int count_num;
  double test_dist[501];

  Mat frame1;
  double dist_total1,dist_total2=0xffffff;

  while(!framefinish)
  {
    double sum_dist=0;  
    Mat frame =  decode.ffmpegshowframe();
                    if(!frame.empty())
                    {   
			Gframe.upload(frame);
			cv::cuda::cvtColor(Gframe,Gframeray,COLOR_BGR2GRAY);
	                d_orb->detectAndComputeAsync(Gframeray,cuda::GpuMat(),d_Keypointframe,d_descriptorframe);   //创建ORB识别对象
			d_orb->convert(d_Keypointframe,Keypointframe);
			d_descriptorframe.convertTo(d_descriptorframe_format, CV_32F);
                        d_matcher->match(d_descriptorlocal_format,d_descriptorframe_format,matches);
			drawMatches(local,Keypointlocal,frame,Keypointframe,matches,ShowMatches);
                        //imshow("DECODE",ShowMatches);
                        int sz = matches.size();             //total is 500          

			for(int i=0;i<sz;i++)
			{
			   double dist = matches[i].distance;
			   sum_dist =sum_dist + dist;
			}
		        
		        dist_total1 = sum_dist;
			if(dist_total1 < dist_total2)
			{
			dist_total2 = dist_total1;
			Gframe.download(frame1);
			//cout<<"sum_dis"<<dist_total2<<endl;
			//imwrite("/home/tany/download/result.jpg",frame1);
			}

		       if(test==false)
		       { 
		       	 test = true;     
		         gettimeofday(&tpstart,NULL);
		       }
                    }
     
  }
  imwrite("/home/tany/download/result.jpg",frame1);
  gettimeofday(&tpend,NULL);
  timeuse=1000000*(tpend.tv_sec-tpstart.tv_sec)+tpend.tv_usec-tpstart.tv_usec;
  timeuse/=1000000;
  printf("Used Time:%f\n",timeuse);
  return 0;
}
