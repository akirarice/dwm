/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 2;        /* border pixel of windows */
static const unsigned int gappx     = 8;
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const int user_bh            = 25;        /* 0 means that dwm will calculate bar height, >= 1 means dwm will user_bh as bar height */
static const char *fonts[]          = { "Liberation Mono:size=12", "Noto Color Emoji:antialias=true:autohint=true" };
static const char dmenufont[]       = "Liberation Mono:size=14";
static const char col_gray1[]       = "#222222";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#eeeeee";
static const char col_cyan[]        = "#7E0404";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
	[SchemeSel]  = { col_gray4, col_cyan,  "cyan"  },
};

/* tagging */
static const char *tagsalt[] = { "1", "2", "3", "4", "5" };
static const char *tags[] = { "","","","", ""};

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Gimp",     NULL,       NULL,       0,            0,           -1 },
	{ "Steam",    NULL,       NULL,       1 << 4,       0,           -1 },
	{ "discord",  NULL,       NULL,       1 << 2,       0,           -1 },
	{ "PortalWars-Linux-Shipping", NULL, NULL, 1 << 3,  0,		 -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[+]",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
};

/* key definitions */
#define MODKEY Mod1Mask
#define SUPER  Mod4Mask
#define TERMINAL "st"
#define TERMCLASS "St"
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }


/* include XF86 keys */
#include <X11/XF86keysym.h>

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon,"-h", "40", "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", "#2a9d8f", "-sf", col_gray4, NULL };
static const char *pass[] = { "pmenu","-m", dmenumon,"--type", NULL };
static const char *passotp[] = { "pmenu","otp","-m", dmenumon,"--type", NULL };
static const char *passcopy[] = { "pmenu","-m", dmenumon, NULL };
static const char *termcmd[]  = { "st", NULL };
static const char *dvim[] = {"dvim", dmenumon, NULL};
static const char *bksrf[] = {"bookmarksurf.sh", dmenumon, NULL};
static const char *mpdmenu[] = {"mpdmenu", dmenumon, NULL};
static const char *vmlauncher[] = {"vmlauncher",dmenumon, NULL};
static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_p,      spawn,          {.v = dmenucmd } }, 
	{ MODKEY|ShiftMask,             XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY|ShiftMask,		XK_p,	   spawn,	   {.v = dvim } },
	{ SUPER|ShiftMask,		XK_w,	   spawn,          SHCMD("tabbed -cr2 surf -e x searx.bar") },
	{ SUPER|ShiftMask,		XK_o,	   spawn,	   SHCMD(TERMINAL " -e ncmpcpp") },
	{ SUPER,			XK_v,	   spawn,	   SHCMD("sxiv -t $WALLPAPERS") },
	{ MODKEY,			XK_b,	   spawn,	   SHCMD("firefox") },
	{ MODKEY|ShiftMask,		XK_b,	   spawn,	   SHCMD("firefox -private") },
	{ SUPER,			XK_e,	   spawn,	   SHCMD(TERMINAL " -e neomutt") },
	{ SUPER|ShiftMask,		XK_y,	   spawn,	   SHCMD("bookmarker.sh") },
	{ SUPER|ShiftMask,		XK_l,	   spawn,	   SHCMD("slock") },
	{ MODKEY|ShiftMask,		XK_u,	   spawn,	   {.v = passotp } },
	{ MODKEY|SUPER,			XK_u,	   spawn,	   {.v = passcopy } },
	{ SUPER,			XK_w,	   spawn,          {.v = bksrf } },
	{ SUPER,			XK_n,	   spawn,   	   SHCMD(TERMINAL " -e newsboat") }, 
	{ SUPER,			XK_o,      spawn,	   {.v = mpdmenu } },
	{ MODKEY,			XK_u,	   spawn,          {.v = pass } },
	{ MODKEY,			XK_Down,   spawn,	   SHCMD("changevolume -d3") },
	{ MODKEY,			XK_Up,     spawn,  	   SHCMD("changevolume -i3") },
	{ SUPER,			XK_Right,  spawn,	   SHCMD("spt playback -n") },
	{ SUPER,			XK_Left,   spawn,	   SHCMD("spt playback -p") },
	{ SUPER,			XK_Down,   spawn,	   SHCMD("spt playback -t") },
	{ SUPER|ShiftMask,		XK_m,      spawn,	   {.v = vmlauncher } },
	{ SUPER|ShiftMask,		XK_g,	   spawn,	   SHCMD("yt_clipboard") },
	{ SUPER|ShiftMask,		XK_z,	   spawn,	   SHCMD("start_webcam") },
	{ 0, XF86XK_AudioMute,		spawn,		SHCMD("amixer sset Master toggle") },
	{ 0, XF86XK_AudioRaiseVolume,	spawn,		SHCMD("amixer sset Master 3%+") },
	{ 0, XF86XK_AudioLowerVolume,	spawn,		SHCMD("amixer sset Master 3%-") },
	{ 0, XF86XK_AudioPrev,		spawn,		SHCMD("mpc prev") },
	{ 0, XF86XK_AudioNext,		spawn,		SHCMD("mpc next") },
	{ 0, XF86XK_AudioPause,		spawn,		SHCMD("mpc pause") },
	{ 0, XF86XK_AudioPlay,		spawn,		SHCMD("mpc toggle") },
	{ 0, XF86XK_MonBrightnessUp,	spawn,		SHCMD("xbacklight -inc 15") },
	{ 0, XF86XK_MonBrightnessDown,	spawn,		SHCMD("xbacklight -dec 15") },
	{ 0, XF86XK_ScreenSaver,	spawn,		SHCMD("slock") },
	{ MODKEY,                       XK_n,      togglealttag,   {0} },
	{ MODKEY|ShiftMask,		XK_x,	   movecenter,     {0} },
	{ SUPER|ShiftMask,              XK_b,      togglebar,      {0} },
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
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	{ MODKEY,                       XK_minus,  setgaps,        {.i = -1 } },
	{ MODKEY,                       XK_equal,  setgaps,        {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_equal,  setgaps,        {.i = 0  } },
        { MODKEY,                       XK_Right,  viewnext,       {0} },
        { MODKEY,                       XK_Left,   viewprev,       {0} },
        { MODKEY|ShiftMask,             XK_Right,  tagtonext,      {0} },
        { MODKEY|ShiftMask,             XK_Left,   tagtoprev,      {0} },
	{ MODKEY|ShiftMask,             XK_Home,   spawn,   SHCMD("dm-tool switch-to-greeter") },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	{ MODKEY|ShiftMask,             XK_q,      quit,           {0} },
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

