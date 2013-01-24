/*==============================================================================

                    Copyright (c) 2012 Ritesh Kumar Sinha
                             
================================================================================
File description:

    Atomix.cpp - 

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
#ifndef ATOMIX_H
#define ATOMIX_H

#include <QMainWindow>
#include <QVector>
#include <QMenu>

#include "Level.h"

class Atomix : public QMainWindow
{
    Q_OBJECT
public:
    //explicit Atomix(QWidget *parent = 0);
    Atomix();
    ~Atomix();
    void play();

signals:
    
public slots:
    void showWinningMessage();
    void howToPlaySlot();
    void aboutAtomixHelp();
    void exitGameSlot();

private slots:
    void playNext();
    void skipLevelSlot();

private:
    void intialize(int level);
    void destroy(int level);
    void createMenu();
    void createHelpMenu();
    void createExitMenu();

    Level *m_level;
    int m_level_no;
    QMenu *m_help_menu;
    QMenu *m_exit_menu;
    QAction *m_about_atomix;
    QAction *m_how_to_play;
    QAction *m_exit_game;

    //int m_max_level;
};

#endif // ATOMIX_H
