/*
 *  Marching Cubes Demo, by glUser3f [gluser3f@gdnmail.net]
 *  Feel free to use this code in your own projects.
 *  If you do something cool with it, please email me so I can see it!
 *  
 *  Credits:
 *  Theory by Paul Bourke        [http://astronomy.swin.edu.au/~pbourke/modelling/polygonise/]
 *  OpenGL basecode by NeHe      [nehe.gamedev.net]
 *  Lookup Tables by Paul Bourke [http://astronomy.swin.edu.au/~pbourke/modelling/polygonise/]
 *  The rest is done by me, glUser3f ;)
 *
 */
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
#ifndef OBJECTCONVERTERTOTRIANGLEMESH_H
#define OBJECTCONVERTERTOTRIANGLEMESH_H

#include <list>

/**
	@author Hramchenko <user@localhost.localdomain>
*/

class HObjectConverterToTriangleMesh{
	public:
		class GridPoint{
			public:
				GridPoint();
				~ GridPoint();
			public:	
				float	X;
				float	Y;
				float	Z;
				float Value;
		};
		class Point{
			public:
				Point();
				~Point();
			public:
				float	X;
				float Y;
				float	Z;
		};
		class Triangle{
			public:
				Triangle();
				~Triangle();
			public:
				Point Points[3];
				Point Normal;
		};
		class GridCell{
			public:
				GridCell();
				~GridCell();
			public:
				GridPoint* Points[8];
		};
		class Parameters{
			public:
				Parameters();
				~Parameters();
			public:
				char*** Voxels;		
				int StepCount;
				float IsoLevel;
		};
	public:
		HObjectConverterToTriangleMesh();
		~HObjectConverterToTriangleMesh();
		void	Convert();
		void	SetParameters(HObjectConverterToTriangleMesh::Parameters params);
		std::list<Triangle>	GetTriangles();
	private:
		int	Go();
		void	CalculateGrids();
		int	PolygoniseAndInsert(const GridCell* grid, float isoLevel);
		HObjectConverterToTriangleMesh::Point	Interpolate(float isoLevel, const GridPoint* gp1, const GridPoint* gp2);
		void	ConnectGrids();
		void	AllocateTables();
		void	DeallocateTables();
		void	CalculateNormal(Triangle& tri);
	private:
		int	ItsSize;
		float	ItsIsoLevel;
		char***	ItsVoxels;
		GridPoint***	ItsGridPoints;
		GridCell***	ItsGridCells;
		std::list<Triangle> ItsTriangles;
		HObjectConverterToTriangleMesh::Parameters* ItsParameters;
		static int EdgeTable[256];
		static int TriangleTable[256][16];
};

#endif
