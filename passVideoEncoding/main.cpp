#include <string>
#include <iostream>
#include <cstdlib>

int main(int argc,char* argv[])
{
	if(argc < 2)
	{
		std::cout << "no input file" << std::endl;
		return 1;
	}
	std::string fileName = argv[1];
	std::string cmdline1 = "ffmpeg -i " + fileName + " -c:v libx264 -preset slow -b:v 10000k -framerate 60 -pass 1 -an -f mp4 -y NUL";
	std::string cmdline2 = "ffmpeg -i " + fileName + " -c:v libx264 -preset slow -b:v 10000k -framerate 60 -pass 2 -c:a copy " + fileName + "_0.mp4";
	system(cmdline1.c_str());
	system(cmdline2.c_str());
	return 0;
}