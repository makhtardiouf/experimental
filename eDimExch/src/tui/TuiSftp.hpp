
/* $Id: TuiSftp.hpp 2 2007-02-05 09:17:01Z elmakdi $

Interface of the _FtpTab object. */

#ifndef TUIFTPTAB_HPP
#define TUIFTPTAB_HPP

#include "CWidgets.hpp"

class _FtpTab : public NCursesPanel
{
    // The following statement allow me to set the elements of
    // the FtpTab widget to private while allow free access
    // to them from the Gui class's composites.
    friend class Tui;

public:
    _FtpTab();

private:
    NCursesFormField* url;

    NCursesFormField* user;

    NCursesFormField* passw;

    NCursesFormField* localPath;

    CButton* cdUpLocal;

    NCursesFormField* localfs;

    CButton* uploadBt;

    CButton* downloadBt;

    NCursesFormField* remotePath;

    CButton* cdUpRemote;

    NCursesFormField* remotefs;

    NCursesFormField* jobs;
};

  //} // END EDesktop namespace

#endif

// END $Id: TuiSftp.hpp 2 2007-02-05 09:17:01Z elmakdi $
