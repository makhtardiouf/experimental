/*****************************************************************
 * $Id: gui.hpp 7 2007-05-22 15:03:42Z makhtar $
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

/** GUI prototype */
#ifndef EDIMGUI_HPP
#define EDIMGUI_HPP

#define LIBSSH_STATIC

#include "GuiMenu.hpp"
#include "GuiSftp.hpp"
#include "GuiTermEmu.hpp"
#include "ui_infomsg.h"
#include <sstream>
#include <string>
#include <cstring>
#include <iostream>
#include "libssh/libssh.h"
#include "libssh/sftp.h"


class Gui : public QMainWindow
{
    Q_OBJECT

public:
    Gui(QWidget* papa = 0);

    enum
    {
        PASSW,
        KBDINTERACT,
        PUBKEY,
        MAXCHARS = 15,
        MAXHEIGHT = 25
    };

public slots:
    inline void SetHostname(const char* str)
    {
        Sftp->host->setText(QString(str));
    }

private slots:
    void AddToList(QString file);

    void Cancel();

    inline void CdUpLocal()
    {
        chdir("..");
        UpdateLocalFs();
    }

    void CdUpRemote()
    {};

    void Download();

    inline void EnableConnectBt()
    {
        concancBt->setCurrentWidget(connectBt);
        connectBt->setEnabled(true);
    }

    void ExecLoginMethod();

    int GetLoginMethod() const;

    inline const char* Host() const
    {
        return Sftp->host->text().toStdString().c_str();
    }

    int InteractLogin();

    int ListRemoteFs();

    void Login();

    void Logout();

    inline char* Pass() const
    {
        return strdup(Sftp->detailsWin->passw->text()
                      .toStdString().c_str());
    }

    inline int PasswLogin()
    {
        ShowMsg("Trying password login...");
        return ssh_userauth_password(sshSession, User(), Pass());
    }

    inline int Port() const
    {
        return Sftp->detailsWin->port->value();
    }

    void Progress(int fake = 0);

    void Progress(int value, bool showText);

    int PubKeyLogin();

    void UpdateLocalFs();

    void Retry();

    /** Set initial size and look of the main window */
    void SetAesthetics();

    /** Connect signals to slots */
    void SetCallbacks();

    /** Set the title of the main window. */
    void SetTitle(std::string postfix = "");

    void ShowMsg(QString msg);

    inline void SysError(const char* msg)
    {
        ShowMsg(QString(msg).append(strerror(errno)));
    }

    inline QString SftpError()
    {
        return QString(ssh_get_error(sshSession));
    }

    void TellAbout();

    void Upload()
    {};

    inline char* User() const
    {
        return strdup(Sftp->detailsWin->user->text().toStdString().c_str());
    }

private:
    Ui::InfoDialog infoDialog;

    AbstractMenu* Menu;

    QTabWidget* TabGroup;
    AbstractSftp* Sftp;
    int SftpIndex;
    AbstractTermEmu* TermEmu;
    int TermEmuIndex;

    QPushButton* connectBt;
    QPushButton* cancelBt;
    QStackedWidget* concancBt;
    QPushButton* disconnectBt;
    QPushButton* quitBt;

    QTextEdit* msgField;
    QProgressBar* pgress;
    QStackedWidget* info;

    int loginMethod;
    QHash<QString, bool> isDir;
    QTcpSocket* socket;

    ssh_session sshSession;
   // ssh_options_e sshOptions;
    sftp_session sftpSession;
    sftp_attributes sftpAttribs;
};
#endif
