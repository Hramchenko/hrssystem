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
#ifndef HMAINWINDOW_H
#define HMAINWINDOW_H

/**
	@author Hramchenko <Hramchenko@bk.ru>
*/

#include <ui_HMainWindow.h>

class QMainWindow;
class HModelViewer;
class QApplication;
class HFrameParamsDock;
class HGluLookAtParamsDock;
class HGLMatrixParamsDock;
class HProjectFilesDock;

extern QApplication* application;

class HMainWindow: public QMainWindow, private Ui::HMainWindow {
		Q_OBJECT
	public:
		HMainWindow(QWidget* parent=0);
    virtual ~HMainWindow();
		static HMainWindow*	instance();
	public slots:
		void	reconstructionStartedST();
		void	reconstructionStoppedST();
		void	reconstructionComplitedST();
		void	reconstructionMessageST(QString message);
		void	helpAboutST();
		void	closeWindowST();
	private:
		void	setViewAsMeshActionEnabled(bool state);
		void	setStartReconstructionEnabled(bool state);
	private:
		static HMainWindow*	_instance;
	protected:
		friend class HFrameParamsDock;
		friend class HGluLookAtParamsDock;
		friend class HGLMatrixParamsDock;
		friend class HProjectFilesDock;
};

#endif
