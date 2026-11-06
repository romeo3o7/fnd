#!/usr/bin/env bash
set -euo pipefail
script_path=$(readlink -f "${BASH_SOURCE[0]}")
script_dir=$(dirname "$script_path")
for module in update helpers; do
	source "$script_dir/$module.sh"
done
invoke_update
