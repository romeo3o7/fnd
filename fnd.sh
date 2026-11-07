#!/usr/bin/env bash
__main() {
	set -uo pipefail
	script_path=$(readlink -f "${BASH_SOURCE[0]}")
	script_dir=$(dirname "$script_path")
	for module in update helpers package; do
		source "$script_dir/$module.sh"
	done
	case "${1:-}" in
		up)
			if ! invoke_update; then
				return 1
			fi
		;;
		pkg)
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
