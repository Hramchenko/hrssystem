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
#include "hglmatrixparamsdock.h"

#include "hframelist.h"
#include "hmainwindow.h"
#include "hframe.h"
#include "hframeparamlist.h"
#include "hframeparammatrix.h"

HGLMatrixParamsDock::HGLMatrixParamsDock(QWidget* parent): QDockWidget(parent){
	currentFrame="";
}

HGLMatrixParamsDock::~HGLMatrixParamsDock(){
}

void	HGLMatrixParamsDock::frameSelectedST(QString name){
	currentFrame=name;
	HFrame* frame=HFrameList::instance()->findFrame(currentFrame);
	if(!frame)
		return;
	HFrameParamMatrix* param=(HFrameParamMatrix*)frame->findParam("glMatrix");
	HMainWindow::instance()->MatrixAALbl->setText(QString::number(param->aa));
	HMainWindow::instance()->MatrixABLbl->setText(QString::number(param->ab));
	HMainWindow::instance()->MatrixACLbl->setText(QString::number(param->ac));
	HMainWindow::instance()->MatrixBALbl->setText(QString::number(param->ba));
	HMainWindow::instance()->MatrixBBLbl->setText(QString::number(param->bb));
	HMainWindow::instance()->MatrixBCLbl->setText(QString::number(param->bc));
	HMainWindow::instance()->MatrixCALbl->setText(QString::number(param->ca));
	HMainWindow::instance()->MatrixCBLbl->setText(QString::number(param->cb));
	HMainWindow::instance()->MatrixCCLbl->setText(QString::number(param->cc));
}

void	HGLMatrixParamsDock::applyST(){
	HFrame* frame=HFrameList::instance()->findFrame(currentFrame);
	if(!frame)
		return;
	HFrameParamMatrix* param=(HFrameParamMatrix*)frame->findParam("glMatrix");
	param->aa=HMainWindow::instance()->MatrixAALbl->text().toDouble();
	param->ab=HMainWindow::instance()->MatrixABLbl->text().toDouble();
	param->ac=HMainWindow::instance()->MatrixACLbl->text().toDouble();
	param->ba=HMainWindow::instance()->MatrixBALbl->text().toDouble();
	param->bb=HMainWindow::instance()->MatrixBBLbl->text().toDouble();
	param->bc=HMainWindow::instance()->MatrixBCLbl->text().toDouble();
	param->ca=HMainWindow::instance()->MatrixCALbl->text().toDouble();
	param->cb=HMainWindow::instance()->MatrixCBLbl->text().toDouble();
	param->cc=HMainWindow::instance()->MatrixCCLbl->text().toDouble();
	emit(frameParamsChanged(currentFrame));
}

