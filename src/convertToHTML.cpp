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

#include "convertToHTML.h"

using namespace std;

/**
 * Regex
 */
//*some tex*
regex italic_regex(".*\\*(.*)\\*.*");
//**some text**
regex bold_regex(".*\\*\\*(.*)\\*\\*.*");
//*		Some text
regex list_regex("\\*\t(.*)");
//1.	Some text
regex ordonate_list_regex("[[digit]]\\.\t(.*)");
//[some text](URL)
regex url_regex("[^!]*\\[(.*)\\]\\((.*)\\)");
//![some text](URL)
regex img_regex("!\\[(.*)\\]\\((.*)\\)");

/*
 * H1, H2 and H3 style headers regexs
 */
//# some text
regex h1_regex("# (.*)");
//## some text
regex h2_regex("## (.*)");
//### some text
regex h3_regex("### (.*)");
//#### some text
regex h4_regex("#### (.*)");
//##### some text
regex h5_regex("##### (.*)");
//###### some text
regex h6_regex("###### (.*)");

// Some text
// =========
regex equals_title("[^a-zA-Z0-9]\\=+[^a-zA-Z0-9]");

// Some text
// ---------
regex dash_title("[^a-zA-Z0-9]\\-+[^a-zA-Z0-9]");

extern bool need_paragraph;
extern bool current_paragraph;
extern bool current_list;

void convertToHTML::str_replace( string &s, string &search, string &replace ) {
	for( size_t pos = 0; ; pos += replace.length() )
	{
		pos = s.find( search, pos );
		if( pos == string::npos )
			break;

		s.erase( pos, search.length() );
		s.insert( pos, replace );
	}
}

bool convertToHTML::search_headers_style(string& stringToReturn, smatch& match);

void convertToHTML::verification_bold(string& actualString, const string& PreviousString) {

	//**some text**
	regex bold_regex("\\*\\*(.*)\\*\\*");

	smatch match;

	string toReplace, search;

	if (regex_search(actualString, match, bold_regex)) {
		if (current_list) {
			current_list = false;
			actualString += "</ul>";
		}
		if (need_paragraph) {
			toReplace += "<p>";
			need_paragraph = false;
			current_paragraph = true;
		}
		toReplace += "<b>";
		toReplace += match[1];
		toReplace += "</b>";
		search += "**";
		search += match[1];
		search += "**";
		str_replace(actualString, search, toReplace);
	}
	else {
		if (debug) {
			cout << actualString << ": No replacement (bold)" << endl;
		}
	}

}

string convertToHTML::parseline(string& line) {

	string stringToReturn = line;

	string toReplace;

	string search;

	smatch match;

	if (stringToReturn.empty() && current_list) {
		current_list = false;
		stringToReturn += "</ul>";
	}

	if ((stringToReturn.empty() == false) && !(regex_search(stringToReturn, match, bold_regex) || regex_search(stringToReturn, match, italic_regex)
			|| regex_search(stringToReturn, match, url_regex) || search_headers_style(stringToReturn, match)
			|| regex_search(stringToReturn, match, img_regex)
			|| regex_search(stringToReturn, match, list_regex))) {
		if (current_list) {
			current_list = false;
			toReplace += "</ul>";
			toReplace += stringToReturn;
			stringToReturn = toReplace;
		}
		if (need_paragraph) {
			toReplace += "<p>";
			toReplace += stringToReturn;
			stringToReturn = toReplace;
			need_paragraph = false;
			current_paragraph = true;
		}
	}

	if (stringToReturn.empty() && current_paragraph) {
		stringToReturn += "</p>";
		need_paragraph = true;
		current_paragraph = false;
	}

	while (regex_search(stringToReturn, match, bold_regex) || regex_search(stringToReturn, match, italic_regex)
			|| regex_search(stringToReturn, match, url_regex) || search_headers_style(stringToReturn, match)
			|| regex_search(stringToReturn, match, img_regex)
			|| regex_search(stringToReturn, match, list_regex)) {
		verification_bold(stringToReturn);
		verification_italic(stringToReturn);
		verification_non_ordonate_list(stringToReturn);
		verification_img(stringToReturn);
		verification_url(stringToReturn);
		verification_headers(stringToReturn);
	}

	return stringToReturn;

}

bool convertToHTML::search_headers_style(string& stringToReturn, smatch& match) {

	if (regex_search(stringToReturn, match, h1_regex) || regex_search(stringToReturn, match, h2_regex)
			|| regex_search(stringToReturn, match, h3_regex))
		return true;
	return false;

}
