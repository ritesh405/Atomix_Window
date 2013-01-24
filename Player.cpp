/*==============================================================================

                    Copyright (c) 2012 Ritesh Kumar Sinha
                             
================================================================================
File description:

    Player.cpp - 

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
#include <QGridLayout>

#include "Player.h"

Player::Player(QWidget *parent) :
    QWidget(parent)
{
}

Player::Player(QString playerName, int levelnum)
{
    m_player_name = playerName;
    m_level_number = levelnum;

    m_player_name_label = new QLabel(tr("Name"));
    m_level_number_label = new QLabel(tr("Level"));
    m_time_elapsed_label = new QLabel(tr("Time Elapsed"));

    m_player_name_label_value = new QLabel(m_player_name);
    m_level_number_label_value = new QLabel(QString("%1").arg(m_level_number));//m_level_number);
    m_time_elapsed_value_label = new QLabel();

    m_player_name_label->setAlignment(Qt::AlignLeft | Qt::AlignTop);
    m_player_name_label_value->setWordWrap(true);

    renderPlayerInfo();
}

void Player::setLevel(const int level)
{
    m_level_number = level;
    m_level_number_label_value->setText(QString("%1").arg(m_level_number));
}

void Player::renderPlayerInfo()
{
    QFont playerFont("Times", 12, QFont::Normal);
    this->setFont(playerFont);
    m_player_layout = new QGroupBox(tr("Player"), this);
    QGridLayout *gridLayout = new QGridLayout();
    QLabel *colon1 = new QLabel(":");
    QLabel *colon2 = new QLabel(":");
    QLabel *colon3 = new QLabel(":");

    colon1->setAlignment(Qt::AlignLeft | Qt::AlignTop);
    gridLayout->addWidget(m_player_name_label, 0, 0);
    gridLayout->addWidget(colon1, 0, 1);
    gridLayout->addWidget(m_player_name_label_value, 0, 2);
    gridLayout->addWidget(m_level_number_label, 1, 0);
    gridLayout->addWidget(colon2, 1, 1);
    gridLayout->addWidget(m_level_number_label_value, 1, 2);
    gridLayout->addWidget(m_time_elapsed_label, 2, 0);
    gridLayout->addWidget(colon3, 2, 1);
    gridLayout->addWidget(m_time_elapsed_value_label, 2, 2);

    gridLayout->setColumnMinimumWidth(0,100);
    gridLayout->setColumnMinimumWidth(1,20);
    gridLayout->setColumnMinimumWidth(2,120);

    m_player_layout->setLayout(gridLayout);
    //m_player_layout->setFixedSize(gridLayout->sizeHint());
    //this->setLayout(gridLayout);

}

QWidget* Player::getWindow()
{
    //return this;
    return m_player_layout;
}

Player::~Player()
{
    delete m_player_name_label;
    delete m_level_number_label;
    delete m_time_elapsed_label;
    delete m_player_name_label_value;
    delete m_level_number_label_value;
    delete m_time_elapsed_value_label;
    delete m_player_layout;

}
