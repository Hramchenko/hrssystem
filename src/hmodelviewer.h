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
#ifndef HMODELVIEWER_H
#define HMODELVIEWER_H

/**
	@author Hramchenko <hramchenko@bk.ru>
*/

class HVoxel;

class HModelViewer{
	public:
    HModelViewer();
    virtual ~HModelViewer();
		virtual void	prepare(HVoxel* root)=0;
		virtual void	view()=0;
		virtual void	clear()=0;
};

#endif
