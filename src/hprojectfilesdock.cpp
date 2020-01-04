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
#include "hprojectfilesdock.h"

#include <QTreeWidget>
#include <QFileDialog>
#include <QInputDialog>
#include <QImage>
#include <Qt>

#include "hmodel.h"
#include "hworkspaceloader.h"
#include "hworkspacesaver.h"
#include "hframelist.h"
#include "hmainwindow.h"
#include "hframe.h"

HProjectFilesDock* HProjectFilesDock::_instance=0;
QString	HProjectFilesDock::currentFrame="";
		
HProjectFilesDock::HProjectFilesDock(QWidget* parent): QDockWidget(parent){
	_instance=this;
	currentFrame="";
}

HProjectFilesDock::~HProjectFilesDock(){
	_instance=0;
}

void	HProjectFilesDock::reloadTree(){
	if(!_instance)
		return;
	HFrameList::iterator iter;
	HMainWindow::instance()->ProjectFilesTree->clear();
	QTreeWidget* root=HMainWindow::instance()->ProjectFilesTree;
	QTreeWidgetItem* i=new QTreeWidgetItem();
	i->setText(0, HModel::instance()->name);
	root->setHeaderItem(i);
	while(iter.frame()){
		QTreeWidgetItem* item=new QTreeWidgetItem(root);
		item->setText(0, iter.frame()->name);
		iter.goNext();
	}
	HMainWindow::instance()->ProjectFilesTree->repaint();
	currentFrame="";
}

void	HProjectFilesDock::itemActivatedST(QTreeWidgetItem* item, int column){
	emit(frameSelected(item->text(0)));
	currentFrame=item->text(0);
}

void	HProjectFilesDock::loadWorkspaceST(){
	HWorkspaceLoader l;
	QString file=QFileDialog::getOpenFileName(this, tr("Please select project file"), "", "*.xml");
	if(file!="")
		l.loadWorkspace(file);
}

void	HProjectFilesDock::saveWorkspaceST(){
	HWorkspaceSaver s;
	if(HModel::instance()->file=="")
		HModel::instance()->file=QFileDialog::getSaveFileName(this, tr("Please select project file"), "", "*.xml");
	s.saveWorkspace(HModel::instance()->file);
}

void	HProjectFilesDock::saveWorkspaceToST(){
	HWorkspaceSaver s;
	QString file=QFileDialog::getSaveFileName(this, tr("Please select project file"), "", "*.xml");
	if(file!="")
		s.saveWorkspace(file);
}

void	HProjectFilesDock::createNewWorkspaceST(){
	HWorkspaceSaver s;
	QString file=QFileDialog::getSaveFileName(this, tr("Please select project file"), "", "*.xml");
	if(file!=""){
		HModel::instance()->clearModel();
		s.saveWorkspace(file);
	}
}

void	HProjectFilesDock::frameNameChangedST(QString old_name, QString new_name){
	reloadTree();
}

void	HProjectFilesDock::addFrameST(){
	QString name=QInputDialog::getText(0, "HRS Reconstruction System", tr("Please enter frame name:"));
	if(name=="")
		return;
	HFrame* frame=HFrameList::instance()->findFrame(name);
	if(frame)
		return;
	HFrameList::instance()->addFrame(name, QImage());
	reloadTree();
	emit(frameSelected(name));
	currentFrame=name;
}

void	HProjectFilesDock::removeFrameST(){
	HFrame* frame=HFrameList::instance()->findFrame(currentFrame);
	if(!frame)
		return;
	emit(frameDeleted(currentFrame));
	HFrameList::instance()->removeFrame(currentFrame);
	reloadTree();
}



