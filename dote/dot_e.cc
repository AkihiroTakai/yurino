#include <opencv2/opencv.hpp>

int main(int argc, char **argv){
	if(argc == 1){
		std::cout << "INPUT IMAGE PATH!!!!!!! (#ﾟДﾟ)" << std::endl;
		return -1;
	}

	cv::Mat src_img = cv::imread(argv[1]);

	if(src_img.empty()){
		std::cout << "BAD IMAGE PATH!!!!!!! (#ﾟДﾟ)" << std::endl;
		return -1;
	}

	cv::Mat dst_img = src_img.clone();

      
	for(int x = 0;x + 10 < dst_img.cols;x += 10){
		for(int y = 0;y + 10 < dst_img.rows;y += 10){
			cv::Rect roi(x, y, 10, 10);
			cv::Mat edit = dst_img(roi);
			int r, g, b;
			r = g = b = 0;
		      for(int i = 0;i < 10;i++){
				cv::Vec3b *src = edit.ptr<cv::Vec3b>(i);
				for(int j = 0;j < 10;j++){
					b += src[j][0];
					g += src[j][1];
					r += src[j][2];
				}
			}

			for(int i = 0;i < 10;i++){
				cv::Vec3b *src = edit.ptr<cv::Vec3b>(i);
				for(int j = 0;j < 10;j++){
					src[j][0] = b / 100;
					src[j][1] = g / 100;
					src[j][2] = r / 100;
				}
			}
		}
	}

	cv::imshow("dst", dst_img);
	cv::waitKey();

	return 0;
	
}
