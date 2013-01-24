/*==============================================================================

                    Copyright (c) 2012 Ritesh Kumar Sinha
                             
================================================================================
File description:

    Level.cpp - 

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
#include <QEvent>
#include <QMouseEvent>
#include <QVBoxLayout>
#include <QTextStream>
//#include <iostream>
#include <QDialog>
#include <QFile>
#include <QVector>

#include "Level.h"
#include "MACRO.h"
#include "InitializeInputFiles.h"
#include "XmlParser.h"
#include "Structure.h"

Level::Level(const int levelno)
{
    m_selected_atom_index = -1;
    m_level_num = levelno;
    connect(this, SIGNAL(moveAtomSig(int,int)),this, SLOT(moveAtomSlot(int,int)));
    connect(this, SIGNAL(selectAtomSig(int)),this,SLOT(selectAtomSlot(int)));
}

void Level::initialize()
{
    InitializeInputFiles initializeInputFiles;
    initializeInputFiles.initialize(m_level_num, m_board_file_location, m_atom_file_location, m_molecule_file_location);
    m_board = new Board(m_board_file_location);
    m_molecule_info = new Molecule(m_molecule_file_location);
}

void Level::destroy(int level)
{

}

void Level::render()
{
    initialize();
    m_board->draw();
    m_board->installEventFilter(this);

    drawAtom();

    m_player_info = new Player("Ritesh Kumar Sinha", 1);
    m_player_info->setLevel(m_level_num);
    //m_player_info = new Player("Ritesh Kumar Sinha Big Name Big", 1);

    m_timer = new DigitalClock();


    QVBoxLayout *rightLayout = new QVBoxLayout();
    rightLayout->setSizeConstraint(QLayout::SetFixedSize);
    rightLayout->addStretch(1);
    rightLayout->addWidget(m_player_info->getWindow());

    QGridLayout *middleLayout = new QGridLayout();
    m_start_button = new QPushButton("Start");
    m_skip_button = new QPushButton("Skip");
    m_start_button->setFixedSize(110, 30);
    m_skip_button->setFixedSize(110, 30);
    middleLayout->addWidget(m_timer->getWindow(), 0, 0, 2, 0);
    middleLayout->addWidget(m_start_button, 0, 1);
    middleLayout->addWidget(m_skip_button, 1, 1);

    rightLayout->setSpacing(5);
    rightLayout->addStretch(1);
    rightLayout->addLayout(middleLayout);
    rightLayout->addWidget(m_molecule_info->getWindow());
    rightLayout->setSpacing(5);
    rightLayout->addStretch(1);

    connect(m_start_button, SIGNAL(clicked()), SLOT(startTimerSlot()));
    connect(m_skip_button, SIGNAL(clicked()), SLOT(skipLevelSlot()));

    QWidget *rightWidget = new QWidget();
    rightWidget->setLayout(rightLayout);

    QHBoxLayout *boardlayout = new QHBoxLayout();
    boardlayout->addWidget(m_board->getWindow(), 0, Qt::AlignLeft);

    QGridLayout *gridLayout = new QGridLayout();
    gridLayout->addLayout(boardlayout, 0, 0);
    gridLayout->addWidget(rightWidget, 0, 1);


    this->setLayout(gridLayout);
    //this->setFixedSize(gridLayout->sizeHint());

    m_timer->getWindow()->setFixedSize(150, 60);
    if(m_level_num == MAX_LEVEL)
        m_skip_button->setEnabled(false);
    m_statusChecker = new StatusChecker(*m_board, m_atom_list, m_level_num);
}

void Level::startTimerSlot()
{
    m_timer->startTime();
    m_start_button->setEnabled(false);
}

void Level::skipLevelSlot()
{
    if(m_level_num < MAX_LEVEL)
        emit skipLevelSig();
}

Board* Level::getBoard()
{
    return m_board;
}

QWidget* Level::getWindow()
{
    return this;
}

void Level::drawAtom()
{
    QFile file(":/levels/Levels.xml");
    XmlParser atomXmlFile(&file);
    QVector<AtomWithPosition> atomsListWithPosition;
    atomXmlFile.geteAtomsList(m_level_num, atomsListWithPosition);

    for( int count = 0; count < atomsListWithPosition.count(); count++)
    {
        QString atomName = atomsListWithPosition.at(count).m_atom_name;
        int row = atomsListWithPosition.at(count).m_row;
        int col = atomsListWithPosition.at(count).m_col;

        if(!QString::compare(atomName,"H",Qt::CaseInsensitive))
        {
            Atom *hydrogen = new Atom(Atom::HYDROGEN, row, col);
            hydrogen->setSelectedImage(HYDROGEN_SELECTED_IMAGE);
            hydrogen->setDeSelectedImage(HYDROGEN_DISSELECTED_IMAGE);
            hydrogen->setSelected(false);
            hydrogen->installEventFilter(this);
            m_atom_list.push_back(hydrogen);
            m_board->addAtomAt(hydrogen, row, col);
        }
        if(!QString::compare(atomName,"C",Qt::CaseInsensitive))
        {
            Atom *carbon = new Atom(Atom::CARBON, row, col);
            carbon->setSelectedImage(CARBON_SELECTED_IMAGE);
            carbon->setDeSelectedImage(CARBON_DISSELECTED_IMAGE);
            carbon->setSelected(false);
            carbon->installEventFilter(this);
            m_atom_list.push_back(carbon);
            m_board->addAtomAt(carbon, row, col);
        }
        if(!QString::compare(atomName,"O",Qt::CaseInsensitive))
        {
            Atom *oxygen = new Atom(Atom::OXYGEN, row, col);
            oxygen->setSelectedImage(OXYGEN_SELECTED_IMAGE);
            oxygen->setDeSelectedImage(OXYGEN_DISSELECTED_IMAGE);
            oxygen->setSelected(false);
            oxygen->installEventFilter(this);
            m_atom_list.push_back(oxygen);
            m_board->addAtomAt(oxygen, row, col);
        }
    }

}

bool Level::eventFilter(QObject *object, QEvent *event)
{
    QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event);

    if(event->type() == QEvent::MouseButtonRelease && mouseEvent->button() == Qt::LeftButton)
    {
        if(m_start_button->isEnabled() == true)
        {
            QMessageBox *msgBox = new QMessageBox();
            msgBox->setText("Please click on Start Button!");
            msgBox->show();
            return true;
        }
        else
        {
            for(int count = 0; count < m_atom_list.count(); count++)
            {
                if(object == m_atom_list.at(count))
                {
                    emit selectAtomSig(count);
                    return true;
                }
            }
            if(object == m_board)
            {
                int y = (mouseEvent->x() - BOARD_EXTTERNAL_WIDTH)/BRICK_WIDTH;
                int x = (mouseEvent->y() - BOARD_EXTTERNAL_WIDTH)/BRICK_WIDTH;
                emit moveAtomSig(x, y);
                return true;
            }
        }
    }
    //return false;
    // pass the event on to the parent class
    return QObject::eventFilter(object, event);
}

void Level::selectAtomSlot(int index)
{
    m_atom_list.at(index)->setSelected(true);
    if(m_selected_atom_index >= 0 && m_selected_atom_index != index)
    {
        m_atom_list.at(m_selected_atom_index)->setSelected(false);
    }
    m_selected_atom_index = index;
}

void Level::moveAtomSlot(int row, int col)
{
    int newRow, newCol;

    if (m_selected_atom_index >=0 && m_board->findRowAndCol(*m_atom_list.at(m_selected_atom_index), row, col, newRow, newCol) == OK)
    {
        m_board->removeAtom(m_atom_list.at(m_selected_atom_index));
        m_board->addAtomAt(m_atom_list.at(m_selected_atom_index),newRow,newCol);
        m_atom_list.at(m_selected_atom_index)->setRow(newRow);
        m_atom_list.at(m_selected_atom_index)->setCol(newCol);
        wonOrNot(m_atom_list.at(m_selected_atom_index));
    }
}

bool Level::wonOrNot(Atom *movedAtom)
{
    if( m_statusChecker->wonOrNot(*movedAtom) == OK )
    {
        emit wonLevelSig();
        return OK;
    }
    return NOT_OK;
}

Level::~Level()
{
    delete m_board;
    delete m_player_info;
    delete m_molecule_info;
    delete m_timer;
    //QVector<Atom *> m_atom_list;
    delete m_skip_button;
    delete m_start_button;
    //delete m_statusChecker;

}
