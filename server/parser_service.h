#ifndef PARSER_SERVICE_H
#define PARSER_SERVICE_H

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <vector>
#include <map>

#include <QtWidgets/QApplication>
#include <QtCore/QCommandLineParser>

std::map<std::string, std::string> init_parser(QCommandLineParser* parser, QCoreApplication* app);

#endif // PARSER_SERVICE_H
