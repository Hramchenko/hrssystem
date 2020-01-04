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
#ifndef HRECONSTRUCTION_H
#define HRECONSTRUCTION_H

/**
	@author Hramchenko <user@localhost.localdomain>
*/

#include "hframelist.h"

#include <list>
#include <QString>
#include <QObject>

class QGLWidget;

class HFrame;
class	HVoxel;
class	HComparator;

class HReconstruction: public QObject{
	public:
		HReconstruction(QGLWidget* parent);
    ~HReconstruction();
		void	prepare();
		void	start();
		void	clear();
		bool	idle();
		bool	isReconstructionComplited();
		QString	status();
	public:
		std::list<HFrame*>	frames;
		HVoxel*	model;
		int	precision;
		int idleValue;
	private:
		void	process();
	private:
		friend 	void*	HReconstructionThreadFunction(void* params);
	private:
		int	currentPrecision;
		long int	voxelsCount;
		long int	nextVoxelsCount;
		long int	currentVoxelNum;
		std::list<HVoxel*>*	currentVoxels;
		std::list<HVoxel*>*	nextVoxels;
		std::list<HVoxel*>::iterator	currentVoxel;
		HComparator*	comparator;
		int	workFlag;
		bool	newReconstructionFlag;
		QGLWidget* parentWidget;
};

#endif
