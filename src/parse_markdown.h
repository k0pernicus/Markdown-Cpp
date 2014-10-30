/*
 * parse_markdown.h
 *
 *  Created on: 30 oct. 2014
 *      Author: cameron
 */

#ifndef SRC_PARSE_MARKDOWN_H_
#define SRC_PARSE_MARKDOWN_H_

#include <string>

using namespace std;

void parseline(string& line);

bool paragraph = false;
bool entry = false;
bool italic = false;
bool bold = false;

#endif /* SRC_PARSE_MARKDOWN_H_ */
