/*==============================================================================

                    Copyright (c) 2012 Ritesh Kumar Sinha
                             
================================================================================
File description:

    Player.h - 

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
#ifndef PLAYER_H
#define PLAYER_H

#include <QWidget>
#include <QLabel>
#include <QString>
#include <QGroupBox>
#include <QLayout>

class Player : public QWidget
{
    Q_OBJECT
public:
    explicit Player(QWidget *parent = 0);
    ~Player();
    Player(QString playerName, int levelnum);
    QWidget* getWindow();
    void setLevel(const int level);

signals:
    
public slots:

private:
    void renderPlayerInfo();

    QLabel *m_player_name_label;
    QLabel *m_level_number_label;
    QLabel *m_time_elapsed_label;
    QLabel *m_player_name_label_value;
    QLabel *m_level_number_label_value;
    QLabel *m_time_elapsed_value_label;
    QString m_player_name;
    int m_level_number;
    QGroupBox *m_player_layout;

};

#endif // PLAYER_H
