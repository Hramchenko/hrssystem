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
#ifndef HDOCUMENTSTAB_H
#define HDOCUMENTSTAB_H

/**
	@author Hramchenko <Hramchenko@bk.ru>
*/

#include <QTabWidget>

class QToolButton;

class HDocumentsTab: public QTabWidget{
		Q_OBJECT
	public:
    HDocumentsTab(QWidget* parent);
    ~HDocumentsTab();
	public slots:
		void	closeTabST();
		void	closePageST(QString name);
		void	insertFrameST(QString name);
		void	selectFrameST(QString name);
    void	pageSelectedST(int id);
		void	frameNameChangedST(QString old_name, QString new_name);
	signals:
		void	frameSelected(QString name);
	private:
		QToolButton* closeTabBtn;
};

#endif
