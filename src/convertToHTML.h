/*
 * parse_markdown.h
 *
 *  Created on: 30 oct. 2014
 *      Author: cameron
 */

#ifndef SRC_CONVERTTOHTML_
#define SRC_CONVERTTOHTML_

#include <string>
#include <regex>

using namespace std;

class convertToHTML {

public:
	void verification_bold(string& actualString);

	void verification_italic(string& actualString);

	void verification_url(string& actualString);

	void verification_img(string& actualString);

	void verification_non_ordonate_list(string& actualString);

	void verification_ordonate_list(string& actualString);

	void verification_headers(string& actualString);

	void verification_title(string& actualString);

	string parseline(string& line);

	void str_replace( string &s, string &search, string &replace );

	bool search_headers_style(string& stringToReturn, smatch& match);

};

#endif /* SRC_CONVERTTOHTML_ */
