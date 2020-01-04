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
#include "hvoxel.h"

HVoxel::HVoxel(){
	y=1;
	x=z=0;
	size=1;
	type=3;
	subvoxels=0;
}

HVoxel::~HVoxel(){
	if(subvoxels)
		delete[] subvoxels; 
}

void	HVoxel::createSubvoxels(){
	if(!subvoxels)
		subvoxels=new HVoxel[8];
	int i;
	float sz=size/2;
	for(i=0;i<8;i++)
		subvoxels[i].size=sz;
	subvoxels[0].x=x;	
	subvoxels[0].y=y;	
	subvoxels[0].z=z;
	subvoxels[1].x=x;	
	subvoxels[1].y=y;	
	subvoxels[1].z=z+sz;
	subvoxels[2].x=x+sz;	
	subvoxels[2].y=y;	
	subvoxels[2].z=z+sz;
	subvoxels[3].x=x+sz;	
	subvoxels[3].y=y;	
	subvoxels[3].z=z;
	subvoxels[4].x=x;	
	subvoxels[4].y=y-sz;	
	subvoxels[4].z=z;
	subvoxels[5].x=x;	
	subvoxels[5].y=y-sz;	
	subvoxels[5].z=z+sz;
	subvoxels[6].x=x+sz;	
	subvoxels[6].y=y-sz;	
	subvoxels[6].z=z+sz;
	subvoxels[7].x=x+sz;	
	subvoxels[7].y=y-sz;	
	subvoxels[7].z=z;
	type=2;
}

void	HVoxel::deleteSubvoxels(){
	if(subvoxels)
		delete[] subvoxels; 
	subvoxels=0;
}


