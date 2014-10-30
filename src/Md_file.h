/*
 * Md_file.h
 *
 *  Created on: 30 oct. 2014
 *      Author: cameron
 */

#ifndef SRC_MD_FILE_H_
#define SRC_MD_FILE_H_

#include <fstream>
#include <iostream>

using namespace std;

class Md_file {

private:
	string file_name;
	ifstream file;

public:
	Md_file(string file_name);
	~Md_file(void);
	bool openFile(void);
	void closeFile(void);

};

#endif /* SRC_MD_FILE_H_ */
