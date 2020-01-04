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
#include "hdocumentstab.h"

#include <QToolButton>
#include <QImage>
#include <QLabel>
#include <QFileDialog>
#include <QScrollArea>

#include "hframe.h"
#include "hframelist.h"

HDocumentsTab::HDocumentsTab(QWidget* parent): QTabWidget(parent){
	closeTabBtn=new QToolButton(this);
	closeTabBtn->setIcon(QIcon(":/CloseTab/tab-close.png"));
	closeTabBtn->setAutoRaise(true);
	setCornerWidget(closeTabBtn);
	connect(closeTabBtn, SIGNAL(pressed()), this, SLOT(closeTabST()));
}

HDocumentsTab::~HDocumentsTab(){
}

void	HDocumentsTab::insertFrameST(QString name){
	HFrame* frame=HFrameList::instance()->findFrame(name);
	if(!frame)
		return;
	int index=insertTab(1, frame->area, frame->name);
	setCurrentIndex(index);
}

void	HDocumentsTab::selectFrameST(QString name){
	HFrame* frame=HFrameList::instance()->findFrame(name);
	if(!frame)
		return;
	int index=indexOf(frame->area);
	if(index==-1)
		insertFrameST(name);
	else
		setCurrentIndex(index);
	emit(frameSelected(name));
}

void	HDocumentsTab::pageSelectedST(int id){
  QString name = tabText(id);
  if(name!=tr("3D Model"))
    emit(frameSelected(name));
}

void	HDocumentsTab::closeTabST(){
	if(currentIndex()!=0)
		removeTab(currentIndex());
}

void	HDocumentsTab::closePageST(QString name){
	HFrame* frame=HFrameList::instance()->findFrame(name);
	if(!frame)
		return;
	int index=indexOf(frame->area);
	if(index!=-1)
		removeTab(index);
}

void	HDocumentsTab::frameNameChangedST(QString old_name, QString new_name){
	HFrame* frame=HFrameList::instance()->findFrame(old_name);
	if(!frame)
		return;
	int index=indexOf(frame->area);
	setTabText(index, new_name);
}
