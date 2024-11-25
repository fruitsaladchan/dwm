#!/bin/bash

options="Shutdown\nRestart\nSleep"

action=$(echo -e "$options" | dmenu -i -l 3)

# If user selects an action, confirm with a Yes/No prompt
if [[ -n "$action" ]]; then
    confirm=$(echo -e "Yes\nNo" | dmenu -i)

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

