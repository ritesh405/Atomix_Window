/*==============================================================================

                    Copyright (c) 2012 Ritesh Kumar Sinha
                             
================================================================================
File description:

    Molecule.cpp - 

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
#include <QPixmap>
#include <QFont>
#include <QHBoxLayout>

#include "Molecule.h"

Molecule::Molecule(QWidget *parent) :
    QWidget(parent)
{
}

Molecule::Molecule(QString moleculeImage)
{
    QFont playerFont("Times", 11, QFont::Normal);
    this->setFont(playerFont);

    m_molecule_image = new QImage(moleculeImage);
    m_molecule_label = new QLabel(this);
    m_molecule_label->setPixmap(QPixmap::fromImage(*m_molecule_image));

    m_molecule_layout = new QGroupBox(tr("Molecule"), this);
    QHBoxLayout *layout = new QHBoxLayout();
    layout->addWidget(m_molecule_label);
    m_molecule_layout->setLayout(layout);
    this->setFixedSize(m_molecule_label->sizeHint());
}

QWidget* Molecule::getWindow()
{
    //return this;
    return m_molecule_layout;
}

Molecule::~Molecule()
{
    delete m_molecule_label;
    delete m_molecule_image;
    delete m_molecule_layout;
}
