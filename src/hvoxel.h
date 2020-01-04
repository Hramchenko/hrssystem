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
#ifndef HVOXEL_H
#define HVOXEL_H

/**
	@author Hramchenko <user@localhost.localdomain>
*/

class HVoxel{
	public:
    HVoxel();
    ~HVoxel();
		void	createSubvoxels();
		void	deleteSubvoxels();
	public:
		float x;
		float y;
		float z;
		float size;
		char	type;	//	0-void, 1-filled, 2-must be subdivided, 3-not analyzed.
		HVoxel*	subvoxels;
};

#endif
