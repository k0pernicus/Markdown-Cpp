/*
 * main.cpp
 *
 *  Created on: 30 oct. 2014
 *      Author: cameron
 */
#include <string.h>
#include <fstream>
#include <string>
#include <iostream>

#include "Md_file.h"
#include "parse_markdown.h"

using namespace std;

string changeExtensionFile(string& file_name);

int main(int argc, char* argv[]) {

	string file_name;

	string line;
	string parsed_line;

	cout << "Welcome to Markdown-Cpp" << endl;

	cout << endl;

	cout << "Please to enter a file name" << endl;

	cin >> file_name;

	Md_file* md_file = new Md_file(file_name);

	ofstream outfile (changeExtensionFile(file_name));

	if (!md_file->openFile()) {
		cout << "File not found..." << endl;
		exit(EXIT_FAILURE);
	}

	cout << "File opened" << endl;

	cout << endl;

	outfile << "<p>" << endl;

	while (getline(md_file->getFile(), line)) {
		outfile << parseline(line) << endl;
	}

	outfile << "</p>" << endl;

	md_file->closeFile();

	outfile.close();

	cout << endl;

	delete md_file;

}

string changeExtensionFile(string& file_name) {
	return file_name.substr(0, (file_name.rfind(".") + 1)) + "html";
}
