# Dwm
my fork of suckless dwm

# Patches
- vanity gaps
- layouts (centered master, fibonacci, bstack,gapless grid. horiz grid)
- Actual full screen
- Swallow
- Alpha for dwm bar transpareny
- Notitle
- Attach below (with binding)
- Splitstatus to get date and time in the center of the bar
- always center

# Requirements

```
yay -S ttf-jetbrains-mono-nerd xwallpaper 
```

# Installation

```
git clone https://github.com/fruitsaladchan/dwm.git
cd dwm
sudo make install
```

# Extra

- i am using [luke smiths st](https://github.com/LukeSmithxyz/st) for my terminal
- if you want my bar move the dwmbar.sh in your ~/.local/bin/ and start it up with xinitrc
- i am using [brillo](https://github.com/CameronNemo/brillo) for brightness 
- i am also using picom with this setup to get animations and blurred terminals. if you want to use my config move the picom.conf to ~/.config/picom/
