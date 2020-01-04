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
#include "hframelist.h"

#include <QMessageBox>

#include "hframe.h"
#include "hframeparam.h"
#include "hframeparamlist.h"
#include "hprojectfilesdock.h"

using namespace std;

HFrameList* HFrameList::_instance=0;

HFrameList::iterator::iterator(){
	currentFrame=HFrameList::instance()->root;
}

HFrameList::iterator::~iterator(){
}

HFrame*	HFrameList::iterator::frame(){
	return currentFrame;
}

void	HFrameList::iterator::goNext(){
	if(currentFrame)
		currentFrame=currentFrame->nextFrame;
}

void	HFrameList::iterator::goBegin(){
	currentFrame=HFrameList::instance()->root;
}

HFrameList::HFrameList(): QObject(){
	root=0;
	framesCount=0;
}

HFrameList::~HFrameList(){
	clearList();
}

HFrameList*	HFrameList::instance(){
	if(!_instance)
		_instance=new HFrameList();
	return _instance;
}

HFrame*	HFrameList::addFrame(QString name, QImage image){
	HFrame* frame=new HFrame(name, image);
	if(root)
		root->previousFrame=frame;
	frame->nextFrame=root;
	root=frame;
	framesCount++;
	HProjectFilesDock::reloadTree();
	return frame;
}

HFrame*	HFrameList::findFrame(QString name){
	HFrame* frame=root;
	while(frame){
		if(frame->name==name)
			return frame;
		frame=frame->nextFrame;
	}
	return 0;
}

void	HFrameList::removeFrame(QString name){
	HFrame* frame=findFrame(name);
	if(!frame)
		return;
	if(frame==root){
		root=frame->nextFrame;
		if(root)
			if(root->nextFrame)
				root->nextFrame->previousFrame=0;
	}
	else if(frame->previousFrame&&frame->nextFrame){
		frame->previousFrame->nextFrame=frame->nextFrame;
		frame->nextFrame->previousFrame=frame->previousFrame;
	}
	else if(frame->previousFrame){
		frame->previousFrame->nextFrame=0;
	}
	delete frame;
	framesCount--;
	HProjectFilesDock::reloadTree();
}

void	HFrameList::clearList(){
	HFrame* temp;
	while(root){
		temp=root->nextFrame;
		delete root;
		root=temp;
	}
	root=0;
	framesCount=0;
	HProjectFilesDock::reloadTree();
}

bool	HFrameList::loadFrame(QDomElement element){
	QString name=element.attribute("name","");
	if(name==""){
		QMessageBox::critical(0, "HRS Reconstruction System", tr("Frame name can't be null"));
		return false;
	}
	QImage image;
	if(!image.load(element.attribute("image_file",""))){
		QMessageBox::critical(0, "HRS Reconstruction System", tr("Can't load image: ")+element.attribute("image_file",""));
		return false;
	}
	QString description=element.attribute("description", tr("No description."));
	QString frame_type=element.attribute("default_frame_type", "gluLookAt");
	if(!HFrameParamList::hasParam(frame_type)){
		QMessageBox::critical(0, "HRS Reconstruction System", tr("Unknown default frame type: ")+frame_type);
		return false;
	}
	HFrame* frame=addFrame(name, image);
	frame->setActiveParam(frame_type);
	frame->longDescription=description;
	frame->imageFile=element.attribute("image_file", "");
	frame->activeParam=element.attribute("default_frame_type");
	QDomNode dom_node=element.firstChild();
	QDomElement dom_element;
	HFrameParam* param=0;
	while(!dom_node.isNull()){
		if(dom_node.isElement()){
			element=dom_node.toElement();
			param=frame->paramList->findParam(element.tagName());
			if(param){
				if(!param->loadParam(element))
					return false;
			}
			else{
				QMessageBox::critical(0, "HRS Reconstruction System", tr("Unknown frame param:")+element.tagName());
				return false;
			}
		}
		dom_node=dom_node.nextSibling();
	}
	return true;
}

bool	HFrameList::saveFrame(QDomDocument document, QDomElement element, HFrame* frame){
	QDomElement elem=document.createElement("frame");
	QDomAttr attr=document.createAttribute("name");
	attr.setValue(frame->name);
	elem.setAttributeNode(attr);
	attr=document.createAttribute("image_file");
	attr.setValue(frame->imageFile);
	elem.setAttributeNode(attr);
	attr=document.createAttribute("description");
	attr.setValue(frame->longDescription);
	elem.setAttributeNode(attr);
	attr=document.createAttribute("default_frame_type");
	attr.setValue(frame->activeParam);
	elem.setAttributeNode(attr);
	HFrameParamList::iterator iter(frame->paramList);
	while(iter.param()){
		iter.param()->saveParam(document, elem);
		iter.goNext();
	}
	element.appendChild(elem);
	return true;
}

int	HFrameList::count(){
	return framesCount;
}
