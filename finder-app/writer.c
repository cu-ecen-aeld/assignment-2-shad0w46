#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <syslog.h>
#include <string.h>
#include <errno.h>

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        fprintf(stderr, "Usage: %s <writefile> <writestr>\n", argv[0]);
        return 1;
    }

    const char *writefile = argv[1];
    const char *writestr = argv[2];

    /* Setup syslog */
    openlog("writer", LOG_PID, LOG_USER);

    /* Log debug message */
    syslog(LOG_DEBUG, "Writing %s to %s", writestr, writefile);

    /* Open (create if needed, truncate if exists) */
    int fd = open(writefile, O_WRONLY | O_CREAT | O_TRUNC, 0644);

    if (fd == -1)
    {
        syslog(LOG_ERR, "Error opening file %s: %s",
               writefile, strerror(errno));
        closelog();
        return 1;
    }

    /* Write string */
    ssize_t written = write(fd, writestr, strlen(writestr));

    if (written == -1)
    {
        syslog(LOG_ERR, "Error writing to file %s: %s",
               writefile, strerror(errno));
        close(fd);
        closelog();
        return 1;
    }

    close(fd);
    closelog();

    return 0;
}
