/*==============================================================================

                    Copyright (c) 2012 Ritesh Kumar Sinha
                             
================================================================================
File description:

    Board.h - 

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
#ifndef BOARD_H
#define BOARD_H

#include <QWidget>
#include <QString>
#include <QGridLayout>

#include "Atom.h"

class Board : public QWidget
{
    Q_OBJECT

public:
    explicit Board(QWidget *parent = 0);
    Board(QString boardFile);
    Board(const Board &board);
    ~Board();
    QWidget* getWindow();
    QGridLayout* getGridLayout() const;
    void draw();
    bool getAtomAt(int row, int col, Atom **atom);
    void addAtomAt(Atom *atom, int row, int col);
    void removeAtom(Atom *atom);
    bool findRowAndCol(const Atom &atom,const int row, const int col, int &newRow, int &newCol);

    Board& operator =(const Board &board);

private:
    QString *m_board_level_file;
    QGridLayout *m_gridlayout;
};

#endif // BOARD_H
