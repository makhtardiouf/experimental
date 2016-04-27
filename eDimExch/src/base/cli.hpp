/*****************************************************************
 * $Id: cli.hpp 4 2007-04-27 21:57:55Z makhtar $
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

/* Command Line Interface */

#ifndef CLI_HPP
#define CLI_HPP

class Cli
{
public:
    Cli()
    {};

    /** Parse command line options and do appropriate initialization. */
    const char* Initialize(int argc, char** argv);

    /** Print application's name, version number...etc */
    void Present();

    /** Print the available command line options */
    int Usage(char** argv, bool wait_for_input = false);

    bool EnableGui()
    {
        return guiEnabled;
    }

    void LaunchTui();

private:
    bool guiEnabled;
    bool tuiEnabled;
};
#endif
