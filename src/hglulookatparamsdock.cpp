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
#include "hglulookatparamsdock.h"

#include "hframelist.h"
#include "hmainwindow.h"
#include "hframe.h"
#include "hframeparamlist.h"
#include "hframeparamlookat.h"

HGluLookAtParamsDock::HGluLookAtParamsDock(QWidget* parent): QDockWidget(parent){
	currentFrame="";
}

HGluLookAtParamsDock::~HGluLookAtParamsDock(){
}

void	HGluLookAtParamsDock::frameSelectedST(QString name){
	currentFrame=name;
	HFrame* frame=HFrameList::instance()->findFrame(currentFrame);
	if(!frame)
		return;
	HFrameParamLookAt* param=(HFrameParamLookAt*)frame->findParam("gluLookAt");
	HMainWindow::instance()->lookAtEyeXLbl->setText(QString::number(param->eyeX));
	HMainWindow::instance()->lookAtEyeYLbl->setText(QString::number(param->eyeY));
	HMainWindow::instance()->lookAtEyeZLbl->setText(QString::number(param->eyeZ));
	HMainWindow::instance()->lookAtCenterXLbl->setText(QString::number(param->centerX));
	HMainWindow::instance()->lookAtCenterYLbl->setText(QString::number(param->centerY));
	HMainWindow::instance()->lookAtCenterZLbl->setText(QString::number(param->centerZ));
	HMainWindow::instance()->lookAtUpXLbl->setText(QString::number(param->upX));
	HMainWindow::instance()->lookAtUpYLbl->setText(QString::number(param->upY));
	HMainWindow::instance()->lookAtUpZLbl->setText(QString::number(param->upZ));
}

void	HGluLookAtParamsDock::applyST(){
	HFrame* frame=HFrameList::instance()->findFrame(currentFrame);
	if(!frame)
		return;
	HFrameParamLookAt* param=(HFrameParamLookAt*)frame->findParam("gluLookAt");
	param->eyeX=HMainWindow::instance()->lookAtEyeXLbl->text().toDouble();
	param->eyeY=HMainWindow::instance()->lookAtEyeYLbl->text().toDouble();
	param->eyeZ=HMainWindow::instance()->lookAtEyeZLbl->text().toDouble();
	param->centerX=HMainWindow::instance()->lookAtCenterXLbl->text().toDouble();
	param->centerY=HMainWindow::instance()->lookAtCenterYLbl->text().toDouble();
	param->centerZ=HMainWindow::instance()->lookAtCenterZLbl->text().toDouble();
	param->upX=HMainWindow::instance()->lookAtUpXLbl->text().toDouble();
	param->upY=HMainWindow::instance()->lookAtUpYLbl->text().toDouble();
	param->upZ=HMainWindow::instance()->lookAtUpZLbl->text().toDouble();
	emit(frameParamsChanged(currentFrame));
}



