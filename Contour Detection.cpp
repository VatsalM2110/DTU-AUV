#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;

Mat imgGray, imgBlur, imgCanny;

void main() {

	string path = "Resources/shapes.png";
	Mat img = imread(path);

	cvtColour(img, imgGray, COLOR_BGR2GRAY);
	GaussianBlur(img, imgBlur, size(3, 3), 3, 0);
	Canny(imgBlur, imgCanny, 25, 75);
	Mat kernel = getStructuringElement(MORPH_RECT, Size(3, 3));
	dilate(imgCanny, imgDil, kernel);


	imshow("Image", img);
	imshow("Image Gray", imgGray);
	imshow("Image Blur", imgBlur);
	imshow("Image Canny", imgCanny);
	imshow("Image Dilated", imgDil);
	waitkey(0);
}