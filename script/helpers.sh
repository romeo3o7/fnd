usage() {
cat <<'EOF'
fnd up : manages system update

fnd p <flag> <package/file> : checks for package/file specifed flag
flags:
	m	;ackage metadata
	d	package dependency
	r	package requirement
	i	package files installed
	o	package file-ownership
EOF
}
confirmation() {
    # confirmation "msg" "prompt"
    # returns 0 for yes, 2 for no, 3 for quit, 1 on EOF/error
    local msg=$1 prompt=$2 reply
    if [[ -z $msg && -z $prompt ]]; then
        return 1
    fi

    printf '\n%s\n\n' "$msg" >&2

    while true; do
        read -r -p "$prompt" reply || return 1
        case "${reply,,}" in
            y) return 0 ;;
            n) return 2 ;;
            *) printf 'Invalid choice\n' >&2 ;;
        esac
    done
}
