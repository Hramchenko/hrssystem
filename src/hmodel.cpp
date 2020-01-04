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
#include "hmodel.h"

#include "hframelist.h"
#include "hvoxel.h"

HModel*	HModel::_instance=0;

HModel::HModel(): QObject(){
	name=tr("MODEL");
	_root=new HVoxel();
}

HModel::~HModel(){
}

void	HModel::clearModel(){
	name=tr("MODEL");
	file="";
	HFrameList::instance()->clearList();
	if(_root)
		delete _root;
	_root=new HVoxel();
}

void	HModel::clearRoot(){
	if(_root)
		delete _root;
	_root=new HVoxel();
}

HModel* HModel::instance(){
	if(!_instance)
		_instance=new HModel();
	return _instance;
}

HVoxel*	HModel::root(){
	return _root;
}

