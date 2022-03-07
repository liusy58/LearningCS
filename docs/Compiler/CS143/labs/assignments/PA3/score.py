import glob, os


files = glob.glob("./grading/*.test")
score = 0
for file in files:
    os.system("cp " + file + "  " + file[10:])
    answer = open(file+".out")
    file = file[10:]
    print(file)
    cmd = "bash myparser " + file
    os.system(cmd + "> temp.txt 2>&1")
    my_output = open("temp.txt")

    my_output_lines = my_output.readlines()
    answer_lines = answer.readlines()

    succeed = True
    for i in range(len(my_output_lines)):
        if "#" in my_output_lines[i] and "#" in answer_lines[i]:
            continue
        if my_output_lines[i] != answer_lines[i]:
            print(my_output_lines[i], " != ", answer_lines[i])
            succeed = False
            break
    if succeed:
        score += 1
    os.system("rm -rf " + file)


print("You got " + str(score) + " out of " + str(len(files)))













