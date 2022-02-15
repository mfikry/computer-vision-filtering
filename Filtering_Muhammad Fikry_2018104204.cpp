#include <iostream>
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/core.hpp"
#include <fstream>

using namespace cv;
using std::cout;
using std::endl;

Point anchor;
int kernel_size = 11;

int main(int argc, char** argv) {
	Mat src = imread("media/me.jpg");
	resize(src, src, Size(440, 540));
	if (src.empty()) {
		cout << "Gambar tidak ditemukan !" << endl;
		return -1;
	}

	imshow("Original", src);

	Mat homogeneous, gaussian, median, bilateral;
	// Homogeneous Filter
	anchor = Point(-1, 1);
	blur(src, homogeneous, Size(kernel_size, kernel_size), anchor);

	// Gaussian Filter
	GaussianBlur(src, gaussian, Size(kernel_size, kernel_size), 0, 0);

	// Median Filter
	medianBlur(src, median, 11);

	// Bilateral Filter
	// Parameter (src, dest, diameter, sigmacolor, sigmaspace)
	bilateralFilter(src, bilateral, 25, 25 * 2, 25 / 2);

	imshow("homogenous Filter", homogeneous);
	imshow("Gaussian Filter", gaussian);
	imshow("Median Filter", median);
	imshow("Bilateral Filter", bilateral);
	

	// SHARPEN

	// Filter 2D
	Mat sharp;
	Mat sharpening_kernel = (Mat_<double>(3, 3) << -1, -1, -1,
		-1, 9, -1,
		-1, -1, -1);
	filter2D(src, sharp, -1, sharpening_kernel);
	imshow("Sharpening Filter", sharp);

	// addWeighted
	Mat sharp_sub;
	addWeighted(src, 4, gaussian, -4, 0, sharp_sub);
	imshow("Weighted Sharpening Filter", sharp_sub);

	waitKey(0);
	return 0;
}