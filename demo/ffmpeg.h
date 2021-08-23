#include <iostream>
#include <opencv2/core/ocl.hpp>

#include <vector>
#include <signal.h>

#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/cudabgsegm.hpp>
#include <opencv2/core/cuda.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/cuda_stream_accessor.hpp>
#include <opencv2/cudafeatures2d.hpp>

#include <opencv2/cudaimgproc.hpp>
#include <opencv2/cudaarithm.hpp>
#include <opencv2/cudafilters.hpp>
#include <opencv2/cudawarping.hpp>

#include <opencv2/features2d.hpp>



#define __STDC_CONSTANT_MACROS

extern bool framefinish;

extern "C"
{
#include <libavutil/opt.h>
#include <libavcodec/avcodec.h>
#include <libavutil/channel_layout.h>
#include <libavutil/common.h>
#include <libavutil/imgutils.h>
#include <libavutil/mathematics.h>
#include <libavutil/samplefmt.h>
#include "libavformat/avformat.h"
#include <libavformat/avformat.h>
#include <libswscale/swscale.h>
//#include <SDL/SDL.h>
};

using namespace std;

   class ffmpegDecode
   {
     public:
            ffmpegDecode(char *filename);
	    cv::Mat ffmpegshowframe();
	    ~ffmpegDecode();

			
     private:
	     AVCodec *pCodec;           //解码器指针
	     AVCodecContext* pCodecCtx; //ffmpeg解码类的类成员
	     AVFrame* pAvFrame,*pFrameBGR; //多媒体帧，保存解码后的数据帧
	     AVFormatContext* pFormatCtx; //保存视频流的信息 
	     AVPacket* packet;
	     uint8_t *out_buffer;
             int videoindex = -1;
	     int size;
	     SwsContext *img_convert_ctx; 
	     cv::Mat pCvMat;
			 
   };







