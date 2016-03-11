

#include <vector>
#include "APath.h"
#include <cstring>

class PathIO
{
public:
	PathIO();
	~PathIO();

	// save to a file
	void SavePath(std::vector<APath> paths, std::string filename);
	
	// load from a file
	std::vector<APath> LoadPath(std::string filename);

};
