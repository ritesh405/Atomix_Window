/*==============================================================================

                    Copyright (c) 2012 Ritesh Kumar Sinha
                             
================================================================================
File description:

    XmlParser.cpp - 

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
#include <QDomNode>
#include <QMessageBox>
#include <QDomNodeList>
#include <iostream>
#include <QDomNamedNodeMap>
#include <QDomAttr>

#include "XmlParser.h"

XmlParser::XmlParser(QIODevice *device)
{
    QString errorStr;
    int errorLine;
    int errorColumn;
    QDomDocument doc;
    if (!doc.setContent(device, true, &errorStr, &errorLine,
                        &errorColumn)) {
        QMessageBox::warning(0, QObject::tr("Xml File Parser"),
                             QObject::tr("Parse error at line %1, "
                                         "column %2:\n%3")
                             .arg(errorLine)
                             .arg(errorColumn)
                             .arg(errorStr));
        return;
    }
    m_root = doc.documentElement();
    if (m_root.tagName() != "atomix")
        return; // do exception handling; exit from the application
}

void XmlParser::geteAtomsList(int level, QVector<AtomWithPosition> &atomsListWithPosition)
{
    if( m_root.isNull() )
        return; // do exception handling; exit from the application

    QDomNodeList levelList = m_root.elementsByTagName("level");

    for( int count = 0; count < levelList.count(); count++ )
    {
        QDomElement levelElement = levelList.item(count).toElement();
        if( !levelElement.hasAttribute("id") )
            continue;

        QDomAttr levelIdAttribute = levelElement.attributeNode("id");

        if( level != levelIdAttribute.value().toInt() )
            continue;

        QDomNodeList atomList =  levelElement.elementsByTagName("atom");

        for( int atomCount = 0; atomCount < atomList.count(); atomCount++)
        {
            QDomElement atom = atomList.item(atomCount).toElement();
            if( !atom.hasAttribute("name") || !atom.hasAttribute("row") || !atom.hasAttribute("col"))
                return; // do exception handling

            QDomAttr atomName = atom.attributeNode("name");
            QDomAttr atomRow = atom.attributeNode("row");
            QDomAttr atomCol = atom.attributeNode("col");

            if( atomName.value().isEmpty() || atomRow.value().isEmpty() || atomCol.value().isEmpty())
                return; // do exception handling

            AtomWithPosition atomWithPosition;
            atomWithPosition.m_atom_name = atomName.value();
            atomWithPosition.m_row = atomRow.value().toInt();
            atomWithPosition.m_col = atomCol.value().toInt();

            atomsListWithPosition.push_back(atomWithPosition);
        }
    }
}
