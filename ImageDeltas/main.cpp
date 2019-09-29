#include "ImageDeltas.h"

using namespace std;


namespace po = boost::program_options;

po::variables_map parse_ops(int argc, char** argv)
{
	po::variables_map vm;

	try {
		po::options_description desc("Usage:");
		desc.add_options()
			("help,h", "produce help message")
			("first,f", po::value<std::string>()->required(), "set original image file")
			("second,s", po::value<std::string>()->required(), "set second image file image file")
			;

		po::store(po::parse_command_line(argc, argv, desc), vm);
		if (vm.count("help")) {
			cout << desc << "\n";
			return 0;
		}

		po::notify(vm);


	}
	catch (exception& e)
	{
		cerr << "options parsing failed: " << e.what() << endl;
		exit(EXIT_FAILURE);
	}

	return vm;
}

int main(int argc, char** argv)
{
	cout << "Using OpenCV version " << CV_VERSION << endl;
	auto vm = parse_ops(argc, argv);

	cout << "Computing deltas between " << vm["first"].as<string>() << " and " << vm["second"].as<string>() << endl;

	auto first = LoadPngOrDie(vm["first"].as<string>());
	auto second = LoadPngOrDie(vm["second"].as<string>());

	if (first.rows != second.rows || first.cols != second.cols)
	{
		cerr << "images are not of the same dimensions" << endl;
		exit(EXIT_FAILURE);
	}

	LocateDifferences(first, second);

	return 0;
}