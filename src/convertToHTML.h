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

	using namespace std;

	void convertToHTML::verification_bold(string& actualString, const string& PreviousString);

	string parseline(string& line);

	void str_replace( string &s, string &search, string &replace );

	bool search_headers_style(string& stringToReturn, smatch& match);

};

#endif /* SRC_CONVERTTOHTML_ */
