/*==============================================================================

                    Copyright (c) 2012 Ritesh Kumar Sinha
                             
================================================================================
File description:

    Atom.h - 

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
#ifndef ATOM_H
#define ATOM_H

#include <QWidget>
#include <QLabel>
#include <QString>
#include <QImage>


class Atom : public QWidget
{
    Q_OBJECT

public:
    enum AtomName
    {
        HYDROGEN, OXYGEN, CARBON
    };

     ~Atom();
    Atom(AtomName name, int row, int col);
    int getRow() const;
    int getCol() const;
    AtomName getName() const;
    QLabel* getLabel();
    void setLabel(QLabel *atom);
    void setName(AtomName name);
    void setRow(int row);
    void setCol(int col);
    void move(int row, int col);
    void select();
    void setSelected(bool value);
    bool isSelected();
    void setSelectedImage(QString image);
    void setDeSelectedImage(QString image);

protected:
    void findRowAndCol(int &row, int &col);

    QLabel *m_label;
    AtomName m_name;
    QImage *m_selected_image;
    QImage *m_desselected_image;
    int m_row;
    int m_col;
    bool m_selected;

private:
};

#endif // ATOM_H
