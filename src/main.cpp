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

#include <QtWidgets/QApplication>
#include <QString>
#include <QSplashScreen>

#include "hmainwindow.h"

QApplication* application;

int	main(int argc, char **argv){
	application=new QApplication(argc, argv);
	QSplashScreen splash(QPixmap(":/SplashScreen/splash.png"));
	splash.show();
	if (!QGLFormat::hasOpenGL() || !QGLPixelBuffer::hasOpenGLPbuffers()) {
		QMessageBox::information(0, "HRS Reconstruction System", QObject::tr("This system does not support OpenGL/pbuffers."));
		return -1;
	}
	HMainWindow* main_window=new HMainWindow();
	main_window->show();
	splash.finish(main_window);
	return application->exec();
}

