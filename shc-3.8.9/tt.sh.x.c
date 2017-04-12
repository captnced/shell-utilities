#if 0
	shc Version 3.8.9, Generic Script Compiler
	Copyright (c) 1994-2012 Francisco Rosales <frosal@fi.upm.es>

	./shc -r -T -D -f tt.sh 
#endif

static  char data [] = 
#define      inlo_z	3
#define      inlo	((&data[0]))
	"\324\101\041"
#define      date_z	1
#define      date	((&data[3]))
	"\014"
#define      chk1_z	22
#define      chk1	((&data[5]))
	"\025\332\110\375\252\155\203\263\115\243\030\321\205\070\135\001"
	"\206\335\106\036\237\064\200"
#define      xecc_z	15
#define      xecc	((&data[30]))
	"\123\023\123\302\224\230\054\254\134\154\033\351\200\223\043\331"
	"\160\117\015"
#define      lsto_z	1
#define      lsto	((&data[46]))
	"\362"
#define      msg2_z	19
#define      msg2	((&data[48]))
	"\342\334\057\171\041\174\127\305\065\244\153\371\317\031\344\216"
	"\017\022\127\271\051\127\067"
#define      rlax_z	1
#define      rlax	((&data[70]))
	"\166"
#define      shll_z	8
#define      shll	((&data[71]))
	"\316\106\033\351\216\272\230\304"
#define      tst1_z	22
#define      tst1	((&data[84]))
	"\177\072\244\233\272\145\252\110\161\052\132\257\030\000\311\346"
	"\274\100\046\225\147\312\161\005\345\211\024"
#define      msg1_z	42
#define      msg1	((&data[106]))
	"\171\304\137\310\127\063\157\226\122\261\024\204\103\005\274\306"
	"\274\317\334\037\065\203\206\004\314\003\245\236\313\313\235\042"
	"\355\112\130\322\377\041\003\164\014\351\005\327\051\315\240\037"
	"\266\100\243\126"
#define      opts_z	1
#define      opts	((&data[158]))
	"\257"
#define      text_z	34
#define      text	((&data[159]))
	"\367\132\021\007\274\043\302\133\342\146\371\060\311\200\327\150"
	"\245\060\134\026\141\343\234\007\257\157\022\365\264\210\234\031"
	"\013\332\101\013\342\254\175\114\313"
#define      chk2_z	19
#define      chk2	((&data[204]))
	"\176\005\167\300\162\144\111\070\020\151\327\137\364\107\355\137"
	"\261\311\202\067\335\321\367"
#define      tst2_z	19
#define      tst2	((&data[226]))
	"\274\234\366\006\132\010\016\271\264\024\161\010\002\117\215\175"
	"\254\027\230\216\362\211\102"
#define      pswd_z	256
#define      pswd	((&data[268]))
	"\066\020\072\147\242\116\030\233\350\143\162\244\175\233\076\175"
	"\332\360\370\222\215\140\330\271\303\201\045\326\261\351\255\034"
	"\165\347\062\353\160\016\235\245\267\301\170\201\002\222\332\063"
	"\372\147\217\231\163\377\001\103\200\254\130\105\124\131\260\046"
	"\256\256\042\336\031\232\014\157\341\374\032\024\275\153\075\153"
	"\326\000\315\161\137\261\147\263\324\026\031\305\023\104\036\354"
	"\102\211\236\360\004\246\344\324\207\301\144\050\205\320\100\002"
	"\260\251\256\233\340\371\266\252\322\201\351\221\143\150\065\024"
	"\162\134\167\105\161\366\160\042\331\105\173\343\224\237\077\036"
	"\057\107\215\304\351\062\120\307\226\004\131\104\203\257\152\265"
	"\343\341\206\056\072\306\204\227\160\232\060\045\011\344\120\104"
	"\146\236\237\347\256\000\205\340\211\351\047\232\110\314\134\160"
	"\326\032\260\151\332\244\302\313\227\257\075\174\166\340\157\140"
	"\367\366\212\171\072\310\044\174\315\277\204\364\241\157\162\130"
	"\310\260\362\031\225\376\050\214\273\060\260\213\125\071\371\240"
	"\376\353\314\351\043\375\233\020\012\043\372\147\010\061\252\055"
	"\042\271\254\013\024\201\353\156\202\265\167\240\313\337\332\157"
	"\133\324\204\162\234\224\273\205\027\374\270\262\166\343\164\250"
	"\326\050\057\117\352\221\224\042\102\050\074\332"/* End of data[] */;
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
