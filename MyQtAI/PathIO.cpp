
#include "PathIO.h"

#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>

#include <sstream> // std::stringstream

// split string
std::vector<std::string>& split(const std::string &s, char delim, std::vector<std::string> &elems)
{
	std::stringstream ss(s);
	std::string item;
	while (std::getline(ss, item, delim))
	{
		elems.push_back(item);
	}
	return elems;
}

// split string
std::vector<std::string> split(const std::string &s, char delim)
{
	std::vector<std::string> elems;
	split(s, delim, elems);
	return elems;
}


PathIO::PathIO()
{
}

PathIO::~PathIO()
{
}

void PathIO::SavePath(std::vector<APath> paths, std::string filename)
{
	std::ofstream f;
	f.open(filename);

	for (size_t a = 0; a < paths.size(); a++)
	{
		APath aPath = paths[a];
		for (size_t b = 0; b < aPath.points.size(); b++)
		{
			f << std::setprecision(20) << aPath.points[b].x << " " << std::setprecision(20) << aPath.points[b].y;
			if (b < aPath.points.size() - 1) { f << " "; }
		}
		f << "\n";
	}


	f.close();
}

std::vector<APath> PathIO::LoadPath(std::string filename)
{
	std::vector<APath> paths;

	std::ifstream myfile(filename);
	while (!myfile.eof())
	{
		APath aPath;

		std::string line;
		std::getline(myfile, line);

		std::vector<std::string> arrayStr = split(line, ' ');

		if (arrayStr.size() < 2) { continue;  }

		size_t halfLength = arrayStr.size() / 2;

		for (size_t a = 0; a < halfLength; a++)
		{
			int idx = a * 2;
			double x = std::stod(arrayStr[idx]);
			double y = std::stod(arrayStr[idx+1]);
			aPath.points.push_back(AVector(x, y));
		}

		//std::cout << aPath.points.size() << "\n";

		aPath.isClosed = true;
		paths.push_back(aPath);
	}

	myfile.close();

	return paths;
}