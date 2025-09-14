#!/bin/bash
if [[ ! -x "./debug" ]]; then
	echo "Error: ./debug executable not found or not executable." >&2
	exit 1
fi

run_test() {
	clear
	DEBUG_FILE="./debug"
	local cmd="$1"

	$DEBUG_FILE "$cmd"
	echo -e "\nTesting command: [$cmd]\n"
	echo -ne "\nPress [Enter] to continue or [Esc] to quit..."
	while true; do
		read -rsn1 key
		if [[ "$key" == $'\e' ]]; then
			read -rsn2 -t 0.01
			if [[ $? -ne 0 ]]; then
				echo -e "\n\nAborting tests."
				exit 0
			fi
		elif [[ -z "$key" ]]; then
			break
		fi
	done
}

COMMANDS=(
	"ls -l"
	"echo"
	"echo 'Hello world!'"
	"echo \"Hello world!\""
	"echo \"'Single' in double\""
	"echo '\"Double\" in single'"
	"echo \" Spaces at ends \""
	"    echo     Hello     World!    "
	"echo      "
	"echo '    '"
	"echo ''"
	"echo \"\""
	"ls | wc -l"
	"cat hello.txt | grep 'world!' | sort"
	"echo Hello! > file"
	"cat < file"
	"echo Hello! >> file"
	"cat << EOF"
	"ls > file < file"
	"> file ls -l"
	"< file cat"
	"echo Hello! > file > file"
	"true && echo success"
	"false || echo success"
	"true && false || echo third"
	"echo a && echo b | cat || echo c"
	"echo a | echo b && echo c | echo d"
	"echo \$HOME"
	"echo \"\$HOME\""
	"echo '\$HOME'"
	"echo '\"\$HOME\"'"
	"echo \"'\$HOME'\""
	"(ls)"
	"(ls | wc -l)"
	"echo Hello && (ls | wc -l) || echo world!"
	"(echo a && echo b) | wc -l"
	"cat < file | grep 'abc' > file"
	"((echo a) && (echo b)) | (grep a)"
	"(echo a && echo b) || (echo c && echo d)"
	"true || (false && true) && echo x"
	"echo abc \"def\" | echo ghi < file >> file"
	""
	"   "
	"echo \"Hello"
	"echo 'World!"
	"(ls"
	"ls)"
	"((ls)"
	")("
	"| ls"
	"ls |"
	"&& ls"
	"ls &&"
	"|| ls"
	"ls ||"
	"ls || | wc"
	"ls && | wc"
	"ls | | wc"
	"ls && && ls"
	"| |"
	"&& ||"
	">"
	"<"
	">>"
	"<<"
	"|"
	"&&"
	"||"
	"ls >"
	"> | ls"
	"echo < >"
	"echo < file < file"
	"()"
	"ls ()"
	"echo (hello)"
	"ls || && echo fail"
	"ls | | | wc"
	"((()))"
	"( ( ( echo deep ) ) )"
	")command("
	"((echo hello)"
	"echo)world("
	"ls < < < file"
)

for cmd in "${COMMANDS[@]}"; do
	touch file
	run_test "$cmd"
	rm file
done

clear
echo -e "All tests completed.\n"
echo "Press any key to exit."
read -rsn1 -p ""
