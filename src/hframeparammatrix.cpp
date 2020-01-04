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
#include "hframeparammatrix.h"

#include <QtOpenGL>

HFrameParamMatrix::HFrameParamMatrix() {
	ab=ac=0;
	ba=bc=0;
	ca=cb=0;
	aa=bb=cc=1;
}


HFrameParamMatrix::~HFrameParamMatrix() {
}

QString	HFrameParamMatrix::paramName(){
	return "glMatrix";
}

void	HFrameParamMatrix::setGL(int width, int height){
	GLfloat matrix[]={
		aa, ab, ac, 0,
		ba, bb, bc, 0,
		ca, cb, cc, 0,
		 0,  0,  0, 1
	};
	glMatrixMode(GL_PROJECTION);
	glViewport(0, 0, width, height);
	glLoadIdentity();
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	if(width>height)
		glScalef((float)height/(float)width, 1, 1);
	else
		glScalef(1, (float)width/(float)height, 1);
	glScalef(2, 2, 2);
	glMultMatrixf(matrix);
}

bool	HFrameParamMatrix::loadParam(QDomElement element){
	QDomNode dom_node=element.firstChild();
	QDomElement dom_element;
	aa=element.attribute("aa","1.0").toDouble();
	ab=element.attribute("ab","0.0").toDouble();
	ac=element.attribute("ac","0.0").toDouble();
	ba=element.attribute("ba","0.0").toDouble();
	bb=element.attribute("bb","1.0").toDouble();
	bc=element.attribute("bc","0.0").toDouble();
	ca=element.attribute("ca","0.0").toDouble();
	cb=element.attribute("cb","0.0").toDouble();
	cc=element.attribute("cc","1.0").toDouble();
	return true;
}

bool	HFrameParamMatrix::saveParam(QDomDocument document, QDomElement element){
	QDomElement elem=document.createElement("glMatrix");
	QDomAttr attr=document.createAttribute("aa");
	attr.setValue(QString::number(aa));
	elem.setAttributeNode(attr);
	attr=document.createAttribute("ab");
	attr.setValue(QString::number(ab));
	elem.setAttributeNode(attr);
	attr=document.createAttribute("ac");
	attr.setValue(QString::number(ac));
	elem.setAttributeNode(attr);
	attr=document.createAttribute("ba");
	attr.setValue(QString::number(ba));
	elem.setAttributeNode(attr);
	attr=document.createAttribute("bb");
	attr.setValue(QString::number(bb));
	elem.setAttributeNode(attr);
	attr=document.createAttribute("bc");
	attr.setValue(QString::number(bc));
	elem.setAttributeNode(attr);
	attr=document.createAttribute("ca");
	attr.setValue(QString::number(ca));
	elem.setAttributeNode(attr);
	attr=document.createAttribute("cb");
	attr.setValue(QString::number(cb));
	elem.setAttributeNode(attr);
	attr=document.createAttribute("cc");
	attr.setValue(QString::number(cc));
	elem.setAttributeNode(attr);
	element.appendChild(elem);
	return true;
}



