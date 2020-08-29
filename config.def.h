/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 2;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int swallowfloating    = 0;        /* 1 means swallow floating windows by default */
static const unsigned int gappih    = 20;       /* horiz inner gap between windows */
static const unsigned int gappiv    = 10;       /* vert inner gap between windows */
static const unsigned int gappoh    = 10;       /* horiz outer gap between windows and screen edge */
static const unsigned int gappov    = 30;       /* vert outer gap between windows and screen edge */
static       int smartgaps          = 0;        /* 1 means no outer gap when there is only one window */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const unsigned int systrayspacing = 2;   /* systray spacing */
static const int showsystray             = 1;   /* 0 means no systray */
static const char *fonts[]          = { "JetBrains Mono:pixelsize=14", "JoyPixels:size=12", "Symbols Nerd Font:size=12" };
static const char dmenufont[]       = "JetBrains Mono:size=11";
static char normbgcolor[]           = "#1D1F21";
static char normbordercolor[]       = "#000000";
static char normfgcolor[]           = "#808080";
static char selfgcolor[]            = "#ffffff";
static char selbordercolor[]        = "#005577";
static char selbgcolor[]            = "#1D1F21";
static char statusfgcolor[]         = "#dedede";
static const unsigned int baralpha = 200;
static const unsigned int borderalpha = OPAQUE;
static const char *colors[][3]      = {
	/*               fg            bg           border   */
	[SchemeNorm] 	= { normfgcolor, normbgcolor, normbordercolor },
	[SchemeSel]  	= { selfgcolor,  selbgcolor,  selbordercolor  },
};
static const unsigned int alphas[][3]      = {
	/*               fg      bg        border     */
	[SchemeNorm] = { OPAQUE, baralpha, borderalpha },
	[SchemeSel]  = { OPAQUE, baralpha, borderalpha },
};

/* tagging */
static const char *tags[] = { " term", " web", " dev", " work", "", "", " img", " rss", " music"};

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     iscentered   isfloating   isterminal  noswallow  monitor */
	{ "Gimp",     NULL,       NULL,       0,            0,           1,           0,           0,        -1 },
	{ "Firefox",  NULL,       NULL,       1 << 8,       0,           0,           0,          -1,        -1 },
	{ "st",       NULL,       NULL,       0,            0,           0,           1,           0,        -1 },
	{ NULL,       NULL,       "Event Tester",0,         0,           0,           0,           1,        -1 }, /* xev */

	/* class     instance  title           tags mask  iscentered   isfloating  isterminal  noswallow  monitor  key */
	{ "st",      NULL,     NULL,           0,         0,           0,          1,           0,        -1,      0},
	{ "Brave-browser",NULL,NULL,           1 << 1,    0,           0,          0,          -1,        -1,      0},
	{ "ncmpcppterm",NULL,  NULL,           1 << 8,    0,           0,          0,          -1,        -1,      0},
	{ "newsboatterm",NULL, NULL,           1 << 7,    0,           0,          0,          -1,        -1,      0},
	{ NULL,      NULL,     "Event Tester", 0,         0,           0,          0,          1,          -1,     0}, /* xev */
	{ "scratchpad",NULL,   NULL,           0,         1,           1,          1,          0,          -1,     's' },
	{ "pulsemixercmd",NULL,NULL,           0,         1,           1,          1,          0,          -1,     'p' },
	{ "gotopcmd", NULL,    NULL,           0,         1,           1,          1,          0,          -1,     'g' },
	{ "bccmd",    NULL,    NULL,           0,         1,           1,          1,          0,          -1,     'c' },
};

/* Bar rules allow you to configure what is shown where on the bar, as well as
 * introducing your own bar modules.
 *
 *    monitor:
 *      -1  show on all monitors
 *       0  show on monitor 0
 *      'A' show on active monitor (i.e. focused / selected) (or just -1 for active?)
 *    bar - bar index, 0 is default, 1 is extrabar
 *    alignment - how the module is aligned compared to other modules
 *    widthfunc, drawfunc, clickfunc - providing bar module width, draw and click functions
 *    name - does nothing, intended for visual clue and for logging / debugging
 */
static const BarRule barrules[] = {
	/* monitor  bar    alignment         widthfunc              drawfunc              clickfunc           name */
	{ -1,       0,     BAR_ALIGN_LEFT,   width_tags,            draw_tags,            click_tags,         "tags" },
	{ -1,       1,     BAR_ALIGN_LEFT,   width_ltsymbol,        draw_ltsymbol,        click_ltsymbol,     "layout" },
	{ 'A',      1,     BAR_ALIGN_RIGHT,  width_systray,         draw_systray,         click_systray,      "systray" },
	{ -1,       0,     BAR_ALIGN_RIGHT,  width_status,          draw_status,          click_status,       "status" },
	{ -1,       1,     BAR_ALIGN_NONE,   width_wintitle,        draw_wintitle,        click_wintitle,     "wintitle" },
};

/* layout(s) */
static const float mfact     = 0.5; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */

#define FORCE_VSPLIT 1  /* nrowgrid layout: force two clients to always split vertically */
#include "vanitygaps.c"

static const Layout layouts[] = {
		/* symbol     arrange function */
	{ " ",      tile },    /* first entry is default */
	{ " ",      bstack },
	{ " ",      dwindle },
	{ "ﱖ ",      gaplessgrid },
	{ "ﰀ ",      horizgrid },
	{ " ",      centeredmaster },
	{ " ",      centeredfloatingmaster },
	{ " ",      monocle },
	{ " ",      deck },
	{ "缾",      NULL },    /* no layout function means floating behavior */
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
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", normbgcolor, "-nf", normfgcolor, "-sb", selbordercolor, "-sf", selfgcolor, NULL };
static const char *termcmd[]  = { "st", NULL };

/*First arg only serves to match against key in rules*/
static const char *scratchpadcmd[] = {"s", "st", "-c", "scratchpad", NULL}; 
static const char *pulsemixercmd[] = {"p", "st", "-c", "pulsemixercmd", "-e", "pulsemixer", NULL}; 
static const char *gotopcmd[] = {"g", "st", "-c", "gotopcmd", "-e", "gotop", NULL}; 
static const char *bccmd[] = {"c", "st", "-c", "bccmd", "-e", "bc", "-lq", NULL};

#include "movestack.c"
#include <X11/XF86keysym.h>
static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_p,      spawn,          {.v = dmenucmd } },
	{ MODKEY|ShiftMask,             XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_grave,  togglescratch,  {.v = scratchpadcmd } },
  { MODKEY,                       XK_w,      spawn,          SHCMD("$BROWSER") },
	{ MODKEY,                       XK_a,      togglescratch,  {.v = pulsemixercmd } },
	{ MODKEY,                       XK_s,      togglescratch,  {.v = gotopcmd } },
	{ MODKEY,                       XK_c,      togglescratch,  {.v = bccmd } },
	{ Mod1Mask|ControlMask,         XK_m,      spawn,          SHCMD("st -c ncmpcppterm -e ncmpcpp") },
	{ Mod1Mask|ControlMask,	        XK_r,      spawn,          SHCMD("st -c newsboatterm -e newsboat") },
	{ Mod1Mask|ControlMask,	        XK_u,      spawn,          SHCMD("dmenuunicode") },
	{ Mod1Mask|ControlMask,	        XK_x,      spawn,          SHCMD("sstocb") },
	{ Mod1Mask|ControlMask,	        XK_s,      spawn,          SHCMD("sstop") },
	{ Mod1Mask|ShiftMask,	          XK_x,      spawn,          SHCMD("colorp") },
	{ Mod1Mask|ControlMask,	        XK_c,      spawn,          SHCMD("toggleprogram picom") },
	{ Mod1Mask|ControlMask,	        XK_l,      spawn,          SHCMD("lock") },
	{ MODKEY,                       XK_0,      scratchpad_show,{0} },
	{ MODKEY|ShiftMask,             XK_0,      scratchpad_hide,{0} },
	{ MODKEY,                       XK_Escape, scratchpad_remove,{0} },
	{ MODKEY|ShiftMask,		          XK_s,	     spawn,	         SHCMD("transset-df -a --dec .1") },
	{ MODKEY|ShiftMask,		          XK_d,	     spawn,	         SHCMD("transset-df -a --inc .1") },
	{ MODKEY|ShiftMask,		          XK_f,	     spawn,	         SHCMD("transset-df -a .75") },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY|ShiftMask,             XK_h,      setcfact,       {.f = +0.25} },
	{ MODKEY|ShiftMask,             XK_l,      setcfact,       {.f = -0.25} },
	{ MODKEY|ShiftMask,             XK_o,      setcfact,       {.f =  0.00} },
	{ MODKEY|ShiftMask,             XK_j,      movestack,      {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_k,      movestack,      {.i = -1 } },
	{ MODKEY,                       XK_s,      swapfocus,      {.i = -1 } },
	{ MODKEY,                       XK_Return, zoom,           {0} },
	{ MODKEY|Mod4Mask,              XK_u,      incrgaps,       {.i = +1 } },
	{ MODKEY|Mod4Mask|ShiftMask,    XK_u,      incrgaps,       {.i = -1 } },
	{ MODKEY|Mod4Mask,              XK_i,      incrigaps,      {.i = +1 } },
	{ MODKEY|Mod4Mask|ShiftMask,    XK_i,      incrigaps,      {.i = -1 } },
	{ MODKEY|Mod4Mask,              XK_o,      incrogaps,      {.i = +1 } },
	{ MODKEY|Mod4Mask|ShiftMask,    XK_o,      incrogaps,      {.i = -1 } },
	{ MODKEY|Mod4Mask,              XK_6,      incrihgaps,     {.i = +1 } },
	{ MODKEY|Mod4Mask|ShiftMask,    XK_6,      incrihgaps,     {.i = -1 } },
	{ MODKEY|Mod4Mask,              XK_7,      incrivgaps,     {.i = +1 } },
	{ MODKEY|Mod4Mask|ShiftMask,    XK_7,      incrivgaps,     {.i = -1 } },
	{ MODKEY|Mod4Mask,              XK_8,      incrohgaps,     {.i = +1 } },
	{ MODKEY|Mod4Mask|ShiftMask,    XK_8,      incrohgaps,     {.i = -1 } },
	{ MODKEY|Mod4Mask,              XK_9,      incrovgaps,     {.i = +1 } },
	{ MODKEY|Mod4Mask|ShiftMask,    XK_9,      incrovgaps,     {.i = -1 } },
	{ MODKEY|Mod4Mask,              XK_0,      togglegaps,     {0} },
	{ MODKEY|Mod4Mask|ShiftMask,    XK_0,      defaultgaps,    {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY|ShiftMask,             XK_c,      killclient,     {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_y,      togglefullscreen, {0} },
	{ MODKEY,                       XK_s,      togglesticky,   {0} },
	{ Mod1Mask,                     XK_j,      moveresize,     {.v = "0x 25y 0w 0h" } },
	{ Mod1Mask,                     XK_k,      moveresize,     {.v = "0x -25y 0w 0h" } },
	{ Mod1Mask,                     XK_l,      moveresize,     {.v = "25x 0y 0w 0h" } },
	{ Mod1Mask,                     XK_h,      moveresize,     {.v = "-25x 0y 0w 0h" } },
	{ Mod1Mask|ShiftMask,           XK_j,      moveresize,     {.v = "0x 0y 0w 25h" } },
	{ Mod1Mask|ShiftMask,           XK_k,      moveresize,     {.v = "0x 0y 0w -25h" } },
	{ Mod1Mask|ShiftMask,           XK_l,      moveresize,     {.v = "0x 0y 25w 0h" } },
	{ Mod1Mask|ShiftMask,           XK_h,      moveresize,     {.v = "0x 0y -25w 0h" } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
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
	{ MODKEY|ShiftMask,             XK_r,      quit,           {1} }, 

	/* External programs */
	{ Mod1Mask|ControlMask,		XK_p,		spawn,          SHCMD("mpc toggle") },
	{ Mod1Mask|ShiftMask,		XK_p,		spawn,          SHCMD("mpc stop") },
	{ Mod1Mask|ControlMask,		XK_comma,	spawn,          SHCMD("mpc prev") },
	{ Mod1Mask|ControlMask,		XK_period,	spawn,          SHCMD("mpc next") },
	{ Mod1Mask|ShiftMask,		XK_comma,	spawn,          SHCMD("mpc seek -10") },
	{ Mod1Mask|ShiftMask,		XK_period,	spawn,          SHCMD("mpc seek +10") },
	{ Mod1Mask|ControlMask,		XK_minus,	spawn,          SHCMD("pamixer --allow-boost -d 5; dunstify -r 2 \"VOL: $(pamixer --get-volume-human)\"") },
	{ Mod1Mask|ControlMask,		XK_equal,	spawn,          SHCMD("pamixer --allow-boost -i 5; dunstify -r 2 \"VOL: $(pamixer --get-volume-human)\"") },
	{ Mod1Mask|ControlMask,		XK_BackSpace,	spawn,          SHCMD("pamixer -t; dunstify -r 2 \"$(pamixer --get-volume-human)\"") },
	{ Mod1Mask|ShiftMask,		XK_minus,	spawn,          SHCMD("xbacklight -dec 10; dunstify -r 3 \"BRIGHT: $(xbacklight -get | awk '{print int($1)}')\"") },
	{ Mod1Mask|ShiftMask,		XK_equal,	spawn,          SHCMD("xbacklight -inc 10; dunstify -r 3 \"BRIGHT: $(xbacklight -get | awk '{print int($1)}')\"") },

/* Extra keyboard keys */
	{ 0, XF86XK_AudioMute,		spawn,		SHCMD("pamixer -t") },
	{ 0, XF86XK_AudioRaiseVolume,	spawn,		SHCMD("pamixer --allow-boost -i 5") },
	{ 0, XF86XK_AudioLowerVolume,	spawn,		SHCMD("pamixer --allow-boost -d 5") },
	{ 0, XF86XK_AudioPrev,		spawn,		SHCMD("mpc prev") },
	{ 0, XF86XK_AudioNext,		spawn,		SHCMD("mpc next") },
	{ 0, XF86XK_AudioPause,		spawn,		SHCMD("mpc pause") },
	{ 0, XF86XK_AudioPlay,		spawn,		SHCMD("mpc play") },
	{ 0, XF86XK_AudioStop,		spawn,		SHCMD("mpc stop") },
	{ 0, XF86XK_AudioRewind,	spawn,		SHCMD("mpc seek -10") },
	{ 0, XF86XK_AudioForward,	spawn,		SHCMD("mpc seek +10") },
	{ 0, XF86XK_AudioMedia,		spawn,		SHCMD("st -e ncmpcpp") },
	/* { 0, XF86XK_PowerOff,		spawn,		SHCMD("sysact") }, */
	{ 0, XF86XK_Calculator,		spawn,		SHCMD("st -e bc -l") },
	{ 0, XF86XK_Sleep,		spawn,		SHCMD("sudo -A zzz") },
	{ 0, XF86XK_WWW,		spawn,		SHCMD("$BROWSER") },
	{ 0, XF86XK_DOS,		spawn,		SHCMD("st") },
	{ 0, XF86XK_ScreenSaver,	spawn,		SHCMD("lock") },
	{ 0, XF86XK_TaskPane,		spawn,		SHCMD("st -e htop") },
	{ 0, XF86XK_Mail,		spawn,		SHCMD("st -e neomutt") },
	{ 0, XF86XK_MyComputer,		spawn,		SHCMD("st -e lf /") },
	/* { 0, XF86XK_Battery,		spawn,		SHCMD("") }, */
	{ 0, XF86XK_Launch1,		spawn,		SHCMD("xset dpms force off") },
	{ 0, XF86XK_TouchpadToggle,	spawn,		SHCMD("toggletouchpad") },
	{ 0, XF86XK_TouchpadOff,	spawn,		SHCMD("toggletouchpad on") },
	{ 0, XF86XK_TouchpadOn,		spawn,		SHCMD("toggletouchpad off") },
	{ 0, XF86XK_MonBrightnessUp,	spawn,		SHCMD("xbacklight -inc 10") },
	{ 0, XF86XK_MonBrightnessDown,	spawn,		SHCMD("xbacklight -dec 10") },
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
	{ ClkClientWin,         MODKEY|ShiftMask, Button3,      dragcfact,      {0} },
	{ ClkClientWin,         MODKEY|ShiftMask, Button1,      dragmfact,      {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

