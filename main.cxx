#include <opencv2/opencv.hpp>
#include <vector>
#include <iostream>
#include <cmath>

using P2F = cv::Point2f;
using Image = cv::Mat;
using u32_t = unsigned int;

void MoveImage(cv::VideoWriter & writer, const Image & base, const Image & move_image, P2F start, P2F end, u32_t ms);
void PutImage(const cv::Mat & base, const cv::Mat & in, cv::Mat & result, const cv::Point2f p0, const cv::Point2f p1);
float PF2PFDistance(P2F p1, P2F p2);

int main(int argc, char **argv){
	cv::Mat img1(500, 500, CV_8UC3, cv::Scalar(255, 255, 255));
	cv::Mat img2 = cv::imread(argv[1]);
	cv::VideoWriter writer("test2.avi", CV_FOURCC('M', 'J', 'P', 'G'), 60, cv::Size(img1.cols, img1.rows), true);

	MoveImage(writer, img1, img2, P2F(0, 0), P2F(100, 100), 1000);

/*
	cv::Mat img3 = img1.clone();
	PutImage(img1, img2, img3, cv::Point2f(0, 0), cv::Point2f(img2.cols, img2.rows));
	cv::imshow("window", img3);
	cv::waitKey();
	*/
	
      return 0;
}

void PutImage(const cv::Mat & base, const cv::Mat & in, cv::Mat & result, const cv::Point2f p0, const cv::Point2f p1){
      
	base.copyTo(result);

	//３組の対応点を作成
	std::vector<cv::Point2f> src, dst;
	src.push_back(cv::Point2f(0, 0));
	src.push_back(cv::Point2f(in.cols, 0));
	src.push_back(cv::Point2f(in.cols, in.rows));

	dst.push_back(p0);
	dst.push_back(cv::Point2f(p1.x, p0.y));
	dst.push_back(p1);

	//前景画像の変形行列
	cv::Mat mat = cv::getAffineTransform(src, dst);

	//アフィン変換の実行
	cv::warpAffine(in, result, mat, result.size(), CV_INTER_LINEAR, cv::BORDER_TRANSPARENT);

}

/*
 *=======================================================================================
 *MoveImage関数
 *画像を水平移動させる関数
 *引数
 *cv::VideoWriter writer
 *=>書き込む動画
 *const cv::Mat & base
 *=>背景となる画像
 *const cv::Mat & move_image
 *=>平行移動させる画像
 *cv::Point2f start
 *=>開始座標cv::Point2f end
 *int time
 *=>何秒で移動するか
 *=======================================================================================
 */
void MoveImage(cv::VideoWriter & writer, const Image & base, const Image & move_image, P2F start, P2F end, u32_t ms){
	int distance, times;
	float angle, step, stepx, stepy, space;

      //二点間の距離
	distance = PF2PFDistance(start, end);
	//動かす間隔(ミリ秒)
	space = ms / distance;
	space /= (float)(1000.0 / 60.0);

	//一歩の長さ
	step = 1 / (float)space;
	//動かす回数
	times = distance / step;
	//角度
	angle = std::atan((end.y - start.y) / (end.x - start.x));
	//xy
	stepx = step * std::cos(angle);
	stepy = step * std::sin(angle);

	std::cout << stepx << ":" << stepy << "=x:y" << std::endl;
	std::cout << space << std::endl;

	for(int i = 0;i < times;i++){
		std::cout << i << "/" << times << std::endl;
		Image result = base.clone();
		PutImage(base, move_image, result, P2F(start.x, start.y), P2F(start.x + move_image.cols, start.y + move_image.rows));
		start.x += stepx;
		start.y += stepy;
		writer << result;
	}
}

float PF2PFDistance(P2F p1, P2F p2){
	return std::sqrt(std::pow(p1.x - p2.x, 2) + std::pow(p1.y - p2.y, 2));
}
