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
regex italic_regex("[a-zA-Z0-9 ]\\*([a-zA-Z0-9]*)\\*[a-zA-Z0-9 ]");
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

void parseline(string& line) {



}
