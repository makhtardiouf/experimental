/*****************************************************************
 * $Id: GuiSftp.hpp 7 2007-05-22 15:03:42Z makhtar $
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

#ifndef GUISFTP_HPP
#define GUISFTP_HPP

#include "edimexch.h"
#include "qt.hpp"
#include <iostream>

/** Connection settings popup interface */
class AbstractDetailsWin : public QDialog
{
    Q_OBJECT

public:
    AbstractDetailsWin(QWidget* papa = 0);

public slots:
    void SelectKey();

public:
    QGroupBox* connBox;
    QSpinBox* port;
    QLineEdit* user;
    QLineEdit* passw;

    QCheckBox* passMeth;
    QCheckBox* kbdIntMeth;
    QCheckBox* pubKeyMeth;
    QComboBox* keyFile;

    QPushButton* connectBt;
    QPushButton* cancelBt;
};


/** SFTP interface */
class AbstractSftp : public QWidget
{
    Q_OBJECT

    friend class Gui;

public:
    AbstractSftp(QWidget* papa = 0);

public slots:
    void RedispTest()
    {
        std::cout<< "test..\n" ;
        //localfsDir->cd(localfs->currentItem()->text());
        // ListLocalFiles();
    }

    void UpdateLocalFs();
    void UpdateLocalFs(QListWidgetItem* item);
    void ListLocalFiles();

    //void mouseDoubleClickEvent(QMouseEvent* e);

private slots:
    void EnableDetailsBt();

private:
    QSignalSpy* dblClickSpy;
    QSignalSpy* selectionSpy;

    QLineEdit* host;
    AbstractDetailsWin* detailsWin;
    QComboBox* keyFile;
    QPushButton* detailsBt;

    QComboBox* localPath;
    QPushButton* cdUpLocBt;
    //QDir* localfsDir;
    QDirModel* localfsModel;
    QTreeView* localfs;

    QPushButton* uploadBt;
    QPushButton* downloadBt;

    QComboBox* remotePath;
    QPushButton* cdUpRemBt;
    QListWidget* remotefs;

    QStandardItemModel* jobsModel;
    QTableView* jobs;

    QMenu* contextMenu;
    QAction* uploadFile;
    QAction* downloadFile;
    QAction* encryptFile;
    QAction* decryptFile;
};
#endif
