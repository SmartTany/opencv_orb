#include "common.hpp"
#include <stdio.h>
#include "ffmpeg.h"
#include <sys/time.h>

using namespace cv;
bool test=false;


void OpenCL_Init(void)
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
}

/*void FFMPEG_Decode_H264(char *videofilename)
{
  ffmpegDecode decode=ffmpegDecode(videofilename);
}*/




int main()
{
  OpenCL_Init();
  long tv_usec; /* 微秒数 */
  struct timeval tpstart,tpend;
  float timeuse;
  UMat frame,framegray;
  UMat local,localgray;
  ffmpegDecode decode=ffmpegDecode("/home/tany/download/input.mp4");
  imread("/home/tany/download/local.jpg").copyTo(local);
  //cvtColor(local, localgray, COLOR_BGR2GRAY);
  Mat reSize = Mat::zeros(368, 640,CV_8UC3);
  resize(local,local,reSize.size());

  Ptr<ORB> orb = ORB::create();
  vector<KeyPoint> Keypointlocal,Keypointframe;
  UMat descriptorlocal,descriptorframe;

  orb->detectAndCompute(local,Mat(),Keypointlocal,descriptorlocal);
  vector<DMatch> matches;
  Ptr<DescriptorMatcher> matcher = DescriptorMatcher::create("BruteForce");

  UMat ShowMatches;
  clock_t begin,end;
  ocl::setUseOpenCL(true);
  //cvNamedWindow("DECODE", CV_WINDOW_AUTOSIZE);  //创建一个OpenCV窗口，自动大小
  //cvNamedWindow("DECODE",1);  //创建一个OpenCV窗口，自动大小

  while(!framefinish)
  {
     decode.ffmpegshowframe().copyTo(frame);
                    if(!frame.empty())
                    {
                        cvtColor(frame, framegray, COLOR_BGR2GRAY);
                        orb->detectAndCompute(frame,Mat(),Keypointframe,descriptorframe);   //创建ORB识别对象
                        matcher->match(descriptorlocal,descriptorframe,matches);
                        drawMatches(local,Keypointlocal,frame,Keypointframe,matches,ShowMatches);
                     //imshow("DECODE",ShowMatches);
                     if(test==false)
                    {
                        test = true;
                        gettimeofday(&tpstart,NULL);
                     }
                     waitKey(1);
                    }

  }
  gettimeofday(&tpend,NULL);
  timeuse=1000000*(tpend.tv_sec-tpstart.tv_sec)+tpend.tv_usec-tpstart.tv_usec;
  timeuse/=1000000;
  printf("Used Time:%f\n",timeuse);
  destroyWindow("DECODE");
  return 0;
}
                                                                                                                          1,1          顶端

