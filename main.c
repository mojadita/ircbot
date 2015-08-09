/* $Id$
 * Author: Luis Colorado <luiscoloradourcola@gmail.com>
 * Date: Thu Jul 30 18:31:15 EEST 2015
 * Copyright: (2015) LUIS COLORADO.  All rights reserved.
 */

#include <errno.h>
#include <getopt.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>

#include "debug.h"
#include "config.h"
#include "input.h"
#include "input_cb.h"

void do_help()
{
	printf(
		"Usage: %s [ options ... ]\n"
		"options:\n"
		" -V shows ircbot version.\n"
		" -L <libdir> allows to change the\n"
		"	directory from where shared modules\n"
		"	are loaded.\n"
		" -d Debug mode.  Show traces of what's\n"
		"	being done.\n"
		" -h <host> set the host to connect to.\n"
		" -p <port> set the port number to\n"
		"	connect to.\n"
		" -? Get help.  Shows this help text\n"
		"", /* to facilitate to add new lines */
	config.cfg_package
		);
	exit(EXIT_SUCCESS);
} /* do_help */

int main(int argc, char **argv)
{
	int opt, res;
	int sfd; /* socket */
	struct sockaddr_in srvr;
	struct hostent *host;
	struct servent *port;
	struct message msg;
	FILE *in;

	while ((opt = getopt(argc, argv, "L:Vdf:h:p:")) != EOF) {
		switch (opt) {
		case '?': config.cfg_flags |= FLAG_HELP; break;
		case 'L': config.cfg_libdir = optarg; break;
		case 'V': config.cfg_flags |= FLAG_SHOWVERSION; break;
		case 'd': config.cfg_flags |= FLAG_DEBUG; break;
		case 'f': config.cfg_script = optarg; break;
		case 'h': config.cfg_host = optarg; break;
		case 'p': config.cfg_port = optarg; break;
		} /* switch */
	} /* while */

	if (config.cfg_flags & FLAG_SHOWVERSION) {
		printf(D("Version: %s\n"),
			config.cfg_version);
		exit(EXIT_SUCCESS);
	} /* if */

	if (config.cfg_flags & FLAG_HELP) {
		do_help();
	} /* if */

	if (config.cfg_flags & FLAG_DEBUG)
		show_config();
	
	TR("%#p", struct hostent *, host = gethostbyname(config.cfg_host));
	host = gethostbyname(config.cfg_host);
	if (!host) {
		ERR(D("gethostbyname: %s: %s (h_errno = %d)\n"),
			config.cfg_host, hstrerror(h_errno), h_errno);
	} /* if */
	srvr.sin_len = sizeof srvr;
	srvr.sin_family = AF_INET;
	srvr.sin_addr = *(struct in_addr *)(host->h_addr_list[0]);
	TR("%#p", struct servent *, port = getservbyname(config.cfg_port, "tcp"));
	srvr.sin_port = port ? port->s_port : htons(atoi(config.cfg_port));
	if (!srvr.sin_port) srvr.sin_port = htons(DEFAULT_PORT);
	TR("%s", char *, inet_ntoa(srvr.sin_addr));
	TR("%hu", short, ntohs(srvr.sin_port));
	TR("%d", int, sfd = socket(AF_INET, SOCK_STREAM, 0));
	TR("%d", int, res = connect(sfd, (struct sockaddr *)&srvr, sizeof srvr));
	if (res < 0) {
		ERR(D("ERROR: connect: %s(%s:%hu): %s (errno = %d)\n"),
			host->h_name,
			inet_ntoa(srvr.sin_addr),
			ntohs(srvr.sin_port),
			strerror(errno),
			errno);
	} /* if */

	in = fdopen(sfd, "r");
	if (!in) {
		ERR(D("ERROR: fdopen: %s (errno = %d)\n"),
			strerror(errno), errno);
	} /* if */

	input(in, input_cb, &msg);

	exit(EXIT_SUCCESS);
} /* main */
