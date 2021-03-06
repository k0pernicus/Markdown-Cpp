/*
 * Md_file.cpp
 *
 *  Created on: 30 oct. 2014
 *      Author: cameron
 */
#include <fstream>
#include <iostream>
#include <string>

#include "Md_file.h"

using namespace std;

Md_file::Md_file(string file_name){
	this->file_name = file_name;
}

Md_file::~Md_file(){
	cout << "Md_file destructor" << endl;
}

ifstream& Md_file::getFile(void) {
	return file;
}

bool Md_file::openFile(void){
	const char* c_file_name = (this->file_name).c_str();
	(this->file).open(c_file_name, ios::in);
	return ((this->file).is_open());
}

void Md_file::closeFile(){
	(this->file).close();
}
