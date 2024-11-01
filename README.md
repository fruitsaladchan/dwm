# Dwm
my fork of suckless dwm

![img1](assets/dwm1.png)


![img2](assets/dwm2.png)



# Patches
- vanity gaps
- layouts (centered master, fibonacci, bstack,gapless grid. horiz grid)
- Actual full screen
- Swallow
- Alpha (for dwm bar transpareny)
- Notitle
- Attach below (with tab binding)
- Splitstatus (used to get date and time in the center of the bar)
- Always center
- Sticky

# Requirements

```
yay -S ttf-jetbrains-mono-nerd xwallpaper xorg-server xorg-xinit xdotool libx11 libxinerama libxft xorg
```

# Installation

```
git clone https://github.com/fruitsaladchan/dwm.git
cd dwm
sudo make install
```
if you want to make changes to the configuration you need to edit config.h and recompile it with 

```
sudo make
sudo make install
```

# Extra

- i am using [luke smiths st](https://github.com/LukeSmithxyz/st) for my terminal + pywal
- if you want my bar move the dwmbar.sh in your ~/.local/bin/ and start it up with xinitrc
- i am using [brillo](https://github.com/CameronNemo/brillo) for brightness with a changebrighess script 
- i am also using picom with this setup to get animations and blurred terminals. if you want to use my config move the picom.conf to ~/.config/picom/
