#ifndef SYSTEMPARAMS_H
#define SYSTEMPARAMS_H

#include <iostream>

/**
* Reza Adhitya Saputra
* radhitya@uwaterloo.ca
* February 2016
*/

class SystemParams
{
public:
    SystemParams();

public:
    static std::string v_shader_file;
    static std::string f_shader_file;
	static std::string temp_png_location;

};

#endif // SYSTEMPARAMS_H
