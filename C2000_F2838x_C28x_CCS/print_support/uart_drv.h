/*****************************************************************************/
/* Must include stdio.h before this file for the definition of fpos_t        */
/*****************************************************************************/
#include <stdio.h>

int    UART_open(const char *path, unsigned flags, int llv_fd);
int    UART_close(int dev_fd);
int    UART_read(int dev_fd, char *buf, unsigned count);
int    UART_write(int dev_fd, const char *buf, unsigned count);
fpos_t UART_lseek(int dev_fd, fpos_t offset, int origin);
int    UART_unlink(const char *path);
int    UART_rename(const char *old_name, const char *new_name);
