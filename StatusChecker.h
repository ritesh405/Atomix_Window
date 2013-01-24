/*==============================================================================

                    Copyright (c) 2012 Ritesh Kumar Sinha
                             
================================================================================
File description:

    StatusChecker.h - 

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
#ifndef STATUSCHECKER_H
#define STATUSCHECKER_H

#include "Board.h"
#include "Atom.h"

class StatusChecker
{
public:
    StatusChecker(const Board &board, QVector<Atom *> atomList, int level);
    ~StatusChecker();
    bool wonOrNot(const Atom &movedAtom);

private:
    bool level1WonOrNot(const Atom &movedAtom);
    bool level2WonOrNot(const Atom &movedAtom);
    bool level3WonOrNot(const Atom &movedAtom);

    //Board *m_board;
    Board m_board;
    QVector<Atom *> m_atom_list;
    int m_level_num;
};

#endif // STATUSCHECKER_H
