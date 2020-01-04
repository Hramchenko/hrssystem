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
#include "hmodelviewert.h"

#include <QtOpenGL>

#include "hobjectconvertertotrianglemesh.h"
#include "hobjectconvertertovoxelvolume.h"

HModelViewerT::HModelViewerT(){
	precision=0;
}

HModelViewerT::~HModelViewerT(){
}

void	HModelViewerT::prepare(HVoxel* root){
	clear();
	HObjectConverterToVoxelVolume vox_conv;
	HObjectConverterToVoxelVolume::Parameters vox_params;
	vox_params.Root=root;
	vox_params.StepCount=precision;
	vox_conv.SetParameters(vox_params);
	vox_conv.Convert();
	HObjectConverterToTriangleMesh tri_conv;
	HObjectConverterToTriangleMesh::Parameters tri_params;
	tri_params.Voxels=vox_conv.GetVoxels();
	tri_params.StepCount=precision;
	tri_params.IsoLevel=0.5;
	tri_conv.SetParameters(tri_params);
	tri_conv.Convert();
	triangles=tri_conv.GetTriangles();
}

void	HModelViewerT::view(){
	glPushMatrix();
	glScalef(0.5, 0.5, 0.5);
	glTranslatef(0.5, 0.5, 0.5);
	glBegin(GL_TRIANGLES);
	std::list<HObjectConverterToTriangleMesh::Triangle>::iterator i;
	for(i=triangles.begin();i!=triangles.end();i++){
		glNormal3fv((float*)&(*i).Normal);
		for(int j=0;j<3;j++)
			glVertex3fv((float*)&(*i).Points[j]);
	}	
	glEnd();
	glPopMatrix();
}

void	HModelViewerT::clear(){
	triangles.clear();
}




