# Dwm
my fork of suckless dwm

# Patches
- vanity gaps
- layouts (centered master, fibonacci, bstack,gapless grid. horiz grid)
- actual full screen
- swallow
- alpha for dwm bar transpareny
- notitle
- attach below
- splitstatus to get date and time in the center of the bar

# Requirements

```
yay -S ttf-jetbrains-mono-nerd
```

# Installation

```
git clone https://github.com/fruitsaladchan/dwm.git
cd dwm
sudo make install
```

# Extra

- i am using [luke smiths st](https://github.com/LukeSmithxyz/st) for my terminal
- if you want my bar move the dwmbar.sh in your ~/.local/bin/ and start it up with xprofile
- i am also using picom with this setup to get animations and blurred terminals. if you want to use my config move the picom.conf to ~/.config/picom/
