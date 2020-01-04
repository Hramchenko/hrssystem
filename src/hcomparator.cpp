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
#include "hcomparator.h"

#include <QPixmap>

#include "hframe.h"
#include "hvoxel.h"

#include <iostream>

HComparator::HComparator(QGLWidget* parent, int max_width, int max_height){
	pixelBuffer = new QGLPixelBuffer(QSize(max_width, max_height), parent->format(), parent);
	initPixelBuffer();
	currentData=0;
	currentData=new char[max_width*max_height];
}

HComparator::~HComparator(){
	pixelBuffer->makeCurrent();
	glDeleteLists(voxelList,1);
	delete pixelBuffer;
	delete[] currentData;
}

char	HComparator::compare(HVoxel* voxel, HFrame* frame){
	if(!(voxel && frame))
		return -1;
	currentVoxel=voxel;
	currentFrame=frame;
	render();
	return compareData();
}

void	HComparator::initPixelBuffer(){
	pixelBuffer->makeCurrent();
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_LIGHTING);
	glDisable(GL_BLEND);
	glEnable(GL_AUTO_NORMAL);
	glEnable(GL_VERTEX_ARRAY);
	glClearColor(0, 0, 0, 0);
	glColor3f(1, 1, 1);
	createVoxelList();
}

void	HComparator::createVoxelList(){
	static GLfloat vertices[]={
		0, 0, 0, 1, 0, 0,
		1, 1, 0, 0, 1, 0,
 		0, 0, 1, 1, 0, 1,
 		1, 1, 1, 0, 1, 1
	};
	static GLubyte indices[]={
		0, 3, 2, 1, 2, 3, 7, 6,
		0, 4, 7, 3, 1, 2, 6, 5,
 		4, 5, 6, 7, 0, 1, 5, 4
	};
	voxelList=glGenLists(1);
	glVertexPointer(3, GL_FLOAT, 0, vertices);
	glMatrixMode(GL_MODELVIEW);
	glNewList(voxelList, GL_COMPILE);
	glTranslatef(0, -1, 0);
	glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, indices);
	glEndList();
}

inline void	HComparator::render(){
	pixelBuffer->makeCurrent();
	glLoadIdentity();
	glClear(GL_COLOR_BUFFER_BIT);
	currentFrame->setGL(currentFrame->width(), currentFrame->height());
	glTranslatef(-0.5, -0.5, -0.5);
	glTranslatef(currentVoxel->x, currentVoxel->y, currentVoxel->z);
	glScalef(currentVoxel->size, currentVoxel->size, currentVoxel->size);
	glCallList(voxelList);
	glFlush();
}

inline void	HComparator::getBounds(int& min_x, int& min_y, int& max_x, int& max_y, int width, int height){
	int i, j, k;
	static float mat[4][4], prj[4][4], mpm[4][4];
	glGetFloatv(GL_MODELVIEW_MATRIX, &mat[0][0]);
	glGetFloatv(GL_PROJECTION_MATRIX, &prj[0][0]);
	for(i=0; i<4; i++)
		for(j=0; j<4; j++)
			mpm[j][i]=mat[i][0]*prj[0][j]+
				      mat[i][1]*prj[1][j]+
					  mat[i][2]*prj[2][j]+
					  mat[i][3]*prj[3][j];
	static float res[4];
	static GLfloat vert[]={
		0, 0, 0, 1,
 		0, 0, 1, 1,
		0, 1, 0, 1,
 		0, 1, 1, 1,
		1, 0, 0, 1,
 		1, 0, 1, 1,
		1, 1, 0, 1,
 		1, 1, 1, 1
	};
	float minx, miny, maxx, maxy;
	minx=miny=10000;
	maxx=maxy=-10000;
	for(k=0; k<8; k++){
		for(i=0; i<4; i++){
			res[i]=0;
			for(j=0; j<4; j++)
				res[i]+=mpm[i][j]*vert[k*4+j];
		}
		if(res[0]>maxx)
			maxx=res[0];
		if(res[0]<minx)
			minx=res[0];
		if(res[1]>maxy)
			maxy=res[1];
		if(res[1]<miny)
			miny=res[1];
	}
	min_x=(minx+1)/2*width;
	max_x=(maxx+1)/2*width;
	min_y=(miny+1)/2*height;
	max_y=(maxy+1)/2*height;
	if(min_x<0)
		min_x=0;
	if(min_y<0)
		min_y=0;
	if(max_x>width)
		max_x=width;
	if(max_y>height)
		max_y=height;
}

inline char	HComparator::compareData(){
	int min_x, min_y, max_x, max_y;
	long int width, height;
	long int WIDTH, _width;
	char* image=currentFrame->data();
	getBounds(min_x, min_y, max_x, max_y, currentFrame->width(), currentFrame->height());
	width=max_x-min_x;
	height=max_y-min_y;
	WIDTH=currentFrame->width();
	glReadPixels(min_x, min_y, width, height, GL_RED, GL_UNSIGNED_BYTE, currentData);
	_width=width;
	if(_width%4)
		_width+=4-_width%4;
	static long int i, j, k;
	static long int I, J, K;
	static char result;
	static char foto;
	static char cube;
	k=0;
	K=min_y*WIDTH;
	result=4;
	for(j=0; j<height; j++){
		J=j+min_y;
		for(i=0; i<width; i++){
			I=i+min_x;
			foto=image[K+I];
			cube=currentData[k+i];
			if(cube){
				if(foto){
					if(result==1)
						return 2;
					result=0;
				}
				else{
					if(result==0)
						return 2;
					result=1;
				}
			}
		}
		K+=WIDTH;
		k+=_width;
	}
	if(result==4)
		result=1;
	return result;
}
