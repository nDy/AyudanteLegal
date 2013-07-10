 ##################################################################################
 #                                                                                #
 #    This file is part of AyudanteLegal.                                         #
 #    AyudanteLegal is free software: you can redistribute it and/or modify       #
 #    it under the terms of the GNU General Public License as published by        #
 #    the Free Software Foundation, either version 3 of the License, or           #
 #    (at your option) any later version.                                         #
 #                                                                                #
 #    AyudanteLegal is distributed in the hope that it will be useful,            #
 #    but WITHOUT ANY WARRANTY; without even the implied warranty of              #
 #    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the               #
 #    GNU General Public License for more details.                                #
 #                                                                                #
 #    Source Code written by nDy (Andres Rangel)                                  #
 #    Contact info:                                                               #
 #    Email: nDy.Work@gmail.com      GitHub Repository: https://github.com/nDy    #
 #                                                                                #
 #    Copyright:                                                                  #
 #               nDySoft© (2013)                                                  #
 #                                                                                #
 ##################################################################################

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = AyudanteLegal
TEMPLATE = app

QMAKE_CXXFLAGS += -std=c++11

SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui

OTHER_FILES +=
