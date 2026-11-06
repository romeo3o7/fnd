#!/usr/bin/env bash
set -euo pipefail

check_status() {
	local status_in=$1 invoker=$2
	if (( "$status_in" != 0 )); then 
		printf '%s : failed\n' "$invoker"
		return 1
	fi
	return 0

}
confirmation() {
	# confirmation "msg" "prompt"
	# returns 0 for yes, 2 for no, 3 for quit, 1 on EOF/error
	# call it as: if confirmation ...; then rc=0; else rc=$?; fi   (a bare call dies under set -e)
	local msg=$1 prompt=$2 reply
	if [[ -z $msg && -z $prompt ]]; then return 1
	fi
	printf '\n%s\n\n' "$msg" >&2

	while true; do
		read -r -p "$prompt" reply || return 1
		case "${reply,,}" in
			y) return 0 ;;
			n) return 2 ;;
			q) return 3 ;;
			*) printerr "Invalid choice" ;;
		esac
	done
}

__update() {
	local rv=0 opt
	dnf check-update --refresh
	rv=$?
	if (( "$rv" != 0 && "$rv" != 100 )); then
		printf "dnf failed\n"
		return "$rv"
	fi
	if (( "$rv" == 0  )); then
		printf "up to date\n"
		return "$rv"
	fi

	printf 'update found, [l]ocal update , [o]ffline or [c]ancel?\n'
	
	while true; do
		read -r -p "[l/f/c]" reply
		if [[ ${#reply} -eq 1 ]]; then
			case "${reply,,}" in
				l) 
					sudo dnf upgrade
					if ! check_status $? "upgrade"; then
						return 1
					fi
					return 0
					;;
				f) 	
					sudo dnf upgrade --offline
					if ! check_status $? "upgrade offline"; then
						return 1
					fi
					# confirm 
					if confirmation "perform offline transaction now?[y/n/q] "; then rv=0
						else rv=$?
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

					break;
					;;

				c) return 0 ;;
				*) continue;;
			esac
		fi
	done
}

__update
