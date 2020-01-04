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
#ifndef HCOMPARATOR_H
#define HCOMPARATOR_H

/**
	@author Hramchenko <user@localhost.localdomain>
*/

#include <QtOpenGL>

class	HVoxel;
class	HFrame;

class HComparator{
	public:
		HComparator(QGLWidget* parent, int max_width, int max_height);
    virtual ~HComparator();
		char	compare(HVoxel* voxel, HFrame* frame);
	private:
		void	initPixelBuffer();
		void	createVoxelList();
		void	render();
		char	compareData();
		void	getBounds(int& min_x, int& min_y, int& max_x, int& max_y, int width, int height);
	private:
		HVoxel*	currentVoxel;
		HFrame*	currentFrame;
		int	voxelList;
		char*	currentData;
		QGLPixelBuffer*	pixelBuffer;
};

#endif
