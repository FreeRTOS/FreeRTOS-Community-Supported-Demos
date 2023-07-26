/*****************************************************************************/
/* UART_LOWLEV.C - Example user-defined device.                              */
/*****************************************************************************/
#include <file.h>
#include "uart_drv.h"
//#include "uart.h"

extern void UartSetup();
extern void UartPutChar(int charToWrite);

/*****************************************************************************/
/* This is a sample implementation of a user-defined device.  The device     */
/* must define the seven basic functions (open, close, read, write, lseek,   */
/* unlink, rename).  These are expected to behave just like the Unix         */
/* functions of these names.  Some devices might not have a reasonable       */
/* action to take for some functions; a UART or TTY device might not be      */
/* lseek-able, but can still be opened and written to.  A device is added    */
/* using the add_device() RTS function call (q.v.).                          */
/*****************************************************************************/
/* The low-level interface is based on file names and file descriptors.      */
/* The file names don't need to be valid Unix file names, but must mean      */
/* something to the device.  The device must keep track of its own file      */
/* descriptors, which will be used by the calling functions to read and      */
/* write to the device.  If there can only be one instance of a "file" on a  */
/* device, the file descriptor doesn't matter much, so just pass a       */
/* non-negative integer such as zero.                        */
/*****************************************************************************/

/*****************************************************************************/
/*                                                                           */
/* UART_open()                                                   */
/*                                                                           */
/*****************************************************************************/
int UART_open(const char *path, unsigned flags, int llv_fd)
{
    /*-----------------------------------------------------------------------*/
    /* Only one UART device exists (_SSA).  For an _SSA device, file names   */
    /* are not meaningful, so ignore the file name.                          */
    /*-----------------------------------------------------------------------*/

    /*-----------------------------------------------------------------------*/
    /* Don't allow attempts to open the UART device that aren't O_WRONLY.    */
    /*-----------------------------------------------------------------------*/
    if (!(flags & O_WRONLY)) return -1;

    /*-----------------------------------------------------------------------*/
    /* Set up the UART                                                       */
    /*-----------------------------------------------------------------------*/
    UartSetup();

    /*-----------------------------------------------------------------------*/
    /* Arbitrarily give it file descriptor 1.  File descriptors are          */
    /* device-specific; this file descriptor 1 is not the same as HOST file  */
    /* descriptor 1 (stdout).                                                */
    /*-----------------------------------------------------------------------*/
    return 1;
}

/*****************************************************************************/
/*                                                                           */
/* UART_close()                                                  */
/*                                                                           */
/*****************************************************************************/
int UART_close(int dev_fd)
{
    /*-----------------------------------------------------------------------*/
    /* Only one UART device exists, so we don't do anything upon close.      */
    /*-----------------------------------------------------------------------*/
    return 0;
}

/*****************************************************************************/
/*                                                                           */
/* UART_read() reads *at most* count bytes.                                  */
/*                                                                           */
/*****************************************************************************/
int UART_read(int dev_fd, char *buf, unsigned count)
{
    /*-----------------------------------------------------------------------*/
    /* Only one UART device exists, and it is write-only, so return error    */
    /*-----------------------------------------------------------------------*/
    return -1;
}

/*****************************************************************************/
/*                                                                           */
/* UART_write()                                                              */
/*                                                                           */
/*****************************************************************************/
int UART_write(int dev_fd, const char *buf, unsigned count)
{
    unsigned i;

    /*-----------------------------------------------------------------------*/
    /* Output character-by-character                                         */
    /*-----------------------------------------------------------------------*/
    for (i=0; i < count; i++)
        UartPutChar(buf[i]);

    return count;
}

/*****************************************************************************/
/*                                                                           */
/* UART_lseek()                                                              */
/*                                                                           */
/*****************************************************************************/
off_t UART_lseek(int dev_fd, off_t offset, int origin)
{
    /*-----------------------------------------------------------------------*/
    /* lseek is not possible on UART.                                        */
    /*-----------------------------------------------------------------------*/
    return -1;
}

/*****************************************************************************/
/*                                                                           */
/* UART_unlink()                                                             */
/*                                                                           */
/*****************************************************************************/
int UART_unlink(const char *path)
{
    /*-----------------------------------------------------------------------*/
    /* unlink is not possible on UART                                        */
    /*-----------------------------------------------------------------------*/
    return -1;
}

/*****************************************************************************/
/*                                                                           */
/* UART_rename()                                                             */
/*                                                                           */
/*****************************************************************************/
/* rename is unusual among the low-level functions in that it is also        */
/* specified in the ISO C standard.  It has the same prototype and       */
/* semantics, so it's not really an issue.                   */
/*****************************************************************************/
int UART_rename(const char *old_name, const char *new_name)
{
    /*-----------------------------------------------------------------------*/
    /* rename is not possible on UART                                        */
    /*-----------------------------------------------------------------------*/
    return -1;
}
