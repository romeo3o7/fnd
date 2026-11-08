_invoke_update() {
    local rv=0
    dnf check-update --refresh
    rv=$?

    if (( rv != 0 && rv != 100 )); then
        printf 'dnf update checking failed\n' >&2
        return 1
    fi
	if (( "$rv" == 0 )); then
		printf 'Up to date\n' >&2
		return 0
	fi

	if ! _preformUpdate; then
		return 1
	fi

}

_preformUpdate() {
	local reply rv
    printf 'update found, [l]ocal update, [o]ffline or [c]ancel?\n'
    while true; do
        read -r -p "[l/o/c]: " reply || return 1
        if [[ ${#reply} -eq 1 ]]; then
            case "${reply,,}" in
                l)
                    if ! sudo dnf update; then
						return 1
					fi
                    return 0
                    ;;
                o)
					if ! check_command dnf5; then
						return 1
					fi
                    if ! sudo dnf upgrade --offline; then
						return 1
					fi

                    if confirmation "Perform offline transaction now?" "[y/n]: "; then
                        rv=0
                    else
                        rv=$?
                    fi

                    case $rv in
                        0)
                            if ! sudo dnf5 offline reboot -y; then
								return 1
							fi
                            break
                            ;;
                        *) return 1 ;;
                    esac
                    ;;
                c) return 0 ;;
                *) printf 'Invalid choice\n' >&2; continue ;;
            esac
        fi
    done
}
