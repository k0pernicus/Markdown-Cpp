/*
 * main.cpp
 *
 *  Created on: 30 oct. 2014
 *      Author: cameron
 */
#include <fstream>
#include <string>
#include <iostream>

#include "Md_file.h"
#include "parse_markdown.h"

using namespace std;

int main(int argc, char* argv[]) {

	string file_name;

	string line;
	string parsed_line;

	cout << "Welcome to Markdown-Cpp" << endl;

	cout << endl;

	cout << "Please to enter a file name" << endl;

	cin >> file_name;

	Md_file* md_file = new Md_file(file_name);

	if (!md_file->openFile()) {
		cout << "File not found..." << endl;
		exit(EXIT_FAILURE);
	}

	cout << "File opened" << endl;

	cout << endl;

	while (getline(md_file->getFile(), line)) {
		cout << parseline(line) << endl;
	}

	cout << endl;

	md_file->closeFile();

	cout << endl;

	delete md_file;

}
