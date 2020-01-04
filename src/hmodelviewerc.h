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
#ifndef HMODELVIEWERC_H
#define HMODELVIEWERC_H

/**
	@author Hramchenko <hramchenko@bk.ru>
*/

#include "hmodelviewer.h"

class HModelViewerC: public HModelViewer{
	public:
    HModelViewerC();
    virtual ~HModelViewerC();
		void	prepare(HVoxel* root);
		void	view();
		void	clear();
	private:
		void	drawVoxel(HVoxel* voxel);
		void	drawCube();
	private:
		HVoxel*	rootVoxel;
};

#endif
