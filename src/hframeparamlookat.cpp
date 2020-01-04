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
#include "hframeparamlookat.h"

#include <GL/glu.h>
#include <QtOpenGL>

#define sqr(x) x*x

HFrameParamLookAt::HFrameParamLookAt(){
	eyeX=0;
	eyeY=0;
	eyeZ=2;
	centerX=0;
	centerY=0;
	centerZ=0;
	upX=0;
	upY=1;
	upZ=2;
}

HFrameParamLookAt::~HFrameParamLookAt(){
}

QString	HFrameParamLookAt::paramName(){
	return QString::fromUtf8("gluLookAt");
}

void	HFrameParamLookAt::setGL(int width, int height){
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0, 0, width, height);
	float r=sqrt(sqr(eyeX-centerX)+sqr(eyeY-centerY)+sqr(eyeZ-centerZ));
	if(width>height)
		glOrtho(-0.5*((float)height/(float)width), 0.5*((float)height/(float)width), -0.5*((float)height/(float)width), 0.5*((float)height/(float)width), -2, r+2);
	else
		glOrtho(-0.5*((float)width/(float)height), 0.5*((float)width/(float)height), -0.5*((float)width/(float)height), 0.5*((float)width/(float)height), -2, r+2);
	glMatrixMode(GL_MODELVIEW);
	gluLookAt(eyeX, eyeY, eyeZ, centerX, centerY, centerZ, upX, upY, upZ);
}

bool	HFrameParamLookAt::loadParam(QDomElement element){
	QDomNode dom_node=element.firstChild();
	QDomElement dom_element;
	eyeX=element.attribute("eyeX","0.0").toDouble();
	eyeY=element.attribute("eyeY","0.0").toDouble();
	eyeZ=element.attribute("eyeZ","0.0").toDouble();
	centerX=element.attribute("centerX","0.0").toDouble();
	centerY=element.attribute("centerY","0.0").toDouble();
	centerZ=element.attribute("centerZ","0.0").toDouble();
	upX=element.attribute("upX","0.0").toDouble();
	upY=element.attribute("upY","0.0").toDouble();
	upZ=element.attribute("upZ","0.0").toDouble();
	return true;
}

bool	HFrameParamLookAt::saveParam(QDomDocument document, QDomElement element){
	QDomElement elem=document.createElement("gluLookAt");
	QDomAttr attr=document.createAttribute("eyeX");
	attr.setValue(QString::number(eyeX));
	elem.setAttributeNode(attr);
	attr=document.createAttribute("eyeY");
	attr.setValue(QString::number(eyeY));
	elem.setAttributeNode(attr);
	attr=document.createAttribute("eyeZ");
	attr.setValue(QString::number(eyeZ));
	elem.setAttributeNode(attr);
	attr=document.createAttribute("centerX");
	attr.setValue(QString::number(centerX));
	elem.setAttributeNode(attr);
	attr=document.createAttribute("centerY");
	attr.setValue(QString::number(centerY));
	elem.setAttributeNode(attr);
	attr=document.createAttribute("centerZ");
	attr.setValue(QString::number(centerZ));
	elem.setAttributeNode(attr);
	attr=document.createAttribute("upX");
	attr.setValue(QString::number(upX));
	elem.setAttributeNode(attr);
	attr=document.createAttribute("upY");
	attr.setValue(QString::number(upY));
	elem.setAttributeNode(attr);
	attr=document.createAttribute("upZ");
	attr.setValue(QString::number(upZ));
	elem.setAttributeNode(attr);
	element.appendChild(elem);
	return true;
}

