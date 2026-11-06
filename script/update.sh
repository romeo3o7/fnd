invoke_update() {
    local rv=0 reply

    # Temporarily disable set -e because dnf check-update returns 100 on updates available
    set +e
    dnf check-update --refresh
    rv=$?
    set -e

    if (( rv != 0 && rv != 100 )); then
        printf "dnf failed\n" >&2
        return "$rv"
    fi
    if (( rv == 0 )); then
        printf "up to date\n"
        return "$rv"
    fi

    printf 'update found, [l]ocal update, [o]ffline or [c]ancel?\n'

    while true; do
        read -r -p "[l/o/c]: " reply
        if [[ ${#reply} -eq 1 ]]; then
            case "${reply,,}" in
                l)
                    sudo dnf upgrade
                    if ! check_status $? "upgrade"; then
                        return 1
                    fi
                    return 0
                    ;;
                o)
                    sudo dnf upgrade --offline
                    if ! check_status $? "upgrade offline"; then
                        return 1
                    fi

                    # Pass both message and prompt correctly
                    if confirmation "Perform offline transaction now?" "[y/n/q]: "; then
                        rv=0
                    else
                        rv=$?
                    fi

                    case $rv in
                        0)
                            sudo dnf5 offline reboot -y
                            if ! check_status $? "offline reboot"; then
                                return 1
                            fi
                            break
                            ;;
                        2) return 0 ;;
                        3) return 1 ;;
                        *) return 2 ;;
                    esac
                    ;;
                c) return 0 ;;
                *) printf 'Invalid choice\n' >&2; continue ;;
            esac
        fi
    done
}
