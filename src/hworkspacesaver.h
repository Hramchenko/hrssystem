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
#ifndef HWORKSPACESAVER_H
#define HWORKSPACESAVER_H

/**
	@author Hramchenko <Hramchenko@bk.ru>
*/

#include <QString>
#include <QDomDocument>
#include <QObject>

class HWorkspaceSaver: public QObject{
public:
    HWorkspaceSaver();
    ~HWorkspaceSaver();
		bool	saveWorkspace(QString filename);
	protected:
		void	saveWorkspace(QDomDocument document);
		void	saveProject(QDomDocument document, QDomElement element);
		void	saveFrames(QDomDocument document, QDomElement element);
};

#endif