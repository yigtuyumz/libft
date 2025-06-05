#!/usr/bin/env bash
RED=$(tput setaf 1)
GREEN=$(tput setaf 2)
YELLOW=$(tput setaf 3)
BLUE=$(tput setaf 4)
RESET=$(tput sgr0)
MSG_SUCC="${GREEN}+ Success!${RESET}  "
MSG_ERR="${RED}x Error!${RESET}    "
MSG_WARN="${YELLOW}! Warning${RESET}   "
MSG_INFO="${BLUE}i Info${RESET}      "
WRONG_INPUT="w4nn46043"
TEST_SUCCESS="wh3nw1lluf41l"
TEST_FAIL="66wpuf41l3d"

SCRIPT_DIR=$(cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" &> /dev/null && pwd)
MINIFIER_PATH="${SCRIPT_DIR}/minifier.py"

banner() {
  printf "%s\n" \
' ________ _________  _______   ________  _________  _______   ________     ' \
'|\  _____\\___   ___\\  ___ \ |\   ____\|\___   ___\\  ___ \ |\   __  \    ' \
'\ \  \__/\|___ \  \_\ \   __/|\ \  \___|\|___ \  \_\ \   __/|\ \  \|\  \   ' \
' \ \   __\    \ \  \ \ \  \_|/_\ \_____  \   \ \  \ \ \  \_|/_\ \   _  _\  ' \
'  \ \  \_|     \ \  \ \ \  \_|\ \|____|\  \   \ \  \ \ \  \_|\ \ \  \\  \| ' \
'   \ \__\       \ \__\ \ \_______\____\_\  \   \ \__\ \ \_______\ \__\\ _\ ' \
'    \|__|        \|__|  \|_______|\_________\   \|__|  \|_______|\|__|\|__|' \
'                                 \|_________|                              ' \
'                                                                  wannago43' \
'                                                                           '
}

# arg 1 is the message of the prompt
yn_prompt() {
  local answer
  echo -n "${1} [y/N] "

  IFS= read -r -n 1 answer
  echo ""
  case "$answer" in
    [Yy]) return 0 ;;
    *)    return 1 ;;
  esac
}

file_exists() {
  if [ -f "${1}" ];then
    return 0
  else
    return 1
  fi
}

set_src() {
  local out_fil_name compressed_headers compressed_srcs test_files main_str test_filelist
  main_str="int main(int a, char *b[]){"
  if [ -z "${1}" ]; then
    return
  else
    out_fil_name="${SCRIPT_DIR}/${1}"
  fi
  if file_exists "${out_fil_name}"; then
    if ! yn_prompt "${MSG_WARN} Compressed source file exists. Do you want to overwrite?"; then
      return
    fi
  fi
  echo "${MSG_INFO} Compressing sources..."
  compressed_srcs=$(find "${SCRIPT_DIR}/../" -maxdepth 1 -name 'ft_*.c' -type f -exec python3 "${MINIFIER_PATH}" {} + | sed "/#include \"libft.h\"/d; /^$/d")
  compressed_headers=$(find "${SCRIPT_DIR}/../" -maxdepth 1 -name '*.h' -type f -exec python3 "${MINIFIER_PATH}" {} + | sed "/^$/d")
  if [ "$(find "${SCRIPT_DIR}/extra/" -maxdepth 1 -name '*.c' -type f 2>/dev/null | wc -l)" -ne 0 ]; then
    echo "${MSG_INFO} Appending test sources..."
    test_files=$(find "${SCRIPT_DIR}/extra" -maxdepth 1 -name '*.c' -type f -exec python3 "${MINIFIER_PATH}" {} + | sed "/^\s*#\(define\|include\)/d;/^\s*$/d")
    test_filelist=$(find "${SCRIPT_DIR}/extra" -maxdepth 1 -name '*.c' -type f)
    for file in "${test_filelist[@]}"; do
      # get only filename; ./path/file.tar.gz -> file.tar.gz
      file="${file##*/}"
      # remove extension; ./path/file.tar.gz -> file.tar
      file="${file%.*}"
      main_str="${main_str}${file}(a,b);"
    done
    main_str="${main_str}return (0);}"
  else
    main_str="int main(int a, char *b[]){return (0);}"
    echo "${MSG_WARN} No C file in ${SCRIPT_DIR}/extra"
  fi
  printf "\
#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <signal.h>
#define __DEBUG__
#define WRNG \"%s\"
#define SUCC \"%s\"
#define FAIL \"%s\"
%s
%s
%s
%s
" "${WRONG_INPUT}" "${TEST_SUCCESS}" "${TEST_FAIL}" "${compressed_headers}" "${compressed_srcs}" "${test_files}" "${main_str}"> "${out_fil_name}"
  # remove redundant header includes, which comes from C sources.
  sed -i '17,$ {/include/d}' "${out_fil_name}"
  echo "${MSG_SUCC} Minified sources"
}


compile_src() {
  local file_name

  if [ -z "${1}" ]; then
    return
  else
    file_name="${1}"
  fi
  echo "${MSG_INFO} Compiling..."
  if ! gcc "${file_name}" -o "${file_name%%.*}" 2>/dev/null; then
    echo "${MSG_ERR} Something went wrong while compiling compressed source!"
    return 1
  else
    echo "${MSG_SUCC} Done!"
  fi
}

run_tests() {
  return
}

main() {
  local compressed_file
  compressed_file="out.c"

  stty -echo
  clear
  banner
  set_src "${compressed_file}"
  # compile_src "${compressed_file}"
  run_tests
  echo
  stty echo
}

main
