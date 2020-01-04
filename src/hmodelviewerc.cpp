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
#include "hmodelviewerc.h"

#include <QtOpenGL>

#include "hvoxel.h"

HModelViewerC::HModelViewerC(){
}

HModelViewerC::~HModelViewerC(){
}

void	HModelViewerC::prepare(HVoxel* root){
	rootVoxel=root;
}

void	HModelViewerC::view(){
	drawVoxel(rootVoxel);
}

void	HModelViewerC::drawVoxel(HVoxel* voxel){
	if(!voxel)
		return;
	switch(voxel->type){
		case 0:
			break;
		case 1:
			glPushMatrix();
			glTranslatef(voxel->x, voxel->y, voxel->z);
			glScalef(voxel->size, voxel->size, voxel->size);
			drawCube();
			glPopMatrix();
			break;
		case 2:
			int i;
			for(i=0;i<8;i++)
				drawVoxel(&voxel->subvoxels[i]);
			break;
		default:
			glPushMatrix();
			glTranslatef(voxel->x, voxel->y, voxel->z);
			glScalef(voxel->size, voxel->size, voxel->size);
			drawCube();
			glPopMatrix();
			break;
	}
	return;
}

inline void	HModelViewerC::drawCube(){
	static GLfloat vertices[]={
		0, 0, 0,
		1, 0, 0,
		1, 1, 0,
		0, 1, 0,
		0, 0, 1,
		1, 0, 1,
		1, 1, 1,
		0, 1, 1
	};
	char indices[]={
		0, 3, 2, 1, 2, 3, 7, 6,
		0, 4, 7, 3, 1, 2, 6, 5,
		4, 5, 6, 7, 0, 1, 5, 4
	};
	glPushMatrix();
	glTranslatef(0, -1, 0);
	glEnable(GL_AUTO_NORMAL);
	glEnable(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, vertices);
	glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, indices);
	glDisable(GL_VERTEX_ARRAY);
	glPopMatrix();
}

void	HModelViewerC::clear(){
	rootVoxel=0;
}
