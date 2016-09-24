#include <opencv2/opencv.hpp>
#include <iostream>
#include <string>

using namespace cv;
using namespace std;

//  
// 运动前景提取——背景减除
// foreground = | frame - last_frame | > threshold 
// 更新背景模型——背景插值
// background = background * (1 - alpha) + frame * alpha 
//
int main(int argc, char **argv)
{
	Mat frame, grayImage, grayMat;
	Mat fgImage, fgMat, bgImage, bgMat, lastBGMat;

	int threshold = 25; // 二值化阈值  
	float alpha = 0.005; // 更新速度 [0, 1]  

	VideoCapture video("video.mp4");
	if (!video.isOpened()) {
		cout << "Error: open file fail!" << endl;
		return -1;
	}

	// 跳过部分无用信息
	int totalFrame = video.get(CV_CAP_PROP_FRAME_COUNT);
	video.set(CV_CAP_PROP_POS_FRAMES, totalFrame >> 2);

	//获取帧率  
	double rate = video.get(CV_CAP_PROP_FPS);
	int delay = 1000 / rate;

	namedWindow("Video", WINDOW_NORMAL);
	namedWindow("Foreground", WINDOW_NORMAL);
	namedWindow("Background", WINDOW_NORMAL);
	resizeWindow("Video", 400, 400);
	resizeWindow("Foreground", 400, 400);
	resizeWindow("Background", 400, 400);
	moveWindow("Video", 50, 50);
	moveWindow("Foreground", 460, 50);
	moveWindow("Background", 870, 50);

	while (video.read(frame)) {
		cvtColor(frame, grayImage, CV_BGR2GRAY);
		grayImage.convertTo(grayMat, CV_32FC1);

		if (bgMat.empty()) {
			grayImage.copyTo(bgImage);
			grayImage.convertTo(bgMat, CV_32FC1);
			lastBGMat = bgMat.clone();
		}
		// 背景消除
		absdiff(grayMat, lastBGMat, fgMat);
		// 自适应背景更新
		addWeighted(bgMat, 1 - alpha, grayMat, alpha, 0, bgMat);
		// 二值化
		::threshold(fgMat, fgMat, threshold, 255, CV_THRESH_BINARY);

		convertScaleAbs(fgMat, fgImage);
		convertScaleAbs(bgMat, bgImage);

		imshow("Video", frame);
		imshow("Foreground", fgImage);
		imshow("Background", bgImage);
		if (waitKey(delay) >= 0)
			break;

		lastBGMat = grayMat.clone();
	}
	video.release();

	return 0;
}
