#!/bin/bash

options="Shutdown\nRestart\nSleep"

action=$(echo -e "$options" | dmenu -i -l 3)

if [[ -n "$action" ]]; then
    confirm=$(echo -e "Yes\nNo" | dmenu -i -l 3)

    if [[ "$confirm" == "Yes" ]]; then
        case "$action" in
        Shutdown)
            shutdown now
            ;;
        Restart)
            reboot
            ;;
        Sleep)
            systemctl suspend
            ;;
        *)
            exit 1
            ;;
        esac
    fi
fi
