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
//*some tex*
regex italic_regex("[<>a-zA-Z0-9 ]*\\*([a-zA-Z0-9 ]*)\\*[<>a-zA-Z0-9 ]*");
//**some text**
regex bold_regex("\\*\\*(.*)\\*\\*");
//*		Some text
regex list_regex("\\*\t(.*)");
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

extern bool need_paragraph;
extern bool current_paragraph;
extern bool current_list;

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
		if (regex_search(stringToReturn, match, bold_regex)) {
			if (current_list) {
				current_list = false;
				stringToReturn += "</ul>";
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
			str_replace(stringToReturn, search, toReplace);
		}
		toReplace = "";
		search = "";
		if (regex_search(stringToReturn, match, italic_regex)) {
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
			str_replace(stringToReturn, search, toReplace);
		}
		toReplace = "";
		search = "";
		if (regex_search(stringToReturn, match, list_regex)) {
			if (!current_list) {
				current_list = true;
				toReplace += "<ul>";
			}
				toReplace += "<li>";
				toReplace += match[1];
				toReplace += "</li>";
				search += "*	";
				search += match[1];
				str_replace(stringToReturn, search, toReplace);
		}
		toReplace = "";
		search = "";
		if (regex_search(stringToReturn, match, img_regex)) {
			if (current_list) {
				current_list = false;
				stringToReturn += "</ul>";
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
			str_replace(stringToReturn, search, toReplace);
		}
		toReplace = "";
		search = "";
		if (regex_search(stringToReturn, match, url_regex)) {
			if (current_list) {
				current_list = false;
				stringToReturn += "</ul>";
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
			str_replace(stringToReturn, search, toReplace);
		}
		toReplace = "";
		search = "";
		if (search_headers_style(stringToReturn, match)) {
			if (current_list) {
				current_list = false;
				stringToReturn += "</ul>";
			}
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
				search += "# ";
				search += match[1];
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
