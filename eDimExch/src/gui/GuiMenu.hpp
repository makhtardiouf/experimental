/*****************************************************************
 * $Id: GuiMenu.hpp 7 2007-05-22 15:03:42Z makhtar $
 * Copyright (C) 2006-2007 Makhtar Diouf
 * elmakdi@users.sourceforge.net
 *
 * -You can redistribute and/or modify this program
 *  under the terms of the GNU General Public License version 2.
 *  See the file COPYING for further information.
 *
 * -Vous pouvez redistribuer et/ou modifier ce programme
 *  sous les termes de la license GNU General Public version 2.
 *  Voir le fichier COPYING pour plus d'information.
 ****************************************************************/
/** Menubar prototype */

#ifndef GUIMENU_HPP
#define GUIMENU_HPP

#include "qt.hpp"

class AbstractMenu : public QMenuBar
{
    Q_OBJECT

public:
    AbstractMenu(QWidget* papa = 0);

    QMenu* File;
    QAction* fileOpen;
    QAction* fileSave;
    QAction* fileQuit;

    QMenu* Control;
    QAction* ctrlConnect;
    QAction* ctrlDownload;
    QAction* ctrlUpload;
    QAction* ctrlCancel;
    QAction* ctrlDisconnect;

    QMenu* View;
    QAction* vwToggleViewMode;
    QAction* vwShowHidden;

    QMenu* Bookmark;
    QAction* bmarkAdd;
    QAction* bmarkEdit;
    QAction* bmarkImport;
    QAction* bmarkExport;

    QMenu* Tools;
    QAction* toolTerminal;
    QAction* toolMonitor;

    QMenu* Settings;
    QAction* settingConfig;
    QAction* settingAppear;

    QMenu* Help;
    QAction* hlpAbout;
    QAction* hlpUserManual;
    QAction* hlpBWReport;
};
#endif
