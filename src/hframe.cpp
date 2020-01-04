/***************************************************************************
 *   Copyright (C) 2007 by Hramchenko                                      *
 *   hramchenko@bk.ru                                                      *
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
 ***************************************************************************/
#include "hframe.h"

#include <QImage>
#include <QLabel>
#include <QScrollArea>

#include "hframeparam.h"
#include "hframeparamlist.h"

HFrame::HFrame(QString frame_name,QImage frame_image): QObject(){
	previousFrame=0;
	nextFrame=0;
	imageData=0;
	label=new QLabel();
	area=new QScrollArea();
	area->setWidgetResizable(true);
	area->setWidget(label);
	label->setStyleSheet("QLabel {\n	background-image: url(:/AlphaBgr/alphabgr.png);\n    border-width: 3px;\n    border-style: solid;\n	border-color:rgb(117, 117, 117);\n}");
	loadImage(frame_image);
	name=frame_name;
	paramList=new HFrameParamList();
	activeParam=paramList->defaultParam();
	imageFile="";
	label->setScaledContents(true);
	longDescription=tr("No description.");
}

HFrame::~HFrame(){
	if(imageData)
		delete[] imageData;
	delete paramList;
	if(area)
		delete area;
}

void	HFrame::setActiveParam(QString param){
	if(HFrameParamList::hasParam(name))
		activeParam=param;
	else
		activeParam=paramList->defaultParam();
}

HFrameParam*	HFrame::findParam(QString param){
	return paramList->findParam(param);
}	

void	HFrame::loadImage(QImage& img){
	image=img;
	QImage alpha=image.createAlphaMask();
	imageWidth=alpha.width();
	imageHeight=alpha.height();
	if(imageData)
		delete[] imageData;
	imageData=new char[imageWidth*imageHeight];
	int i, j;
	for(j=0; j<imageHeight; j++){
		for(i=0; i<imageWidth;i++)
			imageData[i+j*imageWidth]=qRed(alpha.pixel(i, j)); 
	}
	label->setPixmap(QPixmap::fromImage(image));
}

void	HFrame::setGL(int width, int height){
	paramList->findParam(activeParam)->setGL(width, height);
}

char*	HFrame::data(){
	return imageData;
}

int	HFrame::width(){
	return imageWidth;
}

int	HFrame::height(){
	return imageHeight;
}



