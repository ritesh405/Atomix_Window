/*==============================================================================

                    Copyright (c) 2012 Ritesh Kumar Sinha
                             
================================================================================
File description:

    Board.cpp - 

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
#include <QFile>
#include <QTextStream>
#include <QLabel>
#include <QEvent>
#include <QMouseEvent>
#include <QLayout>
//#include <typeinfo>
//#include <string.h>

#include "Board.h"
#include "MACRO.h"

Board::Board(QWidget *parent) :
    QWidget(parent)
{
    m_board_level_file = new QString();
    m_gridlayout = new QGridLayout();
}

Board::Board(QString boardFile)
{
    m_board_level_file = new QString(boardFile);
    m_gridlayout = new QGridLayout();
}

Board::Board(const Board &board)
{
    m_board_level_file = new QString(*(board.m_board_level_file));
    m_gridlayout = new QGridLayout(dynamic_cast<QWidget*>(board.getGridLayout()));

    //m_gridlayout = board.m_gridlayout;
}

Board& Board::operator =(const Board &board)
{
    if( this == &board )
        return *this;
    m_board_level_file = board.m_board_level_file;
    m_gridlayout = board.m_gridlayout;
    return *this;
}

QWidget* Board::getWindow()
{
    return this;
}

QGridLayout* Board::getGridLayout() const
{
    return m_gridlayout;
}

void Board::draw()
{
    QFile file(*m_board_level_file);
    QMessageBox errorMessage;
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        //return;
        errorMessage.setText("File cannot be opened!");
        errorMessage.show();
    }

    QTextStream in(&file);
    int row = 0;
    while (!in.atEnd())
    {
        QString line = in.readLine();
        QStringList list;
        list = line.split(QRegExp("\\s+"));
        for(int index=0; index < list.size(); index++)
        {
            if(!QString::compare(list.at(index),"B",Qt::CaseInsensitive))
            {
                QLabel *brick =new QLabel();
                //brick->setFrameStyle(QFrame::Box);
                brick->setCursor(Qt::ForbiddenCursor);

                QImage *brickImage = new QImage(BRICK_IMAGE);
                brick->setPixmap(QPixmap::fromImage(*brickImage));
                //brick->installEventFilter(this);
                brick->blockSignals(true);

                m_gridlayout->addWidget(brick,row,index);
            }
        }
        row++;
    }
    m_gridlayout->setSizeConstraint(QLayout::SetFixedSize);
    m_gridlayout->setSpacing(0);
    this->setLayout(m_gridlayout);
    this->setFixedSize(m_gridlayout->sizeHint());
}

bool Board::findRowAndCol(const Atom &atom, const int row, const int col, int &newRow, int &newCol)
{
    newCol = atom.getCol();
    newRow = atom.getRow();
    if(newRow == row)
    {
        if(col > newCol)
        {
            newCol++;
            while(1)
            {
                QLayoutItem * const item = m_gridlayout->itemAtPosition(row,newCol);
                //if(!dynamic_cast<QWidgetItem *>(item))
                if(!item)
                   newCol += 1;
                else
                    break;
            }
            newCol--;
        }
        else
        {
            newCol--;
            while(1)
            {
                QLayoutItem * const item = m_gridlayout->itemAtPosition(row,newCol);
                //if(!dynamic_cast<QWidgetItem *>(item))
                if(!item)
                   newCol -= 1;
                else
                    break;
            }
            newCol++;
        }
        return OK;
    }
    else if(newCol == col)
    {
        if(row > newRow)
        {
            newRow++;
            while(1)
            {
                QLayoutItem * const item = m_gridlayout->itemAtPosition(newRow,col);
                //if(!dynamic_cast<QWidgetItem *>(item))
                if(!item)
                   newRow += 1;
                else
                    break;
            }
            newRow--;
        }
        else
        {
            newRow--;
            while(1)
            {
                QLayoutItem * const item = m_gridlayout->itemAtPosition(newRow,col);
                //if(!dynamic_cast<QWidgetItem *>(item))
                if(!item)
                   newRow -= 1;
                else
                    break;
            }
            newRow++;
        }
        return OK;
    }
    return NOT_OK;
}

bool Board::getAtomAt(int row, int col, Atom **atom)
{
    QLayoutItem* const item = m_gridlayout->itemAtPosition(row, col);
    if(item != 0)
    {
        QWidget *widget = item->widget();
        if (strcmp(widget->metaObject()->className(), Atom::staticMetaObject.className()) == 0)
        {
            *atom = dynamic_cast<Atom *>(widget);
            return OK;
        }
    }
    *atom = NULL;
    return NOT_OK;
}

void Board::addAtomAt(Atom *atom, int row, int col)
{
    m_gridlayout->addWidget(atom, row, col);
}

void Board::removeAtom(Atom *atom)
{
    m_gridlayout->removeWidget(atom);
}

Board::~Board()
{
    delete m_board_level_file;
    delete m_gridlayout;
}
