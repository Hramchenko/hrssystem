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
#ifndef HFRAMEPARAMSDOCK_H
#define HFRAMEPARAMSDOCK_H

/**
	@author Hramchenko <Hramchenko@bk.ru>
*/

#include <QDockWidget>
#include <QString>

class HFrameParamsDock: public QDockWidget{
		Q_OBJECT
	public:
		HFrameParamsDock(QWidget* parent);
    ~HFrameParamsDock();
	public slots:
		void	selectImageFileST();
		void	imageFileChangedST(QString file);
		void	changeFrameDescriptionST();
		void	frameNameChangedST(QString name);
		void	gluLookAtSelectedST();
		void	glMatrixSelectedST();
		void	frameSelectedST(QString name);
	signals:
		void	frameNameChanged(QString, QString);
		void	imageChanged(QString);
	public:
		static QString	currentFrame;
};

#endif
