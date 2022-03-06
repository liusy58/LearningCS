import glob, os


files = glob.glob("./grading/*.test")
score = 0
for file in files:
    cmd = "bash myparser " + file
    os.system(cmd + "> temp.txt")

    my_output = open("temp.txt")
    answer = open(file+".out")

    my_output_lines = my_output.readlines()
    answer_lines = answer.readlines()

    succeed = True
    for i in range(len(my_output_lines)):
        if "#" in my_output_lines[i] and "#" in answer_lines[i]:
            continue
        if my_output_lines[i] != answer_lines[i]:
            succeed = False
            break
    if succeed:
        score += 1


print("You got " + str(score) + " out of " + str(len(files)))













