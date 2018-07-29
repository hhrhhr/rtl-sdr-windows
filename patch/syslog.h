#ifndef SYSLOG_FAKE_H
#define SYSLOG_FAKE_H

#define	LOG_EMERG	0
#define	LOG_ALERT	1
#define	LOG_CRIT	2
#define	LOG_ERR		3
#define	LOG_WARNING	4
#define	LOG_NOTICE	5
#define	LOG_INFO	6
#define	LOG_DEBUG	7
#define	LOG_PID		0x01
#define	LOG_DAEMON	(3<<3)
static void closelog (void) {};
static void openlog (const char *__ident, int __option, int __facility) {};
static void vsyslog (int __pri, const char *__fmt, va_list __ap) {};

#endif /* SYSLOG_FAKE_H */
