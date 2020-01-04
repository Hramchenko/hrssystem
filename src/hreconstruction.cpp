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
#include "hreconstruction.h"

#include "hframe.h"
#include "hvoxel.h"
#include "hcomparator.h"

HReconstruction::HReconstruction(QGLWidget* parent): QObject(){
	parentWidget=parent;
	workFlag=0;
	precision=1;
	idleValue=15;
	currentPrecision=0;
	newReconstructionFlag=1;
	currentVoxels=new std::list<HVoxel*>;
	nextVoxels=new std::list<HVoxel*>;
	comparator=0;
}

HReconstruction::~HReconstruction(){
	delete currentVoxels;
	delete nextVoxels;
	delete comparator;
}

void	HReconstruction::prepare(){
	if(!newReconstructionFlag)
		return;
	int width=0;
	int height=0;
	HFrameList::iterator current_frame;
	while(current_frame.frame()){
		if(current_frame.frame()->width()>width)
			width=current_frame.frame()->width();
		if(current_frame.frame()->height()>height)
			height=current_frame.frame()->height();
		current_frame.goNext();
	}
	currentVoxels->push_back(model);
	currentVoxel=currentVoxels->begin();
	comparator=new HComparator(parentWidget, width, height);
	newReconstructionFlag=0;
	workFlag=1;
	nextVoxelsCount=0;
	voxelsCount=0;
	currentVoxelNum=0;
}

void	HReconstruction::start(){
	if(!workFlag)
		prepare();
	workFlag=1;
}

void	HReconstruction::clear(){
	currentPrecision=0;
	currentVoxels->clear();
	nextVoxels->clear();
	newReconstructionFlag=1;
	workFlag=0;
	if(comparator)
		delete comparator;
	comparator=0;
}

bool	HReconstruction::isReconstructionComplited(){
	return !workFlag;
}

bool	HReconstruction::idle(){
	if(!workFlag)
		return false;
	process();
	return true;
}

QString	HReconstruction::status(){
	return tr("Reconstruction: step ")+QString::number(currentPrecision)+tr(" of ")+QString::number(precision)+tr(". Voxels analyzed: ")+QString::number(currentVoxelNum)+tr(" of ")+QString::number(voxelsCount)+tr(".");
}


void	HReconstruction::process(){
	int k=0;
	std::list<HVoxel*>* temp;
	workFlag=1;
	int i;
	HFrameList::iterator current_frame;
	for(i=currentPrecision; i<precision; i++){
		currentPrecision=i;
		for(; currentVoxel!=currentVoxels->end(); ++currentVoxel, currentVoxelNum++){
			char t;
			current_frame.goBegin();
			(*currentVoxel)->type=1;
			while(current_frame.frame()){
				t=comparator->compare(*currentVoxel, current_frame.frame());
				switch(t){
					case 0:
						(*currentVoxel)->type=0;
						goto label;
						break;
					case 2:
						(*currentVoxel)->type=2;
				}
				current_frame.goNext();
			}
			if((*currentVoxel)->type==2){
				(*currentVoxel)->createSubvoxels();
				int j;
				for(j=0; j<8; j++)
					nextVoxels->push_back(&((*currentVoxel)->subvoxels[j]));
				nextVoxelsCount+=8;
			}
			label:
			if(k++>idleValue)
				return;
		}
		temp=currentVoxels;
		temp->clear();
		currentVoxels=nextVoxels;
		nextVoxels=temp;
		currentVoxel=currentVoxels->begin();
		voxelsCount=nextVoxelsCount;
		nextVoxelsCount=0;
		currentVoxelNum=0;
	}
	workFlag=0;
	currentPrecision=precision;
}
