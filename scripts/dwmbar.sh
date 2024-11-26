#!/bin/bash

interval=0

vol() {
    curStatus=$(pactl get-sink-mute @DEFAULT_SINK@)
    volume=$(pactl get-sink-volume @DEFAULT_SINK@ | tail -n 2 | sed -e 's,.* \([0-9][0-9]*\)%.*,\1,' | head -n 1)

    if [ "${curStatus}" = 'Mute: yes' ]; then
        echo " $volume%"
    else
        echo "  $volume%"
    fi
}

brightness() {
    printf " "
    printf "%.0f\n" $(brillo)
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
    acpi --ac-adapter | grep 'off' &>/dev/null
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
    printf " $(sensors | grep 'Core 0' | awk '{print $3}' | tr -d '+')"
}

fan_speed() {
    printf "  $(sensors | grep cpu_fan | awk 'NR==1{print $2}') RPM"
}

weather() {
    condition=$(curl -s v2.wttr.in | grep -e "Weather" | sed -n 2p | sed 's/Weather://g' | sed 's/,//g' | sed 's/+//g' | sed 's/°C.*/°C/' | sed 's/.*m//' | sed 's/^[^a-zA-Z0-9]*//g')

    case "$condition" in
    *clear*) icon=" " ;;
    *cloudy*) icon=" " ;;
    *rain* | *drizzle* | *overcast*) icon=" " ;;
    *snow*) icon="󰜗 " ;;
    *thunderstorm*) icon="󰖓 " ;;
    *fog*) icon=" " ;;
    *wind*) icon=" " ;;
    *haze*) icon="絛" ;;
    *) icon="󰇧 " ;;
    esac

    printf "$icon $condition"
}

down_speed() {
    RECEIVE1=$(cat /sys/class/net/wlo1/statistics/rx_bytes)
    sleep 1
    RECEIVE2=$(cat /sys/class/net/wlo1/statistics/rx_bytes)

    BYTE_DIFF=$((RECEIVE2 - RECEIVE1))

    DOWNLOAD_SPEED=$((BYTE_DIFF * 8 / 1000000))

    printf " $DOWNLOAD_SPEED Mbit/s"
}

up_speed() {
    TRANSMIT1=$(cat /sys/class/net/wlo1/statistics/tx_bytes)
    sleep 1
    TRANSMIT2=$(cat /sys/class/net/wlo1/statistics/tx_bytes)

    BYTE_DIFF=$((TRANSMIT2 - TRANSMIT1))

    UPLOAD_SPEED=$((BYTE_DIFF * 8 / 1000000))

    printf "  $UPLOAD_SPEED Mbit/s"
}

while true; do

    [ $interval = 0 ] || [ $(($interval % 3600)) = 0 ]

    sleep 1 && xsetroot -name "$(date_time) ; $(vol)  $(battery)  $(brightness)  $(mem)  $(cpu)  $(down_speed) $(up_speed) "
done
