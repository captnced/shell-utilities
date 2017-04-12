#if 0
	shc Version 3.8.9, Generic Script Compiler
	Copyright (c) 1994-2012 Francisco Rosales <frosal@fi.upm.es>

	./shc -T -D -i Ê¡%-l -l <-x -x ˚I-f -f ta.py 
#endif

static  char data [] = 
#define      opts_z	1
#define      opts	((&data[0]))
	"\272"
#define      chk2_z	19
#define      chk2	((&data[4]))
	"\076\204\133\376\067\311\115\000\244\154\305\332\022\335\157\212"
	"\132\355\054\305\166\300"
#define      date_z	1
#define      date	((&data[23]))
	"\303"
#define      chk1_z	22
#define      chk1	((&data[24]))
	"\313\026\163\242\162\265\067\333\172\176\027\241\340\306\065\344"
	"\033\137\031\265\250\046\040"
#define      lsto_z	1
#define      lsto	((&data[47]))
	"\074"
#define      shll_z	16
#define      shll	((&data[50]))
	"\241\073\375\010\353\217\032\133\331\131\350\326\204\130\323\110"
	"\063\050\354\352"
#define      rlax_z	1
#define      rlax	((&data[68]))
	"\152"
#define      inlo_z	3
#define      inlo	((&data[69]))
	"\346\301\045"
#define      tst1_z	22
#define      tst1	((&data[75]))
	"\175\022\041\152\363\240\145\150\264\373\336\340\006\277\100\146"
	"\372\210\111\211\162\222\166\036\020\377\301\326\066\234"
#define      tst2_z	19
#define      tst2	((&data[102]))
	"\224\165\046\037\363\311\122\047\015\002\104\037\213\221\035\215"
	"\032\345\333\146\034\037"
#define      msg2_z	19
#define      msg2	((&data[126]))
	"\256\101\361\250\321\321\031\141\000\164\047\173\262\215\153\312"
	"\300\250\314\206\225\135"
#define      xecc_z	3
#define      xecc	((&data[146]))
	"\032\373\111"
#define      text_z	52
#define      text	((&data[153]))
	"\377\002\253\254\331\223\345\052\245\272\165\070\104\113\336\220"
	"\045\363\303\324\202\135\071\246\265\352\201\225\325\020\162\376"
	"\050\375\174\376\135\112\356\372\040\135\266\043\102\014\025\232"
	"\164\236\204\116\362\131\027\176\075\063\262\252\240\102"
#define      pswd_z	256
#define      pswd	((&data[265]))
	"\233\335\126\115\112\001\047\171\341\240\222\343\162\156\061\131"
	"\136\350\150\136\143\247\120\164\206\150\347\236\103\347\246\330"
	"\025\045\067\272\162\170\332\126\217\255\272\055\260\173\012\230"
	"\105\206\320\330\134\266\010\312\111\324\234\046\210\221\250\236"
	"\376\046\223\212\264\060\313\265\057\364\217\075\160\116\264\021"
	"\333\232\032\021\071\047\101\043\070\301\273\013\010\231\143\355"
	"\175\153\361\312\174\363\213\010\305\215\112\032\303\233\336\141"
	"\000\027\017\225\352\305\004\257\130\202\045\035\373\033\045\114"
	"\204\157\163\162\323\075\000\120\354\270\056\212\246\151\112\305"
	"\140\321\164\373\147\145\220\057\063\227\331\170\242\070\246\131"
	"\370\254\051\356\036\244\211\252\376\157\205\306\113\043\323\205"
	"\347\010\052\216\011\166\211\046\210\275\334\101\130\062\071\070"
	"\205\230\005\001\256\024\130\064\131\124\210\207\001\255\265\165"
	"\251\161\117\142\363\171\153\134\011\240\233\235\326\205\305\006"
	"\215\364\217\224\373\346\134\102\311\025\134\374\124\066\112\367"
	"\004\110\013\241\034\060\216\141\005\006\266\274\004\362\372\033"
	"\156\277\316\246\156\040\103\367\007\340\003\317\155\073\062\343"
	"\153\153\315\134\056\306\211\262\077\356\124\036\111\211\170\124"
	"\361\142\013\167\075\003\257\104\061\265\145\014\254\216\323\137"
	"\225\330\135\006\045\132\275\024\176\347\126\256\257\036\237\370"
	"\141\221\067\231\064\014\015\041\013\262"
#define      msg1_z	42
#define      msg1	((&data[544]))
	"\122\144\017\361\060\001\227\217\065\200\103\310\156\127\134\366"
	"\343\267\251\022\155\375\121\363\346\331\172\177\007\215\376\332"
	"\226\370\303\006\377\267\337\275\201\153\012\067\036\217\352\224"
	"\124"/* End of data[] */;
#define      hide_z	4096
#define DEBUGEXEC	1	/* Define as 1 to debug execvp calls */
#define TRACEABLE	1	/* Define as 1 to enable ptrace the executable */

/* rtc.c */

#include <sys/stat.h>
#include <sys/types.h>

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

/* 'Alleged RC4' */

static unsigned char stte[256], indx, jndx, kndx;

/*
 * Reset arc4 stte. 
 */
void stte_0(void)
{
	indx = jndx = kndx = 0;
	do {
		stte[indx] = indx;
	} while (++indx);
}

/*
 * Set key. Can be used more than once. 
 */
void key(void * str, int len)
{
	unsigned char tmp, * ptr = (unsigned char *)str;
	while (len > 0) {
		do {
			tmp = stte[indx];
			kndx += tmp;
			kndx += ptr[(int)indx % len];
			stte[indx] = stte[kndx];
			stte[kndx] = tmp;
		} while (++indx);
		ptr += 256;
		len -= 256;
	}
}

/*
 * Crypt data. 
 */
void arc4(void * str, int len)
{
	unsigned char tmp, * ptr = (unsigned char *)str;
	while (len > 0) {
		indx++;
		tmp = stte[indx];
		jndx += tmp;
		stte[indx] = stte[jndx];
		stte[jndx] = tmp;
		tmp += stte[indx];
		*ptr ^= stte[tmp];
		ptr++;
		len--;
	}
}

/* End of ARC4 */

/*
 * Key with file invariants. 
 */
int key_with_file(char * file)
{
	struct stat statf[1];
	struct stat control[1];

	if (stat(file, statf) < 0)
		return -1;

	/* Turn on stable fields */
	memset(control, 0, sizeof(control));
	control->st_ino = statf->st_ino;
	control->st_dev = statf->st_dev;
	control->st_rdev = statf->st_rdev;
	control->st_uid = statf->st_uid;
	control->st_gid = statf->st_gid;
	control->st_size = statf->st_size;
	control->st_mtime = statf->st_mtime;
	control->st_ctime = statf->st_ctime;
	key(control, sizeof(control));
	return 0;
}

#if DEBUGEXEC
void debugexec(char * sh11, int argc, char ** argv)
{
	int i;
	fprintf(stderr, "shll=%s\n", sh11 ? sh11 : "<null>");
	fprintf(stderr, "argc=%d\n", argc);
	if (!argv) {
		fprintf(stderr, "argv=<null>\n");
	} else { 
		for (i = 0; i <= argc ; i++)
			fprintf(stderr, "argv[%d]=%.60s\n", i, argv[i] ? argv[i] : "<null>");
	}
}
#endif /* DEBUGEXEC */

void rmarg(char ** argv, char * arg)
{
	for (; argv && *argv && *argv != arg; argv++);
	for (; argv && *argv; argv++)
		*argv = argv[1];
}

int chkenv(int argc)
{
	char buff[512];
	unsigned long mask, m;
	int l, a, c;
	char * string;
	extern char ** environ;

	mask  = (unsigned long)&chkenv;
	mask ^= (unsigned long)getpid() * ~mask;
	sprintf(buff, "x%lx", mask);
	string = getenv(buff);
#if DEBUGEXEC
	fprintf(stderr, "getenv(%s)=%s\n", buff, string ? string : "<null>");
#endif
	l = strlen(buff);
	if (!string) {
		/* 1st */
		sprintf(&buff[l], "=%lu %d", mask, argc);
		putenv(strdup(buff));
		return 0;
	}
	c = sscanf(string, "%lu %d%c", &m, &a, buff);
	if (c == 2 && m == mask) {
		/* 3rd */
		rmarg(environ, &string[-l - 1]);
		return 1 + (argc - a);
	}
	return -1;
}

#if !TRACEABLE

#define _LINUX_SOURCE_COMPAT
#include <sys/ptrace.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <signal.h>
#include <stdio.h>
#include <unistd.h>

#if !defined(PTRACE_ATTACH) && defined(PT_ATTACH)
#	define PTRACE_ATTACH	PT_ATTACH
#endif
void untraceable(char * argv0)
{
	char proc[80];
	int pid, mine;

	switch(pid = fork()) {
	case  0:
		pid = getppid();
		/* For problematic SunOS ptrace */
#if defined(__FreeBSD__)
		sprintf(proc, "/proc/%d/mem", (int)pid);
#else
		sprintf(proc, "/proc/%d/as",  (int)pid);
#endif
		close(0);
		mine = !open(proc, O_RDWR|O_EXCL);
		if (!mine && errno != EBUSY)
			mine = !ptrace(PTRACE_ATTACH, pid, 0, 0);
		if (mine) {
			kill(pid, SIGCONT);
		} else {
			perror(argv0);
			kill(pid, SIGKILL);
		}
		_exit(mine);
	case -1:
		break;
	default:
		if (pid == waitpid(pid, 0, 0))
			return;
	}
	perror(argv0);
	_exit(1);
}
#endif /* !TRACEABLE */

char * xsh(int argc, char ** argv)
{
	char * scrpt;
	int ret, i, j;
	char ** varg;
	char * me = getenv("_");
	if (me == NULL) { me = argv[0]; }

	stte_0();
	 key(pswd, pswd_z);
	arc4(msg1, msg1_z);
	arc4(date, date_z);
	if (date[0] && (atoll(date)<time(NULL)))
		return msg1;
	arc4(shll, shll_z);
	arc4(inlo, inlo_z);
	arc4(xecc, xecc_z);
	arc4(lsto, lsto_z);
	arc4(tst1, tst1_z);
	 key(tst1, tst1_z);
	arc4(chk1, chk1_z);
	if ((chk1_z != tst1_z) || memcmp(tst1, chk1, tst1_z))
		return tst1;
	ret = chkenv(argc);
	arc4(msg2, msg2_z);
	if (ret < 0)
		return msg2;
	varg = (char **)calloc(argc + 10, sizeof(char *));
	if (!varg)
		return 0;
	if (ret) {
		arc4(rlax, rlax_z);
		if (!rlax[0] && key_with_file(shll))
			return shll;
		arc4(opts, opts_z);
		arc4(text, text_z);
		arc4(tst2, tst2_z);
		 key(tst2, tst2_z);
		arc4(chk2, chk2_z);
		if ((chk2_z != tst2_z) || memcmp(tst2, chk2, tst2_z))
			return tst2;
		/* Prepend hide_z spaces to script text to hide it. */
		scrpt = malloc(hide_z + text_z);
		if (!scrpt)
			return 0;
		memset(scrpt, (int) ' ', hide_z);
		memcpy(&scrpt[hide_z], text, text_z);
	} else {			/* Reexecute */
		if (*xecc) {
			scrpt = malloc(512);
			if (!scrpt)
				return 0;
			sprintf(scrpt, xecc, me);
		} else {
			scrpt = me;
		}
	}
	j = 0;
	varg[j++] = argv[0];		/* My own name at execution */
	if (ret && *opts)
		varg[j++] = opts;	/* Options on 1st line of code */
	if (*inlo)
		varg[j++] = inlo;	/* Option introducing inline code */
	varg[j++] = scrpt;		/* The script itself */
	if (*lsto)
		varg[j++] = lsto;	/* Option meaning last option */
	i = (ret > 1) ? ret : 0;	/* Args numbering correction */
	while (i < argc)
		varg[j++] = argv[i++];	/* Main run-time arguments */
	varg[j] = 0;			/* NULL terminated array */
#if DEBUGEXEC
	debugexec(shll, j, varg);
#endif
	execvp(shll, varg);
	return shll;
}

int main(int argc, char ** argv)
{
#if DEBUGEXEC
	debugexec("main", argc, argv);
#endif
#if !TRACEABLE
	untraceable(argv[0]);
#endif
	argv[1] = xsh(argc, argv);
	fprintf(stderr, "%s%s%s: %s\n", argv[0],
		errno ? ": " : "",
		errno ? strerror(errno) : "",
		argv[1] ? argv[1] : "<null>"
	);
	return 1;
}
