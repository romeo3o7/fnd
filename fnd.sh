#!/usr/bin/env bash
__main() {
	set -uo pipefail
	local script_path script_dir
	script_path=$(readlink -f "${BASH_SOURCE[0]}")
	script_dir=$(dirname "$script_path")
	source "$script_dir/helpers.sh"
	if ! check_command dnf rpm; then
		return 1
	fi

	case "${1:-}" in
		up)
			source "$script_dir/update.sh"
			if ! _invoke_update; then
				return 1
			fi
		;;
		pkg)
			source "$script_dir/package.sh"
			if [[ -z ${2:-} || -z ${3:-} ]]; then
				printf 'flag or package/file name not provided\n' >&2
				return 1
			fi
			if ! _package "$2" "$3"; then
				return 1
			fi
		;;
		*)
			usage
			return 0
		;;
	esac
}

__main "$@"
