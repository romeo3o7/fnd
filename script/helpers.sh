check_status() {
    local status_in=$1 invoker=$2
    if (( status_in != 0 )); then
        printf '%s : failed\n' "$invoker" >&2
        return 1
    fi
    return 0
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
            q) return 3 ;;
            *) printf 'Invalid choice\n' >&2 ;;
        esac
    done
}
