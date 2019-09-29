# CMakeList.txt : CMake project for ImageDeltas, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)
find_package(OpenCV CONFIG REQUIRED)
find_package(Boost REQUIRED COMPONENTS program_options)

# benchmarking
find_package(benchmark CONFIG REQUIRED)

# Add source to this project's executable.
add_executable (ImageDeltas "main.cpp" "ImageDeltas.cpp" "ImageDeltas.h")
set_property(TARGET ImageDeltas PROPERTY CXX_STANDARD 17)
set_property(TARGET ImageDeltas PROPERTY CXX_STANDARD_REQUIRED ON)

target_link_libraries(ImageDeltas PRIVATE opencv_core opencv_imgproc opencv_imgcodecs) #opencv_ml opencv_dnn opencv_core opencv_flann)
target_link_libraries(ImageDeltas PRIVATE Boost::program_options)

# TODO: Add tests and install targets if needed.
add_executable(ImageBenchmarks "ImageDeltas.cpp" "ImageDeltas.h" "benchmarks.cpp")
set_property(TARGET ImageBenchmarks PROPERTY CXX_STANDARD 17)
set_property(TARGET ImageBenchmarks PROPERTY CXX_STANDARD_REQUIRED ON)
target_link_libraries(ImageBenchmarks PRIVATE benchmark::benchmark benchmark::benchmark_main)
target_link_libraries(ImageBenchmarks PRIVATE opencv_core opencv_imgproc opencv_imgcodecs) #opencv_ml opencv_dnn opencv_core opencv_flann)
target_link_libraries(ImageBenchmarks PRIVATE Boost::program_options)