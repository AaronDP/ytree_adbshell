/***************************************************************************
 *
 * $Header: /usr/local/cvsroot/utils/ytree/passwd.c,v 1.14 2010/10/13 19:57:54 werner Exp $
 *
 * Handhabung von User-Nummern / Namen
 *
 ***************************************************************************/


#include "ytree.h"


#ifdef WIN32
#include <pwd.h>
#else

typedef struct
{
  int   uid;
  char  name[OWNER_NAME_MAX + 1];
} PasswdEntry;


extern struct passwd *getpwent(void);
#if !defined(__OpenBSD__) && !defined(__NetBSD__) && !defined( __FreeBSD__ ) && !defined( OSF1 ) && !defined( __APPLE__ )
extern void          setpwent(void);
#endif

static PasswdEntry   *passwd_array;
static unsigned int  passwd_count;

#endif /* WIN32 */


int ReadPasswdEntries(void)
{
#if !defined(WIN32) && !defined(__ANDROID__)
  int i;
  struct passwd *pwd_ptr;
  

  for( passwd_count=0; getpwent(); passwd_count++ )
    ;

  setpwent();

  if( passwd_array ) 
  {
    free( passwd_array );
    passwd_array = NULL;
  }

  if( passwd_count == 0 )
  {
    passwd_array = NULL;
  }
  else
  {
    if( ( passwd_array = (PasswdEntry *) calloc( passwd_count, 
					         sizeof( PasswdEntry )
					       ) ) == NULL )
    {
      ERROR_MSG( "Calloc Failed" );
      passwd_array = NULL;
      passwd_count = 0;
      return( 1 );
    }
  }

  for(i=0; i < (int)passwd_count; i++)
  {
    if( ( pwd_ptr = getpwent() ) == NULL )
    {
      ERROR_MSG( "Getpwent Failed" );
      if( passwd_array) free( passwd_array );
      passwd_array = NULL;
      passwd_count = 0;
      return( 1 );
    }
  
    passwd_array[i].uid = pwd_ptr->pw_uid;
    (void) strncpy( passwd_array[i].name, pwd_ptr->pw_name, OWNER_NAME_MAX );
     passwd_array[i].name[OWNER_NAME_MAX] = '\0';
  }
#endif /* ANDROID / WIN32 */

  return( 0 );
}




char *GetPasswdName(unsigned int uid)
{

/* # ifdef WIN32 */
#if defined(WIN32) || defined(__ANDROID__)

  struct passwd *pwd_ptr;

  pwd_ptr = getpwuid( uid );

  if( pwd_ptr ) return( pwd_ptr->pw_name );
  else          return( NULL );

#else

  int i;

  for( i=0; i < (int)passwd_count; i++ )
  {
    if( passwd_array[i].uid == (int)uid )
      return( passwd_array[i].name );
  }

  return( NULL );

#endif /* ANDROID / WIN32 */

}




int GetPasswdUid(char *name)
{
/* # ifdef WIN32 */
#if defined(WIN32) || defined(__ANDROID__)

  struct passwd *pwd_ptr;

  pwd_ptr = getpwnam( name );

  if( pwd_ptr ) return( pwd_ptr->pw_uid );
  else          return( -1 );

#else

  int i;

  for( i=0; i < (int)passwd_count; i++ )
  {
    if( !strcmp( name, passwd_array[i].name ) )
      return( (int) passwd_array[i].uid );
  }

  return( -1 );

#endif /* ANDROID / WIN32 */

}





