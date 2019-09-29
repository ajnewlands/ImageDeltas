//
// ImageDeltas : Uses OpenCV to compute the regions of difference between two images
//

#include "ImageDeltas.h"

using namespace std;


cv::Mat LoadPngOrDie(std::string path)
{
	auto image = cv::imread(path, cv::IMREAD_UNCHANGED);
	if (image.empty())
	{
		cerr << "Failed to load PNG from " << path << endl;
		exit(EXIT_FAILURE);
	}
	else
	{
		cout << "Loaded image of dims " << image.rows << " x " << image.cols << endl;
	}
	return image;
}

vector<uchar> EncodeDifference(cv::Mat& first, cv::Mat& second, int compression_level)
{
	vector<uchar> output;
	vector<int> params;
	params.push_back(cv::IMWRITE_PNG_COMPRESSION);
	params.push_back(compression_level);
	auto deltas = cv::Mat(first.rows, first.cols, first.type());
	cv::bitwise_xor(first, second, deltas);
	cv::imencode(".png", deltas, output, params);
	return output;
}

void OpenCV_Xor(cv::Mat& first, cv::Mat& second)
{
	auto deltas = cv::Mat(first.rows, first.cols, first.type());
	cv::bitwise_xor(first, second, deltas);
}

// Note element size will be 3 (BGR)
void LocateDifferences(cv::Mat& first, cv::Mat& second)
{
	vector<int> params;
	params.push_back(cv::IMWRITE_PNG_COMPRESSION);
	params.push_back(9);
	auto deltas = cv::Mat(first.rows, first.cols, first.type());
	cv::bitwise_xor(first, second, deltas);
	cv::imwrite("C:\\tmp\\deltas.png", deltas, params);
	cv::imwrite("C:\\tmp\\first-new.png", first,params);
	cv::bitwise_xor(first, deltas, first);
	cv::imwrite("C:\\tmp\\updated.png", first, params);

}

vector<uchar> EncodePng(cv::Mat& data, int compression_level)
{
	vector<uchar> output;
	vector<int> params;
	params.push_back(cv::IMWRITE_PNG_COMPRESSION);
	params.push_back(compression_level);
	cv::imencode(".png", data, output, params);

	return output;
}


