cv::Mat AlternativeLineReduction(cv::Mat srcImage, float widthRatio, float heightRatio){
	CV_Assert(srcImage.data != NULL);
	cv::Mat tmpImage(int(widthRatio * srcImage.rows), srcImage.cols, srcImage.type(), cv::Scalar(0));
	cv::Mat dstImage(int(widthRatio * srcImage.rows), int(heightRatio * srcImage.cols), srcImage.type(), cv::Scalar(0));
	for (int i = 0; i < int(srcImage.rows * widthRatio); i++){
		 srcImage.row(cvFloor(i / widthRatio)).copyTo(tmpImage.row(i));
	}
	imshow("tmp", tmpImage);
	for (int j = 0; j < int(srcImage.cols * heightRatio); j++){
		tmpImage.col(cvFloor(j / heightRatio)).copyTo(dstImage.col(j));
	}
	return  dstImage;
}


cv::Mat PixelReplication(cv::Mat srcImage, float widthRatio, float heightRatio){
	CV_Assert(srcImage.data != NULL);
	cv::Mat dstImage(int(widthRatio * srcImage.rows), int(heightRatio * srcImage.cols) ,srcImage.type(),cv::Scalar(0));
	for (int i = 0; i < int(srcImage.rows * widthRatio); i++){
		for (int j = 0; j < int(srcImage.cols * heightRatio); j++){
			dstImage.at<cv::Vec3b>(i, j) = srcImage.at<cv::Vec3b>(cvFloor(i / widthRatio), cvFloor(j / heightRatio));
		}
	}
	return  dstImage;
}


cv::Mat nearestNeighbourInterpolation(cv::Mat srcImage, float widthRatio, float heightRatio)
{
	CV_Assert(srcImage.data != NULL);
	cv::Mat dstImage(int(widthRatio * srcImage.rows), int(heightRatio * srcImage.cols) ,srcImage.type(),cv::Scalar(0));
	for (int i = 0; i < int(srcImage.rows * widthRatio); i++){
		for (int j = 0; j < int(srcImage.cols * heightRatio); j++){
			dstImage.at<cv::Vec3b>(i, j) = srcImage.at<cv::Vec3b>(cvRound(i / widthRatio), cvRound(j / heightRatio));
		}
	}
	return  dstImage;
}

// 变量名字没取好，导致误认为rows 是srcImage.rows. 我调试了近6个小时才发现，深刻体会了一把取个有意义的名字及调试技巧的重要性
cv::Mat BilinearInterpolation(cv::Mat srcImage, float widthRatio, float heightRatio){
	CV_Assert(srcImage.data != NULL);
	int dstRows = int(widthRatio * srcImage.rows);
	int dstCols = int(heightRatio * srcImage.cols);
	cv::Mat dstImage(dstRows, dstCols, srcImage.type(), cv::Scalar(0) );
	for (int i = 0; i < dstRows; i++){
		for (int j = 0; j <dstCols; j++){
			double x = (i + 0.5) / widthRatio - 0.5;
			double y = (j + 0.5) / heightRatio - 0.5;
			int x1 = cvFloor(x);
			int y1 = cvFloor(y);
			int x2 = x1 + 1;
			int y2 = y1 + 1;
			if (x1 < 0) x1 = x2 = 0;
			if (y1 < 0) y1 = y2 = 0;
			if (x2 > srcImage.rows - 1) x1 = x2 = srcImage.rows - 1;
			if (y2 > srcImage.cols - 1) y1 = y2= srcImage.cols- 1;
			
			if (x2 == dstRows - 1 || y2 >= dstCols - 1 || x1 == 0 || y1 == 0)
				dstImage.at<cv::Vec3b>(i, j) = srcImage.at<cv::Vec3b>(x1, y1);
			else
				for (int k = 0; k < 3; k++){
					double temp = srcImage.at<cv::Vec3b>(x1, y1)[k] * (x2 - x)*(y2 - y) + srcImage.at<cv::Vec3b>(x2, y1)[k] * (x - x1)*(y2 - y);
					temp += srcImage.at<cv::Vec3b>(x2, y2)[k] * (x - x1) * (y - y1) + srcImage.at<cv::Vec3b>(x1, y2)[k] * (x2 - x)*(y - y1); 
					dstImage.at<cv::Vec3b>(i, j)[k] = int(temp);
				}
		}
	}
	return  dstImage;
}

