/***************************************************************************
 *
 * $Header: /usr/local/cvsroot/utils/ytree/stat.c,v 1.18 2010/10/10 08:34:23 werner Exp $
 *
 * Statistik-Modul
 *
 ***************************************************************************/


#include "ytree.h"



static void PrettyPrintNumber(int y, int x, LONGLONG number);


void DisplayDiskStatistic(void)
{
  const char *fmt= "[%-14s]";
  char buff[17];
  *buff = '\0';
  
  sprintf( buff, fmt, statistic.file_spec);
  PrintMenuOptions( stdscr, 2, COLS - 15, buff, MENU_COLOR, HIMENUS_COLOR);
  PrettyPrintNumber( 5,  COLS - 14, statistic.disk_space / (LONGLONG)1024 );
  PrintOptions( stdscr, 7,  COLS - 21, "[DISK Statistics]" );
  PrettyPrintNumber( 9, COLS - 14, statistic.disk_total_files );
  PrettyPrintNumber( 10, COLS - 14, statistic.disk_total_bytes );
  PrettyPrintNumber( 12, COLS - 14, statistic.disk_matching_files );
  PrettyPrintNumber( 13, COLS - 14, statistic.disk_matching_bytes );
  PrettyPrintNumber( 15, COLS - 14, statistic.disk_tagged_files );
  PrettyPrintNumber( 16, COLS - 14, statistic.disk_tagged_bytes );
  PrintOptions( stdscr, 17, COLS - 21, "[Current Directory ]");
  DisplayDiskName();
  return;
}



void DisplayAvailBytes(void)
{
  PrettyPrintNumber( 5,  COLS - 14, statistic.disk_space / (LONGLONG)1024 );
  RefreshWindow( stdscr );
}




void DisplayFileSpec(void)
{
  mvwprintw( stdscr, 2,  COLS - 15, "%-14s", statistic.file_spec );
  RefreshWindow( stdscr );
}


void DisplayDiskName(void)
{
  const char *fmt= "[%-14s]";
  char buff[17];
  
  sprintf( buff, fmt, statistic.disk_name);
  PrintMenuOptions( stdscr, 4, COLS - 15, buff, MENU_COLOR, HIMENUS_COLOR);
  RefreshWindow( stdscr );
}




void DisplayDirStatistic(DirEntry *dir_entry)
{
  char format[10];
  char buffer[PATH_LENGTH + 1];
  char auxbuff[PATH_LENGTH + 1];

  *auxbuff = *buffer = '\0';
  (void) sprintf( format, "%%-%ds", COLS - 7 );
  (void) GetPath( dir_entry, statistic.path );
  if (dir_entry -> not_scanned)
     strcat(statistic.path,"*");
  sprintf(auxbuff, format, FormFilename( buffer, statistic.path, COLS - 7 ));
  wmove( stdscr, 0, 6);
  wclrtoeol( stdscr);
  Print( stdscr, 0, 6, auxbuff, HIMENUS_COLOR);
  PrintOptions( stdscr, 7,  COLS - 21, "[DIR Statistics ]" );
  PrettyPrintNumber( 9, COLS - 14, dir_entry->total_files );
  PrettyPrintNumber( 10, COLS - 14, dir_entry->total_bytes );
  PrettyPrintNumber( 12, COLS - 14, dir_entry->matching_files );
  PrettyPrintNumber( 13, COLS - 14, dir_entry->matching_bytes );
  PrettyPrintNumber( 15, COLS - 14, dir_entry->tagged_files );
  PrettyPrintNumber( 16, COLS - 14, dir_entry->tagged_bytes );
  PrintOptions( stdscr, 17, COLS - 21, "[Current File     ]" );
  RefreshWindow( stdscr );
  return;
}





void DisplayDirTagged(DirEntry *dir_entry)
{
  PrettyPrintNumber( 15, COLS - 14, dir_entry->tagged_files );
  PrettyPrintNumber( 16, COLS - 14, dir_entry->tagged_bytes );
  
  RefreshWindow( stdscr );
}



void DisplayDiskTagged(void)
{
  PrettyPrintNumber( 15, COLS - 14, statistic.disk_tagged_files );
  PrettyPrintNumber( 16, COLS - 14, statistic.disk_tagged_bytes );
  
  RefreshWindow( stdscr );
}



void DisplayDirParameter(DirEntry *dir_entry)
{
  char *p, *f;
  char format[10];
  char buffer[PATH_LENGTH + 1];
  char auxbuff[PATH_LENGTH + 1];

  p = strrchr( dir_entry->name, FILE_SEPARATOR_CHAR ); 
 
  if( p == NULL ) f = dir_entry->name;
  else            f = p + 1;
 
  (void) sprintf( format, "%%-%ds", COLS - 7 );
  (void) GetPath( dir_entry, statistic.path );
  if (dir_entry -> not_scanned)
     strcat(statistic.path,"*");
  sprintf(auxbuff, format, FormFilename(buffer,statistic.path,COLS-7));
  wmove( stdscr, 0, 6);
  wclrtoeol( stdscr);
  Print( stdscr, 0, 6, auxbuff, HIMENUS_COLOR);
  *auxbuff = '\0';
  sprintf(auxbuff, "[%-17s]", CutFilename(buffer, f, 17));
  PrintMenuOptions( stdscr, 18, COLS - 19, auxbuff, MENU_COLOR, HIMENUS_COLOR);
  PrettyPrintNumber( 19, COLS - 14, (LONGLONG) dir_entry->total_bytes );
  RefreshWindow( stdscr );
}






void DisplayGlobalFileParameter(FileEntry *file_entry)
{
  char buffer1[PATH_LENGTH+1];
  char buffer2[PATH_LENGTH+1];
  char format[10];

  (void) sprintf( format, "[%%-%ds]", COLS - 7 );
  (void) GetPath( file_entry->dir_entry, buffer1 );
  FormFilename( buffer2, buffer1, COLS - 7 );
  sprintf(buffer1, format, buffer2);
  wmove( stdscr, 0, 6);
  wclrtoeol( stdscr);
  PrintMenuOptions( stdscr, 0, 6, buffer1, GLOBAL_COLOR, HIGLOBAL_COLOR);
  CutFilename( buffer1, file_entry->name, 17 );
  sprintf( buffer2, "[%-17s]", buffer1 );
  PrintMenuOptions( stdscr, 18, COLS - 19, buffer2, GLOBAL_COLOR, HIGLOBAL_COLOR);
  PrettyPrintNumber( 19, COLS - 14, (LONGLONG) file_entry->stat_struct.st_size );
  RefreshWindow( stdscr );
}




void DisplayFileParameter(FileEntry *file_entry)
{
  char buffer[18*6];
  char auxbuff[20*6];
  sprintf( auxbuff, "[%-17s]", CutFilename( buffer, file_entry->name, 17 ) );
  PrintMenuOptions( stdscr, 18, COLS - 19, auxbuff, MENU_COLOR, HIMENUS_COLOR);
  PrettyPrintNumber( 19, COLS - 14, (LONGLONG)file_entry->stat_struct.st_size );
  RefreshWindow( stdscr );
}



void PrettyPrintNumber(int y, int x, LONGLONG number)
{
  char buffer[20];
  long billion, million, thousand, one;
  
  *buffer = 0;
  billion  = (long) ( number / (LONGLONG) 1000000000 );
  million  = (long) ( number % (LONGLONG) 1000000000 / (LONGLONG) 1000000 );
  thousand = (long) ( ( number % (LONGLONG) 1000000 ) / (LONGLONG) 1000 );
  one      = (long) ( number % (LONGLONG) 1000 );

  if( billion ){
     /* "123123123123" */
     sprintf( buffer, "[%3ld%03ld%03ld%03ld]", billion, million, thousand, one);
     PrintMenuOptions( stdscr, y, x, buffer, MENU_COLOR, HIMENUS_COLOR);
     }
  else if( million ) {
     /* " 123,123,123" */
     sprintf( buffer, "[ %3ld%c%03ld%c%03ld]", million, number_seperator, thousand, number_seperator, one);
     PrintMenuOptions( stdscr, y, x, buffer, MENU_COLOR, HIMENUS_COLOR);
     }
  else if( thousand ) {
     /* "     123,123" */
     sprintf( buffer, "[     %3ld%c%03ld]", thousand, number_seperator, one);
     PrintMenuOptions( stdscr, y, x, buffer, MENU_COLOR, HIMENUS_COLOR);
     }
  else {
     /* "         123" */
     sprintf( buffer, "[         %3ld]", one);
     PrintMenuOptions( stdscr, y, x, buffer, MENU_COLOR, HIMENUS_COLOR);
     }
 return;
}



