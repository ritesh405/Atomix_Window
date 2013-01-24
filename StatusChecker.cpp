/*==============================================================================

                    Copyright (c) 2012 Ritesh Kumar Sinha
                             
================================================================================
File description:

    StatusChecker.cpp - 

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
#include <QMessageBox>

#include "StatusChecker.h"
#include "MACRO.h"

StatusChecker::StatusChecker(const Board &board, QVector<Atom *> atomList, int level)
{
    m_board = board;
    m_atom_list = atomList;
    m_level_num = level;
}

bool StatusChecker::wonOrNot(const Atom &movedAtom)
{
    switch(m_level_num)
    {
        case 1 :
            return level1WonOrNot(movedAtom);

        case 2 :
            return level2WonOrNot(movedAtom);

        case 3 :
            return level3WonOrNot(movedAtom);
    }

}

bool StatusChecker::level1WonOrNot(const Atom &movedAtom)
{
    int row = movedAtom.getRow();
    int col = movedAtom.getCol();
    Atom *oxygen, *hydrogen;

    switch(movedAtom.getName())
    {
        case Atom::HYDROGEN :
            if(
                    ((m_board.getAtomAt(row, col-1, &oxygen) == OK &&
                      oxygen->getName() == Atom::OXYGEN &&
                      m_board.getAtomAt(row, col-2, &hydrogen) == OK &&
                      hydrogen->getName() == Atom::HYDROGEN) ||
                      (m_board.getAtomAt(row, col+1, &oxygen) == OK &&
                      oxygen->getName() == Atom::OXYGEN &&
                      m_board.getAtomAt(row, col+2, &hydrogen) == OK &&
                      hydrogen->getName() == Atom::HYDROGEN))
               )
            {
                return OK;
            }
            break;
        case Atom::OXYGEN :
            if(
                      m_board.getAtomAt(row, col-1, &hydrogen) == OK &&
                      hydrogen->getName() == Atom::HYDROGEN &&
                      m_board.getAtomAt(row, col+1, &hydrogen) == OK &&
                      hydrogen->getName() == Atom::HYDROGEN
                )
            {
                return OK;
            }
            break;
    }
    return NOT_OK;
}

bool StatusChecker::level2WonOrNot(const Atom &movedAtom)
{
    int row = movedAtom.getRow();
    int col = movedAtom.getCol();
    Atom *carbon, *hydrogen;
    switch(movedAtom.getName())
    {
        case Atom::CARBON :
            if(
                    ((m_board.getAtomAt(row, col-1, &hydrogen) == OK &&
                      hydrogen->getName() == Atom::HYDROGEN &&
                      m_board.getAtomAt(row, col+1, &hydrogen) == OK &&
                      hydrogen->getName() == Atom::HYDROGEN &&
                      m_board.getAtomAt(row-1, col, &hydrogen) == OK &&
                      hydrogen->getName() == Atom::HYDROGEN &&
                      m_board.getAtomAt(row+1, col, &hydrogen) == OK &&
                      hydrogen->getName() == Atom::HYDROGEN))
               )
            {
                return OK;
            }
            break;
        case Atom::HYDROGEN :
            if(
                    (m_board.getAtomAt(row, col-1, &carbon) == OK &&
                    carbon->getName() == Atom::CARBON) ||
                    (m_board.getAtomAt(row, col+1, &carbon) == OK &&
                    carbon->getName() == Atom::CARBON) ||
                    (m_board.getAtomAt(row+1, col, &carbon) == OK &&
                    carbon->getName() == Atom::CARBON) ||
                    (m_board.getAtomAt(row-1, col, &carbon) == OK &&
                    carbon->getName() == Atom::CARBON)
               )
            {
                return level2WonOrNot(*carbon);
            }
            break;
    }
    return NOT_OK;
}

bool StatusChecker::level3WonOrNot(const Atom &movedAtom)
{
    int row = movedAtom.getRow();
    int col = movedAtom.getCol();
    Atom *carbon, *hydrogen, *oxygen;
    switch(movedAtom.getName())
    {
        // left = up =down = Hydrogen && right = Oxygen && right + 1 = Hydrogen
        case Atom::CARBON :
            if(
                    (m_board.getAtomAt(row, col-1, &hydrogen) == OK &&
                      hydrogen->getName() == Atom::HYDROGEN &&
                      m_board.getAtomAt(row + 1, col, &hydrogen) == OK &&
                      hydrogen->getName() == Atom::HYDROGEN &&
                      m_board.getAtomAt(row-1, col, &hydrogen) == OK &&
                      hydrogen->getName() == Atom::HYDROGEN &&
                      m_board.getAtomAt(row, col + 1, &oxygen) == OK &&
                      oxygen->getName() == Atom::OXYGEN &&
                      m_board.getAtomAt(row, col + 1 + 1, &hydrogen) == OK &&
                      hydrogen->getName() == Atom::HYDROGEN)
               )
            {
                return OK;
            }
            break;
        // (right || up || down = Carbon) || ( left = Oxygen && left - 1 = Carbon ) => call case Atom::CARBON
        case Atom::HYDROGEN :
            if(
                    (m_board.getAtomAt(row, col + 1, &carbon) == OK &&
                    carbon->getName() == Atom::CARBON) ||
                    (m_board.getAtomAt(row - 1, col, &carbon) == OK &&
                    carbon->getName() == Atom::CARBON) ||
                    (m_board.getAtomAt(row + 1, col, &carbon) == OK &&
                    carbon->getName() == Atom::CARBON) ||
                    (m_board.getAtomAt(row, col - 1, &oxygen) == OK &&
                    oxygen->getName() == Atom::OXYGEN &&
                    m_board.getAtomAt(row, col - 1 - 1, &carbon) == OK &&
                    carbon->getName() == Atom::CARBON)
               )
            {
                return level3WonOrNot(*carbon);
            }
            break;
        // right = hydrogen && left = carbon => call case Atom::CARBON
        case Atom::OXYGEN :
            if(
                    m_board.getAtomAt(row, col + 1, &hydrogen) == OK &&
                    hydrogen->getName() == Atom::HYDROGEN &&
                    m_board.getAtomAt(row, col - 1, &carbon) == OK &&
                    carbon->getName() == Atom::CARBON
                )
            {
                return level3WonOrNot(*carbon);
            }
    }
   return NOT_OK;
}

StatusChecker::~StatusChecker()
{
    //delete m_board;
    //QVector<Atom *> m_atom_list;
}
