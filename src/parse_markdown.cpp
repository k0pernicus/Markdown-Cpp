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
regex url_regex("\\[(.*)\\]\\((.*)\\)");
regex list_regex("\\*\t(.*)");

/*
 * H1, H2 and H3 style headers regexs
 */
regex h1_regex("# (.*)");
regex h2_regex("## (.*)");
regex h3_regex("### (.*)");

/**
 * Bool
 */
bool paragraph = false;
bool entry = false;
bool italic = false;
bool bold = false;

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

bool search_headers_style(string& stringToReturn, smatch& match);

string parseline(string& line) {

	string stringToReturn = line;

	string toReplace;

	string search;

	smatch match;

	while (regex_search(stringToReturn, match, bold_regex) || regex_search(stringToReturn, match, italic_regex)
			|| regex_search(stringToReturn, match, url_regex) || search_headers_style(stringToReturn, match)) {
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
		toReplace = "";
		search = "";
		if (regex_search(stringToReturn, match, url_regex)) {
			toReplace +="<a href=\"";
			toReplace += match[2];
			toReplace += "\">";
			toReplace += match[1];
			toReplace += "</a>";
			search += "[";
			search += match[1];
			search += "]";
			search += "(";
			search += match[2];
			search += ")";
			str_replace(stringToReturn, search, toReplace);
		}
		toReplace = "";
		search = "";
		if (search_headers_style(stringToReturn, match)) {
			if (regex_search(stringToReturn, match, h3_regex)) {
				toReplace += "<h3>";
				toReplace += match[1];
				toReplace += "</h3>";
				search += "### ";
				search += match[1];
				str_replace(stringToReturn, search, toReplace);
			}
			if (regex_search(stringToReturn, match, h2_regex)) {
				toReplace += "<h2>";
				toReplace += match[1];
				toReplace += "</h2>";
				search += "## ";
				search += match[1];
				str_replace(stringToReturn, search, toReplace);
			}
			if (regex_search(stringToReturn, match, h1_regex)) {
				toReplace += "<h1>";
				toReplace += match[1];
				toReplace += "</h1>";
				cout << "toReplace : " << toReplace << endl;
				search += "# ";
				search += match[1];
				cout << "search : " << search << endl;
				str_replace(stringToReturn, search, toReplace);
			}
		}
	}

	return stringToReturn;

}

bool search_headers_style(string& stringToReturn, smatch& match) {

	if (regex_search(stringToReturn, match, h1_regex) || regex_search(stringToReturn, match, h2_regex)
			|| regex_search(stringToReturn, match, h3_regex))
		return true;
	return false;

}
