#!/bin/bash

interval=0

# vol() {
#     amixer sget Master | grep 'off' &> /dev/null
#     if [ $? -eq 0 ] 
#     then 
#         printf "^c$blue^^b$black^  "
#     else
#         printf "^c$blue^^b$black^  "
#     fi
#     value="$(awk -F"[][]" '/Left:/ { print $2 }' <(amixer sget Master))"
#     printf "^c$blue^^b$black^$value%"
# }

brightness() {
  printf "  "
  printf "%.0f\n" $(cat /sys/class/backlight/acpi_video0/brightness)
}


mem() {
  printf " "
  printf "$(free -h | awk '/^Mem/ { print $3 }' | sed s/i//g)"
}

cpu() {
  cpu_val=$(mpstat 1 1 | awk '/Average/ {printf "%.1f", 100 - $NF}')

  printf " %s%%\n" "$cpu_val"
}

battery() {
    acpi --ac-adapter | grep 'off' &> /dev/null
    if [ $? -eq 0 ]; then
        value=$(acpi -b | grep -oP '(?<=, )\d+(?=%)')

        int_value=$(printf "%.0f" "$value")

        if ((int_value > 98)); then
            icon=" " 
        elif ((int_value > 75)); then
            icon=" "
        elif ((int_value > 40)); then
            icon=" "
        elif ((int_value > 10)); then
            icon=" "
        else
            icon=" "
        fi

        printf "$icon"
    else
        printf " "  
    fi

    get_capacity=$(acpi -b | grep -oP '(?<=, )\d+(?=%)')
    printf "$get_capacity%%"
}


wlan() {
	case "$(cat /sys/class/net/wl*/operstate 2>/dev/null)" in
    up) printf "  $(iwgetid -r)" ;;
	down | dormant) printf "󰤭  Disconnected" ;;
	esac
}


date_time() {
	printf " $(date '+%a %d %B') |  $(date '+%I:%M %p')"
}

temp() {
    printf  " $(sensors | grep 'Core 0' | awk '{print $3}' | tr -d '+')"
}

while true; do

    [ $interval = 0 ] || [ $(($interval % 3600)) = 0 ]

    sleep 1 && xsetroot -name "$(date_time) ; $(wlan)  $(battery)  $(temp)  $(mem)  $(cpu) "
done


