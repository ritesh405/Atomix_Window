/*==============================================================================

                    Copyright (c) 2012 Ritesh Kumar Sinha
                             
================================================================================
File description:

    InitializeInputFiles.cpp - 

================================================================================
This file is part of Atomix_Window.

    Atomix_Window is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Atomix_Window is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Atomix_Window.  If not, see <http://www.gnu.org/licenses/>.
================================================================================
   Date      Name                    Description of Change
--------------------------------------------------------------------------------
02-Nov-2012  Ritesh Kumar Sinha            Initial Creation
================================================================================*/
#include "InitializeInputFiles.h"

InitializeInputFiles::InitializeInputFiles()
{
}

void InitializeInputFiles::initialize(const int level, QString &boardFileLocation, QString &atomFileLocation, QString &moleculeFileLocation)
{
    switch(level)
    {
        case 1:
            boardFileLocation = ":/levels/level1/board.txt";
            atomFileLocation = ":/levels/level1/atom.txt";
            moleculeFileLocation = ":/images/water.png";
            break;
        case 2:
            boardFileLocation = ":/levels/level2/board.txt";
            atomFileLocation = ":/levels/level2/atom.txt";
            moleculeFileLocation = ":/images/methane.png";
            break;
        case 3:
            boardFileLocation = ":/levels/level3/board.txt";
            atomFileLocation = ":/levels/level3/atom.txt";
            moleculeFileLocation = ":/images/methyle_alcohal.png";
            break;
        case 4:
            boardFileLocation = ":/levels/level4/board.txt";
            atomFileLocation = ":/levels/level4/atom.txt";
            moleculeFileLocation = ":/images/ethylene.png";
            break;
        case 5:
            boardFileLocation = ":/levels/level5/board.txt";
            atomFileLocation = ":/levels/level5/atom.txt";
            moleculeFileLocation = ":/images/ethylene.png";
    }
}
