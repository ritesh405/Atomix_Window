/*==============================================================================

                    Copyright (c) 2012 Ritesh Kumar Sinha
                             
================================================================================
File description:

    Level.h - 

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
#ifndef ILEVEL_H
#define ILEVEL_H

#include <QWidget>
#include <QVector>
#include <QHBoxLayout>
#include <QGroupBox>
#include <QPushButton>

#include "Board.h"
#include "Atom.h"
#include "Player.h"
#include "Molecule.h"
#include "DigitalClock.h"
#include "StatusChecker.h"

class Level : public QWidget
{
    Q_OBJECT

public:
    Level(const int levelno);
    ~Level();
    void render();
    int winOrNot();
    Board* getBoard();
    QWidget* getWindow();

signals:
    void moveAtomSig(int row, int col);
    void selectAtomSig(int index);
    void wonLevelSig();
    void skipLevelSig();

public slots:
    void moveAtomSlot(int row, int col);
    void selectAtomSlot(int index);
    void startTimerSlot();
    void skipLevelSlot();

protected:
    bool eventFilter(QObject * object, QEvent * event);

private:
    void drawAtom();
    bool wonOrNot(Atom *movedAtom);
    void initialize();
    void destroy(int level);

    Board *m_board;
    Player *m_player_info;
    Molecule *m_molecule_info;
    DigitalClock *m_timer;
    QVector<Atom *> m_atom_list;
    //QHBoxLayout *m_mainlayout;
    QString m_board_file_location;
    QString m_atom_file_location;
    QString m_molecule_file_location;
    QPushButton *m_skip_button;
    QPushButton *m_start_button;
    StatusChecker *m_statusChecker;

    int m_level_num;
    int m_num_atom;
    int m_selected_atom_index;
};

#endif // ILEVEL_H
