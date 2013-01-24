/*==============================================================================

                    Copyright (c) 2012 Ritesh Kumar Sinha
                             
================================================================================
File description:

    Molecule.h - 

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
#ifndef MOLECULE_H
#define MOLECULE_H

#include <QWidget>
#include <QLabel>
#include <QImage>
#include <QGroupBox>

class Molecule : public QWidget
{
    Q_OBJECT
public:
    explicit Molecule(QWidget *parent = 0);
    Molecule(QString moleculeImage);
    ~Molecule();
    QWidget* getWindow();

signals:
    
public slots:

private:
    QLabel *m_molecule_label;
    QImage *m_molecule_image;
    QGroupBox *m_molecule_layout;
};

#endif // MOLECULE_H
