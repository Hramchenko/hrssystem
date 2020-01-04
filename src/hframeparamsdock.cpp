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
#include "hframeparamsdock.h"

#include <QLabel>
#include <QRadioButton>
#include <QImage>

#include "hmainwindow.h"
#include "hframelist.h"
#include "hframe.h"
#include "heditdescriptiondialog.h"

QString	HFrameParamsDock::currentFrame="";

HFrameParamsDock::HFrameParamsDock(QWidget* parent): QDockWidget(parent){
}

HFrameParamsDock::~HFrameParamsDock(){
}

void	HFrameParamsDock::selectImageFileST(){
	QString file=QFileDialog::getOpenFileName(this, tr("Please select image file"), "", "*.png");
	if(file!="")
		HMainWindow::instance()->ImageFileLe->setText(file);
}

void	HFrameParamsDock::imageFileChangedST(QString file){
	QImage img;
	if(!img.load(file))
		return;
	HFrame* frame=HFrameList::instance()->findFrame(currentFrame);
	if(!frame)
		return;
	frame->loadImage(img);
	frame->imageFile=file;
	HMainWindow::instance()->FramePreviewLbl->setPixmap(*frame->label->pixmap());
	emit(imageChanged(currentFrame));
}

void	HFrameParamsDock::changeFrameDescriptionST(){
	QString description=HEditDescriptionDialog::getDescription(this);
	if(description=="")
		return;
	HMainWindow::instance()->FrameDescriptionLbl->setText(description);
	HFrame* frame=HFrameList::instance()->findFrame(currentFrame);
	if(!frame)
		return;
	frame->longDescription=description;
}

void	HFrameParamsDock::frameNameChangedST(QString name){
	if(currentFrame==""||name=="")
		return;
	HFrame* frame=HFrameList::instance()->findFrame(name);
	if(frame)
		return;
	frame=HFrameList::instance()->findFrame(currentFrame);
	if(!frame)
		return;
	frame->name=name;
	currentFrame=name;
	emit(frameNameChanged(currentFrame, name));
}

void	HFrameParamsDock::gluLookAtSelectedST(){
	HFrame* frame=HFrameList::instance()->findFrame(currentFrame);
	if(!frame)
		return;
	frame->activeParam="gluLookAt";
}

void	HFrameParamsDock::glMatrixSelectedST(){
	HFrame* frame=HFrameList::instance()->findFrame(currentFrame);
	if(!frame)
		return;
	frame->activeParam="glMatrix";
}

void	HFrameParamsDock::frameSelectedST(QString name){
	currentFrame=name;
	HFrame* frame=HFrameList::instance()->findFrame(name);
	if(!frame)
		return;
	HMainWindow::instance()->FramePreviewLbl->setPixmap(*frame->label->pixmap());
	HMainWindow::instance()->FrameNameLe->setText(frame->name);
	HMainWindow::instance()->FrameDescriptionLbl->setText(frame->longDescription);
	HMainWindow::instance()->ImageFileLe->setText(frame->imageFile);
	if(frame->activeParam=="gluLookAt")
		HMainWindow::instance()->gluLookAtRb->setChecked(true);
	if(frame->activeParam=="glMatrix")
		HMainWindow::instance()->glMatrixRb->setChecked(true);
}
