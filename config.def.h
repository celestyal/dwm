/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 2;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int swallowfloating    = 0;        /* 1 means swallow floating windows by default */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 0;        /* 0 means bottom bar */
static const char *fonts[]          = { "Libertinus Sans: size 12", "Noto Color Emoji:size=12" };
static const char dmenufont[]       = "Libertinus Sans: size 12";
static const char col_normfg[]       = "#c2c1c0";
static const char col_normbg[]       = "#121212";
static const char col_selfg[]       = "#9a9a9a";
static const char col_selbg[]       = "#680822";
static const char col_normborder[] = "#c2c1c0";
static const char col_selborder[] = "#680822";
static const unsigned int baralpha  = 0xff;
static const unsigned int borderalpha = OPAQUE;
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_normfg, col_normbg, col_normborder },
	[SchemeSel]  = { col_selfg, col_selbg, col_selborder  },
};
static const XPoint stickyicon[]    = { {0,0}, {4,0}, {4,8}, {2,6}, {0,8}, {0,0} }; /* represents the icon as an array of vertices */
static const XPoint stickyiconbb    = {4,8};	/* defines the bottom right corner of the polygon's bounding box (speeds up scaling) */

static const unsigned int alphas[][3]      = {
        /*               fg      bg        border     */
        [SchemeNorm] = { OPAQUE, baralpha, borderalpha },
        [SchemeSel]  = { OPAQUE, baralpha, borderalpha },
};

/* tagging */
static const char *tagsalt[] = { "", "", "", "", "", "", "", "", "" };
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };
static const int momentaryalttags = 0; /* 1 means alttags will show only when key is held down*/


static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
       /* class      instance    title            tags mask  isfloating  isterminal  noswallow  monitor */
       { "firefox",  	NULL,   NULL,            1 << 8,    0,          0,          -1,        -1 },
       { "St",		NULL,   NULL,                 0,    0,          1,           0,        -1 },
       { "Thunderbird", NULL,   NULL,            1 << 5,    0,          0,          -1,        -1 },
       { "Ymuse", 	NULL,	NULL,		 1 << 3,    0,		0,	    -1,	       -1 },
       { "KeePassXC", 	NULL,	NULL,		 1 << 6,    0,		0,	    -1,	       -1 },
       { "Tor Browser",	NULL,   NULL,            1 << 7,    1,          0,           0,        -1 },
       { NULL,       	NULL,   "Event Tester",  0,         0,          0,           1,        -1 }, /* xev */

};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "Tiling",      tile },    /* first entry is default */
	{ "Floating",      NULL },    /* no layout function means floating behavior */
	{ "Monocle",      monocle },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_normbg, "-nf", col_normfg, "-sb", col_selbg, "-sf", col_selfg, NULL };
static const char *termcmd[]  = { "st", NULL };
/* Networking */
static const char *wifion[]   = { "connmanctl", "enable", "wifi",  NULL };
static const char *wifioff[]  = { "connmanctl", "disable", "wifi", NULL };
/* MPC controls */
static const char *musictoggle[] = { "mpc", "toggle", NULL };
static const char *nextsong[] = { "mpc", "next", NULL };
static const char *prevsong[] = { "mpc", "prev", NULL };
static const char *musicvolup[] = { "mpc", "vol", "+5", NULL };
static const char *musicvoldown[] = { "mpc", "vol", "-5", NULL };
/* Other */
static const char *brightness_up[] = { "xbacklight", "-inc", "5", NULL };
static const char *brightness_down[] = { "xbacklight", "-dec", "5", NULL };

static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_p,      spawn,          {.v = dmenucmd } },
	{ MODKEY|ShiftMask,             XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY|ShiftMask,             XK_c,      killclient,     {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_s,      togglesticky,   {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	/*{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },*/
        { MODKEY,                       XK_n,      togglealttag,   {0} },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	{ MODKEY|ShiftMask,             XK_q,      quit,           {0} },
	/* My key definitions */
	{ MODKEY,			XK_F5,	   spawn,	   {.v = wifion } },
	{ MODKEY|ShiftMask,		XK_F5,	   spawn,	   {.v = wifioff } },
	{ MODKEY,			XK_F11,	   spawn,	   {.v = musictoggle } },
	{ MODKEY,			XK_F10,	   spawn,	   {.v = prevsong } },
	{ MODKEY,			XK_F12,	   spawn,	   {.v = nextsong } },
	{ MODKEY,			XK_comma,  spawn,	   {.v = musicvoldown } },
	{ MODKEY,			XK_F9,	   spawn,	   {.v = brightness_up } },
	{ MODKEY,			XK_F8, 	   spawn,	   {.v = brightness_down } },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

