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
#ifndef HGLSCREEN_H
#define HGLSCREEN_H

/**
	@author Hramchenko <Hramchenko@bk.ru>
*/

#include <QtOpenGL>

class QWidget;
class HModelViewer;
class HModelViewerC;
class HModelViewerT;
class HVoxel;
class HVirtualTrackball;
class	HReconstruction;

class HGLScreen: public QGLWidget{
		Q_OBJECT
	public:
		HGLScreen(QWidget* parent);
   ~HGLScreen();
	 static HGLScreen*	instance();
	 void	initializeGL();
	 void resizeGL(int width, int height);
	 void paintGL();
	 void	clearReconstruction();
	 void	mouseMoveEvent(QMouseEvent* event);
	 void	mousePressEvent(QMouseEvent* event);
	 void	mouseReleaseEvent(QMouseEvent* event);
	 void	wheelEvent(QWheelEvent* event);
	public slots:
		void	frameChangedST(QString);
		void	frameParamsChangedST(QString);
		void	startReconstructionST();
		void	stopReconstructionST();
		void	clearReconstructionST();
		void	viewAsMeshST(bool checked);
	signals:
		void	reconstructionCompleted();
		void	reconstructionStarted();
		void	reconstructionStopped();
		void	reconstructionMessage(QString);
	private:
		HVirtualTrackball* virtualTrackball;
		HReconstruction*	reconstruction; 
		HModelViewerC*	modelViewerC;
		HModelViewerT*	modelViewerT;
		HModelViewer*	modelViewer;
		bool	stop;
		bool	clearModel;
		static HGLScreen*	_instance;
};

#endif
