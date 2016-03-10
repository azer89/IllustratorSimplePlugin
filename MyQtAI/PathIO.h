

#include <vector>
#include "APath.h"
#include <cstring>

class PathIO
{
public:
	PathIO();
	~PathIO();

	void SavePath(std::vector<APath> paths, std::string filename);
	std::vector<APath> LoadPath(std::string filename);

};
