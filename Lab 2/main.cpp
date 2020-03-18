#include <opencv2/opencv.hpp>
#include <iostream>
#include "function.h"
using namespace cv;
using namespace std;
// Mat nearestNeighborInterpolation(Mat srcImage);
int main(){
	cv::Mat srcImage = imread("..\\images\\athena.jpg");
	if (!srcImage.data)
		return -1;
	// �Լ�ʵ�ֵ����ַ���������ʹ��fraction
	//cv::Mat dstImage = nearestNeighbourInterpolation(srcImage, 1.5, 1.5);
	//cv::Mat dstImage = BilinearInterpolation(srcImage, 1.5, 1.5);
	//cv::Mat dstImage = PixelReplication(srcImage, 1.5, 1.5);

	//Bicubic interpolation ,LANCZOS, Fractal�Ȳ�ֵ�������±�ע�Ͳ��֣�ʹ��ʱ�޸���Ӧ�������ɣ����ظ�
	float widthRatio = 1.5;
	float heightRatio = 1.5;
	cv::Mat dstImage(int(heightRatio * srcImage.rows), int(widthRatio * srcImage.cols), srcImage.type(), cv::Scalar(0));
	resize(srcImage, dstImage, dstImage.size(), 0, 0, cv::INTER_LANCZOS4);

	//cv::Mat dstImage = AlternativeLineReduction(srcImage, 0.5, 0.5);	
	cv::imshow("srcImage", srcImage);
	cv::imshow("dstImage", dstImage);
	cv::imwrite("..\\images\\athenaProcessed.jpg", dstImage);
	waitKey(0);
}