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
#include "hworkspaceloader.h"

#include <QFile>
#include <QMessageBox>
#include <QDomDocument>
#include <QFileInfo>
#include <QDir>

#include "hframelist.h"
#include "hmodel.h"
#include "hglscreen.h"

HWorkspaceLoader::HWorkspaceLoader(): QObject(){
}

HWorkspaceLoader::~HWorkspaceLoader(){
}

bool	HWorkspaceLoader::loadWorkspace(QString filename){
	QFile file(filename);
	if(!file.open(QFile::ReadOnly)){
		QMessageBox::critical(0, "HRS Reconstruction System", tr("Can't open file: ")+filename);
		return false;
	}
	QFileInfo info(file);
	QDir::setCurrent(info.absolutePath ());
	QDomDocument dom_doc;
	if(!dom_doc.setContent(&file)){
		QMessageBox::critical(0, "HRS Reconstruction System", tr("Invalid file format: ")+filename);
		file.close();
		return false;
	}
	HGLScreen::instance()->clearReconstruction();
	QDomNode root_dom_node=dom_doc.firstChild();
	QDomNode dom_node;
	while(!root_dom_node.isNull()){
		if(root_dom_node.isElement()){
			if(root_dom_node.toElement().tagName()=="workspace"){
				dom_node=root_dom_node.firstChild();
				while(!dom_node.isNull()){
					
					if(!analyseElement(dom_node.toElement())){
						cancelLoading();
						break;
					}
					dom_node=dom_node.nextSibling();
				}
			}
			else{
				QMessageBox::critical(0, "HRS Reconstruction System", tr("Can't find root (workspace)"));
				cancelLoading();
				break;
			}
		}
		root_dom_node=root_dom_node.nextSibling();
	}	
	HModel::instance()->file=filename;
	file.close();
	return true;
}

bool	HWorkspaceLoader::analyseElement(QDomElement element){
	if(element.tagName()=="project"){
		if(!loadProject(element))
			return false;
	}
	else{
		QMessageBox::critical(0, "HRS Reconstruction System", tr("Unknown element type: ")+element.tagName());
		return false;
	}
	return true;
}

void	HWorkspaceLoader::cancelLoading(){
	QMessageBox::critical(0, "HRS Reconstruction System", tr("Loading was canceled"));
	HFrameList::instance()->clearList();
}

bool	HWorkspaceLoader::loadProject(QDomElement element){
	QDomNode dom_node=element.firstChild();
	QDomElement dom_element;
	HModel::instance()->name=element.attribute("name", tr("MODEL"));
	while(!dom_node.isNull()){
		if(dom_node.isElement()){
			element=dom_node.toElement();
			if(element.tagName()==QString::fromUtf8("frames")){
				if(!loadFrames(element))
					return false;
			}
			else{
				QMessageBox::critical(0, "HRS Reconstruction System", tr("Unknown element type: ")+element.tagName());
				return false;
			}
		}
		dom_node=dom_node.nextSibling();
	}	
	return true;
}

bool	HWorkspaceLoader::loadFrames(QDomElement element){
	QDomNode dom_node=element.firstChild();
	QDomElement dom_element;
	while(!dom_node.isNull()){
		if(dom_node.isElement()){
			element=dom_node.toElement();
			if(element.tagName()=="frame"){
				if(!HFrameList::instance()->loadFrame(element))
					return false;
			}
			else{
				QMessageBox::critical(0, "HRS Reconstruction System", tr("Unknown element type: ")+element.tagName());
				return false;
			}
		}
		dom_node=dom_node.nextSibling();
	}	
	return true;
}

