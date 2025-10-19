import sys
#import subprocess

#subprocess.run(["ls", "-al"])


###############################################################################
# load a file into a list of lines.
###############################################################################
def load_file_lines(filename):
    lines = []
    try:
        with open(filename, 'r') as file:
            for line in file:
                cleansed = line.strip()
                if cleansed:
                    lines.append(cleansed)
        return lines
    except FileNotFoundError as fnfe:
        print(f"{fnfe}: can't find {filename}")
    except Exception as ex:
        print(f"{ex}: unexpected exception")

###############################################################################
# compare the contents of two files.
#
# note this may not be the fastest way; i want more info on why they're not equal.
###############################################################################
def compare_files(name, expected, actual):
    errors = []
    if (len(expected) != len(actual)):
        errors.append(f"{name} line length; {len(expected)} <> {len(actual)}")
    else:
        for i in range(len(expected)):
            if expected[i] != actual[i]:
                errors.append(f"{name}: line {i+1}: failed comparison")
        return errors


###############################################################################
# debug print the lines of a file.
###############################################################################
def debug_list(list, name):
    print(f"{name} has {len(list)} lines:")
    print(list)


###############################################################################
# main program entrypoint.
###############################################################################
# load the expected file
expected = load_file_lines('expected.txt')

# load the actual files, by language
c_output = load_file_lines('c.txt')
cpp_output = load_file_lines('cpp.txt')
rust_output = load_file_lines('rust.txt')
go_output = load_file_lines('go.txt')
java_output = load_file_lines('java.txt')

# debug print contents of files
#debug_list(expected, "expected")
#debug_list(c_output, "c")
#debug_list(cpp_output, "cpp")
#debug_list(rust_output, "rust")
#debug_list(go_output, "go")
#debug_list(java_output, "java")

# compare the files
errors = []
errors.append(compare_files('c', expected, c_output))
errors.append(compare_files('cpp', expected, cpp_output))
errors.append(compare_files('rust', expected, rust_output))
errors.append(compare_files('go', expected, go_output))
errors.append(compare_files('java', expected, java_output))

# print status
errors = list(filter(None, errors))
print(f"found {len(errors)} errors")
for e in range(len(errors)):
    print(f"error#{e}: {errors[e]}")

# return error count; 0 is success
sys.exit(len(errors))
