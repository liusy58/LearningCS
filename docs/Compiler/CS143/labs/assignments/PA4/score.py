import glob, os

files = glob.glob("./grading/*.test")
score = 0
for file in files:
    os.system("cp " + file + "  " + file[10:])
    file = file[10:]
    # print(file)

    solution_file = "output/" + file[:-5] + "_solution.txt"
    output_file = "output/" + file[:-5] + "_output.txt"
    # print("solution_file:    ", solution_file )
    # print("output_file:    ", output_file )

    cmd = "bash mysemant " + file + " > " + output_file + " 2>&1"
    get_solution_command = "bash semant.sh " + file +" > " +solution_file + " 2>&1"
    # print("cmd:   " + cmd)
    # print("get_solution_command:   " + get_solution_command)
    os.system(cmd)
    os.system(get_solution_command)

    my_output = open(output_file)
    answer = open(solution_file)

    my_output_lines = my_output.readlines()
    answer_lines = answer.readlines()

    succeed = True
    for i in range(len(my_output_lines)):
        if my_output_lines[i] != answer_lines[i]:
            # print(my_output_lines[i], "    ", answer_lines[i])
            succeed = False
            break
    if len(my_output_lines) != len(answer_lines):
        succeed = False
    if succeed:
        print("PASS: ", file)
        score += 1
        os.system("rm -rf " + solution_file)
        os.system("rm -rf " + output_file)
    else:
        print("FAILED: ", file)

    os.system("rm -rf " + file)
    os.system("rm -rf temp.txt")
    os.system("rm -rf solution.txt")

print("You got " + str(score) + " out of " + str(len(files)))
