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
#ifndef HFRAMEPARAMMATRIX_H
#define HFRAMEPARAMMATRIX_H

/**
	@author Hramchenko <Hramchenko@bk.ru>
*/

#include "hframeparam.h"

class HFrameParamMatrix: public HFrameParam{
	public:
    HFrameParamMatrix();
    ~HFrameParamMatrix();
		QString	paramName();
		virtual void	setGL(int width, int height);
		virtual	bool	loadParam(QDomElement element);
		bool	saveParam(QDomDocument document, QDomElement element);
	public:
		float	aa;
		float	ab;
		float	ac;
		float	ba;
		float	bb;
		float	bc;
		float	ca;
		float	cb;
		float	cc;
};

#endif
