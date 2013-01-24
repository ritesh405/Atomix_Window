/*==============================================================================

                    Copyright (c) 2012 Ritesh Kumar Sinha
                             
================================================================================
File description:

    DigitalClock.cpp - 

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
#include "DigitalClock.h"

#include <QTimer>
#include <QTime>

#include "DigitalClock.h"

DigitalClock::DigitalClock(QWidget *parent)
     : QLCDNumber(parent)
{
    m_start_time = new QTime(QTime::currentTime());
    setSegmentStyle(Filled);
    setDigitCount(8);

    m_timer = new QTimer(this);

    connect(m_timer, SIGNAL(timeout()), this, SLOT(showTime()));
    //timer->start(1000);

    showTime();

    setWindowTitle(tr("Digital Clock"));
    //resize(150, 60);
}

void DigitalClock::startTime()
{
    *m_start_time = QTime::currentTime();
    m_timer->start();
}

void DigitalClock::showTime()
{
    int sec, min, hr;
    int totalSeconds = m_start_time->secsTo(QTime::currentTime());
    sec = min = hr = 0;

    if(totalSeconds < 0)
    {
        totalSeconds = 0;
        *m_start_time = QTime::currentTime();
    }
    sec = totalSeconds % 60;
    if((totalSeconds / 60) < 60)
    {
        min = totalSeconds / 60;
    }
    else
    {
        min = totalSeconds % 60;
        hr = totalSeconds / 60;
    }
    QTime timeTaken = QTime(hr, min, sec);
    QString timeString = timeTaken.toString("hh:mm:ss");

    if ((timeTaken.second() % 2) != 0)
    {
        timeString[2] = ' ';
        timeString[5] = ' ';
    }

    display(timeString);
    //display(totalSeconds);
}

QWidget* DigitalClock::getWindow()
{
    this->setFixedSize(this->sizeHint());
    return this;
}

DigitalClock::~DigitalClock()
{
    delete m_start_time;
    delete m_timer;
}
