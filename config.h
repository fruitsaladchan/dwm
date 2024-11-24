static const unsigned int borderpx = 1; /* border pixel of windows */
static const unsigned int snap = 32;    /* snap pixel */
static const int showbar = 1;           /* 0 means no bar */
static const int topbar = 1;            /* 0 means bottom bar */
static const int splitstatus = 1;       /* 1 for split status items */
static const char *splitdelim = ";"; /* Character used for separating status */
static const int swallowfloating = 0; /* 1 means swallow floating windows by default */
static const unsigned int gappih = 9; /* horiz inner gap between windows */
static const unsigned int gappiv = 9; /* vert inner gap between windows */
static const unsigned int gappoh = 9; /* horiz outer gap between windows and screen edge */
static const unsigned int gappov = 9; /* vert outer gap between windows and screen edge */
static int smartgaps = 0; /* 1 means no outer gap when there is only one window */
static const char *fonts[] = {
    "JetBrainsMono Nerd Font:size=12",
    "UbuntuMono Nerd Font:pixelsize=12:antialias=true"};
static const char dmenufont[] = "JetBrainsMono Nerd Font:size=10.5";
static const char col_gray3[] = "#f1be9b";
static const char col_gray1[] = "#020914";
static const char col_gray2[] = "#a8856c";
static const char col_gray4[] = "#f1be9b";
static const char col_cyan[] = "#63576E";
static const unsigned int baralpha = 140;
static const unsigned int borderalpha = 140;
static const char *colors[][3] = {
    /*               fg         bg         border   */
    [SchemeNorm] = {col_gray3, col_gray1, col_gray2},
    [SchemeSel] = {col_gray4, col_cyan, col_cyan},
};
static const unsigned int alphas[][3] = {
    /*               fg      bg        border*/
    [SchemeNorm] = {OPAQUE, baralpha, borderalpha},
    [SchemeSel] = {OPAQUE, baralpha, borderalpha},
};

/* tagging */
static const char *tags[] = {" 󰣇 ", "  ", "  ",
                             " 󰉋 ", "  ", "  "};

static const unsigned int ulinepad = 5;
static const unsigned int ulinestroke = 2;
static const unsigned int ulinevoffset = 0;
static const int ulineall = 0;

static const Rule rules[] = {
    /* xprop(1):
     *	WM_CLASS(STRING) = instance, class
     *	WM_NAME(STRING) = title
     */
    /* class                instance  title           tags mask  isfloating
       isterminal  noswallow  monitor */
    {"firefox", NULL, NULL, 1 << 8, 0, 0, -1, -1},
    {"St", NULL, NULL, 0, 0, 1, 0, -1},
};

/* layout(s) */
static const float mfact = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster = 1;    /* number of clients in master area */
static const int resizehints = 0; /* 1 means respect size hints in tiled resizals */
static int attachbelow = 1; /* 1 means attach at the end */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

#include "vanitygaps.c"
#include <X11/XF86keysym.h>
static const Layout layouts[] = {
    /* symbol     arrange function */
    {"[]=", tile}, /* first entry is default */
    {"><>", NULL}, /* no layout function means floating behavior */
    {"[M]", monocle},  {"|M|", centeredmaster}, {">M>", centeredfloatingmaster},
    {"TTT", bstack},   {"===", bstackhoriz},    {"[@]", spiral},
    {"[\\]", dwindle}, {"---", horizgrid},      {":::", gaplessgrid},
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY, TAG)                                                      \
  {MODKEY, KEY, view, {.ui = 1 << TAG}},                                       \
      {MODKEY | ControlMask, KEY, toggleview, {.ui = 1 << TAG}},               \
      {MODKEY | ShiftMask, KEY, tag, {.ui = 1 << TAG}},                        \
      {MODKEY | ControlMask | ShiftMask, KEY, toggletag, {.ui = 1 << TAG}},

#define SHCMD(cmd)                                                             \
  {                                                                            \
    .v = (const char *[]) { "/bin/sh", "-c", cmd, NULL }                       \
  }

/* commands */
static char dmenumon[2] =
    "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = {
    "dmenu_run", "-m",      dmenumon, "-fn",    dmenufont, "-nb",     col_gray1,
    "-nf",       col_gray3, "-sb",    col_cyan, "-sf",     col_gray4, NULL};
static const char *termcmd[] = {"kitty", NULL};

static const Key keys[] = {
    {MODKEY, XK_d, spawn, {.v = dmenucmd}},
    {MODKEY, XK_Return, spawn, {.v = termcmd}},
    {MODKEY, XK_b, togglebar, {0}},
    {MODKEY | ShiftMask, XK_s, spawn, SHCMD("flameshot gui")},
    {MODKEY, XK_s, togglesticky, {0}},
    {MODKEY, XK_a, togglegaps, {0}},
    {MODKEY, XK_p, spawn, SHCMD("dmenu-wallpaper.sh")},
    {MODKEY | ShiftMask, XK_a, defaultgaps, {0}},
    {MODKEY, XK_z, incrgaps, {.i = +3}},
    {MODKEY, XK_x, incrgaps, {.i = -3}},
    {MODKEY, XK_j, focusstack, {.i = +1}},
    {MODKEY, XK_k, focusstack, {.i = -1}},
    {MODKEY, XK_h, setmfact, {.f = -0.05}},
    {MODKEY, XK_l, setmfact, {.f = +0.05}},
    {MODKEY, XK_f, togglefullscr, {0}},
    {MODKEY, XK_space, zoom, {0}},
    {MODKEY, XK_Tab, toggleAttachBelow, {0}},
    {MODKEY, XK_q, killclient, {0}},
    {MODKEY, XK_t, setlayout, {.v = &layouts[0]}},
    {MODKEY | ShiftMask, XK_space, setlayout, {.v = &layouts[1]}},
    {MODKEY, XK_i, setlayout, {.v = &layouts[3]}},
    {MODKEY | ShiftMask, XK_i, setlayout, {.v = &layouts[4]}},
    {MODKEY | ShiftMask, XK_t, setlayout, {.v = &layouts[5]}},
    {MODKEY, XK_y, setlayout, {.v = &layouts[7]}},
    {MODKEY | ShiftMask, XK_y, setlayout, {.v = &layouts[8]}},
    {MODKEY, XK_u, setlayout, {.v = &layouts[9]}},
    {MODKEY | ShiftMask, XK_u, setlayout, {.v = &layouts[10]}},
    {MODKEY, XK_w, togglefloating, {0}},
    {MODKEY, XK_0, view, {.ui = ~0}},
    {MODKEY | ShiftMask, XK_0, tag, {.ui = ~0}},
    {MODKEY, XK_comma, focusmon, {.i = -1}},
    {MODKEY, XK_period, focusmon, {.i = +1}},
    {MODKEY | ShiftMask, XK_comma, tagmon, {.i = -1}},
    {MODKEY | ShiftMask, XK_period, tagmon, {.i = +1}},
    TAGKEYS(XK_1, 0) TAGKEYS(XK_2, 1) TAGKEYS(XK_3, 2) TAGKEYS(XK_4, 3)
        TAGKEYS(XK_5, 4) TAGKEYS(XK_6, 5) TAGKEYS(XK_7, 6) TAGKEYS(XK_8, 7)
            TAGKEYS(XK_9, 8){MODKEY | ShiftMask, XK_q, quit, {0}},
    {0, XF86XK_MonBrightnessUp, spawn, SHCMD("changebrightness up")},
    {0, XF86XK_MonBrightnessDown, spawn, SHCMD("changebrightness down")},
};

static const Button buttons[] = {
    /* click                event mask      button          function argument */
    {ClkLtSymbol, 0, Button1, setlayout, {0}},
    {ClkLtSymbol, 0, Button3, setlayout, {.v = &layouts[2]}},
    {ClkWinTitle, 0, Button2, zoom, {0}},
    {ClkStatusText, 0, Button2, spawn, {.v = termcmd}},
    {ClkClientWin, MODKEY, Button1, movemouse, {0}},
    {ClkClientWin, MODKEY, Button2, togglefloating, {0}},
    {ClkClientWin, MODKEY, Button3, resizemouse, {0}},
    {ClkTagBar, 0, Button1, view, {0}},
    {ClkTagBar, 0, Button3, toggleview, {0}},
    {ClkTagBar, MODKEY, Button1, tag, {0}},
    {ClkTagBar, MODKEY, Button3, toggletag, {0}},
};
