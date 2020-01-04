/***************************************************************************
 *   Copyright (C) 2009 by Hramchenko   *
 *   Hramchenko@bk.ru   *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/
#include "hworkspacesaver.h"

#include <QFile>
#include <QMessageBox>
#include <QDomDocument>
#include <QTextStream>
#include <QFileInfo>
#include <QDir>

#include "hmodel.h"
#include "hframelist.h"
#include "hframe.h"

HWorkspaceSaver::HWorkspaceSaver(): QObject(){
}

HWorkspaceSaver::~HWorkspaceSaver(){
}

bool	HWorkspaceSaver::saveWorkspace(QString filename){
	QFile file(filename);
	QDomDocument dom_doc("HRSWorkspace");
	saveWorkspace(dom_doc);
	if(!file.open(QFile::WriteOnly)){
		QMessageBox::critical(0, "HRS Reconstruction System", tr("Can't open file: ")+filename);
		return false;
	}
	QFileInfo info(file);
	QDir::setCurrent(info.absolutePath ());
	QTextStream(&file)<<dom_doc.toString();
	file.close();
	HModel::instance()->file=filename;
	return true;
}

void	HWorkspaceSaver::saveWorkspace(QDomDocument document){
	QDomElement elem=document.createElement("workspace");
	document.appendChild(elem);
	saveProject(document, elem);
}

void	HWorkspaceSaver::saveProject(QDomDocument document, QDomElement element){
	QDomElement elem=document.createElement("project");
	QDomAttr attr=document.createAttribute("name");
	attr.setValue(HModel::instance()->name);
	elem.setAttributeNode(attr);
	saveFrames(document, elem);
	element.appendChild(elem);
}

void	HWorkspaceSaver::saveFrames(QDomDocument document, QDomElement element){
	QDomElement elem=document.createElement("frames");
	HFrameList::iterator iter;
	while(iter.frame()){
		HFrameList::instance()->saveFrame(document, elem, iter.frame());
		iter.goNext();
	}
	element.appendChild(elem);
}	

