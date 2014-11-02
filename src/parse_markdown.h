/*
 * parse_markdown.h
 *
 *  Created on: 30 oct. 2014
 *      Author: cameron
 */

#ifndef SRC_PARSE_MARKDOWN_H_
#define SRC_PARSE_MARKDOWN_H_

#include <string>
#include <regex>

using namespace std;

string parseline(string& line);

void str_replace( string &s, string &search, string &replace );

bool search_headers_style(string& stringToReturn, smatch& match);

#endif /* SRC_PARSE_MARKDOWN_H_ */
