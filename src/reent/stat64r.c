/* Reentrant versions of stat64 system call.  This implementation just
   calls the stat64 system call.  */

#include <reent.h>
#include <unistd.h>
#include <sys/stat.h>
#include <_syslist.h>

/* Some targets provides their own versions of these functions.  Those
   targets should define REENTRANT_SYSCALLS_PROVIDED in
   TARGET_CFLAGS.  */

#ifdef _REENT_ONLY
#ifndef REENTRANT_SYSCALLS_PROVIDED
#define REENTRANT_SYSCALLS_PROVIDED
#endif
#endif

#ifdef REENTRANT_SYSCALLS_PROVIDED

int _dummy_stat64_syscalls = 1;

#else

/* We use the errno variable used by the system dependent layer.  */
#undef errno
extern int errno;

/*
FUNCTION
	<<_stat64_r>>---Reentrant version of stat64
	
INDEX
	_stat64_r

SYNOPSIS
	#include <reent.h>
	int _stat64_r(struct _reent *<[ptr]>,
		    const char *<[file]>, struct stat64 *<[pstat]>);

DESCRIPTION
	This is a reentrant version of <<stat64>>.  It
	takes a pointer to the global data block, which holds
	<<errno>>.
*/
struct stat64;
extern int	_stat64 (const char *__restrict __path, struct stat64 *__restrict __sbuf );
int
_stat64_r (struct _reent *ptr,
     const char *file,
     struct stat64 *pstat)
{
  int ret;

  errno = 0;
  if ((ret = _stat64 (file, pstat)) == -1 && errno != 0)
    ptr->_errno = errno;
  return ret;
}

#endif /* ! defined (REENTRANT_SYSCALLS_PROVIDED) */
