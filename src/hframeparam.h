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
#ifndef HFRAMEPARAM_H
#define HFRAMEPARAM_H

/**
	@author Hramchenko <Hramchenko@bk.ru>
*/

#include <QString>
#include <QDomDocument>

class HFrameParamList;

class HFrameParam{
	public:
    HFrameParam();
    virtual ~HFrameParam();
		virtual QString	paramName()=0;
		virtual void	setGL(int width, int height)=0;
		virtual	bool	loadParam(QDomElement element)=0;
		virtual bool	saveParam(QDomDocument document, QDomElement element)=0;
	protected:
		HFrameParam*	nextParam;
	protected:
		friend class HFrameParamList;
};

#endif
