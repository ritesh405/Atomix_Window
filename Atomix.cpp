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
#include <QPalette>
#include <QBrush>
#include <QImage>
#include <QDialog>
#include <QPushButton>
#include <QMessageBox>
#include <QAbstractButton>
#include <QMenu>
#include <QMenuBar>

#include "Atomix.h"
#include "MACRO.h"
/*
Atomix::Atomix(QWidget *parent) :
    QMainWindow(parent)
{
}
*/
Atomix::Atomix()
{
    m_level_no = 1;
    //m_max_level = 5;
    createMenu();
}

void Atomix::play()
{
    m_level = new Level(m_level_no);
    m_level->render();

    this->setCentralWidget(m_level->getWindow());

    connect(m_level, SIGNAL(wonLevelSig()), this, SLOT(showWinningMessage()));
    connect(m_level, SIGNAL(skipLevelSig()), this, SLOT(skipLevelSlot()));

    QPalette palette;
    palette.setBrush(this->backgroundRole(), QBrush(QImage(":/images/background_1_750_500.png")));

    this->setPalette(palette);
    this->setFixedSize(700, 400);
    this->show();
}

void Atomix::skipLevelSlot()
{
    playNext();
}

void Atomix::showWinningMessage()
{
    QMessageBox *msgBox = new QMessageBox();
    msgBox->setText("Congrates ! You won this level");
    msgBox->setWindowTitle("Congrates");
    QAbstractButton *nextLevel = new QPushButton("Next Level");
    QAbstractButton *cancel = new QPushButton("Cancel");
    QAbstractButton *exit = new QPushButton("Exit");

    msgBox->addButton(nextLevel, QMessageBox::AcceptRole);
    msgBox->addButton(cancel, QMessageBox::RejectRole);
    msgBox->addButton(exit, QMessageBox::AcceptRole);

    connect(exit, SIGNAL(clicked()), this, SLOT(close()));
    connect(cancel, SIGNAL(clicked()), msgBox, SLOT(close()));
    connect(nextLevel, SIGNAL(clicked()), this, SLOT(playNext()));
    msgBox->show();
}

void Atomix::playNext()
{
    delete m_level;
    if( m_level_no < MAX_LEVEL )
        m_level_no += 1;

    play();
}

void Atomix::createMenu()
{
    createHelpMenu();
    createExitMenu();
}

void Atomix::createHelpMenu()
{
    m_help_menu = menuBar()->addMenu(tr("&Help"));
    m_how_to_play = new QAction(tr("How to Play"), m_help_menu);
    m_about_atomix = new QAction(tr("About"), m_help_menu);
    m_help_menu->addAction(m_how_to_play);
    m_help_menu->addAction(m_about_atomix);

    connect(m_how_to_play, SIGNAL(triggered()), this, SLOT(howToPlaySlot()));
    connect(m_about_atomix, SIGNAL(triggered()), this, SLOT(aboutAtomixHelp()));
}

void Atomix::createExitMenu()
{
    m_exit_menu = menuBar()->addMenu(tr("&Exit"));
    m_exit_game = new QAction(tr("Exit"), m_exit_menu);
    m_exit_menu->addAction(m_exit_game);
    connect(m_exit_game, SIGNAL(triggered()), this, SLOT(exitGameSlot()));
}

void Atomix::howToPlaySlot()
{

}

void Atomix::aboutAtomixHelp()
{

}

void Atomix::exitGameSlot()
{
    QMessageBox *msgBox = new QMessageBox();
    msgBox->setText("Are you sure, you want to exit ?");
    msgBox->setWindowTitle("Exit");
    QAbstractButton *cancel = new QPushButton("Cancel");
    QAbstractButton *exit = new QPushButton("Exit");

    msgBox->addButton(cancel, QMessageBox::RejectRole);
    msgBox->addButton(exit, QMessageBox::AcceptRole);

    connect(exit, SIGNAL(clicked()), this, SLOT(close()));
    connect(cancel, SIGNAL(clicked()), msgBox, SLOT(close()));
    msgBox->show();
}

Atomix::~Atomix()
{
    delete m_level;
}
