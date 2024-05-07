#!/usr/bin/env python3

import subprocess

# Program name
name = "execute"

# Valgrind
valgrind = "valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --suppressions=readline.supp -q --log-file=valgrind.log"

# Colours
GREEN = "\033[32;1m"
RED = "\033[31;1m"
COLOR_LIMITER = "\033[0m"
colours = [GREEN, RED, COLOR_LIMITER]

# Preparing environment.
trash = subprocess.run(f"make -C {name}", shell=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
subprocess.run("touch infile", shell=True)
subprocess.run("echo apple, banana, carrot, bread > infile", shell=True)

# Input Samples:
input_data_list = ["\'cat < infile\'"]
output_data_list = [f'apple, banana, carrot, bread\n']

input_data_list.append("\'cat -e < infile\'")
output_data_list.append(f'apple, banana, carrot, bread$\n')

input_data_list.append("\'cat < infile -e | tr , . | tr a-z A-Z\'")
output_data_list.append(f'APPLE. BANANA. CARROT. BREAD$\n')

input_data_list.append("\'cat < infile -e | trX , . | echo melvin\'")
output_data_list.append(f'melvin\nCommand \'trX\' not found\n')

i = 1

for input_data, output_ref in zip(input_data_list, output_data_list):
	output = subprocess.run(f"{valgrind} ./{name}/{name} {input_data}", stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True, shell=True)
	outfile_content = output.stdout
	if outfile_content == output_ref:
		print(f"{colours[0]}{i}/{len(input_data_list)}.	OK  {colours[2]}")
	else:
		print(f"{colours[1]}{i}/{len(input_data_list)}.	KO  {colours[2]}")

	valgrind_status = subprocess.run('./valgrind.sh', stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True, shell=True)

	# Check for leaks
	if (valgrind_status.stdout == '0\n'):
		print(f"{colours[0]}	MOK  {colours[2]}")
	else:
		print(f"{colours[1]}	MKO  {colours[2]}")
	i = i + 1

trash = subprocess.run(f"rm infile", stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True, shell=True)
trash = subprocess.run(f"make fclean -C {name}", stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True, shell=True)