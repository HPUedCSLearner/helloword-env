#include <opencv2/opencv.hpp>
#include <string>


using namespace cv;
using namespace std;

int main()
{
    cout << "hello world" << endl;
    string imgPath = "/home/feng/github/helloword-env/ch02-OpenCV/demo-01-OpenCV-Helloword/opencv-demo.png";
    cv::Mat img = cv::imread(imgPath);
    cv::imshow("$$$$$$$$", img);
    cv::waitKey();

    return 0;
}