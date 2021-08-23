#include "ffmpeg.h"
#include <sys/time.h>

using namespace cv;
bool framefinish=false;

   ffmpegDecode :: ~ffmpegDecode()
   {
       av_free_packet(packet);
       av_free(out_buffer);
       av_free(pFrameBGR);
       av_free(pAvFrame);
       avcodec_close(pCodecCtx);
       avformat_close_input(&pFormatCtx);
       sws_freeContext(img_convert_ctx);
       //cvDestroyWindow("DECODE");
   }

   ffmpegDecode :: ffmpegDecode(char * filename)
   {
       av_register_all();                 //注册库中所有可用的文件格式及其编码器
       pFormatCtx = avformat_alloc_context();
	if (avformat_open_input(&pFormatCtx, filename, NULL, NULL) != 0)  //检查文件头部
		printf("Can't find the stream!\n");
	if (avformat_find_stream_info(pFormatCtx, NULL) < 0)              //查找流信息
		printf("Can't find the stream information !\n");
	for (int i=0; i < pFormatCtx->nb_streams; ++i) //遍历各个流，找到第一个视频流，并记录该流的编码信息
	{
	      if (pFormatCtx->streams[i]->codec->codec_type == AVMEDIA_TYPE_VIDEO) 
	      {
			videoindex = i;
			break;
	      }
	}
	if (videoindex == -1)
	{       	
		printf("Don't find a video stream !\n");
		return;
	}
       pCodecCtx = pFormatCtx->streams[videoindex]->codec; //获取一个指向视频流的上下文指针
       pCodec = avcodec_find_decoder(pCodecCtx->codec_id); //获取该格式的解码器
        if (pCodec == NULL) 
	{
			printf("Cant't find the decoder !\n"); 
			return ;
	}
	if (avcodec_open2(pCodecCtx,pCodec,NULL) < 0) 
	{ 
			printf("Can't open the decoder !\n");
			return ;
	}

       pAvFrame = av_frame_alloc(); //分配帧存储空间
       pFrameBGR = av_frame_alloc(); //存储解码后转换的RGB数据

       size = avpicture_get_size(AV_PIX_FMT_BGR24, pCodecCtx->width, pCodecCtx->height);//保存OpenCV支持的BGR格式数据
       out_buffer = (uint8_t *)av_malloc(size);
       avpicture_fill((AVPicture *)pFrameBGR, out_buffer, AV_PIX_FMT_BGR24, pCodecCtx->width, pCodecCtx->height);
       packet = (AVPacket*)malloc(sizeof(AVPacket));
       printf("-----------File information---------\n");
       av_dump_format(pFormatCtx, 0, filename, 0);
       printf("------------------------------------\n");

       img_convert_ctx = sws_getContext(pCodecCtx->width, pCodecCtx->height, pCodecCtx->pix_fmt, pCodecCtx->width, pCodecCtx->height, AV_PIX_FMT_BGR24, SWS_BICUBIC, NULL, NULL, NULL);
       pCvMat.create(cv::Size(pCodecCtx->width, pCodecCtx->height), CV_8UC3);

   }	

  //long tv_usec; /* 微秒数 */
  //struct timeval tpstart,tpend;
  //float timeuse;


cv::Mat ffmpegDecode :: ffmpegshowframe()
   {
      int ret;
      int got_picture;
      framefinish = false;

 // clock_t begin,end;

      while(av_read_frame(pFormatCtx, packet)>=0)
      {
	  //gettimeofday(&tpstart,NULL);
	
	  if(packet->stream_index==videoindex)
	 {
		ret = avcodec_decode_video2(pCodecCtx, pAvFrame, &got_picture, packet);
		if(ret < 0)
		{
		     printf("Decode Error\n");
		     //return;
		}
		if (got_picture)
		{
		     //YUV to RGB
		     sws_scale(img_convert_ctx, (const uint8_t* const*)pAvFrame->data, pAvFrame->linesize, 0, pCodecCtx->height, pFrameBGR->data, pFrameBGR->linesize);
                


		        //gettimeofday(&tpend,NULL);
                        //timeuse=1000000*(tpend.tv_sec-tpstart.tv_sec)+tpend.tv_usec-tpstart.tv_usec;
                        //timeuse/=1000000;
                        //printf("H264 Time:%f\n",timeuse);  //解码时间测试


		     memcpy(pCvMat.data, out_buffer, size);
		     return pCvMat;
		}
	}
	 av_free_packet(packet);
      }     
      framefinish = true;

   }



