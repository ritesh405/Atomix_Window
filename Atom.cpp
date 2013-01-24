/*==============================================================================

                    Copyright (c) 2012 Ritesh Kumar Sinha
                             
================================================================================
File description:

    Atom.cpp - 

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
#include "Atom.h"

Atom::Atom(AtomName name, int row, int col)
{
    m_label = new QLabel(this);
    m_name = name;
    m_selected_image = new QImage();
    m_desselected_image = new QImage();
    m_row = row;
    m_col = col;
}

int Atom::getRow() const
{
    return m_row;
}

int Atom::getCol() const
{
    return m_col;
}
Atom::AtomName Atom::getName() const
 {
     return m_name;
 }

QLabel* Atom::getLabel()
{
    return m_label;
}

void Atom::setLabel(QLabel *atomLabel)
{
    m_label = atomLabel;
}

void Atom::setName(AtomName name)
{
    m_name = name;
}

void Atom::setRow(int row)
{
    m_row = row;
}

void Atom::setCol(int col)
{
    m_col = col;
}

void Atom::move(int row, int col)
{

}

void Atom::select()
{

}

void Atom::setSelected(bool value)
{
    m_selected = value;
    if(m_selected == true)
        m_label->setPixmap(QPixmap::fromImage(*m_selected_image));
    else
        m_label->setPixmap(QPixmap::fromImage(*m_desselected_image));
}

bool Atom::isSelected()
{
    return m_selected;
}

void Atom::setSelectedImage(QString image)
{
    m_selected_image = new QImage(image);
}

void Atom::setDeSelectedImage(QString image)
{
    m_desselected_image = new QImage(image);
}

Atom::~Atom()
{
    delete m_label;
    delete m_selected_image;
    delete m_desselected_image;
}
