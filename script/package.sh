_package() {
    local flag=$1 obj=$2
    local -a rpm_cmd dnf_cmd
    local use_rpm=0

    case ${flag,,} in
        in)
			rpm_cmd=(rpm -ql)
			dnf_cmd=(dnf repoquery -l)
		;;
        req)
			rpm_cmd=(rpm -q --whatrequires)
			dnf_cmd=(dnf repoquery --whatrequires)
		;;
        dep)
			rpm_cmd=(rpm -qR)
			dnf_cmd=(dnf repoquery --requires)
		;;
        meta)
			rpm_cmd=(rpm -qi)
			dnf_cmd=(dnf info)
		;;
        own)
			rpm_cmd=(rpm -qf)
			dnf_cmd=(dnf provides)
		;;
        *)
			printf 'unrecognized flag\n' >&2
			return 1
		;;
    esac

	 if [[ ${flag,,} == own ]]; then
        if [[ -e $obj ]]; then
			use_rpm=1
		fi
    elif rpm -q -- "$obj" >/dev/null 2>&1; then
        use_rpm=1
    fi

    if (( use_rpm )); then
        "${rpm_cmd[@]}" "$obj"
    else
        "${dnf_cmd[@]}" "$obj"
    fi
}
