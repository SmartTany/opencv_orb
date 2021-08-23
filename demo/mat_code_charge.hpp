#include <iostream>
#include <opencv2/core.hpp>

using namespace std;
using namespace cv;

vector<vector<uchar>> mattocode(Mat img);
Mat codetomat(vector<vector<uchar>> array);

