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
regex italic_regex(".*\\*([a-zA-Z0-9ÉÈÊËÀÔÖÇéèêëàôöç ]+)\\*{1}");
//**some text**
regex bold_regex("\\*\\*([a-zA-Z0-9ÉÈÊËÀÔÖÇéèêëàôöç* ]+)\\*\\*.*");
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

bool convertToHTML::verification_bold(string& actualString) {

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
		cout << "Replace " << actualString << " by " << toReplace << endl;
		str_replace(actualString, search, toReplace);
		return true;
	}
	return false;
}

bool convertToHTML::verification_italic(string& actualString) {

	smatch match;

	string toReplace, search;

	if (regex_search(actualString, match, italic_regex)) {
		if (current_list) {
			current_list = false;
			toReplace += "</ul>";
		}
		if (need_paragraph) {
			toReplace += "<p>";
			need_paragraph = false;
			current_paragraph = true;
		}
		toReplace += "<i>";
		toReplace += match[1];
		toReplace += "</i>";
		search += "*";
		search += match[1];
		search += "*";
		cout << "Replace " << actualString << " by " << toReplace << endl;
		str_replace(actualString, search, toReplace);
		return true;
	}
	return false;
}

bool convertToHTML::verification_non_ordonate_list(string& actualString){

	smatch match;

	string toReplace, search;

	if (regex_search(actualString, match, list_regex)) {
		if (!current_list) {
			current_list = true;
			toReplace += "<ul>";
		}
		toReplace += "<li>";
		toReplace += match[1];
		toReplace += "</li>";
		search += "*	";
		search += match[1];
		cout << "Replace " << actualString << " by " << toReplace << endl;
		str_replace(actualString, search, toReplace);
		return true;
	}
	return false;
}

bool convertToHTML::verification_img(string& actualString) {

	smatch match;

	string toReplace, search;

	if (regex_search(actualString, match, img_regex)) {
		if (current_list) {
			current_list = false;
			actualString += "</ul>";
		}
		toReplace +="<img src=\"";
		toReplace += match[2];
		toReplace += "\"";
		toReplace += " alt=\"";
		toReplace += match[1];
		toReplace += "\">";
		search += "![";
		search += match[1];
		search += "]";
		search += "(";
		search += match[2];
		search += ")";
		cout << "Replace " << actualString << " by " << toReplace << endl;
		str_replace(actualString, search, toReplace);
		return true;
	}
	return false;
}

bool convertToHTML::verification_url(string& actualString) {

	smatch match;

	string toReplace, search;

	if (regex_search(actualString, match, url_regex)) {
		if (current_list) {
			current_list = false;
			actualString += "</ul>";
		}
		if (need_paragraph) {
			toReplace += "<p>";
			need_paragraph = false;
			current_paragraph = true;
		}
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
		cout << "Replace " << actualString << " by " << toReplace << endl;
		str_replace(actualString, search, toReplace);
		return true;
	}
	return false;
}

bool convertToHTML::verification_headers(string& actualString) {

	smatch match;

	string toReplace, search;

	if (search_headers_style(actualString, match)) {
		if (current_list) {
			current_list = false;
			actualString += "</ul>";
		}
		if (regex_search(actualString, match, h3_regex)) {
			toReplace += "<h3>";
			toReplace += match[1];
			toReplace += "</h3>";
			search += "### ";
			search += match[1];
			cout << "Replace " << actualString << " by " << toReplace << endl;
			str_replace(actualString, search, toReplace);
		}
		if (regex_search(actualString, match, h2_regex)) {
			toReplace += "<h2>";
			toReplace += match[1];
			toReplace += "</h2>";
			search += "## ";
			search += match[1];
			cout << "Replace " << actualString << " by " << toReplace << endl;
			str_replace(actualString, search, toReplace);
		}
		if (regex_search(actualString, match, h1_regex)) {
			toReplace += "<h1>";
			toReplace += match[1];
			toReplace += "</h1>";
			search += "# ";
			search += match[1];
			cout << "Replace " << actualString << " by " << toReplace << endl;
			str_replace(actualString, search, toReplace);
		}
		return true;
	}
	return false;
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
		if (verification_bold(stringToReturn))
			continue;
		if (verification_italic(stringToReturn))
			continue;
		if (verification_non_ordonate_list(stringToReturn))
			continue;
		if (verification_img(stringToReturn))
			continue;
		if (verification_url(stringToReturn))
			continue;
		if (verification_headers(stringToReturn))
			continue;
	}

	return stringToReturn;

}

bool convertToHTML::search_headers_style(string& stringToReturn, smatch& match) {

	if (regex_search(stringToReturn, match, h1_regex) || regex_search(stringToReturn, match, h2_regex)
			|| regex_search(stringToReturn, match, h3_regex))
		return true;
	return false;

}
