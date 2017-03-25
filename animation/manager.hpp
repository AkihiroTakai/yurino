#ifndef __MANAGER_HPP__
#define __MANAGER_HPP__

#include <opencv2/opencv.hpp>

/*
 *=======================================================================================
 *動画を管理するクラス
 *=======================================================================================
 */
class AnManager {
	//動画のFPS
	unsigned short fps;
	//動画を書き込む変数
	cv::VideoWriter *writer;
public:
	AnManager();
	AnManager(unsigned short fps);
	unsigned short getFPS();
	void WriteVideo(cv::Mat frame);
};

#endif
