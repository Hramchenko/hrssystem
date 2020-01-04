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
#ifndef HFRAMELIST_H
#define HFRAMELIST_H

/**
	@author Hramchenko <Hramchenko@bk.ru>
*/

#include <QString>
#include <QImage>
#include <QDomDocument>
#include <QObject>

class HFrame;

class HFrameList: public QObject{
	public:
		class iterator{
			public:
				iterator();
				~iterator();
				HFrame*	frame();
				void	goNext();
				void	goBegin();
			private:
				HFrame*	currentFrame;
		};
	public:
		static HFrameList*	instance();
    ~HFrameList();
		HFrame*	addFrame(QString name, QImage image);
		HFrame*	findFrame(QString name);
		void	removeFrame(QString name);
		void	clearList();
		bool	loadFrame(QDomElement element);
		bool	saveFrame(QDomDocument document, QDomElement element, HFrame* frame);
		int	count();
	protected:
		HFrameList();
	protected:
		HFrame*	root;
		static HFrameList* _instance;
		int	framesCount;
	protected:
		friend class iterator;
};

#endif
