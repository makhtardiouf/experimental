/*****************************************************************
 * $Id: proto.c 3 2007-04-27 21:54:32Z makhtar $
 * Copyright (C) 2006-2007 by Makhtar Diouf
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
 
/** Prototype of the Textual User Interface */

#include <ncurses.h>
#include <menu.h>
#include <panel.h>
#include <stdlib.h>
#include <ctype.h>
#include <signal.h>
#include <stdlib.h>

void handle_resize(int signum);

  int screen_w;
  int screen_h;
  WINDOW* mainWindow;
  WINDOW* url;
  WINDOW* local;
  WINDOW* remote;
  WINDOW* transferView;
  WINDOW* status;

  FILE* debugout;

int main(void)
{
  int ch;
  FILE* fp;

  ITEM** menu_items;
  MENU* menu;

  /*  ITEM* item; */
  char* choices[] = {"File", "Control", "View", "Bookmark", 
		     "Tools", "Settings", "Help", NULL};
  int totalChoices = (int)(sizeof(choices)/sizeof(choices[0]));
  int i;
  int localX = 1;
  int localY = 1;

  /*  PANEL* localPan;
    PANEL* remotePan;
  */
  int panelWidth =  40;
  int panelHeight = 25;
  int panelStartX = 1;
  int panelStartY = 10;

  initscr();
  start_color();
  /*   keypad(stdscr, TRUE); */
  noecho();
  curs_set(0);   /* make the cursor invisible */
  init_pair(1, COLOR_CYAN, COLOR_BLACK);

  signal(SIGWINCH, handle_resize);

  getmaxyx(stdscr, screen_h, screen_w);

  debugout = fopen("log", "w");
  if(!debugout)
  {
      perror("Enable to create log file");
      return EXIT_FAILURE;
  }

  fprintf(debugout, "\nStartup screen size is %dX%d\n", 
	  screen_w, screen_h);

  mainWindow = newwin(screen_h, screen_w, 0, 0);
  keypad(mainWindow, TRUE);
  box(mainWindow, 0, 0);
  wattron(mainWindow, A_BOLD);
  mvwprintw(mainWindow, 2, screen_w - 50, "eDimExch");
  wrefresh(mainWindow);
  wattroff(mainWindow, A_BOLD);

  menu_items = (ITEM**)calloc(totalChoices, sizeof(ITEM*));
  for(i = 0; i < totalChoices; ++i)
    menu_items[i] = new_item(choices[i], NULL);

  menu = new_menu((ITEM**)menu_items);
  set_menu_win(menu, mainWindow);
  /*  set_menu_sub(menu, derwin(mainWindow, 50, 30, 2, 2)); */
  set_menu_format(menu, 1, totalChoices);
  set_menu_back(menu, A_REVERSE);
  post_menu(menu);

  wattron(mainWindow, A_BOLD);
/*   wattron(mainWindow, A_BLINK); */
  mvwprintw(mainWindow, panelStartY - 5, panelStartX + 20, "Host:");
/*   wattroff(mainWindow, A_BLINK); */
  wattroff(mainWindow, A_BOLD);
  url = subwin(mainWindow, 2.5 , (3 * panelWidth) / 2 , 
	       panelStartY - 5, panelStartX + 25);
  box(url, 0, 0);

  local = subwin(mainWindow, panelHeight + 1 , 
		 panelWidth, panelStartY, panelStartX);
  /*     keypad(local, TRUE); */
  box(local, 0, 0);

  wattron(mainWindow, A_BOLD);
  mvwprintw(mainWindow, panelStartY + 3, 
	    panelStartX + panelWidth + panelWidth/3, "F3");
  wattroff(mainWindow, A_BOLD);
  wattron(mainWindow, A_REVERSE);
  wprintw(mainWindow, " Upload >> ");
  wattroff(mainWindow, A_REVERSE);

  wattron(mainWindow, A_BOLD);
  mvwprintw(mainWindow, panelStartY+ 6, 
	    panelStartX + panelWidth + panelWidth/3, "F4");
  wattroff(mainWindow, A_BOLD);
  wattron(mainWindow, A_REVERSE);
  wprintw(mainWindow, "<< Download");
  wattroff(mainWindow, A_REVERSE);

  transferView = subwin(mainWindow, panelHeight - 9, 
			panelWidth + 1 , panelStartY + 10, 
			panelStartX + panelWidth);
  box(transferView, 0, 0);

  remote = subwin(mainWindow, panelHeight + 1, 
		  panelWidth, panelStartY, 
		  panelStartX + panelWidth + 40 + 1 );
  /*     keypad(local, TRUE); */
  box(remote, 0, 0);

  wattron(mainWindow, A_BOLD);
  mvwprintw(mainWindow, panelStartY + panelHeight + 2, 
	    panelStartX + panelWidth/2, "F5");
  wattroff(mainWindow, A_BOLD);
  wattron(mainWindow, A_REVERSE);
  wprintw(mainWindow, "Connect");
  wattroff(mainWindow, A_REVERSE);

  wattron(mainWindow, A_BOLD);
  mvwprintw(mainWindow, panelStartY + panelHeight + 2, 
	    panelStartX + panelWidth + panelWidth/3, "F6");
  wattroff(mainWindow, A_BOLD);
  wattron(mainWindow, A_REVERSE);
  wprintw(mainWindow, "Disconnect");
  wattroff(mainWindow, A_REVERSE);

  wattron(mainWindow, A_BOLD);
  mvwprintw(mainWindow, panelStartY + panelHeight + 2, 
	    panelStartX + (2*panelWidth) + panelWidth/3, "F7");
  wattroff(mainWindow, A_BOLD);
  wattron(mainWindow, A_REVERSE);
  wprintw(mainWindow, "Quit");
  wattroff(mainWindow, A_REVERSE);

  status = subwin(mainWindow, 6, screen_w - 2, 
		  panelStartY + panelHeight + 4 , panelStartX);
  box(status, 0, 0);

  mvwprintw(mainWindow, panelStartY + panelHeight + 5, panelStartX + 1, 
	    "Dimorphic data Exchanger: Ready...");

  /*     localPan = new_panel(local); */
  /*     show_panel(localPan);  */
  /*     update_panels(); */

  touchwin(mainWindow);
  wrefresh(mainWindow);

  fp = fopen("cache", "r");
  if(fp != NULL)
  {
    mvwprintw(local, localY, 1, "");
    while( (ch = fgetc(fp)) != EOF )
    {
      if(isspace(ch))
      {
        localX = 1;
        wmove(local, ++localY, localX);
      }
      mvwprintw(local, localY, localX, "%c", ch);
      ++localX;
    }
    fclose(fp);
  }

  box(local, 0, 0);
  touchwin(local);
  wrefresh(local);

  /*     wgetch(local);   */
  while(1)
    if( (ch = wgetch(mainWindow)) == KEY_F(7) )
    {
      unpost_menu(menu);
      free_menu(menu);
      for(i = 0; i < totalChoices; ++i)
        free_item(menu_items[i]);

      /* del_panel(localPan); */
      delwin(url);
      delwin(local);
      delwin(transferView);
      delwin(remote);
      delwin(status);
      delwin(mainWindow);
      endwin();
      fclose(debugout);
      return 0;
    }
}


void handle_resize(int signum)
{
    getmaxyx(stdscr, screen_h, screen_w);
    fprintf(debugout, "\nCurrent screen size is %dX%d\n", 
	    screen_w, screen_h);
    //resizeterm(screen_h, screen_w);
    wresize(mainWindow, screen_h, screen_w);

    wrefresh(url);
    wrefresh(local);
    wrefresh(remote);
    wrefresh(transferView);
    wrefresh(status);
    wrefresh(mainWindow);

    touchwin(mainWindow);
    signal(signum, SIG_DFL);
    raise(signum);
}
