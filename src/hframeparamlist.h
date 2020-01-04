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
#ifndef HFRAMEPARAMLIST_H
#define HFRAMEPARAMLIST_H

/**
	@author Hramchenko <Hramchenko@bk.ru>
*/

#include <QString>

class HFrameParam;

class HFrameParamList {
	public:
		class iterator{
			public:
				iterator(HFrameParamList* param_list);
				~iterator();
				HFrameParam*	param();
				void	goNext();
				void	goBegin();
			private:
				HFrameParam*	currentParam;
				HFrameParamList*	paramList;
		};
	public:
    HFrameParamList();
    ~HFrameParamList();
		HFrameParam*	findParam(QString name);
		static bool	hasParam(QString name);
		QString	defaultParam();
	protected:
		void	addParam(HFrameParam* param);
		void	loadParams();
	protected:
		HFrameParam*	root;
		static HFrameParamList	_sampleParam;
	protected:
		friend class	HFrameParamList::iterator;
};

#endif
