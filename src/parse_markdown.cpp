/*
 * parse_markdown.cpp
 *
 *  Created on: 30 oct. 2014
 *      Author: cameron
 */

#include <fstream>
#include <iostream>
#include <string>
#include <regex>

#include "parse_markdown.h"

using namespace std;

/**
 * Regex
 */
regex italic_regex("[<>a-zA-Z0-9 ]*\\*([a-zA-Z0-9 ]*)\\*[<>a-zA-Z0-9 ]*");
regex bold_regex("\\*\\*(.*)\\*\\*");
regex list_regex("\\*\t(.*)");

/**
 * Replacement strings
 */

/**
 * Bool
 */
bool paragraph = false;
bool entry = false;
bool italic = false;
bool bold = false;

void str_replace( string &s, string &search, string &replace );

string parseline(string& line) {

	string stringToReturn = line;

	string toReplace;

	string search;

	smatch match;

	while (regex_search(stringToReturn, match, bold_regex) || regex_search(stringToReturn, match, italic_regex)) {
		if (regex_search(stringToReturn, match, bold_regex)) {
			toReplace += "<b>";
			toReplace += match[1];
			toReplace += "</b>";
			search += "**";
			search += match[1];
			search += "**";
			str_replace(stringToReturn, search, toReplace);
		}
		toReplace = "";
		search = "";
		if (regex_search(stringToReturn, match, italic_regex)) {
			toReplace += "<i>";
			toReplace += match[1];
			toReplace += "</i>";
			search += "*";
			search += match[1];
			search += "*";
			str_replace(stringToReturn, search, toReplace);
		}
	}

	return stringToReturn;

}

void str_replace( string &s, string &search, string &replace ) {
	for( size_t pos = 0; ; pos += replace.length() )
	{
		pos = s.find( search, pos );
		if( pos == string::npos )
			break;

		s.erase( pos, search.length() );
		s.insert( pos, replace );
	}
}
