#if 0
	shc Version 3.8.9, Generic Script Compiler
	Copyright (c) 1994-2012 Francisco Rosales <frosal@fi.upm.es>

	shc -v -f ./test.bash 
#endif

static  char data [] = 
#define      msg1_z	42
#define      msg1	((&data[8]))
	"\264\161\252\335\006\014\165\155\051\365\357\250\163\226\214\237"
	"\362\071\221\327\270\324\353\112\225\160\221\052\172\313\031\241"
	"\216\114\027\047\070\130\122\323\230\235\377\010\066\000\011\115"
	"\316\365\276\231\074\220\006"
#define      tst2_z	19
#define      tst2	((&data[59]))
	"\012\374\246\142\365\022\002\173\003\025\377\325\073\064\040\175"
	"\143\232\007\274\334\243\340"
#define      rlax_z	1
#define      rlax	((&data[78]))
	"\322"
#define      xecc_z	15
#define      xecc	((&data[79]))
	"\044\135\360\153\335\013\332\134\376\037\145\371\274\273\124\177"
	"\321\116"
#define      msg2_z	19
#define      msg2	((&data[98]))
	"\116\051\145\175\121\102\331\212\074\172\213\147\225\346\302\344"
	"\227\343\106\222\223\353"
#define      lsto_z	1
#define      lsto	((&data[119]))
	"\136"
#define      shll_z	10
#define      shll	((&data[122]))
	"\122\371\147\260\274\060\046\154\204\143\234\134\314"
#define      tst1_z	22
#define      tst1	((&data[138]))
	"\232\370\305\357\065\077\147\301\304\372\140\323\032\173\333\167"
	"\336\352\053\254\002\337\271\364\075\170\206"
#define      chk1_z	22
#define      chk1	((&data[163]))
	"\020\254\275\036\161\162\122\246\063\222\057\341\245\047\043\160"
	"\341\367\341\026\346\364\044\133\011\120\054\251"
#define      inlo_z	3
#define      inlo	((&data[188]))
	"\103\033\064"
#define      opts_z	3
#define      opts	((&data[191]))
	"\022\064\267"
#define      text_z	139
#define      text	((&data[198]))
	"\307\006\310\322\360\002\136\275\330\105\013\040\145\203\233\175"
	"\376\236\166\333\053\031\265\130\336\230\247\366\002\356\355\075"
	"\234\134\177\167\066\332\103\300\331\021\227\233\004\044\122\111"
	"\233\125\264\012\054\253\344\142\120\131\300\071\175\374\363\064"
	"\050\067\365\205\177\266\367\317\212\040\041\315\037\340\325\335"
	"\342\122\234\305\377\161\274\265\304\064\355\277\042\212\133\177"
	"\006\012\016\030\002\066\116\215\074\230\020\216\014\102\145\273"
	"\311\330\034\320\304\355\000\174\103\215\062\254\266\226\365\132"
	"\146\030\065\205\307\057\275\107\045\241\321\253\340\010\145\313"
	"\271\331\312\374\130\204\125\113\151\032\373\224"
#define      chk2_z	19
#define      chk2	((&data[350]))
	"\233\015\312\103\047\053\241\040\366\036\012\071\212\062\172\025"
	"\010\326\334"
#define      pswd_z	256
#define      pswd	((&data[383]))
	"\156\300\057\116\126\256\270\014\143\211\150\042\000\366\324\054"
	"\222\011\276\313\313\346\315\166\375\046\226\352\272\306\000\107"
	"\153\126\053\265\151\153\347\163\152\056\071\006\163\247\046\206"
	"\110\205\231\171\070\042\231\373\100\373\264\311\132\272\270\133"
	"\365\156\201\135\245\022\046\262\016\035\035\152\332\346\021\271"
	"\233\373\135\221\252\205\020\361\341\201\154\370\011\122\221\231"
	"\333\231\137\226\004\343\125\153\073\076\015\034\003\145\063\002"
	"\104\140\164\232\034\167\141\017\330\142\264\116\213\137\175\070"
	"\246\217\225\074\005\112\241\012\062\131\350\370\336\125\077\370"
	"\047\202\107\115\155\311\356\073\335\034\252\057\051\020\327\261"
	"\135\020\362\022\324\213\301\214\055\230\264\000\346\021\324\353"
	"\167\071\204\334\376\123\055\164\373\131\265\251\002\155\250\035"
	"\153\344\227\262\317\101\300\275\177\301\112\062\226\345\302\241"
	"\043\033\226\001\271\126\075\275\160\255\320\237\341\056\264\045"
	"\233\220\137\367\110\315\274\141\207\320\107\011\130\334\236\042"
	"\132\304\252\315\273\266\362\130\076\365\171\310\340\077\160\275"
	"\120\242\234\157\216\107\145\063\053\023\350\257\210\315\217\147"
	"\373\117\056\372\347\024\124\074\027\012\021\270\051\224\124\044"
	"\056\340\037\224\216\303\176\246\224\257\342\335\150\046\322\334"
	"\117\250\234"
#define      date_z	1
#define      date	((&data[676]))
	"\213"/* End of data[] */;
#define      hide_z	4096
#define DEBUGEXEC	0	/* Define as 1 to debug execvp calls */
#define TRACEABLE	0	/* Define as 1 to enable ptrace the executable */

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
