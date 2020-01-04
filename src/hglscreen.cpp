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
#include "hglscreen.h"

#include <GL/glu.h>

#include <QAction>
#include <QDialog>
#include <QMessageBox>

#include "hvoxel.h"
#include "hmodelviewer.h"
#include "hmodelviewerc.h"
#include "hmodelviewert.h"
#include "hvirtualtrackball.h"

#include "hcomparator.h"
#include "hframe.h"
#include "hframelist.h"
#include "hreconstruction.h"
#include "hmodel.h"
#include "hmainwindow.h"

#include <iostream>

HGLScreen*	HGLScreen::_instance=0;

HGLScreen::HGLScreen(QWidget* parent): QGLWidget(parent){
	virtualTrackball=new HVirtualTrackball(this);
	stop=true;
	_instance=this;
	clearModel=false;
}

HGLScreen::~HGLScreen() {
	delete modelViewerC;
	delete modelViewerT;
	delete virtualTrackball;
	delete reconstruction;
	_instance=0;
}

HGLScreen*	HGLScreen::instance(){
	return _instance;
}

void HGLScreen::initializeGL(){
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_FOG);
	glEnable(GL_BLEND);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_LIGHTING);
	glShadeModel(GL_SMOOTH);
	glDepthFunc(GL_LEQUAL);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST );
	GLfloat material_specular[]={0.8, 0.8, 0.8, 0.5};
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, material_specular);
	GLfloat material_diffuse[]={0.5, 0.5, 1.0, 0.5};
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, material_diffuse);
	GLfloat material_emission[]={0.5, 0.5, 1.0, 0.5};
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, material_emission);
//	glClearColor(0.1, 0.1, 0.1, 0.0);
	glClearColor(0.0, 0.0, 0.0, 0.0);
	reconstruction=new HReconstruction(this);
	modelViewerC=new HModelViewerC();
	modelViewerT=new HModelViewerT();
	modelViewer=modelViewerC;
	modelViewer->prepare(HModel::instance()->root());
	reconstruction->model=HModel::instance()->root();
	reconstruction->idleValue=30;
}

void HGLScreen::resizeGL(int width, int height){
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0, 0, width, height);
	gluPerspective(20.0, (float)width/(float)height, 0.5, 10.0);
	gluLookAt(4.0, 0.0, 4.0, 0.0, 0.0, 0.0, 4.0, 4.0, 4.0);
	glMatrixMode(GL_MODELVIEW);
}

void HGLScreen::paintGL(){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	virtualTrackball->applyTransform();
	glPushMatrix();
	glRotatef(90, 0, 1, 0);
	glTranslatef(-0.5, -0.5, -0.5);
	modelViewer->view();
	glPopMatrix();
	glFlush();
	if(!stop){
		if(!reconstruction->isReconstructionComplited()){
			emit(reconstructionMessage(reconstruction->status()));
			reconstruction->idle();
		}
		else
			stop=true;
	}
}

void	HGLScreen::viewAsMeshST(bool is_mesh){
	if(reconstruction->isReconstructionComplited()&&is_mesh){
		modelViewer=modelViewerT;
		modelViewerT->precision=reconstruction->precision-1;
		modelViewer->prepare(HModel::instance()->root());
	}
	else
		modelViewer=modelViewerC;
	updateGL();
}

void	HGLScreen::startReconstructionST(){
	if(clearModel){
		if(QMessageBox::question(0, "HRS Reconstruction System",	tr("Some of frames was changed. Do you want to clear reconstruction?"), QMessageBox::Yes| QMessageBox::No)==QMessageBox::Yes){
			HModel::instance()->clearRoot();
			reconstruction->clear();
			reconstruction->model=HModel::instance()->root();
		}
		clearModel=false;
	}
	updateGL();
	if(reconstruction->isReconstructionComplited())
    reconstruction->precision=QInputDialog::getInt(0, "HRS Reconstruction System", tr("Please enter precision:"), 6, 1, 10, 1);
	reconstruction->prepare();
	reconstruction->start();
	emit(reconstructionStarted());
	stop=false;
	modelViewer=modelViewerC;
	while(!(reconstruction->isReconstructionComplited()||stop)){
		updateGL();
		application->processEvents();
	}
	modelViewer->prepare(HModel::instance()->root());
	if(reconstruction->isReconstructionComplited())
		emit(reconstructionCompleted());
	updateGL();
}

void	HGLScreen::stopReconstructionST(){
	stop=true;
	updateGL();
	emit(reconstructionStopped());
}

void	HGLScreen::clearReconstruction(){
	HModel::instance()->clearModel();
	reconstruction->clear();
	reconstruction->model=HModel::instance()->root();
	reconstruction->idleValue=600;
}

void	HGLScreen::clearReconstructionST(){
	if(QMessageBox::question(0, "HRS Reconstruction System",	tr("Do really you want to clear reconstruction?"), QMessageBox::Yes| QMessageBox::No)==QMessageBox::Yes){
		HModel::instance()->clearRoot();
		reconstruction->clear();
		reconstruction->model=HModel::instance()->root();
		clearModel=false;
	}
}
void	HGLScreen::mouseMoveEvent(QMouseEvent* event){
	virtualTrackball->mouseMoveEvent(event);
}

void	HGLScreen::mousePressEvent(QMouseEvent* event){
	virtualTrackball->mousePressEvent(event);
}

void	HGLScreen::mouseReleaseEvent(QMouseEvent* event){
	virtualTrackball->mouseReleaseEvent(event);
}

void	HGLScreen::wheelEvent(QWheelEvent* event){
	virtualTrackball->wheelEvent(event);
}

void	HGLScreen::frameChangedST(QString){
}

void	HGLScreen::frameParamsChangedST(QString){
	clearModel=true;
}
