%{
/* $Id$
 * Author: Luis Colorado <luiscoloradourcola@gmail.com>
 * Date: Sun Aug  9 13:09:17 EEST 2015
 * Copyright: (C) 2015 LUIS COLORADO.  All rights reserved.
 */

#include <stdio.h>
#include "debug.h"

#define PARSEINT(b)
#define PARSECHR()
#define PARSESTR()
#define PARSEFLT(b)
#define PARSERGX()
#define PARSEIP4()
#define PARSEIP6()
#define PARSEMSK4()
#define PARSEMSK6()
#define RETURN(X) printf(D(#X ": [%s]\n"), yytext)

%}


dec			([1-9](_?[0-9])*)
dec_		([0-9](_?[0-9])*)
oct			(0(_?[0-7])*)
oct_		([0-7](_?[0-7])*)
bin			(0[bB](_?[01])*)
bin_        ([01](_?[01])*)
hex			(0[xX](_?[0-9a-fA-F])*)
hex_		([0-9a-fA-F](_?[0-9a-fA-F])*)
ident		([a-zA-Z](_?[a-zA-Z0-9])*)
comm		("#".*)
chre		(\'([^\\\n]|\\[^\n]))
chr			({chre}\')
stre		\"([^"\\\n]|\\[^\n])*
str			({stre}\")

flt2		({bin}"."{bin_}?([eE][+-]?{dec_})?)
flt8		({oct}"."{oct_}?([eE][+-]?{oct_})?)
flt10		({dec}"."{dec_}?([eE][+-]?{dec_})?)
flt16		({hex}"."{hex_}?([Gg][+-]?{hex_})?)
rgxe		(@([^@\n]|\\.)*)
rgx			({rgxe}@)
ipv4_comp	(0|[1-9][0-9]?|1[0-9][0-9]|2[0-4][0-9]|25[0-5])
ipv4		({ipv4_comp}("."{ipv4_comp}){3})
ip6c		([0-9a-fA-F]{1,4})
ip61		{ip6c}
ip62		{ip6c}(":"{ip6c}){1}
ip63		{ip6c}(":"{ip6c}){2}
ip64		{ip6c}(":"{ip6c}){3}
ip65		{ip6c}(":"{ip6c}){4}
ip66		{ip6c}(":"{ip6c}){5}
ip67		{ip6c}(":"{ip6c}){6}
ip68		{ip6c}(":"{ip6c}){7}
ip6_1		({ip6c})?
ip6_2		({ip6c}(":"{ip6c}){0,1})?
ip6_3		({ip6c}(":"{ip6c}){0,2})?
ip6_4		({ip6c}(":"{ip6c}){0,3})?
ip6_5		({ip6c}(":"{ip6c}){0,4})?
ip6_6		({ip6c}(":"{ip6c}){0,5})?
ip6_7		({ip6c}(":"{ip6c}){0,6})?
ip6_8		({ip6c}(":"{ip6c}){0,7})?
ip680		{ip68}"::"
ip671		{ip67}"::"{ip6_1}
ip662		{ip66}"::"{ip6_2}
ip653		{ip65}"::"{ip6_3}
ip644		{ip64}"::"{ip6_4}
ip635		{ip63}"::"{ip6_5}
ip626		{ip62}"::"{ip6_6}
ip617		{ip61}"::"{ip6_7}
ip608		"::"{ip6_8}
ip660		{ip66}":"{ipv4}
ip651		{ip65}"::"{ip6_1}":"{ipv4}
ip642		{ip64}"::"{ip6_2}":"{ipv4}
ip633		{ip63}"::"{ip6_3}":"{ipv4}
ip624		{ip62}"::"{ip6_4}":"{ipv4}
ip615		{ip61}"::"{ip6_5}":"{ipv4}
ip606		"::"{ip6_6}":"{ipv4}
ipv61		({ip68}|{ip680}|{ip671}|{ip662}|{ip653}|{ip644}|{ip635}|{ip626}|{ip617})
ipv62		({ip608}|{ip660}|{ip651}|{ip642}|{ip633}|{ip624}|{ip615}|{ip606})
ipv6		({ipv61}|{ipv62})
mask6		{ipv6}"/"(0|[1-9][0-9]?|1[01][0-9]|12[0-6])
mask4		{ipv4}"/"(0|[12][0-9]?|30?|[4-9])

%%

{comm}		;
{dec}/".."	PARSEINT(10); RETURN(NUMBER10);
{dec}		PARSEINT(10); RETURN(NUMBER10);
{oct}/".."	PARSEINT( 8); RETURN(NUMBER8);
{oct}		PARSEINT( 8); RETURN(NUMBER8);
{bin}/".."	PARSEINT( 2); RETURN(NUMBER2);
{bin}		PARSEINT( 2); RETURN(NUMBER2);
{hex}/".."	PARSEINT(16); RETURN(NUMBER16);
{hex}		PARSEINT(16); RETURN(NUMBER16);
{ident}		RETURN(IDENT);
{chre}		WARN(D("WARNING: Unterminated char %s\n"), yytext); PARSECHR(); RETURN(CHAR);
{chr}		PARSECHR();	  RETURN(CHAR);
{stre}		WARN(D("WARNING: Unterminated string %s\n"), yytext); PARSESTR(); RETURN(STRING);
{str}		PARSESTR();   RETURN(STRING);
{flt2}		PARSEFLT( 2); RETURN(FLOAT2);
{flt8}		PARSEFLT( 8); RETURN(FLOAT8);
{flt10}		PARSEFLT(10); RETURN(FLOAT10);
{flt16}		PARSEFLT(16); RETURN(FLOAT16);
{rgxe}		WARN(D("WARNING: Unterminated regex %s\n"), yytext); PARSERGX(); RETURN(REGEX);
{rgx}		PARSERGX(  ); RETURN(REGEX);
{ipv4}		PARSEIP4();	  RETURN(IPV4);
{mask4}		PARSEMSK4();  RETURN(IPV4_NET);
{ipv6}		PARSEIP6();   RETURN(IPV6);
{mask6}		PARSEMSK6();  RETURN(IPV6_NET);
[ \t]		;
\\\n		;

\n			|
.			RETURN(SYMBOL);

%%
