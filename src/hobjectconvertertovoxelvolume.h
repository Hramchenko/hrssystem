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
#ifndef OBJECTCONVERTERTOVOXELVOLUME_H
#define OBJECTCONVERTERTOVOXELVOLUME_H

/**
	@author Hramchenko <user@localhost.localdomain>
*/

class HVoxel;

class HObjectConverterToVoxelVolume{
	public:
		class Parameters{
			public:
				Parameters();
				~Parameters();
			public:
				HVoxel* Root;
				int	StepCount;
		};
	public:
		HObjectConverterToVoxelVolume();
		~HObjectConverterToVoxelVolume();
		void	Convert();
		void	DeleteVolume();
		void	SetParameters(HObjectConverterToVoxelVolume::Parameters& params);
		char***	GetVoxels();
	private:
		void	FillCube(HVoxel* cube);
	private:
		HObjectConverterToVoxelVolume::Parameters* ItsParameters;
		char***	ItsVoxels;
};

#endif
