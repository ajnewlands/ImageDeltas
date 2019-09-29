#include <benchmark/benchmark.h>
#include "ImageDeltas.h"

using namespace std;

static void BM_OpenCV_XOR(benchmark::State& state) {
	auto image1 = cv::imread("C:\\tmp\\first.png", cv::IMREAD_UNCHANGED);
	auto image2 = cv::imread("C:\\tmp\\second.png", cv::IMREAD_UNCHANGED);

	if (image1.empty() || image2.empty()) {
		cerr << "Failed loading images" << endl;
		exit(EXIT_FAILURE);
	}

	for (auto _ : state) {
		OpenCV_Xor(image1, image2);
	}
}

static void BM_EncodeDelta(benchmark::State& state) {
	auto image1 = cv::imread("C:\\tmp\\first.png", cv::IMREAD_UNCHANGED);
	auto image2 = cv::imread("C:\\tmp\\second.png", cv::IMREAD_UNCHANGED);
	
	if (image1.empty() || image2.empty()) {
		cerr << "Failed loading images" << endl;
		exit(EXIT_FAILURE);
	}

	for (auto _ : state) {
		auto in_size = image2.rows * image2.cols * image2.elemSize();
		auto png = EncodeDifference(image1, image2, state.range(0));
		auto out_size = png.size();
		state.counters["in-sz"] = in_size;
		state.counters["out-sz"] = out_size;
		state.counters["compress"] = out_size / (float)in_size * 100;
	}	
}

static void BM_EncodePng(benchmark::State& state) {
	// Perform setup here
	auto image = cv::imread("C:\\tmp\\second.png", cv::IMREAD_UNCHANGED);
	if (image.empty())
	{
		cerr << "Failed to load PNG " << endl;
		exit(EXIT_FAILURE);
	}

	for (auto _ : state) {
		// This code gets timed
		auto in_size = image.rows * image.cols * image.elemSize();
		auto png = EncodePng(image, state.range(0));
		auto out_size = png.size();
		state.counters["in-sz"] = in_size;
		state.counters["out-sz"] = out_size;
		state.counters["compress"] = out_size / (float)in_size * 100;
	}
}
// Register the function as a benchmark

BENCHMARK(BM_EncodePng)->DenseRange(1, 9, 1);
BENCHMARK(BM_EncodeDelta)->DenseRange(1, 9, 1);
BENCHMARK(BM_OpenCV_XOR);
// Run the benchmark
BENCHMARK_MAIN();