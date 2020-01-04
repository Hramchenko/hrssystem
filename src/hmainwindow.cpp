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
#include "hmainwindow.h"

#include <stdlib.h>

#include <QMainWindow>
#include <QAction>
#include <QFileDialog>
#include <QStatusBar>
#include <QMessageBox>
#include <QSplashScreen>

#include "hworkspaceloader.h"
#include "hworkspacesaver.h"
#include "hmodel.h"

HMainWindow*	HMainWindow::_instance=0;

HMainWindow::HMainWindow(QWidget* parent): QMainWindow(parent){
	setupUi(this);
	_instance=this;
}

HMainWindow::~HMainWindow(){
	_instance=0;
}

HMainWindow*	HMainWindow::instance(){
	return _instance;
}

void	HMainWindow::setViewAsMeshActionEnabled(bool state){
	if(state)
		viewAsMeshAction->setEnabled(true);
	else
		viewAsMeshAction->setEnabled(false);
	viewAsMeshAction->setChecked(false);
}

void	HMainWindow::setStartReconstructionEnabled(bool state){
	startReconstructionAction->setEnabled(state);
	startReconstructionAction->setChecked(false);
	stopReconstructionAction->setEnabled(!state);
}

void	HMainWindow::reconstructionStartedST(){
	setViewAsMeshActionEnabled(false);
	clearReconstructionAction->setEnabled(false);
}

void	HMainWindow::reconstructionComplitedST(){
	startReconstructionAction->toggle();
	setStartReconstructionEnabled(true);
	setViewAsMeshActionEnabled(true);
	clearReconstructionAction->setEnabled(true);
	statusbar->showMessage(tr("Reconstruction complited."), 5000);
}
void HMainWindow::reconstructionStoppedST(){
	setStartReconstructionEnabled(true);
	setViewAsMeshActionEnabled(false);
	clearReconstructionAction->setEnabled(true);
	statusbar->showMessage(tr("Reconstruction stopped."), 5000);
}

void	HMainWindow::reconstructionMessageST(QString message){
	statusbar->showMessage(message);
}

void	HMainWindow::helpAboutST(){
	static QSplashScreen* splash=0;
	if(splash)
		delete splash;
	splash=new QSplashScreen(QPixmap(":/SplashScreen/splash.png"));
	splash->show();
}

void	HMainWindow::closeWindowST(){
	exit(0);
}



