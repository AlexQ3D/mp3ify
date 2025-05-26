#include <iostream>
#include <string>
#include <filesystem>

using namespace std;
namespace fs = std::filesystem;

int main(int argc, char *argv[]) {	
	// Scrape the input file for it's name/original path
	string inputFile = fs::absolute(argv[1]).string();
	string inputFileName = fs::path(inputFile).stem().string();
	
	string appDirectory = fs::absolute(argv[0]).parent_path().string();
	string exportDirectory = appDirectory + "/export/";
	
	// Fix some weird stuff with windows where if we drag a file in from a DIFFERENT directory, the program thinks we're running in that directory
	string ffmpegExe = fs::absolute(appDirectory + "/tools/ffmpeg.exe").string();
	
	// Build the command we're gonna send to ffmpeg
	string cmd = ffmpegExe + " -sample_fmt s16 -r 44100 -y -i \"" + inputFile + "\" -vn \"" + exportDirectory + inputFileName + ".wav\"";
	
	// Print the command, handy for debugging purposes
	cout << cmd << "\n";
	
	// Execute the command
	system(cmd.c_str());
	return 0;
}
