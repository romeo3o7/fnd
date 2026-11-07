_package() {
	local flag=$1 obj=$2
	rpm -q "$obj" >/dev/null 2>&1
	local installed=$?
	case ${flag,,} in
		i)
			if [[ "$installed" -eq 0 ]]; then
				rpm -ql "$obj"
			else
				dnf repoquery -l "$obj"
			fi
		;;
		r)
			if [[ "$installed" -eq 0 ]]; then
				rpm -q --whatrequires "$obj"
			else
				dnf repoquery --whatrequires "$obj"
			fi

		;;
		d)
			if [[ "$installed" -eq 0 ]]; then
				rpm -qR "$obj"
			else
				dnf repoquery --requires "$obj"
			fi
		;;
		m)
			if [[ "$installed" -eq 0 ]]; then
				rpm -qi "$obj"
			else
				dnf info "$obj"
			fi
		;;
		o)
			if [[ "$installed" -eq 0 ]]; then
				rpm -qf "$obj"
			else
				dnf provides "$obj"
			fi

		;;
		*)
			printf 'unrecognized flag\n' >&2
			return 1
		;;
	esac
}
