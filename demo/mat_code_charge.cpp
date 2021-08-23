#include "mat_code_charge.hpp"

vector<vector<uchar>> mattocode(Mat img)
{
  int w = img.cols * img.channels();
  int h = img.rows;

  vector<vector<uchar>> array (h,vector<uchar>(w));
  for(int i=0;i<h;i++)
  {
    uchar* inData = img.ptr<uchar>(i);
    for(int j=0;j<w;j++)
    {
      array[i][j] = inData[j];
    }
  }
return array;
}

Mat codetomat(vector<vector<uchar>> array)
{
  size_t h = array.size();
  size_t w = array[0].size();

  Mat img(h,(size_t)(w/3),CV_8UC3);
  for(size_t i=0;i<h;i++)
  {
    uchar* outData = img.ptr<uchar>(i);
    for(size_t j=0;j<w;j++)
    {
      outData[j] = array[i][j];
    }
  }
return img;  
}
