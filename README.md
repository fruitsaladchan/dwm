# dwm
my fork of suckless dwm

# Patches
- vanity gaps
- layouts (centered master, fibonacci, bstack,gapless grid. horiz grid)
- actual full screen
- swallow
- xrdb (to read pywal colors)

# Requrirments

```
yay -S ttf-jetbrains-mono-nerd picom 
```

# Installation

```
git clone https://github.com/frtuisaladchan/dwm
cd dwm
sudo make install
```

# Extra

- i am using [luke smiths st](https://github.com/LukeSmithxyz/st) for my terminal
- if you want my bar move the dwmbar.sh in your ~/.local/bin/ and start it up with xprofile
- to use pywal with dwm move the setbg script into your ~/.local/bin/ and use that to change wallpapers
- i am also using picom with this setup to get animations and blurred terminals. if you want to use my config move the picom.conf to ~/.config/picom/
