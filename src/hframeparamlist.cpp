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
#include "hframeparamlist.h"

#include "hframeparam.h"
#include "hframeparamlookat.h"
#include "hframeparammatrix.h"

HFrameParamList	HFrameParamList::_sampleParam;

HFrameParamList::iterator::iterator(HFrameParamList* param_list){
	paramList=param_list;
	currentParam=paramList->root;
}

HFrameParamList::iterator::~iterator(){
}

HFrameParam*	HFrameParamList::iterator::param(){
	return currentParam;
}

void	HFrameParamList::iterator::goNext(){
	if(currentParam)
		currentParam=currentParam->nextParam;
}

void	HFrameParamList::iterator::goBegin(){
	currentParam=paramList->root;
}

HFrameParamList::HFrameParamList(){
	root=0;
	loadParams();
}

HFrameParamList::~HFrameParamList(){
	HFrameParam* temp;
	while(root){
		temp=root->nextParam;
		delete root;
		root=temp;
	}
}

HFrameParam*	HFrameParamList::findParam(QString name){
	HFrameParam* param=root;
	while(param){
		if(param->paramName()==name)
			return param;
		param=param->nextParam;
	}
	return 0;
}

QString	HFrameParamList::defaultParam(){
	return "gluLookAt";
}

void	HFrameParamList::addParam(HFrameParam* param){
	param->nextParam=root;
	root=param;
}

void	HFrameParamList::loadParams(){
	addParam(new HFrameParamLookAt());
	addParam(new HFrameParamMatrix());
}

bool	HFrameParamList::hasParam(QString name){
	if(_sampleParam.findParam(name))
		return true;
	return false;
}


