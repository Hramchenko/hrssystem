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
#ifndef HFRAME_H
#define HFRAME_H

/**
	@author Hramchenko <user@localhost.localdomain>
*/

#include <QString>
#include <QImage>
#include <QObject>

#include "hframelist.h"

class QLabel;
class QScrollArea;
class HFrameParam;
class HFrameParamList;

class HFrame: public QObject{
	public:
		HFrame(QString frame_name, QImage frame_image);
		~HFrame();
		void	setGL(int width, int height);
		void	setActiveParam(QString param);
		void	loadImage(QImage& img);
	public:	
		QImage	image;
		QScrollArea*	area;
		QLabel*	label;
		char*	data();
		int	width();
		int	height();
		HFrameParam*	findParam(QString param);	
		QString name;
		QString activeParam;
		QString	longDescription;
		QString	imageFile;
	protected:
		HFrame*	previousFrame;
		HFrame*	nextFrame;
		HFrameParamList*	paramList;
		char*	imageData;
		int	imageWidth;
		int	imageHeight;
	protected:
		friend class HFrameList;
		friend class HFrameList::iterator;
};

#endif
