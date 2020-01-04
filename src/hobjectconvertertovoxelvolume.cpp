/***************************************************************************
 *   Copyright (C) 2006 by Hramchenko   *
 *   user@localhost.localdomain   *
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
#include "hobjectconvertertovoxelvolume.h"

#include <string.h>

#include "hvoxel.h"

HObjectConverterToVoxelVolume::Parameters::Parameters(){
	Root=0;
	StepCount=0;
}

HObjectConverterToVoxelVolume::Parameters::~Parameters(){
}

HObjectConverterToVoxelVolume::HObjectConverterToVoxelVolume(){
	ItsParameters=new HObjectConverterToVoxelVolume::Parameters;
	ItsVoxels=0;
}

HObjectConverterToVoxelVolume::~HObjectConverterToVoxelVolume(){
	if(ItsVoxels){
		long count=1;
		int i,j;
		for(int i=0;i<ItsParameters->StepCount;i++)
			count*=2;
		count+=2;
		for(i=0;i<count;i++){
			for(j=0;j<count;j++)
				delete[] ItsVoxels[i][j];
			delete[] ItsVoxels[i];
		}
		delete[] ItsVoxels;
		ItsVoxels=0;
	}
	delete ItsParameters; 
}

void	HObjectConverterToVoxelVolume::SetParameters(HObjectConverterToVoxelVolume::Parameters& params){
	*ItsParameters=params;
}

char***	HObjectConverterToVoxelVolume::GetVoxels(){
	return ItsVoxels;
}

void	HObjectConverterToVoxelVolume::Convert(){
	if(!(ItsParameters->Root&&ItsParameters->StepCount))
		return;
	long count=1;
	int i,j,k;
	for(int i=0;i<ItsParameters->StepCount;i++)
		count*=2;
	count+=2;
	ItsVoxels=new char**[count];
	for(i=0;i<count;i++){
		ItsVoxels[i]=new char*[count];
		for(j=0;j<count;j++) 
			ItsVoxels[i][j]=new char[count];		
	}
	for(i=0;i<count;i++)
		for(j=0;j<count;j++) 
			for(k=0;k<count;k++) 
				ItsVoxels[i][j][k]=0;
	FillCube(ItsParameters->Root);
} 

void	HObjectConverterToVoxelVolume::FillCube(HVoxel* cube){
	if(!cube)
		return;
	int i,j,k;
	long count=1;
	for(int i=0;i<ItsParameters->StepCount;i++)
		count*=2;
	switch((int)cube->type){
		case 0:
			break;
		case 1:
			for(k=0;k<count*cube->size;k++)
				for(j=0;j<count*cube->size;j++)
					for(i=0;i<count*cube->size;i++)
						ItsVoxels[i+(int)(count*cube->x)][j+(int)(count*cube->y)][k+(int)(count*cube->z)]=1;
			break;
		case 2:
			if(cube->subvoxels[0].type!=3)
				for(i=0;i<8;i++)
					FillCube(&cube->subvoxels[i]);
			else
				ItsVoxels[(int)(count*cube->x)][(int)(count*cube->y)][(int)(count*cube->z)]=1;
			break;
		default:
			break;
	}
	return;
}
