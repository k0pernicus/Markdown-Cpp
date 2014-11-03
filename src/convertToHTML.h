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
	bool verification_bold(string& actualString);

	bool verification_italic(string& actualString);

	bool verification_url(string& actualString);

	bool verification_img(string& actualString);

	bool verification_non_ordonate_list(string& actualString);

	bool verification_ordonate_list(string& actualString);

	bool verification_headers(string& actualString);

	bool verification_title(string& actualString);

	string parseline(string& line);

	void str_replace( string &s, string &search, string &replace );

	bool search_headers_style(string& stringToReturn, smatch& match);

};

#endif /* SRC_CONVERTTOHTML_ */
